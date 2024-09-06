#pragma once
#include "Slide.h"
#include <fstream>
using namespace std;


class Student
{
private:
	vector<Data> Data_vector;
	vector<int> wchar_t_Index;
	vector<int> score_Index;

protected:

	static bool S_score_English_low(const Data& a, const Data& b) { return a.score.English > b.score.English; }
	static bool S_score_English_high(const Data& a, const Data& b) { return a.score.English < b.score.English; }
	static bool S_score_Physics_low(const Data& a, const Data& b) { return a.score.Physics > b.score.Physics; }
	static bool S_score_Physics_high(const Data& a, const Data& b) { return a.score.Physics < b.score.Physics; }
	static bool S_score_Math_low(const Data& a, const Data& b) { return a.score.Math > b.score.Math; }
	static bool S_score_Math_high(const Data& a, const Data& b) { return a.score.Math < b.score.Math; }
	static bool S_score_C_low(const Data& a, const Data& b) { return a.score.C > b.score.C; }
	static bool S_score_C_high(const Data& a, const Data& b) { return a.score.C < b.score.C; }
	static bool S_score_none_low(const Data& a, const Data& b) { return a.score.none > b.score.none; }
	static bool S_score_none_high(const Data& a, const Data& b) { return a.score.none < b.score.none; }

	void sort_base(int low, int high, bool (*function)(const Data&, const Data&));

public:
	void read_buliding(const string& File);
	bool read(const string& File);
	bool write(const string& File);
	void add(Data& data);
	void delect(int i); 
	void search_wchar_t(wchar_t* test);
	bool search_score(unsigned short score);
	void sort(bool (*function)(const Data&, const Data&));
	void clear_data();
	//numbers.sort(MyVector::compareByData3);
	const Data& get_Data(int index) const;
	const int& get_wchar_int(int index) const;
	const int& get_score_int(int index) const;
	int get_Data_size() const;
	int get_wchar_size() const;
	int get_score_size()const;
};

