#include<iostream>
#include "Window.h"

/////////////////////////////
//���뻷��  visual studio 2022
//�ⲿ��easyx
//����޸�ʱ�� 2023��6��5��
//���� ���

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