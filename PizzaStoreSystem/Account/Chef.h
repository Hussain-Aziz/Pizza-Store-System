#ifndef CHEF
#define CHEF
#include "Account.h"
class Chef :public Account
{
public:
	Chef();
	Chef(string accountid, string storeId, string username, string password);
	virtual ~Chef(){}
	void displayMenu();
	Account* duplicate();
	void saveToFile(ofstream& ofile) override;
};
#endif