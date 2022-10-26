#pragma once
#include "Account.h"
class Chef :public Account
{
public:
	Chef();
	Chef(string accountid, string storeId, string username, string password);
	void displayMenu();
	Account* duplicate();
	void saveToFile(ofstream& ofile) override;
};

