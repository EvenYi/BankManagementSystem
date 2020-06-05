#include "Accumulator.h"
#include "Date.h"
#include <iostream>
using namespace std;

// lastDate is used to record the time of last transation.
// sum is used to store previous accumulated amount.
Accumulator::Accumulator(Date date, double value) : lastDate(date), sum(value) {
}


// When new transaction take effect, we nee to call change funtion
// to calculate accumulated amount which is equal to the balance
// between last transaction and current transaction multiply total of days 
// between last transaction and current transaction
void Accumulator::change(Date date, const double value) {

	sum += value * (date - lastDate);
	lastDate = date;
	return;
}
// Reset the accumulated amount and the time of last transaction.
void Accumulator::reset(Date date, double value) {

	sum = value;
	lastDate = date;
	return;

}