#include "savingsacc.h"

using namespace std;

SavingsAcc::SavingsAcc() : Account() {
    interestrate = 0.0;
}

SavingsAcc::SavingsAcc(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer,
    double _interestrate)
    : Account(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer) {
    interestrate = (_interestrate < 0.0) ? 0.0 : _interestrate;
}

void SavingsAcc::setAll(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer,
    double interestrate) {
    setID(_id);
    setBalance(_balance);
    setWithdrawalCounter(_withdrawalcounter);
    setDepositCounter(_depositcounter);
    setAccountCustomer(_accountcustomer);
    this->interestrate = (interestrate < 0.0) ? 0.0 : interestrate;
}

double SavingsAcc::getInterestrate() const {
    return interestrate;
}

void SavingsAcc::setInterestrate(double interestrate) {
    if (interestrate < 0) {
        cout << "Interest rate cannot be negative. Keeping previous value.\n";
        return;
    }
    this->interestrate = interestrate;
}

void SavingsAcc::payInterest() {
    if (interestrate <= 0.0) {
        cout << "No interest applied (rate <= 0)." << endl;
        return;
    }
    double interest = balance * interestrate;
    balance += interest;
    cout << "Interest of $"
        << Account::formatCurrency(interest)
        << " applied. New balance: $"
        << Account::formatCurrency(balance) << endl;
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
    if (balance < amount) {
        cout << "Insufficient funds." << endl;
        return;
    }

    WithdrawMoney(amount);
    destinationacc->depositMoney(amount);

    cout << "Transfer of $"
        << Account::formatCurrency(amount)
        << " to account ID " << destinationacc->getID()
        << " successful." << endl;
}
