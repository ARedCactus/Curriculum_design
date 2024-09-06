#include "Button.h"

Button::Button(int x, int y, int width, int height, wstring text)
{
	this->X = x;
	this->Y = y;
	this->Width = width;
	this->Height = height;
	this->Text = text;
	this->line_color = RGB(100, 100, 100);
	this->button_color_A = RGB(220, 220, 220);
	this->button_color_B = RGB(150, 150, 150);
}

void Button::draw_button()
{
	setlinecolor(line_color);
	setlinestyle(PS_SOLID, 2);

	if (color_change) setfillcolor(button_color_A);
	else setfillcolor(button_color_B);

	fillrectangle(X, Y, X + Width, Y + Height);
	RECT rect = { X, Y, X + Width, Y + Height };
	drawtext(Text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

bool Button::If_In(ExMessage& msg)
{
	if (msg.x >= this->X && msg.x <= this->X + Width && msg.y >= this->Y && msg.y <= this->Y + Height)
	{
		color_change = true;
		draw_button();
		return true;
	}
	else
	{
		color_change = false;
		draw_button();
		return false;
	}
}

bool Button::If_button_click(ExMessage& msg)
{
	if (msg.message == WM_LBUTTONDOWN )
	{
		return true;
	}
	else return false;
}

former_Button::former_Button(int x, int y, int width, int height, LPCTSTR mask, LPCTSTR origin)
{
	this->X = x;
	this->Y = y;
	this->Width = width;
	this->Height = height;
	this->button_color_A = RGB(220, 220, 220);
	this->button_color_B = RGB(150, 150, 150);

	loadimage(&Mask, mask, 30, 30);
	loadimage(&Origin, origin, 30, 30);
}


void former_Button::draw_former_butter()
{
	setfillcolor(button_color_B);
	fillrectangle(X, Y, X + Width, Y + Height);
	putimage(1, 1, &Mask, PATPAINT);
	putimage(1, 1, &Origin, SRCAND); 
}
