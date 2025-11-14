#include <iostream>
#include <string>
#include "account.h"
#include "savingsacc.h"
#include "checkingacc.h"
#include "customer.h"

using namespace std;

int menudisplay();

int main() {
    int size;
    cout << "Enter number of customers: ";
    cin >> size;

    while (size <= 0) {
        cout << "Invalid size." << endl;
        cout << "Enter number of customers: ";
        cin >> size;
    }

    Customer* customers = new Customer[size];
    SavingsAcc* savingsAccounts = new SavingsAcc[size];
    CheckingAcc* checkingAccounts = new CheckingAcc[size];

    for (int i = 0; i < size; i++) {
        string fname, lname, address, phone, email;
        cout << "Enter details for customer " << (i + 1) << ":\n";
        cout << "First Name: ";
        cin >> fname;
        cout << "Last Name: ";
        cin >> lname;
        cout << "Address: ";
        cin >> address;
        cout << "Phone: ";
        cin >> phone;
        cout << "Email: ";
        cin >> email;
        customers[i].setAll(fname, lname, address, phone, email);
    }

    int choice = menudisplay();

    switch (choice) {
    case 1: {
        // Create checking account
        cout << "Enter customer phone number for checking account: ";
        string phone;
        cin >> phone;
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (customers[i].getPhone() == phone) {
                double overdraftlimit;
                cout << "Enter overdraft limit: ";
                cin >> overdraftlimit;
                cout << "Enter account ID: ";
                int id;
                cin >> id;
                checkingAccounts[i].setAll(id, 0, 0, 0, &customers[i], overdraftlimit);
                cout << "Checking account created for " << customers[i].getFirstName()
                    << " " << customers[i].getLastName() << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Customer with phone number " << phone << " not found." << endl;
        }
        choice = menudisplay();
        break;
    }
    case 2: {
        // Create savings account
        cout << "Enter customer phone number for savings account: ";
        string phone2;
        cin >> phone2;
        bool found = false;
        int idx = -1;
        for (int i = 0; i < size; i++) {
            if (customers[i].getPhone() == phone2) {
                double interestrate;
                cout << "Enter interest rate: ";
                cin >> interestrate;
                cout << "Enter account ID: ";
                int id;
                cin >> id;
                savingsAccounts[i].setAll(id, 0, 0, 0, &customers[i], interestrate);
                cout << "Savings account created for " << customers[i].getFirstName()
                    << " " << customers[i].getLastName() << endl;
                found = true;
                idx = i;
                break;
            }
        }
        if (!found) {
            cout << "Customer with phone number " << phone2 << " not found." << endl;
        }
        else {
            cout << "Would you like to make an initial deposit? (y/n): ";
            char depositChoice;
            cin >> depositChoice;
            if (depositChoice == 'y' || depositChoice == 'Y') {
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                savingsAccounts[idx].deposit(amount);
                cout << "Deposited $" << amount << " into savings account." << endl;
            }
        }
        choice = menudisplay();
        break;
    }
    case 3:
        // View account info (placeholder)
        cout << "View account info not implemented yet." << endl;
        break;
    case 4: {
        // Modify or delete account
        cout << "Would you like to modify or delete an account? (m/d): ";
        char moddelChoice;
        cin >> moddelChoice;
        if (moddelChoice == 'm' || moddelChoice == 'M') {
            cout << "What would you like to modify?\n";
            cout << "1. Balance (withdraw/deposit)\n";
            cout << "2. Customer Information\n";
            cout << "3. Interest Rate/Overdraft Limit\n";
            cout << "4. Override account balance\n";
            int modifyChoice;
            cin >> modifyChoice;

            if (modifyChoice == 1) {
                cout << "For which account? (checking or savings c/s)" << endl;
                char accType;
                cin >> accType;
                if (accType == 'c' || accType == 'C') {
                    cout << "Enter an account ID: ";
                    int accID;
                    cin >> accID;
                    bool foundAcc = false;
                    for (int i = 0; i < size; i++) {
                        if (checkingAccounts[i].getID() == accID) {
                            cout << "Would you like to withdraw or deposit? (w/d): ";
                            char transType;
                            cin >> transType;
                            if (transType == 'w' || transType == 'W') {
                                cout << "Enter withdrawal amount: ";
                                double amount;
                                cin >> amount;
                                checkingAccounts[i].withdrawmoney(amount);
                                cout << "New balance: $" << checkingAccounts[i].getBalance() << endl;
                            }
                            else if (transType == 'd' || transType == 'D') {
                                cout << "Enter deposit amount: ";
                                double amount;
                                cin >> amount;
                                checkingAccounts[i].deposit(amount);
                                cout << "New balance: $" << checkingAccounts[i].getBalance() << endl;
                            }
                            foundAcc = true;
                            break;
                        }
                    }
                    if (!foundAcc) {
                        cout << "Account with ID " << accID << " not found." << endl;
                    }
                }
                else if (accType == 's' || accType == 'S') {
                    cout << "Enter an account ID: ";
                    int accID;
                    cin >> accID;
                    bool foundAcc = false;
                    for (int i = 0; i < size; i++) {
                        if (savingsAccounts[i].getID() == accID) {
                            cout << "Would you like to withdraw or deposit? (w/d): ";
                            char transType;
                            cin >> transType;
                            if (transType == 'w' || transType == 'W') {
                                cout << "Enter withdrawal amount: ";
                                double amount;
                                cin >> amount;
                                savingsAccounts[i].withdraw(amount);
                                cout << "New balance: $" << savingsAccounts[i].getBalance() << endl;
                            }
                            else if (transType == 'd' || transType == 'D') {
                                cout << "Enter deposit amount: ";
                                double amount;
                                cin >> amount;
                                savingsAccounts[i].deposit(amount);
                                cout << "New balance: $" << savingsAccounts[i].getBalance() << endl;
                            }
                            foundAcc = true;
                            break;
                        }
                    }
                    if (!foundAcc) {
                        cout << "Account with ID " << accID << " not found." << endl;
                    }
                }
            }
            else if (modifyChoice == 2) {
                cout << "Enter customer phone number to modify information: ";
                string phone;
                cin >> phone;

                cout << "Which information would you like to modify?\n";
                cout << "1. First Name\n";
                cout << "2. Last Name\n";
                cout << "3. Address\n";
                cout << "4. Phone\n";
                cout << "5. Email\n";
                int infoChoice;
                cin >> infoChoice;

                for (int i = 0; i < size; i++) {
                    if (customers[i].getPhone() == phone) {
                        if (infoChoice == 1) {
                            cout << "Enter new first name: ";
                            string newFName;
                            cin >> newFName;
                            customers[i].setFirstName(newFName);
                            cout << "First name updated successfully." << endl;
                        }
                        else if (infoChoice == 2) {
                            cout << "Enter new last name: ";
                            string newLName;
                            cin >> newLName;
                            customers[i].setLastName(newLName);
                            cout << "Last name updated successfully." << endl;
                        }
                        else if (infoChoice == 3) {
                            cout << "Enter new address: ";
                            string newAddr;
                            cin >> newAddr;
                            customers[i].setAddress(newAddr);
                            cout << "Address updated successfully." << endl;
                        }
                        else if (infoChoice == 4) {
                            cout << "Enter new phone: ";
                            string newPhone;
                            cin >> newPhone;
                            customers[i].setPhone(newPhone);
                            cout << "Phone updated successfully." << endl;
                        }
                        else if (infoChoice == 5) {
                            cout << "Enter new email: ";
                            string newEmail;
                            cin >> newEmail;
                            customers[i].setEmail(newEmail);
                            cout << "Email updated successfully." << endl;
                        }
                        break;
                    }
                }
            }
            else if (modifyChoice == 3) {
                cout << "Modify interest rate/overdraft limit not implemented yet." << endl;
            }
            else if (modifyChoice == 4) {
                cout << "Override account balance not implemented yet." << endl;
            }

        }
        else if (moddelChoice == 'd' || moddelChoice == 'D') {
            cout << "Delete account not implemented yet." << endl;
        }
        break;
    }
    case 5:
        cout << "Transfer between accounts not implemented yet." << endl;
        break;
    case 6:
        cout << "Exiting program." << endl;
        break;
    default:
        break;
    }

    delete[] customers;
    delete[] savingsAccounts;
    delete[] checkingAccounts;

    return 0;
}

int menudisplay() {
    cout << "Menu Options:\n";
    cout << "1. Create checking Account\n";
    cout << "2. Create savings Account\n";
    cout << "3. View Account Info\n";
    cout << "4. Modify or delete an account\n";
    cout << "5. Transfer between 2 accounts\n";
    cout << "6. Exit\n";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 6) {
        cout << "Invalid choice. Please select a valid option (1-6): ";
        cin >> choice;
    }
    return choice;
}
