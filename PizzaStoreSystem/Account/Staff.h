#pragma once
#include "Account.h"
class Staff: public Account
{
public:
	Staff();
	Staff(string accountid, string storeId, string username, string password);

	void displayMenu();
	Staff* duplicate();
	void saveToFile(ofstream& ofile) override;
};

