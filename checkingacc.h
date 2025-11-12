#pragma once
#ifndef CHECKINGACC_H
#define CHECKINGACC_H
#include "account.h"
class CheckingAcc : public Account {
private:
	double overdraftlimit;
public:
	CheckingAcc();
	CheckingAcc(int _id, double _balance, int _withdrawalcounter,
		int _depositcounter,
		Customer* _accountcustomer, double _overdraftlimit):
		Account(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer) ; //add logic in account to check whether its nullptr

	void setOverdraftLimit(double _overdraftlimit);
	double getOverdraftLimit() const;
	void setAll(int _id, double _balance, int _withdrawalcounter,
		int _depositcounter,
		Customer* _accountcustomer, double _overdraftlimit)
		:Account(_id, _balance, _withdrawalcounter, _depositcounter);

	void withdrawmoney(double amount);





};
#endif // !CHECKINGACC_H