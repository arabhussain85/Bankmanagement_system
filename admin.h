#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

class Admin {
private:
    stack<string> tasks;
    queue<string> notifications;
    const string taskFile = "tasks.txt";
    const string notificationFile = "notifications.txt";

public:
    Admin() {
        loadTasks();
        loadNotifications();
    }

    ~Admin() {
        saveTasks();
        saveNotifications();
    }

    void addTask(const string& task) {
        tasks.push(task);
        cout << "Task added: " << task << endl;
    }

    void removeTask() {
        if (!tasks.empty()) {
            cout << "Task removed: " << tasks.top() << endl;
            tasks.pop();
        }
        else {
            cout << "No tasks to remove." << endl;
        }
    }

    void viewTask() {
        if (!tasks.empty()) {
            cout << "Most recent task: " << tasks.top() << endl;
        }
        else {
            cout << "No tasks to view." << endl;
        }
    }

    void addNotification(const string& notification) {
        notifications.push(notification);
        cout << "Notification added: " << notification << endl;
    }

    void processNotification() {
        if (!notifications.empty()) {
            cout << "Processing notification: " << notifications.front() << endl;
            notifications.pop();
        }
        else {
            cout << "No notifications to process." << endl;
        }
    }

    void viewNextNotification() {
        if (!notifications.empty()) {
            cout << "Next notification: " << notifications.front() << endl;
        }
        else {
            cout << "No notifications to view." << endl;
        }
    }

    // File handling methods
    void saveTasks() {
        ofstream outFile(taskFile);
        if (outFile.is_open()) {
            stack<string> temp = tasks;
            while (!temp.empty()) {
                outFile << temp.top() << endl;
                temp.pop();
            }
            outFile.close();
        }
        else {
            cerr << "Error: Unable to save tasks to file." << endl;
        }
    }

    void loadTasks() {
        ifstream inFile(taskFile);
        if (inFile.is_open()) {
            string line;
            stack<string> temp;
            while (getline(inFile, line)) {
                temp.push(line);
            }
            inFile.close();
            while (!temp.empty()) {
                tasks.push(temp.top());
                temp.pop();
            }
        }
    }

    void saveNotifications() {
        ofstream outFile(notificationFile);
        if (outFile.is_open()) {
            queue<string> temp = notifications;
            while (!temp.empty()) {
                outFile << temp.front() << endl;
                temp.pop();
            }
            outFile.close();
        }
        else {
            cerr << "Error: Unable to save notifications to file." << endl;
        }
    }

    void loadNotifications() {
        ifstream inFile(notificationFile);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                notifications.push(line);
            }
            inFile.close();
        }
    }
};
