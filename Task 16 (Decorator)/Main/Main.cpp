#include"../Task 16 (Decorator)/Decorator.h"

int main() {

	TypeOfFood *pancake = new Pancake();
	pancake->showComponents();
	cout << endl;
	cout << "Add something" << endl;
	pancake = new AddCream(pancake, "custard");
	pancake->showComponents();
	cout << endl;
	cout << "Add more" << endl;
	pancake = new AddChocolate(pancake, "white chocolate");
	pancake->showComponents();
	cout << endl;
	AddChocolate *full = new AddChocolate(new AddCream(new Pancake, " oil cream "), " milk chocolate");
	full->showComponents();
	system("Pause");
	return 0;
}