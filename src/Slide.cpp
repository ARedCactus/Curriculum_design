#include "Slide.h"

void Slide::draw_slide_rect(int y)
{
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	setfillcolor(Color);
	setlinecolor(BLACK);
	fillroundrect(X, y, X + Width, y + Height, Round_X, Round_Y);
}

//当yes_no为首次true时，获取矩形区域所在的黑域图，用于擦掉原图。
//当yes_no为false时，擦掉原图
//当yes_no为true时，绘制新图
void Slide::slide_rect_move(int y, bool yes_no) 
{
	static IMAGE img;
//	bool once = true;
	if (yes_no == false)
	{
		putimage(X, y, &img);
	}
	else
	{
		if (once)
		{
//		    getimage(&img, X - 1, y - 1, Width + 1, Height + 1);
			getimage(&img, X - 1, y + 10, Width + 1, Height + 1);
			once = false;
		}
		draw_slide_rect(y);
//		outtextxy(X + 3, y + 3, Text);
		draw_text();
	}
}

//Y+slide_interval超过上界，返回-1
//Y超过下界，返回1
//都未发生，则返回0
int Slide::slide_Y_state()
{
	if (Y > lower_bound) return 1;
	else if (Y + slide_interval < upper_bound) return -1;
	else return 0;
}

void Slide::draw_text()
{
	wchar_t buffer[10];
	RECT S_num = { X,Y,X + 200,Y + Height };
	RECT S_name = { X + 200,Y,X + 400,Y + Height };
	RECT S_class = { X + 400,Y,X + 600,Y + Height };
	drawtext(data.S_num, &S_num, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(data.S_name, &S_name, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(data.S_class, &S_class, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT English = { X + 600,Y,X + 720,Y + Height };
	RECT Physics = { X + 720,Y,X + 840,Y + Height };
	RECT Math = { X + 840,Y,X + 960,Y + Height };
	RECT C = { X + 960,Y,X + 1080,Y + Height };
	RECT none = { X + 1080,Y,X + 1200,Y + Height };
	_itow_s(data.score.English, buffer, 10);
	drawtext(buffer, &English, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	_itow_s(data.score.Physics, buffer, 10);
	drawtext(buffer, &Physics, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	_itow_s(data.score.Math, buffer, 10);
	drawtext(buffer, &Math, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	_itow_s(data.score.C, buffer, 10);
	drawtext(buffer, &C, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	_itow_s(data.score.none, buffer, 10);
	drawtext(buffer, &none, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

Slide::Slide(int index, int slide_interval, LPCTSTR s, int box_top, int box_bottom, int slide_num)
{
	this->slide_interval = slide_interval;
	this->Text = s;
	this->box_top = box_top;
	this->box_bottom = box_bottom;
	this->Y_change_distance = slide_num * (slide_interval + Height);
	this->Y = index * (Height + slide_interval) + box_top;
	this->upper_bound = box_top - (Height + slide_interval);
	this->lower_bound = box_bottom;
	slide_rect_move(Y, true);
}
 
void Slide::slide_wheel(ExMessage msg,int Index,int max_data_num)
{
	if (msg.message == WM_MOUSEWHEEL)
	{
		int each_num = 5;
		switch (msg.wheel)
		{
		case -120:
		{
			while (each_num--)
			{
				slide_rect_move(Y, false);
				Y += 4;
				slide_rect_move(Y, true);
			}
		}break;
		case 120:
		{
			while (each_num--)
			{
				slide_rect_move(Y, false);
				Y -= 4;
			    slide_rect_move(Y, true);
			}
		}break;
		default:break;
		}
		if (slide_Y_state() == 1)
		{
			slide_rect_move(Y, false);
			Y -= Y_change_distance;
			if (Index + text_index - 15 >= 0) text_index -= 15;
			slide_rect_move(Y, true);
		}
		else if (slide_Y_state() == -1)
		{
			slide_rect_move(Y, false);
			Y += Y_change_distance;
			if (Index + text_index + 15 <= max_data_num)  text_index += 15;
			slide_rect_move(Y, true);
		}
	}
}

void Slide::slide_wheel_down(bool down_switch, int Index, int max_data_num)
{
	if (down_switch)
	{
		int each_num = 5;
		while (each_num--)
		{
			slide_rect_move(Y, false);
			Y -= 4;
			slide_rect_move(Y, true);
		}
		if (slide_Y_state() == 1)
		{
			slide_rect_move(Y, false);
			Y -= Y_change_distance;
			if (Index + text_index - 15 >= 0) text_index -= 15;
			slide_rect_move(Y, true);
		}
	}
}

void Slide::slide_wheel_up(bool up_switch,int Index, int max_data_num)
{
	if (up_switch)
	{
		int each_num = 5;
		while (each_num--)
		{
			slide_rect_move(Y, false);
			Y += 4;
			slide_rect_move(Y, true);
		}
		if (slide_Y_state() == -1)
		{
			slide_rect_move(Y, false);
			Y += Y_change_distance;
			if (Index + text_index + 15 <= max_data_num)  text_index += 15;
			slide_rect_move(Y, true);
		}
	}
}

//2023.6.2 debug 失败  上滑时1号slide打印缺失  下滑时最末尾slide打印缺失
//设立 emergency 作为补丁
void Slide::slide_emergency()
{
	draw_slide_rect(Y);
	outtextxy(X + 3, Y + 3, Text);
	draw_text();
}

void Slide::revise_data(Data data)
{
	this->data = data;
}