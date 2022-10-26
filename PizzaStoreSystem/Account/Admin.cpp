#include "Admin.h"
#include "../Company/Company.h"

Admin::Admin():Account()
{
	currentAccountType = AccountType::Admin;
}

Admin::Admin(string accountid, string username, string password):Account(accountid, "None", username, password, AccountType::Admin) {}

void Admin::displayMenu()
{
	int choice;
	
	do
	{
		cout << "Please select one of the options below" << endl;
		cout << "1. List Pizza Stores\n2. Create Pizza Store\n3. Edit Pizza Store\n4. Delete Pizza Store" << endl;
		cout << "5. List Managers\n6. Create Manager\n7. Edit Manager\n8. Delete Manager\n9. LogOut" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		//List stores
		case 1:
		{
			for (size_t i = 0; i < Company::getInstance()->getAllStores().size(); i++)
			{
				Company::getInstance()->getAllStores()[i].output();
			}
		}
		break;
		//create pizza store
		case 2:
		{
			string id = Utils::getNewId(Company::getInstance()->getAllStores(), "Store_");
			Store newStore(id);
			cout << "Please specify the store name" << endl;
			string name;
			cin >> name;
			newStore.setName(name);
			cout << "Please specify the Manager Id for the store" << endl;
			string Mid;
			cin >> Mid;

			int index = Utils::searchVector(Company::getInstance()->getAllManagers(), Mid);
			if (index < 0)
			{
				cout << "Manager not found" << endl;
				break;
			}
			newStore.SetManagerId(Mid);
			Company::getInstance()->getAllManagers()[index].setStoreId(id);

			Company::getInstance()->getAllStores().push_back(newStore);
		}
		break;
		//edit pizza store
		case 3:
		{
			cout << "Enter ID of store" << endl;
			string id;
			cin >> id;
			int index = Utils::searchVector(Company::getInstance()->getAllStores(), id);
			if (index < 0)
			{
				cout << "Id not found" << endl;
				break;
			}
			else
			{
				cout << "Please specify the a new store name" << endl;
				string name;
				cin >> name;
				Company::getInstance()->getAllStores()[index].setName(name);
				cout << "Please specify the new Manager Id for the store" << endl;
				string Mid;
				cin >> Mid;
				Company::getInstance()->getAllStores()[index].SetManagerId(Mid);
			}
		}
		//delete store
		case 4:
		{
			cout << "Enter Id of the store you want to delete: ";
			string id;
			cin >> id;
			int index = Utils::searchVector(Company::getInstance()->getAllStores(), id);
			if (index < 0)
			{
				cout << "Id not found" << endl;
				break;
			}
			else
			{
				Company::getInstance()->getAllStores().erase(Company::getInstance()->getAllStores().begin() + index);
				cout << "Store deleted sucessfully" << endl;
			}
		}
		break;
		//print all managers
		case 5:
		{
			for (size_t i = 0; i < Company::getInstance()->getAllManagers().size(); i++)
			{
				Company::getInstance()->getAllManagers()[i].print();
			}
		}
		break;
		//create manager
		case 6:
		{
			Manager newManager;
			newManager.setAccountId(Utils::getNewId(Company::getInstance()->getAllManagers(), "Manager_"));
			newManager.askForDetails();
			Company::getInstance()->getAllManagers().push_back(newManager);

		}
		//edit manager
		case 7:
		{
			cout << "Enter Id of the manager you want to edit: ";
			string id;
			cin >> id;
			int index = Utils::searchVector(Company::getInstance()->getAllManagers(), id);
			if (index < 0)
			{
				cout << "Id not found" << endl;
				break;
			}
			else
			{
				Company::getInstance()->getAllManagers()[index].askForDetails();
			}
		}
		break;
		//delete manager
		case 8:
		{
			cout << "Enter Id of the manager you want to delete: ";
			string id;
			cin >> id;
			int index = Utils::searchVector(Company::getInstance()->getAllManagers(), id);
			if (index < 0)
			{
				cout << "Id not found" << endl;
				break;
			}
			else
			{
				Company::getInstance()->getAllManagers().erase(Company::getInstance()->getAllManagers().begin() + index);
				cout << "Manager deleted sucessfully" << endl;
			}
		}
		break;
		case 9:
			break;
		default:
			cout << "Invalid Choice\n Please try again" << endl;
		}
	} while (choice != 9);
}

Account* Admin::duplicate()
{
	return new Admin(accountid, username, password);
}

void Admin::saveToFile(ofstream& ofile)
{
	Account::saveToFile(ofile);
	ofile << endl;
}
