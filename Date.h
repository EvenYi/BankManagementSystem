#pragma once
#include <iostream>
using namespace std;

// Class Date used to handle format date.
class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1);
	int getYear()const { return year; };
	int getMonth()const { return month; };
	int getDay()const { return day; };
	int getMaxDay()const;
	void show()const;
	int operator - (const Date& date) const;
	bool operator < (const Date& date)const {
		return totalday < date.totalday;
	}


private:
	int year;
	int month;
	int day;
	int totalday;
	bool isLeapYear()const;

};

istream& operator >> (istream& in, Date& date);
ostream& operator << (ostream& out, const Date& date);

