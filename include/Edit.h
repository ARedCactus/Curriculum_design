#pragma once
#include "HELLO.h"

class Edit
{
private:
	int left, top, right, bottom;
	wchar_t* text;
	size_t MaxLength;
	COLORREF LineColor;
	COLORREF FillColor;

protected:
	void draw_line(int width, bool mode);
	void draw_rect(int width, bool mode);
	void draw_round(int width, bool mode);
public:
	Edit(int left, int top, int right, int bottom,size_t maxlength, COLORREF linecolor, COLORREF fillcolor);
	~Edit();
	wchar_t* return_Text();
	size_t return_size();
	bool If_In_Edit(ExMessage msg);
	void draw_frame();
	bool OnMessage(ExMessage msg, bool& binput);
};
