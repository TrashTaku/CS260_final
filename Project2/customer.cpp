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

 void setFirstName(string _fname); {
	fname = _fname;
}
 void setLastName(string _lname); {
	 lname = _lname;
}
void setAddress(string _address);
{
	address = _address;
}
void setPhone(string _phone);
{
	phone = _phone;
}
void setEmail(string _email); {
	email = _email;
}

void setAll(string _fname, string _lname, string _address, string _phone, string _email) {
	fname = _fname;
	lname = _lname;
	address = _address;
	phone = _phone;
	email = _email;
}

string getFirstName();
{ return fname; }
string getLastName(); {
	return lname;
}
string getAddress(); {
	return address;
}
string getPhone(); {
	return phone;
}
string getEmail(); {
	return email;
}

void printInfo() {
	cout << setw(20) << fname << "|" << setw(20) << lname << "|" << setw(20) << address << "|" << setw(20) << phone << "|" << setw(20) << email << "|";
}
