#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <limits>
#include <cstdlib> 
#include <fstream> // Library for file handling

using namespace std;

// --- COLOR CODES ---
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

class Reminder
{
    string heading;
    string details;
    string dueDate;
    bool isDone;

public:
    // Constructor
    Reminder(string h, string d, string date, bool status = false)
    {
        heading = h;
        details = d;
        dueDate = date;
        isDone = status;
    }

    string getHeading() { return heading; }
    string getDetails() { return details; }
    string getDueDate() { return dueDate; }
    bool getStatus() { return isDone; }

    void toggleStatus() { isDone = !isDone; }
};

class ReminderSystem
{
    vector<Reminder> reminders;
    const string filename = "reminders.txt";

public:
    // Constructor: Loads data immediately when app starts
    ReminderSystem() {
        loadFromFile();
    }

    // --- FILE HANDLING START ---
    
    void saveToFile()
    {
        ofstream file(filename);
        if (!file) return;

        // Format: 
        // Title
        // Details
        // Date
        // Status (0 or 1)
        for (size_t i = 0; i < reminders.size(); i++)
        {
            file << reminders[i].getHeading() << endl;
            file << reminders[i].getDetails() << endl;
            file << reminders[i].getDueDate() << endl;
            file << reminders[i].getStatus() << endl;
        }
        file.close();
    }

    void loadFromFile()
    {
        ifstream file(filename);
        if (!file) return;

        string h, d, date, statusStr;
        while (getline(file, h))
        {
            if (!getline(file, d)) break;
            if (!getline(file, date)) break;
            if (!getline(file, statusStr)) break;

            bool s = (statusStr == "1");
            reminders.push_back(Reminder(h, d, date, s));
        }
        file.close();
    }
    // --- FILE HANDLING END ---

    void clearScreen() {
        system("cls"); 
    }

    void printHeader() {
        cout << CYAN << "=======================================================" << RESET << endl;
        cout << BOLD << "      TASK & EVENT REMINDER SYSTEM (v3.0 Saved)       " << RESET << endl;
        cout << CYAN << "=======================================================" << RESET << endl;
    }

    void pause() {
        cout << "\n" << YELLOW << ">> Press Enter to continue..." << RESET;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    void createReminder()
    {
        clearScreen();
        printHeader();
        cout << "\n" << BOLD << "[ CREATE NEW REMINDER ]" << RESET << "\n";
        
        string h, d, date;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        cout << "Enter Title: ";
        getline(cin, h);

        cout << "Enter Details: ";
        getline(cin, d);

        while (true) {
            cout << "Enter Date (DD-MM-YYYY): ";
            getline(cin, date);
            regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-(20\d{2})$)");
            if (regex_match(date, pattern)) break;
            cout << RED << ">> Invalid date format! Try again." << RESET << "\n";
        }

        reminders.push_back(Reminder(h, d, date));
        saveToFile(); // SAVE AUTOMATICALLY
        cout << "\n" << GREEN << ">> SUCCESS! Reminder saved to file." << RESET << "\n";
        pause();
    }

    void showAll()
    {
        clearScreen();
        printHeader();
        cout << "\n" << BOLD << "[ YOUR LIST ]" << RESET << "\n";

        if (reminders.empty()) {
            cout << "\n" << RED << "   (List is empty)" << RESET << "\n";
            pause();
            return;
        }

        cout << "-------------------------------------------------------\n";
        for (size_t i = 0; i < reminders.size(); i++)
        {
            cout << " ID: " << BOLD << (i + 1) << RESET << " | " 
                 << "Date: " << reminders[i].getDueDate() << endl;
            
            cout << " " << CYAN << reminders[i].getHeading() << RESET << endl;
            cout << " Desc: " << reminders[i].getDetails() << endl;
            
            if (reminders[i].getStatus())
                cout << " Status: " << GREEN << "[ COMPLETED ]" << RESET << endl;
            else
                cout << " Status: " << RED << "[ PENDING ]" << RESET << endl;
            
            cout << "-------------------------------------------------------\n";
        }
        pause();
    }

    void toggleComplete()
    {
        clearScreen();
        printHeader();
        cout << "\n" << BOLD << "[ CHANGE STATUS ]" << RESET << "\n";
        
        if (reminders.empty()) {
            cout << RED << "List is empty." << RESET << endl;
            pause();
            return;
        }

        int id;
        cout << "Enter ID to toggle: ";
        cin >> id;

        if (id < 1 || id > (int)reminders.size()) {
            cout << RED << ">> Invalid ID!" << RESET << endl;
        } else {
            reminders[id - 1].toggleStatus();
            saveToFile(); // SAVE AUTOMATICALLY
            cout << GREEN << ">> Status Updated & Saved!" << RESET << endl;
        }
        pause();
    }

    void deleteReminder()
    {
        clearScreen();
        printHeader();
        cout << "\n" << BOLD << "[ DELETE REMINDER ]" << RESET << "\n";

        if (reminders.empty()) {
            cout << RED << "List is empty." << RESET << endl;
            pause();
            return;
        }

        int id;
        cout << "Enter ID to delete: ";
        cin >> id;

        if (id < 1 || id > (int)reminders.size()) {
            cout << RED << ">> Invalid ID!" << RESET << endl;
        } else {
            reminders.erase(reminders.begin() + (id - 1));
            saveToFile(); // SAVE AUTOMATICALLY
            cout << RED << ">> Deleted & Saved." << RESET << endl;
        }
        pause();
    }
};

int main()
{
    ReminderSystem app; // Constructor loads file automatically
    int choice;

    while (true)
    {
        app.clearScreen();
        app.printHeader();
        
        cout << "\n" << BOLD << "   MAIN MENU" << RESET << endl;
        cout << "   " << GREEN << "1." << RESET << " Add New Reminder" << endl;
        cout << "   " << GREEN << "2." << RESET << " View All Reminders" << endl;
        cout << "   " << GREEN << "3." << RESET << " Delete a Reminder" << endl;
        cout << "   " << GREEN << "4." << RESET << " Mark as Done/Pending" << endl;
        cout << "   " << RED   << "5. Exit" << RESET << endl;
        cout << "\n=======================================================" << endl;
        cout << "Select Option: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1: app.createReminder(); break;
        case 2: app.showAll(); break;
        case 3: app.deleteReminder(); break;
        case 4: app.toggleComplete(); break;
        case 5: return 0;
        default: break;
        }
    }
    return 0;
}