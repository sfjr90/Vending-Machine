#include<iostream>
#include<string>

using namespace std;

enum VendingMachineState {
	SELECT, QUANTITY, CALCULATE, UPDATE
};

enum Brand {
	COKE = 100, FANTA = 200, SPRITE = 300 //Why soda names don't show up?
};

struct Student {
	string name;
	long double cash;
};

struct Soda {
	Brand brandName;
	int inventory;
	long double price;
};

int main()
{
	VendingMachineState currentState = SELECT; //SELECT is the starting point

	/*Fill vending machine with soda*/
	Soda vendingMachine[3]; //Array

	vendingMachine[0].brandName = COKE;
	vendingMachine[0].inventory = 20;
	vendingMachine[0].price = 1.25;

	vendingMachine[1].brandName = FANTA;
	vendingMachine[1].inventory = 10;
	vendingMachine[1].price = 1.00;

	vendingMachine[2].brandName = SPRITE;
	vendingMachine[2].inventory = 10;
	vendingMachine[2].price = 0.75;

	Soda selectedSoda;
	Student saul;
	saul.name = "Saul";
	saul.cash = 50.00; //5 dollars in wallet

	while (true) {
		switch (currentState) {
		case SELECT:
			cout << "Current Status" << endl;
			cout << "[[Vending Machine]]" << endl;
			for (int i = 0; i < 3; i++) {
				cout << vendingMachine[i].brandName << " has " << vendingMachine[i]
					.inventory << " drinks and each costs " <<
					vendingMachine[i].price << " dollars " << endl;
			}
			cout << "[[Student]] " << endl;
			cout << saul.name << " has " << saul.cash << " dollars cash total " << endl;
			cout << "<<--End Status-->>" << endl << endl;

			cout << "Please select a drink from the following available options: " << endl;
			cout << "COKE = 100\nFANTA = 200\nSPRITE = 300" << endl;
			int selectedDrink;
			cin >> selectedDrink;
			switch (selectedDrink) {
			case COKE:
				cout << "You have selected COKE" << endl;
				selectedSoda.brandName = COKE;
				currentState = QUANTITY;
				break;
			case FANTA:
				cout << "You have selected FANTA" << endl;
				selectedSoda.brandName = FANTA;
				currentState = QUANTITY;
				break;
			case SPRITE:
				cout << "You have selected SPRITE" << endl;
				selectedSoda.brandName = SPRITE;
				currentState = QUANTITY;
				break;
			default:
				cout << "invalid drink selected" << endl;
				currentState = SELECT;
				break;
			}
			break;
		case QUANTITY:
			cout << "How many drinks would you like? ";
			int orderQuantity;
			cin >> orderQuantity;
			cout << "Your order of " << orderQuantity << " drinks has been received" << endl;
			switch (selectedSoda.brandName) {
			case COKE:
				if (orderQuantity < 0 || orderQuantity > vendingMachine[0].inventory) {
					cout << "Not enough in stock" << endl;
					currentState = SELECT;
					cout << endl << endl;
				}
				else {
					currentState = CALCULATE;
				}
				break;
			case FANTA:
				if (orderQuantity < 0 || orderQuantity > vendingMachine[1].inventory) {
					cout << "Not enough in stock" << endl;
					currentState = SELECT;
					cout << endl << endl;
				}
				else {
					currentState = CALCULATE;
				}
				break;
			case SPRITE:
				if (orderQuantity < 0 || orderQuantity > vendingMachine[2].inventory) {
					cout << "Not enough in stock" << endl;
					currentState = SELECT;
					cout << endl << endl;
				}
				else {
					currentState = CALCULATE;
				}
				break;
			default:
				cout << "Invalid drink" << endl;
				break;
			}
			break;
		case CALCULATE:
			cout << "Total cost of your soda is: ";
			int cost;
			switch (selectedSoda.brandName) {
			case COKE:
				cost = vendingMachine[0].price * orderQuantity;
				cout << cost << endl;
				break;
			case FANTA:
				cost = vendingMachine[1].price * orderQuantity;
				cout << cost << endl;
				break;
			case SPRITE:
				cost = vendingMachine[2].price * orderQuantity;
				cout << cost << endl;
				break;
			}
			int payment;
			cout << "Please type in your payment ";
			cin >> payment;
			if (payment > saul.cash || payment < cost || payment <= 0) {
				cout << "You don't have enough money" << endl;
				currentState = SELECT;
				cout << endl << endl;
			}
			else {
				saul.cash = saul.cash - payment;
				int change = payment - cost;
				cout << "Thank you, your change is " << change << " dollars." << endl;
				saul.cash = saul.cash + change;
				currentState = UPDATE;
			}
			break;
		case UPDATE:
			switch (selectedSoda.brandName) {
			case COKE:
				vendingMachine[0].inventory = vendingMachine[0].inventory - orderQuantity;
				currentState = SELECT;
				cout << endl << endl;
				break;
			case FANTA:
				vendingMachine[1].inventory = vendingMachine[1].inventory - orderQuantity;
				currentState = SELECT;
				cout << endl << endl;
				break;
			case SPRITE:
				vendingMachine[2].inventory = vendingMachine[2].inventory - orderQuantity;
				currentState = SELECT;
				cout << endl << endl;
				break;
			default:
				cout << "Error" << endl;
				currentState = SELECT;
				cout << endl << endl;
				break;
			}
			cout << "Inventory Updated" << endl;
			currentState = SELECT;
			cout << endl << endl;
		}
	}
}