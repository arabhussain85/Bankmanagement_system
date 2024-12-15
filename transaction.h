#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <limits> // For numeric_limits
#include <chrono>
#include <ctime>

using namespace std;

void updateCustomerBalance(const string& username, double newBalance)
{
    string line;
    vector<string> fileData; // To store all lines of the file
    bool found = false;

    ifstream inputFile("customerdata.csv"); // Adjust the path if necessary
    if (!inputFile.is_open())
    {
        cerr << "Error opening customer file." << endl;
        return;
    }

    // Read file line by line
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ','))
        {
            tokens.push_back(token);
        }

        // Check if this is the user we need to update
        if (tokens.size() >= 6 && tokens[0] == username)
        {
            // Update the balance
            double currentBalance = stod(tokens[5]);            // Balance is the 7th field
            tokens[5] = to_string(currentBalance + newBalance); // Update balance
            found = true;
        }

        // Reconstruct the line
        string updatedLine = tokens[0];
        for (size_t i = 1; i < tokens.size(); i++)
        {
            updatedLine += "," + tokens[i];
        }
        fileData.push_back(updatedLine);
    }

    inputFile.close();

    if (!found)
    {
        cerr << "Customer not found in file." << endl;
        return;
    }

    // Write back updated data to the file
    ofstream outputFile("customerdata.csv", ios::trunc);
    if (!outputFile.is_open())
    {
        cerr << "Error opening customer file for writing." << endl;
        return;
    }

    for (const auto& line : fileData)
    {
        outputFile << line << endl;
    }

    outputFile.close();
}

class Transaction
{
public:
    string transactionID;
    string username;
    double amount;
    string event;
    string date;

    Transaction(string tID, string uname, double amt, string event, string buffer)
        : transactionID(tID), username(uname), amount(amt), event(event), date(buffer) {}

    void displayTransaction() const
    {
        cout << "\nTransaction ID: " << transactionID
            << "\nUsername: " << username
            << "\nAmount: $" << fixed << setprecision(2) << amount
            << "\nType: " << event
            << "\nDate & Time: " << date
            << "\n-----------------------------------" << endl;
    }
};

class TransactionManager
{
private:
    vector<Transaction> transactions;
    int transactionCounter = 100; // Initialized to 1000 for unique transaction IDs

public:
    TransactionManager()
    {
        loadTransactionCounter(); // Load counter on initialization
    }

    // Function to add a transaction
    void addTransaction(string tID, string uname, double amt, string event)
    {
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);
        char buffer[100];
        

        Transaction newTransaction(tID, uname, amt, event, buffer);
        transactions.push_back(newTransaction);
        saveTransactionsToFile();
        cout << "\nTransaction Successful! Transaction ID: " << tID << endl;
    }

    // Function to handle deposits
    void deposit(string username)
    {
        double amount;

        cout << "Enter Deposit Amount: $";
        while (!(cin >> amount) || amount <= 0)
        {
            cout << "Invalid amount. Please enter a positive value: $";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(); // Clear buffer

        addTransaction(generateTransactionID(), username, amount, "Deposit");

        updateCustomerBalance(username, amount);
    }

    // Function to handle withdrawals
    void withdrawAmount(string usernameToSearch)
    {
        string filePath = "customerdata.csv";
        double withdrawAmount;

        cout << usernameToSearch;

        // Input username and amount to withdraw
        cout << "Enter the amount to withdraw: $";
        cin >> withdrawAmount;

        if (withdrawAmount <= 0)
        {
            cout << "Error: Withdrawal amount must be greater than zero!" << endl;
            return;
        }

        // Open the file for reading and writing
        ifstream inputFile(filePath);
        if (!inputFile)
        {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        stringstream updatedData;
        string line;
        bool userFound = false;

        // Process the file line by line
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string username, password, accountType, pin, accountNumber;
            double balance;

            // Parse the line
            getline(ss, username, ',');      // 1st field
            getline(ss, password, ',');      // 2nd field
            getline(ss, accountType, ',');   // 3rd field
            getline(ss, pin, ',');           // 4th field
            getline(ss, accountNumber, ','); // 5th field
            ss >> balance;                   // 6th field

            if (username == usernameToSearch)
            {
                userFound = true;

                // Check if sufficient balance exists
                if (balance >= withdrawAmount)
                {
                    balance -= withdrawAmount;
                    cout << "Withdrawal successful!" << endl;
                    cout << "Remaining Balance: $" << balance << endl;
                    addTransaction(generateTransactionID(), username, withdrawAmount, "WithDrawal");
                }
                else
                {
                    cout << "Error: Insufficient balance!" << endl;
                    return; // Exit without updating the file
                }
            }

            updatedData << username << ","
                << password << ","
                << accountType << ","
                << pin << ","
                << accountNumber << ","
                << fixed << setprecision(2) << balance << endl;
        }

        inputFile.close();

        // If the user was not found, show an error
        if (!userFound)
        {
            cout << "Error: User with username '" << usernameToSearch << "' not found!" << endl;
            return;
        }

        // Write the updated data back to the file
        ofstream outputFile(filePath, ios::trunc);
        if (!outputFile)
        {
            cout << "Error: Unable to write to file!" << endl;
            return;
        }

        outputFile << updatedData.str();
        outputFile.close();
    }

    void transferMoney(string senderName)
    {
        string filePath = "customerdata.csv";
        string receiverAcc;
        double amount;
        vector<string> lines;
        bool senderFound = false, receiverFound = false;
        double senderBalance = 0, receiverBalance = 0;
        string senderAccountNumber;

        // Input details
        cout << "Enter receiver's account number: ";
        cin >> receiverAcc;
        cout << "Enter amount to transfer: $";
        cin >> amount;

        // Open the file for reading
        ifstream inputFile(filePath);
        if (!inputFile)
        {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        // Read and process the file line by line
        string line;
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string username, password, accountType, pin, accountNumber;
            double balance;

            // Parse the line
            getline(ss, username, ',');      // 1st field
            getline(ss, password, ',');      // 2nd field
            getline(ss, accountType, ',');   // 3rd field
            getline(ss, pin, ',');           // 4th field
            getline(ss, accountNumber, ','); // 5th field
            ss >> balance;                   // 6th field

            // Check if it's the sender
            if (username == senderName)
            {
                senderFound = true;
                senderAccountNumber = accountNumber;
                if (balance < amount)
                {
                    cout << "Error: Insufficient balance in sender's account!" << endl;
                    return;
                }
                senderBalance = balance - amount; // Deduct amount
                line = username + "," + password + "," + accountType + "," + pin + "," + accountNumber + "," + to_string(senderBalance);
            }

            // Check if it's the receiver
            if (accountNumber == receiverAcc)
            {
                receiverFound = true;
                receiverBalance = balance + amount; // Add amount
                line = username + "," + password + "," + accountType + "," + pin + "," + accountNumber + "," + to_string(receiverBalance);
            }

            // Store the updated line
            lines.push_back(line);
        }

        inputFile.close();

        // Ensure both accounts were found
        if (!senderFound)
        {
            cout << "Error: Sender with name '" << senderName << "' not found!" << endl;
            return;
        }
        if (!receiverFound)
        {
            cout << "Error: Receiver account number '" << receiverAcc << "' not found!" << endl;
            return;
        }

        // Write updated data back to the file
        ofstream outputFile(filePath, ios::trunc);
        for (const auto& updatedLine : lines)
        {
            outputFile << updatedLine << endl;
        }
        outputFile.close();

        cout << "Transaction successful! $" << amount << " transferred from "
            << senderAccountNumber << " to " << receiverAcc << "." << endl;
        addTransaction(generateTransactionID(), senderName, amount, "MoneyTransfer to " + receiverAcc);
    }
    // Function to load transactions from a file
    void loadTransactionsFromFile()
    {
        ifstream inputFile("transactions.csv");
        string line;
        while (getline(inputFile, line))
        {
            string tID, uname, event, buffer;
            double amt;
            stringstream ss(line);
            getline(ss, tID, ',');
            getline(ss, uname, ',');
            ss >> amt;
            ss.ignore(1, ','); // Ignore the comma
            getline(ss, event, ',');
            getline(ss, buffer, ',');

            Transaction newTransaction(tID, uname, amt, event, buffer);
            transactions.push_back(newTransaction);
        }
        inputFile.close();
    }

    // Function to save all transactions to a file
    void saveTransactionsToFile() const
    {
        ofstream outputFile("transactions.csv", ios::trunc);
        for (const auto& transaction : transactions)
        {
            outputFile << transaction.transactionID << ","
                << transaction.username << ","
                << fixed << setprecision(2) << transaction.amount << ","
                << transaction.event << ","
                << transaction.date << endl;
        }
        outputFile.close();
    }

    // Function to display all transactions for a specific user
    void displayTransactionsForUser(const string& username) const
    {
        cout << "\nTransactions for " << username << ":\n";
        bool found = false;
        for (const auto& transaction : transactions)
        {
            if (transaction.username == username)
            {
                transaction.displayTransaction();
                found = true;
            }
        }
        if (!found)
        {
            cout << "\nNo transactions found for this user.\n";
        }
    }

    // Function to display all transactions
    void displayAllTransactions() const
    {
        if (transactions.empty())
        {
            cout << "\nNo transactions available.\n";
        }
        else
        {
            for (const auto& transaction : transactions)
            {
                transaction.displayTransaction();
            }
        }
    }

    // Function to generate a unique transaction ID
    string generateTransactionID()
    {
        return "TXN" + to_string(transactionCounter++);
    }

    // Load the transaction counter from a file
    void loadTransactionCounter()
    {
        ifstream counterFile("transaction_counter.txt");
        if (counterFile.is_open())
        {
            counterFile >> transactionCounter;
        }
        counterFile.close();
    }

    void showBalance(string nameToSearch)
    {
        string filePath = "customerdata.csv";
        // Open the file for reading
        ifstream inputFile(filePath);
        if (!inputFile)
        {
            cout << "Error: Unable to open file!" << endl;
            return;
        }

        string line;
        bool userFound = false;

        // Read and process the file line by line
        while (getline(inputFile, line))
        {
            stringstream ss(line);
            string username, password, accountType, pin, accountNumber;
            double balance;

            // Parse the line
            getline(ss, username, ',');      // 1st field
            getline(ss, password, ',');      // 2nd field
            getline(ss, accountType, ',');   // 3rd field
            getline(ss, pin, ',');           // 4th field
            getline(ss, accountNumber, ','); // 5th field
            ss >> balance;                   // 6th field

            // Check if the name matches
            if (username == nameToSearch)
            {
                userFound = true;
                cout << "Account Holder: " << username << endl;
                cout << "Account Number: " << accountNumber << endl;
                cout << "Balance: $" << balance << endl;
                break;
            }
        }

        inputFile.close();

        if (!userFound)
        {
            cout << "Error: User with name '" << nameToSearch << "' not found!" << endl;
        }
    }
    // Save the transaction counter to a file
    void saveTransactionCounter() const
    {
        ofstream counterFile("transaction_counter.txt", ios::trunc);
        counterFile << transactionCounter;
        counterFile.close();
    }

    ~TransactionManager()
    {
        saveTransactionCounter(); // Save counter on destruction
    }
};

void handleTransactions()
{
    TransactionManager transactionManager;
    transactionManager.loadTransactionsFromFile();

    string username;
    char choice;

    do
    {
        cout << "\nTransaction Menu:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. View Transactions for User\n";
        cout << "4. View All Transactions\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            cout << "\nEnter Username: ";
            cin >> username;
            transactionManager.deposit(username);
            break;
        case '2':
            cout << "\nEnter Username: ";
            cin >> username;
            transactionManager.withdrawAmount(username);
            break;
        case '3':
            cout << "\nEnter Username to View Transactions: ";
            cin >> username;
            transactionManager.displayTransactionsForUser(username);
            break;
        case '4':
            transactionManager.displayAllTransactions();
            break;
        case '5':
            cout << "\nExiting Transaction Menu...\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

        if (choice != '5')
        {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != '5');
}
