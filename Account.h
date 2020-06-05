#pragma once
#include "Date.h"
#include "Accumulator.h"
#include <iostream>
#include <istream>
#include <map>
#include <stdexcept>
using namespace std;

//Prepost declare of class Account
class Account;

//Class AccountException used to handle the error from the account.
//It store the error information and account information.
class AccountException :public runtime_error {
private:
	const Account* account;
public:
	AccountException(const Account* account, const string& msg) :runtime_error(msg), account(account) {}
	const Account* getAccount() const { return account; }

};


//Class AccountRecord which used to record the transactions of each account.
//Evary object of class AccountRecord store the transaction information of each account.
class AccountRecord {
public:
	AccountRecord(const Date& date, const Account* account, double amount, double balance, const string& desc);
	void show() const;
private:
	Date date;
	const Account* account;
	double amount;
	double balance;
	string desc;


};

//Define a specific type multimap<Date, AccountRecord>RecordMap which used to store relation between date and transactions.
//Each AccountRecord transaction corresponde to the time when the transaction committed.
typedef multimap<Date, AccountRecord>RecordMap;


// Class Account is basis class of class SavingAccount and CreditAccount.
// Class Account define basic attributes that all the different types of accounts must have.
// Also define basic operation for any type accounts.
// Settle function is used to calculate interest.
class Account
{
public:
	string getId()const { return id; };
	double getBalance()const { return balance; };
	virtual void show(ostream& out) const;			//Pure virtual function, different derived class objects call same name function can redirect to their specific implemented function
	static double getTotal() { return total; };
	virtual void deposit(const Date& date, double amount, string desc = "-") = 0;
	virtual void withdraw(const Date& date, double amount, string desc = "-") = 0;
	virtual void settle(const Date& date) = 0;
	static void query(const Date& begin, const Date& end);

protected:
	Account(string id);
	void record(const Date& date, double amount, string desc = "-");
	void error(string msg)const;

private:
	string id;
	double balance;
	static double total;
	static RecordMap recordMap;

};


// Operator overloading for output stream operator <<
inline ostream& operator <<(ostream& out, const Account& account) {
	account.show(out);
	return out;
}
