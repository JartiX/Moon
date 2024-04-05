#include <iostream>
#include "calculate.h"
#include <fstream>
using namespace std;


void calculate(string& path, Datetime& full_date) {
	ifstream file(path);
	if (!file.is_open()) {
		cerr << "������ ��� ������ �����";
	}


	char curr_date[9];
	char HMS[7];

	double last_El;
	double El;
	double max_El = -9999;



	Datetime answer_date;
	answer_date = Datetime();
	Datetime date;

	file.ignore(numeric_limits<streamsize>::max(), '\n');

	cout << "����: " << full_date << endl;

	while (true) {
		file >> curr_date;
		if ((10 * (curr_date[4] - 48) + (curr_date[5] - 48)) != full_date.month or
			(10 * (curr_date[6] - 48) + (curr_date[7] - 48)) != full_date.day) {
			file.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		file >> HMS >> last_El >> last_El >> last_El;
		file.ignore(numeric_limits<streamsize>::max(), '\n');

		break;
	}
	while (true) {
		file >> curr_date >> HMS >> El >> El >> El;
		file.ignore(numeric_limits<streamsize>::max(), '\n');

		if (last_El < 0 and El >= 0) {
			make_date(answer_date, HMS, curr_date);
			cout << "������ ����:" << answer_date << endl;
		}
		else if (last_El > 0 and El <= 0) {
			make_date(answer_date, HMS, curr_date);
			cout << "����� ����:" << answer_date << endl;
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
	cout << "����������� ����: " << date;
	file.close();
}