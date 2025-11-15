#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Customer {
private:
    string fname;
    string lname;
    string address;
    string phone;
    string email;

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

    // Row-style print (Excel-like)
    void printInfo() const;
    // Wrapper name matching spec
    void PrintInfo() const { printInfo(); }
};

#endif
