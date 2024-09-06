#include<iostream>
#include "Window.h"

/////////////////////////////
//编译环境  visual studio 2022
//外部库easyx
//最后修改时间 2023年6月5日
//作者 李迪

int main()
{
	initgraph(1400, 800,EX_DBLCLKS);

	HELLO hello(1400, 800);
	hello.HELLO_Show();
	cleardevice();

	setfont(20, 0, _T("Arial"));
	Windows window;
	window.message();

	Sleep(3000);
	closegraph();
	return 0;
}