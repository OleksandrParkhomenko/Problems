#include <iostream>
#include<string>
using namespace std;

// Common interface
class AddChocolate;
class TypeOfFood {
public:
	virtual void showComponents() = 0;
};

//Concrete type of food
class Pancake : public TypeOfFood {
private:
	string meal;
public:
	Pancake() :meal("Pancake"){};
	void showComponents() {
		cout << "Pancake";
	}
};

// Abstract decorator
class AddComponents : public TypeOfFood {
	TypeOfFood *food;
public:
	AddComponents(TypeOfFood* lnk) :food(lnk) {}
	virtual void showComponents() {
		food->showComponents();
	}
};

// Concrete decorators
class AddCream : public AddComponents {
private:
	string cream;
public:
	AddCream(TypeOfFood * lnk, string type) :AddComponents(lnk), cream(type){}

	void showComponents() {
		AddComponents::showComponents();
		cout << " with cream";
	}
};
class AddChocolate : public AddComponents {
private:
	string chocolate;
public:
	AddChocolate(TypeOfFood*lnk, string type) :AddComponents(lnk), chocolate(type){}
	void showComponents() {
		AddComponents::showComponents();
		cout << " with chocolate" << endl;
	}
};