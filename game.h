#pragma once
#ifndef game
#include <graphics.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>                           
#include <conio.h>
#include <iostream>
#include <easyx.h>
#include <time.h>
#include <stdio.h>
#include<fstream>
#include<process.h>
#include<iostream>

using namespace std;

const int WIDTH = 1200;
const int P_WIDTH = WIDTH + 420;
const int HEIGHT = 800;
const int MapNum = 3;

extern int Arr[MapNum][WIDTH / 20][HEIGHT / 20];

class System
{
private:
	const int WIDTH = 1080;
	const int P_WIDTH = WIDTH + 420;
	const int HEIGHT = 720;

	DWORD t1, t2;

public:
	unsigned int a, b;
	System();
	void outtext(int );
	void Init();
	void Servation();
	void Reflush();
	void Loop();
	void bulidGrid();
	void Demo();
};

struct Node
{
	int x;
	int y;
	Node* pre;
};

int const MaxLength = 1000;

class Queue
{
private:
	Node* data;
	int front;
	int rear;
public:
	Queue();
	~Queue();
	void Pop();
	void Push(Node node);
	Node visit(int i);
	inline int GetFront();
	inline int GetRear();
	void PrintRoute();
	void ReSetPre();
};



class Class
{
private:
	COLORREF COLOR1 = NULL;
	COLORREF COLOR2 = NULL;
	COLORREF COLOR3 = NULL;
	const int BLOCK_XY = 20;
	int MaxNum = 0;
	struct Node
	{
		int x;
		int y;
		bool s = true;
		int Num[20] = { 0 };
	}node[100];
public:
	void SetColor();
	void Init();
	void Draw();
	void SetNum();
	void Print();
	void Move();
};

#endif 
