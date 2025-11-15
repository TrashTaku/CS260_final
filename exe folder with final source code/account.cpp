#include "account.h"
#include <cmath>    // for round, fabs

using namespace std;

Account::Account() {
    accountcustomer = nullptr;
    id = 0;
    balance = 0.0;
    withdrawalcounter = 0;
    depositcounter = 0;
}

Account::Account(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer) {
    id = _id;
    balance = _balance;
    withdrawalcounter = _withdrawalcounter;
    depositcounter = _depositcounter;
    accountcustomer = _accountcustomer;
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
}

void Account::setAccountCustomer(Customer* _accountcustomer) {
    accountcustomer = _accountcustomer;
}

void Account::setAll(int _id, double _balance, int _withdrawalcounter,
    int _depositcounter, Customer* _accountcustomer) {
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
    return accountcustomer;
}

// Deposit with validation
double Account::depositMoney(double amount) {
    if (amount <= 0) {
        cout << "Deposit amount must be positive." << endl;
        return balance;
    }
    balance += amount;
    depositcounter++;
    return balance;
}

// Base withdrawal: no overdraft, only if sufficient funds
double Account::WithdrawMoney(double amount) {
    if (amount <= 0) {
        cout << "Withdrawal amount must be positive." << endl;
        return balance;
    }
    if (amount > balance) {
        cout << "Insufficient funds. Withdrawal cancelled." << endl;
        return balance;
    }
    balance -= amount;
    withdrawalcounter++;
    return balance;
}

// Format currency with commas, e.g. 1234567.89 -> "1,234,567.89"
string Account::formatCurrency(double amount) {
    bool negative = (amount < 0);
    double absAmount = fabs(amount);

    long long totalCents = static_cast<long long>(std::round(absAmount * 100.0));
    long long dollars = totalCents / 100;
    int cents = static_cast<int>(totalCents % 100);

    // Convert dollars to string and insert commas
    string d = to_string(dollars);
    for (int i = static_cast<int>(d.size()) - 3; i > 0; i -= 3) {
        d.insert(i, ",");
    }

    // Build final string with two decimal places
    ostringstream oss;
    oss << d << '.' << setw(2) << setfill('0') << cents;
    string result = oss.str();
    if (negative && (dollars != 0 || cents != 0)) {
        result = "-" + result;
    }
    return result;
}

void Account::printTableHeader() {
    cout << left;
    cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
    cout << "| " << setw(8) << "AcctID"
        << " | " << setw(12) << "Balance"
        << " | " << setw(10) << "Deposits"
        << " | " << setw(12) << "Withdrawals"
        << " | " << setw(15) << "First Name"
        << " | " << setw(15) << "Last Name"
        << " | " << setw(15) << "Phone"
        << " |" << '\n';
    cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
}

void Account::displayAccountInfo() const {
    string fname = (accountcustomer ? accountcustomer->getFirstName() : "");
    string lname = (accountcustomer ? accountcustomer->getLastName() : "");
    string phone = (accountcustomer ? accountcustomer->getPhone() : "");

    cout << left
        << "| " << setw(8) << id
        << " | " << setw(12) << Account::formatCurrency(balance)
        << " | " << setw(10) << depositcounter
        << " | " << setw(12) << withdrawalcounter
        << " | " << setw(15) << fname
        << " | " << setw(15) << lname
        << " | " << setw(15) << phone
        << " |" << '\n';
}
