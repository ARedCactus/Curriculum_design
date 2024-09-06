#pragma once
#include "Menu.h"

struct slide_BOX
{
	COLORREF frame_color;
	int Left;
	int Top;
	int Right;
	int Bottom;
	int box_width;
};
class Windows
{
private:
	int slide_num = 15;
	int slide_interval = 10;
	slide_BOX box = { RGB(10,10,10), 100,100,1300,795,100 };

	Slide* slide[15];    //数组大小与slide_num一致
	Student* student;
	Menu* menu;
	Edit* edit;
	size_t edit_input_maxlength = 200;
	LPCTSTR Text;
	Data data;
	bool Text_switch = false;    //edit是否按下enter
	bool up_switch = false;
	bool down_switch = true;

	const string File_name = "data.txt";

protected:
	void slide_init();
	void all_slide_data_init(bool init_or_clear,int max_data_num);
	void draw_all_slide(bool real_change);
	void Student_init();
	void Menu_init();
	void Edit_init();
	bool If_In_slide_box(ExMessage msg);
	void message_renew();
	void edit_data_to_data();
	void get_text_inform(const wchar_t* S_num, const wchar_t* S_name, const wchar_t* S_class);
	void search_wchar_to_Data_vector(int wchar_num);
	void search_score_to_Data_vector(int score_num);
public:
	enum class window_object
	{
		Main,Add_Data,development_log
	};

	Windows();
	~Windows();
	void draw_all(window_object object, bool real_change);

	void all_slide_wheel(ExMessage msg, int max_data_num);
	void message();

	void out_x_y(const ExMessage& msg);

	void draw_slide_box(bool real_change);

private:
	window_object object;
	//Main控制
	bool former_menu;
	bool after_menu;
	bool change;
	bool edit_binput;
	bool search_function;
	//Add_Data控制
	bool If_redraw_edit = true;

	vector<Data> search_data_storage;
};
