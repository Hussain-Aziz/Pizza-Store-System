#ifndef COMPANY
#define COMPANY
#include "../Account/Admin.h"
#include "../Account/Manager.h"
#include "../Account/DeliveryDriver.h"
#include "../Account/Chef.h"
#include "../Account/Staff.h"
#include "../Account/Customer.h"
#include "../Store/Store.h"
#include "../Utils.h"
#include "../Exceptions.h"
#include<string>
#include<vector>
using namespace std;

class Company
{
private:
	vector<Store> allStores;
	vector<Admin> allAdmins;
	vector<Toppings> allToppings;
	vector<Pizza> allPizzas;
	vector<NonPizzaItem> allNonPizzaItems;
	vector<Manager> allManagers;

	template<class T>
	void standardReadFromFile(vector<T> &t, string fileName, bool extraChar = false);
	template<class T>
	void standardSaveToFile(vector<T> &t, string fileName);
	static Company* instance;
	Company();

public:
	static Company* getInstance();

	void Save();

	vector<Store>& getAllStores();
	vector<Admin>& getAllAdmins();
	vector<Toppings>& getAllToppings();
	vector<Pizza>& getAllPizzas();
	vector<NonPizzaItem>& getAllNonPizzaItems();
	vector<Manager>& getAllManagers();
};


template<class T>
void Company::standardReadFromFile(vector<T> &t, string fileName, bool extraChar)
{
	ifstream ifile("Persistent Data/" + fileName + ".txt");
	if (ifile.fail())
	{
		throw FileNotOpened("Persistent Data/" + fileName + ".txt");
	}
	int numT;
	ifile >> numT;
	string dummy;

	t.resize(numT);
	for (size_t i = 0; i < t.size(); i++)
	{
		if (extraChar) ifile >> dummy;
		t[i].readFromFile(ifile);
	}
	ifile.close();
}

template<class T>
void Company::standardSaveToFile(vector<T> &t, string fileName)
{
	ofstream ofile("Persistent Data/" + fileName + ".txt");
	ofile << t.size() << endl;
	for (size_t i = 0; i < t.size(); i++)
	{
		t[i].saveToFile(ofile);
	}
	ofile.flush();
	ofile.close();

}
#endif