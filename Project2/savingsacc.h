#pragma once
#ifndef SAVINGSACC_H
#define SAVINGSACC_H
#include"account.h"
#include<string>
using namespace std;

class SavingsAcc : public Account {
private:
	double interestrate;
public :
	SavingsAcc();
	SavingsAcc(int _id, double _balance, int _withdrawalcounter,
		int _depositcounter,
		Customer* _accountcustomer, double interestrate) :
		Account(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer);

	void setAll(int _id, double _balance, int _withdrawalcounter,
		int _depositcounter,
		Customer* _accountcustomer, double interestrate);
	double getInterestrate() const;
		void setInterestrate(double interestrate);
		void payInterest();
		void transfer(double _amount, SavingsAcc* destinationacc);

};
#endif // SAVINGSACC_H