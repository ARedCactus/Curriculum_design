#include "Student.h"

void Student::read_buliding(const string& File)
{
	ofstream ofs;
	ofs.open(File, ios::app );  // ios::binary
	ofs.close();
}

bool Student::read(const string& File)
{
	ifstream is(File, ios::in );
	if (!is) return false;

	Data data = {};
	while (is.read((char*)&data, sizeof(Data)))
	{
	Data_vector.push_back(data);
	}
	is.close();

	return true;
}

bool Student::write(const string& File)
{
	ofstream os(File, ios::out);
	if (os)
	{
		int count = Data_vector.size();
		for (int k = 0; k < count; k++)
		{
			os.write((char*)&Data_vector[k], sizeof(Data));
		}
		os.close();
		return true;
	}
	else return false;
}

void Student::add(Data& data)
{
	Data_vector.push_back(data);
}


void Student::delect(int i)
{
	Data_vector.erase(Data_vector.begin() + i);
}

void Student::search_wchar_t(wchar_t* test)
{
	vector<Data>::iterator first_iter = Data_vector.begin();
	vector<Data>::iterator iter = Data_vector.begin();
	int succeed_search = 0;
	while (1)
	{
		iter = find(iter, Data_vector.end(), test);
		wchar_t_Index.push_back((int)(iter - first_iter));
		if (iter != Data_vector.end())
		{
			iter++;
		}
		else break;
	}
}

bool Student::search_score(unsigned short score)
{
	int num = Data_vector.size();
	int succeed_search = 0;
	for (int i = 0; i < num; i++)
	{
		const Data& element = Data_vector[i];
		if (element.score.English == score || element.score.Math == score || element.score.Physics == score || element.score.C == score || element.score.none == score)
		{
			succeed_search++;
			score_Index.push_back(i);
		}
	}
	if (succeed_search == 0) return false;
	else return true;
}

void Student::sort_base(int low, int high, bool (*function)(const Data&, const Data&))
{
	if (low < high) {
		Data pivot = Data_vector[high];
		int i = low - 1;

		for (int j = low; j < high; j++) {
			if (function(Data_vector[j], pivot)) {
				i++;
				std::swap(Data_vector[i], Data_vector[j]);
			}
		}

		std::swap(Data_vector[i + 1], Data_vector[high]);

		int pi = i + 1;

		sort_base(low, pi - 1, function);
		sort_base(pi + 1, high, function);
	}
}

void Student::sort(bool (*function)(const Data&, const Data&))
{
	int n = Data_vector.size();
	sort_base(0, n - 1, function);
}

void Student::clear_data()
{
	Data_vector.clear();
}

const Data& Student::get_Data(int index) const
{
	return Data_vector[index];
}

const int& Student::get_wchar_int(int index) const
{
	return wchar_t_Index[index];
}

const int& Student::get_score_int(int index) const
{
	return score_Index[index];
}

int Student::get_Data_size() const
{
	return Data_vector.size();
}

int Student::get_wchar_size() const
{
	return wchar_t_Index.size();
}

int Student::get_score_size()const
{
	return score_Index.size();
}