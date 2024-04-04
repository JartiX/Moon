#include <iostream>
#include "Date/DateTime.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;



//void make_date(Datetime& _date, char(&_HMS)[7], char(&current_date)[9]) {
//	try {
//		_date.hour = (_HMS[0] - 48) * 10 + (_HMS[1] - 48);
//		_date.minute = (_HMS[2] - 48) * 10 + (_HMS[3] - 48);
//		_date.second = (_HMS[4] - 48) * 10 + (_HMS[5] - 48);
//		_date.year = 1000 * (current_date[0] - 48) + 100 * (current_date[1] - 48) + 10 * (current_date[2] - 48) + (current_date[3] - 48);
//		_date.day = 10 * (current_date[6] - 48) + (current_date[7] - 48);
//		_date.month = 10 * (current_date[4] - 48) + (current_date[5] - 48);
//	}
//	catch (...) {
//		return;
//	}
//}

//void make_row(istringstream& isstr, char(&current_date)[9], row& result) {
//	char HMS[7];
//	result.data = Datetime();
//	isstr >> HMS >> result.El >> result.El >> result.El;
//
//	make_date(result.data, HMS, current_date);
//}

void calculate(string path, Datetime full_date) {
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "Ошибка при чтении файла";
	}

	char line[100];

	char curr_date[9];
	char HMS[7];

	double last_El;
	double El;


	bool is_found_date = false;
	double max_El = -9999;
	Datetime answer_date;
	answer_date = Datetime();
	Datetime date;

	file.getline(line, 100);
	file.getline(line, 100);

	cout << "Дата: " << full_date << endl;

	istringstream iss(line);
	iss >> HMS >> HMS >> last_El >> last_El >> last_El;

	while (true) {
		file.getline(line, 100);
		istringstream iss(line);
		iss >> curr_date;
		if (!is_found_date and ((10 * (curr_date[4] - 48) + (curr_date[5] - 48)) != full_date.month or
			(10 * (curr_date[6] - 48) + (curr_date[7] - 48)) != full_date.day)) {
			continue;
		}
		iss >> HMS >> El >> El >> El;

		is_found_date = true;


		if (last_El < 0 and El >= 0) {
			answer_date.hour = (HMS[0] - 48) * 10 + (HMS[1] - 48);
			answer_date.minute = (HMS[2] - 48) * 10 + (HMS[3] - 48);
			answer_date.second = (HMS[4] - 48) * 10 + (HMS[5] - 48);
			answer_date.year = 1000 * (curr_date[0] - 48) + 100 * (curr_date[1] - 48) + 10 * (curr_date[2] - 48) + (curr_date[3] - 48);
			answer_date.day = 10 * (curr_date[6] - 48) + (curr_date[7] - 48);
			answer_date.month = 10 * (curr_date[4] - 48) + (curr_date[5] - 48);
			cout << "Восход луны:" << answer_date << endl;
		}
		else if (last_El > 0 and El <= 0) {
			answer_date.hour = (HMS[0] - 48) * 10 + (HMS[1] - 48);
			answer_date.minute = (HMS[2] - 48) * 10 + (HMS[3] - 48);
			answer_date.second = (HMS[4] - 48) * 10 + (HMS[5] - 48);
			answer_date.year = 1000 * (curr_date[0] - 48) + 100 * (curr_date[1] - 48) + 10 * (curr_date[2] - 48) + (curr_date[3] - 48);
			answer_date.day = 10 * (curr_date[6] - 48) + (curr_date[7] - 48);
			answer_date.month = 10 * (curr_date[4] - 48) + (curr_date[5] - 48);
			cout << "Заход луны:" << answer_date << endl;
		}
		if (max_El < El) {
			date.hour = (HMS[0] - 48) * 10 + (HMS[1] - 48);
			date.minute = (HMS[2] - 48) * 10 + (HMS[3] - 48);
			date.second = (HMS[4] - 48) * 10 + (HMS[5] - 48);
			date.year = 1000 * (curr_date[0] - 48) + 100 * (curr_date[1] - 48) + 10 * (curr_date[2] - 48) + (curr_date[3] - 48);
			date.day = 10 * (curr_date[6] - 48) + (curr_date[7] - 48);
			date.month = 10 * (curr_date[4] - 48) + (curr_date[5] - 48);
			max_El = El;
		}
		last_El = El;
		if (curr_date[0] == '\0' or (is_found_date and ((10 * (curr_date[6] - 48) + (curr_date[7] - 48)) != full_date.day or
			(10 * (curr_date[4] - 48) + (curr_date[5] - 48)) != full_date.month))) {
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