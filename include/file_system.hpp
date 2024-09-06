#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include "element.hpp"
#include<cstring>
#include<vector>
#include<iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

class file_system{
public:
    file_system();
    ~file_system();

    void init_pcbc(PCBC* p);  //初始化PCBC链
    void distribute(PCB* run); //分配磁盘空间
    void callbackall(PCBC* pcbc);  //回收所有
    void callbackpointed(FileDisk D);  //回收特定文件
    void allocateDisk(PCB* run);
    void showDisk();

    //进程功能部分
    MemoryNode create(MemoryNode& p, int address = 0, int length = 0, std::string name = "");
    void mergeMenory(MemoryNode& before, MemoryNode& p, MemoryNode& now);  //三个关于释放空间的
    void recoveryMenoryToFreeMemoryList(MemoryNode& p);
    void recoveryMenory(PCB* run);
    void create_process(JCB* jcb, PCBC* pcbc);   //为进入内存的作业建立相应进程
    void swapx(PCB* p1, PCB* p2);     //交换
    void sort_pcbc(PCBC* pcbc);  //将就绪队列按优先级别大小按冒泡排序算法进行排序
    void print_log(PCBC* pcbc);  //打印当前进程控制块中的情况
    void run_pcbc_priority(PCBC* pcbc);  //优先级调度算法
    void create_job(int i, PCBC* pcbc);

    // 内存功能部分 
    void deleteMemoryNode(MemoryNode& p, MemoryNode& q);   //删除内存
    void insertMemoryNode(MemoryNode& p);   //添加内存
    bool firstFit(MemoryNode& p, PCBC* pcbc);   //首次适应算法
    void allocateMemory(PCBC* pcbc);    //分配内存
    bool Safe(int y,int Available[], int Need[][1], int Allocation[][1]);  //安全测试函数int y
    void allocateResource(int y);  //资源分配

    void select1();   //目录和功能选项定义
    void select2();  
    void select3();

    void menu();

private:
    MemoryNode freeMemoryList, usedMemoryList;     //内存的空闲部分和使用部分
    FileDisk FileDiskList = NULL;  //磁盘块创建
    int x{0}, y{0};  //自定义总内存大小
    int disk{0}; //自定义总磁盘大小 
    int file_num{0}; //记录创建的文件个数
    int *temp, *Work;
    int **a, **b;   //自定义的磁盘状况
};

#endif