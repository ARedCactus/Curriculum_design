#include"HELLO.h"

HELLO::HELLO(int i, int j)
{
	this->Win_Width = i;
	this->Win_Height = j;
	this->count = 0;
	this->s_height = 0;
	this->s_width = 0;
	this->Point_Pre = nullptr;
	this->Point_Random = nullptr;
}

HELLO::~HELLO()
{
	delete[] Point_Pre;
	delete[] Point_Random;
}

void HELLO::GetPoint_Pre()
{
	//初始化
	IMAGE img;
	SetWorkingImage(&img);
	TCHAR s[] = _T("H E L L O");
	setcolor(WHITE);
	setfont(180, 0, _T("Arial"));
	s_width = textwidth(s);
	s_height = textheight(s);

	//绘制原始图
	Resize(&img, s_width, s_height);
	outtextxy(0, 0, s);

	//计算原始图s的像素点数
	int x, y;
	count = 0;
	for (x = 0; x < s_width; x++)
	{
		for (y = 0; y < s_height; y++)
		{
			if (getpixel(x, y) == WHITE)
			{
				count++;
			}
		}
	}
	Point_Pre = new POINT[count+2];

	//映射目标点的坐标
	int k = 0;
	LONG X_move = (LONG)((Win_Width - s_width) / 2);
	LONG Y_move = (LONG)((Win_Height - s_height) / 2);
	for (x = 0; x < s_width; x++)
	{
		for (y = 0; y < s_height; y++)
		{
			if (getpixel(x, y) == WHITE)
			{
				Point_Pre[k].x = x + X_move;
				Point_Pre[k].y = y + Y_move;
				k++;
			}
		}
	}
	SetWorkingImage(nullptr);
}

void HELLO::GetPoint_Random()
{
	srand((unsigned int)time(NULL));
	Point_Random = new POINT[count];
	int k;
	for (k = 0; k < count; k++)
	{
		Point_Random[k].x = rand() % Win_Width;
		Point_Random[k].y = rand() % Win_Height;
	}

}

void HELLO::Fuzzy(DWORD* p)
{
	int k;
	int K = Win_Width * (Win_Height - 1);
	for (k = Win_Width; k < K; k++)
	{
		p[k] = RGB(
			(GetRValue(p[k - Win_Width]) + GetRValue(p[k + Win_Width]) + GetRValue(p[k - 1]) + GetRValue(p[k + 1])) / 5,
			(GetGValue(p[k - Win_Width]) + GetGValue(p[k + Win_Width]) + GetGValue(p[k - 1]) + GetGValue(p[k + 1])) / 5,
			(GetBValue(p[k - Win_Width]) + GetBValue(p[k + Win_Width]) + GetBValue(p[k - 1]) + GetBValue(p[k + 1])) / 5);
	}
}

void HELLO::HELLO_Show()
{
	DWORD* p = GetImageBuffer();
	GetPoint_Pre();
	GetPoint_Random();
	int x, y, k, k1;
	COLORREF color;
	for (k = 2; k <= 256; k += 2)
	{
		color = RGB(k-1, 0, k-1);
		Fuzzy(p);
		for (k1 = 0; k1 < count; k1++)
		{
			x = Point_Random[k1].x + (Point_Pre[k1].x - Point_Random[k1].x) * k / 256;
			y = Point_Random[k1].y + (Point_Pre[k1].y - Point_Random[k1].y) * k / 256;
			p[y * Win_Width + x] = color;
		}
		Sleep(18);
	}
	cleardevice();
	for (k1 = 0; k1 < count; k1++)
	{
		x = Point_Pre[k1].x;
		y = Point_Pre[k1].y;
		p[y * Win_Width + x] = RGB(255, 0, 255);
	}

	p = nullptr;
	Sleep(1800);
}