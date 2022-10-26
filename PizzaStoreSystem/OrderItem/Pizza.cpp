#include "Pizza.h"
#include "../Company/Company.h"

Pizza::Pizza() 
{
	selectedCrust = Crusts::NormalCrust;
	price = 10;//standard base price
}

Pizza::Pizza(string id):OrderItem(id, 10)
{
	selectedCrust = Crusts::NormalCrust;
}

Pizza::Pizza(string id, string name) : OrderItem(id, name, 10)
{
	selectedCrust = Crusts::NormalCrust;
}

Pizza::Pizza(string id, string name, double basePrice) :OrderItem(id, name, basePrice)
{
	selectedCrust = Crusts::NormalCrust;
}
Pizza::Pizza(string id, double basePrice) :OrderItem(id, basePrice)
{
	selectedCrust = Crusts::NormalCrust;
}

Pizza::Pizza(string id, string name, double price, vector<Toppings> selectedToppings, Crusts selectedCrust) : OrderItem(id, name, price)
{
	this->selectedToppings = selectedToppings;
	this->selectedCrust = selectedCrust;
}

bool Pizza::addToppings(Toppings topping)
{
	int index = searchTopping(topping);
	if (index != -1)
	{
		cout << "Topping already added. Please add another one" << endl;
		return false;
	}
	selectedToppings.push_back(topping);
	price += topping.getPrice();
	return true;
}

bool Pizza::removeToppings(Toppings topping)
{
	int index = searchTopping(topping);
	if (index > -1)
	{
		selectedToppings.erase(selectedToppings.begin() + index);
		price -= topping.getPrice();
		return true;
	}
	else
	{
		cout << "Topping not found. cannot be removed." << endl;
		return false;
	}
}

int Pizza::searchTopping(Toppings topping)
{
	for (int i = 0; i < selectedToppings.size(); i++)
	{
		if (topping == selectedToppings[i]) return i;
	}
	return -1;
}

vector<Toppings>& Pizza::getSelectedToppings() { return selectedToppings; }

void Pizza::setSelectedToppings(vector<Toppings> newToppingsVec) { selectedToppings = newToppingsVec; }

Crusts Pizza::GetCrust() { return selectedCrust; }

void Pizza::setCrust(Crusts newCrust)
{
	int currentCrustPrice = getPriceFromCrust(selectedCrust);
	int newCrustPrice = getPriceFromCrust(newCrust);

	price += newCrustPrice - currentCrustPrice;

	selectedCrust = newCrust;
}

Pizza* Pizza::duplicate(string newid)
{
	Pizza* newPizza = new Pizza(newid, name, price, selectedToppings, selectedCrust);
	return newPizza;
}

void Pizza::print()
{
	OrderItem::print();
	cout << "Crust: " << getTextFromCrust(selectedCrust) << endl;
	cout << "Toppings: " << endl;
	for (int i = 0; i < selectedToppings.size(); i++)
	{
		cout << "\t" << selectedToppings[i];
	}
	cout << endl;
}

void Pizza::saveToFile(ofstream& ofile)
{
	//so when reading file we can know type of order item it is
	ofile << "p" << " ";
	OrderItem::saveToFile(ofile);
	ofile << " ";
	//output crust name
	ofile << getTextFromCrust(selectedCrust) << " ";

	//output toppings name
	ofile << selectedToppings.size() << " ";
	for (int i = 0; i < selectedToppings.size(); i++)
	{
		selectedToppings[i].saveToFile(ofile, false);

		//put space only if it isnt last topping
		if (i != selectedToppings.size() - 1) ofile << " ";
	}
	ofile << endl;
}

void Pizza::readFromFile(ifstream& ifile)
{
	string crust;
	int numToppings;
	OrderItem::readFromFile(ifile);
	ifile >> crust >> numToppings;
	selectedCrust = getCrustFromText(crust);

	for (int i = 0; i < numToppings; i++)
	{
		Toppings newTopping;
		newTopping.readFromFile(ifile);
		selectedToppings.push_back(newTopping);
	}
}
#pragma region Toppings
ostream& operator<<(ostream& out, const Toppings& topping)
{
	out << topping.toppingId << " " << topping.name << "\t" << topping.price << " Dhs" << endl;
	return out;
}

void Toppings::saveToFile(ofstream& ofile, bool endl)
{
	ofile << toppingId << " " << name << " " << price;
	if (endl) ofile << endl;
}

void Toppings::readFromFile(ifstream& ifile)
{
	ifile >> toppingId >> name >> price;
}

Toppings::Toppings()
{
	price = 0;
}

Toppings::Toppings(string toppingId, string name, double price)
{
	this->toppingId = toppingId;
	this->name = name;
	this->price = price;
}

bool Toppings::operator==(const Toppings& topping)
{
	if (toppingId == topping.toppingId) return true;
	return false;
}

bool Toppings::operator==(const string& id)
{
	if (toppingId == id) return true;
	return false;
}

double Toppings::getPrice() { return price; }

void Toppings::setPrice(double newPrice) { price = newPrice; }

string Toppings::getName() { return name; }

void Toppings::setName(string newName) { name = newName; }

#pragma endregion

#pragma region Crust
Crusts getCrustFromText(string crust)
{
	//cant switch case string :(
	if (crust == "NormalCrust")
		return Crusts::NormalCrust;
	if (crust == "ThickCrust")
		return Crusts::ThickCrust;
	if (crust == "ThinCrust")
		return Crusts::ThinCrust;
	if (crust == "CheeseCrust")
		return Crusts::CheeseCrust;

	throw TextToEnumConversionError();
}

string getTextFromCrust(Crusts crust)
{
	switch (crust)
	{
	case Crusts::NormalCrust:
		return "NormalCrust";
	case Crusts::ThickCrust:
		return "ThickCrust";
	case Crusts::ThinCrust:
		return "ThinCrust";
	case Crusts::CheeseCrust:
		return "CheeseCrust";
	default:
		throw EnumNotFound();

	}
}

int getPriceFromCrust(Crusts crust)
{
	switch (crust)
	{
	case Crusts::NormalCrust:
		return 0;
	case Crusts::ThickCrust:
		return 1;
	case Crusts::ThinCrust:
		return 1;
	case Crusts::CheeseCrust:
		return 2;
	default:
		throw EnumNotFound();
	}
}

void CreatePizza(Pizza& newPizza, bool askForName)
{
	string crust;
	Crusts selectedCrust;
	if (askForName)
	{
		cout << "Enter name of the Pizza: ";
		cin >> newPizza.name;
	}

	cout << "Select type of crust (NormalCrust, ThickCrust, ThinCrust or CheeseCrust): ";
	cin >> crust;
	try
	{
		selectedCrust = getCrustFromText(crust);
	}
	catch (TextToEnumConversionError& e)
	{
		//throw error back to caller
		//with this, the caller can try catch the process of adding the pizza to the vector
		throw e;
	}
	newPizza.setCrust(selectedCrust);
	newPizza.EditToppings();
}

void Pizza::EditToppings()
{
	cout << "Choose from available toppings" << endl;
	for (int i = 0; i < Company::getInstance()->getAllToppings().size(); i++)
	{
		cout << Company::getInstance()->getAllToppings()[i];
	}
	cout << endl;

	int editPremadePizzaChoice;
	do
	{
		cout << "Are you happy with this pizza. Do you want to\n1. Add Topping\n2. Delete Topping\n3. Proceed with the rest of the order" << endl;
		cin >> editPremadePizzaChoice;
		switch (editPremadePizzaChoice)
		{
		case 1:
		{
			cout << "Enter Topping id to add: ";
			string tid;
			cin >> tid;
			int Toppingindex = Utils::searchVector(Company::getInstance()->getAllToppings(), tid);
			if (Toppingindex < 0)
			{
				cout << "Topping not found" << endl;
			}
			else
			{
				addToppings(Company::getInstance()->getAllToppings()[Toppingindex]);
				cout << "Topping added sucessfully " << endl;
			}
		}
		break;
		case 2:
		{
			cout << "Enter Topping id to delete: ";
			string tid;
			cin >> tid;
			int Toppingindex = Utils::searchVector(selectedToppings, tid);
			if (Toppingindex < 0)
			{
				cout << "Topping not found" << endl;
			}
			else
			{
				selectedToppings.erase(selectedToppings.begin() + Toppingindex);
				cout << "Topping deleted sucessfully " << endl;
			}
		}
		break;
		case 3:
			break;
		default:
			break;
		}
	} while (editPremadePizzaChoice != 3);
}
