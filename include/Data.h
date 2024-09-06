#pragma once
#include <string>

struct SCORE
{
	unsigned short English;
	unsigned short Physics;
	unsigned short Math;
	unsigned short C;
	unsigned short none;
}; 

class Data
{
public:
	wchar_t S_num[20];
	wchar_t S_name[20];
	wchar_t S_class[20];
	SCORE score;

	bool operator==(wchar_t* test)
	{
		return (std::wstring(S_num) == test || std::wstring(S_name) == test || std::wstring(S_class) == test);
	}
};