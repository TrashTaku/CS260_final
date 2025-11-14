#include <iostream>
#include <iomanip>
#include "account.h"
#include "customer.h"
using namespace std;

Account::Account() {
	accountcustomer = nullptr;
	id = 0;
	balance = 0.0;
	withdrawalcounter = 0;
	depositcounter = 0;
}//make sure to use if else for customer ptr
Account::Account(int _id, double _balance, int _withdrawalcounter, int _depositcounter,
	Customer* _accountcustomer) {
	id = _id; //? should i use this->
	balance = _balance;
	withdrawalcounter = _withdrawalcounter;
	depositcounter = _depositcounter;
	if (_accountcustomer != nullptr) {
		accountcustomer = _accountcustomer;
	}
	else {
		cout << "Invalid customer pointer. Setting accountcustomer to nullptr." << endl;
	}

}
void Account::setID(int _id) {
	id = _id;
}
void Account::setBalance(double _balance) {
	balance = _balance;
}
void Account::setWithdrawalCounter(int _withdrawalcounter) {
	withdrawalcounter = _withdrawalcounter;
}
void Account::setDepositCounter(int _depositcounter) {
	depositcounter = _depositcounter;
}// for the display we can use customer->customerfx
void Account::setAccountCustomer(Customer* _accountcustomer) {
	accountcustomer = _accountcustomer;

}
void Account::setall(int _id, double _balance, int _withdrawalcounter, int _depositcounter,
	Customer* _accountcustomer) {
	id = _id;
	balance = _balance;
	withdrawalcounter = _withdrawalcounter;
	depositcounter = _depositcounter;
	accountcustomer = _accountcustomer;

}

int Account::getID() const {
	return id;
}
double Account::getBalance() const {
	return balance;
}
int Account::getWithdrawalCounter() const {
	return withdrawalcounter;
}
int Account::getDepositCounter() const {
	return depositcounter;
}
Customer* Account::getAccountCustomer() const {
	return accountcustomer; //do we need to add a accountcustomer-> display here
}

double Account::deposit(double amount) {
	if (amount > 0) {
		balance += amount;
		depositcounter++;
	}
	return balance;
}
double Account::withdraw(double amount) {
	if (amount > 0 && amount <= balance) {
		balance -= amount;
		withdrawalcounter++;
	}
	return balance;
}

//probably should change format to columns
void Account::displayAccountInfo() const {
	cout << fixed << setprecision(2);
	cout << "Account ID: " << id << endl;
	cout << "Balance: $" << balance << endl;
	cout << "Number of Deposits: " << depositcounter << endl;
	cout << "Number of Withdrawals: " << withdrawalcounter << endl;
	if (accountcustomer != nullptr) {
		cout << "Customer Information:" << endl;
		cout << "First Name: " << accountcustomer->getFirstName() << endl;
		cout << "Last Name: " << accountcustomer->getLastName() << endl;
		cout << "Address: " << accountcustomer->getAddress() << endl;
		cout << "Phone: " << accountcustomer->getPhone() << endl;
		cout << "Email: " << accountcustomer->getEmail() << endl;
	}
	else {
		cout << "No customer information available." << endl;
	}
}

