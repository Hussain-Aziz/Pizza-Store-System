#ifndef ORDER
#define ORDER
#include "../OrderItem/Pizza.h"
#include "../OrderItem/NonPizzaItem.h"
#include "../Utils.h"

enum class OrderProcess
{
	Sent = 0,
	Recieved,
	InKitchen,
	Prepared,
	OutForDilivery,
	Delivered,
	FailureToDeliver,
	Reject,
	Canceled
};

string getTextFromOrderProcess(OrderProcess progress);
OrderProcess getOrderProcessFromText(string progress);

class Order
{
private:
	int id;
	string customerId;
	vector<OrderItem*> orderContents;
	OrderProcess currentProgress;
	double price;

public:
	Order();
	Order(int id, string customerId);
	Order(int id, string customerId, OrderProcess currentProgress);
	Order(const Order& order);
	~Order();
	void operator=(const Order& order);

	void viewOrderContents();
	void viewPizzasOrderContents();
	void AddToOrderContent(OrderItem* newItem);
	void removeFromOrderContent(string OrderItemid);

	void saveToFile(ofstream& ofile);
	void readFromFile(ifstream& ifile);

	int getId();
	string getCustomerId();
	int getOrderLength();
	OrderProcess getOrderProcess();
	vector<OrderItem*>& getOrderContents();

	void setCustomerId(string newCustomerId);
	void setOrderProcess(OrderProcess newProgress);
	void setId(int id);
	double getPrice();

	bool operator==(int id);
	bool operator==(string id);

};

#endif