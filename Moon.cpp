#include <iostream>
#include <vector>
#include <string>
#include "Date/DateTime.h"
#include <fstream>
#include <sstream>
using namespace std;

struct row {
	Datetime data;
	double El;
};

void make_hms(Datetime& _date, char _HMS[7]) {
	_date.hour = (_HMS[0] - 48) * 10 + (_HMS[1] - 48);
	_date.minute = (_HMS[2] - 48) * 10 + (_HMS[3] - 48);
	_date.second = (_HMS[4] - 48) * 10 + (_HMS[5] - 48);
}

row make_row(istringstream& isstr, string current_date) {
	char HMS[7];
	row result;
	result.data = Datetime(current_date);
	isstr >> HMS >> result.El >> result.El >> result.El;

	make_hms(result.data, HMS);
	return result;

}

void calculate(string path, Datetime full_date) {
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "Ошибка при чтении файла";
	}

	char line[100];

	string curr_date;
	row my_row;
	vector<row> vect;
	size_t ptr = 1;

	bool is_found_date = false;
	double max_El = -9999;
	Datetime date;

	file.getline(line, 100);
	file.getline(line, 100);

	cout << "Дата: " << full_date << endl;

	istringstream iss(line);
	iss >> curr_date;
	my_row = make_row(iss, curr_date);
	vect.push_back(my_row);

	while (true) {
		file.getline(line, 100);
		istringstream iss(line);
		iss >> curr_date;
		if (!is_found_date and (stoi(curr_date.substr(4, 2)) != full_date.month or stoi(curr_date.substr(6, 2)) != full_date.day)) {
			continue;
		}
		my_row = make_row(iss, curr_date);
		is_found_date = true;

		vect.push_back(my_row);

		if (vect[ptr - 1].El < 0 and vect[ptr].El >= 0) {
			cout << "Восход луны:" << vect[ptr].data << endl;
		}
		else if (vect[ptr - 1].El > 0 and vect[ptr].El <= 0) {
			cout << "Заход луны:" << vect[ptr].data << endl;
		}
		if (max_El < vect[ptr].El) {
			date = vect[ptr].data;
			max_El = vect[ptr].El;
		}
		ptr++;

		if (is_found_date and (stoi(curr_date.substr(6, 2)) != full_date.day or stoi(curr_date.substr(4, 2)) != full_date.month)) {
			break;
		}
	}
	cout << "Кульминация Луны: " << date;
	file.close();

}
int main() {
	setlocale(LC_ALL, "ru-RU");
	string path = "Moon/moon";

	Datetime full_date(6, 3, 2023);
	//try {
	//	cin >> full_date; // day-month-year
	//}
	//catch (const string& ex) {
	//	cerr << ex;
	//}

	path += to_string(full_date.year) + ".dat";

	calculate(path, full_date);
}