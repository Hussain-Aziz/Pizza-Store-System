#ifndef PIZZA
#define PIZZA
#include"OrderItem.h"
class Toppings
{
private:
	string toppingId;
	string name;
	double price;
public:
	Toppings();
	Toppings(string toppinId, string name, double price);
	friend ostream& operator<<(ostream& out, const Toppings& topping);
	bool operator==(const Toppings& topping);
	bool operator==(const string& id);

	void saveToFile(ofstream& ofile, bool endl = true);
	void readFromFile(ifstream& ifile);

	double getPrice();
	void setPrice(double newPrice);
	string getName();
	void setName(string newName);
};

enum class Crusts
{
	NormalCrust,
	ThickCrust,
	ThinCrust,
	CheeseCrust
};

Crusts getCrustFromText(string crust);
string getTextFromCrust(Crusts crust);
int getPriceFromCrust(Crusts crust);



class Pizza : public OrderItem
{
private:
	vector<Toppings> selectedToppings;
	Crusts selectedCrust;

public:
	Pizza();
	Pizza(string id);
	Pizza(string id, string name);
	Pizza(string id, string name, double basePrice);
	Pizza(string id, double basePrice);
	Pizza(string id, string name, double price, vector<Toppings> selectedToppings, Crusts selectedCrust);
	virtual ~Pizza(){}

	bool addToppings(Toppings topping);
	bool removeToppings(Toppings topping);
	int searchTopping(Toppings topping);

	void print() override;
	Pizza* duplicate(string newid) override;
	void saveToFile(ofstream& ofile) override;
	void readFromFile(ifstream& ifile) override;

	vector<Toppings>& getSelectedToppings();
	void setSelectedToppings(vector<Toppings> newToppingsVec);

	Crusts GetCrust();
	void setCrust(Crusts newCrust);

	friend void CreatePizza(Pizza& newPizza, bool askForName);

	void EditToppings();
};
#endif