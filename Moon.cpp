#include <iostream>
#include "Date/DateTime.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct row {
	Datetime data;
	double El;
};

void make_hms(Datetime& _date, char(&_HMS)[7]) {
	_date.hour = (_HMS[0] - 48) * 10 + (_HMS[1] - 48);
	_date.minute = (_HMS[2] - 48) * 10 + (_HMS[3] - 48);
	_date.second = (_HMS[4] - 48) * 10 + (_HMS[5] - 48);
}

row make_row(istringstream& isstr, string& current_date) {
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

	char curr_date[9];
	string curre_date;

	row last_row;
	row my_row;


	bool is_found_date = false;
	double max_El = -9999;
	Datetime date;

	file.getline(line, 100);
	file.getline(line, 100);

	cout << "Дата: " << full_date << endl;

	istringstream iss(line);
	iss >> curr_date;
	curre_date = curr_date;
	last_row = make_row(iss, curre_date);

	while (true) {
		file.getline(line, 100);
		istringstream iss(line);
		iss >> curr_date;
		curre_date = curr_date;
		if (!is_found_date and ((10 * (curr_date[4] - 48) + (curr_date[5] - 48)) != full_date.month or
			(10 * (curr_date[6] - 48) + (curr_date[7] - 48)) != full_date.day)) {
			continue;
		}
		try {
			my_row = make_row(iss, curre_date);
		}
		catch (...) {
			break;
		}
		is_found_date = true;


		if (last_row.El < 0 and my_row.El >= 0) {
			cout << "Восход луны:" << my_row.data << endl;
		}
		else if (last_row.El > 0 and my_row.El <= 0) {
			cout << "Заход луны:" << my_row.data << endl;
		}
		if (max_El < my_row.El) {
			date = my_row.data;
			max_El = my_row.El;
		}
		last_row = my_row;

		if (is_found_date and ((10 * (curr_date[6] - 48) + (curr_date[7] - 48)) != full_date.day or
			(10 * (curr_date[4] - 48) + (curr_date[5] - 48)) != full_date.month)) {
			break;
		}
	}
	cout << "Кульминация Луны: " << date;
	file.close();

}
int main() {
	setlocale(LC_ALL, "ru-RU");
	string path = "Moon/moon";

	Datetime full_date(9, 3, 2023);
	//try {
	//	cin >> full_date; // day-month-year
	//}
	//catch (const string& ex) {
	//	cerr << ex;
	//}

	path += to_string(full_date.year) + ".dat";

	calculate(path, full_date);
}