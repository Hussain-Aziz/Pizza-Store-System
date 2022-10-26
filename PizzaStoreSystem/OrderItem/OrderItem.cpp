#include"OrderItem.h"
OrderItem::OrderItem() 
{
	price = 0;
}

OrderItem::OrderItem(string id)
{
	this->id = id;
}

OrderItem::OrderItem(string id, string name)
{
	this->id = id;
	this->name = name;
	this->price = 0;
}

OrderItem::OrderItem(string id, double price)
{
	this->id = id;
	this->price = price;
}

OrderItem::OrderItem(string id, string name, double price)
{
	this->name = name;
	this->id = id;
	this->price = price;
}

void OrderItem::print()
{
	cout << id << ". " << name << endl;
	cout << "Price: " << price << " Dhs" << endl;
}

void OrderItem::saveToFile(ofstream& ofile)
{
	ofile << id << " " << name << " " << price;
}

void OrderItem::readFromFile(ifstream& ifile)
{
	ifile >> id >> name >> price;
}

double OrderItem::getPrice() { return price; }

void OrderItem::setPrice(double newPrice) { price = newPrice; }

string OrderItem::getName() { return name; }

void OrderItem::setName(string newName) { name = newName; }

string OrderItem::getId() { return id; }

void OrderItem::setId(string newid) { id = newid; }

bool OrderItem::operator==(const OrderItem& item)
{
	if (item.id == id) return true;
	return false;
}

bool OrderItem::operator==(string id)
{
	if (this->id == id) return true;
	return false;
}

bool operator==(OrderItem* item, string id)
{
	if (item->id == id) return true;
	return false;
}
