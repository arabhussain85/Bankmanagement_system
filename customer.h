#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
using namespace std;

class Customer
{
public:
    string name;
    string username;
    string password;
    string accountType;
    double balance;
    string pincode;
    string accountNumber;
    Customer* next;
    Customer();
    Customer(const string& name, const string& username, const string& password,
        const string& accountType, double balance, const string& pincode, const string& accountNumber);
};

Customer* customerHead = nullptr;

void loadCustomersFromFile();
void saveCustomersToFile();
void addCustomer(const string& name, const string& username, const string& password,
    const string& accountType, double balance, const string& pincode, string& accountNumber);
Customer* searchCustomerByUsername(const string& username);
bool removeCustomerByUsername(const string& username);
void displayCustomerDetails(Customer* customer);
void displayAllCustomers();
bool modifyCustomer(const string& username);

Customer::Customer() : name(""), username(""), password(""), accountType(""), balance(0.0), pincode(""), accountNumber(""), next(nullptr) {}

Customer::Customer(const string& name, const string& username, const string& password,
    const string& accountType, double balance, const string& pincode, const string& accountNumber)
    : name(name), username(username), password(password), accountType(accountType),
    balance(balance), pincode(pincode), accountNumber(accountNumber), next(nullptr) {}

bool isUsernameExists(const string& username) {
    ifstream customersFile("customersdata.csv");
    if (!customersFile.is_open()) {
        throw runtime_error("Failed to open customersdata.csv file.");
    }
    string line, existingUsername;
    while (getline(customersFile, line)) {
        size_t pos = line.find(',');
        if (pos != string::npos) {
            existingUsername = line.substr(0, pos); // Assuming username is the first field in the line
            if (existingUsername == username) {
                customersFile.close();
                return true;
            }
        }
    }
    customersFile.close();
    return false;
}
void addCustomer(const string& name, const string& username, const string& password,
    const string& accountType, double balance, const string& pincode, string& accountNumber) {
    try {
        
        if (name.empty() || username.empty() || password.empty() || accountType.empty()) {
            throw invalid_argument("Input fields cannot be empty.");
        }
        if (accountType != "savings" && accountType != "current") {
            throw invalid_argument("Account type must be either 'savings' or 'current'.");
        }
        if (balance <= 0) {
            throw invalid_argument("Balance must be greater than zero.");
        }
        if (isUsernameExists(username)) {
            throw invalid_argument("A user with this username already exists.");
        }
        srand(time(0));
        accountNumber = "ACC" + to_string(rand() % 1000000);
        string pin = to_string(rand() % 9000 + 1000);

        Customer* newCustomer = new Customer(name, username, password, accountType, balance, pin, accountNumber);
        newCustomer->next = customerHead;
        customerHead = newCustomer;

        saveCustomersToFile();
        ofstream pinFile("pincode.csv", ios::app);
        if (!pinFile.is_open()) {
            throw runtime_error("Failed to open pincode.csv file.");
        }
        pinFile << username << "," << pin << endl;
        pinFile.close();

        cout << "\n\t\t\t\t  Customer Added Successfully with Account Number: " << accountNumber
            << " and pincode: " << pin;
        cout << "\t\t\t\t\t\t\t\t\t\tPRESS ENTER TO CONTINUE........." << endl;
        cin.get();

    }
    catch (const exception& e) {
        cerr << "\nError: " << e.what() << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "\t\t\t\t\t\tPRESS ENTER TO RETURN TO MENU........." << endl;
        cin.get();
    }
}

void loadCustomersFromFile()
{
    ifstream inputFile("customerdata.csv");
    string line;
    while (getline(inputFile, line))
    {
        string name, username, password, accountType, pincode, accountNumber;
        double balance;
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, accountType, ',');
        getline(ss, pincode, ',');
        getline(ss, accountNumber, ',');
        ss >> balance;
        addCustomer(name, username, password, accountType, balance, pincode, accountNumber);
    }
    inputFile.close();
}

void saveCustomersToFile()
{
    ofstream outputFile("customerdata.csv", ios::trunc);
    Customer* current = customerHead;
    while (current != nullptr)
    {
        outputFile << current->username<<","
            << current->password << ","
            << current->accountType << ","
            << current->pincode << ","
            << current->accountNumber << ","
            << fixed << setprecision(2) << current->balance << endl;
        current = current->next;
    }
    outputFile.close();
}

bool removeCustomerByUsername(const string& username)
{
    Customer* current = customerHead;
    Customer* previous = nullptr;
    while (current != nullptr)
    {
        if (current->username == username)
        {
            if (previous == nullptr)
            {
                customerHead = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            delete current;
            saveCustomersToFile();
            cout << "\n\t\t\t\t  Customer Removed Successfully!" << endl;
            cout << "\t\t\t\t\t\t\t\t\t\tPRESS ENTER TO CONTINUE........." << endl;
            cin.get();
            return true;
        }
        previous = current;
        current = current->next;
    }
    cout << "\n\t\t\t\t  Customer Not Found!" << endl;
    return false;
}

Customer* searchCustomerByUsername(const string& username)
{
    Customer* current = customerHead;
    while (current != nullptr)
    {
        if (current->username == username)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void displayCustomerDetails(Customer* customer)
{
    if (customer == nullptr)
    {
        cout << "\n\t\t\t\t  Customer Not Found!" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\tPRESS ENTER TO CONTINUE........." << endl;
        cin.get();
        return;
    }
    cout << "\n\t\t\t\t  Customer Details" << endl;
    cout << "\t\t\t\t  ---------------------------" << endl;
    cout << "\t\t\t\t  Name: " << customer->name << endl;
    cout << "\t\t\t\t  Username: " << customer->username << endl;
    cout << "\t\t\t\t  Account Type: " << customer->accountType << endl;
    cout << "\t\t\t\t  Balance: $" << fixed << setprecision(2) << customer->balance << endl;
    cout << "\t\t\t\t  Account Number: " << customer->accountNumber << endl;
    cout << "\t\t\t\t  ---------------------------" << endl;

}

void displayAllCustomers()
{
    if (customerHead == nullptr)
    {
        cout << "\n\t\t\t\t  No Customers Available!" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\tPRESS ENTER TO CONTINUE........." << endl;
        cin.get();
        return;
    }
    Customer* current = customerHead;
    cout << "\n\t\t\t\t  All Customers" << endl;
    cout << "\t\t\t\t  -----------------------------------------" << endl;
    cout << left << setw(25) << "Name" << setw(25) << "Username" << setw(25) << "Account Type" << setw(15) << "Balance" << endl;
    cout << "\t\t\t\t  -----------------------------------------" << endl;
    while (current != nullptr)
    {
        cout << left << setw(25) << current->name
            << setw(25) << current->username
            << setw(25) << current->accountType
            << setw(15) << fixed << setprecision(2) << current->balance
            << endl;
        current = current->next;
    }
    cout << "\t\t\t\t  -----------------------------------------" << endl;
}


void makeComplaint(const string& username, const string& complaint)
{
    ofstream complaintFile("notifications.txt", ios::app);
    if (!complaintFile.is_open())
    {
        cout << "\n\t\t\t\t  Unable to open notifications file!" << endl;
        return;
    }
    complaintFile << "Complaint from " << username << ":\n" << complaint << "\n\n";
    complaintFile.close();
    cout << "\n\t\t\t\t  Complaint Registered Successfully!" << endl;
}
bool modifyCustomer(const string& username)
{
    Customer* customer = searchCustomerByUsername(username);
    if (customer == nullptr)
    {
        cout << "\n\t\t\t\t  Customer Not Found!" << endl;
        return false;
    }
    char choice;
    cout << "\n\t\t\t\t  What would you like to modify?" << endl;
    cout << "\n\t\t\t\t  1. Password" << endl;
    cout << "\n\t\t\t\t  2. Account Type" << endl;
    cout << "\n\t\t\t\t  3. Balance" << endl;
    cout << "\n\t\t\t\t  Enter your choice: ";
    choice = _getch();
    switch (choice)
    {
    case '1':
    {
        string newPassword;
        cout << "\n\t\t\t\t  Enter New Password: ";
        cin >> newPassword;
        customer->password = newPassword;
        saveCustomersToFile();
        cout << "\n\t\t\t\t  Password Updated Successfully!" << endl;
        break;
    }
    case '2':
    {
        string newAccountType;
        cout << "\n\t\t\t\t  Enter New Account Type (Savings/Current): ";
        cin >> newAccountType;
        customer->accountType = newAccountType;
        saveCustomersToFile();
        cout << "\n\t\t\t\t  Account Type Updated Successfully!" << endl;
        break;
    }
    case '3':
    {
        double newBalance;
        cout << "\n\t\t\t\t  Enter New Balance: $";
        cin >> newBalance;
        customer->balance = newBalance;
        saveCustomersToFile();
        cout << "\n\t\t\t\t  Balance Updated Successfully!" << endl;
        break;
    }
    default:
        cout << "\n\t\t\t\t  Invalid Choice!" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\tPRESS ENTER TO CONTINUE........." << endl;
        cin.get();
    }
    return true;
}
#pragma once
