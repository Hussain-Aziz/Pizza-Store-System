#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
class OrderItem
{
protected:
	string name;
	string id;
	double price;
public:
	OrderItem();
	OrderItem(string id);
	OrderItem(string id, string name);
	OrderItem(string id, double price);
	OrderItem(string id, string name, double price);

	virtual void print();
	virtual OrderItem* duplicate(string newid) = 0;
	virtual void saveToFile(ofstream& ofile);
	virtual void readFromFile(ifstream& ifile);

	double getPrice();
	void setPrice(double newPrice);

	string getName();
	void setName(string newName);

	string getId();
	void setId(string newid);

	bool operator==(const OrderItem& item);
	bool operator==(string id);
	friend bool operator==(OrderItem* item, string id);
};
