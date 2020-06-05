#pragma once
#include <iostream>
#include <vector>
#include "Account.h"
#include "Date.h"

// Class controller is used to manage and execute command from use input.
// Function runCommand which used to execute the command and report whether current input command need to record in file.
// When varible end is not true, measn the use not exit system.
using namespace std;
class Controller
{
public:
	Controller(const Date& date) :date(date), end(false) {}
	~Controller();
	const Date getDate() const { return date; }
	bool isEnd() const { return end; }
	bool runCommand(const string& cmdLine);

private:
	Date date;
	vector<Account*>accounts;
	bool end;
};

