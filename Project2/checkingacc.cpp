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

