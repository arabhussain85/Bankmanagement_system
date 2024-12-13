#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
// #include <termios.h>

using namespace std;
class Login {
private:
    string username;
    string password;
public:
    Login(string username, string password) {
        this->username = username;
        this->password = password;
    }

    bool login_as_admin(string username, string password) {
        ifstream userFile("admins.csv");
        if (userFile.is_open()) {
            stringstream ss;
            string line;
            while (getline(userFile, line)) {
                ss << line;
                string user;
                getline(ss, user, ',');
                string pass;
                getline(ss, pass, ',');
                if (user == username && pass == password) {
                    return 1;
                }
                ss.clear();
            }
            userFile.close();
        }
        return 0;
    }

    bool login_as_customer(string username, string pincode) {
        ifstream userFile("pincode.csv");
        if (userFile.is_open()) {
            stringstream ss;
            string line;
            while (getline(userFile, line)) {
                ss << line;
                string user;
                getline(ss, user, ','); 
                string p;
                getline(ss, p, ',');
                if (user == username && p == pincode) {
                    return 1;
                }
                ss.clear();
            }
            userFile.close();
        }
        return 0;
    }

    bool login_as_atm(string username, string pincode) {
        ifstream userFile("pincode.csv");
        if (userFile.is_open()) {
            stringstream ss;
            string line;
            while (getline(userFile, line)) {
                ss << line;
                string user;
                getline(ss, user, ',');
                string p;
                getline(ss, p, ',');
                if (user == username && p == pincode) {
                    return 1;
                }
                ss.clear();
            }
            userFile.close();
        }
        return 0;
    }

};
