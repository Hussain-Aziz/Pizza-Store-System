#pragma once
#include"../Account/Account.h"
#include"../Order/Order.h"
class Store
{
private:
	string id;
	string name;
	vector<Order> currentOrders;
	vector<Account*> StoreStaff;
	string Managerid;
	void ReadToVector(AccountType type);
public:
	Store();
	Store(string id);
	Store(const Store& s);
	~Store();
	void operator=(const Store& s);

	void InitStore();
	void saveToFile();

	void displayOrders(OrderProcess progress);
	void displayAllOrders();
	void AddNewOrder(Order& o);
	void RemoveOrder(int id);

	string getName();
	string getId();
	vector<Account*>& getStoreStaff();
	vector<Order>& getCurrentOrders();
	void SetId(string id);
	void setName(string name);
	void SetManagerId(string Mid);

	bool operator==(const Store& s);
	bool operator==(string id);

	void output();
};

