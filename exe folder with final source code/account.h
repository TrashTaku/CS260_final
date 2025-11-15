#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>     // <-- added for formatCurrency
#include "customer.h"

using namespace std;

class Account {
protected:
    int id;
    double balance;
    int withdrawalcounter;
    int depositcounter;
    Customer* accountcustomer;

public:
    Account();
    Account(int _id, double _balance, int _withdrawalcounter,
        int _depositcounter, Customer* _accountcustomer);

    void setID(int _id);
    void setBalance(double _balance);
    void setWithdrawalCounter(int _withdrawalcounter);
    void setDepositCounter(int _depositcounter);
    void setAccountCustomer(Customer* _accountcustomer);
    void setAll(int _id, double _balance, int _withdrawalcounter,
        int _depositcounter, Customer* _accountcustomer);

    int getID() const;
    double getBalance() const;
    int getWithdrawalCounter() const;
    int getDepositCounter() const;
    Customer* getAccountCustomer() const;

    // Core money operations (spec names)
    double depositMoney(double amount);
    virtual double WithdrawMoney(double amount);

    // Convenience wrappers
    double deposit(double amount) { return depositMoney(amount); }
    double withdraw(double amount) { return WithdrawMoney(amount); }

    // Currency formatting with commas
    static string formatCurrency(double amount);

    // Display helpers
    static void printTableHeader();
    void displayAccountInfo() const; // one row
    void PrintInfo() const { displayAccountInfo(); }
};

#endif // ACCOUNT_H
