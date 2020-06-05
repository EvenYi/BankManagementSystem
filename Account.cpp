#include "Account.h"
#include "Accumulator.h"
#include<iostream>
using namespace std;


double Account::total = 0; // initialize the static varible total of class Account
RecordMap Account::recordMap; // initialize the statisc varible recordMap of class Account


// According to the span of the input date, query all the records between two date.
void Account::query(const Date& begin, const Date& end) {
	if (begin < end) {
		RecordMap::iterator iter1 = recordMap.lower_bound(begin);		// Get the iterator of multimapl container recordMap
		RecordMap::iterator iter2 = recordMap.upper_bound(end);
		for (RecordMap::iterator iter = iter1; iter != iter2; ++iter) {
			iter->second.show();										// Second means the value(AccountRecord) of the key-value couple in multimap.
		}
	}
}
Account::Account(string id) : id(id) {
	balance = 0;
}
void Account::record(const Date& date, double amount, string desc) {
	amount = floor(amount * 100 + 0.5) / 100; //Keep two decimal places
	balance += amount;
	total += amount;
	cout << desc << amount << endl;
	recordMap.insert(make_pair(date, AccountRecord(date, this, amount, balance, desc))); // Record current transaction, push the key(date)-value(AccountRecord) into the multimap continer recordMap.
	return;

}
void Account::error(string msg)const {
	throw AccountException(this, msg); // Throw error.
}
void Account::show(ostream& out) const {
	out << "[INFO] Id: " << id << "  Balance: " << balance;
}
AccountRecord::AccountRecord(const Date& date, const Account* account, double amount, double balance, const string& desc) :date(date), account(account), amount(amount), balance(balance), desc(desc) {
}
void AccountRecord::show()const {
	cout << date << "\t#" << account->getId() << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}
