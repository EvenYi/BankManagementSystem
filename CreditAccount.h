#pragma once
#include "Account.h"
#include "Date.h"
#include "Accumulator.h"
#include <iostream>
#include <istream>
using namespace std;

// Class CreditAccount public inherit from Account
class CreditAccount : public Account
{
public:
	CreditAccount(Date date, string id, double credit, double rate, double fee);
	double getCredit()const { return credit; };
	double getRate()const { return rate; };
	double getFee()const { return fee; };
	double getAvailableCredit()const {
		double currentBalance = getBalance();
		if (currentBalance < 0) {
			return currentBalance + credit;
		}
		else
		{
			return credit;

		}
	};
	void deposit(const Date& date, double amount, string desc = "-");
	void withdraw(const Date& date, double amount, string desc = "-");
	void settle(const Date& date);
	void show(ostream &out) const;


private:
	Accumulator acc;
	double credit;
	double rate;
	double fee;

	double getDebt()const {

		double reBalance = Account::getBalance();
		return (reBalance < 0 ? reBalance : 0);
	};

};

