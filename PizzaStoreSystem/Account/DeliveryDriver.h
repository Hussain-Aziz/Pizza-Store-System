#pragma once
#include "Account.h"

enum class DriverStatus
{
	Available,
	OnDelivery,
	OffDuty,
};
DriverStatus getDriverStatusFromText(string status);
string getTextFromDriverStatus(DriverStatus status);

class DeliveryDriver :public Account
{
private:
	DriverStatus status;
	int assignedOrderId;
public:
	DeliveryDriver();
	DeliveryDriver(string accountid, string storeId, string username, string password,DriverStatus status, int assignedOrderId);
	virtual ~DeliveryDriver(){}

	void displayMenu();
	DeliveryDriver* duplicate();
	void print();
	void readFromFile(ifstream& ifile);
	void saveToFile(ofstream& ofile);
	void askForDetails();
	DriverStatus getStatus();
	void setStatus(DriverStatus status);

	void setAssignedOrderId(int id);
};

