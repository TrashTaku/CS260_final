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
		Account(_id, _balance, _withdrawalcounter, _depositcounter) ;




};
#endif // !CHECKINGACC_H