#include <iostream>
#include "DateTime.h"
#include <sstream>
using namespace std;

void make_date(Datetime& _date, char(&_HMS)[7], char(&current_date)[9]) {
	_date.hour = (_HMS[0] - 48) * 10 + (_HMS[1] - 48);
	_date.minute = (_HMS[2] - 48) * 10 + (_HMS[3] - 48);
	_date.second = (_HMS[4] - 48) * 10 + (_HMS[5] - 48);
	_date.year = 1000 * (current_date[0] - 48) + 100 * (current_date[1] - 48) + 10 * (current_date[2] - 48) + (current_date[3] - 48);
	_date.day = 10 * (current_date[6] - 48) + (current_date[7] - 48);
	_date.month = 10 * (current_date[4] - 48) + (current_date[5] - 48);
}

Datetime::Datetime(int _day, int _month, int _year) {
	day = _day;
	month = _month;
	year = _year;
	hour = 0;
	minute = 0;
	second = 0;
	julian_date = Julian_days();
	if (!isDateValid()) {
		throw "Invalid date!";
	}
}
Datetime::Datetime() {
	day = 0;
	month = 0;
	year = 0;
	hour = 0;
	minute = 0;
	second = 0;
	julian_date = 0;
}
Datetime::Datetime(int _day, int _month, int _year, int _hour, int _minute, int _second) {
	day = _day;
	month = _month;
	year = _year;
	hour = _hour;
	minute = _minute;
	second = _second;
	julian_date = Julian_days();
	if (!isDateValid()) {
		throw "Invalid date!";
	}
}

Datetime::Datetime(string date) {
	char delimiter1, delimiter2, delimiter3, delimiter4, delimeter5;
	istringstream iss(date);
	if (date.find('T') != string::npos and date.find('-') != string::npos) {
		iss >> year >> delimiter1 >> month >> delimiter2 >> day >>
			delimiter3 >> hour >> delimiter4 >> minute >> delimeter5 >> second;
		if (delimiter1 != '-' || delimiter2 != '-' || delimiter3 != 'T' || delimiter4 != ':' || delimeter5 != ':') {
			throw "Invalid date";
		}
	} else if (date.find('.') != string::npos) {
		iss >> day >> delimiter1 >> month >> delimiter2 >> year;
		hour = 0, minute = 0, second = 0;
		if (delimiter1 != '.' || delimiter2 != '.') {
			throw "Invalid date";
		}
	}
	else {
		if (date.length() == 8) {
			year = stoi(date.substr(0, 4));
			month = stoi(date.substr(4, 2));
			day = stoi(date.substr(6, 2));
			hour = 0, minute = 0, second = 0;
		}
		else {
			throw "Invalid date";
		}

	}
	if (!isDateValid()) {
		throw "Invalid date!";
	}
}
ostream& operator<<(ostream& out, const Datetime& date) {
	out << date.day << "." << date.month << "." << date.year << " " << date.hour << ":" << date.minute << ":" << date.second;
	return out;
}
istream& operator>>(istream& in, Datetime& date) {
	char delimiter1, delimiter2, delimiter3, delimiter4, delimiter5;
	string input;
	getline(in, input);
	istringstream iss(input);
	if (input.find('T') != string::npos) {
		iss >> date.year >> delimiter1 >> date.month >> delimiter2 >> date.day >>
			delimiter3 >> date.hour >> delimiter4 >> date.minute >> delimiter5 >> date.second;
		if (delimiter1 != '-' || delimiter2 != '-' || delimiter3 != 'T' || delimiter4 != ':' || delimiter5 != ':') {
			in.setstate(ios::failbit);
		}
	} else if (input.find('-') != string::npos) {
		iss >> date.day >> delimiter1 >> date.month >> delimiter2 >> date.year;
		if (delimiter1 != '-' || delimiter2 != '-') {
			in.setstate(ios::failbit);
		}
	}
	else if (input.find(" ") != string::npos) {
		iss >> date.day >> date.month >> date.year;
	}
	else {
		if (input.length() == 8) {
			date.year = stoi(input.substr(0, 4));
			date.month = stoi(input.substr(4, 2));
			date.day = stoi(input.substr(6, 2));
		}
		else {
			in.setstate(ios::failbit);
		}
	}
	if (!date.isDateValid()) {
		throw "Invalid date!";
	}
	return in;
}

int& Datetime::operator -(const Datetime& date) const {
	int diff;
	diff = abs(julian_date - date.julian_date);
	return diff;
}
int& Datetime::operator +(const Datetime& date) const {
	int diff;
	diff = julian_date + date.julian_date;
	return diff;
}

Datetime& Datetime::operator -(const int& _day) const {
	Datetime temp(*this);
	Datetime result;
	temp.julian_date -= _day;
	result = convert_date(temp.julian_date);

	return result;
}

Datetime& Datetime::operator +(const int& _day) const {
	Datetime temp(*this);
	Datetime result;
	temp.julian_date += _day;
	result = convert_date(temp.julian_date);

	return result;
}

bool Datetime::operator <(const Datetime& date) const {
	double j1, j2;
	j1 = date.Julian_days();
	j2 = Julian_days();
	return j2 < j1;
}
bool Datetime::operator >(const Datetime& date) const {
	double j1, j2;
	j1 = date.Julian_days();
	j2 = Julian_days();
	return j2 > j1;
}

bool Datetime::operator <=(const Datetime& date) const {
	return !(*this > date);
}
bool Datetime::operator >=(const Datetime& date) const {
	return !(*this < date);
}

bool Datetime::operator ==(const Datetime& date) const {
	double j1, j2;
	j1 = date.Julian_days();
	j2 = Julian_days();
	return j1 == j2;
}
bool Datetime::operator !=(const Datetime& date) const {
	return !(*this != date);
}

int Datetime::Calculate_day_of_week() const {
	int julian = Julian_days() + 1.5;
	return julian % 7;
}

int Datetime::Calculate_day_of_year() const {
	int k;
	if (check_leap_year()) {
		k = 1;
	} else {
		k = 2;
	}
	int day_num = int((275 * month) / 9) - k * int((month + 9) / 12) + day - 30;
	return day_num;
}

bool Datetime::check_leap_year() const{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return true;
	} return false;
}

Datetime convert_date(double julian) {
	julian += 0.5;
	int z = int(julian);
	double F = julian - int(julian);
	int A;
	int alpha;
	int B;
	int C;
	int D;
	int E;
	Datetime result;
	if (z < 2299161) {
		A = z;
	} else {
		alpha = int((z - 1867216.25) / 36524.25);
		A = z + 1 + alpha - int(alpha / 4);
	}
	B = A + 1524;
	C = int((B - 122.1) / 365.25);
	D = int((365.25) * C);
	E = int((B - D) / 30.6001);
	
	result.day = int(B - D - int(30.6001 * E) + F);
	if (E < 14) {
		result.month = E - 1;
	}
	else if (E == 14 || E == 15){
		result.month = E - 13;
	}
	if (result.month > 2) {
		result.year = C - 4716;
	}
	else if (result.month == 1 || result.month == 2) {
		result.year = E - 4715;
	}
	result.julian_date = result.Julian_days();

	return result;

}


double Datetime::Julian_days() const {
	Datetime temp(*this);
	double days;
	int A = int(temp.year / 100);
	int B = 2 - A + int(A / 4);
	if (temp.month == 1 or temp.month == 2) {
		temp.year = temp.year - 1;
		temp.month = temp.month + 12;
	}
	days = int(365.25 * (temp.year + 4716)) + int(30.6001 * (temp.month + 1)) + temp.day + B - 1524.5;
	return days;
}

bool Datetime::isDateValid() {
	// Проверка года
	if (year < 1900 || year > 9999) {
		return false;
	}
	// Проверка месяца
	if (month < 1 || month > 12) {
		return false;
	}
	// Проверка дня
	if (day < 1) {
		return false;
	}
	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (check_leap_year()) {
		daysInMonth[1] = 29;
	}
	if (day > daysInMonth[month - 1]) {
		return false;
	}

	return true;
}