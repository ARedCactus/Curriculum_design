#pragma once
#include "Student.h"

class Button
{
private:
	COLORREF line_color;
	COLORREF button_color_A;
	COLORREF button_color_B;
	int X, Y;
	int Width, Height;
	wstring Text;
	bool color_change = false;
protected:

public:
	Button(int x, int y, int width, int height, wstring text);
	void draw_button();
	bool If_In(ExMessage& msg);
	bool If_button_click(ExMessage& msg);
};

class former_Button
{
public:
	COLORREF button_color_A;
	COLORREF button_color_B;
	int X, Y;
	int Width;
	int	Height;
    IMAGE Mask;
	IMAGE Origin;
public:
	former_Button(int x, int y, int width, int height, LPCTSTR mask, LPCTSTR origin);
	void draw_former_butter();
};