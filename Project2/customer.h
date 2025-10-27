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
    Customer(string fn, string ln, string addr, string ph, string em);

    void setFirstName(string fn);
    void setLastName(string ln);
    void setAddress(string addr);
    void setPhone(string ph);
    void setEmail(string em);

    void setAll(string fn, string ln, string addr, string ph, string em);

    string getFirstName();
    string getLastName();
    string getAddress();
    string getPhone();
    string getEmail();

    void printInfo();



};


#endif
