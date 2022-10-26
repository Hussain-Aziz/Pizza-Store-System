#ifndef ADMIN
#define ADMIN
#include "Account.h"

class Admin : public Account
{
public:
	Admin();
	Admin(string accountid, string username, string password);
	virtual ~Admin(){}
	void displayMenu() override;
	Account* duplicate() override;
	void saveToFile(ofstream& ofile)override;
};
#endif
