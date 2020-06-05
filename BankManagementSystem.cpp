// BankManagementSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "SavingsAccount.h"
#include "CreditAccount.h"
#include "Array.h"
#include "Account.h"
#include <string>
#include "Date.h"
#include "Controller.h"
using namespace std;


int main()
{
	Date date(2008, 11, 1);
	Controller controller(date);
	string cmdLine;


	// Read commamds file, execute the command to restore the system state back to the last runtime.
	const char* FILE_NAME = "commands.txt";
	ifstream fileIn(FILE_NAME);
	if (fileIn)
	{
		while (getline(fileIn, cmdLine))
		{
			try
			{
				controller.runCommand(cmdLine);
			}
			catch (const std::exception& e)
			{
				cout << "Bad line in " << FILE_NAME << ":" << cmdLine << endl;
				cout << "[ERROR]:" << e.what() << endl;
			}

		}
		fileIn.close();
	}


	// Get new commands from user input and execute it.
	// Store crucial commands in commands.txt file.
	ofstream fileOut(FILE_NAME, ios_base::app);
	cout << "(a) add account  (d) deposit  (w) withdraw  (s) show  (c) change day  (n) next month  (q) query  (e) exit" << endl;
	while (!controller.isEnd())
	{
		cout << controller.getDate() << "\tTotal: " << Account::getTotal() << "\tcommand>";
		string cmdLine;
		getline(cin, cmdLine);
		try
		{
			if (controller.runCommand(cmdLine)) {
				fileOut << cmdLine << endl;
			}
		}
		catch (const AccountException& e)
		{
			cout << "[ERROR]: " << e.getAccount()->getId() << ".  " << e.what() << endl;

		}
		catch (const std::exception& e)
		{
			cout << "[ERROR]: " << e.what() << endl;

		}


	}
	fileOut.close();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
