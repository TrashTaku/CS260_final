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
    Customer(const string& _fname, const string& _lname,
        const string& _address, const string& _phone,
        const string& _email);

    void setFirstName(const string& _fname);
    void setLastName(const string& _lname);
    void setAddress(const string& _address);
    void setPhone(const string& _phone);
    void setEmail(const string& _email);

    void setAll(const string& _fname, const string& _lname,
        const string& _address, const string& _phone,
        const string& _email);

    string getFirstName() const;
    string getLastName() const;
    string getAddress() const;
    string getPhone() const;
    string getEmail() const;

    void printInfo() const;
};

#endif