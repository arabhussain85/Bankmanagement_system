#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <chrono>
#include <thread>

#include "login.h"
#include "customer.h"
#include "Transaction.h"
#include "admin.h"

using namespace std;


#define RESET "\033[0m"
#define BOLD "\033[1m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define WHITE "\033[37m"
#define RED "\033[31m"


void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void centerText(const string& text) {
    int screenWidth = 80;
    int padding = (screenWidth - text.length()) / 2;
    for (int i = 0; i < padding; ++i) cout << " ";
    cout << text << endl;
}
void loadingScreen(const string& message = "Loading...") {
    const int barWidth = 50; // Width of the progress bar
    const string progressChars = "|/-\\";  // Animation characters

    cout << "\033[2J\033[1;1H";  // Clear screen
    cout << "\033[1;34m" << message << "\033[0m" << endl;  // Display message in blue

    for (int i = 0; i <= barWidth; ++i) {
        // Animation of the loading bar
        int pos = i;
        string progressBar = "[";

        // Filling the progress bar with '='
        for (int j = 0; j < pos; ++j) progressBar += "=";
        for (int j = pos; j < barWidth; ++j) progressBar += " ";
        progressBar += "]";

        // Display progress with the current character animation
        cout << progressBar << " " << int((pos * 100) / barWidth) << "% "
            << progressChars[i % 4] << "\r";  // Switch the animation character
        cout.flush();

        // Delay for effect
        std::this_thread::sleep_for(std::chrono::milliseconds(12));  // Adjust for speed
    }


    // Short pause before clearing the screen
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    cout << "\033[2J\033[1;1H";  // Clear screen after loading
}
char singleInput() {
    
    char ch = _getch(); 
    std::cout << ch << std::endl;
    return ch;
}


void displayBanner() {
    // Bank Management System Title with ASCII Art
    cout << CYAN << BOLD;
    cout << "=============================================================\n";
    cout << " __        __         _                                      \n";
    cout << " \\ \\      / /   ___  | |   ___    ___    _ __    ___   _ __  \n";
    cout << "  \\ \\ /\\ / /   / _ \\ | |  / __|  / _ \\  | '__|  / _ \\ | '__| \n";
    cout << "   \\ V  V /   |  __/ | | | (__  | (_) | | |    |  __/ | |    \n";
    cout << "    \\_/\\_/     \\___| |_|  \\___|  \\___/  |_|     \\___| |_|    \n";
    cout << "=============================================================\n";


    // BMS in Colorful ASCII Art
    cout << RED << "   BBBBB   M   M   SSSSS   \n";
    cout << RED << "   B    B  MM MM  S        \n";
    cout << GREEN << "   BBBBB   M M M  SSSSS    \n";
    cout << GREEN << "   B    B  M   M      S    \n";
    cout << CYAN << "   BBBBB   M   M   SSSSS   \n";
    cout << "=============================================================\n";

    // Adding the group members' names and roll numbers
    centerText(YELLOW "Group Members: " RESET);
    centerText(CYAN "1. ARAB HUSSAIN     - Roll Number: 23021519-099" RESET);
    centerText(CYAN "2. ABDULLAH NAEEM   - Roll Number: 230121519-088" RESET);

    cout << CYAN << BOLD;
    cout << "=============================================================\n";
    cout << RESET;

    // Stylish separator line with star decoration
    cout << YELLOW << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n" RESET;

    // Prompt to continue
    centerText(YELLOW "Press Enter to continue..." RESET);
    cin.get();
}
string getMaskedPassword() {
    string password;
    char ch;
    while (true) {
        ch = _getch();
        if (ch == '\r') {
            cout << endl;
            break;
        }
        else if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password.push_back(ch);
            cout << '*';
        }
    }
    return password;
}


void displayMenu() {
    clearScreen();
    cout << CYAN << BOLD;
    loadingScreen();

    // Stylish Header with more space
    cout << endl << MAGENTA << BOLD << "+----------------------------------------------------------+" << RESET << endl;
    cout << MAGENTA << BOLD << "|                                                          |" << RESET << endl;
    cout << MAGENTA << BOLD << "|          " << CYAN << BOLD << "   WELCOME TO THE MAIN MENU   " << MAGENTA << "             |" << RESET << endl;
    cout << MAGENTA << BOLD << "|                                                          |" << RESET << endl;
    cout << MAGENTA << BOLD << "+----------------------------------------------------------+" << RESET << endl;

    // Only essential menu options
    cout << endl;
    cout << YELLOW << "|  " << BLUE << "1." << RESET << " " << BOLD << "Login as Admin" << RESET << "                " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "2." << RESET << " " << BOLD << "Login as Customer" << RESET << "             " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "3." << RESET << " " << BOLD << "Login as ATM User" << RESET << "             " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "4." << RESET << " " << BOLD << "Exit" << RESET << "                          " << YELLOW << "|" << endl;

    // Bottom border with filled dashes
    cout << endl;
    cout << MAGENTA << BOLD << "+----------------------------------------------------------+" << RESET << endl;
    cout << endl;
    cout << CYAN << "Please select an option (1-4): " << RESET;
}

void displayAdminMenu() {
    clearScreen();
    loadingScreen();

    // Stylish Header with a more spacious and elegant appearance
    cout << endl << MAGENTA << BOLD << "+----------------------------------------------------------+" << RESET << endl;
    cout << MAGENTA << BOLD << "|                                                          |" << RESET << endl;
    cout << MAGENTA << BOLD << "|         " << CYAN << BOLD << "     ADMIN MENU         " << MAGENTA << "               |" << RESET << endl;
    cout << MAGENTA << BOLD << "|                                                          |" << RESET << endl;
    cout << MAGENTA << BOLD << "+----------------------------------------------------------+" << RESET << endl;

    // Adding a gap before the menu options
    cout << endl;

    // Menu options with improved alignment and visual hierarchy
    cout << YELLOW << "|  " << BLUE << "1." << RESET << " " << BOLD << "Add New Customer" << RESET << "                " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "2." << RESET << " " << BOLD << "Remove Customer" << RESET << "                 " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "3." << RESET << " " << BOLD << "Modify Customer" << RESET << "                 " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "4." << RESET << " " << BOLD << "Update Customer Details" << RESET << "         " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "5." << RESET << " " << BOLD << "Display All Customers" << RESET << "           " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "6." << RESET << " " << BOLD << "Deposit Funds" << RESET << "                   " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "7." << RESET << " " << BOLD << "View Transaction History" << RESET << "        " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "8." << RESET << " " << BOLD << "Withdraw Funds" << RESET << "                  " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "9." << RESET << " " << BOLD << "Manage Admin Tasks" << RESET << "              " << YELLOW << "|" << endl;
    cout << YELLOW << "|  " << BLUE << "e." << RESET << " " << BOLD << "Log Out" << RESET << "                        " << YELLOW << "|" << endl;

    // Bottom border with enhanced design for a more polished look
    cout << endl;
    cout << MAGENTA << BOLD << "+----------------------------------------------------------+" << RESET << endl;
    cout << endl;

    // A more distinct prompt for user selection
    cout << CYAN << BOLD << "Please select an option (1-10): " << RESET;
}

void adminActions() {
    char adminChoice;
    do {
        displayAdminMenu();
        TransactionManager admin;
        Admin admin1;
        cout << "\nEnter your choice: ";
        adminChoice = singleInput();
        

        string username;

        switch (adminChoice) {
        case '1': {
            string name, username, password, accountType, pincode, accountNumber;
            double balance;

            clearScreen();
            loadingScreen();

            centerText(BOLD BLUE "=== Add New Customer ===" RESET);
            cout << endl;
            cout << "----------------------------------------------------------" << endl;
            cout << "Enter Customer Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Customer Username: ";
            getline(cin, username);
            cout << "Enter Customer Password: ";
            password = getMaskedPassword();
            cout << "Enter Account Type (Savings/Current): ";
            getline(cin, accountType);
            cout << "Enter Initial Balance: $";
            cin >> balance;

            addCustomer(name, username, password, accountType, balance, pincode, accountNumber);
            cout << endl;
            _getch();
            break;
        }
        case '2': {
            clearScreen();
            loadingScreen();

            centerText(BOLD BLUE "=== Remove Customer ===" RESET);
            cout << "----------------------------------------------------------" << endl;
            cout << "Enter Customer Username to Remove: ";
            cin >> username;
            removeCustomerByUsername(username);
            cout << "Press any key to continue...";
            _getch();
            break;

        }
        case '3': {
            clearScreen();
            loadingScreen();

            centerText(BOLD BLUE "=== Modify Customer ===" RESET);
            cout << "----------------------------------------------------------" << endl;
            cout << "Enter Customer Username to Modify: ";
            cin >> username;
            modifyCustomer(username);
            break;
        }
        case '4': {
            clearScreen();
            loadingScreen();

            centerText(BOLD BLUE "=== Update Customer Details ===" RESET);
            cout << "----------------------------------------------------------" << endl;
            cout << "Enter Customer Username to Update: ";
            cin >> username;
            modifyCustomer(username);
            break;
        }
        case '5':
            clearScreen();
            loadingScreen();

            centerText(BOLD BLUE "=== Display All Customers ===" RESET);
            displayAllCustomers();
            break;
        case '6':
            clearScreen();
            loadingScreen();

            centerText(BOLD BLUE "=== Deposit Funds ===" RESET);
            cout << "----------------------------------------------------------" << endl;
            cout << "Enter Customer Username: ";
            cin >> username;
            admin.deposit(username);
            break;
        case '7':

            clearScreen();
            loadingScreen();

            centerText(BOLD BLUE "=== View Transaction History ===" RESET);
            cout << "----------------------------------------------------------" << endl;
            cout << "Enter Customer Username: ";
            cin >> username;
            admin.displayTransactionsForUser(username);
            break;
        case '8':
            clearScreen();
            loadingScreen();

            centerText(BOLD BLUE "=== Withdraw Funds ===" RESET);
            cout << "----------------------------------------------------------" << endl;
            cout << "Enter Customer Username: ";
            cin >> username;
            admin.withdrawAmount(username);
            break;
        case '9':
        {
            clearScreen();
            loadingScreen();

            centerText(BOLD BLUE "=== Manage Admin Tasks ===" RESET);
            cout << "----------------------------------------------------------" << endl;
            cout << "1. Add Task" << endl;
            cout << "2. Remove Task" << endl;
            cout << "3. View Most Recent Task" << endl;
            cout << "Enter your choice: ";
            char taskChoice;
            taskChoice = singleInput();
            
            switch (taskChoice) {
            case '1': {
                loadingScreen();

                cout << "----------------------------------------------------------" << endl;
                cout << "Enter task: ";
                string task;
                getline(cin, task);
                admin1.addTask(task);
                break;
            }
            case '2':
                loadingScreen();

                cout << "----------------------------------------------------------" << endl;
                admin1.removeTask();
                break;
            case '3':
                loadingScreen();

                cout << "----------------------------------------------------------" << endl;
                admin1.viewTask();
                break;
            default:
                centerText(RED "❌ Invalid choice. Please try again." RESET);
            }
            break;
        }

        case 'e':
            clearScreen();
            loadingScreen();

            centerText(CYAN "Logging out... Goodbye!" RESET);
            break;
        default:
            centerText(RED "❌ Invalid choice. Please try again." RESET);
        }

        if (adminChoice != 'e') {
            cout << endl << endl;
            centerText(BLUE "Press Enter to continue..." RESET);
            cin.get();
        }

    } while (adminChoice != 'e');
}



void customerActions(const string& username) {
    TransactionManager transactionManager;
    transactionManager.loadTransactionsFromFile();
    string complaint;

    char choice;
    do {
        clearScreen();
        centerText(BOLD BLUE "=== Customer Menu ===" RESET);
        cout << "\n----------------------------------------------------------" << endl;
        cout << "1. View Balance" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. View Transaction History" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. Add Complaint" << endl;
        cout << "6. Exit" << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << "\nEnter your choice: ";
        choice = singleInput();

        switch (choice) {
        case '1':
            clearScreen();
            transactionManager.showBalance(username);
            break;
        case '2':
            clearScreen();
            transactionManager.deposit(username);
            break;
        case '3':
            clearScreen();
            transactionManager.displayTransactionsForUser(username);
            break;
        case '4':
            clearScreen();
            transactionManager.transferMoney(username);
            break;
        case '5':
            clearScreen();
            centerText(BOLD YELLOW "=== Submit Complaint ===" RESET);
            cout << "\n----------------------------------------------------------" << endl;
            cout << "Enter the complaint you want to submit: ";
            cin.ignore(); // to clear the input buffer
            getline(cin, complaint);
            makeComplaint(username, complaint);
            cout << "\nComplaint submitted successfully!" << endl;
            break;
        case '6':
            clearScreen();
            centerText(BLUE "Exiting Customer Menu... Goodbye!" RESET);
            break;
        default:
            centerText(RED "❌ Invalid choice. Please try again." RESET);
        }

        if (choice != '6') {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != '6');
}


void atmActions() {
    TransactionManager transactionManager;
    transactionManager.loadTransactionsFromFile();

    char atmChoice;
    string username;

    // Request ATM username with clear instruction and space
    cout << "\n" << CYAN << BOLD << "Enter ATM Username: " << RESET;
    cin >> username;

    do {
        clearScreen();

        // Centered and bold title with color
        centerText(BOLD BLUE "=== ATM Menu ===" RESET);
        cout << "\n----------------------------------------------------------" << endl;

        // List options with proper spacing for readability
        cout << YELLOW << "1." << RESET << " " << BOLD << "View Balance" << RESET << endl;
        cout << YELLOW << "2." << RESET << " " << BOLD << "Withdraw" << RESET << endl;
        cout << YELLOW << "3." << RESET << " " << BOLD << "View Transaction History" << RESET << endl;
        cout << YELLOW << "4." << RESET << " " << BOLD << "Exit" << RESET << endl;

        cout << "----------------------------------------------------------" << endl;
        cout << "\n" << CYAN << "Enter your choice: " << RESET;
        atmChoice=singleInput();

        switch (atmChoice) {
        case '1':
            clearScreen();
            transactionManager.showBalance(username);
            break;
        case '2':
            clearScreen();
            transactionManager.withdrawAmount(username);
            break;
        case '3':
            clearScreen();
            transactionManager.displayTransactionsForUser(username);
            break;
        case '4':
            clearScreen();
            centerText(BLUE "Exiting ATM Menu... Goodbye!" RESET);
            break;
        default:
            clearScreen();
            centerText(RED "❌ Invalid choice. Please try again." RESET);
        }

        if (atmChoice != '4') {
            // Clear space for better user flow
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (atmChoice != 4);
}


int main() {
    clearScreen();
    displayBanner();

    char choice;
    do {
        clearScreen();
        cout << CYAN << BOLD;
        loadingScreen();

        // Stylish Header with more space
        cout << endl << MAGENTA << BOLD << "+----------------------------------------------------------+" << RESET << endl;
        cout << MAGENTA << BOLD << "|                                                          |" << RESET << endl;
        cout << MAGENTA << BOLD << "|          " << CYAN << BOLD << "   WELCOME TO THE MAIN MENU   " << MAGENTA << "             |" << RESET << endl;
        cout << MAGENTA << BOLD << "|                                                          |" << RESET << endl;
        cout << MAGENTA << BOLD << "+----------------------------------------------------------+" << RESET << endl;

        // Only essential menu options
        cout << endl;
        cout << YELLOW << "|  " << BLUE << "1." << RESET << " " << BOLD << "Login as Admin" << RESET << "                " << YELLOW << "|" << endl;
        cout << YELLOW << "|  " << BLUE << "2." << RESET << " " << BOLD << "Login as Customer" << RESET << "             " << YELLOW << "|" << endl;
        cout << YELLOW << "|  " << BLUE << "3." << RESET << " " << BOLD << "Login as ATM User" << RESET << "             " << YELLOW << "|" << endl;
        cout << YELLOW << "|  " << BLUE << "4." << RESET << " " << BOLD << "Exit" << RESET << "                          " << YELLOW << "|" << endl;

        // Bottom border with filled dashes
        cout << endl;
        cout << MAGENTA << BOLD << "+----------------------------------------------------------+" << RESET << endl;
        cout << endl;
        cout << CYAN << "Please select an option (1-4): " << RESET;
        choice = singleInput();
        

        switch (choice) {
        case '1': {
            string username, password;
            clearScreen();
            centerText(BOLD BLUE "=== Admin Login ===" RESET);  // Centered title for the section
            cout << endl;
            cout << MAGENTA << "Enter Admin Username: " << RESET;
            cin >> username;
            cout << MAGENTA << "Enter Admin Password: " << RESET;
            cin.ignore();
            password = getMaskedPassword();
            Login adminLogin(username, password);
            if (adminLogin.login_as_admin(username, password)) {
                clearScreen();
                centerText(GREEN "✔ Logged in as Admin successfully." RESET);  // Positive feedback
                adminActions();  // Navigate to Admin Menu after successful login
            }
            else {
                centerText(RED "❌ Invalid Admin credentials. Try again." RESET);  // Error feedback
            }
            break;
        }
        case '2': {
            string username, password;
            clearScreen();
            centerText(BOLD BLUE "=== Customer Login ===" RESET);  // Centered title for the section
            cout << endl;
            cout << MAGENTA << "Enter Customer Username: " << RESET;
            cin >> username;
            cout << MAGENTA << "Enter Customer Password: " << RESET;
            cin.ignore();
            password = getMaskedPassword();
            Login customerLogin(username, password);
            if (customerLogin.login_as_customer(username, password)) {
                clearScreen();
                centerText(GREEN "✔ Logged in as Customer successfully." RESET);  // Positive feedback
                customerActions(username);  // Navigate to Customer Menu after successful login
            }
            else {
                centerText(RED "❌ Invalid Customer credentials. Try again." RESET);  // Error feedback
            }
            break;
        }
        case '3': {
            string username, pin;
            clearScreen();
            centerText(BOLD BLUE "=== ATM Login ===" RESET);  // Centered title for the section
            cout << endl;
            cout << MAGENTA << "Enter ATM Username: " << RESET;
            cin >> username;
            cout << MAGENTA << "Enter ATM Pin: " << RESET;
            cin >> pin;
            Login atmLogin(username, pin);  // ATM login
            if (atmLogin.login_as_atm(username, pin)) {
                clearScreen();
                centerText(GREEN "✔ Logged in as ATM User successfully." RESET);  // Positive feedback
                atmActions();  // Navigate to ATM Menu after successful login
            }
            else {
                centerText(RED "❌ Invalid ATM credentials. Try again." RESET);  // Error feedback
            }
            break;
        }
        case '4':
            clearScreen();
            loadingScreen();
            centerText(CYAN "Exiting... Goodbye!" RESET);  // Exit message with positive color
            break;
        default:
            centerText(RED "❌ Invalid choice. Please try again." RESET); 
            centerText(CYAN "press enter to continue.... " RESET);
            cin.get();

            // Error feedback for invalid choices
        }

    } while (choice != '4');

    return 0;

}

