#include "customer.h"

using namespace std;

Customer::Customer() {
    fname = "";
    lname = "";
    address = "";
    phone = "";
    email = "";
}

Customer::Customer(const string& _fname, const string& _lname,
    const string& _address, const string& _phone,
    const string& _email) {
    fname = _fname;
    lname = _lname;
    address = _address;
    phone = _phone;
    email = _email;
}

void Customer::setFirstName(const string& _fname) {
    fname = _fname;
}

void Customer::setLastName(const string& _lname) {
    lname = _lname;
}

void Customer::setAddress(const string& _address) {
    address = _address;
}

void Customer::setPhone(const string& _phone) {
    phone = _phone;
}

void Customer::setEmail(const string& _email) {
    email = _email;
}

void Customer::setAll(const string& _fname, const string& _lname,
    const string& _address, const string& _phone,
    const string& _email) {
    fname = _fname;
    lname = _lname;
    address = _address;
    phone = _phone;
    email = _email;
}

string Customer::getFirstName() const {
    return fname;
}

string Customer::getLastName() const {
    return lname;
}

string Customer::getAddress() const {
    return address;
}

string Customer::getPhone() const {
    return phone;
}

string Customer::getEmail() const {
    return email;
}

void Customer::printInfo() const {
    cout << left
        << "| " << setw(15) << fname
        << " | " << setw(15) << lname
        << " | " << setw(25) << address
        << " | " << setw(15) << phone
        << " | " << setw(20) << email
        << " |" << '\n';
}
