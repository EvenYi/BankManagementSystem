#include "Controller.h"
#include "CreditAccount.h"
#include "SavingsAccount.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

// Special class struct, struct deleter just overloading the () operator, 
// which let the deleter can be used as function object.
struct deleter
{
	template<class T>void operator () (T* p) { delete p; }

};

// Using the for_each and iterator of the vector container to release the resource.
// The third argument is the function object, this object will handle each elemet we get from the iterator.
Controller::~Controller() {
	for_each(accounts.begin(), accounts.end(), deleter());
}

// According to the user input to execute the command.
// If current command need to be record in file, then the function will return True.
bool Controller::runCommand(const string& cmdLine) {
	istringstream str(cmdLine);
	char cmd, type;
	int index, day;
	double amount, credit, rate, fee;
	string id, desc;
	Account* account;
	Date date1, date2;
	str >> cmd;
	switch (cmd)
	{
	case'a':
		str >> type >> id;
		if (type == 's')
		{
			str >> rate;
			account = new SavingsAccount(date, id, rate);
		}
		else
		{
			str >> credit >> rate >> fee;
			account = new CreditAccount(date, id, credit, rate, fee);
		}
		accounts.push_back(account);
		return true;
	case'd':
		str >> index >> amount;
		getline(str, desc);
		accounts[index]->deposit(date, amount, desc);
		return true;
	case'w':
		str >> index >> amount;
		getline(str, desc);
		accounts[index]->withdraw(date, amount, desc);
		return true;
	case's':
		for (int i = 0; i < accounts.size(); i++) {
			accounts[i]->show(cout);
			cout << endl;
		}
		return false;
	case'c':
		str >> day;
		if (day < date.getDay())
		{
			cout << "[ERROR]: You can not specify a previous day." << endl;
		}
		else if (day > date.getMaxDay())
		{
			cout << "Invalid day" << endl;

		}
		else
		{
			date = Date(date.getYear(), date.getMonth(), day);
		}
		return true;
	case 'n':
		if (date.getMonth() == 12)
		{
			date = Date(date.getYear() + 1, 1, 1);
		}
		else
		{
			date = Date(date.getYear(), date.getMonth() + 1, 1);
		}
		for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter) {
			(*iter)->settle(date);
		}
		return true;
	case 'q':
		str >> date1 >> date2;
		cout << date1 << date2;
		Account::query(date1, date2);
		return false;
	case 'e':
		end = true;
		return false;
	}
	cout << "Invalid command" << cmdLine << endl;
	return false;
}