#include "Edit.h"

//当mode为true，画光标
//当mode为false，擦光标
void Edit::draw_line(int width, bool mode)
{
	if (mode) setlinecolor(LineColor);
	else setlinecolor(FillColor);
	line(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);
}

void Edit::draw_rect(int width, bool mode)
{
	if (mode)
	{
		setlinecolor(LineColor);
		setfillcolor(FillColor);
	}
	else 
	{
		setlinecolor(FillColor);
		setfillcolor(FillColor);
	}
	fillrectangle(left + 10 + width + 1, top + 3, left + 10 + width + 1, bottom - 3);
}

void Edit::draw_round(int width, bool mode)
{
	if (mode)
	{
		setlinecolor(LineColor);
		setfillcolor(FillColor);
	}
	else
	{
		setlinecolor(FillColor);
		setfillcolor(FillColor);
	}
	fillroundrect(left + 10 + width, top + 1, right - 1, bottom - 1, 20, 20);
}

Edit::Edit(int left, int top, int right, int bottom,size_t maxlength, COLORREF linecolor, COLORREF fillcolor)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;

	this->MaxLength = maxlength;
	this->text = new wchar_t[MaxLength];
	text[0] = 0;

	this->LineColor = linecolor;
	this->FillColor = fillcolor;
}

Edit::~Edit()
{
	if (text != NULL)
		delete[] text;
}

wchar_t* Edit::return_Text()
{
	return text;
}

size_t Edit::return_size()
{
	return textwidth(text);
}

bool Edit::If_In_Edit(ExMessage msg)
{
	return (left <= msg.x && msg.x <= right && top <= msg.y && msg.y <= bottom);
}

void Edit::draw_frame()
{
	setlinecolor(LineColor);	
	setfillcolor(FillColor);			
	fillroundrect(left, top, right, bottom,20,20);
	outtextxy(left + 10, top + 5, text);

}

bool Edit::OnMessage(ExMessage msg, bool& binput)
{
	int width = textwidth(text);	// 字符串总宽度
	int counter = 0;				// 光标闪烁计数器
	int edit_width = right - left-20;
	while (binput)
	{
		while (binput && peekmessage(&msg, EX_MOUSE | EX_CHAR, false))	// 获取消息，但不从消息队列拿出
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x < left || msg.x > right || msg.y < top || msg.y > bottom)
				{
					binput = false;
					break;
				}
			}
			else if (msg.message == WM_MOUSEWHEEL)
			{
				binput = false;
				break;
			}
			else if (msg.message == WM_CHAR)
			{
				size_t len = wcslen(text);
				switch (msg.ch)
				{
				case '\b':				// 退格键，删掉一个字符
					if (len > 0)
					{
						text[len - 1] = 0;
						width = textwidth(text);
						counter = 0;
						draw_round(width, false);
					}
					break;
				case '\r':				// 回车键，结束文本输入
				case '\n':
				{
					binput = false;
					return true;
				}
				break;
				default:				// 其它键，接受文本输入
					if (width < edit_width && len < MaxLength - 1)
					{
						text[len++] = msg.ch;
						text[len] = 0;
						draw_rect(width, false);
						width = textwidth(text);	
						counter = 0;
						outtextxy(left + 10, top + 5, text);
					}
				}
			}
			peekmessage(NULL, EX_MOUSE | EX_CHAR); // 从消息队列抛弃刚刚处理过的一个消息
		}
		counter = (counter + 1) % 32;
		if (counter < 16)  draw_line(width, true);			
		else               draw_line(width, false);

		Sleep(20);
	}
	draw_rect(width, true);
	draw_frame();
}

