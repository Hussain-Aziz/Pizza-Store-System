#include "Order.h"
#include "../Exceptions.h"

Order::Order()
{
	price = 0;
}
Order::Order(int id, string customerId)
{
	this->id = id;
	this->customerId = customerId;
	currentProgress = OrderProcess::Sent;
	price = 0;
}

Order::Order(int id, string customerId, OrderProcess currentProgress)
{
	this->id = id;
	this->customerId = customerId;
	this->currentProgress = currentProgress;
	price = 0;
}

Order::Order(const Order& order)
{
	id = order.id;
	customerId = order.customerId;
	currentProgress = order.currentProgress;
	price = order.price;

	for (int i = 0; i < order.orderContents.size(); i++)
	{
		orderContents.push_back(order.orderContents[i]->duplicate(order.orderContents[i]->getId()));
	}
}

void Order::operator=(const Order& order)
{
	for (int i = 0; i < orderContents.size(); i++)
	{
		delete orderContents[i];
	}
	orderContents.clear();
	price = order.price;
	id = order.id;
	customerId = order.customerId;
	currentProgress = order.currentProgress;

	for (int i = 0; i < order.orderContents.size(); i++)
	{
		orderContents.push_back(order.orderContents[i]->duplicate(order.orderContents[i]->getId()));
	}

}

Order::~Order()
{
	for (int i = 0; i < orderContents.size(); i++)
	{
		delete orderContents[i];
	}
}

void Order::viewOrderContents()
{
	cout << "Displaying Order " << id << " For " << customerId << endl;
	cout << "The price of the order is: " << price << endl;
	cout << "Progress is: " << getTextFromOrderProcess(currentProgress) << endl;
	for (int i = 0; i < orderContents.size(); i++)
	{
		orderContents[i]->print();
	}
	cout << endl;
}
void Order::viewPizzasOrderContents()
{
	for (int i = 0; i < orderContents.size(); i++)
	{
		if (dynamic_cast<Pizza*>(orderContents[i]) != nullptr)
			orderContents[i]->print();
	}
	cout << endl;
}

void Order::AddToOrderContent(OrderItem* newItem)
{
	price += newItem->getPrice();
	if (dynamic_cast<Pizza*>(newItem) != nullptr)
	{
		orderContents.push_back(newItem->duplicate(Utils::getNewId(orderContents, "P_")));
	}
	else
	{
		orderContents.push_back(newItem->duplicate(Utils::getNewId(orderContents, "NP_")));
	}
}

void Order::removeFromOrderContent(string OrderItemid)
{
	int index = Utils::searchVector(orderContents, OrderItemid);
	if (index < 0)
	{
		cout << "Not able to remove from order content because index not found" << endl;
	}
	else
	{
		price -= orderContents[index]->getPrice();
		delete orderContents[index];
		orderContents.erase(orderContents.begin() + index);
	}
}

void Order::saveToFile(ofstream& ofile)
{
	ofile << "START_OF_ORDER" << " " << id << " " << customerId << " " << getTextFromOrderProcess(currentProgress) << " " << price << endl;
	for (int i = 0; i < orderContents.size(); i++)
	{
		orderContents[i]->saveToFile(ofile);
	}
	ofile << endl <<"END_OF_ORDER" << endl;
}

void Order::readFromFile(ifstream& ifile)
{
	string begin;
	string reader;
	string progress;
	string endMarker = "END_OF_ORDER";

	ifile >> begin;
	ifile >> id;
	ifile >> customerId;
	ifile >> progress;
	ifile >> price;
	currentProgress = getOrderProcessFromText(progress);

	while (ifile >> reader)
	{
		if (reader == endMarker) break;
		if (reader == "n")
		{
			NonPizzaItem* newNPI = new NonPizzaItem();
			newNPI->readFromFile(ifile);
			orderContents.push_back(newNPI);
		}
		if (reader == "p")
		{
			Pizza* newP = new Pizza();
			newP->readFromFile(ifile);
			orderContents.push_back(newP);
		}
	}

}

int Order::getId()
{
	return id;
}

string Order::getCustomerId() { return customerId; }

void Order::setCustomerId(string newCustomerId) { customerId = newCustomerId; }

OrderProcess Order::getOrderProcess() { return currentProgress; }

void Order::setOrderProcess(OrderProcess newProgress) { currentProgress = newProgress; }

int Order::getOrderLength()
{
	return orderContents.size();
}

vector<OrderItem*>& Order::getOrderContents()
{
	return orderContents;
}

void Order::setId(int id)
{
	this->id = id;
}

double Order::getPrice()
{
	return price;
}

bool Order::operator==(int id)
{
	if (this->id == id) return true;
	return false;
}

bool Order::operator==(string id)
{
	int IntId = stoi(id);
	if (this->id == IntId) return true;
	return false;
}

string getTextFromOrderProcess(OrderProcess progress)
{
	switch (progress)
	{
	case OrderProcess::Sent:
		return "Sent";
	case OrderProcess::Recieved:
		return "Recieved";
	case OrderProcess::InKitchen:
		return "InKitchen";
	case OrderProcess::Prepared:
		return "Prepared";
	case OrderProcess::OutForDilivery:
		return "OutForDilivery";
	case OrderProcess::Delivered:
		return "Delivered";
	case OrderProcess::FailureToDeliver:
		return "FailureToDeliver";
	case OrderProcess::Reject:
		return "Reject";
	case OrderProcess::Canceled:
		return "Canceled";
	default:
		throw EnumNotFound();
	}
}

OrderProcess getOrderProcessFromText(string progress)
{
	if (progress == "Sent")
		return OrderProcess::Sent;
	if (progress == "Recieved")
		return OrderProcess::Recieved;
	if (progress == "InKitchen")
		return OrderProcess::InKitchen;
	if (progress == "Prepared")
		return OrderProcess::Prepared;
	if (progress == "OutForDilivery")
		return OrderProcess::OutForDilivery;
	if (progress == "Delivered")
		return OrderProcess::Delivered;
	if (progress == "FailureToDeliver")
		return OrderProcess::FailureToDeliver;
	if (progress == "Reject")
		return OrderProcess::Reject;
	if (progress == "Canceled")
		return OrderProcess::Canceled;


	throw TextToEnumConversionError();
}
