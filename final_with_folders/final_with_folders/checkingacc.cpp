#include <iostream>
#include "checkingacc.h"
#include "customer.h"

using namespace std;

CheckingAcc::CheckingAcc() {
    overdraftlimit = 0.0;
}

CheckingAcc::CheckingAcc(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer,
    double _overdraftlimit)
    : Account(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer) {
    overdraftlimit = _overdraftlimit;
}

void CheckingAcc::setOverdraftLimit(double _overdraftlimit) {
    overdraftlimit = _overdraftlimit;
}

double CheckingAcc::getOverdraftLimit() const {
    return overdraftlimit;
}

void CheckingAcc::withdrawmoney(double amount) {
    double balance = Account::getBalance();

    if (amount <= 0) {
        cout << "Invalid amount. Withdrawal amount must be positive." << endl;
        return;
    }

    if (amount <= balance) {
        // Normal withdraw
        Account::withdraw(amount);
    }
    else {
        // Allow overdraft up to limit
        double deficit = amount - balance;
        if (deficit <= overdraftlimit) {
            // withdraw everything that's in the account
            Account::withdraw(balance);   // sets balance to 0 and increments counter
            // represent overdraft as negative balance
            Account::setBalance(Account::getBalance() - deficit);
            cout << "Overdraft used: " << deficit << endl;
        }
        else {
            cout << "Withdrawal amount exceeds overdraft limit. Transaction cancelled." << endl;
        }
    }
}

void CheckingAcc::setAll(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer,
    double _overdraftlimit) {
    Account::setAll(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer);
    overdraftlimit = _overdraftlimit;
}

string CheckingAcc::displayAll(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer,
    double _overdraftlimit) {
    Account::displayAccountInfo();
    cout << getOverdraftLimit;
}