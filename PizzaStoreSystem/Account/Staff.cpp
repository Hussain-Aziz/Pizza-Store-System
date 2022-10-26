#include "Staff.h"
#include "../Company/Company.h"

Staff::Staff():Account()
{
	currentAccountType = AccountType::Staff;
}

Staff::Staff(string accountid, string storeId, string username, string password) :Account(accountid, storeId, username, password, AccountType::Staff) {}

void Staff::displayMenu()
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
		cout << "1. View all sent orders\n2. View all orders\n3. View all customers\n4. Create an order\n5. Edit Order\n6. Delete Order\n7. Set Order to recieved\n8. View all prepared orders\n9. Assign prepared order to driver";
		cout << "\n10. Mark order as failure to deliver\n11. Mark order as rejected\n12. Mark order as Canceled\n13. View all Pizzas\n14. View all Toppings\n15. View all Non Pizza Items\n16. LogOut" << endl;
		cin >> choice;

		switch(choice)
		{
		case 1:
		{
			store->displayOrders(OrderProcess::Sent);
		}
		break;
		case 2:
		{
			store->displayAllOrders();
		}
		break;
		case 3:
		{
			for (int i = 0; i < store->getStoreStaff().size(); i++)
			{
				if (store->getStoreStaff()[i]->getAccountType() == AccountType::Customer) 
					store->getStoreStaff()[i]->print();
			}
		}
		break;
		case 4:
		{
			cout << "Enter the id of the customer or enter \"new\" to create a new customer:";
			string input;
			cin >> input;
			Customer* customer;
			if (input == "new")
			{
				string id = Utils::getNewId(store->getStoreStaff(), "Customer_");
				customer = new Customer();
				customer->setAccountId(id);
				customer->askForDetails(false);
				customer->setStoreId(storeId);
			}
			else
			{
				int customerIndex = Utils::searchVector(store->getStoreStaff(), input);
				if (customerIndex < 0)
				{
					cout << "Customer id not found" << endl;
					break;
				}
				else if (store->getStoreStaff()[customerIndex]->getAccountType() != AccountType::Customer)
				{
					cout << "This account doesnt belong to a customer" << endl;
					break;
				}
				else
				{
					customer = static_cast<Customer*>(store->getStoreStaff()[customerIndex]);
				}

				Order newOrder(store->getCurrentOrders().size(), customer->getAccountId());
				int orderOption;
				do
				{
					cout << "Choose from following:\n1. Add premade pizza\n2. Add customized pizza\n3. add non pizza item\n4. finish order" << endl;
					cin >> orderOption;
					switch (orderOption)
					{
					case 1:
					{
						cout << "Enter Pizza Id" << endl;
						string PizzaId;
						cin >> PizzaId;
						int PizzaIndex = Utils::searchVector(Company::getInstance()->getAllPizzas(), PizzaId);
						if (PizzaIndex < 0)
						{
							cout << "Id not found" << endl;
							break;
						}
						newOrder.AddToOrderContent(&Company::getInstance()->getAllPizzas()[PizzaIndex]);

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
							cout << e.what() << endl;
						}
					}
					break;
					case 3:
					{
						cout << "Enter Non Pizza Item Id" << endl;
						string NPIId;
						cin >> NPIId;
						int NPIIndex = Utils::searchVector(Company::getInstance()->getAllNonPizzaItems(), NPIId);
						if (NPIIndex < 0)
						{
							cout << "Id not found" << endl;
							break;
						}
						newOrder.AddToOrderContent(&Company::getInstance()->getAllPizzas()[NPIIndex]);

					}
					break;
					case 4:
						break;
					default:
						cout << "Invalid option" << endl;
						break;
					}
				} while (orderOption != 4);

				if (newOrder.getOrderLength() != 0) store->AddNewOrder(newOrder);
			}
		}
		break;
		case 5:
		{
			cout << "Enter id of order to edit: ";
			int id;
			cin >> id;
			int orderIndex = Utils::searchVector(store->getCurrentOrders(), id);
			if (orderIndex < 0)
			{
				cout << "Order not found" << endl;
				break;
			}
			cout << "Choose from the following:\n1. Add Item\n2. Edit Pizza\n3. Delete Item" << endl;
			int editChoice;
			cin >> editChoice;
			switch (editChoice)
			{
			case 1:
			{
				int AddOption;
				cout << "Choose from following:\n1. Add premade pizza\n2. Add customized pizza\n3. add non pizza item\n4. finish order" << endl;
				cin >> AddOption;
				switch (AddOption)
				{
				case 1:
				{
					cout << "Enter Pizza Id" << endl;
					string PizzaId;
					cin >> PizzaId;
					int PizzaIndex = Utils::searchVector(Company::getInstance()->getAllPizzas(), PizzaId);
					if (PizzaIndex < 0)
					{
						cout << "Id not found" << endl;
						break;
					}
					store->getCurrentOrders()[orderIndex].AddToOrderContent(&Company::getInstance()->getAllPizzas()[PizzaIndex]);

				}
				break;
				case 2:
				{
					string id = Utils::getNewId(store->getCurrentOrders(), "P_");
					Pizza newPizza(id);
					try
					{
						CreatePizza(newPizza, true);
						store->getCurrentOrders()[orderIndex].AddToOrderContent(&newPizza);
					}
					catch (TextToEnumConversionError& e)
					{
						cout << e.what() << endl;
					}
				}
				break;
				case 3:
				{
					cout << "Enter Non Pizza Item Id" << endl;
					string NPIId;
					cin >> NPIId;
					int NPIIndex = Utils::searchVector(Company::getInstance()->getAllNonPizzaItems(), NPIId);
					if (NPIIndex < 0)
					{
						cout << "Id not found" << endl;
						break;
					}
					store->getCurrentOrders()[orderIndex].AddToOrderContent(&Company::getInstance()->getAllPizzas()[NPIIndex]);

				}
				break;
				case 4:
					break;
				default:
					cout << "Invalid option" << endl;
					break;
				}
			}
			break;
			case 2:
			{
				cout << "Enter id of Pizza: ";
				string pizzaId;
				cin >> pizzaId;
				int PizzaIndex = Utils::searchVector(store->getCurrentOrders()[orderIndex].getOrderContents(), pizzaId);
				if (PizzaIndex < 0)
				{
					cout << "Pizza not found" << endl;
					break;
				}
				else if (dynamic_cast<Pizza*>(store->getCurrentOrders()[orderIndex].getOrderContents()[PizzaIndex]) == nullptr)
				{
					cout << "Selected item is not a pizza" << endl;
					break;
				}
				else
				{
					OrderItem* OldPizza = store->getCurrentOrders()[orderIndex].getOrderContents()[PizzaIndex];
					Pizza EditedPizza(OldPizza->getId(), OldPizza->getName());
					try
					{
						CreatePizza(EditedPizza, false);

						delete store->getCurrentOrders()[orderIndex].getOrderContents()[PizzaIndex];
						store->getCurrentOrders()[orderIndex].getOrderContents()[PizzaIndex] = &EditedPizza;

					}
					catch(TextToEnumConversionError& e)
					{
						cout << e.what() << endl;
					}
				}

			}
			break;
			case 3:
			{
				cout << "Enter Item Id to delete" << endl;
				string ItemId;
				cin >> ItemId;
				store->getCurrentOrders()[orderIndex].removeFromOrderContent(ItemId);
			}
			case 4:
				break;
			default:
				break;
			}
		}
		break;
		case 6:
		{
			cout << "Enter id of order to delete: ";
			int id;
			cin >> id;
			store->RemoveOrder(id);
		}
		break;
		case 7:
		{
			cout << "Enter id of order to set as received: ";
			int id;
			cin >> id;
			int orderIndex = Utils::searchVector(store->getCurrentOrders(), id);
			if (orderIndex < 0)
			{
				cout << "Order not found" << endl;
				break;
			}
			store->getCurrentOrders()[orderIndex].setOrderProcess(OrderProcess::Recieved);
		}
		break;
		case 8:
		{
			store->displayOrders(OrderProcess::Prepared);
		}
		break;
		case 9:
		{
			cout << "Enter id of order to assign delivery driver: ";
			int id;
			cin >> id;
			int orderIndex = Utils::searchVector(store->getCurrentOrders(), id);
			if (orderIndex < 0)
			{
				cout << "Order not found" << endl;
				break;
			}
			cout << "List of delivery Drivers Available: " << endl;
			int count = 0;
			for (int i = 0; i < store->getStoreStaff().size(); i++)
			{
				if (store->getStoreStaff()[i]->getAccountType() == AccountType::DeliveryDriver)
				{
					if (static_cast<DeliveryDriver*>(store->getStoreStaff()[i])->getStatus() == DriverStatus::Available)
					{
						store->getStoreStaff()[i]->print();
						count++;
					}
				}
			}
			if (count == 0) cout << "No available delivery drivers" << endl;

			cout << "Enter Id of the driver:" << endl;
			string Did;
			cin >> Did;
			int Dindex = Utils::searchVector(store->getStoreStaff(), Did);
			if (Dindex < 0)
			{
				cout << "Driver not found" << endl;
				break;
			}
			else if (dynamic_cast<DeliveryDriver*>(store->getStoreStaff()[Dindex]) == nullptr)
			{
				cout << "Id is not for a driver" << endl;
				break;
			}
			else if (dynamic_cast<DeliveryDriver*>(store->getStoreStaff()[Dindex])->getStatus() != DriverStatus::Available)
			{
				cout << "Driver is not available" << endl;
				break;
			}
			else
			{
				dynamic_cast<DeliveryDriver*>(store->getStoreStaff()[Dindex])->setAssignedOrderId(id);
				dynamic_cast<DeliveryDriver*>(store->getStoreStaff()[Dindex])->setStatus(DriverStatus::OnDelivery);
			}
		}
		break;
		case 10:
		{
			cout << "Enter order id to mark as failure to deliver" << endl;
			int id;
			cin >> id;
			int index = Utils::searchVector(store->getCurrentOrders(), id);
			if (index < 0)
			{
				cout << "Order not found" << endl;
				break;
			}
			store->getCurrentOrders()[index].setOrderProcess(OrderProcess::FailureToDeliver);
		}
		break;
		case 11:
		{
			cout << "Enter order id to mark as Reject" << endl;
			int id;
			cin >> id;
			int index = Utils::searchVector(store->getCurrentOrders(), id);
			if (index < 0)
			{
				cout << "Order not found" << endl;
				break;
			}
			store->getCurrentOrders()[index].setOrderProcess(OrderProcess::FailureToDeliver);
		}
		break;
		case 12:
		{
			cout << "Enter order id to mark as Canceled" << endl;
			int id;
			cin >> id;
			int index = Utils::searchVector(store->getCurrentOrders(), id);
			if (index < 0)
			{
				cout << "Order not found" << endl;
				break;
			}
			store->getCurrentOrders()[index].setOrderProcess(OrderProcess::FailureToDeliver);
		}
		break;
		case 13:
		{
			for (int i = 0; i < Company::getInstance()->getAllPizzas().size(); i++)
			{
				Company::getInstance()->getAllPizzas()[i].print();
			}
		}
		break;
		case 14:
		{
			for (int i = 0; i < Company::getInstance()->getAllToppings().size(); i++)
			{
				cout << Company::getInstance()->getAllToppings()[i];
			}
		}
		break;
		case 15:
		{
			for (int i = 0; i < Company::getInstance()->getAllNonPizzaItems().size(); i++)
			{
				Company::getInstance()->getAllNonPizzaItems()[i].print();
			}
		}
		break;
		break;
		case 16:
			break;
		default:
			break;
		}
	} while (choice != 16);
}

Staff* Staff::duplicate()
{
	return new Staff(accountid, storeId, username, password);
}

void Staff::saveToFile(ofstream& ofile)
{
	Account::saveToFile(ofile);
	ofile << endl;
}
