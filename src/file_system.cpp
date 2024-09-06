#include "file_system.hpp"

file_system::file_system(){
    temp = new int[10]{0};
    Work = new int[3]{0};

    a = new int*[ROW];
    b = new int*[ROW];
    for(int i{0}; i < ROW; i++){
        a[i] = new int[COLUMN]{0};
        b[i] = new int[COLUMN]{0};
    }
	freeMemoryList = new(memoryNode);
	freeMemoryList->address = freeMemoryList->length = 0;
	freeMemoryList->next = NULL;
	usedMemoryList = new(memoryNode);
	usedMemoryList->address = usedMemoryList->length = 0;
	usedMemoryList->next = NULL;
	x = MAX_Memory;
	create(freeMemoryList, 0, x);
	std::cout << "初始化成功!" << "\n\n";
	std::cout << "本次内存分配使用的是firstFit(首次适应算法)" << "\n";
}

file_system::~file_system(){
    if(temp != nullptr) delete temp;
    if(Work != nullptr) delete Work;
    if(a != nullptr) delete[] a;
    if(b != nullptr) delete[] b;
    if(freeMemoryList != nullptr) delete freeMemoryList;
    if(usedMemoryList != nullptr) delete usedMemoryList; 
}

MemoryNode file_system::create(MemoryNode& p, int address, int length, std::string name){
	p->next = new(memoryNode);
	MemoryNode q = p->next;
	q->name = name;
	q->address = address;
	q->length = length;
	q->next = NULL;
	return q;
}

void file_system::init_pcbc(PCBC* p){
	p->job = NULL;
	p->job_tail = NULL;
	p->run = NULL;
	p->ready = NULL;
	p->ready_tail = NULL;
	p->finish = NULL;
}

//分配磁盘空间
void file_system::distribute(PCB* run){
	int i, col, j, k, p, m, n, q, x, y, res, line = 0;
	PCB* FIN = run; 
	int count = 0;
	j = FIN->disk;
	for (i = 0; i < ROW && count != j; i++) {
		for (col = 0; col < COLUMN && count != j; col++) {
			if (a[i][col] == 1) {
				count = 0;
			}
			else {
				count++;
				if (count == j){
					line = j / 16;
					res = j % 16;
					if (col + 1 < res) {
						x = i - line - 1;
						y = 16 - res + col + 1;
					}
					else{
						x = i - line;
						y = col + 1 - res;
					}
					k = x * 16 + y + 1;
				}
			}
		}
	}
	if (count != j) {
		std::cout << "磁盘空间不足，文件" << FIN->file_name << "创建失败！" << "\n\n";
		return;
	}

	else {
		for (int i = k; i < k + j; i++) {
			m = i / 16;
			n = (i - (m - 1) * 16) % 16;
			a[m][n - 1] = 1; b[m][n - 1] = 1;
		}
		std::cout << "\n\n文件" << FIN->file_name << "创建成功， 物理地址如下： \n";
		printf("柱面号：%d, 盘面号：%d, 扇区号：%d \n", (k - 1) / 16, ((k - 1) % 16) / 4, ((k - 1) % 16) % 4);
		std::cout << "\n分配好的磁盘如下: \n";
		for (int i = 0; i < ROW; i++) {
			for (j = 0; j < COLUMN; j++) {
				std::cout << a[i][j];
			}
			std::cout << "\n";
		}
		FileDisk F = new fileDisk;
		F->name = FIN->file_name;
		F->start = k;
		F->blocks = FIN->disk;
		F->next = NULL;
		file_num++;
		if (FileDiskList == NULL)
			FileDiskList = F;
		else {
			FileDisk before = FileDiskList;
			FileDisk now = FileDiskList->next;
			while (now != NULL)
			{
				before = now;
				now = now->next;
			}
			before->next = F;
		}
	}
}

//回收所有
void file_system::callbackall(PCBC* pcbc){
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COLUMN; j++) {
			if (!b[i][j]) continue;
			else  a[i][j] = 0;
		}
	}
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COLUMN; j++) {
			std::cout << a[i][j];
		}
		std::cout << "\n";
	}
}

//回收特定文件
void file_system::callbackpointed(FileDisk D){	// 部分回收
	int i, k, q, m, j, p;
	FileDisk before = NULL;
	before = FileDiskList;
	k = D->start;
	j = D->blocks;
	//修改位示图
	for (int i = k; i < k + j; i++) {
		//q = c[i - 1][1];
		m = i / 16;
		p = (i - (m - 1) * 16) % 16;
		a[m][p - 1] = 0;
	}

	if (before == D) {
		std::cout << "\n\n文件" << D->name << "删除成功！\n";
	}
	else {
		while (before->next != D) {
			before = before->next; //找到文件D的上一个文件
		}
		before->next = D->next;
		std::cout << "\n\n文件" << D->name << "删除成功！";
	}
}

void file_system::allocateDisk(PCB* run){
	int p = 0;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			if (!a[i][j]) {
				p++;
			}

		}
	}
	disk = p;  
	std::cout << "空闲块的个数为：" << p << "\n";
	distribute(run);		
}

void file_system::showDisk(){
	std::cout << "\n************************************磁盘分布如下************************************:\n";
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			std::cout << a[i][j];
		}
		std::cout << "\n";
	}
}

void file_system::mergeMenory(MemoryNode& before, MemoryNode& p, MemoryNode& now){
	if (now != NULL && p->address + p->length == now->address) {
		p->length = p->length + now->length;
		p->next = now->next;
	}
	if (p->address != 0 && before->address + before->length == p->address) {
		before->length = before->length + p->length;
		before->next = p->next;
	}
}

void file_system::recoveryMenoryToFreeMemoryList(MemoryNode& p){
	MemoryNode before = freeMemoryList;
	MemoryNode now = freeMemoryList->next;
	while (now != NULL) {
		if (p->address < now->address) {
			before->next = p;
			p->next = now;
			mergeMenory(before, p, now);
			return;
		}
		before = now;
		now = now->next;
	}
	if (now == NULL) {
		before->next = p;
		p->next = NULL;
		mergeMenory(before, p, now);
		return;
	}
}

void file_system::recoveryMenory(PCB* run){
	std::string processName;
	processName = run->file_name;
	MemoryNode before = usedMemoryList;
	MemoryNode now = usedMemoryList->next;
	bool flag = false;
	while (now != NULL) {
		if (now->name == processName) {
			flag = true;
			std::cout << "成功回收进程" << run->PID << "的内存！" << "起始地址："
                 << now->address << " 结束地址：" << now->address + now->length << "\n";
			before->next = now->next;
			recoveryMenoryToFreeMemoryList(now);
			break;
		}
		before = now;
		now = now->next;
	}
}

void file_system::create_process(JCB* jcb, PCBC* pcbc){
	PCB* pcb;
	pcb = new PCB;
	std::cout << "\n************************************正在创建进程PCB************************************:\n";
	std::cout << "\n当前创建的文件名字为:" << jcb->file_name << "\n";
	std::cout << "\n随机生成进程的标识符PID:";
	std::stringstream ss;
	ss<< "P" << rand()%100;
	pcb->PID = ss.str();
	std::cout << pcb->PID << '\t';
	std::cout << "\n随机生成进程(优先级, 要求运行时间):";
	pcb->priority_num = rand()%10+1;
	pcb->process_time = rand()%10+1;
	std::cout << pcb->priority_num << '\t' << pcb->process_time;
	
	pcb->file_name = jcb->file_name;
	pcb->disk = jcb->disk;
	pcb->memory = jcb->memory;
	pcb->status = Cr;
	std::cout << "\n************************************进程创建成功************************************:\n";
	pcb->status = RE;
	
	if (pcbc->ready == NULL && pcbc->ready_tail == NULL) {
		pcbc->ready = pcbc->ready_tail = pcb;
		pcb->next = NULL;
	}
	else{
		pcb->next = pcbc->ready_tail->next;
		pcbc->ready_tail->next = pcb;
		pcbc->ready_tail = pcb;
	}
	pcbc->job = pcbc->job->next;
	std::cout << "、\n、\n、\n、\n、\n";
	std::cout << "************************************进程成功进入就绪队列************************************\n";
}

//交换
void file_system::swapx(PCB* p1, PCB* p2){
	int  i, priority_num, process_time, memory, space;
	pcb* ptr = NULL;
	std::string temp;

	temp = p1->PID;
	p1->PID = p2->PID;
	p2->PID = temp;
	
	priority_num = p1->priority_num;
	p1->priority_num = p2->priority_num;
	p2->priority_num = priority_num;
	
	process_time = p1->process_time;
	p1->process_time = p2->process_time;
	p2->process_time = process_time;

	memory = p1->memory;
	p1->memory = p2->memory;
	p2->memory = memory;

	space = p1->disk;
	p1->disk = p2->disk;
	p2->disk = space;

	
	temp = p1->file_name;
	p1->file_name = p2->file_name;
	p2->file_name = temp;
}

//将就绪队列按优先级别大小按冒泡排序算法进行排序
void file_system::sort_pcbc(PCBC* pcbc){
	PCB* p, * p1;
	p = pcbc->ready;
	for (p = pcbc->ready; p != NULL; p = p->next){
		for (p1 = p->next; p1 != NULL; p1 = p1->next){
			if (p->priority_num < p1->priority_num) {
				swapx(p, p1); 
			}
		}
	}
}

//打印当前进程控制块中的情况
void file_system::print_log(PCBC* pcbc){
	PCB* ready, * finish;
	ready = pcbc->ready;
	finish = pcbc->finish;
	std::cout << "\nRun:\n";

	if (pcbc->run != NULL){
		std::cout << "进程名字" << '\t' << "优先级" << '\t' << "要求运行时间" << '\t' << "进程状态\n";
		std::cout << pcbc->run->PID << '\t' << '\t' << pcbc->run->priority_num << '\t' << pcbc->run->process_time << '\t' << '\t' << pcbc->run->status << "\n";
	}

	else{
		std::cout << "无运行进程! \n";
	}
	std::cout << "\n";
	std::cout << "Wait:\n";
	std::cout << "进程名字" << '\t' << "优先级" << '\t' << "要求运行时间" << '\t' << "进程状态\n";

	while (ready != NULL){
		std::cout << ready->PID << '\t' << '\t' << ready->priority_num << '\t' << ready->process_time << '\t' << '\t' << ready->status << "\n";
		ready = ready->next;
	}

	std::cout << "\n";
	std::cout << "Finish: \n";
	std::cout << "进程名字" << '\t' << "优先级" << '\t' << "要求运行时间" << '\t' << "进程状态\n";
	
	while (finish != NULL){
		std::cout << finish->PID << '\t' << '\t' << finish->priority_num << '\t' << finish->process_time << '\t' << '\t' << finish->status << "\n";
		finish = finish->next;
	}
	std::cout << "\n************************************************************************\n";
}

//优先级调度算法
void file_system::run_pcbc_priority(PCBC* pcbc){
	PCB* temp = NULL;
	PCB* pre = NULL;
	PCB* tail = NULL;
	while (pcbc->ready != NULL) {
		pcbc->run = pcbc->ready;
		pcbc->run->status = R;
		pcbc->ready = pcbc->ready->next; 
		print_log(pcbc);
		pcbc->run->priority_num -= 1;
		pcbc->run->process_time -= 1;
		//进程完成后
		if (pcbc->run->process_time == 0) {
			allocateDisk(pcbc->run);
			recoveryMenory(pcbc->run);
			pcbc->run->status = E;
			if (pcbc->finish == NULL) {
				pcbc->finish = pcbc->run;
				pcbc->finish->next = NULL;
				tail = pcbc->finish;
			}
			
			else {
				tail->next = pcbc->run;
				tail = tail->next;
				tail->next = NULL;
			}
			} 
		//进程没完成
		else {
			if (pcbc->ready != NULL) {
				pcbc->run->status = RE;
				temp = pcbc->ready;
				while (temp != NULL) {
					if (pcbc->run->priority_num > temp->priority_num)
						break;
					pre = temp;
					temp = temp->next;
				}
				//就绪队列的头的优先级就没有正在运行
				if (temp == pcbc->ready) {
					pcbc->run->next = pcbc->ready;  //把正在运行的进程插到队列头部
					pcbc->ready = pcbc->run;        //插队
				}
				else {
					pcbc->run->next = pre->next;
					pre->next = pcbc->run;
				}
			}
			else
				pcbc->ready = pcbc->run;
			
		}
	}
	pcbc->ready = pcbc->ready_tail = NULL;
	pcbc->run = NULL;
	print_log(pcbc);
}

void file_system::create_job(int i, PCBC* pcbc){
	JCB* jcb = new JCB;
	JCB* check = pcbc->job;

	std::cout << "\n请输入第" << i+1 <<"个作业的文件名：";
	std::cin >> jcb->file_name;
	//检查是否重名
t:	while (check != NULL) { 
		if (jcb->file_name == check->file_name ) {
			std::cout << "存在文件重名，请重新输入！\n";
			std::cout << "\n请输入第" << i + 1 << "个作业的文件名：";
			std::cin >> jcb->file_name;
			check = pcbc->job;  //从头开始
		}
		else {
			check = check->next;
		}
		
	}
	FileDisk F = FileDiskList;//已有文件名是否重命名
	while (F != NULL) {
		if (jcb->file_name == F->name ) {
			std::cout << "存在文件重名，请重新输入！\n";
			std::cout << "\n请输入第" << i + 1 << "个作业的文件名：";
			std::cin >> jcb->file_name;
			goto t;  //从头开始
		}
		else {
			F = F->next;
		}
		
	}

	jcb->memory = rand()%(MAX_Memory/4)+1;
	std::cout << "\n第" << i+1 << "个作业所需要占用的内存大小：" << jcb->memory ;

	while (jcb->memory > x) {    //虚拟存储 
		std::cout << "输入不合法，请重新输入！\n";
		std::cout <<"\n请输入第" << i + 1 << "个作业所需要占用的内存大小：";
		std::cin >> jcb->memory;
		std::cin.clear();//防止输入字符死循环 
		std::cin.ignore();
	}
	jcb->disk = rand()%(ROW*COLUMN/10)+1;
	std::cout << "\n第" << i+1 << "个数据文件需要占用的磁盘大小：" << jcb->disk ;
	std::cout << "\n";
	while (jcb->memory > x || jcb->memory <= 0){
		std::cout << "输入不合法， 请重新输入！\n";
		jcb->memory = 0;
		std::cin >> jcb->memory;
		std::cin.clear();//防止输入字符死循环 
		std::cin.ignore();
	}

	//当作业队列为空时
	if (pcbc->job == NULL && pcbc->job_tail == NULL) {
		pcbc->job = pcbc->job_tail = jcb;
		jcb->next = NULL;
	}
	else {
		jcb->next = NULL;
		pcbc->job_tail->next = jcb;
		pcbc->job_tail = jcb;
	}
}

void file_system::deleteMemoryNode(MemoryNode& p, MemoryNode& q){
	p->next = q->next;//尾部开始删
	delete(q);
}

void file_system::insertMemoryNode(MemoryNode& p){
	MemoryNode before = usedMemoryList;
	MemoryNode now = usedMemoryList->next;
	while (now != NULL) {
		before = now;
		now = now->next;
	}
	before->next = p;
	p->next = now; //尾插内存
}

bool file_system::firstFit(MemoryNode& p, PCBC* pcbc){
	MemoryNode before = freeMemoryList;
	MemoryNode now = freeMemoryList->next;
	bool flag = false;
	while (now != NULL) {
		if (now->length >= p->length) {
			flag = true;  //能分配
			now->length = now->length - p->length;
			p->address = now->address;
			now->address = now->address + p->length;
			if (now->length == 0) {
				deleteMemoryNode(before, now);
			}
			insertMemoryNode(p);
			break;
		}
		before = now;
		now = now->next;
	}
	if (flag) {
		std::cout << "文件" << p->name << "成功进入内存！起始地址为：" << p->address << 
            "  结束地址：" << p->address + p->length << "\n";
		//给一个作业分配内存后，JCB转化为相应的PCB，并且该进程直接进入就绪态
		create_process(pcbc->job, pcbc);  
	}
	else {
		std::cout << "内存不足！文件（" << p->name << "）需要等待\n";
	}
	return flag;
}

void file_system::allocateMemory(PCBC* pcbc){
	//这个flag为true说明内存足够于分配给进程，假如不够，flag为false，进程要等到内存足够时，也就是等待释放后再来
	bool flag = true;
	y=0;
	while (flag && pcbc->job != NULL) {
		MemoryNode p = new(memoryNode);
		p->next = NULL;
		p->name = pcbc->job->file_name;  //名字(出问题)
		p->length = pcbc->job->memory; //内存大小
		flag = firstFit(p, pcbc);
		if(flag==true)y++;
	}
}

//安全测试函数int y
bool file_system::Safe(int y,int Available[], int Need[][1], int Allocation[][1]){	
	std::vector<int> v;
	std::vector<int>::iterator iter;
	v.clear();
	int a;
	a=y; //传个参数 
	bool Finish[a];
	for(int i=0;i<a;i++)
	{	Finish[i]=false;
	}
	int count = 0, k = 0;
	for (int i = 0; i < 1; i++) //赋值，保护现场
	{
		Work[i] = Available[i];
	}

	for (int i = 0; i < a; i++)
	{		
		count = 0;
		for (int j = 0; j < 1; j++)
		{
			if (Finish[i] == false && Need[i][j] <= Work[j])
				count++;
		}
		if (count == 1)//当进程i 各类资源都满足NEED<=WORK时
		{
			for (int m = 0; m < 1; m++)
				Work[m] += Allocation[i][m]; //新的available
			Finish[i] = true;
			temp[k] = i;//记录进程号
			k++;
			if (k == a && v.empty()) //所有进程都能运行
			{
				return true;
			}
		}
		else
		{
			v.push_back(i); //阻塞当前进程
			continue;
		}
	}
	iter = v.end() - 1;
	//遍历阻塞的进程
	while (!v.empty())
	{
		int i = *iter;
		count = 0;
		for (int j = 0; j < 1; j++)
		{
			if (Finish[i] == false && Need[i][j] <= Work[j])
				count++;
		}
		if (count == 1)
		{
			v.pop_back(); //从阻塞队列中移除
			for (int m = 0; m < 1; m++)
				Work[m] += Allocation[i][m]; //新的available
			Finish[i] = true;
			temp[k] = i;//记录进程号
			k++;
			if (k == a && v.empty()) //所有进程都能运行
			{
				return true;
			}
			iter = v.end() - 1; //更新迭代器，保证每个阻塞的进程都能得到遍历
		}
		else 
		{
			if (iter == v.begin()) //余下阻塞进程都不满足
			{
				return false;
			}
			else
				iter--;
		}
	}
	std::cout << "\n\n";
	return true;	
}

void file_system::allocateResource(int y){
b1:	
	int Resource[1] = {15}; //资源总量
	std::cout << "系统拥有资源为："<<Resource[0] << "\n";
	std::cout << "************************************资源分配************************************\n";
	int Max[y][1];//各进程所需资源总量
	for(int i=0;i<y;i++) {
	Max[i][0] = rand()%(Resource[0]*2/3);
	std::cout<<"队列中第"<<i+1<<"个进程所需最大需求资源：" << Max[i][0] << '\n';
	while(Max[i][0]>Resource[0]){
	    std::cout<<"ERROR,作业需求超过了资源总量,请重新输入" ; 
	    std::cin>>Max[i][0];
	    std::cin.clear();//防止输入字符死循环 
	    std::cin.ignore();
	    }
	}
	int sub=0;
	int Allocation[y][1]; 
	for(int i=0;i<y;i++) {
		Allocation[i][0] = rand()%(Resource[0]/2);
		if(Allocation[i][0]>Max[i][0]){
			(Allocation[i][0] = Max[i][0]);//按最大资源分配 
		}
		std::cout << "分配给队列中第"<<i+1<<"个进程的资源：" << Allocation[i][0] << '\n';
		sub+=Allocation[i][0];
	}
//各进程还需要的资源
	int Need[y][1];
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}
	}
	//可用资源
	int Available[1];
	Available[0] =Resource[0]-sub;//申请的资源
	if (Safe(y,Available,Need,Allocation)==true) //测试安全算法
	{
		std::cout << "经安全性检查，系统安全，本次分配成功。\n\n";
		std::cout << "本次安全序列：\n";
		for (int i = 0; i < y; i++)//打印安全系统的进程调用顺序
		{
			std::cout<<"进程" << temp[i]+1;
		}
        std::cout << "\n";
		char anykey; 
		std::cout << "继续操作\n";
		anykey = getchar();
		anykey = getchar();
		}
		else{
		std::cout << "资源分配不当!系统处于不安全状态，需要重新分配资源！\n";//中断进程
		goto b1;
	}
}

void file_system::select1(){
	PCBC* pcbc = new PCBC; //创建进程控制块链
	int input_num = 0;
	init_pcbc(pcbc);
	std::cout << "\n************************************执行作业************************************\n\n";
	std::cout << "\n\n请输入要执行的作业数目:";
	std::cin >> input_num;
	for (int i = 0; i < input_num; i++) {
		create_job(i, pcbc);
	}
	//开始作业调度
	while (pcbc->job != NULL) {
		std::cout << "\n************************************分配内存************************************\n\n";
		allocateMemory(pcbc);
		allocateResource(y);
		std::cout << "\n\n**********************************运行优先级调度算法*********************************\n";
		
		//根据就绪队列优先级进行排序
		sort_pcbc(pcbc);
		run_pcbc_priority(pcbc);
		std::cout << "************************************调度完成************************************\n";
		pcbc->finish = NULL;
	}
	init_pcbc(pcbc);
}

void file_system::select2(){
	int delete_num; //删除uoye数目
	std::cout << "************************************删除文件************************************\n";

	std::cout << "\n请输入要删除的文件数目：       输入0则返回目录!";
	std::cin >> delete_num;
	while (!(delete_num <= file_num && delete_num > 0))
	{
		if (delete_num == 0)
			return;
		std::cout << "\n输入错误, 请重新输入要删除的文件数目:\n";
		std::cin >> delete_num;
		std::cin.clear();//防止输入字符死循环 
		std::cin.ignore(); 
	}

	FileDisk D = FileDiskList; //找目录
	std::cout << "作业名" << '\t' << '\t' << "始址" << '\t' << "块数\n";
	while (D != NULL){
		std::cout << D->name << '\t' << '\t' << D->start - 1 << '\t' << D->blocks << '\t' << "\n";
		D = D->next;
	}
	std::string fileName = "";
	
	while (delete_num != 0)
	{
		D = FileDiskList;
		std::cout << "\n请输入需要删除的作业名:";
		std::cin >> fileName;
		while (D != NULL) {
			if (D->name == fileName) {
				std::cout << "已找到作业" << D->name << "\n";
				break;
			}
			D = D->next;
		}
		if (D == NULL) {
			std::cout << "输入的文件名不存在\n";
			std::cout << "请确认后再输入\n";
			continue;
		}
		std::cout << "\n************************************释放磁盘************************************\n";
		callbackpointed(D);

		std::cout << "\n\n";

		delete_num--;
	}
	if (file_num == 0) {
		std::cout << "目录已空\n";
	}
}

void file_system::select3(){
	FileDisk F = FileDiskList;
	showDisk();
	std::cout << "\n\n";
	if (file_num == 0) {
		std::cout << "作业目录已空！\n";
		std::cout << "请先添加文件！\n";
		return;
	}
	std::cout << "文件名" << '\t' << '\t' << "始址" << '\t' << "块数\n";
	while (F != NULL){
		std::cout << F->name << '\t' << '\t' << F->start - 1 << '\t' << F->blocks << '\t' << "\n";
		F = F->next;
	}
}

void file_system::menu(){
	char anykey;
	int select;
	while(1){
		std::cout << "目前总内存为：" << x << "\n";
		std::cout <<"目前磁盘分布为\n";
    	for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COLUMN; j++) {
				std::cout << a[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "\n*****************************\n";
		std::cout << "*    1、执行作业            *\n";
		std::cout << "*    2、删除数据作业        *\n";
		std::cout << "*    3、查看已有数据文件    *\n";
		std::cout << "*    (其他输入)退出系统     *\n";
		std::cout << "*****************************\n";
		std::cout <<"请选择:";
		std::cin >> select;
		std::cout << "\n";
		if(select == 1) select1();
		else if(select == 2) select2();
		else if(select == 3) select3();
		else{
			std::cout << "结束";
			break;
		}
	}
}