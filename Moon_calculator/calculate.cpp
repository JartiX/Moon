#include <iostream>
#include "calculate.h"
#include <fstream>
#include <sstream>
using namespace std;


void calculate(string& path, Datetime& full_date) {
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "Ошибка при чтении файла";
	}

	char line[100];

	char curr_date[9];
	char HMS[7];

	double last_El;
	double El;
	double max_El = -9999;



	Datetime answer_date;
	answer_date = Datetime();
	Datetime date;

	file.getline(line, 100);
	file.getline(line, 100);

	cout << "Дата: " << full_date << endl;

	while (true) {
		file.getline(line, 100);
		istringstream iss(line);
		iss >> curr_date;
		if ((10 * (curr_date[4] - 48) + (curr_date[5] - 48)) != full_date.month or
			(10 * (curr_date[6] - 48) + (curr_date[7] - 48)) != full_date.day) {
			continue;
		}
		iss >> HMS >> last_El >> last_El >> last_El;
		break;
	}
	while (true) {
		file.getline(line, 100);
		istringstream isss(line);
		isss >> curr_date >> HMS >> El >> El >> El;

		if (last_El < 0 and El >= 0) {
			make_date(answer_date, HMS, curr_date);
			cout << "Восход луны:" << answer_date << endl;
		}
		else if (last_El > 0 and El <= 0) {
			make_date(answer_date, HMS, curr_date);
			cout << "Заход луны:" << answer_date << endl;
		}
		if (max_El < El) {
			make_date(date, HMS, curr_date);
			max_El = El;
		}
		last_El = El;
		if (curr_date[0] == '\0' or ((10 * (curr_date[6] - 48) + (curr_date[7] - 48)) != full_date.day or
			(10 * (curr_date[4] - 48) + (curr_date[5] - 48)) != full_date.month)) {
			break;
		}
	}
	cout << "Кульминация Луны: " << date;
	file.close();
}