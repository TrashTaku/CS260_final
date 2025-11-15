#include "checkingacc.h"

using namespace std;

CheckingAcc::CheckingAcc() : Account() {
    overdraftlimit = 0.0;
}

CheckingAcc::CheckingAcc(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer,
    double _overdraftlimit)
    : Account(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer) {
    overdraftlimit = (_overdraftlimit < 0.0) ? 0.0 : _overdraftlimit;
}

void CheckingAcc::setOverdraftLimit(double _overdraftlimit) {
    if (_overdraftlimit < 0) {
        cout << "Overdraft limit cannot be negative. Keeping previous value.\n";
        return;
    }
    overdraftlimit = _overdraftlimit;
}

double CheckingAcc::getOverdraftLimit() const {
    return overdraftlimit;
}

void CheckingAcc::setAll(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer,
    double _overdraftlimit) {
    setID(_id);
    setBalance(_balance);
    setWithdrawalCounter(_withdrawalcounter);
    setDepositCounter(_depositcounter);
    setAccountCustomer(_accountcustomer);
    overdraftlimit = (_overdraftlimit < 0.0) ? 0.0 : _overdraftlimit;
}

// Spec behaviour with overdraft + $20 fee
double CheckingAcc::WithdrawMoney(double amount) {
    if (amount <= 0) {
        cout << "Withdrawal amount must be positive." << endl;
        return balance;
    }

    double currentBalance = getBalance();

    if (amount <= currentBalance) {
        // Normal withdrawal using base logic
        return Account::WithdrawMoney(amount);
    }

    double deficit = amount - currentBalance;

    if (deficit <= overdraftlimit) {
        overdraftlimit -= deficit; // reduce remaining overdraft room
        double newBalance = currentBalance - amount - 20.0; // fee
        setBalance(newBalance);
        withdrawalcounter++;

        cout << "Overdraft used: $"
            << Account::formatCurrency(deficit)
            << ", service fee $20.00 applied." << endl;
        cout << "Remaining overdraft limit: $"
            << Account::formatCurrency(overdraftlimit) << endl;
        return newBalance;
    }
    else {
        cout << "Withdrawal amount exceeds overdraft limit. Transaction cancelled." << endl;
        return balance;
    }
}
