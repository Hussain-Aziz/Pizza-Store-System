#ifndef NONPIZZAITEM
#define NONPIZZAITEM
#include "OrderItem.h"
class NonPizzaItem :public OrderItem
{
public:
	NonPizzaItem();
	NonPizzaItem(string id, string name, double price);
	virtual ~NonPizzaItem(){}

	NonPizzaItem* duplicate(string newid) override;
	void print() override;
	void saveToFile(ofstream& ofile) override;
};
#endif