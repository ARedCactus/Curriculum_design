#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <string>

#define RE 'W'		//就绪 
#define Cr 'c'		//创建 
#define R 'R'		//执行 
#define E 'F'   	//完成 

#define MAX_Memory 256		//内存大小 
#define Block 4				//页框/内存块
#define ROW 10				//磁盘大小
#define COLUMN 16

//作业控制块
typedef struct jcb {
	std::string file_name;			//文件名
	int memory;                 //所占内存大小
	int disk;                   //所占磁盘大小
	struct jcb* next;			//连接下一作业的指针
} JCB;

//进程控制块
typedef struct pcb {
	std::string PID;				//进程标识符
	int priority_num;       //优先级大的先进行
	int process_time;       //进程所需时间片数
	char status;            //进程当前的状态
	struct pcb* next;       //连接下一个进程的指针
	std::string file_name;		//作业对应的文件名
	int memory;             //所占内存大小
	int disk;               //所占磁盘大小
} PCB;

//内存块定义
typedef struct memoryNode {
	std::string name;
	int address;
	int length;
	memoryNode* next;
}*MemoryNode;

//磁盘块定义
typedef struct fileDisk {
	std::string name;
	int start; //始址
	int blocks; //扇区块数
	fileDisk* next;
}*FileDisk;

//指针库
typedef struct {
	JCB* job;			//作业队列
	JCB* job_tail;		//作业队列尾指针
	PCB* run;           //当前运行的进程指针
	PCB* ready;         //当前就绪队列的头指针
	PCB* ready_tail;    //就绪队列的尾指针
	PCB* finish;        //完成队列的头指针
} PCBC;

#endif