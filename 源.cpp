#include <graphics.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>                           //VS2022      easyx     �����ͼ  +��Ϸ�����ƶ�  +�浵
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

#define BLOCK_XY 15	//С����߳�
#define BLOCK_JJ 1		//С����֮��ļ��

COLORREF TEXT_COLOR = COLORREF RGB(110, 110, 180);			    // ����ɫ2
COLORREF HERO_COLOR = COLORREF RGB(100, 150, 150);		     //hero��ɫ
COLORREF BIG_COLOR = COLORREF RGB(255, 0, 0);		         //Big��ɫ
COLORREF BIGX_COLOR = COLORREF RGB(255, 0, 0);		         //Bigx��ɫ
COLORREF SMALL_COLOR = COLORREF RGB(100, 120, 120);          //small��ɫ
COLORREF SMALLX_COLOR = COLORREF RGB(164, 114, 229);          //smallx��ɫ
COLORREF BK_COLOR = COLORREF RGB(150, 150, 150);			 //Χǽ��ɫ1
COLORREF BK_COLOR2 = COLORREF RGB(80, 80, 80);			    //Χǽ��ɫ2
COLORREF BK_COLOR3 = COLORREF RGB(38, 89, 229);			    // Χǽ��ɫ3 
COLORREF BK_COLOR4 = COLORREF RGB(85, 226, 229);			    //Χǽ��ɫ4
COLORREF BK_COLOR5 = COLORREF RGB(132, 138, 79);			    //Χǽ��ɫ5
COLORREF BK_COLOR6 = COLORREF RGB(128, 85, 138);			    //Χǽ��ɫ6
COLORREF DOOR_COLOR1 = COLORREF RGB(120, 120, 250);			    // ����ɫ1 
COLORREF DOOR_COLOR2 = COLORREF RGB(120, 250, 120);			    // ����ɫ2
COLORREF DOOR_COLOR3 = COLORREF RGB(150, 120, 120);            //�ŵ���ɫ3
COLORREF WEN_COLOR = COLORREF RGB(0, 200, 0);			     // ��������ɫ
COLORREF BLOOD_COLOR = COLORREF RGB(200, 250, 200);           //blood����ɫ
COLORREF BLOODX_COLOR = COLORREF RGB(200, 250, 200);           //bloodx����ɫ
COLORREF KEY_COLOR = COLORREF RGB(100, 100, 200);             //key����ɫ
COLORREF STAIR_COLOR = COLORREF RGB(100, 200, 200);           //������ɫ1
COLORREF STAIR_COLOR2 = COLORREF RGB(203, 217, 229);           //������ɫ2
COLORREF jp_COLOR1 = COLORREF RGB(92, 92, 92);           //������ɫ1
COLORREF jp_COLOR2 = COLORREF RGB(66, 66, 66);           //������ɫ2


#define GAMETIME 150			//��Ϸ�ٶ�
#define LIZINUM 200	             //��������
#define DOORLIZINUM 20           //�Ŵ�ʱ���ӻ�����������
#define BIGNUM 20               //ͻϮ��������
#define BIGNUMX 20               //ͻϮ����x����
#define SMALLNUM 22               //��ͨ��������
#define SMALLNUMX 30               //��ͨ����x����
#define BLOODNUM 10              //��Ѫ������
#define BLOODNUMX 10              //��Ѫ��x����
#define KEYNUM 10                //Կ������
#define STARNUM 500              //������
int CAMERA_X = 0;				//���x����,0Ϊ��Ļ�м�
int CAMERA_Y = 0;				//���y����,0Ϊ��Ļ�м�
#define SHAKE 30				//����Ч����֡��
int WINDOW_SHAKE = 0;			//��¼�����˶��ٴ�

const int P_WIDTH = WIDTH + 417;     //��Ļ��� width
const int P_HEIGHT = HEIGHT;     //��Ļ�߶� height
const int WEN_DISTANT = 40;       //��Ϣ�����������ּ����
const int WEN_LR = 150;       //��Ϣ�����������ּ����
const int WEN_P = 2;           //��Ϣ����������߿���
const int BLOCK_WIDTH = WIDTH / (BLOCK_XY + BLOCK_JJ);	 //С����x������
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY + BLOCK_JJ); //С����y������

const int PYI_X = WIDTH - BLOCK_WIDTH * (BLOCK_XY + BLOCK_JJ);  //x���ϵ�ƫ��������Ϊ�ֱ��ʺͷ��񾭳���������
const int PYI_Y = HEIGHT - BLOCK_HEIGHT * (BLOCK_XY + BLOCK_JJ);//y���ϵ�ƫ��������Ϊ�ֱ��ʺͷ��񾭳���������
const int py_x = PYI_X / 2;
const int py_y = PYI_Y / 2;

const float G = 0;			        //����
const float MC = 0.9999f;		    //Ħ����
float jd = 0;
const int dooropening = 100;         //�ſ����ٶ�   dooropening/100  ��

// ���ڿ��
int px = 1497;
int py = 720;

int font_h = 200;					// ���ָ�
int font_w = 20;					// ���ֿ�

int K[WIDTH][HEIGHT] = { 0 };               //�����������Ķ�ά����     0�����   1����ǽ    2������   3����small   4�����Ѫ��  5����key  6����¥��
int K1[WIDTH][HEIGHT] = { 0 };               //�����������Ķ�ά����     0�����   1����ǽ    2������   3����small   4�����Ѫ��  5����key  6����¥��
int K2[WIDTH][HEIGHT] = { 0 };                //��ʱx=3  

wchar_t pszText[] =
L"You are dead������\n"
L"����������ҹ��\n"
L"������ˮ����ƽ���������¹�������\n"
L"�����沨ǧ����δ�������������\n"
L"������ת�Ʒ��飬���ջ��ֽ�������\n"
L"������˪�����ɣ�͡�ϰ�ɳ��������\n"
L"����һɫ���˳�������й����֡�\n"
L"���Ϻ��˳����£����º�������ˣ�\n"
L"�������������ѣ���������ֻ���ơ�\n"
L"��֪���´����ˣ�������������ˮ��\n"
L"����һƬȥ���ƣ�������ϲ�ʤ�\n"
L"˭�ҽ�ҹ�����ӣ��δ���˼����¥��\n"
L"����¥�����ǻ���Ӧ������ױ��̨��\n"
L"�����о�ȥ���������Ϸ�������\n"
L"��ʱ���������ţ�Ը���»����վ���\n"
L"���㳤�ɹⲻ�ȣ�����ǱԾˮ���ġ�\n"
L"��ҹ��̶���仨���������벻���ҡ�\n"
L"��ˮ����ȥ��������̶���¸���б��\n"
L"б�³����غ�����ʯ��������·��\n"
L"��֪���¼��˹飬����ҡ����������\n"
L"game made by ���\n";

struct Big {                             //big�Ľṹ��
	int x = 0, y = 0;                              //big���ֵĶ�ά����
	int dx = -1, dy = 0;                      //big�ƶ���Ĭ��xy����
	int s = 1;                             //big�Ĵ���״̬     1�������  2��������
}BIG[BIGNUM];

struct Bigx {                             //big�Ľṹ��
	int x = 0, y = 0;                              //big���ֵĶ�ά����
	int dx = -1, dy = 0;                      //big�ƶ���Ĭ��xy����
	int s = 1;                             //big�Ĵ���״̬     1�������  2��������
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


int Xtox(int x) {                                                                  //x������תС����
	return(x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X + BLOCK_XY / 2);
}
int Ytoy(int y) {                                                                  //y������תС����
	return(y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y + BLOCK_XY / 2);
}
int maptox(int map) {                                                              //map����תx����
	return (map % BLOCK_WIDTH);
}
int maptoy(int map) {                                                              //map����תy����
	return (map / BLOCK_WIDTH);
}
int xytomap(int x, int y) {                                                         //xy����תmap
	return (y * BLOCK_WIDTH + x);
}

void k(int x, int y, int m, int n) {                      //��ÿ��ǽ�Ĵ�����¼������
	int* p;                                       //m�����������Ż���ǽ m=1ʱ ������ ��m=0ʱ ����ǽ
	p = &K[x][y];                                 //n�������ö�ά���� ʹK����������0 Ĭ��n=0��n=1ʱ����
	if (n == 0) {
		*p = 1 + m;
	}
	else *p = 0;
}
void kx(int x, int y, int m, int n) {                      //��ÿ��ǽ�Ĵ�����¼������
	int* p;                                       //m�����������Ż���ǽ m=1ʱ ������ ��m=0ʱ ����ǽ
	p = &K1[x][y];                                 //n�������ö�ά���� ʹK����������0 Ĭ��n=0��n=1ʱ����
	if (n == 0) {
		*p = 1 + m;
	}
	else *p = 0;
}
void kx1(int x, int y, int m, int n) {                      //��ÿ��ǽ�Ĵ�����¼������
	int* p;                                       //m�����������Ż���ǽ m=1ʱ ������ ��m=0ʱ ����ǽ
	p = &K2[x][y];                                 //n�������ö�ά���� ʹK����������0 Ĭ��n=0��n=1ʱ����
	if (n == 0) {
		*p = 1 + m;
	}
	else *p = 0;
}
///////////////////////////////////////////////////////////
void gamewindowshake() {                              //������
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
void drawbk() {                                          //��ӡ�߽�
	setfillcolor(BK_COLOR);
	setlinecolor(BK_COLOR);
	fillrectangle(0, 0, PYI_X / 2 + CAMERA_X, HEIGHT + CAMERA_Y);
	fillrectangle((WIDTH - PYI_X / 2) + CAMERA_X, 0 + CAMERA_Y, WIDTH + CAMERA_X, HEIGHT + CAMERA_Y);
	fillrectangle(0 + CAMERA_X, 0 + CAMERA_Y, WIDTH + CAMERA_X, PYI_Y / 2 + CAMERA_Y);
	fillrectangle(0 + CAMERA_X, HEIGHT + CAMERA_Y, WIDTH + CAMERA_X, (HEIGHT - PYI_Y / 2) + CAMERA_Y);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void gamepause() {                                //��Ϸ��ͣ
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(90, 50, _T("Consolas"));
	RECT r = { 0, 0, WIDTH ,HEIGHT };
	drawtext(_T("Pause!"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(15, 16, _T("Consolas"));
	drawroundrect(WIDTH + 8, 20, 60, 35, 3, 10, jp_COLOR1, jp_COLOR2);               //Esc
	RECT a1 = { WIDTH + 15,20,WIDTH + 60,60 };
	drawtext(_T("Esc"), &a1, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 260, 30, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //��
	RECT a3 = { WIDTH + 272,30,WIDTH + 300,70 };
	drawtext(_T("W"), &a3, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 260, 80, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //��
	RECT a4 = { WIDTH + 272,80,WIDTH + 300,120 };
	drawtext(_T("S"), &a4, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 210, 80, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //��
	RECT a5 = { WIDTH + 222,80,WIDTH + 250,120 };
	drawtext(_T("A"), &a5, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 310, 80, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //��
	RECT a6 = { WIDTH + 322,80,WIDTH + 350,120 };
	drawtext(_T("D"), &a6, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	drawroundrect(WIDTH + 10, 150, 200, 30, 3, 10, jp_COLOR1, jp_COLOR2);             //�ո�
	drawroundrect(WIDTH + 90, 20, 40, 40, 3, 10, jp_COLOR1, jp_COLOR2);             //�浵B
	RECT a2 = { WIDTH + 100,20,WIDTH + 160,60 };
	drawtext(_T("B"), &a2, DT_TOP | DT_VCENTER | DT_SINGLELINE);

	RECT a9 = { WIDTH ,100,P_WIDTH - 10 ,130 };
	drawtext(_T("Esc�浵 B����"), &a9, DT_TOP | DT_VCENTER | DT_SINGLELINE);

	RECT a7 = { WIDTH + 10,180,P_WIDTH ,210 };
	drawtext(_T("WSAD �������ҿ����ƶ�"), &a7, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a8 = { WIDTH + 10,210,P_WIDTH ,240 };
	drawtext(_T("�ո� ��ͣ"), &a8, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a10 = { WIDTH + 10,240,P_WIDTH ,270 };
	drawtext(_T("�ȿո���ͣ ���ܴ����"), &a10, DT_TOP | DT_VCENTER | DT_SINGLELINE);

	settextcolor(BK_COLOR4);

	RECT a11 = { WIDTH + 40,280,P_WIDTH ,310 };
	drawtext(_T("ͻϮ�� �˺�50"), &a11, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a12 = { WIDTH + 40,310,P_WIDTH ,350 };
	drawtext(_T("С�� �˺�10"), &a12, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a13 = { WIDTH + 40,315,P_WIDTH ,405 };
	drawtext(_T("Կ�� ���ź� key-1"), &a13, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a14 = { WIDTH + 40,340,P_WIDTH ,440 };
	drawtext(_T("��Ҷ �����ָ� HP+50"), &a14, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a15 = { WIDTH + 40,382,P_WIDTH ,462 };
	drawtext(_T("¥�� ǰ������¥��"), &a15, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a16 = { WIDTH + 40,414,P_WIDTH ,497 };
	drawtext(_T("<--��ס ������"), &a16, DT_TOP | DT_VCENTER | DT_SINGLELINE);
	RECT a17 = { WIDTH + 40,500,P_WIDTH ,550 };
	drawpixal(68, 18, BIG_COLOR, 0, 1);
	drawcircle(68, 20, SMALL_COLOR, 0, 1);
	keyshape(68, 22, KEY_COLOR, 0, 1);
	drawpie(68, 24, BLOOD_COLOR, 0, 1);
	buildstair(68, 26, STAIR_COLOR, 3);
	drawpixal(68, 28, HERO_COLOR, 0, 1);

	FlushBatchDraw();			//�������������Ļ
	while (1) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 32) {
				break;
			}
			else if (ch == 98) {
				read();
				drawtext(_T("�����ɹ�"), &a17, DT_TOP | DT_VCENTER | DT_SINGLELINE);
			}
			else if (ch == 27) {
				remove("test.txt");
				drawtext(_T("�浵�ɹ�"), &a17, DT_TOP | DT_VCENTER | DT_SINGLELINE);
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
		FlushBatchDraw();			//�������������Ļ
	}
}
/// //////////////////////////////////////////////////////////////////////////
void draw(int pos, RECT rct, DWORD* pBufImg, DWORD* pBuf) {
	clock_t t = clock();
	float y = (float)pos;	// ��ǰ����������ӳ������Ļ�ϵ�����
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
	// ֡�ʾ���
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

		// ͼƬ���ƫ��
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
		// ���ڿ��
		int nWindowWidth = 1497;
		int nWindowHeight = 720;

		int font_h = 200;					// ���ָ�
		int font_w = 20;					// ���ֿ�
		short nStartLightness = 255;		// ��ʼ����
		short nEndLightness = 60;			// ��������
		float fEndWidthRatio = (float)0.65;	// ������ű���
		float fEndHeightRatio = (float)0.3;	// �߶����ű���

		int fps = 24;		// ֡��
		int nAmount = 2;	// ���ֵ���λ��


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

		// ���ı����ѹ��Ϊ���ڿ��
		float fWindowWidthRatio = (float)nWindowWidth / rct.right;

		BeginBatchDraw();

		clock_t t;

		float f_kLightness = (float)(nStartLightness - nEndLightness) / nWindowHeight;
		float f_kWidth = (1 - fEndWidthRatio) / nWindowHeight;
		float f_kHeight = (1 - fEndHeightRatio) / nWindowHeight;

		// ͼƬ���ƫ��
		for (int pos = nWindowHeight; pos > -rct.bottom; pos -= nAmount)
		{
			t = clock();
			cleardevice();

			float y = (float)pos;	// ��ǰ����������ӳ������Ļ�ϵ�����
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

			// ֡�ʾ���
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
	drawtext(_T("HERO_LEVEL��"), &a1, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("HERO_HP��"), &a2, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("HERO_power��"), &a3, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("HERO_skill��"), &a31, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("HERO_key��"), &a4, DT_TOP | DT_SINGLELINE | DT_LEFT);
	drawtext(_T("<<���ո���鿴����>>"), &a5, DT_TOP | DT_SINGLELINE | DT_CENTER);

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
	drawtext(_T("�����ָ�"), &b1, DT_TOP | DT_SINGLELINE | DT_LEFT);
	RECT b2 = { WIDTH + 6 * WEN_DISTANT,10 + 8 * WEN_DISTANT,WIDTH + 3 + 9 * WEN_DISTANT,10 + 10 * WEN_DISTANT };
	drawtext(_T("����ǹ"), &b2, DT_TOP | DT_SINGLELINE | DT_LEFT);
	RECT b3 = { WIDTH + 1 * WEN_DISTANT,10 + 10 * WEN_DISTANT,WIDTH + 3 + 4 * WEN_DISTANT,10 + 12 * WEN_DISTANT };
	drawtext(_T("��Խ����"), &b3, DT_TOP | DT_SINGLELINE | DT_LEFT);
	RECT b4 = { WIDTH + 6 * WEN_DISTANT,10 + 10 * WEN_DISTANT,WIDTH + 3 + 9 * WEN_DISTANT,10 + 12 * WEN_DISTANT };
	drawtext(_T("�����˺�"), &b4, DT_TOP | DT_SINGLELINE | DT_LEFT);

	setfillcolor(TEXT_COLOR);
	fillrectangle(WIDTH + 3, 8 + WEN_DISTANT, P_WIDTH - 10, 32 + WEN_DISTANT);                            //LEVEL������
	fillrectangle(WIDTH + 3, 8 + 3 * WEN_DISTANT, P_WIDTH - 10, 32 + 3 * WEN_DISTANT);                    //HP������
	fillrectangle(WIDTH + 3, 8 + 5 * WEN_DISTANT, P_WIDTH - 10, 32 + 5 * WEN_DISTANT);                    //power������
	//	fillrectangle(WIDTH + 4, HEIGHT - 8 - 9 * WEN_DISTANT, P_WIDTH - 10, HEIGHT - 8);                  //ԭ�׿�

	setfillcolor(BLACK);
	fillrectangle(WIDTH + 3 + WEN_P, 8 + WEN_DISTANT + WEN_P, P_WIDTH - 10 - WEN_P, 32 + WEN_DISTANT - WEN_P);             //LEVEL��������ɫ����
	fillrectangle(WIDTH + 3 + WEN_P, 8 + 3 * WEN_DISTANT + WEN_P, P_WIDTH - 10 - WEN_P, 32 + 3 * WEN_DISTANT - WEN_P);           //HP��������ɫ����
	fillrectangle(WIDTH + 3 + WEN_P, 8 + 5 * WEN_DISTANT + WEN_P, P_WIDTH - 10 - WEN_P, 32 + 5 * WEN_DISTANT - WEN_P);           //power��������ɫ����
	//	fillrectangle(WIDTH + 4 + WEN_P, HEIGHT - 8 - 9 * WEN_DISTANT + WEN_P, P_WIDTH - 10 - WEN_P, HEIGHT - 8 - WEN_P);       //ԭ�׿��ɫ����
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
void drawpixal(int x, int y, COLORREF COLOR, float xy, int s) {             //���Ʒ���
	float xy2 = xy / 2;
	setfillcolor(COLOR);
	setlinecolor(COLOR);
	if (s)
		fillrectangle(x * BLOCK_XY + x * BLOCK_JJ + xy2 + py_x + CAMERA_X,
			y * BLOCK_XY + y * BLOCK_JJ + xy2 + py_y + CAMERA_Y,
			BLOCK_XY + x * BLOCK_XY + x * BLOCK_JJ - xy2 + py_x + CAMERA_X,
			BLOCK_XY + y * BLOCK_XY + y * BLOCK_JJ - xy2 + py_y + CAMERA_Y);
}

void drawcircle(int x, int y, COLORREF COLOR, float xy, int s) {      //����Բ
	float xy2 = xy / 2;
	setfillcolor(COLOR);
	setlinecolor(COLOR);
	if (s)
		fillcircle(x * (BLOCK_XY + BLOCK_JJ) + xy2 + py_x + CAMERA_X + BLOCK_XY / 2,
			y * (BLOCK_XY + BLOCK_JJ) + xy2 + py_y + CAMERA_Y + BLOCK_XY / 2, 4);
}

void drawpie(int x, int y, COLORREF COLOR, float xy, int s) {                        //������
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
	if (i == 6) drawtext(_T("�ո�"), &a, DT_TOP | DT_LEFT);
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
	int x[20] = { 19,43,58,2,23,52,14,38,43,59, 8,28,43,43,54,23,23,58, 2,23 };                                            //�ŵĵ�ͼ����x��y
	int y[20] = { 2, 2, 2,8, 7, 8,19,19,17,19,23,23,23,38,38,16,22,23,28,34 };
	int xx[20] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };                                 //�ŵĿ������  1δ���� 0�ѿ���
	int sxzy[20] = { 1,1,1,0,0,0,0,0,1,0,1,1,1,1,1,0,0,1,0,0 };                               //�ŵķ�����̬ 1�����£�0������
}DOOR;

struct dooropen {                                                              //�Źر�ʱ ������
	int n[20] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };            //ÿ����������Ҫ�ƶ��ľ���
	int ting[20] = { 0 };                                                       //���ting=0 ��������һֱ������
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

void initdooropen(int i) {   //���������ӵ�n
	for (int n = 0; n < 20; n++)
		DOOROPEN[i].n[n] = n + 1;
}

void kdoor(int x, int y, int sxzy) {                                                             //ǰ����k���� ������¼������2   ������k���� ������¼�����ศ��ǽ������1
	if (sxzy) k(x, y, 1, 0), k(x, y + 1, 1, 0),
		k(x, y - 1, 0, 0), k(x, y + 2, 0, 0),
		k(x - 1, y - 1, 0, 0), k(x - 1, y + 2, 0, 0),
		k(x + 1, y - 1, 0, 0), k(x + 1, y + 2, 0, 0);
	else k(x, y, 1, 0), k(x + 1, y, 1, 0),
		k(x - 1, y, 0, 0), k(x + 2, y, 0, 0),
		k(x - 1, y - 1, 0, 0), k(x + 2, y - 1, 0, 0),
		k(x - 1, y + 1, 0, 0), k(x + 2, y + 1, 0, 0);
}

void initdoor() {                         //�������궨λ��K������
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

void antidoor(int x, int y) {                                        //���������x��y  ����Ӧ��ά�������ŵ�����2����Ϊ0
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

void eachdoor(int x, int y, COLORREF COLOR, COLORREF COLOR1, int p, int sxzy, int n) {          //���Ƶ�����  xΪ������X yΪ������Y pΪ�����ŵĿ�϶  nΪ����ʱ�ź��˵�Ƶ��

	int ax = py_x + CAMERA_X;
	int ay = py_y + CAMERA_Y;
	int Band = BLOCK_XY + BLOCK_JJ;
	int a1 = 1, a2 = 1, b1 = 1, b2 = 1;
	if (sxzy == 1) { a1 = 0; b2 = 0; }
	else { a2 = 0; b1 = 0; }

	int s = 0;
	setfillcolor(COLOR);
	setlinecolor(COLOR);
	fillrectangle(x * Band + ax + b1 * p + n * b2,     //��С���񳤶�+�����*x �ټ�ȥ�����ŵĿ�϶p     
		y * Band + ay + b2 * p + n * b1,
		BLOCK_XY - 14 * b2 + x * Band + ax - b1 * p + n * b2,
		BLOCK_XY - 14 * b1 + y * Band + ay - b2 * p + n * b1);
	setfillcolor(COLOR1);
	setlinecolor(COLOR1);
	fillrectangle(x * Band + ax + b1 * (p + 2) + n * b2,     //��С���񳤶�+�����*x �ټ�ȥ�����ŵĿ�϶p     
		y * Band + ay + b2 * (p + 2) + n * b1,
		BLOCK_XY - 14 * b2 + x * Band + ax - b1 * (p + 2) + n * b2,
		BLOCK_XY - 14 * b1 + y * Band + ay - b2 * (p + 2) + n * b1);
}

void drawdoor() {
	for (int i = 0; i < 20; i++) {
		if (DOOR.xx[i] == 1)
			for (int n = 1; n < 30; n++) {                                       //ѭ����ӡ���е���
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
void buildwall(int x, int y, COLORREF COLOR, int p) {                     //���쵥��ǽ
	int py_x = PYI_X / 2;
	int py_y = PYI_Y / 2;
	setfillcolor(COLOR);
	setlinecolor(COLOR);
	fillrectangle(x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X + p,     //��С���񳤶�+�����*x �ټ�ȥǽ�ڼ�Ŀ�϶p
		y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y + p,
		BLOCK_XY + x * BLOCK_XY + x * BLOCK_JJ + py_x + CAMERA_X - p,
		BLOCK_XY + y * BLOCK_XY + y * BLOCK_JJ + py_y + CAMERA_Y - p);
}


void initwall(int a, int b) {                                                     //��ӡ��ͼ��ש��

	for (int i = 0; i < BLOCK_WIDTH; i++) 	k(i, 0, 0, 0);
	for (int i = 0; i < BLOCK_WIDTH; i++) 	k(i, BLOCK_HEIGHT - 1, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	k(0, i, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	k(BLOCK_WIDTH - 1, i, 0, 0);
	///////////////////////////�����Ǵ󷽿�///////////////
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 3)
		for (int j = 1; j < BLOCK_HEIGHT; j += 3) 	k(i, j, 0, 0);

	for (int i = 1; i < BLOCK_WIDTH - 1; i += 5)
		for (int j = 1; j < BLOCK_HEIGHT; j += 5) {
			k(i, j, 0, 0);          //8���������  ��b
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
	//�ڵ�ͼ�ϴ�ӡ��ש�����
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 7)
		for (int j = 1; j < BLOCK_HEIGHT; j += 7) 	k(i, j, 0, 0);

	for (int i = 1; i < BLOCK_WIDTH - 1; i += 4)
		for (int j = 1; j < BLOCK_HEIGHT; j += 4) {
			k(i, j, 0, 0);                  //�ĸ�����㷽�� ��a
			switch (a) {
			case 0: k(i + 1, j, 0, 0); break;
			case 1: k(i - 1, j, 0, 0); break;
			case 2:k(i, j + 1, 0, 0); break;
			case 3:k(i, j - 1, 0, 0);
			}
		}
	for (int n = 0; n < 20; n++) kdoor(DOOR.x[n], DOOR.y[n], DOOR.sxzy[n]);

}
void drawwall() {                                                     //��ӡ��ͼ��ש��
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
void initwallx(int c, int d, int e) {                                                     //��ӡ��ͼ��ש��

	for (int i = 0; i < BLOCK_WIDTH; i++) 	kx(i, 0, 0, 0);
	for (int i = 0; i < BLOCK_WIDTH; i++) 	kx(i, BLOCK_HEIGHT - 1, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	kx(0, i, 0, 0);
	for (int i = 0; i < BLOCK_HEIGHT; i++) 	kx(BLOCK_WIDTH - 1, i, 0, 0);
	///////////////////////////�����Ǵ󷽿�///////////////
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 3)
		for (int j = 1; j < BLOCK_HEIGHT; j += 3) {
			k(i, j, 0, 0);
			switch (d) {                                    //8���������  ��b	
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
	//�ڵ�ͼ�ϴ�ӡ��ש�����
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 7)
		for (int j = 1; j < BLOCK_HEIGHT; j += 7) 	kx(i, j, 0, 0);

	for (int i = 1; i < BLOCK_WIDTH - 1; i += 4)
		for (int j = 1; j < BLOCK_HEIGHT; j += 4) {
			kx(i, j, 0, 0);                  //�ĸ�����㷽�� ��a
			switch (c) {
			case 0: kx(i + 1, j, 0, 0); break;
			case 1: kx(i - 1, j, 0, 0); break;
			case 2:kx(i, j + 1, 0, 0); break;
			case 3:kx(i, j - 1, 0, 0);
			}
		}
	for (int i = 1; i < BLOCK_WIDTH - 1; i += 4)
		for (int j = 1; j < BLOCK_HEIGHT; j += 4) {
			kx(i + 1, j - 2, 0, 0);                  //�ĸ�����㷽�� ��a
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
void drawwallx() {                                                     //��ӡ��ͼ��ש��
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
	///////////////////////////�����Ǵ󷽿�///////////////
}
void drawwallx1() {                                                     //��ӡ��ͼ��ש��
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
	float x = 0, y = 0;                        //����λ��
	int sjx[6] = { -3, -3, 3, -3, -3, 3 };     //���������ε�����������ʽ
	float dx = 0, dy = 0;                              //�����ٶ�
	float jd = 0;                              //���ӽǶ�
	float djd = 0;                             //������ת�Ľ��ٶ�
	COLORREF RGB;                              //������ɫ
}Lizi[LIZINUM];

void initlizi(int x, int y) {   //x,yΪҪ��ʾ��λ��
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

void randomway(int i, int x) {                  //big����ǽ���赲��ı��˶�����
	//iΪBIG���  xΪ��ͬ��ͼ��big��  0Ϊ��  1Ϊ��
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
	int* p = &K[0][0], n = 0, m = 0;                                       //big�Զ���������ʧ��  �ݻ��ƻ�
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

void initbigmove(int x) {  /////////��xΪ0 ����������   xΪ1ʱ ��������
	int t1 = 0;
	t1 == GetTickCount();		//��ȡ���Կ���ʱ��
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
			if (K[BIG[i].x + BIG[i].dy][BIG[i].y + BIG[i].dx] != 1 || K[BIG[i].x + BIG[i].dy][BIG[i].y + BIG[i].dx] != 2 && K[BIG[i].x][BIG[i].y] != 1 || K[BIG[i].x][BIG[i].y] != 2) {                 //big����
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
		else if (HERO.x == x && HERO.y == y && z == 3) {                  //�ŵĶ�ά��������antidoor����������ɣ��˴������д
			HERO.x = (HERO.x - HERO.dx);                                  //����ʱ��Կ���ж��ѷ����ں���move���������ڣ��˴������д
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
			case 1:	BIG[i].s = 0; break;                //z=1 ����big�Ĵ���                          
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
			case 1:	BIGX[i].s = 0; break;                //z=1 ����big�Ĵ���                          
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
		case 112:heroskill(); break;      //p��
		case 109:HERO.map = 1; break;      //m��
		case 110:HERO.map = 0; break;      //n��
		case 72:HERO.j--; break;     //������
		case 80:HERO.j++; break;     //������
		case 75:HERO.i--; break;     //������
		case 77:HERO.i++; break;     //������
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
		if (K[HERO.x][HERO.y] == 2) {                        //ǰ��heroreact����������Կ�׿���ϵͳ���õ��˴�
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
void read() {                           //��ȡ�浵
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
	srand((unsigned)time(NULL));	//���������
	initgraph(P_WIDTH, P_HEIGHT);		//������ͼ����
	BeginBatchDraw();				//��ʼ������ͼ
	DWORD t1, t2;
	t1 = t2 = GetTickCount();		//��ȡ���Կ���ʱ��
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

		if (t2 - t1 > GAMETIME) {         //ʹ��Ϸ�Ƕ�����ʱ

			initbigmove(0);
			initbigmove(1);
			heromove();
			t1 = t2;
		}
		information();
		informationupdate();
		drawbk();

		FlushBatchDraw();         //�������������Ļ;
		t2 = GetTickCount();
		gameend2();
	}
}