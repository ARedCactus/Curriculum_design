#pragma once
#include "Button.h"
class Menu
{
private:
	COLORREF menu_color = RGB(200,200,200);
	int former_width=40;
	int after_width=150;
	int each_move;
	int height=800;

private:
	former_Button* former_Home;
	former_Button* former_Back;
	former_Button* former_Search;
	former_Button* former_Add_Data;
	former_Button* former_Refresh;
	former_Button* former_Delete_all;
public:
	Button* Home;
	Button* Back;
	Button* Search;
	Button* Add_Data;
	Button* Refresh;
	Button* Delete_all;

protected:
	void button_init();
	void former_bttton_init();
	void former_button_draw();
	void after_button_draw();
public:
	Menu();
	~Menu();
	bool former_If_In(const ExMessage& msg) const;
	bool after_If_In(const ExMessage& msg) const;
	void former_menu();
	void after_menu();

	void clear_after_button();
public:
	Edit* S_num;
	Edit* S_name;
	Edit* S_class;
	Edit* score_English;
	Edit* score_Physics;
	Edit* score_Math;
	Edit* score_C;
	Edit* score_none;
	Button* Enter;
protected:
	int edit_x, edit_y;
	int edit_width, edit_height;
	COLORREF edit_line_color = RGB(100, 100, 200);
	COLORREF edit_fill_color = RGB(0, 255, 255);
	void Add_Data_edit_init(int edit_width, int edit_height);
	void Add_Data_edit_delete();
public:
	void draw_all_Add_Data_edit();

};