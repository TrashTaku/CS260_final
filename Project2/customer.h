#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <iostream>

using namespace std;

class Customer {
private:
	string fname, lname, address, phone, email;
public:
    Customer();
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



};


#endif
