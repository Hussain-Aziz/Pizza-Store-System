#include "Company/Company.h"
using namespace std;

int main()
{
	cout << "Starting..." << endl;
	Company* PizzaCompany = Company::getInstance();

	cout << "Welcome to PizzaCompany!!" << endl;
	cout << "Is this your first time here? (y/n)" << endl;
	string firstTimeInput;
	cin >> firstTimeInput;

	Account* CurrentUser = nullptr;

	if (firstTimeInput == "y")
	{
		//if its a new user then it has to be a customer
		CurrentUser = new Customer();

		cout << "Please choose the store nearest to you: " << endl;
		for (int i = 0; i < Company::getInstance()->getAllStores().size(); i++)
		{
			cout << i << ". " << Company::getInstance()->getAllStores()[i].getName() << endl;
		}
		int storeChoice;
		cin >> storeChoice;

		if (storeChoice < 0 || storeChoice > Company::getInstance()->getAllStores().size() - 1)
		{
			cout << "Invalid choice" << endl;
			return -1;
		}

		cout << "Please enter additional details to help us identify you later" << endl;
		CurrentUser->setStoreId(Company::getInstance()->getAllStores()[storeChoice].getId());
		CurrentUser->setAccountId(Utils::getNewId(Company::getInstance()->getAllStores()[storeChoice].getStoreStaff(), "Customer_"));
		static_cast<Customer*>(CurrentUser)->askForDetails(false);
		Company::getInstance()->getAllStores()[storeChoice].getStoreStaff().push_back(CurrentUser);
	}
	else
	{
		string username, password;
		cout << "Please enter your username: ";
		cin >> username;
		cout << "Please enter your password: ";
		cin >> password;

		AccountLogin accountLogin{ username, password };
		bool found = false;
		
		//search Admins
		for (int i = 0; i < Company::getInstance()->getAllAdmins().size() && !found; i++)
		{
			if (Company::getInstance()->getAllAdmins()[i] == accountLogin)
			{
				CurrentUser = &Company::getInstance()->getAllAdmins()[i];
				found = true;
			}
		}
		//search Managers
		for (int i = 0; i < Company::getInstance()->getAllManagers().size() && !found; i++)
		{
			if (Company::getInstance()->getAllManagers()[i] == accountLogin)
			{
				CurrentUser = &Company::getInstance()->getAllManagers()[i];
				found = true;
			}
		}
		//search others
		for (int i = 0; i < Company::getInstance()->getAllStores().size() && !found; i++)
		{
			for (int j = 0; j < Company::getInstance()->getAllStores()[i].getStoreStaff().size() && !found; j++)
			{
				if (Company::getInstance()->getAllStores()[i].getStoreStaff()[j] == accountLogin)
				{
					CurrentUser = Company::getInstance()->getAllStores()[i].getStoreStaff()[j];
					found = true;
				}
			}
		}
		if (!found)
		{
			CurrentUser = nullptr;
			cout << "Username and password did not match." << endl;
			return -1;
		}
	}

	CurrentUser->displayMenu();
	PizzaCompany->Save();
	cout << "Bye have a great day!!" << endl;

	return 0;
}