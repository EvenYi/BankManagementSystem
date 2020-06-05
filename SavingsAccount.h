#pragma once
#include "Date.h"
#include "Account.h"
#include "Accumulator.h"
#include<iostream>
using namespace std;

// Class SavingAccount public inherit from Account.
class SavingsAccount : public Account
{
public:
	SavingsAccount(Date date, string id, double rate);
	double getRate()const { return rate; };
	void deposit(const Date& date, double amount, string desc = "-");
	void withdraw(const Date& date, double amount, string desc = "-");
	void settle(const Date& date);
private:
	Accumulator acc;
	double rate;
};
