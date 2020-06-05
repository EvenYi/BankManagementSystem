#include "Date.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// DAYS_BEFORE_MONTH is an array to record the total days before current month in current year.
namespace {
	const int DAYS_BEFORE_MONTH[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
}

// In Date object, we not only store the year, month, day but also store the total days from 1-1-1 to current day.
// Total days let us compute interets easily. When we want to compute the total days between two dates.
// We just need to use the totalday varible of late date minus the varible of previous date. 
Date::Date(int year, int month, int day) :year(year), month(month), day(day) {
	int amountday;
	if (day <= 0 || day > getMaxDay())
	{
		throw runtime_error("[ERROR]: Invalid date.");
	}
	if (isLeapYear() && month > 2) // If current month is later than Feb and current year is leap year, then we need add addtional 1 day into total days.
	{							   // Since the DAYS_BEFORE_MONTH array is not leap year.
		day += 1;
	}

	// Compute the total from 1-1-1 to current date YYYY-MM-DD
	totalday = 365 * (year - 1) + floor((year - 1) / 4) - floor((year - 1) / 100) + floor((year - 1) / 400) + DAYS_BEFORE_MONTH[month] + day;
}
// Get total days before current month in current year.
int Date::getMaxDay() const {
	return DAYS_BEFORE_MONTH[month];
};
bool Date::isLeapYear() const {
	if (0 == year % 4)
	{
		if (0 == year % 100)
		{
			if (0 == year % 400)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;

		}
	}
	else
	{
		return false;
	}
};
void Date::show() const {
	cout << year << "-" << month << "-" << day << "     ";
};
int Date::operator - (const Date& date) const {
	return this->totalday - date.totalday;
};

istream& operator >> (istream& in, Date& date) {
	int year, month, day;
	char c1, c2;
	in >> year >> c1 >> month >> c2 >> day;
	if (c1 != '-' || c2 != '-')
	{
		throw runtime_error("[ERROR]: Wrong date format.");
	}
	date = Date(year, month, day);
	return in;
}
ostream& operator << (ostream& out, const Date& date) {
	out << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
	return out;
}