#include "savingacc.h"
#include"account.h"
#include <iostream>
using namespace std;

SavingsAcc::SavingsAcc() {
	interestrate = 0.0;
}
SavingsAcc::SavingsAcc(int _id, double _balance, int _withdrawalcounter,
	int _depositcounter, Customer* _accountcustomer, double _overdraftlimit) :
	Account(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer) {
	interestrate = _interestrate;

}
void SavingsAcc::payinterest() {
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

void SavingAcc::transfer(double _amount, SavingsAcc* destinationacc) {
	if (_amount > balance) {
		cout << "Insufficient balance for transfer." << endl;
	}
	else {
		balance = balance - _amount;
		& destinationacc.balance += _amount;
		cout << "Transfer of " << _amount << " to account ID " << &destinationacc.getId() << " successful." << endl;
		cout << "New balance: $" << balance << endl;
		cout << "Destination account new balance: $" << &destinationacc.balance << endl;

	}
}



double getInterestrate() const {
	return interestrate;
}
void setInterestrate(double interestrate) {
	this->interestrate = interestrate;
}
