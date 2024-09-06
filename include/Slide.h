#pragma once
#include "Edit.h"
#include "Data.h"
class Slide
{
private:
	int X=100, Y, Width=1200, Height=40;
	int Round_X=20, Round_Y=20;
	COLORREF Color = RGB(100, 100, 200);
	LPCTSTR Text;
	Data data;

	bool once = true;

	int box_top;
	int box_bottom;
	int slide_interval;
	int Y_change_distance;

	int upper_bound;
	int lower_bound;
protected:
	void draw_slide_rect(int y);
	void slide_rect_move(int y, bool yes_no);
public:
	int text_index = 0;
	int slide_Y_state();
	Slide(int index, int slide_interval, LPCTSTR s, int box_top, int box_bottom, int slide_num);
	void slide_wheel(ExMessage msg, int Index,int max_data_num);
	void slide_wheel_down(bool up_switch,int Index, int max_data_num);
	void slide_wheel_up(bool down_switch,int Index, int max_data_num);
	void slide_emergency();
	void revise_data(Data data);
	void draw_text();
};
