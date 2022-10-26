#include "Account.h"
#include "../Company/Company.h"
#include "../Utils.h"

AccountType getAccountTypeFromText(string account)
{
	if (account == "Admin")
		return AccountType::Admin;
	if (account == "Manager")
		return AccountType::Manager;
	if (account == "DeliveryDriver")
		return AccountType::DeliveryDriver;
	if (account == "Chef")
		return AccountType::Chef;
	if (account == "Staff")
		return AccountType::Staff;
	if (account == "Customer")
		return AccountType::Customer;

	throw TextToEnumConversionError();
}

string getTextFromAccountType(AccountType account)
{
	switch (account)
	{
	case AccountType::Admin:
		return "Admin";
	case AccountType::Manager:
		return "Manager";
	case AccountType::DeliveryDriver:
		return "DeliveryDriver";
	case AccountType::Chef:
		return "Chef";
	case AccountType::Staff:
		return "Staff";
	case AccountType::Customer:
		return "Customer";
	default:
		throw EnumNotFound();
	}
}

Account::Account() {}

Account::Account(string accountid, string storeId, string username, string password, AccountType currentAccountType)
{
	this->accountid = accountid;
	this->username = username;
	this->password = password;
	this->currentAccountType = currentAccountType;
	this->storeId = storeId;
}

void Account::print()
{
	int Storeindex = Utils::searchVector(Company::getInstance()->getAllStores(), storeId);
	if (Storeindex < 0)
	{
		cout << "Store index not found" << endl;
		return;
	}
	string name = Company::getInstance()->getAllStores()[Storeindex].getName();
	cout << "Account Type: " << getTextFromAccountType(currentAccountType) << endl;
	cout << "ID: " << accountid << endl;
	cout << "Store: " << name << "("<< storeId << ")" << endl;
}

AccountType Account::getAccountType()
{
	return currentAccountType;
}

string Account::getAccountId()
{
	return accountid;
}

string Account::getUsername()
{
	return username;
}

string Account::getPassword()
{
	return password;
}

string Account::getStoreId()
{
	return storeId;
}

void Account::setAccountId(string id)
{
	accountid = id;
}

void Account::setUsername(string username)
{
	this->username = username;
}

void Account::setPassword(string password)
{
	this->password = password;
}

void Account::setStoreId(string storeId)
{
	this->storeId = storeId;
}

bool operator==(const Account* a, string id)
{
	if (a->accountid == id) return true;
	return false;
}

bool operator==(const Account* a, const AccountLogin& aL)
{
	if (a->username == aL.username && a->password == aL.password) return true;
	return false;
}


bool Account::operator==(const Account& a)
{
	if (username == a.username && password == a.password) return true;
	return false;
}

bool Account::operator==(const string& id)
{
	if (this->accountid == id) return true;
	return false;
}

bool Account::operator==(const AccountLogin& a)
{
	if (username == a.username && password == a.password) return true;
	return false;
}

void Account::readFromFile(ifstream& ifile)
{
	string accountType;
	ifile >> accountid >> storeId >> accountType >> username >> password;
	currentAccountType = getAccountTypeFromText(accountType);
}

void Account::saveToFile(ofstream& ofile)
{
	ofile << accountid << " " << storeId << " " << getTextFromAccountType(currentAccountType) << " " << username << " " << password;
}

void Account::askForDetails(bool askForStore)
{
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;
	if (askForStore)
	{
		cout << "Enter storeId: ";
		cin >> storeId;
	}
}
