#pragma once
#include "Date.h"
#include<iostream>
using namespace std;

// Class Accumulator is used to calculate amount between transactions.
// When the transaction, the accumulator will record the time span and balance between last transaction and current transaction.
// Accumulator mainly used to calculate the interest.
class Accumulator
{
public:
	Accumulator(Date date, double value);
	const double getSum(Date date) { return sum; };
	void change(Date date, const double value);
	void reset(Date date, double value);

private:
	Date lastDate;
	double sum;
};




