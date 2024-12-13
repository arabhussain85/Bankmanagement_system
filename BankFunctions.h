#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <unordered_map>

using namespace std;

class BankFunctions {
private:
    string accountNumber;
    string customerName;
    double balance;
    string accountType;

public:
    // Default constructor
    BankFunctions() : accountNumber(""), customerName(""), balance(0.0), accountType("") {}

    // Constructor with arguments
    BankFunctions(string accNum, string custName, double initialBalance, string accType)
        : accountNumber(accNum), customerName(custName), balance(initialBalance), accountType(accType) {}

    // Deposit funds (updates the file)
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            updateAccountInFile(accountNumber, balance);
            cout << "Deposited: $" << fixed << setprecision(2) << amount << ". New balance: $" << balance << endl;
        }
        else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    // Transfer funds to another account
    void transferFunds(const string& recipientID, double amount) {
        if (amount > 0 && amount <= balance) {
            unordered_map<string, BankFunctions> accounts = loadAccountsFromFile();

            if (accounts.find(recipientID) != accounts.end()) {
                balance -= amount;
                accounts[recipientID].balance += amount;

                // Update balances in the file
                updateAccountInFile(accountNumber, balance);
                updateAccountInFile(recipientID, accounts[recipientID].balance);

                cout << "Transferred $" << fixed << setprecision(2) << amount
                    << " to Account ID: " << recipientID << ". New balance: $" << balance << endl;
            }
            else {
                cout << "Recipient account not found." << endl;
            }
        }
        else {
            cout << "Invalid transfer amount or insufficient balance." << endl;
        }
    }

    // View account details
    void viewBalance() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    // Load accounts from CSV file into a map
    static unordered_map<string, BankFunctions> loadAccountsFromFile() {
        unordered_map<string, BankFunctions> accounts;
        ifstream file("accounts.csv");
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string accNum, custName, accType, balanceStr;
                getline(ss, accNum, ',');
                getline(ss, custName, ',');
                getline(ss, accType, ',');
                getline(ss, balanceStr, ',');

                double balance = stod(balanceStr);
                accounts[accNum] = BankFunctions(accNum, custName, balance, accType);
            }
            file.close();
        }
        return accounts;
    }

    // Update the balance for a specific account in the CSV file
    static void updateAccountInFile(const string& accNum, double newBalance) {
        unordered_map<string, BankFunctions> accounts = loadAccountsFromFile();

        if (accounts.find(accNum) != accounts.end()) {
            accounts[accNum].balance = newBalance;

            ofstream file("accounts.csv");
            if (file.is_open()) {
                for (const auto& account : accounts) {
                    file << account.second.accountNumber << ","
                        << account.second.customerName << ","
                        << account.second.accountType << ","
                        << fixed << setprecision(2) << account.second.balance << endl;
                }
                file.close();
            }
            else {
                cout << "Error opening accounts.csv for writing." << endl;
            }
        }
        else {
            cout << "Account not found for update." << endl;
        }
    }

    // Function to check if a string is a valid number
    static bool isValidNumber(const string& str) {
        stringstream ss(str);
        double num;
        char c;
        if (ss >> num && !(ss >> c)) {
            return true;
        }
        return false;
    }
};

// Main user menu logic
#pragma once
