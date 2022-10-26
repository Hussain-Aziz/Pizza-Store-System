#pragma once
#include "Account.h"
class Customer: public Account
{
private:
	string fname, lname, phone, address, email;
	int orderId;
public:
	Customer();
	Customer(string accountid, string storeId, string username, string password, string fname, string lname, string phone, string address, string email, int orderId);

	Customer* duplicate()override;
	void print() override;
	void readFromFile(ifstream& ifile)override;
	void saveToFile(ofstream& ofile)override;
	void displayMenu()override;
	void askForDetails(bool askForStore = true) override;

	void setFname(string nfname);
	void setLname(string nlname);
	void setPhone(string nphone);
	void setAddress(string naddress);
	void setEmail(string nemail);
	void setOrderId(int id);
};


