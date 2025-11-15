#pragma once
#ifndef CHECKINGACC_H
#define CHECKINGACC_H

#include "account.h"

class CheckingAcc : public Account {
private:
    double overdraftlimit; // maximum allowed overdraft

public:
    CheckingAcc();
    CheckingAcc(int _id, double _balance, int _withdrawalcounter,
        int _depositcounter, Customer* _accountcustomer,
        double _overdraftlimit);

    void setOverdraftLimit(double _overdraftlimit);
    double getOverdraftLimit() const;

    void setAll(int _id, double _balance, int _withdrawalcounter,
        int _depositcounter, Customer* _accountcustomer,
        double _overdraftlimit);

    // Override base withdrawal with overdraft + $20 fee logic
    double WithdrawMoney(double amount) override;
};

#endif // CHECKINGACC_H
