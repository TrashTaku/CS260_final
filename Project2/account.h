#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include "customer.h"
using namespace std;

class Account {
private:
	int id;
	double balance;
	int withdrawalcounter = 0;
	int depositcounter = 0;
	Customer* accountcustomer;
public:
	Account();
	Account(int _id, double _balance, int withdrawalcounter, int depositcounter
		Customer* _accountcustomer);
	void setID(int _id);
	void setBalance(double _balance);
	void setWithdrawalCounter(int _withdrawalcounter);
	void setDepositCounter(int _depositcounter);
	void setAccountCustomer(Customer* _accountcustomer);
	void setall(int _id, double _balance, int _withdrawalcounter, int _depositcounter,
		Customer* _accountcustomer);

	int getID() const;
	double getBalance() const;
	int getWithdrawalCounter() const;
	int getDepositCounter() const;
	Customer* getAccountCustomer() const;

	double deposit(double amount);
	double withdraw(double amount);
	void displayAccountInfo() const; //?



















#endif // !ACCOUNT_H

