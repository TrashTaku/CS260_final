#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <cstdlib>   // for rand, srand
#include <ctime>     // for time

#include "account.h"
#include "savingsacc.h"
#include "checkingacc.h"
#include "customer.h"

using namespace std;

// ==== Function Prototypes (helpers defined at bottom) ====
int readInt(const string& prompt, int minVal, int maxVal);
int readIntMin(const string& prompt, int minVal);
double readDoubleMin(const string& prompt, double minVal);
char readCharChoice(const string& prompt, const string& validOptions);
int menudisplay();
void showAllAccounts(CheckingAcc* checkingAccounts, SavingsAcc* savingsAccounts, int size);
int generateAccountID();

int main() {
    // Seed random once
    srand(static_cast<unsigned int>(time(nullptr)));

    int size = readIntMin("Enter number of customers: ", 1);

    Customer* customers = new Customer[size];
    SavingsAcc* savingsAccounts = new SavingsAcc[size];
    CheckingAcc* checkingAccounts = new CheckingAcc[size];

    // collect customer info with duplicate checking (by phone)
    for (int i = 0; i < size; i++) {
        bool duplicate = false;
        do {
            string fname, lname, address, phone, email;
            cout << "\nEnter details for customer " << (i + 1) << ":\n";

            cout << "First Name: ";
            getline(cin, fname);

            cout << "Last Name: ";
            getline(cin, lname);

            cout << "Address: ";
            getline(cin, address);

            cout << "Phone: ";
            getline(cin, phone);

            cout << "Email: ";
            getline(cin, email);

            duplicate = false;
            for (int j = 0; j < i; ++j) {
                if (customers[j].getPhone() == phone) {
                    cout << "A customer with this phone already exists. Please re-enter this customer.\n";
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                customers[i].setAll(fname, lname, address, phone, email);
            }
        } while (duplicate);
    }

    int choice = 0;
    do {
        choice = menudisplay();

        if (choice == 1) {
            // Create checking account
            cout << "Enter customer phone number for checking account: ";
            string phone;
            getline(cin, phone);

            bool found = false;
            for (int i = 0; i < size; i++) {
                if (customers[i].getPhone() == phone) {
                    double overdraftlimit = readDoubleMin("Enter overdraft limit (>= 0): ", 0.0);
                    int id = generateAccountID();
                    cout << "Generated checking account ID: " << id << endl;

                    checkingAccounts[i].setAll(id, 0.0, 0, 0, &customers[i], overdraftlimit);
                    cout << "Checking account created for "
                        << customers[i].getFirstName() << " "
                        << customers[i].getLastName() << endl;

                    char dep = readCharChoice("Initial deposit? (y/n): ", "yn");
                    if (dep == 'y' || dep == 'Y') {
                        double amount = readDoubleMin("Enter deposit amount: ", 0.01);
                        checkingAccounts[i].depositMoney(amount);
                        cout << "Deposited $"
                            << Account::formatCurrency(amount)
                            << " into checking account." << endl;
                    }

                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Customer with phone number " << phone << " not found." << endl;
            }
        }
        else if (choice == 2) {
            // Create savings account
            cout << "Enter customer phone number for savings account: ";
            string phone2;
            getline(cin, phone2);

            bool found = false;
            for (int i = 0; i < size; i++) {
                if (customers[i].getPhone() == phone2) {
                    double interestrate = readDoubleMin("Enter interest rate (e.g., 0.03 for 3%, >= 0): ", 0.0);
                    int id = generateAccountID();
                    cout << "Generated savings account ID: " << id << endl;

                    savingsAccounts[i].setAll(id, 0.0, 0, 0, &customers[i], interestrate);
                    cout << "Savings account created for "
                        << customers[i].getFirstName() << " "
                        << customers[i].getLastName() << endl;

                    char dep = readCharChoice("Initial deposit? (y/n): ", "yn");
                    if (dep == 'y' || dep == 'Y') {
                        double amount = readDoubleMin("Enter deposit amount: ", 0.01);
                        savingsAccounts[i].depositMoney(amount);
                        cout << "Deposited $"
                            << Account::formatCurrency(amount)
                            << " into savings account." << endl;
                    }

                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Customer with phone number " << phone2 << " not found." << endl;
            }
        }
        else if (choice == 3) {
            // View account info
            int viewMode = readInt(
                "1. View specific account\n"
                "2. Show all accounts\n"
                "Enter choice (1-2): ", 1, 2
            );

            if (viewMode == 2) {
                showAllAccounts(checkingAccounts, savingsAccounts, size);
            }
            else {
                char t = readCharChoice("View which account type? (c = checking, s = savings): ", "cs");
                int lookup = readInt("Lookup by 1) Account ID or 2) Phone number? ", 1, 2);

                if (t == 'c' || t == 'C') {
                    if (lookup == 1) {
                        int id = readIntMin("Enter account ID (>= 0): ", 0);
                        bool found = false;
                        for (int i = 0; i < size; i++) {
                            if (checkingAccounts[i].getID() == id) {
                                Account::printTableHeader();
                                checkingAccounts[i].PrintInfo();
                                cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
                                cout << "Overdraft limit: $"
                                    << Account::formatCurrency(checkingAccounts[i].getOverdraftLimit()) << endl;
                                found = true;
                                break;
                            }
                        }
                        if (!found) cout << "Checking account with ID " << id << " not found.\n";
                    }
                    else {
                        string phone;
                        cout << "Enter phone number: ";
                        getline(cin, phone);
                        bool found = false;
                        bool headerPrinted = false;
                        for (int i = 0; i < size; i++) {
                            if (checkingAccounts[i].getAccountCustomer() &&
                                checkingAccounts[i].getAccountCustomer()->getPhone() == phone) {
                                if (!headerPrinted) {
                                    Account::printTableHeader();
                                    headerPrinted = true;
                                }
                                checkingAccounts[i].PrintInfo();
                                found = true;
                            }
                        }
                        if (found) {
                            cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
                        }
                        else {
                            cout << "No checking account found for that phone.\n";
                        }
                    }
                }
                else if (t == 's' || t == 'S') {
                    if (lookup == 1) {
                        int id = readIntMin("Enter account ID (>= 0): ", 0);
                        bool found = false;
                        for (int i = 0; i < size; i++) {
                            if (savingsAccounts[i].getID() == id) {
                                Account::printTableHeader();
                                savingsAccounts[i].PrintInfo();
                                cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
                                cout << "Interest rate: " << savingsAccounts[i].getInterestrate() << endl;
                                found = true;
                                break;
                            }
                        }
                        if (!found) cout << "Savings account with ID " << id << " not found.\n";
                    }
                    else {
                        string phone;
                        cout << "Enter phone number: ";
                        getline(cin, phone);
                        bool found = false;
                        bool headerPrinted = false;
                        for (int i = 0; i < size; i++) {
                            if (savingsAccounts[i].getAccountCustomer() &&
                                savingsAccounts[i].getAccountCustomer()->getPhone() == phone) {
                                if (!headerPrinted) {
                                    Account::printTableHeader();
                                    headerPrinted = true;
                                }
                                savingsAccounts[i].PrintInfo();
                                found = true;
                            }
                        }
                        if (found) {
                            cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
                        }
                        else {
                            cout << "No savings account found for that phone.\n";
                        }
                    }
                }
            }
        }
        else if (choice == 4) {
            // Modify or delete account
            char moddelChoice = readCharChoice("Modify or delete an account? (m/d): ", "md");

            if (moddelChoice == 'm' || moddelChoice == 'M') {
                cout << "What would you like to modify?\n";
                cout << "1. Balance (withdraw/deposit)\n";
                cout << "2. Customer Information\n";
                cout << "3. Interest Rate/Overdraft Limit\n";
                cout << "4. Override account balance\n";
                int modifyChoice = readInt("Enter choice (1-4): ", 1, 4);

                if (modifyChoice == 1) {
                    char accType = readCharChoice("For which account? (c = checking, s = savings): ", "cs");
                    int accID = readIntMin("Enter account ID (>= 0): ", 0);

                    if (accType == 'c' || accType == 'C') {
                        bool found = false;
                        for (int i = 0; i < size; i++) {
                            if (checkingAccounts[i].getID() == accID) {
                                char transType = readCharChoice("Withdraw or deposit? (w/d): ", "wd");
                                double amount = readDoubleMin(
                                    (transType == 'w' || transType == 'W') ?
                                    "Enter withdrawal amount: " : "Enter deposit amount: ", 0.01);
                                if (transType == 'w' || transType == 'W') {
                                    checkingAccounts[i].WithdrawMoney(amount);
                                }
                                else {
                                    checkingAccounts[i].depositMoney(amount);
                                }
                                cout << "New balance: $"
                                    << Account::formatCurrency(checkingAccounts[i].getBalance()) << endl;
                                found = true;
                                break;
                            }
                        }
                        if (!found) cout << "Checking account with ID " << accID << " not found.\n";
                    }
                    else {
                        bool found = false;
                        for (int i = 0; i < size; i++) {
                            if (savingsAccounts[i].getID() == accID) {
                                char transType = readCharChoice("Withdraw or deposit? (w/d): ", "wd");
                                double amount = readDoubleMin(
                                    (transType == 'w' || transType == 'W') ?
                                    "Enter withdrawal amount: " : "Enter deposit amount: ", 0.01);
                                if (transType == 'w' || transType == 'W') {
                                    savingsAccounts[i].WithdrawMoney(amount);
                                }
                                else {
                                    savingsAccounts[i].depositMoney(amount);
                                }
                                cout << "New balance: $"
                                    << Account::formatCurrency(savingsAccounts[i].getBalance()) << endl;
                                found = true;
                                break;
                            }
                        }
                        if (!found) cout << "Savings account with ID " << accID << " not found.\n";
                    }
                }
                else if (modifyChoice == 2) {
                    // Customer information modification
                    cout << "Enter customer phone number to modify information: ";
                    string phone;
                    getline(cin, phone);

                    bool found = false;
                    for (int i = 0; i < size; i++) {
                        if (customers[i].getPhone() == phone) {
                            cout << "Which information would you like to modify?\n";
                            cout << "1. First Name\n";
                            cout << "2. Last Name\n";
                            cout << "3. Address\n";
                            cout << "4. Phone\n";
                            cout << "5. Email\n";
                            int infoChoice = readInt("Enter choice (1-5): ", 1, 5);

                            if (infoChoice == 1) {
                                cout << "Enter new first name: ";
                                string v; getline(cin, v);
                                customers[i].setFirstName(v);
                            }
                            else if (infoChoice == 2) {
                                cout << "Enter new last name: ";
                                string v; getline(cin, v);
                                customers[i].setLastName(v);
                            }
                            else if (infoChoice == 3) {
                                cout << "Enter new address: ";
                                string v; getline(cin, v);
                                customers[i].setAddress(v);
                            }
                            else if (infoChoice == 4) {
                                cout << "Enter new phone: ";
                                string v; getline(cin, v);
                                customers[i].setPhone(v);
                            }
                            else if (infoChoice == 5) {
                                cout << "Enter new email: ";
                                string v; getline(cin, v);
                                customers[i].setEmail(v);
                            }
                            cout << "Customer information updated.\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found) cout << "Customer with that phone not found.\n";
                }
                else if (modifyChoice == 3) {
                    // Modify interest rate / overdraft
                    char t = readCharChoice("Modify (c = checking overdraft, s = savings interest): ", "cs");
                    int id = readIntMin("Enter account ID (>= 0): ", 0);

                    if (t == 'c' || t == 'C') {
                        bool found = false;
                        for (int i = 0; i < size; i++) {
                            if (checkingAccounts[i].getID() == id) {
                                double newLimit = readDoubleMin("Enter new overdraft limit (>= 0): ", 0.0);
                                checkingAccounts[i].setOverdraftLimit(newLimit);
                                cout << "Overdraft limit updated.\n";
                                found = true;
                                break;
                            }
                        }
                        if (!found) cout << "Checking account with ID " << id << " not found.\n";
                    }
                    else {
                        bool found = false;
                        for (int i = 0; i < size; i++) {
                            if (savingsAccounts[i].getID() == id) {
                                double newRate = readDoubleMin("Enter new interest rate (>= 0): ", 0.0);
                                savingsAccounts[i].setInterestrate(newRate);
                                cout << "Interest rate updated.\n";
                                found = true;
                                break;
                            }
                        }
                        if (!found) cout << "Savings account with ID " << id << " not found.\n";
                    }
                }
                else if (modifyChoice == 4) {
                    // Override account balance
                    char t = readCharChoice("Override which account? (c = checking, s = savings): ", "cs");
                    int id = readIntMin("Enter account ID (>= 0): ", 0);
                    double newBal = readDoubleMin("Enter new balance (>= 0): ", 0.0);

                    bool found = false;
                    if (t == 'c' || t == 'C') {
                        for (int i = 0; i < size; i++) {
                            if (checkingAccounts[i].getID() == id) {
                                checkingAccounts[i].setBalance(newBal);
                                cout << "New balance: $"
                                    << Account::formatCurrency(checkingAccounts[i].getBalance()) << endl;
                                found = true;
                                break;
                            }
                        }
                        if (!found) cout << "Checking account with ID " << id << " not found.\n";
                    }
                    else {
                        for (int i = 0; i < size; i++) {
                            if (savingsAccounts[i].getID() == id) {
                                savingsAccounts[i].setBalance(newBal);
                                cout << "New balance: $"
                                    << Account::formatCurrency(savingsAccounts[i].getBalance()) << endl;
                                found = true;
                                break;
                            }
                        }
                        if (!found) cout << "Savings account with ID " << id << " not found.\n";
                    }
                }
            }
            else if (moddelChoice == 'd' || moddelChoice == 'D') {
                // Delete (reset) an account
                char t = readCharChoice("Delete which account type? (c = checking, s = savings): ", "cs");
                int id = readIntMin("Enter account ID (>= 0): ", 0);

                bool found = false;
                if (t == 'c' || t == 'C') {
                    for (int i = 0; i < size; i++) {
                        if (checkingAccounts[i].getID() == id) {
                            checkingAccounts[i].setAll(0, 0.0, 0, 0, nullptr, 0.0);
                            cout << "Checking account deleted.\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found) cout << "Checking account with ID " << id << " not found.\n";
                }
                else {
                    for (int i = 0; i < size; i++) {
                        if (savingsAccounts[i].getID() == id) {
                            savingsAccounts[i].setAll(0, 0.0, 0, 0, nullptr, 0.0);
                            cout << "Savings account deleted.\n";
                            found = true;
                            break;
                        }
                    }
                    if (!found) cout << "Savings account with ID " << id << " not found.\n";
                }
            }
        }
        else if (choice == 5) {
            // Transfer between 2 accounts (generic)
            char fromType = readCharChoice("Transfer from (c = checking, s = savings): ", "cs");
            char toType = readCharChoice("Transfer to (c = checking, s = savings): ", "cs");

            int fromId = readIntMin("Enter source account ID (>= 0): ", 0);
            int toId = readIntMin("Enter destination account ID (>= 0): ", 0);
            double amount = readDoubleMin("Enter amount to transfer: ", 0.01);

            Account* fromAcc = nullptr;
            Account* toAcc = nullptr;

            if (fromType == 'c' || fromType == 'C') {
                for (int i = 0; i < size; i++) {
                    if (checkingAccounts[i].getID() == fromId) {
                        fromAcc = &checkingAccounts[i];
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < size; i++) {
                    if (savingsAccounts[i].getID() == fromId) {
                        fromAcc = &savingsAccounts[i];
                        break;
                    }
                }
            }

            if (toType == 'c' || toType == 'C') {
                for (int i = 0; i < size; i++) {
                    if (checkingAccounts[i].getID() == toId) {
                        toAcc = &checkingAccounts[i];
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < size; i++) {
                    if (savingsAccounts[i].getID() == toId) {
                        toAcc = &savingsAccounts[i];
                        break;
                    }
                }
            }

            if (!fromAcc || !toAcc) {
                cout << "Source or destination account not found.\n";
            }
            else if (fromAcc->getBalance() < amount) {
                cout << "Insufficient funds in source account.\n";
            }
            else {
                fromAcc->WithdrawMoney(amount);
                toAcc->depositMoney(amount);
                cout << "Transfer successful. New source balance: $"
                    << Account::formatCurrency(fromAcc->getBalance()) << endl;
            }
        }
        else if (choice == 6) {
            // Apply interest to a savings account
            int id = readIntMin("Enter savings account ID to apply interest (>= 0): ", 0);
            bool found = false;
            for (int i = 0; i < size; ++i) {
                if (savingsAccounts[i].getID() == id) {
                    savingsAccounts[i].payInterest();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Savings account with ID " << id << " not found.\n";
        }

    } while (choice != 7);

    cout << "Exiting program." << endl;

    delete[] customers;
    delete[] savingsAccounts;
    delete[] checkingAccounts;

    return 0;
}

// ==== Helper function definitions at bottom ====

int readInt(const string& prompt, int minVal, int maxVal) {
    while (true) {
        cout << prompt;
        int value;
        if (!(cin >> value)) {
            cout << "Invalid input. Please enter a whole number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (value < minVal || value > maxVal) {
            cout << "Value must be between " << minVal << " and " << maxVal << ".\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

int readIntMin(const string& prompt, int minVal) {
    while (true) {
        cout << prompt;
        int value;
        if (!(cin >> value)) {
            cout << "Invalid input. Please enter a whole number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (value < minVal) {
            cout << "Value must be at least " << minVal << ".\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

double readDoubleMin(const string& prompt, double minVal) {
    while (true) {
        cout << prompt;
        double value;
        if (!(cin >> value)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (value < minVal) {
            cout << "Value must be at least " << minVal << ".\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }
}

char readCharChoice(const string& prompt, const string& validOptions) {
    while (true) {
        cout << prompt;
        char c;
        if (!(cin >> c)) {
            cout << "Invalid input. Please enter a character.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (char v : validOptions) {
            if (c == v || c == (char)toupper(v)) {
                return c;
            }
        }
        cout << "Please enter one of: ";
        for (char v : validOptions) cout << v << "/" << (char)toupper(v) << " ";
        cout << "\n";
    }
}

int menudisplay() {
    cout << "\nMenu Options:\n";
    cout << "1. Create checking Account\n";
    cout << "2. Create savings Account\n";
    cout << "3. View Account Info\n";
    cout << "4. Modify or delete an account\n";
    cout << "5. Transfer between 2 accounts\n";
    cout << "6. Apply interest to a savings account\n";
    cout << "7. Exit\n";
    return readInt("Enter choice (1-7): ", 1, 7);
}

// Show all checking and savings accounts in table form
void showAllAccounts(CheckingAcc* checkingAccounts, SavingsAcc* savingsAccounts, int size) {
    bool anyChecking = false;
    bool anySavings = false;

    // Show all checking accounts
    for (int i = 0; i < size; ++i) {
        if (checkingAccounts[i].getAccountCustomer() != nullptr &&
            checkingAccounts[i].getID() != 0) {
            if (!anyChecking) {
                cout << "\n=== All Checking Accounts ===\n";
                Account::printTableHeader();
                anyChecking = true;
            }
            checkingAccounts[i].PrintInfo();
        }
    }
    if (anyChecking) {
        cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
    }
    else {
        cout << "\nNo checking accounts to display.\n";
    }

    // Show all savings accounts
    for (int i = 0; i < size; ++i) {
        if (savingsAccounts[i].getAccountCustomer() != nullptr &&
            savingsAccounts[i].getID() != 0) {
            if (!anySavings) {
                cout << "\n=== All Savings Accounts ===\n";
                Account::printTableHeader();
                anySavings = true;
            }
            savingsAccounts[i].PrintInfo();
        }
    }
    if (anySavings) {
        cout << "+----------------------------------------------------------------------------------------------------------------------+\n";
    }
    else {
        cout << "\nNo savings accounts to display.\n";
    }
}

// Generate a random 4-digit account ID (1000–9999)
int generateAccountID() {
    return 1000 + rand() % 9000;
}
