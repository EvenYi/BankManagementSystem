#include "CreditAccount.h"
#include "Account.h"
#include "Date.h"
#include <iostream>
#include <istream>
using namespace std;
CreditAccount::CreditAccount(Date date, string id, double credit, double rate, double fee) :Account(id), acc(Accumulator(date, 0)), credit(credit), rate(rate), fee(fee) {
}
void CreditAccount::deposit(const Date& date, double amount, string desc) {
	acc.change(date, Account::getBalance());
	record(date, amount, desc);
	date.show();
}
void CreditAccount::withdraw(const Date& date, double amount, string desc) {
	if (amount - getBalance() > credit) {
		cout << "[INFO]: No enough credit." << endl;
	}
	else
	{
		acc.change(date, Account::getBalance());
		record(date, -amount, desc);
	}

	date.show();
}
// Compute the interest, If current month is Jan, then add annual fee.
void CreditAccount::settle(const Date& date) {
	double interest = 0;
	acc.change(date, Account::getBalance());
	interest = acc.getSum(date) * this->rate;
	if (interest != 0) {
		record(date, interest, "Compute interest");
	}
	if (date.getMonth() == 1) {
		record(date, -fee, "Annual fee");
	}
	acc.reset(date, getDebt());
}
void CreditAccount::show(ostream &out)const {
	Account::show(out);
	cout << "[INFO] AvailableCredit:" << getAvailableCredit() << endl;
}