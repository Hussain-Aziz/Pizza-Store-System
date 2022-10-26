#ifndef MANAGER
#define MANAGER
#include"Account.h"
class Manager :public Account
{
public:
	Manager();
	Manager(string accountid, string storeId, string username, string password);

	void displayMenu() override;
	Account* duplicate() override;
	void saveToFile(ofstream& ofile) override;
};
#endif