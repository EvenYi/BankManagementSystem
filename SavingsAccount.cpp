#include "SavingsAccount.h"
#include "Date.h"
#include "Accumulator.h"
#include<iostream>
using namespace std;
SavingsAccount::SavingsAccount(Date date, string id, double rate) :Account(id), rate(rate), acc(Accumulator(date, 0)) {
	date.show();
	cout << "Create account:" << id << endl;
}
void SavingsAccount::deposit(const Date& date, double amount, string desc) {
	acc.change(date, Account::getBalance());
	record(date, amount, desc);
	date.show();
	cout << Account::getId() << "  Deposit:" << amount << "  Balance:" << Account::getBalance() << "  Description:" << desc << endl;
}
void SavingsAccount::withdraw(const Date& date, double amount, string desc) {
	acc.change(date, Account::getBalance());
	record(date, -amount, desc);
	date.show();
	cout << Account::getId() << "  Withdraw:" << -amount << "  Balance:" << Account::getBalance() << "  Description:" << desc << endl;
}
//compute the rate.
void SavingsAccount::settle(const Date& date) {
	if (date.getMonth() == 1) {
		double interest = 0;
		acc.change(date, Account::getBalance());
		interest = (acc.getSum(date) * this->rate) / (date - Date(date.getYear() - 1, 1, 1));
		if (interest != 0) {
			acc.change(date, Account::getBalance());
			record(date, interest, "Compute interest");
		}
		acc.reset(date, 0);
	}
}