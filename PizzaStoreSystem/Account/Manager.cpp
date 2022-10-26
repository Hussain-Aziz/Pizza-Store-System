#include"Manager.h"
#include "../Company/Company.h"

Manager::Manager():Account()
{
	currentAccountType = AccountType::Manager;
}

Manager::Manager(string accountid, string storeId, string username, string password) : Account(accountid, storeId, username, password, AccountType::Manager){}

void Manager::displayMenu()
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
		cout << "\n1. View Toppings\n2. Add Toppings\n3. Edit Toppings\n4. Delete Toppings";
		cout << "\n5. View Predefined Pizza\n6. Add Predefined Pizza\n7. Edit Predefined Pizza\n8. Delete Predefined Pizza";
		cout << "\n9. View Non Pizza Item\n10. Add Non Pizza Item\n11. Edit Non Pizza Item\n12. Delete Non Pizza Item";
		cout << "\n13. View Employees\n14. Add Employees\n15. Edit Employees\n16. Delete Employees\n17.LogOut" << endl;


		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			for (size_t i = 0; i < Company::getInstance()->getAllToppings().size(); i++)
			{
				cout << Company::getInstance()->getAllToppings()[i];
			}
		}
		break;
		case 2:
		{
			string name;
			double price;
			cout << "Enter name of topping: ";
			cin >> name;
			cout << "Enter price of topping: ";
			cin >> price;
			string id = Utils::getNewId(Company::getInstance()->getAllToppings(), "T_");
			Toppings newTopping(id, name, price);
			Company::getInstance()->getAllToppings().push_back(newTopping);
		}
		break;
		case 3:
		{
			cout << "Enter Id of topping: ";
			string id;
			cin >> id;
			int index =Utils::searchVector(Company::getInstance()->getAllToppings(), id);
			if (index < 0)
			{
				cout << "Index not found" << endl;
				break;
			}
			else
			{
				string name;
				double price;
				cout << "Enter new name of topping: ";
				cin >> name;
				cout << "Enter new price of topping: ";
				cin >> price;
				Company::getInstance()->getAllToppings()[index].setName(name);
				Company::getInstance()->getAllToppings()[index].setPrice(price);

			}
		}
		break;
		case 4:
		{
			cout << "Enter Id of topping: ";
			string id;
			cin >> id;
			int index = Utils::searchVector(Company::getInstance()->getAllToppings(), id);
			if (index < 0)
			{
				cout << "Index not found" << endl;
				break;
			}
			else
			{
				Company::getInstance()->getAllToppings().erase(Company::getInstance()->getAllToppings().begin() + index);
				cout << "Topping deleted sucessfully " << endl;
			}
		}
		break;
		case 5:
		{
			for (size_t i = 0; i < Company::getInstance()->getAllPizzas().size(); i++)
			{
				Company::getInstance()->getAllPizzas()[i].print();
			}
		}
		break;
		case 6:
		{
			string id = Utils::getNewId(Company::getInstance()->getAllPizzas(), "P_");
			Pizza newPizza(id);
			try
			{
				CreatePizza(newPizza, true);
				Company::getInstance()->getAllPizzas().push_back(newPizza);
			}
			catch (TextToEnumConversionError& e)
			{
				cout << e.what();
			}
		}
		break;
		case 7:
		{
			cout << "Enter Id of the pizza: ";
			string pid;
			cin >> pid;
			int index = Utils::searchVector(Company::getInstance()->getAllPizzas(), pid);
			if (index < 0)
			{
				cout << "Index not found" << endl;
				break;
			}
			else
			{
				try
				{
					CreatePizza(Company::getInstance()->getAllPizzas()[index], true);
				}
				catch (TextToEnumConversionError& e)
				{
					cout << e.what();
				}
			}
		}
		break;
		case 8:
		{
			cout << "Enter Id of the pizza: ";
			string pid;
			cin >> pid;
			int index = Utils::searchVector(Company::getInstance()->getAllPizzas(), pid);
			if (index < 0)
			{
				cout << "Index not found" << endl;
				break;
			}
			else
			{
				Company::getInstance()->getAllPizzas().erase(Company::getInstance()->getAllPizzas().begin() + index);
				cout << "Pizza deleted sucessfully " << endl;
			}
		}
		break;
		case 9:
		{
			for (size_t i = 0; i < Company::getInstance()->getAllNonPizzaItems().size(); i++)
			{
				Company::getInstance()->getAllNonPizzaItems()[i].print();
			}
		}
		break;
		case 10:
		{
			string name;
			double basePrice;
			cout << "Enter name of the Non Pizza Item: ";
			cin >> name;
			cout << "Enter price of Non Pizza Item: ";
			cin >> basePrice;

			string id = Utils::getNewId(Company::getInstance()->getAllNonPizzaItems(), "NP_");
			NonPizzaItem newItem(id, name, basePrice);
			Company::getInstance()->getAllNonPizzaItems().push_back(newItem);
		}
		break;
		case 11:
		{
			cout << "Enter Id of the Non Pizza Item: ";
			string Iid;
			cin >> Iid;
			int index = Utils::searchVector(Company::getInstance()->getAllNonPizzaItems(), Iid);
			if (index < 0)
			{
				cout << "Index not found" << endl;
				break;
			}
			else
			{
				string name;
				double price;
				cout << "Enter name of the Non Pizza Item: ";
				cin >> name;
				cout << "Enter price of Non Pizza Item: ";
				cin >> price;

				Company::getInstance()->getAllNonPizzaItems()[index].setName(name);
				Company::getInstance()->getAllNonPizzaItems()[index].setPrice(price);
			}
		}
		break;
		case 12:
		{
			cout << "Enter Id of the Non Pizza Item: ";
			string Iid;
			cin >> Iid;
			int index = Utils::searchVector(Company::getInstance()->getAllNonPizzaItems(), Iid);
			if (index < 0)
			{
				cout << "Index not found" << endl;
				break;
			}
			else
			{
				Company::getInstance()->getAllNonPizzaItems().erase(Company::getInstance()->getAllNonPizzaItems().begin() + index);
				cout << "Non Pizza Item deleted sucessfully " << endl;
			}
		}
		break;
		case 13:
		{
			for (size_t i = 0; i < store->getStoreStaff().size(); i++)
			{
				store->getStoreStaff()[i]->print();
			}

		}
		break;
		case 14:
		{
			cout << "Enter the type of new employee or customer(DeliveryDriver,Chef,Staff,Customer): " << endl;
			string eType;
			cin >> eType;
			AccountType chosenType;
			try
			{
				chosenType = getAccountTypeFromText(eType);
				if (chosenType == AccountType::Admin) throw InvalidChoice();
				if (chosenType == AccountType::Manager) throw InvalidChoice();
			}
			catch (TextToEnumConversionError& e)
			{
				cout << e.what() << endl;
				break;
			}
			catch (InvalidChoice& e)
			{
				cout << e.what() << endl;
				break;
			}

			Account* newAcc;
			string id;

			switch (chosenType)
			{
			case AccountType::DeliveryDriver:
			{
				newAcc = new DeliveryDriver();
				id = Utils::searchVector(store->getStoreStaff(), "DeliveryDriver_");
			}
			break;
			case AccountType::Chef:
			{
				newAcc = new Chef();
				id = Utils::searchVector(store->getStoreStaff(), "Chef_");
			}
			break;
			case AccountType::Staff:
			{
				newAcc = new Staff();
				id = Utils::searchVector(store->getStoreStaff(), "Staff_");
			}
			break;
			case AccountType::Customer:
			{
				newAcc = new Customer();
				id = Utils::searchVector(store->getStoreStaff(), "Customer_");
			}
			break;
			default:
				newAcc = nullptr;
				id = "";
				break;
			}
			//manager cant make employee not from his own store
			newAcc->askForDetails(false);
			newAcc->setAccountId(id);
			newAcc->setStoreId(storeId);
			store->getStoreStaff().push_back(newAcc);
		}
		break;
		case 15:
		{
			cout << "Enter the Id of the employee or customer: " << endl;
			string Eid;
			cin >> Eid;
			int accountid = Utils::searchVector(store->getStoreStaff(), Eid);
			if (accountid < 0)
			{
				cout << "Id not found" << endl;
				break;
			}
			else
			{
				store->getStoreStaff()[accountid]->askForDetails();
			}
		}
		break;
		case 16:
		{
				cout << "Enter Id of the Employee or customer: ";
				string Accountid;
				cin >> Accountid;
				int Accountindex = Utils::searchVector(store->getStoreStaff(), Accountid);
				if (Accountindex < 0)
				{
					cout << "Id of employee or customer not found" << endl;
					break;
				}
				else
				{
					delete store->getStoreStaff()[Accountindex];
					store->getStoreStaff().erase(store->getStoreStaff().begin() + Accountindex);
					cout << "Employee deleted sucessfully " << endl;
				}
		}
		break;
		case 17:
			break;
		default:
			cout << "Invalid Choice. Please enter another option" << endl;
		}
	} while (choice != 17);
}

Account* Manager::duplicate()
{
	return new Manager(accountid, storeId, username, password);
}

void Manager::saveToFile(ofstream& ofile)
{
	Account::saveToFile(ofile);
	ofile << endl;
}

