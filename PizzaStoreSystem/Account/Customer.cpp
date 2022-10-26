#include "Customer.h"
#include "../Company/Company.h"

Customer::Customer():Account()
{
	currentAccountType = AccountType::Customer;
	orderId = -1;
}

Customer::Customer(string accountid, string storeId, string username, string password, string fname, string lname, string phone, string address, string email, int orderId): Account(accountid, storeId, username, password, AccountType::Customer)
{
	this->fname = fname;
	this->lname = lname;
	this->phone = phone;
	this->address = address;
	this->email = email;
	this->orderId = orderId;
}

Customer* Customer::duplicate()
{
	return new Customer(accountid, storeId, username, password, fname, lname, phone, address, email, orderId);
}

void Customer::print()
{
	Account::print();
	cout << "Name: " << fname << " " << lname << endl;
	cout << "Phone: " << phone << endl;
	cout << "Address: " << address << endl;
	cout << "Email: " << email << endl;
}

void Customer::readFromFile(ifstream& ifile)
{
	Account::readFromFile(ifile);
	ifile >> fname >> lname >> phone >> address >> email >> orderId;
}

void Customer::saveToFile(ofstream& ofile)
{
	Account::saveToFile(ofile);
	ofile << " " << fname << " " << lname << " " << phone << " " << address << " " << email << " " << orderId << endl;
}

void Customer::displayMenu()
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
		cout << "1. Create new order\n2. View Progress of previous order\n3. LogOut" << endl;;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			if (orderId >= 0)
			{
				if (store->getCurrentOrders()[orderId].getOrderProcess() < OrderProcess::Delivered)
				{
					cout << "you have a previous order not delivered yet. Please let us serve you that first" << endl;
					break;
				}
			}

			Order newOrder(store->getCurrentOrders().size() + 1, accountid);
			int orderOption;
			do
			{
				cout << "Choose from following:\n1. Add predefined pizza\n2. Make customized pizza\n3. Add other item\n4. View order\n5. Duplicate Pizza\n6. Duplicate Non Pizza Item\n7. Delete Item\n8. See Price \n9. finish order" << endl;
				cin >> orderOption;
				switch (orderOption)
				{
				case 1:
				{
					cout << "Choose from the following list:" << endl;
					for (size_t i = 0; i < Company::getInstance()->getAllPizzas().size(); i++)
					{
						Company::getInstance()->getAllPizzas()[i].print();
					}
					cout << endl;
					cout << "Enter Pizza Id to add to order" << endl;
					string PizzaId;
					cin >> PizzaId;
					int PizzaIndex = Utils::searchVector(Company::getInstance()->getAllPizzas(), PizzaId);
					if (PizzaIndex < 0)
					{
						cout << "Id of pizza not found" << endl;
						break;
					}
					//create copy
					Pizza newPizza = Company::getInstance()->getAllPizzas()[PizzaIndex];

					newPizza.EditToppings();
					newOrder.AddToOrderContent(&newPizza);
				}
				break;
				case 2:
				{
					string id = Utils::getNewId(store->getCurrentOrders(), "P_");
					Pizza newPizza(id);
					try
					{
						CreatePizza(newPizza, true);
						newOrder.AddToOrderContent(&newPizza);
					}
					catch(TextToEnumConversionError& e)
					{
						cout << e.what();
					}
				}
				break;
				case 3:
				{
					if (newOrder.getOrderLength() == 0)
					{
						cout << "You cant add other items without ordering a pizza" << endl;
						break;
					}
					cout << "Choose from the following list:" << endl;
					for (size_t i = 0; i < Company::getInstance()->getAllNonPizzaItems().size(); i++)
					{
						Company::getInstance()->getAllNonPizzaItems()[i].print();
					}
					cout << "Enter Non Pizza Item Id" << endl;
					string NPIId;
					cin >> NPIId;
					int NPIIndex = Utils::searchVector(Company::getInstance()->getAllNonPizzaItems(), NPIId);
					if (NPIIndex < 0)
					{
						cout << "Id not found" << endl;
						break;
					}
					newOrder.AddToOrderContent(&Company::getInstance()->getAllNonPizzaItems()[NPIIndex]);

				}
				break;
				case 4:
				{
					newOrder.viewOrderContents();
				}
				break;
				case 5:
				{
					cout << "Enter Id of Pizza to dupliicate" << endl;
					string PizId;
					cin >> PizId;
					int PizzIndex = Utils::searchVector(newOrder.getOrderContents(), PizId);
					if (PizzIndex < 0)
					{
						cout << "Pizza not found" << endl;
						break;
					}
					else if (dynamic_cast<Pizza*>(newOrder.getOrderContents()[PizzIndex]) == nullptr)
					{
						cout << "Selected item is nnot found" << endl;
						break;
					}
					else
					{
						string newId = Utils::getNewId(newOrder.getOrderContents(), "P_");
						newOrder.AddToOrderContent(newOrder.getOrderContents()[PizzIndex]->duplicate(newId));
					}
				}
				break;
				case 6:
				{
					cout << "Enter Id of Other Item to dupliicate" << endl;
					string NonPizId;
					cin >> NonPizId;
					int NonPizzIndex = Utils::searchVector(newOrder.getOrderContents(), NonPizId);
					if (NonPizzIndex < 0)
					{
						cout << "Other Item not found" << endl;
						break;
					}
					else if (dynamic_cast<NonPizzaItem*>(newOrder.getOrderContents()[NonPizzIndex]) == nullptr)
					{
						cout << "Selected item is not found" << endl;
						break;
					}
					else
					{
						string newId = Utils::getNewId(newOrder.getOrderContents(), "NP_");
						newOrder.AddToOrderContent(newOrder.getOrderContents()[NonPizzIndex]->duplicate(newId));
					}
				}
				break;
				case 7:
				{
					cout << "Enter Id of Item to delete" << endl;
					string id;
					cin >> id;
					newOrder.removeFromOrderContent(id);
				}
				break;
				case 8:
				{
					cout << "Total price of order is: " << newOrder.getPrice() << endl;
				}
				break;
				case 9:
					break;
				default:
					cout << "Invalid option" << endl;
					break;
				}
			} while (orderOption != 9);

			if (newOrder.getOrderLength() != 0)
			{
				orderId = newOrder.getId();
				store->AddNewOrder(newOrder);
			}
		
		}
		break;
		case 2:
		{
			if (orderId < 0 || orderId > (int) store->getCurrentOrders().size() + 1)
			{
				cout << "You dont have a previous order" << endl;
			}
			else
			{
				int orderIndex = Utils::searchVector(store->getCurrentOrders(), orderId);
				cout << "The current progress of your order is: " << getTextFromOrderProcess(store->getCurrentOrders()[orderIndex].getOrderProcess()) << endl;
			}
		}
		break;
		case 3:
			break;
		default:
			cout << "Invalid choice" << endl;
		}
	} while (choice != 3);
}

void Customer::askForDetails(bool askForStore)
{
	Account::askForDetails(askForStore);
	cout << "Enter fist name: ";
	cin >> fname;
	cout << "Enter last name: ";
	cin >> lname;
	cout << "Enter phone: ";
	cin>> phone;
	cout << "Enter Address: ";
	cin >> address;
	cout << "Enter Email: ";
	cin >> email;
}

void Customer::setFname(string nfname)
{
	fname = nfname;
}

void Customer::setLname(string nlname)
{
	lname = nlname;
}

void Customer::setPhone(string nphone)
{
	phone = nphone;
}

void Customer::setAddress(string naddress)
{
	address = naddress;
}

void Customer::setEmail(string nemail)
{
	email = nemail;
}

void Customer::setOrderId(int id)
{
	orderId = id;
}
