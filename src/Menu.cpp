#include "Menu.h"

void Menu::button_init()
{
	Home = new Button(5, 55, 140, 40, L"Home");
	Back = new Button(5, 105, 140, 40, L"Back");
	Search = new Button(5, 155, 140, 40, L"Search");
	Add_Data = new Button(5, 205, 140, 40, L"Add_Data");
	Refresh = new Button(5, 255, 140, 40, L"Refresh");
	Delete_all = new Button(5, 305, 140, 40, L"Delete_all");
	Add_Data_edit_init(500, 30);
}

void Menu::former_bttton_init()
{
	former_Home = new former_Button(5, 55, former_width - 10, 40, _T("IMAGE/hao/1m.png"), _T("IMAGE/origin/1o.png"));
	former_Back = new former_Button(5, 105, former_width - 10, 40, _T("IMAGE/hao/2m.png"), _T("IMAGE/origin/2o.png"));
	former_Search = new former_Button(5, 155, former_width - 10, 40, _T("IMAGE/hao/3m.png"), _T("IMAGE/origin/3o.png"));
	former_Add_Data = new former_Button(5, 205, former_width - 10, 40, _T("IMAGE/hao/4m.png"), _T("IMAGE/origin/4o.png"));
	former_Refresh = new former_Button(5, 255, former_width - 10, 40, _T("IMAGE/hao/5m.png"), _T("IMAGE/origin/5o.png"));
	former_Delete_all = new former_Button(5, 305, former_width - 10, 40, _T("IMAGE/hao/6m.png"), _T("IMAGE/origin/6o.png"));
}

Menu::Menu()
{
	button_init();
	former_bttton_init();
}

Menu::~Menu()
{
	delete Home;
	delete former_Home;
	delete Back;
	delete former_Back;
	delete Search;
	delete former_Search;
	delete Add_Data;
	delete former_Add_Data;
	delete Refresh;
	delete former_Refresh;
	delete Delete_all;
	delete former_Delete_all;
	Add_Data_edit_delete();
}

bool Menu::former_If_In(const ExMessage& msg) const
{
	if (msg.x <= former_width)return true;
	else return false;
}

bool Menu::after_If_In(const ExMessage& msg) const
{
	if (msg.x <= after_width)return true;
	else return false;
}

void Menu::former_menu()
{
	setfillcolor(menu_color);
	fillrectangle(0, 0, former_width, height);
	former_button_draw();
}

void Menu::after_menu()
{
	setfillcolor(menu_color);
	fillrectangle(0, 0, after_width, height);
	after_button_draw();
}

void Menu::former_button_draw()
{
	former_Home->draw_former_butter();
	former_Back->draw_former_butter();
	former_Search->draw_former_butter();
	former_Add_Data->draw_former_butter();
	former_Refresh->draw_former_butter();
	former_Delete_all->draw_former_butter();
}

void Menu::after_button_draw()
{
	Home->draw_button();
	Back->draw_button();
	Search->draw_button();
	Add_Data->draw_button();
	Refresh->draw_button();
	Delete_all->draw_button();
}

void Menu::clear_after_button()
{
	clearrectangle(0, 0, after_width, height);
}


void Menu::Add_Data_edit_init(int edit_width, int edit_height)
{
	this->edit_width = edit_width;
	this->edit_height = edit_height;
	S_num = new Edit(250, 10, 5 + edit_width, 10 + edit_height, 20, edit_line_color, edit_fill_color);
	S_name = new Edit(250, 60, 5 + edit_width, 60 + edit_height, 20, edit_line_color, edit_fill_color);
	S_class = new Edit(250, 110, 5 + edit_width, 110 + edit_height, 20, edit_line_color, edit_fill_color);
	score_English = new Edit(250, 160, 5 + edit_width, 160 + edit_height, 20, edit_line_color, edit_fill_color);
	score_Physics = new Edit(250, 210, 5 + edit_width, 210 + edit_height, 20, edit_line_color, edit_fill_color);
	score_Math = new Edit(250, 260, 5 + edit_width, 260 + edit_height, 20, edit_line_color, edit_fill_color);
	score_C = new Edit(250, 310, 5 + edit_width, 310 + edit_height, 20, edit_line_color, edit_fill_color);
	score_none = new Edit(250, 360, 5 + edit_width, 360 + edit_height, 20, edit_line_color, edit_fill_color);
	Enter = new Button(250, 400, 100, 40, L"Enter");
}

void Menu::Add_Data_edit_delete()
{
	delete S_num;
	delete S_name;
	delete S_class;
	delete score_English;
	delete score_Physics;
	delete score_Math;
	delete score_C;
	delete score_none;
	delete Enter;
}


void Menu::draw_all_Add_Data_edit()
{
	S_num->draw_frame();
	S_name->draw_frame();
	S_class->draw_frame();
	score_English->draw_frame();
	score_Physics->draw_frame();
	score_Math->draw_frame();
	score_C->draw_frame();
	score_none->draw_frame();
	Enter->draw_button();
}
