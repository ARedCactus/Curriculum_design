#pragma once
#include "include/graphics.h"
#include <conio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>

class HELLO
{
	int Win_Width;
	int Win_Height;
    POINT* Point_Pre;
	POINT* Point_Random;
	int s_width;
	int s_height;
	int count;
public:
	HELLO(int i, int j);
	~HELLO();
	void GetPoint_Pre();
	void GetPoint_Random();
	void Fuzzy(DWORD* p);
	void HELLO_Show();
};
