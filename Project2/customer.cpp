#include "customer.h"
#include <iostream>
using namespace std;

Customer::Customer(){
	fname = "";
	lname = "";
	address = "";
	phone = "";
	email = "";
}
Customer::Customer(string _fname, string _lname, string _address, string _phone, string _email) {
	fname = _fname;
	lname = _lname;
	address = _address;
	phone = _phone;
	email = _email;

}

 void Customer:: setFirstName(string _fname); {
	fname = _fname;
}
 void Customer:: setLastName(string _lname); {
	 lname = _lname;
}
void Customer::setAddress(string _address);
{
	address = _address;
}
void Customer::setPhone(string _phone);
{
	phone = _phone;
}
void Customer:: setEmail(string _email); {
	email = _email;
}

void Customer::setAll(string _fname, string _lname, string _address, string _phone, string _email) {
	fname = _fname;
	lname = _lname;
	address = _address;
	phone = _phone;
	email = _email;
}

string Customer:: getFirstName();
{ return fname; }
string Customer:: getLastName(); {
	return lname;
}
string Customer:: getAddress(); {
	return address;
}
string Customer::getPhone(); {
	return phone;
}
string Customer::getEmail(); {
	return email;
}

void Customer::printInfo() {
	cout << setw(20) << fname << "|"
		<< setw(20) << lname << "|" << setw(20) << address 
		<< "|" << setw(20) << phone << "|" << setw(20) << email << "|";
}
