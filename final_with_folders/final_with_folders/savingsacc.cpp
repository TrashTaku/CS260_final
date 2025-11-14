#include "savingsacc.h"
#include <iostream>

using namespace std;

SavingsAcc::SavingsAcc() {
    interestrate = 0.0;
}

SavingsAcc::SavingsAcc(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer,
    double _interestrate)
    : Account(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer) {
    interestrate = _interestrate;
}

void SavingsAcc::setAll(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer,
    double interestrate) {
    Account::setAll(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer);
    this->interestrate = interestrate;
}

double SavingsAcc::getInterestrate() const {
    return interestrate;
}

void SavingsAcc::setInterestrate(double interestrate) {
    this->interestrate = interestrate;
}

void SavingsAcc::payInterest() {
    if (interestrate < 0) {
        cout << "Interest rate cannot be negative." << endl;
    }
    else if (interestrate > 0 && interestrate < 1) {
        double newBalance = getBalance() + getBalance() * interestrate;
        setBalance(newBalance);
    }
    else {
        cout << "Interest rate should be between 0 and 1." << endl;
    }
}

void SavingsAcc::transfer(double amount, SavingsAcc* destinationacc) {
    if (!destinationacc) {
        cout << "Invalid destination account." << endl;
        return;
    }
    if (amount <= 0) {
        cout << "Invalid amount." << endl;
        return;
    }
    if (getBalance() < amount) {
        cout << "Insufficient funds." << endl;
        return;
    }

    withdraw(amount);
    destinationacc->deposit(amount);

    cout << "Transfer of " << amount
        << " to account ID " << destinationacc->getID()
        << " successful." << endl;
}