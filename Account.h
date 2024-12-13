#include <iostream>
#include <string>

using namespace std;

class Account {
private:
	int accountNumber;
	string accountHolderName;
	string fatherName;
	string motherName;
	string cnic;
	string address;
	string phonenumber;
	string email;
	double balance;
	string accountType;
	string branchName;

public:
	Account(int accountNumber, string accountHolderName, string fatherName, string motherName, string cnic, string address, string phoneNumber, string email, double balance, string accountType, string branchName) {
		this->accountNumber = accountNumber;
		this->accountHolderName = accountHolderName;
		this->fatherName = fatherName;
		this->motherName = motherName;
		this->cnic = cnic;
		this->address = address;
		this->phonenumber = phoneNumber;
		this->email = email;
		this->balance = balance;
		this->branchName = branchName;
	}
	void deposit(double amount) {
		balance += amount;
	}
	void withdraw(double amount) {
		if (balance >= amount) {
			balance -= amount;
		}
		else {
			cout << "insuffiecient balance" << endl;
		}
	}

	double getbalance() {
		return balance;
	}

	void displayAccountInfo() {
		cout << "Account Number: "<<accountNumber << endl;
		cout << "Account Holder: " << accountHolderName << endl;
		cout << "Father name: " << fatherName << endl;
		cout << "Mother name: " << motherName << endl;
		cout << "CNIC: " << cnic << endl;
		cout << "Email: " << email << endl;
		cout << "Balance: " << endl;
		cout << "Account Type: " << accountType << endl;
		cout << "Branch name: " << branchName << endl;

	}
	void updateAccountInfo(string accountHolderName, string fatherName, string motherName, string cnic, string address, string phoneNumber, string email) {
		this->accountHolderName = accountHolderName;
		this->fatherName = fatherName;
		this->motherName = motherName;
		this->cnic = cnic;
		this->address = address;
		this->phonenumber = phoneNumber;
		this->email = email;
	}
};