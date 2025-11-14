#pragma once
#ifndef SAVINGSACC_H
#define SAVINGSACC_H

#include "account.h"
#include <string>

class SavingsAcc : public Account {
private:
    double interestrate;

public:
    SavingsAcc();
    SavingsAcc(int _id, double _balance, int _withdrawalcounter,
        int _depositcounter, Customer* _accountcustomer,
        double interestrate);

    void setAll(int _id, double _balance, int _withdrawalcounter,
        int _depositcounter, Customer* _accountcustomer,
        double interestrate);

    double getInterestrate() const;
    void setInterestrate(double interestrate);

    void payInterest();
    void transfer(double amount, SavingsAcc* destinationacc);
};

#endif // SAVINGSACC_H