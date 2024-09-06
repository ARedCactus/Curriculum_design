#include <graphics.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>                           //VS2022      easyx     随机地图  +游戏人物移动  +存档
#include <conio.h>
#include <iostream>
#include <easyx.h>
#include <time.h>
#include <stdio.h>
#include<fstream>
#include<process.h>

using namespace std;

void heroreact(int x, int y, int z, int s);
void keyshape(int x, int y, COLORREF COLOR, float xy, int s);
void draw(int pos, RECT rct, DWORD* pBufImg, DWORD* pBuf);
void maptest(int x);
void read();
void  drawroundrect(int x, int y, int L1, int L2, int p, int e, COLORREF COLOR1, COLORREF COLOR2);
void drawjpz(int x, int y, int L, int p, int i);
void drawpixal(int x, int y, COLORREF COLOR, float xy, int s);
void drawcircle(int x, int y, COLORREF COLOR, float xy, int s);
void drawpie(int x, int y, COLORREF COLOR, float xy, int s);
void buildstair(int x, int y, COLORREF COLOR, int p);
void doortest();
void drawarr(int i, int j);
void k(int x, int y, int m, int n);
void kx(int x, int y, int m, int n);
#define PI acos(-1)
#define WIDTH 1080
#define HEIGHT 720

#define BLOCK_XY 15	//小方格边长
#define BLOCK_JJ 1		//小方格之间的间距

COLORREF TEXT_COLOR = COLORREF RGB(110, 110, 180);			    // 门颜色2
COLORREF HERO_COLOR = COLORREF RGB(100, 150, 150);		     //hero颜色
COLORREF BIG_COLOR = COLORREF RGB(255, 0, 0);		         //Big颜色
COLORREF BIGX_COLOR = COLORREF RGB(255, 0, 0);		         //Bigx颜色
COLORREF SMALL_COLOR = COLORREF RGB(100, 120, 120);          //small颜色
COLORREF SMALLX_COLOR = COLORREF RGB(164, 114, 229);          //smallx颜色
COLORREF BK_COLOR = COLORREF RGB(150, 150, 150);			 //围墙颜色1
COLORREF BK_COLOR2 = COLORREF RGB(80, 80, 80);			    //围墙颜色2
COLORREF BK_COLOR3 = COLORREF RGB(38, 89, 229);			    // 围墙颜色3 
COLORREF BK_COLOR4 = COLORREF RGB(85, 226, 229);			    //围墙颜色4
COLORREF BK_COLOR5 = COLORREF RGB(132, 138, 79);			    //围墙颜色5
COLORREF BK_COLOR6 = COLORREF RGB(128, 85, 138);			    //围墙颜色6
COLORREF DOOR_COLOR1 = COLORREF RGB(120, 120, 250);			    // 门颜色1 
COLORREF DOOR_COLOR2 = COLORREF RGB(120, 250, 120);			    // 门颜色2
COLORREF DOOR_COLOR3 = COLORREF RGB(150, 120, 120);            //门的颜色3
COLORREF WEN_COLOR = COLORREF RGB(0, 200, 0);			     // 进度条颜色
COLORREF BLOOD_COLOR = COLORREF RGB(200, 250, 200);           //blood的颜色
COLORREF BLOODX_COLOR = COLORREF RGB(200, 250, 200);           //bloodx的颜色
COLORREF KEY_COLOR = COLORREF RGB(100, 100, 200);             //key的颜色
COLORREF STAIR_COLOR = COLORREF RGB(100, 200, 200);           //梯子颜色1
COLORREF STAIR_COLOR2 = COLORREF RGB(203, 217, 229);           //梯子颜色2
COLORREF jp_COLOR1 = COLORREF RGB(92, 92, 92);           //键盘颜色1
COLORREF jp_COLOR2 = COLORREF RGB(66, 66, 66);           //键盘颜色2


#define GAMETIME 150			//游戏速度
#define LIZINUM 200	             //粒子数量
#define DOORLIZINUM 20           //门打开时粒子化的粒子数量
#define BIGNUM 20               //突袭怪物数量
#define BIGNUMX 20               //突袭怪物x数量
#define SMALLNUM 22               //普通怪物数量
#define SMALLNUMX 30               //普通怪物x数量
#define BLOODNUM 10              //回血点数量
#define BLOODNUMX 10              //回血点x数量
#define KEYNUM 10                //钥匙数量
#define STARNUM 500              //星数量
int CAMERA_X = 0;				//相机x坐标,0为屏幕中间
int CAMERA_Y = 0;				//相机y坐标,0为屏幕中间
#define SHAKE 30				//抖动效果的帧数
int WINDOW_SHAKE = 0;			//记录抖动了多少次

const int P_WIDTH = WIDTH + 417;     //屏幕宽度 width
const int P_HEIGHT = HEIGHT;     //屏幕高度 height
const int WEN_DISTANT = 40;       //信息界面上下文字间距离
const int WEN_LR = 150;       //信息界面左右文字间距离
const int WEN_P = 2;           //信息界面进度条边框宽度
const int BLOCK_WIDTH = WIDTH / (BLOCK_XY + BLOCK_JJ);	 //小方格x轴数量
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY + BLOCK_JJ); //小方格y轴数量

const int PYI_X = WIDTH - BLOCK_WIDTH * (BLOCK_XY + BLOCK_JJ);  //x轴上的偏移量，因为分辨率和方格经常不能整除
const int PYI_Y = HEIGHT - BLOCK_HEIGHT * (BLOCK_XY + BLOCK_JJ);//y轴上的偏移量，因为分辨率和方格经常不能整除
const int py_x = PYI_X / 2;
const int py_y = PYI_Y / 2;

const float G = 0;			        //重力
const float MC = 0.9999f;		    //摩擦力
float jd = 0;
const int dooropening = 100;         //门开启速度   dooropening/100  秒

// 窗口宽高
int px = 1497;
int py = 720;

int font_h = 200;					// 文字高
int font_w = 20;					// 文字宽

int K[WIDTH][HEIGHT] = { 0 };               //标记物体坐标的二维数组     0代表空   1代表墙    2代表门   3代表small   4代表回血点  5代表key  6代表楼梯
int K1[WIDTH][HEIGHT] = { 0 };               //标记物体坐标的二维数组     0代表空   1代表墙    2代表门   3代表small   4代表回血点  5代表key  6代表楼梯
int K2[WIDTH][HEIGHT] = { 0 };                //此时x=3  

wchar_t pszText[] =
L"You are dead！！！\n"
L"《春江花月夜》\n"
L"春江潮水连海平，海上明月共潮生。\n"
L"滟滟随波千万里，何处春江无月明。\n"
L"江流宛转绕芳甸，月照花林皆似霰。\n"
L"空里流霜不觉飞，汀上白沙看不见。\n"
L"江天一色无纤尘，皎皎空中孤月轮。\n"
L"江畔何人初见月？江月何年初照人？\n"
L"人生代代无穷已，江月年年只相似。\n"
L"不知江月待何人，但见长江送流水。\n"
L"白云一片去悠悠，青枫浦上不胜愁。\n"
L"谁家今夜扁舟子，何处相思明月楼？\n"
L"可怜楼上月徘徊，应照离人妆镜台。\n"
L"玉户帘中卷不去，捣衣砧上拂还来。\n"
L"此时相望不相闻，愿逐月华流照君。\n"
L"鸿雁长飞光不度，鱼龙潜跃水成文。\n"
L"昨夜闲潭梦落花，可怜春半不还家。\n"
L"江水流春去欲尽，江潭落月复西斜。\n"
L"斜月沉沉藏海雾，碣石潇湘无限路。\n"
L"不知乘月几人归，落月摇情满江树。\n"
L"game made by 李迪\n";

struct Big {                             //big的结构体
	int x = 0, y = 0;                              //big出现的二维坐标
	int dx = -1, dy = 0;                      //big移动的默认xy方向
	int s = 1;                             //big的存在状态     1代表活着  2代表死亡
}BIG[BIGNUM];

struct Bigx {                             //big的结构体
	int x = 0, y = 0;                              //big出现的二维坐标
	int dx = -1, dy = 0;                      //big移动的默认xy方向
	int s = 1;                             //big的存在状态     1代表活着  2代表死亡
}BIGX[BIGNUMX];

void bigtest() {
	ofstream ofs;
	ofs.open("test.txt", ios::app);
	if (ofs.is_open()) {
		for (int i = 0; i < BIGNUM; i++)
			switch (0) {
			case 0:	ofs << BIG[i].x << " "; 
			case 1:	ofs << BIG[i].y << " "; 
			case 2: ofs << BIG[i].dx << " ";
			case 3:	ofs << BIG[i].dy << " "; 
			case 4: ofs << BIG[i].s << " "; 
			}
		for (int i = 0; i < BIGNUMX; i++)
			switch (0) {
			case 0:	ofs << BIGX[i].x << " "; 
			case 1:	ofs << BIGX[i].y << " "; 
			case 2: ofs << BIGX[i].dx << " "; 
			case 3:	ofs << BIGX[i].dy << " "; 
			case 4: ofs << BIGX[i].s << " "; 
			}
	}
}

struct Small {
	int x = 0;
	int y = 0;
	int s = 1;
}SMALL[SMALLNUM];

struct Smallx {
	int x = 0;
	int y = 0;
	int s = 1;
}SMALLX[SMALLNUMX];

void smalltest() {
	ofstream ofs;
	ofs.open("test.txt", ios::app);
	if (ofs.is_open()) {
			for (int i = 0; i < SMALLNUM; i++)
				switch (0) {
				case 0:ofs << SMALL[i].x << " ";
				case 1:ofs << SMALL[i].y << " ";
				case 2:ofs << SMALL[i].s << " ";
				}
				for (int i = 0; i < SMALLNUMX; i++)
					switch (0) {
					case 0:ofs << SMALLX[i].x << " ";
					case 1:ofs << SMALLX[i].y << " ";
					case 2:ofs << SMALLX[i].s << " ";
					}
	}
}

struct blood {
	int x = 0;
	int y = 0;
	int s = 1;
}BLOOD[BLOODNUM];

struct bloodx {
	int x = 0;
	int y = 0;
	int s = 1;
}BLOODX[BLOODNUMX];

void bloodtest(int x) {
	ofstream ofs;
	ofs.open("test.txt", ios::app);
	if (ofs.is_open()) {
		if (x == 0) {
			for (int i = 0; i < BLOODNUM; i++)
				switch (0) {
				case 0:ofs << BLOOD[i].x << " ";
				case 1:ofs << BLOOD[i].y << " ";
				case 2:ofs << BLOOD[i].s << " ";
				}
		}
		else if (x == 1) {
			for (int i = 0; i < BLOODNUMX; i++)
				switch (0) {
				case 0:ofs << BLOODX[i].x << " ";
				case 1:ofs << BLOODX[i].y << " ";
				case 2:ofs << BLOODX[i].s << " ";
				}
		}
	}
}

struct key {
	int x = 0;
	int y = 0;
	int s = 1;
}KEY[KEYNUM];

void keytest(int x) {
	ofstream ofs;
	ofs.open("test.txt", ios::app);
	if (ofs.is_open()) {
		if (x == 0) {
			for (int i = 0; i < KEYNUM; i++)
				switch (0) {
				case 0:ofs << KEY[i].x << " ";
				case 1:ofs << KEY[i].y << " ";
				case 2:ofs << KEY[i].s << " ";
				}
		}
	}
}

struct hero {
	int x = 3, y = 3;
	int dx = 1, dy = 0;
	int level = 1;
	int EXP = 0;
	int HP = 100;
	int key = 1;
	int s = 1;
	int map = 0;
	int power = 0;
	int skill = 0;
	int TOPHP=100;
	int i = 0;
	int j = 0;
	int ss = 1;
}HERO;

void heroskill() {
	if (HERO.skill > 0) {
		if (HERO.i == 0 && HERO.j == 0)  HERO.HP += HERO.TOPHP/2;
		else if (HERO.i == 0 && HERO.j == 1){
			if (HERO.dy == 0 && HERO.dx == -1) {
				int x = HERO.x;
				while (x > 0) {
					x += HERO.dx;
					if (K[x][HERO.y] == 1) k(x, HERO.y, 0, 1);
				}

			}
		}
		else if (HERO.i == 1 && HERO.j == 0) {

		}
		else if (HERO.i == 1 && HERO.j == 1){
		}
		HERO.skill--;
	}
}

void herotest() {
	ofstream ofs;
	ofs.open("test.txt", ios::app);
	if (ofs.is_open()) {
		switch (0) {
		case 0:	ofs << HERO.x << " ";
		case 1:	ofs << HERO.y << " ";
		case 2:	ofs << HERO.dx << " ";
		case 3:	ofs << HERO.dy << " ";
		case 4:	ofs << HERO.level << " ";
		case 5:	ofs << HERO.EXP << " ";
		case 6:	ofs << HERO.HP << " ";
		case 7:	ofs << HERO.key << " ";
		case 8:	ofs << HERO.s << " "; 
		case 9:	ofs << HERO.map << " ";
		}
	}
}


int Xtox(int x) {                                                                  //x大坐标转小坐标
	return(x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X + BLOCK_XY / 2);
}
int Ytoy(int y) {                                                                  //y大坐标转小坐标
	return(y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y + BLOCK_XY / 2);
}
int maptox(int map) {                                                              //map数组转x坐标
	return (map % BLOCK_WIDTH);
}
int maptoy(int map) {                                                              //map数组转y坐标
	return (map / BLOCK_WIDTH);
}
int xytomap(int x, int y) {                                                         //xy坐标转map
	return (y * BLOCK_WIDTH + x);
}

void k(int x, int y, int m, int n) {                      //将每个墙的大坐标录入数组
	int* p;                                       //m用来区分是门还是墙 m=1时 代表门 ；m=0时 代表墙
	p = &K[x][y];                                 //n用来重置二维数组 使K【】【】归0 默认n=0；n=1时重置
	if (n == 0) {
		*p = 1 + m;
	}
	else *p = 0;
}
void kx(int x, int y, int m, int n) {                      //将每个墙的大坐标录入数组
	int* p;                                       //m用来区分是门还是墙 m=1时 代表门 ；m=0时 代表墙
	p = &K1[x][y];                                 //n用来重置二维数组 使K【】【】归0 默认n=0；n=1时重置
	if (n == 0) {
		*p = 1 + m;
	}
	else *p = 0;
}
void kx1(int x, int y, int m, int n) {                      //将每个墙的大坐标录入数组
	int* p;                                       //m用来区分是门还是墙 m=1时 代表门 ；m=0时 代表墙
	p = &K2[x][y];                                 //n用来重置二维数组 使K【】【】归0 默认n=0；n=1时重置
	if (n == 0) {
		*p = 1 + m;
	}
	else *p = 0;
}
///////////////////////////////////////////////////////////
void gamewindowshake() {                              //画面震动
	if (WINDOW_SHAKE < SHAKE) {
		int x = rand() % 30 - 15;
		int y = rand() % 30 - 15;
		CAMERA_X = x;
		CAMERA_Y = y;
		WINDOW_SHAKE++;
	}
	else {
		CAMERA_X = 0;
		CAMERA_Y = 0;
	}
}
/// //////////////////////////////////////////////////////////////////////////
void drawbk() {                                          //打印边界
	setfillcolor(BK_COLOR);
	setlinecolor(BK_COLOR);
	fillrectangle(0, 0, PYI_X / 2 + CAMERA_X, HEIGHT + CAMERA_Y);
	fillrectangle((WIDTH - PYI_X / 2) + CAMERA_X, 0 + CAMERA_Y, WIDTH + CAMERA_X, HEIGHT + CAMERA_Y);
	fillrectangle(0 + CAMERA_X, 0 + CAMERA_Y, WIDTH + CAMERA_X, PYI_Y / 2 + CAMERA_Y);
	fillrectangle(0 + CAMERA_X, HEIGHT + CAMERA_Y, WIDTH + CAMERA_X, (HEIGHT - PYI_Y / 2) + CAMERA_Y);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void gamepause() {                                //游戏暂停
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(90, 50, _T("Consolas"));
	RECT r = { 0, 0, WIDTH ,HEIGHT };
	drawtext(_T("Pause!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(15, 16, _T("Consolas"));
	drawroundrect(WIDTH + 8, 20, 60, 35, 3, 10, jp_COLOR1, jp_COLOR2);               //Esc
	RECT a1 = { WIDTH + 15,20,WIDTH + 60,60 };
	drawtext(_T("Esc"), &a1, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 260, 30, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //上
	RECT a3 = { WIDTH + 272,30,WIDTH + 300,70 };
	drawtext(_T("W"), &a3, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 260, 80, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //下
	RECT a4 = { WIDTH + 272,80,WIDTH + 300,120 };
	drawtext(_T("S"), &a4, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 210, 80, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //左
	RECT a5 = { WIDTH + 222,80,WIDTH + 250,120 };
	drawtext(_T("A"), &a5, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 310, 80, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //右
	RECT a6 = { WIDTH + 322,80,WIDTH + 350,120 };
	drawtext(_T("D"), &a6, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 10, 150, 200, 30, 3, 10, jp_COLOR1, jp_COLOR2);             //空格
	drawroundrect(WIDTH + 90, 20, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //存档B
	RECT a2 = { WIDTH + 100,20,WIDTH + 160,60 };
	drawtext(_T("B"), &a2, DT_TOP | DT_VCENTER | DT_SINGLELINE);

	RECT a9 = { WIDTH ,100,P_WIDTH - 10 ,130 };
	drawtext(_T("Esc存档 B读档"), &a9, DT_TOP | DT_VCENTER | DT_SINGLELINE);

	RECT a7 = { WIDTH + 10,180,P_WIDTH ,210 };
	drawtext(_T("WSAD 上下左右控制移动"), &a7, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a8 = { WIDTH + 10,210,P_WIDTH ,240 };
	drawtext(_T("空格 暂停"), &a8, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a10 = { WIDTH + 10,240,P_WIDTH ,270 };
	drawtext(_T("先空格暂停 才能存读档"), &a10, DT_TOP | DT_VCENTER | DT_SINGLELINE);

	settextcolor(BK_COLOR4);

	RECT a11 = { WIDTH + 40,280,P_WIDTH ,310 };
	drawtext(_T("突袭怪 伤害50"), &a11, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a12 = { WIDTH + 40,310,P_WIDTH ,350 };
	drawtext(_T("小怪 伤害10"), &a12, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a13 = { WIDTH + 40,315,P_WIDTH ,405 };
	drawtext(_T("钥匙 开门后 key-1"), &a13, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a14 = { WIDTH + 40,340,P_WIDTH ,440 };
	drawtext(_T("树叶 生命恢复 HP+50"), &a14, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a15 = { WIDTH + 40,382,P_WIDTH ,462 };
	drawtext(_T("楼梯 前往其他楼层"), &a15, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a16 = { WIDTH + 40,414,P_WIDTH ,497 };
	drawtext(_T("<--记住 这是你"), &a16, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a17 = { WIDTH + 40,500,P_WIDTH ,550 };
	drawpixal(68, 18, BIG_COLOR, 0, 1);
	drawcircle(68, 20, SMALL_COLOR, 0, 1);
	keyshape(68, 22, KEY_COLOR, 0, 1);
	drawpie(68, 24, BLOOD_COLOR, 0, 1);
	buildstair(68, 26, STAIR_COLOR, 3);
	drawpixal(68, 28, HERO_COLOR, 0, 1);

	FlushBatchDraw();			//将缓冲输出到屏幕
	while (1) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 32) {
				break;
			}
			else if (ch == 98) {
				read();
				drawtext(_T("读档成功"), &a17, DT_TOP | DT_VCENTER | DT_SINGLELINE);
			}
			else if (ch == 27) {
				remove("test.txt");
				drawtext(_T("存档成功"), &a17, DT_TOP | DT_VCENTER | DT_SINGLELINE);
				maptest(0);
				maptest(1);
				bigtest();
				smalltest();
				bloodtest(0);
				bloodtest(1);
				keytest(0);
				doortest();
				herotest();
			}
		}
		drawbk();
		FlushBatchDraw();			//将缓冲输出到屏幕
	}
}
/// //////////////////////////////////////////////////////////////////////////
void draw(int pos, RECT rct, DWORD* pBufImg, DWORD* pBuf) {
	clock_t t = clock();
	float y = (float)pos;	// 当前文字像素行映射在屏幕上的坐标
	for (int i = 0; i < (int)rct.bottom; i++)
	{
		y++;
		if (y >= py) break;
		else if (y < 0)
		{
			i = -pos - 1;
			y = 0;
			continue;
		}
		for (int j = 0; j < rct.right; j++)
		{
			if (pBufImg[(int)i * rct.right + j] == WHITE)
				pBuf[(int)y * px + (int)((px - (int)(rct.right * (float)px / rct.right)) / 2 + (float)px / rct.right * j)] = RGB(200, 200, 200);
		}
	}
	// 帧率均衡
	int delay = 1000 / 24 - (clock() - t);
	if (delay > 0)
	{
		Sleep(delay);
	}
}

void gameend() {

	if (HERO.HP <= -10000) {
		RECT rct = { 0 };
		settextstyle(font_h, font_w, L"system");
		drawtext(pszText, &rct, DT_CALCRECT);

		IMAGE imgText(rct.right, rct.bottom);
		DWORD* pBufImg = GetImageBuffer(&imgText);
		SetWorkingImage(&imgText);
		settextstyle(font_h, font_w, L"system");
		drawtext(pszText, &rct, DT_CENTER);
		SetWorkingImage();
		DWORD* pBuf = GetImageBuffer();
		BeginBatchDraw();

		// 图片输出偏移
		for (int pos = py; pos > -rct.bottom; pos -= 2)
		{
			cleardevice();
			draw(pos, rct, pBufImg, pBuf);
			FlushBatchDraw();
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
void gameend2() {
	if (HERO.HP <= 0) {
		// 窗口宽高
		int nWindowWidth = 1497;
		int nWindowHeight = 720;

		int font_h = 200;					// 文字高
		int font_w = 20;					// 文字宽
		short nStartLightness = 255;		// 初始亮度
		short nEndLightness = 60;			// 最终亮度
		float fEndWidthRatio = (float)0.65;	// 宽度缩放比例
		float fEndHeightRatio = (float)0.3;	// 高度缩放比例

		int fps = 24;		// 帧率
		int nAmount = 2;	// 文字单次位移


		RECT rct = { 0 };
		settextstyle(font_h, font_w, L"system");
		drawtext(pszText, &rct, DT_CALCRECT);

		IMAGE imgText(rct.right, rct.bottom);
		DWORD* pBufImg = GetImageBuffer(&imgText);
		SetWorkingImage(&imgText);
		settextstyle(font_h, font_w, L"system");
		drawtext(pszText, &rct, DT_CENTER);
		SetWorkingImage();
		DWORD* pBuf = GetImageBuffer();

		// 将文本宽度压缩为窗口宽度
		float fWindowWidthRatio = (float)nWindowWidth / rct.right;

		BeginBatchDraw();

		clock_t t;

		float f_kLightness = (float)(nStartLightness - nEndLightness) / nWindowHeight;
		float f_kWidth = (1 - fEndWidthRatio) / nWindowHeight;
		float f_kHeight = (1 - fEndHeightRatio) / nWindowHeight;

		// 图片输出偏移
		for (int pos = nWindowHeight; pos > -rct.bottom; pos -= nAmount)
		{
			t = clock();
			cleardevice();

			float y = (float)pos;	// 当前文字像素行映射在屏幕上的坐标
			for (int i = 0; i < (int)(rct.bottom /** fWindowWidthRatio*/); i++)
			{
				y += f_kHeight * y + fEndHeightRatio;

				if (y >= nWindowHeight)
				{
					break;
				}
				else if (y < 0)
				{
					i = -pos - 1;
					y = 0;
					continue;
				}

				short nLightness = (int)(f_kLightness * (int)y) + nEndLightness;
				float fWidthRatio = (f_kWidth * (int)y + fEndWidthRatio) * fWindowWidthRatio;
				int nWidth = (int)(rct.right * fWidthRatio);
				int nHalfWhite = (nWindowWidth - nWidth) / 2;
				for (int j = 0; j < rct.right; j++)
				{
					if (pBufImg[(int)(i /*/ fWindowWidthRatio*/)*rct.right + j] == WHITE)
					{
						//putpixel(nHalfWhite + fWidthRatio * j, y, RGB(nLightness, nLightness, nLightness));
						pBuf[(int)y * nWindowWidth + (int)(nHalfWhite + fWidthRatio * j)] = RGB(nLightness+80, nLightness, nLightness);
					}
				}
			}

			FlushBatchDraw();

			// 帧率均衡
			int delay = 1000 / fps - (clock() - t);
			if (delay > 0)
			{
				Sleep(delay);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
void information() {
	settextcolor(TEXT_COLOR);
	settextstyle(0, 12, _T("Consolas"));
	RECT a1 = { WIDTH + 3 ,10,P_WIDTH,50 };
	RECT a2 = { WIDTH + 3 ,10 + 2 * WEN_DISTANT,P_WIDTH,50 + 2 * WEN_DISTANT };
	RECT a3 = { WIDTH + 3 ,10 + 4 * WEN_DISTANT,P_WIDTH,50 + 6 * WEN_DISTANT };
	RECT a31 = { WIDTH + 220 ,10 + 4 * WEN_DISTANT,P_WIDTH,50 + 6 * WEN_DISTANT };
	RECT a4 = { WIDTH + 3 ,10 + 6 * WEN_DISTANT,P_WIDTH,50 + 8 * WEN_DISTANT };
	RECT a5 = { WIDTH + 3 ,HEIGHT - 30,P_WIDTH,HEIGHT - 10 };
	drawtext(_T("HERO_LEVEL："), &a1, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("HERO_HP："), &a2, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("HERO_power："), &a3, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("HERO_skill："), &a31, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("HERO_key："), &a4, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("<<按空格键查看更多>>"), &a5, DT_TOP | DT_SINGLELINE | DT_CENTER);

	TCHAR s1[10] = { 0 };
	_stprintf_s(s1, _T("%d"), HERO.level);
	outtextxy(WIDTH + 3 + WEN_LR, 10, s1);
	TCHAR s2[10] = { 0 };
	_stprintf_s(s2, _T("%d"), HERO.HP);
	outtextxy(WIDTH + 3 + WEN_LR, 10 + 2 * WEN_DISTANT, s2);
	TCHAR s3[10] = { 0 };
	_stprintf_s(s3, _T("%d"), HERO.power);
	outtextxy(WIDTH + 3 + WEN_LR, 10 + 4 * WEN_DISTANT, s3);
	TCHAR s4[10] = { 0 };
	_stprintf_s(s4, _T("%d"), HERO.key);
	outtextxy(WIDTH + 3 + WEN_LR, 10 + 6 * WEN_DISTANT, s4);
	TCHAR s5[10] = { 0 };
	_stprintf_s(s5, _T("%d"), HERO.skill);
	outtextxy(WIDTH + 210 + WEN_LR, 10 + 4 * WEN_DISTANT, s5);

	setfillcolor(BLUE);
	int a = HERO.i * (5 * WEN_DISTANT);
	int b = HERO.j * (2 * WEN_DISTANT);
	fillrectangle(a+WIDTH -4+ 1 * WEN_DISTANT, b+5 + 8 * WEN_DISTANT, a+WIDTH-15 + 4 * WEN_DISTANT, b+5 + 9 * WEN_DISTANT);

	settextcolor(GREEN);
	setbkmode(TRANSPARENT);
	RECT b1 = { WIDTH + 1 * WEN_DISTANT,10 + 8 * WEN_DISTANT,WIDTH + 3 + 4 * WEN_DISTANT,10 + 10 * WEN_DISTANT };
	drawtext(_T("生命恢复"), &b1, DT_TOP | DT_SINGLELINE | DT_LEFT);
	RECT b2 = { WIDTH + 6 * WEN_DISTANT,10 + 8 * WEN_DISTANT,WIDTH + 3 + 9 * WEN_DISTANT,10 + 10 * WEN_DISTANT };
	drawtext(_T("镭射枪"), &b2, DT_TOP | DT_SINGLELINE | DT_LEFT);
	RECT b3 = { WIDTH + 1 * WEN_DISTANT,10 + 10 * WEN_DISTANT,WIDTH + 3 + 4 * WEN_DISTANT,10 + 12 * WEN_DISTANT };
	drawtext(_T("穿越闪现"), &b3, DT_TOP | DT_SINGLELINE | DT_LEFT);
	RECT b4 = { WIDTH + 6 * WEN_DISTANT,10 + 10 * WEN_DISTANT,WIDTH + 3 + 9 * WEN_DISTANT,10 + 12 * WEN_DISTANT };
	drawtext(_T("免疫伤害"), &b4, DT_TOP | DT_SINGLELINE | DT_LEFT);

	setfillcolor(TEXT_COLOR);
	fillrectangle(WIDTH + 3, 8 + WEN_DISTANT, P_WIDTH - 10, 32 + WEN_DISTANT);                            //LEVEL进度条
	fillrectangle(WIDTH + 3, 8 + 3 * WEN_DISTANT, P_WIDTH - 10, 32 + 3 * WEN_DISTANT);                    //HP进度条
	fillrectangle(WIDTH + 3, 8 + 5 * WEN_DISTANT, P_WIDTH - 10, 32 + 5 * WEN_DISTANT);                    //power进度条
	//	fillrectangle(WIDTH + 4, HEIGHT - 8 - 9 * WEN_DISTANT, P_WIDTH - 10, HEIGHT - 8);                  //原底框

	setfillcolor(BLACK);
	fillrectangle(WIDTH + 3 + WEN_P, 8 + WEN_DISTANT + WEN_P, P_WIDTH - 10 - WEN_P, 32 + WEN_DISTANT - WEN_P);             //LEVEL进度条黑色遮码
	fillrectangle(WIDTH + 3 + WEN_P, 8 + 3 * WEN_DISTANT + WEN_P, P_WIDTH - 10 - WEN_P, 32 + 3 * WEN_DISTANT - WEN_P);           //HP进度条黑色遮码
	fillrectangle(WIDTH + 3 + WEN_P, 8 + 5 * WEN_DISTANT + WEN_P, P_WIDTH - 10 - WEN_P, 32 + 5 * WEN_DISTANT - WEN_P);           //power进度条黑色遮码
	//	fillrectangle(WIDTH + 4 + WEN_P, HEIGHT - 8 - 9 * WEN_DISTANT + WEN_P, P_WIDTH - 10 - WEN_P, HEIGHT - 8 - WEN_P);       //原底框黑色遮码
	setlinecolor(WEN_COLOR);
	setfillcolor(WEN_COLOR);
	fillrectangle(WIDTH + 3 + WEN_P, 8 + WEN_DISTANT + WEN_P, WIDTH + 3 + WEN_P + 4 * (HERO.EXP % 100), 32 + WEN_DISTANT - WEN_P);
	if (HERO.HP >= 0)
		fillrectangle(WIDTH + 3 + WEN_P, 8 + 3 * WEN_DISTANT + WEN_P, WIDTH + 3 + WEN_P + 4 * HERO.HP/HERO.TOPHP*100, 32 + 3 * WEN_DISTANT - WEN_P);
	fillrectangle(WIDTH + 3 + WEN_P, 8 + 5 * WEN_DISTANT + WEN_P, WIDTH + 3 + WEN_P + 4 * HERO.power, 32 + 5 * WEN_DISTANT - WEN_P);
}


void informationupdate() {
	HERO.level = HERO.EXP / 100 + 1;
	HERO.TOPHP = 100 + 20 * (HERO.level - 1);
	if (HERO.HP >= HERO.TOPHP) HERO.HP = HERO.TOPHP;
	if (HERO.power >= 100) { HERO.power = 0; HERO.skill++; }
	if (rand() % 100 == 0) HERO.power++;
	if (HERO.i < 0) HERO.i++;
	else if (HERO.i > 1)  HERO.i--;
	if (HERO.j < 0)HERO.j++;
	else if (HERO.j > 1)HERO.j--;
}
//////////////////////////////////////////////////////////////////////////////
void drawpixal(int x, int y, COLORREF COLOR, float xy, int s) {             //绘制方格
	float xy2 = xy / 2;
	setfillcolor(COLOR);
	setlinecolor(COLOR);
	if (s)
		fillrectangle(x * BLOCK_XY + x * BLOCK_JJ + xy2 + py_x + CAMERA_X,
			y * BLOCK_XY + y * BLOCK_JJ + xy2 + py_y + CAMERA_Y,
			BLOCK_XY + x * BLOCK_XY + x * BLOCK_JJ - xy2 + py_x + CAMERA_X,
			BLOCK_XY + y * BLOCK_XY + y * BLOCK_JJ - xy2 + py_y + CAMERA_Y);
}

void drawcircle(int x, int y, COLORREF COLOR, float xy, int s) {      //绘制圆
	float xy2 = xy / 2;
	setfillcolor(COLOR);
	setlinecolor(COLOR);
	if (s)
		fillcircle(x * (BLOCK_XY + BLOCK_JJ) + xy2 + py_x + CAMERA_X + BLOCK_XY / 2,
			y * (BLOCK_XY + BLOCK_JJ) + xy2 + py_y + CAMERA_Y + BLOCK_XY / 2, 4);
}

void drawpie(int x, int y, COLORREF COLOR, float xy, int s) {                        //画扇形
	float xy2 = xy / 2;
	setfillcolor(COLOR);
	setlinecolor(COLOR);
	if (s)
		fillpie(x * BLOCK_XY + x * BLOCK_JJ + xy2 + py_x + CAMERA_X,
			y * BLOCK_XY + y * BLOCK_JJ + xy2 + py_y + CAMERA_Y,
			BLOCK_XY + x * BLOCK_XY + x * BLOCK_JJ - xy2 + py_x + CAMERA_X,
			BLOCK_XY + y * BLOCK_XY + y * BLOCK_JJ - xy2 + py_y + CAMERA_Y,
			1.7, 4);
}

void keyshape(int x, int y, COLORREF COLOR, float xy, int s) {
	float xy2 = xy / 2;
	setlinecolor(COLOR);
	setfillcolor(COLOR);
	if (s) {
		fillrectangle(x * BLOCK_XY + x * BLOCK_JJ + xy2 + py_x + CAMERA_X + 7,
			y * BLOCK_XY + y * BLOCK_JJ + xy2 + py_y + CAMERA_Y + 2,
			BLOCK_XY + x * BLOCK_XY + x * BLOCK_JJ - xy2 + py_x + CAMERA_X - 7,
			BLOCK_XY + y * BLOCK_XY + y * BLOCK_JJ - xy2 + py_y + CAMERA_Y - 2);

		fillcircle(x * (BLOCK_XY + BLOCK_JJ) + xy2 + py_x + CAMERA_X + BLOCK_XY / 2,
			y * (BLOCK_XY + BLOCK_JJ) + xy2 + py_y + CAMERA_Y + BLOCK_XY - 4, 3);
		setfillcolor(BLACK);
		fillcircle(x * (BLOCK_XY + BLOCK_JJ) + xy2 + py_x + CAMERA_X + BLOCK_XY / 2,
			y * (BLOCK_XY + BLOCK_JJ) + xy2 + py_y + CAMERA_Y + BLOCK_XY - 4, 2);
	}

}

void drawroundrect(int x, int y, int L1, int L2, int p, int e, COLORREF COLOR1, COLORREF COLOR2) {
	setfillcolor(COLOR1);
	fillroundrect(x, y, x + L1, y + L2, e, e);
	setlinecolor(COLOR2);
	setfillcolor(COLOR2);
	fillroundrect(x + p, y + p, x + L1 - p, y + L2 - p, e, e);
}

void drawjpz(int x, int y, int x1, int x2, int i) {
	RECT a = { x,y,x1,x2 };
	if (i == 0) drawtext(_T("W"), &a, DT_TOP | DT_LEFT);
	if (i == 1) drawtext(_T("S"), &a, DT_TOP | DT_LEFT);
	if (i == 2) drawtext(_T("A"), &a, DT_TOP | DT_LEFT);
	if (i == 3) drawtext(_T("D"), &a, DT_TOP | DT_LEFT);
	if (i == 4) drawtext(_T("Esc"), &a, DT_TOP | DT_LEFT);
	if (i == 5) drawtext(_T("B"), &a, DT_TOP | DT_LEFT);
	if (i == 6) drawtext(_T("空格"), &a, DT_TOP | DT_LEFT);
}

void drawarr(int i,int j) {
	setfillcolor(BLACK);
	setlinecolor(GREEN);
	if (i == 1 && j == 0) {
		if (HERO.dy == 0 && HERO.dx == -1) {
			fillrectangle(HERO.x * (BLOCK_XY + BLOCK_JJ) + py_x + CAMERA_X + BLOCK_XY / 2 - 2,
				HERO.y * (BLOCK_XY + BLOCK_JJ) + py_y + CAMERA_Y + BLOCK_XY / 2 - 2,
				10 + CAMERA_X,
				HERO.y * (BLOCK_XY + BLOCK_JJ) + py_y + CAMERA_Y + BLOCK_XY / 2 + 2);
		}
		else if (HERO.dy == 0 && HERO.dx == 1) {
			fillrectangle(HERO.x * (BLOCK_XY + BLOCK_JJ) + py_x + CAMERA_X + BLOCK_XY / 2 - 2,
				HERO.y * (BLOCK_XY + BLOCK_JJ) + py_y + CAMERA_Y + BLOCK_XY / 2 - 2,
				WIDTH - 10 + CAMERA_X,
				HERO.y * (BLOCK_XY + BLOCK_JJ) + py_y + CAMERA_Y + BLOCK_XY / 2 + 2);
		}
		else if (HERO.dy == -1 && HERO.dx == 0) {
			fillrectangle(HERO.x * (BLOCK_XY + BLOCK_JJ) + py_x + CAMERA_X + BLOCK_XY / 2 - 2,
				HERO.y * (BLOCK_XY + BLOCK_JJ) + py_y + CAMERA_Y + BLOCK_XY / 2-2,
				HERO.x * (BLOCK_XY + BLOCK_JJ) + py_x + CAMERA_X + BLOCK_XY / 2 + 2,
				10 + CAMERA_Y);
		}
		else if (HERO.dy == 1 && HERO.dx == 0) {
			fillrectangle(HERO.x * (BLOCK_XY + BLOCK_JJ) + py_x + CAMERA_X + BLOCK_XY / 2 - 2,
				HERO.y * (BLOCK_XY + BLOCK_JJ) + py_y + CAMERA_Y + BLOCK_XY / 2 - 2,
				HERO.x * (BLOCK_XY + BLOCK_JJ) + py_x + CAMERA_X + BLOCK_XY / 2 + 2,
				HEIGHT - 10 + CAMERA_Y);
		}
	}
}

void buildstair(int x, int y, COLORREF COLOR, int p) {
	setlinecolor(BLACK);
	setfillcolor(COLOR);
	fillrectangle(x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X,
		y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y + p,
		BLOCK_XY + x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X,
		BLOCK_XY + y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y - p);
	fillrectangle(x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X,
		y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y + (p + 2),
		BLOCK_XY + x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X,
		BLOCK_XY + y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y - (p + 2));
	fillrectangle(x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X,
		y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y + (p + 4),
		BLOCK_XY + x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X,
		BLOCK_XY + y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y - (p + 4));
}
/// ////////////////////////////////////////////////////////
struct door {
	int x[20] = { 19,43,58,2,23,52,14,38,43,59, 8,28,43,43,54,23,23,58, 2,23 };                                            //门的地图坐标x和y
	int y[20] = { 2, 2, 2,8, 7, 8,19,19,17,19,23,23,23,38,38,16,22,23,28,34 };
	int xx[20] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };                                 //门的开启与否  1未开启 0已开启
	int sxzy[20] = { 1,1,1,0,0,0,0,0,1,0,1,1,1,1,1,0,0,1,0,0 };                               //门的放置形态 1是上下，0是左右
}DOOR;

struct dooropen {                                                              //门关闭时 门粒子
	int n[20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };            //每个门粒子需要移动的距离
	int ting[20] = { 0 };                                                       //如果ting=0 则门粒子一直往后退
}DOOROPEN[20];

void doortest() {
	ofstream ofs;
	ofs.open("test.txt", ios::app);
	if (ofs.is_open())
		for (int i = 0; i < 20; i++) {
			ofs << DOOR.xx[i] << " ";
			for (int j = 0; j < 20; j++)
				ofs << DOOROPEN[i].n[j] << " ";
		}
}

void initdooropen(int i) {   //重置门粒子的n
	for (int n = 0; n < 20; n++)
		DOOROPEN[i].n[n] = n + 1;
}

void kdoor(int x, int y, int sxzy) {                                                             //前两个k（） 用来记录门坐标2   后两个k（） 用来记录门两侧辅助墙的坐标1
	if (sxzy) k(x, y, 1, 0), k(x, y + 1, 1, 0),
		k(x, y - 1, 0, 0), k(x, y + 2, 0, 0),
		k(x - 1, y - 1, 0, 0), k(x - 1, y + 2, 0, 0),
		k(x + 1, y - 1, 0, 0), k(x + 1, y + 2, 0, 0);
	else k(x, y, 1, 0), k(x + 1, y, 1, 0),
		k(x - 1, y, 0, 0), k(x + 2, y, 0, 0),
		k(x - 1, y - 1, 0, 0), k(x + 2, y - 1, 0, 0),
		k(x - 1, y + 1, 0, 0), k(x + 2, y + 1, 0, 0);
}

void initdoor() {                         //将门坐标定位在K数组上
	for (int i = 0; i < 20; i++) {
		kdoor(DOOR.x[i], DOOR.y[i], DOOR.sxzy[i]);
	}
}

void initstair() {
	k(64, 42, 5, 0); k(64, 43, 5, 0);
	k(65, 42, 5, 0); k(65, 43, 5, 0);
	kx(1, 1, 5, 0); kx(2, 1, 5, 0);
	kx(1, 2, 5, 0); kx(2, 2, 5, 0);

}

void antidoor(int x, int y) {                                        //输入大坐标x和y  将对应二维数组内门的坐标2重置为0
	if (K[x - 1][y] == 2) x = x - 1;
	else if (K[x][y - 1] == 2) y = y - 1;
	for (int i = 0; i < 20; i++) {
		if (DOOR.x[i] == x && DOOR.y[i] == y) {
			DOOR.xx[i] = 0;
			k(x, y, 2, 1);
			if (DOOR.sxzy[i] == 1) k(x, y + 1, 2, 1);
			else if (DOOR.sxzy[i] == 0) k(x + 1, y, 2, 1);
			break;
		}
	}
}

void eachdoor(int x, int y, COLORREF COLOR, COLORREF COLOR1, int p, int sxzy, int n) {          //绘制单个门  x为大坐标X y为大坐标Y p为两侧门的空隙  n为关门时门后退的频率

	int ax = py_x + CAMERA_X;
	int ay = py_y + CAMERA_Y;
	int Band = BLOCK_XY + BLOCK_JJ;
	int a1 = 1, a2 = 1, b1 = 1, b2 = 1;
	if (sxzy == 1) { a1 = 0; b2 = 0; }
	else { a2 = 0; b1 = 0; }

	int s = 0;
	setfillcolor(COLOR);
	setlinecolor(COLOR);
	fillrectangle(x * Band + ax + b1 * p + n * b2,     //（小方格长度+间隔）*x 再减去两侧门的空隙p     
		y * Band + ay + b2 * p + n * b1,
		BLOCK_XY - 14 * b2 + x * Band + ax - b1 * p + n * b2,
		BLOCK_XY - 14 * b1 + y * Band + ay - b2 * p + n * b1);
	setfillcolor(COLOR1);
	setlinecolor(COLOR1);
	fillrectangle(x * Band + ax + b1 * (p + 2) + n * b2,     //（小方格长度+间隔）*x 再减去两侧门的空隙p     
		y * Band + ay + b2 * (p + 2) + n * b1,
		BLOCK_XY - 14 * b2 + x * Band + ax - b1 * (p + 2) + n * b2,
		BLOCK_XY - 14 * b1 + y * Band + ay - b2 * (p + 2) + n * b1);
}

void drawdoor() {
	for (int i = 0; i < 20; i++) {
		if (DOOR.xx[i] == 1)
			for (int n = 1; n < 30; n++) {                                       //循环打印所有的门
				eachdoor(DOOR.x[i], DOOR.y[i], DOOR_COLOR1, DOOR_COLOR2, 3, DOOR.sxzy[i], n);
			}
		else if (DOOR.xx[i] == 0) {
			for (int j = 0; j < 20; j++) {
				eachdoor(DOOR.x[i], DOOR.y[i], DOOR_COLOR1, DOOR_COLOR3, 3, DOOR.sxzy[i], DOOROPEN[i].n[j]);
				if (DOOROPEN[i].n[j] > 0) DOOROPEN[i].n[j]--;
			}
			antidoor(DOOR.x[i], DOOR.y[i]);
		}

	}
}
/// /////////////////////////////////////////////////////////////////
void buildwall(int x, int y, COLORREF COLOR, int p) {                     //建造单面墙
	int py_x = PYI_X / 2;
	int py_y = PYI_Y / 2;
	setfillcolor(COLOR);
	setlinecolor(COLOR);
	fillrectangle(x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X + p,     //（小方格长度+间隔）*x 再减去墙壁间的空隙p
		y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y + p,
		BLOCK_XY + x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X - p,
		BLOCK_XY + y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y - p);
}


void initwall(int a, int b) {                                                     //打印地图的砖块

	for (int i = 0; i < BLOCK_WIDTH; i++) 	k(i, 0, 0, 0);
	for (int i = 0; i < BLOCK_WIDTH; i++) 	k(i, BLOCK_HEIGHT - 1, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	k(0, i, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	k(BLOCK_WIDTH - 1, i, 0, 0);
	///////////////////////////上面是大方框///////////////
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 3)
		for (int j = 1; j < BLOCK_HEIGHT; j += 3) 	k(i, j, 0, 0);

	for (int i = 1; i < BLOCK_WIDTH - 1; i += 5)
		for (int j = 1; j < BLOCK_HEIGHT; j += 5) {
			k(i, j, 0, 0);          //8个随机方向  看b
			switch (b) {
			case 0: k(i + 1, j, 0, 0); break;
			case 1: k(i - 1, j, 0, 0); break;
			case 2:k(i, j + 1, 0, 0); break;
			case 3:k(i, j - 1, 0, 0); break;
			case 4:k(i + 1, j + 1, 0, 0); break;
			case 5:k(i - 1, j - 1, 0, 0); break;
			case 6:k(i - 1, j + 1, 0, 0); break;
			case 7:k(i + 1, j - 1, 0, 0);
			}
		}
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 6)
		for (int j = 1; j < BLOCK_HEIGHT; j += 6)  k(i, j, 0, 0);
	//在地图上打印出砖块点阵
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 7)
		for (int j = 1; j < BLOCK_HEIGHT; j += 7) 	k(i, j, 0, 0);

	for (int i = 1; i < BLOCK_WIDTH - 1; i += 4)
		for (int j = 1; j < BLOCK_HEIGHT; j += 4) {
			k(i, j, 0, 0);                  //四个随机点方向 看a
			switch (a) {
			case 0: k(i + 1, j, 0, 0); break;
			case 1: k(i - 1, j, 0, 0); break;
			case 2:k(i, j + 1, 0, 0); break;
			case 3:k(i, j - 1, 0, 0);
			}
		}
	for (int n = 0; n < 20; n++) kdoor(DOOR.x[n], DOOR.y[n], DOOR.sxzy[n]);

}
void drawwall() {                                                     //打印地图的砖块
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++) {
			if (K[i][j] == 1) {
				buildwall(i, j, BK_COLOR, 2);
				buildwall(i, j, BK_COLOR2, 3);
			}
			if (K[i][j] == 6) buildstair(i, j, STAIR_COLOR, 2);
		}
}
///////////////////////////////////////////////////////////////
void initwallx(int c, int d, int e) {                                                     //打印地图的砖块

	for (int i = 0; i < BLOCK_WIDTH; i++) 	kx(i, 0, 0, 0);
	for (int i = 0; i < BLOCK_WIDTH; i++) 	kx(i, BLOCK_HEIGHT - 1, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	kx(0, i, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	kx(BLOCK_WIDTH - 1, i, 0, 0);
	///////////////////////////上面是大方框///////////////
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 3)
		for (int j = 1; j < BLOCK_HEIGHT; j += 3) {
			k(i, j, 0, 0);
			switch (d) {                                    //8个随机方向  看b	
			case 0: kx(i + 1, j, 0, 0); break;
			case 1: kx(i - 1, j, 0, 0); break;
			case 2:kx(i, j + 1, 0, 0); break;
			case 3:kx(i, j - 1, 0, 0); break;
			case 4:kx(i + 1, j + 1, 0, 0); break;
			case 5:kx(i - 1, j - 1, 0, 0); break;
			case 6:kx(i - 1, j + 1, 0, 0); break;
			case 7:kx(i + 1, j - 1, 0, 0);
			}
		}

	for (int i = 1; i < BLOCK_WIDTH - 1; i += 5)
		for (int j = 1; j < BLOCK_HEIGHT; j += 5) {
			kx(i, j, 0, 0);
		}
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 6)
		for (int j = 1; j < BLOCK_HEIGHT; j += 6)  kx(i, j, 0, 0);
	//在地图上打印出砖块点阵
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 7)
		for (int j = 1; j < BLOCK_HEIGHT; j += 7) 	kx(i, j, 0, 0);

	for (int i = 1; i < BLOCK_WIDTH - 1; i += 4)
		for (int j = 1; j < BLOCK_HEIGHT; j += 4) {
			kx(i, j, 0, 0);                  //四个随机点方向 看a
			switch (c) {
			case 0: kx(i + 1, j, 0, 0); break;
			case 1: kx(i - 1, j, 0, 0); break;
			case 2:kx(i, j + 1, 0, 0); break;
			case 3:kx(i, j - 1, 0, 0);
			}
		}
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 4)
		for (int j = 1; j < BLOCK_HEIGHT; j += 4) {
			kx(i + 1, j - 2, 0, 0);                  //四个随机点方向 看a
			switch (e) {
			case 0: kx(i + 1, j + 1, 0, 0); break;
			case 1: kx(i - 1, j - 1, 0, 0); break;
			case 2:kx(i + 1, j + 1, 0, 0); break;
			case 3:kx(i - 1, j - 1, 0, 0);
			}
		}
	for (int n = 0; n < 20; n++) kdoor(DOOR.x[n], DOOR.y[n], DOOR.sxzy[n]);

}
/////////////////////////////////////////////////////////////
void drawwallx() {                                                     //打印地图的砖块
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++) {
			if (K1[i][j] == 1) {
				buildwall(i, j, BK_COLOR3, 2);
				buildwall(i, j, BK_COLOR4, 4);
			}
			if (K1[i][j] == 6) buildstair(i, j, STAIR_COLOR2, 2);
		}
}
////////////////////////////////////////////////////////////
void initwallx1() {
	for (int i = 0; i < BLOCK_WIDTH; i++) 	kx1(i, 0, 0, 0);
	for (int i = 0; i < BLOCK_WIDTH; i++) 	kx1(i, BLOCK_HEIGHT - 1, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	kx1(0, i, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	kx1(BLOCK_WIDTH - 1, i, 0, 0);
	///////////////////////////上面是大方框///////////////
}
void drawwallx1() {                                                     //打印地图的砖块
	for (int i = 0; i < BLOCK_WIDTH; i++)
		for (int j = 0; j < BLOCK_HEIGHT; j++) {
			if (K2[i][j] == 1) {
				buildwall(i, j, BK_COLOR5, 2);
				buildwall(i, j, BK_COLOR6, 4);
			}
			if (K2[i][j] == 6) buildstair(i, j, STAIR_COLOR2, 2);
		}
}
/////////////////////////////////////////////////////////////
void initsmall() {
	for (int n = 0; n < SMALLNUM; n++) {
	LOOP1:
		int i = rand() % BLOCK_WIDTH;
		int j = rand() % BLOCK_HEIGHT;
		if (K[i][j] == 0 && K[i + 1][j] == 0 && K[i - 1][j] == 0 && K[i][j + 1] == 0 && K[i][j - 1] == 0) {
			SMALL[n].x = i;
			SMALL[n].y = j;
			k(i, j, 2, 0);
		}
		else goto LOOP1;
	}
}
void drawsmall() {
	for (int n = 0; n < SMALLNUM; n++) {
		heroreact(SMALL[n].x, SMALL[n].y, 2, n);
		if (SMALL[n].s == 1)
			drawcircle(SMALL[n].x, SMALL[n].y, SMALL_COLOR, 0, SMALL[n].s);
	}
}
/// ////////////////////////////////////////////////
void initsmallx() {
	for (int n = 0; n < SMALLNUMX; n++) {
	LOOP1:
		int i = rand() % BLOCK_WIDTH;
		int j = rand() % BLOCK_HEIGHT;
		if (K1[i][j] == 0 && K1[i + 1][j] == 0 && K1[i - 1][j] == 0 && K1[i][j + 1] == 0 && K1[i][j - 1] == 0) {
			SMALLX[n].x = i;
			SMALLX[n].y = j;
			kx(i, j, 2, 0);
		}
		else goto LOOP1;
	}
}
void drawsmallx() {
	for (int n = 0; n < SMALLNUMX; n++) {
		heroreact(SMALLX[n].x, SMALLX[n].y, 2, n);
		if (SMALLX[n].s == 1)
			drawcircle(SMALLX[n].x, SMALLX[n].y, SMALLX_COLOR, 0, SMALLX[n].s);
	}
}
////////////////////////////////////////////////////
void initblood() {
	for (int n = 0; n < BLOODNUM; n++) {
	LOOP2:
		int i = rand() % BLOCK_WIDTH;
		int j = rand() % BLOCK_HEIGHT;
		if (K[i][j] == 0 && K[i + 1][j] == 0 && K[i - 1][j] == 0 && K[i][j + 1] == 0 && K[i][j - 1] == 0) {
			BLOOD[n].x = i;
			BLOOD[n].y = j;
			k(i, j, 3, 0);
		}
		else goto LOOP2;
	}
}

void drawblood() {
	for (int n = 0; n < BLOODNUM; n++) {
		heroreact(BLOOD[n].x, BLOOD[n].y, 4, n);
		if (BLOOD[n].s == 1)
			drawpie(BLOOD[n].x, BLOOD[n].y, BLOOD_COLOR, 0, BLOOD[n].s);
	}
}
////////////////////////////////////////////////////
void initbloodx() {
	for (int n = 0; n < BLOODNUMX; n++) {
	LOOP2:
		int i = rand() % BLOCK_WIDTH;
		int j = rand() % BLOCK_HEIGHT;
		if (K1[i][j] == 0 && K1[i + 1][j] == 0 && K1[i - 1][j] == 0 && K1[i][j + 1] == 0 && K1[i][j - 1] == 0) {
			BLOODX[n].x = i;
			BLOODX[n].y = j;
			kx(i, j, 3, 0);
		}
		else goto LOOP2;
	}
}

void drawbloodx() {
	for (int n = 0; n < BLOODNUMX; n++) {
		heroreact(BLOODX[n].x, BLOODX[n].y, 4, n);
		if (BLOODX[n].s == 1)
			drawpie(BLOODX[n].x, BLOODX[n].y, BLOOD_COLOR, 0, BLOODX[n].s);
	}
}
////////////////////////////////////////////////////
void initkey() {
	for (int n = 0; n < KEYNUM; n++) {
	LOOP4:
		int i = rand() % BLOCK_WIDTH;
		int j = rand() % BLOCK_HEIGHT;
		if (K[i][j] == 0 && K[i + 1][j] == 0 && K[i - 1][j] == 0 && K[i][j + 1] == 0 && K[i][j - 1] == 0) {
			KEY[n].x = i;
			KEY[n].y = j;
			k(i, j, 4, 0);
		}
		else goto LOOP4;
	}
}

void drawkey() {
	for (int n = 0; n < KEYNUM; n++) {
		heroreact(KEY[n].x, KEY[n].y, 5, n);
		if (KEY[n].s == 1)
			keyshape(KEY[n].x, KEY[n].y, KEY_COLOR, 0, KEY[n].s);
	}
}
////////////////////////////////////////////////////
struct lizi {
	float x = 0, y = 0;                        //粒子位置
	int sjx[6] = { -3, -3, 3, -3, -3, 3 };     //粒子三角形的三点坐标样式
	float dx = 0, dy = 0;                              //粒子速度
	float jd = 0;                              //粒子角度
	float djd = 0;                             //粒子旋转的角速度
	COLORREF RGB;                              //粒子颜色
}Lizi[LIZINUM];

void initlizi(int x, int y) {   //x,y为要显示的位置
	for (int i = 0; i < LIZINUM; i++) {
		Lizi[i].x = rand() % BLOCK_XY + x;
		Lizi[i].y = rand() % BLOCK_XY + y;


		Lizi[i].dx = (float)i / 4.0f * (rand() % 20 - 10) / 50.0f;
		Lizi[i].dy = (float)i / 4.0f * (rand() % 20 - 10) / 50.0f;

		Lizi[i].jd = rand() % 100 + 100;
		Lizi[i].djd = (rand() % 100 + 100) / 10000.0f;
	}
}

void drawlizi() {

	for (int i = 0; i < LIZINUM; i++) {

		setfillcolor(COLORREF RGB(255 - 1 * i, 180 - 3 * i, 180 - 3 * i));
		setlinecolor(COLORREF RGB(255 - 1 * i, 180 - 3 * i, 180 - 3 * i));
		Lizi[i].x += Lizi[i].dx;
		Lizi[i].y += Lizi[i].dy;

		//[i].dx *= MC;
		//Lizi[i].dy *= MC;
		Lizi[i].dy = Lizi[i].dy + G;

		Lizi[i].jd = Lizi[i].jd + Lizi[i].djd;
		jd = Lizi[i].jd;

		int ss[6] = {
		Lizi[i].sjx[0] * cos(jd) - Lizi[i].sjx[1] * sin(jd), Lizi[i].sjx[1] * cos(jd) + Lizi[i].sjx[0] * sin(jd),
		Lizi[i].sjx[2] * cos(jd) - Lizi[i].sjx[3] * sin(jd), Lizi[i].sjx[3] * cos(jd) + Lizi[i].sjx[2] * sin(jd),
		Lizi[i].sjx[4] * cos(jd) - Lizi[i].sjx[5] * sin(jd), Lizi[i].sjx[5] * cos(jd) + Lizi[i].sjx[4] * sin(jd),
		};

		int s[6] = {
			ss[0] + Lizi[i].x + CAMERA_X, ss[1] + Lizi[i].y + CAMERA_Y,
			ss[2] + Lizi[i].x + CAMERA_X, ss[3] + Lizi[i].y + CAMERA_Y,
			ss[4] + Lizi[i].x + CAMERA_X, ss[5] + Lizi[i].y + CAMERA_Y
		};

		fillpolygon((POINT*)s, 3);
	}
}
//////////////////////////////////////////////////////////////////////////
void initbig(int x) {
	if (x == 0) {
		for (int n = 0; n < BIGNUM; n++) {
		LOOP:	int i = rand() % BLOCK_WIDTH;
			int j = rand() % BLOCK_HEIGHT;
			if (K[i][j] == 0 && K[i + 1][j] == 0 && K[i - 1][j] == 0 && K[i][j + 1] == 0 && K[i][j - 1] == 0) {
				if (abs((HERO.x - i) * (HERO.x - i)) + abs((HERO.y - j) * (HERO.y - j)) >= 100) {
					BIG[n].x = i;
					BIG[n].y = j;
				}
				else goto LOOP;
			}
			else goto LOOP;
		}
	}
	if (x == 1) {
		for (int n = 0; n < BIGNUMX; n++) {
		LOOP1:	int i = rand() % BLOCK_WIDTH;
			int j = rand() % BLOCK_HEIGHT;
			if (K1[i][j] == 0 && K1[i + 1][j] == 0 && K1[i - 1][j] == 0 && K1[i][j + 1] == 0 && K1[i][j - 1] == 0) {
				if (abs((HERO.x - i) * (HERO.x - i)) + abs((HERO.y - j) * (HERO.y - j)) >= 100) {
					BIGX[n].x = i;
					BIGX[n].y = j;
				}
				else goto LOOP1;
			}
			else goto LOOP1;
		}
	}

}

void randomway(int i, int x) {                  //big遇到墙壁阻挡后改变运动方向
	//i为BIG序号  x为不同地图的big怪  0为主  1为副
LOOP:
	int ops = 0;
	int bigdy = 0, bigdx = 0;
	ops = rand() % 4;
	switch (ops) {
	case 0:
		bigdy = 1, bigdx = 0; break;
	case 1:
		bigdy = -1, bigdx = 0; break;
	case 2:
		bigdy = 0, bigdx = 1; break;
	case 3:
		bigdy = 0, bigdx = -1; break;
	}
	if (x == 1) {
		if (BIGX[i].dx == bigdx && BIGX[i].dy == bigdy)
			goto LOOP;
		BIGX[i].dy = bigdy;
		BIGX[i].dx = bigdx;
	}
	else if (x == 0) {
		if (BIG[i].dy == bigdy && bigdx == BIG[i].dx)
			goto LOOP;
		BIG[i].dx = bigdx; BIG[i].dy = bigdy;
	}

}
void intellbig(int i) {
	int* p = &K[0][0], n = 0, m = 0;                                       //big自动导航测试失败  暂缓计划
	if (BIG[i].x == HERO.x) {
		gamewindowshake();
		int x;
		x = BIG[i].x - HERO.x;
		p = &K[BIG[i].x][BIG[i].y];
		while (p != &K[HERO.x][HERO.y]) {
			if (x > 0) p--;
			else  p++;
			if (*p != 0) { n = 1; break; }
		}
		if (x > 0 && n == 0) BIG[i].dx = -1, BIG[i].dy = 0;
		else if (x < 0 && n == 0)BIG[i].dx = 1, BIG[i].dy = 0;
	}
	else if (BIG[i].y == HERO.y) {
		gamewindowshake();
		int y;
		y = BIG[i].y - HERO.y;
		p = &K[BIG[i].x][BIG[i].y];
		while (p != &K[HERO.x][HERO.y]) {
			if (y > 0) p -= WIDTH;
			else  p += WIDTH;
			if (*p != 0) { m = 1; break; }
		}
		if (y > 0 && m == 0) BIG[i].dx = 0, BIG[i].dy = -1;
		else if (y < 0 && m == 0)BIG[i].dx = 0, BIG[i].dy = 1;
	}
}

void initbigmove(int x) {  /////////当x为0 代表主世界   x为1时 代表副世界
	int t1 = 0;
	t1 == GetTickCount();		//获取电脑开机时间
	int a = 0;
	if (x == 0) {
		for (int i = 0; i < BIGNUM; i++) {
			a = rand();
			BIG[i].x = BIG[i].s * (BIG[i].x + BIG[i].dx);
			BIG[i].y = BIG[i].s * (BIG[i].y + BIG[i].dy);
			intellbig(i);
			if (K[BIG[i].x][BIG[i].y] == 1 || K[BIG[i].x][BIG[i].y] == 2) {
				BIG[i].x = BIG[i].s * (BIG[i].x - BIG[i].dx);
				BIG[i].y = BIG[i].s * (BIG[i].y - BIG[i].dy);
				randomway(i, 0);
			}
			if (K[BIG[i].x + BIG[i].dy][BIG[i].y + BIG[i].dx] != 1 || K[BIG[i].x + BIG[i].dy][BIG[i].y + BIG[i].dx] != 2 && K[BIG[i].x][BIG[i].y] != 1 || K[BIG[i].x][BIG[i].y] != 2) {                 //big暴走
				if (a % 2 == 0)
					randomway(i, 0);
			}
			if (t1 % 1 == 1) randomway(i, 0);
			heroreact(BIG[i].x, BIG[i].y, 1, i);
		}
	}
	if (x == 1) {
		for (int i = 0; i < BIGNUMX; i++) {
			a = rand();
			BIGX[i].x = BIGX[i].s * (BIGX[i].x + BIGX[i].dx);
			BIGX[i].y = BIGX[i].s * (BIGX[i].y + BIGX[i].dy);
			intellbig(i);
			if (K1[BIGX[i].x][BIGX[i].y] == 1 || K1[BIGX[i].x][BIGX[i].y] == 2) {
				BIGX[i].x = BIGX[i].s * (BIGX[i].x - BIGX[i].dx);
				BIGX[i].y = BIGX[i].s * (BIGX[i].y - BIGX[i].dy);
				randomway(i, 1);
			}
			if (K1[BIGX[i].x + BIGX[i].dy][BIGX[i].y + BIGX[i].dx] != 1 || K1[BIGX[i].x + BIGX[i].dy][BIGX[i].y + BIGX[i].dx] != 2 && K1[BIGX[i].x][BIGX[i].y] != 1 || K1[BIGX[i].x][BIGX[i].y] != 2) {
				if (a % 2 == 0)
					randomway(i, 1);
			}
			if (t1 % 1 == 1) randomway(i, 1);
			heroreact(BIGX[i].x, BIGX[i].y, 1, i);
		}
	}
}
void drawbig(int x) {
	if (x == 0) {
		for (int i = 0; i < BIGNUM; i++)
			if (BIG[i].s == 1)
				drawpixal(BIG[i].x, BIG[i].y, BIG_COLOR, 0, BIG[i].s);
	}
	if (x == 1) {
		for (int i = 0; i < BIGNUMX; i++)
			if (BIGX[i].s == 1)
				drawpixal(BIGX[i].x, BIGX[i].y, BIGX_COLOR, 0, BIGX[i].s);
	}
}
//////////////////////////////////////////////////////
void drawhero() {
	drawpixal(HERO.x, HERO.y, HERO_COLOR, 0, HERO.s);
}
void heroreact(int x, int y, int z, int i) {
	int a = 0;
	if (HERO.map == 0) {
		if (HERO.x == x && HERO.y == y && z == 1 || HERO.x - HERO.dx == x && HERO.y - HERO.dy == y && z == 1) {
			WINDOW_SHAKE = 0;
			gamewindowshake();
			initlizi(Xtox(x), Ytoy(y));
			HERO.HP -= 50;
			HERO.EXP += 60;
			HERO.power += 10;
			a = 1;
		}
		else if (HERO.x == x && HERO.y == y && z == 2) {
			WINDOW_SHAKE = 0;
			gamewindowshake();
			initlizi(Xtox(x), Ytoy(y));
			SMALL[i].x = 0;
			SMALL[i].y = 0;
			k(x, y, 2, 1);
			HERO.HP -= 10;
			HERO.EXP += 20;
			HERO.power += 5;
			a = 1;
		}
		else if (HERO.x == x && HERO.y == y && z == 3) {                  //门的二维重置已在antidoor（）函数完成，此处无需多写
			HERO.x = (HERO.x - HERO.dx);                                  //开门时的钥匙判定已放置在和肉move（）函数内，此处无需多写
			HERO.y = (HERO.y - HERO.dy);
			if (HERO.key > 0) {
				a = 1;
			}

		}
		else if (HERO.x == x && HERO.y == y && z == 4) {
			BLOOD[i].x = 0;
			BLOOD[i].y = 0;
			k(x, y, 3, 1);
			HERO.HP += 50;
			HERO.power += 10;
			a = 1;
		}
		else if (HERO.x == x && HERO.y == y && z == 5) {
			KEY[i].x = 0;
			KEY[i].y = 0;
			k(x, y, 4, 1);
			HERO.key++;
			HERO.power += 5;
			a = 1;
		}
		if (a == 1)
			switch (z) {
			case 1:	BIG[i].s = 0; break;                //z=1 控制big的存亡                          
			case 2:SMALL[i].s = 0; break;
			case 3:DOOR.xx[i] = 0; break;
			case 4:BLOOD[i].s = 0; break;
			case 5:KEY[i].s = 0; break;
			case 6:HERO.map = 1; break;
			}
		a = 0;
	}
	else if (HERO.map == 1) {
		if (HERO.x == x && HERO.y == y && z == 1 || HERO.x - HERO.dx == x && HERO.y - HERO.dy == y && z == 1) {
			WINDOW_SHAKE = 0;
			gamewindowshake();
			initlizi(Xtox(x), Ytoy(y));
			HERO.HP -= 50;
			HERO.EXP += 60;
			HERO.power += 100;
			a = 1;
		}
		else if (HERO.x == x && HERO.y == y && z == 2) {
			WINDOW_SHAKE = 0;
			gamewindowshake();
			initlizi(Xtox(x), Ytoy(y));
			SMALLX[i].x = 0;
			SMALLX[i].y = 0;
			kx(x, y, 2, 1);
			HERO.HP -= 20;
			HERO.EXP += 40;
			HERO.power += 200;
			a = 1;
		}
		else if (HERO.x == x && HERO.y == y && z == 4) {
			BLOODX[i].x = 0;
			BLOODX[i].y = 0;
			kx(x, y, 3, 1);
			HERO.HP += 50;
			HERO.power += 10;
			a = 1;
		}
		if (a == 1)
			switch (z) {
			case 1:	BIGX[i].s = 0; break;                //z=1 控制big的存亡                          
			case 2:SMALLX[i].s = 0; break;
			case 3:DOOR.xx[i] = 0; break;
			case 4:BLOODX[i].s = 0; break;
			case 5:KEY[i].s = 0; break;
			case 6:HERO.map = 1; break;
			}
		a = 0;
	}
}



void heromove() {
	char ch;
	if (_kbhit()) {
		ch = _getch();           //up 119  down 115  left 97  right 100  \n 13  " " 32

		switch (ch) {
		case 119: {  HERO.dx = 0;  HERO.dy = -1;  HERO.y--; HERO.power += 1; }  break;
		case 115: { HERO.dx = 0;  HERO.dy = 1;   HERO.y++; HERO.power += 1; } break;
		case 97: { HERO.dx = -1; HERO.dy = 0;   HERO.x--; HERO.power += 1; } break;
		case 100: { HERO.dx = 1;  HERO.dy = 0;   HERO.x++; HERO.power += 1; }  break;
		case 32:gamepause(); break;
		case 106:
		if(HERO.skill>0&&HERO.i==0&&HERO.j==1) {
			int t = HERO.map;
			HERO.map = 2;
			HERO.skill--;
			char ch = _getch();
			if (ch == 106) {
				HERO.map = t;
				break;
			}
		}break;
		case 112:heroskill(); break;      //p键
		case 109:HERO.map = 1; break;      //m键
		case 110:HERO.map = 0; break;      //n键
		case 72:HERO.j--; break;     //技能上
		case 80:HERO.j++; break;     //技能下
		case 75:HERO.i--; break;     //技能左
		case 77:HERO.i++; break;     //技能右
		default:break;
		}
		if (K[HERO.x][HERO.y] == 6&&HERO.map==0) { HERO.map = 1; HERO.x = 3; HERO.y = 2; }
		else if (K1[HERO.x][HERO.y] == 6&&HERO.map==1) { HERO.map = 0; HERO.x = 63; HERO.y = 42; }
	}
	if (HERO.map == 0) {
		if (K[HERO.x][HERO.y] == 1&&HERO.ss==1) {
			HERO.x = (HERO.x - HERO.dx);
			HERO.y = (HERO.y - HERO.dy);
		}
		if (K[HERO.x][HERO.y] == 2) {                        //前面heroreact（）函数的钥匙开门系统放置到此处
			if (HERO.key > 0) {
				antidoor(HERO.x, HERO.y);
				HERO.key--;
			}
			HERO.x = (HERO.x - HERO.dx);
			HERO.y = (HERO.y - HERO.dy);

		}
	}
	if (HERO.map == 1) {
		if (K1[HERO.x][HERO.y] == 1&&HERO.ss==1) {
			HERO.x = (HERO.x - HERO.dx);
			HERO.y = (HERO.y - HERO.dy);
		}
	}
	if (HERO.map == 2) {
		if (K2[HERO.x][HERO.y] == 1) {
			HERO.x = (HERO.x - HERO.dx);
			HERO.y = (HERO.y - HERO.dy);
		}
	}
}
//////////////////////////////////////////////////////
void maptest(int x) {
	ofstream ofs;
	ofs.open("test.txt", ios::app);
	if (ofs.is_open())
		for (int i = 0; i < BLOCK_WIDTH; i++)
			for (int j = 0; j < BLOCK_HEIGHT; j++) {
				if (x == 0)	ofs << K[i][j] << " ";
				else if (x == 1) ofs << K1[i][j] << " ";
			}
}
///////////////////////////////////////////////////////
void read() {                           //读取存档
	ifstream ifs;
	ifs.open("test.txt", ios::in);
	_ASSERT(ifs.is_open());
	char a;
	int i = 0;
	if (ifs.is_open()) {
		for (int i = 0; i < BLOCK_WIDTH; i++)
			for (int j = 0; j < BLOCK_HEIGHT; j++)
				ifs >> K[i][j];
		for (int i = 0; i < BLOCK_WIDTH; i++)
			for (int j = 0; j < BLOCK_HEIGHT; j++)
				ifs >> K1[i][j];
		for (int i = 0; i < BIGNUM; i++)
			switch (0) {
			case 0:	ifs >> BIG[i].x;
			case 1:	ifs >> BIG[i].y;
			case 2:ifs >> BIG[i].dx;
			case 3:	ifs >> BIG[i].dy;
			case 4:ifs >> BIG[i].s;
			}
		for (int i = 0; i < BIGNUMX; i++)
			switch (0) {
			case 0:	ifs >> BIGX[i].x;
			case 1:	ifs >> BIGX[i].y;
			case 2:ifs >> BIGX[i].dx;
			case 3:	ifs >> BIGX[i].dy;
			case 4:ifs >> BIGX[i].s;
			}
		for (int i = 0; i < SMALLNUM; i++)
		switch (0) {
			case 0:ifs >> SMALL[i].x;
			case 1:ifs >> SMALL[i].y;
			case 2:ifs >> SMALL[i].s;
			}
		for (int i = 0; i < SMALLNUMX; i++)
			switch (0) {
			case 0:ifs >> SMALLX[i].x;
			case 1:ifs >> SMALLX[i].y;
			case 2:ifs >> SMALLX[i].s;
			}
		for (int i = 0; i < BLOODNUM; i++)
			switch (0) {
			case 0:ifs >> BLOOD[i].x;
			case 1:ifs >> BLOOD[i].y;
			case 2:ifs >> BLOOD[i].s;
			}
		for (int i = 0; i < BLOODNUMX; i++)
			switch (0) {
			case 0:ifs >> BLOODX[i].x;
			case 1:ifs >> BLOODX[i].y;
			case 2:ifs >> BLOODX[i].s;
			}
		for (int i = 0; i < KEYNUM; i++)
			switch (0) {
     		case 0:ifs >> KEY[i].x;
			case 1:ifs >> KEY[i].y;
			case 2:ifs >> KEY[i].s;
			}
		if (ifs.is_open())
			for (int i = 0; i < 20; i++) {
				ifs >> DOOR.xx[i];
				for (int j = 0; j < 20; j++)
					ifs >> DOOROPEN[i].n[j];
			}
		switch (0) {
		case 0:	ifs >> HERO.x;
		case 1:	ifs >> HERO.y;
		case 2:	ifs >> HERO.dx;
		case 3:	ifs >> HERO.dy;
		case 4:	ifs >> HERO.level;
		case 5:	ifs >> HERO.EXP;
		case 6:	ifs >> HERO.HP;
		case 7:	ifs >> HERO.key;
		case 8:	ifs >> HERO.s;
		case 9:	ifs >> HERO.map;
		}
	}
}
/////////////////////////////////////////////////////
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )
int main() {
	srand((unsigned)time(NULL));	//随机数种子
	initgraph(P_WIDTH, P_HEIGHT);		//创建绘图窗口
	BeginBatchDraw();				//开始批量绘图
	DWORD t1, t2;
	t1 = t2 = GetTickCount();		//获取电脑开机时间
	static int a = 0, b = 0, c = 0, d = 0;
	a = rand() % 4;
	b = rand() % 8;
	c = rand() % 4;
	d = rand() % 8;
	initwall(a, b);
	initwallx(c, d, a);
	initwallx1();
	initstair();
	initdoor();
	initsmall();
//	initsmallx();
	initblood();
//	initbloodx();
	initkey();
	initbig(0);
//	initbig(1);

	while (1) {
		BeginBatchDraw();
		if (HERO.map == 0) {
			cleardevice();
			drawarr(HERO.i, HERO.j);
			drawwall();
			drawdoor();
			drawsmall();
			drawblood();
			drawkey();
			drawbig(0);
			drawhero();
		}
		else if (HERO.map == 1) {
			cleardevice();
			drawarr(HERO.i, HERO.j);
			drawwallx();
			drawsmallx();
			drawbloodx();
			drawbig(1);
			drawhero();
		}
		else if (HERO.map == 2) {
			cleardevice();
			drawwallx1();
			drawhero();
		}
		else if (HERO.map == 3) {
			drawhero();
		}
		gamewindowshake();
		drawlizi();

		if (t2 - t1 > GAMETIME) {         //使游戏非堵塞延时

			initbigmove(0);
			initbigmove(1);
			heromove();
			t1 = t2;
		}
		information();
		informationupdate();
		drawbk();

		FlushBatchDraw();         //将缓冲输出到屏幕;
		t2 = GetTickCount();
		gameend2();
	}
}