#include "NonPizzaItem.h"

NonPizzaItem::NonPizzaItem() {}

NonPizzaItem::NonPizzaItem(string id, string name, double price) :OrderItem(id, name, price) {}

NonPizzaItem* NonPizzaItem::duplicate(string newid)
{
	NonPizzaItem* newNonPizzaItem = new NonPizzaItem(newid, name, price);
	return newNonPizzaItem;
}

void NonPizzaItem::print()
{
	OrderItem::print();
	cout << endl;
}

void NonPizzaItem::saveToFile(ofstream& ofile)
{
	ofile << "n" << " ";
	OrderItem::saveToFile(ofile);
	ofile << endl;
}
