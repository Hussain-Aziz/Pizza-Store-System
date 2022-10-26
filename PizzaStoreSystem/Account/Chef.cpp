#include "Chef.h"
#include "../Company/Company.h"

Chef::Chef():Account()
{
	currentAccountType = AccountType::Chef;
}

Chef::Chef(string accountid, string storeId, string username, string password) :Account(accountid, storeId, username, password, AccountType::Chef){}

void Chef::displayMenu()
{
	int choice;
	int Storeindex = Utils::searchVector(Company::getInstance()->getAllStores(), storeId);
	if (Storeindex < 0)
	{
		cout << "Store index not found" << endl;
		return;
	}
	Store* store = &Company::getInstance()->getAllStores()[Storeindex];
	do
	{
		cout << "Please select one of the options below" << endl;
		cout << "1. View number of queued orders\n2. Start an order\n3. View current orders in kitchen\n4. Mark order as ready\n5. LogOut" << endl;;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			store->displayOrders(OrderProcess::Recieved);
		}
		break;
		case 2:
		{
			cout << "Enter the id of the order to start: ";
			int id;
			cin >> id;
			int Orderindex = Utils::searchVector(store->getCurrentOrders(), id);

			if (Orderindex < 0)
			{
				cout << "Order id not found" << endl;
				break;
			}
			else
			{
				//if order process isnt recieved, we cant start order
				if (store->getCurrentOrders()[Orderindex].getOrderProcess() != OrderProcess::Recieved)
				{
					cout << "Cannot start this order.";
					break;
				}
				else
				{
					store->getCurrentOrders()[Orderindex].setOrderProcess(OrderProcess::InKitchen);
					store->getCurrentOrders()[Orderindex].viewPizzasOrderContents();
				}
			}
		}
		break;
		case 3:
		{
			store->displayOrders(OrderProcess::InKitchen);
		}
		break;
		case 4:
		{
			cout << "Enter the id of the order to mark as done: ";
			int id;
			cin >> id;
			int Oindex = Utils::searchVector(store->getCurrentOrders(), id);

			if (Oindex < 0)
			{
				cout << "Order id not found" << endl;
				break;
			}
			else
			{
				//if order process isnt in kitchen, we cant mark it as done
				if (store->getCurrentOrders()[Oindex].getOrderProcess() != OrderProcess::InKitchen)
				{
					cout << "Cannot mark this order as complete.";
					break;
				}
				else
				{
					store->getCurrentOrders()[Oindex].setOrderProcess(OrderProcess::Prepared);
				}
			}
		}
		break;
		case 5:
			break;
		default:
			cout << "Invalid option please try again" << endl;
			break;
		}
	} while (choice != 5);
}

Account* Chef::duplicate()
{
    return new Chef(accountid, storeId, username, password);
}

void Chef::saveToFile(ofstream& ofile)
{
	Account::saveToFile(ofile);
	ofile << endl;
}
