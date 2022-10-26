#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 
#include <filesystem>
#include "Store.h"
#include "../Company/Company.h"

void Store::ReadToVector(AccountType type)
{
	ifstream ifile("Persistent Data/" + id + "/" + getTextFromAccountType(type) + ".txt");
	if (ifile.fail())
	{
		throw FileNotOpened("Persistent Data/" + id + "/" + getTextFromAccountType(type) + ".txt");
	}
	int numItems;
	ifile >> numItems;

	for(int i = 0; i < numItems; i++)
	{
		Account* newAcc;
		switch (type)
		{
		case AccountType::Admin:
			newAcc = new Admin();
			break;
		case AccountType::Manager:
			newAcc = new Manager();
			break;
		case AccountType::DeliveryDriver:
			newAcc = new DeliveryDriver();
			break;
		case AccountType::Chef:
			newAcc = new Chef();
			break;
		case AccountType::Staff:
			newAcc = new Staff();
			break;
		case AccountType::Customer:
			newAcc = new Customer();
			break;
		default:
			newAcc = nullptr;
			throw EnumNotFound();
		}

		newAcc->readFromFile(ifile);
		StoreStaff.push_back(newAcc);

	}
	ifile.close();
}
Store::Store()
{
}

Store::Store(string id)
{
	this->id = id;
}

Store::Store(const Store& s)
{
	id = s.id;
	currentOrders = s.currentOrders;

	for (int i = 0; i < s.StoreStaff.size(); i++)
	{
		StoreStaff.push_back(s.StoreStaff[i]->duplicate());
	}
}

Store::~Store()
{
	for (int i = 0; i < StoreStaff.size(); i++)
	{
		delete StoreStaff[i];
	}
	StoreStaff.clear();
}

void Store::operator=(const Store& s)
{
	for (int i = 0; i < StoreStaff.size(); i++)
	{
		delete StoreStaff[i];
	}
	StoreStaff.clear();
	id = s.id;
	currentOrders = s.currentOrders;

	for (int i = 0; i < s.StoreStaff.size(); i++)
	{
		StoreStaff.push_back(s.StoreStaff[i]->duplicate());
	}
}

void Store::InitStore()
{
	ifstream ordersFile("Persistent Data/" + id  + "/orders.txt");

	if (ordersFile.fail())
	{
		throw FileNotOpened("Persistent Data/" + id + "/orders.txt");
	}

	int numOrders;
	ordersFile >> numOrders;
	currentOrders.resize(numOrders);
	for (int i = 0; i < currentOrders.size(); i++)
	{
		currentOrders[i].readFromFile(ordersFile);
	}

	ifstream managerFile("Persistent Data/" + id + "/manager.txt");
	if (ordersFile.fail())
	{
		throw FileNotOpened("Persistent Data/" + id + "/manager.txt");
	}
	managerFile >> name >> Managerid;
	managerFile.close();

	ReadToVector(AccountType::Staff);
	ReadToVector(AccountType::Customer);
	ReadToVector(AccountType::Chef);
	ReadToVector(AccountType::DeliveryDriver);

}

void Store::saveToFile()
{
	if (!filesystem::is_directory("Persistent Data") || !filesystem::exists("Persistent Data"))
	{
		filesystem::create_directory("Persistent Data");
	}
	if (!filesystem::is_directory("Persistent Data/" + id) || !filesystem::exists("Persistent Data/" + id))
	{
		filesystem::create_directory("Persistent Data/" + id);
	}

	ofstream ordersFile("Persistent Data/" + id + "/orders.txt");
	ordersFile << currentOrders.size() << endl;
	for (int i = 0; i < currentOrders.size(); i++)
	{
		currentOrders[i].saveToFile(ordersFile);
	}

	ordersFile.flush();
	ordersFile.close();

	ofstream managerFile("Persistent Data/" + id + "/manager.txt");
	managerFile << name << " " << Managerid << endl;

	managerFile.flush();
	managerFile.close();

	ofstream staff("Persistent Data/" + id + "/Staff.txt");
	ofstream chef("Persistent Data/" + id + "/Chef.txt");
	ofstream customer("Persistent Data/" + id + "/Customer.txt");
	ofstream deliveryDriver("Persistent Data/" + id + "/DeliveryDriver.txt");

	int staffCount = 0, chefCount = 0, customerCount = 0, deliveryDriverCount = 0;

	for (int i = 0; i < StoreStaff.size(); i++)
	{
		switch (StoreStaff[i]->getAccountType())
		{
		case AccountType::DeliveryDriver:
			deliveryDriverCount++;
			break;
		case AccountType::Chef:
			chefCount++;
			break;
		case AccountType::Staff:
			staffCount++;
			break;
		case AccountType::Customer:
			customerCount++;
			break;
		default:
			break;
		}
	}
	staff << staffCount << endl;
	chef << chefCount << endl;
	customer << customerCount << endl;
	deliveryDriver << deliveryDriverCount << endl;
	for (int i = 0; i < StoreStaff.size(); i++)
	{
		switch (StoreStaff[i]->getAccountType())
		{
		case AccountType::DeliveryDriver:
			StoreStaff[i]->saveToFile(deliveryDriver);
			break;
		case AccountType::Chef:
			StoreStaff[i]->saveToFile(chef);
			break;
		case AccountType::Staff:
			StoreStaff[i]->saveToFile(staff);
			break;
		case AccountType::Customer:
			StoreStaff[i]->saveToFile(customer);
			break;
		default:
			break;
		}
	}

	staff.flush();
	staff.close();
	customer.flush();
	customer.close();
	chef.flush();
	chef.close();
	deliveryDriver.flush();
	deliveryDriver.close();

}

void Store::displayOrders(OrderProcess progress)
{
	for (int i = 0; i < currentOrders.size(); i++)
	{
		if (progress == currentOrders[i].getOrderProcess())
			currentOrders[i].viewOrderContents();
	}
}

void Store::displayAllOrders()
{
	for (int i = 0; i < currentOrders.size(); i++)
	{
		currentOrders[i].viewOrderContents();
	}
}

void Store::AddNewOrder(Order& o)
{
	o.setId(currentOrders.size() + 1);
	currentOrders.push_back(o);
}

void Store::RemoveOrder(int id)
{
	if (id < 0 || id > currentOrders.size() - 1)
	{
		cout << "Invalid index to remove order" << endl;
	}
	else
	{
		currentOrders.erase(currentOrders.begin() + id);
		for (int i = 0; i < currentOrders.size(); i++)
		{
			currentOrders[i].setId(i + 1);
		}
	}
}

string Store::getName()
{
	return name;
}

string Store::getId()
{
	return id;
}

void Store::SetId(string id)
{
	this->id = id;
}

void Store::setName(string name)
{
	this->name = name;
}

void Store::SetManagerId(string Mid)
{
	Managerid = Mid;
}

vector<Account*>& Store::getStoreStaff()
{
	return StoreStaff;
}

vector<Order>& Store::getCurrentOrders()
{
	return currentOrders;
}

bool Store::operator==(const Store& s)
{
	if (id == s.id) return true;
	return false;
}

bool Store::operator==(string id)
{
	if (this->id == id) return true;
	return false;
}

void Store::output()
{
	cout << "Store ID: " << id << endl;
	cout << "Store Name" << name << endl;
	cout << "Manager ID: " << Managerid << endl;
}
