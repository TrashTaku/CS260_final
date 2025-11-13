#include <iostream>
#include <string>
#include "account.h"
#include "savingsacc.h"
#include "checkingacc.h"
#include "customer.h"
using namespace std;
int menudisplay();

int main() {
	int size;
	cout << "Enter number of customers: ";
	cin >> size;

	for (size <= 0) {
		cout << "Invalid size." << endl;
		cout << "Enter number of customers: ";
		cin >> size;
	}

	
	Customer* customers = new customerList[size];
	SavingsAcc* savingsAccounts = new SavingsAcc[size]; /*maybe we should dynamically allocate accounts too*/
	CheckingAcc* checkingAccounts = new CheckingAcc[size];

	for (int i = 0; i < size; i++) {
		string fname, lname, address, phone, email;
		cout << "Enter details for customer " << (i + 1) << ":\n";
		cout << "First Name: ";
		cin >> fname;
		cout << "Last Name: ";
		cin >> lname;
		cout << "Address: ";
		cin >> address;
		cout << "Phone: ";
		cin >> phone;
		cout << "Email: ";
		cin >> email;
		customers[i].setAll(fname, lname, address, phone, email);
	}

	int choice = menudisplay();

	switch (choice)
	{
		case 1:
			// Create checking account
			cout << "Enter customer phone number for checking account: ";
			string phone;
			cin >> phone;
			for (int i = 0; i < size; i++) {
				if (customers[i].getPhone() == phone) {
					double overdraftlimit;
					cout << "Enter overdraft limit: ";
					cin >> overdraftlimit;
					cout << "Enter account ID: ";
					int id;
					cin >> id;
					checkingAccounts[i].setAll(id, 0, 0, 0, customers[i], overdraftlimit);
					cout << "Checking account created for " << customers[i].getFirstName() << " " << customers[i].getLastName() << endl;
					break;
				}
				else if (phone != customers[size - 1].getPhone()) {
					cout << "Customer with phone number " << phone << " not found." << endl;
					cout << "Enter customer phone number for checking account: ";
					cin >> phone;
				}
			}
			// add initial deposit feature


			choice = menudisplay();
			break;
		case 2:
			// Create savings account
			cout << "Enter customer phone number for savings account: ";
			string phone2;
			cin >> phone2;
			for (int i = 0; i < size; i++) {
				if (customers[i].getPhone() == phone2) {
					double interestrate;
					cout << "Enter interest rate: ";
					cin >> interestrate;
					cout << "Enter account ID: ";
					int id;
					cin >> id;
					savingsAccounts[i].setAll(id, 0, 0, 0, customers[i], interestrate);
					cout << "Savings account created for " << customers[i].getFirstName() << " " << customers[i].getLastName() << endl;
					break;
				}
				else if (phone2 != customers[size - 1].getPhone()) {
					cout << "Customer with phone number " << phone2 << " not found." << endl;
					cout << "Enter customer phone number for savings account: ";
					cin >> phone2;
				}
			}
			cout << "Would you like to make an initial deposit? (y/n): ";
			char depositChoice;
			cin >> depositChoice;
			if (depositChoice == 'y' || depositChoice == 'Y') {
				double amount;
				cout << "Enter deposit amount: ";
				cin >> amount;
				void savingsacc::setBalance(double amount);
				cout << "Deposited $" << amount << " into savings account." << endl;
			}
			choice = menudisplay();

			break;
		case 3:
			// View account info
			break;
		case 4:
			// Modify or delete account
			cout << "Would you like to modify or delete an account? (m/d): ";
			char moddelChoice;
			cin >> moddelChoice;
			if (moddelChoice == 'm' || moddelChoice == 'M') {
				cout << "What would you like to modify?\n";
				cout << "1. Balance (withdraw/deposit)\n";
				cout << "2. Customer Information\n";
				cout << "3. Interest Rate/Overdraft Limit\n";
				cout << "4. Override account balance\n";
				int modifyChoice;
				cin >> modifyChoice;

				if (modifyChoice == 1) {
					// Balance modification logic
					cout << "for which account? (checking or savings c/s)" << endl;
					char accType;
					cin >> accType;
					if (accType == 'c' || accType == 'C') {
						// Checking account balance modification logic
						cout << "Enter a account ID: ";
						int accID;
						cin >> accID;


					}
					else if (accType == 's' || accType == 'S') {
						// Savings account balance modification logic
					}

				}
				else if (modifyChoice == 2) {
					// Customer information modification logic
				}
				else if (modifyChoice == 3) {
					// Interest rate/overdraft limit modification logic
				}
				else if (modifyChoice == 4) {
					// Override account balance logic
				}

			}
			else if (moddelChoice == 'd' || moddelChoice == 'D') {
				// Delete account logic
			}
			break;
		case 5:
			// Transfer between accounts
			break;
		case 6:
			// Exit
			cout << "Exiting program." << endl;
			break;

	default:
		break;
	}



	system("pause");
	return 0;
}

int menudisplay() {
	cout << "Menu Options:\n";
	cout << "1. Create checking Account\n";
	cout << "2. Create savings Account\n";
	cout << "3. View Account Info\n";
	cout << "4. Modify or delete a account\n";
	cout << "5. Transfer between 2 accounts\n";
	cout << "6. Exit\n";
	int choice;
	cin >> choice;
	for (choice < 1 || choice > 6) {
		cout << "Invalid choice. Please select a valid option (1-5): ";
		cin >> choice;
	}
	return choice;
}