#include "Window.h"

void Windows::slide_init()
{
	LPCTSTR s[15] = { _T("1"),_T("2") ,_T("3") ,_T("4") ,_T("5"),_T("6"),_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14") ,_T("15"), };
	LPCTSTR s_x[15] = { _T(""),_T("") ,_T("") ,_T("") ,_T(""),_T(""),_T(""),_T(""),_T(""),_T(""), _T(""),_T("") ,_T("") ,_T("") ,_T(""), };
//	LPCTSTR s = _T("-----�� �� �� �� �� �� ��------");
//	TCHAR s[] = _T("-----�� �� �� �� �� �� ��------");
	for (int Index = 0; Index < slide_num; Index++)
	{
		slide[Index] = new Slide(Index, slide_interval, s_x[Index], box.Top, box.Bottom, slide_num);
	}
}

void Windows::all_slide_data_init(bool init_or_clear,int max_data_num)
{
	if (init_or_clear)
	{
		if (max_data_num <= 15)
		{
			for (int Index = 0; Index < max_data_num; Index++)
			{
				slide[Index]->revise_data(student->get_Data(Index));
			}
		}
		else if (max_data_num > 15)
		{
			for (int Index = 0; Index < 15; Index++)
			{
				slide[Index]->revise_data(student->get_Data(Index));
			}
		}
	}
	else
	{
		Data data_clear = { L"",L"", L"", 0,0,0,0,0 };
		for (int Index = 0; Index < 15; Index++)
		{
			slide[Index]->revise_data(data_clear);
		}
	}
}


void Windows::draw_all_slide(bool real_change)
{
	if (real_change)
	{
		for (int Index = 0; Index < slide_num; Index++)
		{
			slide[Index]->slide_emergency();
			if (Index == slide_num - 1) slide[0]->slide_emergency();   //�޸���ӡȱʧ
		}
	}
}

void Windows::Student_init()
{
	student = new Student;
	if (!student->read(File_name))
	{
		student->read_buliding(File_name);
		cout << "Դ�ļ������ڣ����ؽ����ļ�" << endl;
	}
	else
	{
		student->read(File_name);
		cout << "��ȡ�ɹ�";
	}
}

void Windows::Menu_init()
{
	menu = new Menu;
}

void Windows::Edit_init()
{
	edit = new Edit(400, 50, 1000, 80, edit_input_maxlength, RGB(100, 100, 100), RGB(200, 200, 200));
}

bool Windows::If_In_slide_box(ExMessage msg)
{
	return(msg.x > box.Left && msg.x<box.Right && msg.y>box.Top && msg.y < box.Bottom);
}

void Windows::message_renew()
{
	former_menu = true;
	after_menu = false;
	change = true;
	edit_binput = true;
	If_redraw_edit = true;
	menu->former_menu();      //ÿ�������Ļ�� �����´�ӡһ��menu
}

void Windows::edit_data_to_data()
{
	get_text_inform(menu->S_num->return_Text(), menu->S_name->return_Text(), menu->S_class->return_Text());
	data.score.English = _wtoi(menu->score_English->return_Text());
	data.score.Physics = _wtoi(menu->score_Physics->return_Text());
	data.score.Math = _wtoi(menu->score_Math->return_Text());
	data.score.C = _wtoi(menu->score_C->return_Text());
	data.score.none = _wtoi(menu->score_none->return_Text());
}

void Windows::get_text_inform(const wchar_t* S_num, const wchar_t* S_name, const wchar_t* S_class)
{
	wcscpy_s(data.S_num, S_num);
	wcscpy_s(data.S_name, S_name);
	wcscpy_s(data.S_class, S_class);
}

void Windows::search_wchar_to_Data_vector(int wchar_num)
{
	int Index;
	for (Index = 0; Index < wchar_num; Index++)
	{
		search_data_storage.push_back(student->get_Data(student->get_wchar_int(Index)));
		cout << student->get_wchar_int(Index) << endl;
	}
}

void Windows::search_score_to_Data_vector(int score_num)
{
	int Index;
	for (Index = 0; Index < score_num; Index++)
	{
		search_data_storage.push_back(student->get_Data(student->get_score_int(Index)));
	}
}

Windows::Windows()
{
	slide_init();
	Student_init();
	Menu_init();
	Edit_init();
}

Windows::~Windows()
{
	delete[] slide;
	delete student;
	delete menu;
	delete edit;
}

void Windows::draw_all(window_object object, bool real_change)
{
	if (object == window_object::Main)
	{
		draw_all_slide(real_change);
		draw_slide_box(real_change);
		edit->draw_frame();
	}
	else if (object == window_object::Add_Data)
	{

	}
	else if (object == window_object::development_log)
	{

	}
}

void Windows::all_slide_wheel(ExMessage msg, int max_data_num)
{
	if (msg.message == WM_MOUSEWHEEL && msg.wheel == 120)
	{
		up_switch = true;
		for (int Index = 0; Index < slide_num; Index++)
		{
			if (Index == 14) cout << slide[Index]->text_index << endl;

			if (Index + slide[Index]->text_index < max_data_num)
			{
				slide[Index]->revise_data(student->get_Data(Index + slide[Index]->text_index));
			}
			else down_switch = false;

//			slide[Index]->slide_wheel_down(up_switch, Index, max_data_num);
			slide[Index]->slide_wheel(msg, Index, max_data_num);
			if (Index == slide_num - 1) slide[0]->slide_emergency();   //�޸���ӡȱʧ
		}
	}
	else if (msg.message == WM_MOUSEWHEEL && msg.wheel == -120)
	{
		down_switch = true;
		for (int Index = slide_num - 1; Index >= 0; Index--)
		{ 
			if (Index == 14) cout << slide[Index]->text_index << endl;

			if (Index + slide[Index]->text_index < max_data_num)
			{
				slide[Index]->revise_data(student->get_Data(Index + slide[Index]->text_index));
			}
			else up_switch = true;

//			slide[Index]->slide_wheel_up(down_switch, Index, max_data_num);
			slide[Index]->slide_wheel(msg, Index, max_data_num);
			if (Index == 0) slide[slide_num - 1]->slide_emergency(); //�޸���ӡȱʧ
		}
	}
}

void Windows::message()
{
	ExMessage msg;
	object = window_object::Main;
	int max_data_num = student->get_Data_size();
	all_slide_data_init(true,max_data_num);
	//Add_Data
	message_renew();
	while (1)
	{
	Begin_Point:
		msg = getmessage();

		if (object == window_object::Main)
		{
			if (If_In_slide_box(msg) && msg.message == WM_MOUSEWHEEL)
			{
				max_data_num = student->get_Data_size();
				setbkmode(TRANSPARENT);
				all_slide_wheel(msg, max_data_num);
				change = true;
			}
			/////////////////////////////////////////////////////////
			if (former_menu && menu->former_If_In(msg))
			{
				former_menu = false;
				after_menu = true;
				menu->after_menu();
				change = true;
			}
			if (after_menu == true)
			{

				if (menu->Home->If_In(msg))
				{
					if (menu->Home->If_button_click(msg))
					{
						settextcolor(BLUE);
//						outtextxy(100, 100, student->get_Data(0).S_num);
					}
				}
				else if (menu->Back->If_In(msg))
				{
					if (menu->Back->If_button_click(msg))
					{

					}
				}
				else if (menu->Search->If_In(msg))
				{
					if (menu->Search->If_button_click(msg))
					{
						wchar_t* search_text = edit->return_Text();
						unsigned short number = _wtoi(search_text);
	
							student->search_wchar_t(search_text);
							cout << "wchar_t size : " << student->get_wchar_size() << endl;
							cout << "score size : " << student->get_score_size() << endl;

							if (student->search_score(number)) cout << "search score success";
							else cout << "search score faile";

							int clear_switch = false;
							if (student->get_wchar_size()>0)
							{
								clear_switch = true;
//								outtextxy(100, 100, student->get_Data(student->get_score_int(0)).S_num);
								search_wchar_to_Data_vector(student->get_wchar_size());
							}
							if (student->get_score_size() > 0)
							{
								clear_switch = true;
//								search_score_to_Data_vector(student->get_score_size());
							}
							all_slide_data_init(false, max_data_num);
					}
				}
				else if (menu->Add_Data->If_In(msg))
				{
					if (menu->Add_Data->If_button_click(msg))
					{
						object = window_object::Add_Data;
						cleardevice();
						message_renew();
						goto Begin_Point;
					}
				}
				else if (menu->Refresh->If_In(msg))
				{
					if (menu->Refresh->If_button_click(msg))
					{
						max_data_num = student->get_Data_size();
						cout << "data_num : " << max_data_num;
						all_slide_data_init(true,max_data_num);
					}
				}
				else if (menu->Delete_all->If_In(msg))
				{
					if (menu->Delete_all->If_button_click(msg))
					{
						student->clear_data();
						cout << "��ɾ��ȫ���ļ�����";
					}
				}
			}
			if (after_menu && menu->after_If_In(msg) == false)
			{
				after_menu = false;
				former_menu = true;
				menu->clear_after_button();
				menu->former_menu();
				change = true;
			}
			////////////////////////////////////////////////////////////
			if (msg.message == WM_LBUTTONDOWN && edit->If_In_Edit(msg))
			{
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				edit_binput = true;
				if (edit->OnMessage(msg, edit_binput))
				{
					Text = edit->return_Text();
					outtextxy(500, 500, Text);
					Text_switch = true;
				}
			}
			//		out_x_y(msg);

			if (change)
			{
				draw_all(window_object::Main, !after_menu);
				change = false;
			}

		}

		else if (object == window_object::Add_Data)
		{
			if (If_redraw_edit)
			{
				menu->draw_all_Add_Data_edit();
				If_redraw_edit = false;
			}
			if (former_menu && menu->former_If_In(msg))
			{
				former_menu = false;
				after_menu = true;
				menu->after_menu();
				change = true;
			}
			if (after_menu == true)
			{
				if (menu->Home->If_In(msg))
				{
					if (menu->Home->If_button_click(msg))
					{
						object = window_object::Main;
						cleardevice();
						message_renew();
						goto Begin_Point;
					}
				}
				else if (menu->Back->If_In(msg))
				{
					if (menu->Back->If_button_click(msg))
					{

					}
				}
				else if (menu->Search->If_In(msg))
				{
					if (menu->Search->If_button_click(msg))
					{

					}
				}
				else if (menu->Add_Data->If_In(msg)&&menu->Add_Data->If_button_click(msg))
				{
					if (menu->Add_Data->If_button_click(msg))
					{

					}
				}
				else if (menu->Refresh->If_In(msg))
				{
					if (menu->Refresh->If_button_click(msg))
					{

					}
				}
				else if (menu->Delete_all->If_In(msg))
				{
					if (menu->Delete_all->If_button_click(msg))
					{
						student->clear_data();
						cout << "��ɾ��ȫ���ļ�����";
					}
				}
			}
			if (after_menu && menu->after_If_In(msg) == false)
			{
				after_menu = false;
				former_menu = true;
				menu->clear_after_button();
				menu->draw_all_Add_Data_edit();
				menu->former_menu();
				change = true;
				If_redraw_edit = true;
			}

			if (msg.message == WM_LBUTTONDOWN && menu->S_num->If_In_Edit(msg))
			{
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				edit_binput = true;
				if (menu->S_num->OnMessage(msg, edit_binput))
				{
				}
			}
			else if (msg.message == WM_LBUTTONDOWN && menu->S_name->If_In_Edit(msg))
			{
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				edit_binput = true;
				if (menu->S_name->OnMessage(msg, edit_binput))
				{
				}
			}
			else if (msg.message == WM_LBUTTONDOWN && menu->S_class->If_In_Edit(msg))
			{
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				edit_binput = true;
				if (menu->S_class->OnMessage(msg, edit_binput))
				{
				}
			}
			else if (msg.message == WM_LBUTTONDOWN && menu->score_English->If_In_Edit(msg))
			{
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				edit_binput = true;
				if (menu->score_English->OnMessage(msg, edit_binput))
				{
				}
			}
			else if (msg.message == WM_LBUTTONDOWN && menu->score_Physics->If_In_Edit(msg))
			{
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				edit_binput = true;
				if (menu->score_Physics->OnMessage(msg, edit_binput))
				{
				}
			}
			else if (msg.message == WM_LBUTTONDOWN && menu->score_Math->If_In_Edit(msg))
			{
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				edit_binput = true;
				if (menu->score_Math->OnMessage(msg, edit_binput))
				{
				}
			}
			else if (msg.message == WM_LBUTTONDOWN && menu->score_C->If_In_Edit(msg))
			{
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				edit_binput = true;
				if (menu->score_C->OnMessage(msg, edit_binput))
				{
				}
			}
			else if (msg.message == WM_LBUTTONDOWN && menu->score_none->If_In_Edit(msg))
			{
				settextcolor(BLACK);
				setbkmode(TRANSPARENT);
				edit_binput = true;
				if (menu->score_none->OnMessage(msg, edit_binput))
				{
				}
			}
			else if (menu->Enter->If_In(msg))
			{
				if (menu->Enter->If_button_click(msg))
				{
					edit_data_to_data();
					student->add(data);
					if (student->write(File_name)) cout <<endl<< "д���ļ��ɹ�";
					else cout <<endl<< "д���ļ�ʧ��";
				}
			}

			if (change)
			{
				draw_all(window_object::Add_Data, !after_menu);
				change = false;
			}
		}
		else if (object == window_object::development_log)
		{

		}
	}
}

void Windows::out_x_y(const ExMessage& msg)
{
	cout << msg.x << " " << msg.y << endl;
}

void Windows::draw_slide_box(bool real_change)
{
	if (real_change)
	{
		setlinecolor(box.frame_color);
		setfillcolor(box.frame_color);
		fillrectangle(40, box.Top - box.box_width, box.Right + box.box_width, box.Top);
		fillrectangle(40, box.Bottom-20, box.Right + box.box_width, box.Bottom + box.box_width);
		fillrectangle(40, box.Top, box.Left, box.Bottom);
		fillrectangle(box.Right, box.Top, box.Right + box.box_width, box.Bottom);
	}
	else return;
}
