#include "DeliveryDriver.h"
#include "../Company/Company.h"

DriverStatus getDriverStatusFromText(string status)
{
	if (status == "Available")
		return DriverStatus::Available;
	if (status == "OnDelivery")
		return DriverStatus::OnDelivery;
	if (status == "OffDuty")
		return DriverStatus::OffDuty;

	throw TextToEnumConversionError();
}

string getTextFromDriverStatus(DriverStatus status)
{
	switch (status)
	{
	case DriverStatus::Available:
		return "Available";
	case DriverStatus::OnDelivery:
		return "OnDelivery";
	case DriverStatus::OffDuty:
		return "OffDuty";
	default:
		throw EnumNotFound();
		break;
	}
}

DeliveryDriver::DeliveryDriver():Account()
{
	currentAccountType = AccountType::DeliveryDriver;
	status = DriverStatus::Available;
	assignedOrderId = -1;
}

DeliveryDriver::DeliveryDriver(string accountid, string storeId, string username, string password, DriverStatus status, int assignedOrderId):Account(accountid, storeId, username, password, AccountType::DeliveryDriver)
{
	this->status = status;
	this->assignedOrderId = assignedOrderId;
}

void DeliveryDriver::displayMenu()
{
	int choice;
	int Storeindex = Utils::searchVector(Company::getInstance()->getAllStores(), storeId);
	if (Storeindex < 0)
	{
		cout << "Store index not found" << endl;
		return;
	}
	Store* store = &Company::getInstance()->getAllStores()[Storeindex];
	do
	{
		cout << "Please select one of the options below" << endl;
		cout << "1. See Current Status\n2.Set status to available\n3. Set assigned order as delivered\n4. Set status to Off Duty\n5. LogOut " << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Current status is " << getTextFromDriverStatus(status);
		}
		break;
		case 2:
		{
			status = DriverStatus::Available;
			cout << "Current status is now set to available" << endl;
		}
		break;
		case 3:
		{
			if (assignedOrderId > -1)
			{
				int orderIndex = Utils::searchVector(store->getCurrentOrders(), assignedOrderId);
				if (orderIndex < 0)
				{
					cout << "Order Index not found" << endl;
					break;
				}
				else
				{
					store->getCurrentOrders()[orderIndex].setOrderProcess(OrderProcess::Delivered);
					status = DriverStatus::Available;
				}
			}
			else
			{
				cout << "No assigned order" << endl;
			}
		}
		break;
		case 4:
		{
			status = DriverStatus::OffDuty;
			cout << "Current status is now set to off duty" << endl;
		}
		break;
		case 5:
			break;
		default:
			cout << "Invalid choice please try again" << endl;
			break;
		}
	} while (choice != 5);
}

DeliveryDriver* DeliveryDriver::duplicate()
{
	return new DeliveryDriver(accountid, storeId, username, password, status, assignedOrderId);
}

void DeliveryDriver::print()
{
	Account::print();
	cout << "Status: " << getTextFromDriverStatus(status) << endl;
	cout << "Assigned Order" << assignedOrderId << endl;
}

void DeliveryDriver::readFromFile(ifstream& ifile)
{
	Account::readFromFile(ifile);
	string Dstatus;
	ifile >> Dstatus >> assignedOrderId;
	status = getDriverStatusFromText(Dstatus);
}

void DeliveryDriver::saveToFile(ofstream& ofile)
{
	Account::saveToFile(ofile);
	ofile << " " << getTextFromDriverStatus(status) << " " << assignedOrderId << endl;
}

void DeliveryDriver::askForDetails()
{
	Account::askForDetails();
	cout << "Enter status: ";
	string Dstatus;
	cin >> Dstatus;
	cout << "Enter assigned order id: ";
	cin >> assignedOrderId;
	status = getDriverStatusFromText(Dstatus);
}

DriverStatus DeliveryDriver::getStatus()
{
	return status;
}

void DeliveryDriver::setStatus(DriverStatus status)
{
	this->status = status;
}

void DeliveryDriver::setAssignedOrderId(int id)
{
	assignedOrderId = id;
}
