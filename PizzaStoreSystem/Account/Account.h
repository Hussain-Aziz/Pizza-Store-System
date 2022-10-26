#ifndef ACCOUNT
#define ACCOUNT
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

enum class AccountType
{
	Admin,
	Manager,
	DeliveryDriver,
	Chef,
	Staff,
	Customer
};
AccountType getAccountTypeFromText(string account);
string getTextFromAccountType(AccountType account);

struct AccountLogin
{
	string username, password;
};

class Account
{
protected:
	string accountid;
	string username, password;
	AccountType currentAccountType;
	string storeId;

public:
	Account();
	Account(string accountid, string storeId, string username, string password, AccountType currentAccountType);

	//getters
	AccountType getAccountType();
	string getAccountId();
	string getUsername();
	string getPassword();
	string getStoreId();

	//setters
	void setAccountId(string id);
	void setUsername(string username);
	void setPassword(string password);
	void setStoreId(string storeId);
	
	//overloads for comparing acccounts
	bool operator==(const Account& a);
	bool operator==(const string& id);
	bool operator==(const AccountLogin& aL);
	friend bool operator==(const Account* a, string id);
	friend bool operator==(const Account* a, const AccountLogin& aL);
	
	//virtual functions
	virtual void displayMenu() = 0;
	virtual Account* duplicate() = 0;//function to make a new deep copy of a account pointer 
	virtual void print();
	virtual void readFromFile(ifstream& ifile);
	virtual void saveToFile(ofstream& ofile);
	virtual void askForDetails(bool askForStore = true);
};
#endif