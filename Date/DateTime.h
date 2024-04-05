#include <iostream>
using namespace std;

class Datetime {
public:
	int day, month, year, hour, minute, second;
	double julian_date;
	Datetime();
	Datetime(int _day, int _month, int _year);
	Datetime(int _day, int _month, int _year, int _hour, int _minute, int _second);
	Datetime(string date);

	friend ostream& operator<<(ostream& out, const Datetime& date);
	friend istream& operator>>(istream& in, Datetime& date);

	// Вычислить разницу между датами в днях, сложить две даты
	int& operator -(const Datetime& date) const;
	int& operator +(const Datetime& date) const;

	// Добавить / вычесть дни из даты
	Datetime& operator -(const int& _day) const;
	Datetime& operator +(const int& _day) const;

	// Сравнить даты
	bool operator <(const Datetime& date) const;
	bool operator >(const Datetime& date) const;
	bool operator <=(const Datetime& date) const;
	bool operator >=(const Datetime& date) const;
	bool operator ==(const Datetime& date) const;
	bool operator !=(const Datetime& date) const;

	// Вычислить день недели для заданной даты
	int Calculate_day_of_week() const;

	// Вычислить день в году для заданной даты
	int Calculate_day_of_year() const;

	// Проверка года на високосность
	bool check_leap_year() const;

	// Вычисление юлианской даты
	double Julian_days() const;

	// Проверка даты на валидность
	bool isDateValid();
};

void make_date(Datetime& _date, char(&_HMS)[7], char(&current_date)[9]);
// Вычисление календарной даты по юлианской
Datetime convert_date(double julian);