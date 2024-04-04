#include <iostream>
#include "Moon_calculator/calculate.h"
#include <fstream>
#include <sstream>
using namespace std;

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