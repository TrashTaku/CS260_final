#include "savingsacc.h"
#include"account.h"
#include <iostream>
using namespace std;

SavingsAcc::SavingsAcc() {
	interestrate = 0.0;
}
SavingsAcc::SavingsAcc(int _id, double _balance, int _withdrawalcounter,
	int _depositcounter, Customer* _accountcustomer, double _interestrate) {
	Account::setAll(_id, _balance, _withdrawalcounter,
		_depositcounter, _accountcustomer);
	this->interestrate = _interestrate;

}
void SavingsAcc::payInterest() {
	if (interestrate <0 ) {
		cout << "Interest rate cannot be negative." << endl;
	}
	else if (getInterestrate() > 0 && getInterestrate() < 1) {
		balance = balance + (balance * interestrate);
	}
	else {
		cout << "Interest rate should be between 0 and 1." << endl;
	}
}

void SavingsAcc::transfer(double amount, SavingsAcc* destinationacc) {
    if (!destinationacc) {
        cout << "Invalid destination account.\n";
        return;
    }
    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }
    if (getBalance() < amount) {
        cout << "Insufficient funds.\n";
        return;
    }

    withdraw(amount);               // or changeBalance(-amount)
    destinationacc->deposit(amount);

    cout << "Transfer of " << amount
        << " to account ID " << destinationacc->getID()
        << " successful.\n";
}




double getInterestrate() const {
	return interestrate;
}
void setInterestrate(double interestrate) {
	this->interestrate = interestrate;
}
