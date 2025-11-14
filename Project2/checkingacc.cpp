#include <iostream>
#include "checkingacc.h"
#include"customer.h"
#include <string>
using namespace std;

CheckingAcc::CheckingAcc() {
	overdraftlimit = 0.0;
}

CheckingAcc::CheckingAcc (int _id, double _balance, int _withdrawalcounter,
	int _depositcounter, Customer* _accountcustomer, double _overdraftlimit) :
	Account(_id, _balance, _withdrawalcounter, _depositcounter, _accountcustomer) {
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
	}
	
	if (amount <= balance) {
		balance = balance - amount;
		Account::withdraw(amount);
	}
	else if (amount>balance){
		if (amount < balance + overdraftlimit) {
			double diffamount = balance - amount;
			diffamount = abs(diffamount); // https://www.w3schools.com/cpp/ref_math_abs.asp
			if (diffamount > overdraftlimit) {
				cout << "withdrawal amount exceeds overdraft limit. Transaction cancelled." << endl;
			}
			else{
				balance = balance - amount;
				Account::withdraw(amount);
			}
	}
		else {
			cout << "withdrawal amount exceeds overdraft limit. Transaction cancelled." << endl;
		}
	}
}

void CheckingAcc::setAll(int _id, double _balance, int _withdrawalcounter,
	int _depositcounter,
	Customer* _accountcustomer, double _overdraftlimit) {
	Account::setAll(_id, _balance, _withdrawalcounter,
		_depositcounter, _accountcustomer);
	overdraftlimit = _overdraftlimit;
}