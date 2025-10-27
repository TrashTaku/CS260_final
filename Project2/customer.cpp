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
Customer(string _fname, string _lname, string _address, string _phone, string _email);

void setFirstName(string _fname);
void setLastName(string _lname);
void setAddress(string _address);
void setPhone(string _phone);
void setEmail(string _email);

void setAll(string _fname, string _lname, string _address, string _phone, string _email);

string getFirstName();
string getLastName();
string getAddress();
string getPhone();
string getEmail();

void printInfo();
