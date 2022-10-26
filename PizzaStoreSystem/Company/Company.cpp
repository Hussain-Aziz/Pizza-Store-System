#include "../Company/Company.h"
#include <time.h>

Company* Company::instance = 0;

Company::Company()
{
	//set random seed so we can get random numbers for the ids
	srand(time(NULL));
	cout << "Loading Stores" << endl;
	ifstream stores("Persistent Data/stores.txt");
	if (stores.fail())
	{
		throw FileNotOpened("Persistent Data/stores.txt");
	}
	int numstores;
	stores >> numstores;

	allStores.resize(numstores);
	for (size_t i = 0; i < allStores.size(); i++)
	{
		string id;
		stores >> id;
		allStores[i].SetId(id);
		allStores[i].InitStore();
	}

	stores.close();

	cout << "loading other data" << endl;
	standardReadFromFile(allAdmins, "admins");
	standardReadFromFile(allManagers, "managers");
	standardReadFromFile(allToppings, "toppings");
	standardReadFromFile(allPizzas, "pizza", true);
	standardReadFromFile(allNonPizzaItems, "nonpizzaitem", true);
}

void Company::Save()
{
	ofstream stores("Persistent Data/stores.txt");
	stores << allStores.size() << endl;
	for (size_t i = 0; i < allStores.size(); i++)
	{
		stores << allStores[i].getId() << endl;
	}
	stores.flush();
	stores.close();

	for (size_t i = 0; i < allStores.size(); i++)
	{
		allStores[i].saveToFile();
	}
	standardSaveToFile(allAdmins, "admins");
	standardSaveToFile(allManagers, "managers");
	standardSaveToFile(allToppings, "toppings");
	standardSaveToFile(allPizzas, "pizza");
	standardSaveToFile(allNonPizzaItems, "nonpizzaitem");
}

Company* Company::getInstance()
{
	if (instance == 0)
	{
		instance = new Company();
	}
	return instance;
}

vector<Store>& Company::getAllStores()
{
	return allStores;
}

vector<Admin>& Company::getAllAdmins()
{
	return allAdmins;
}

vector<Toppings>& Company::getAllToppings()
{
	return allToppings;
}

vector<Pizza>& Company::getAllPizzas()
{
	return allPizzas;
}

vector<NonPizzaItem>& Company::getAllNonPizzaItems()
{
	return allNonPizzaItems;
}

vector<Manager>& Company::getAllManagers()
{
	return allManagers;
}


