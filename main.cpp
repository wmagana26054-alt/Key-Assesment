#include <iostream>
#include <string>
#include <array>
#include <iomanip>
#include "EventManager.h"

using namespace std;

// Collects and validates menu choice (0-6)
int getValidatedMenuChoice() {
    int choice = -1;
    cout << "Enter your choice (0-6): ";
    while (!(cin >> choice) || choice < MIN_MENU || choice > MAX_MENU) {
        cout << "Invalid choice. Please enter a number between 0 and 6: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');
    return choice;
}

// Collects non-empty text input
string getValidatedText(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);

    while (input.empty() || input.find_first_not_of(' ') == string::npos) {
        cout << "Invalid input. Field cannot be empty: ";
        getline(cin, input);
    }
    return input;
}

// Registers a new student if capacity and duplicate checks pass
void registerStudent(array<Student, MAX_STUDENTS>& students, int& count) {
    if (count >= MAX_STUDENTS) {
        cout << "\nSorry, the event is at full capacity (" << MAX_STUDENTS << " seats).\n";
        return;
    }

    string fullName = getValidatedText("Please enter your full name: ");
    string email = getValidatedText("Please enter your email address: ");

    for (int i = 0; i < count; ++i) {
        if (students[i].getEmail() == email) {
            cout << "Error: A student with this email is already registered.\n";
            return;
        }
    }

    string classname = getValidatedText("Please enter your class: ");
    string phonenumber = getValidatedText("Please enter your phone number: ");

    students[count] = Student(fullName, email, classname, phonenumber);
    ++count;

    cout << "\n--- REGISTRATION COMPLETED ---\n";
    cout << "Name   : " << fullName << "\n";
    cout << "Email  : " << email << "\n";
    cout << "Class  : " << classname << "\n";
    cout << "Phone  : " << phonenumber << "\n";
    cout << "------------------------------\n";
}

// Displays all registered students
void viewAllRegistrations(const array<Student, MAX_STUDENTS>& students, int count) {
    if (count == 0) {
        cout << "\nNo students registered yet.\n";
        return;
    }

    cout << "\n--- REGISTERED STUDENTS (" << count << "/" << MAX_STUDENTS << ") ---\n";
    for (int i = 0; i < count; ++i) {
        cout << (i + 1) << ". " << students[i].getFullName()
             << " | " << students[i].getEmail()
             << " | " << students[i].getClassname()
             << " | " << students[i].getPhonenumber()
             << " | [" << (students[i].isCheckedIn() ? "Checked In" : "Registered") << "]\n";
    }
    cout << "-------------------------------------\n";
}

// Searches for a student by full name
void searchStudent(const array<Student, MAX_STUDENTS>& students, int count) {
    if (count == 0) {
        cout << "\nNo students registered yet.\n";
        return;
    }

    string searchName = getValidatedText("Please enter full name to search: ");
    for (int i = 0; i < count; ++i) {
        if (students[i].getFullName() == searchName) {
            cout << "\n--- STUDENT FOUND ---\n";
            cout << "Seat # : " << (i + 1) << "\n";
            cout << "Name   : " << students[i].getFullName() << "\n";
            cout << "Email  : " << students[i].getEmail() << "\n";
            cout << "Class  : " << students[i].getClassname() << "\n";
            cout << "Phone  : " << students[i].getPhonenumber() << "\n";
            cout << "Status : " << (students[i].isCheckedIn() ? "Checked In" : "Registered") << "\n";
            cout << "---------------------\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

// Marks a registered student as checked in
void checkInStudent(array<Student, MAX_STUDENTS>& students, int count) {
    if (count == 0) {
        cout << "\nNo students registered yet.\n";
        return;
    }

    string name = getValidatedText("Please enter full name to check in: ");
    for (int i = 0; i < count; ++i) {
        if (students[i].getFullName() == name) {
            if (students[i].isCheckedIn()) {
                cout << name << " is already checked in.\n";
            } else {
                students[i].setCheckedIn(true);
                cout << name << " is now checked in.\n";
            }
            return;
        }
    }

    cout << "Student not found.\n";
}

// Cancels a registration and shifts remaining elements left
void cancelRegistration(array<Student, MAX_STUDENTS>& students, int& count) {
    if (count == 0) {
        cout << "\nNo students registered yet.\n";
        return;
    }

    string name = getValidatedText("Please enter full name to cancel: ");
    for (int i = 0; i < count; ++i) {
        if (students[i].getFullName() == name) {
            for (int j = i; j < count - 1; ++j) {
                students[j] = students[j + 1];
            }
            --count;
            cout << "Registration canceled for " << name << ".\n";
            return;
        }
    }

    cout << "Student not found.\n";
}

// Displays formatted summary of event attendance
void displaySummary(const array<Student, MAX_STUDENTS>& students, int count) {
    int checkedInCount = 0;
    for (int i = 0; i < count; ++i) {
        if (students[i].isCheckedIn()) {
            ++checkedInCount;
        }
    }

    double attendanceRate = (count == 0) ? 0.0 : ((double)checkedInCount / count) * 100.0;

    cout << fixed << setprecision(1);
    cout << "\n--- EVENT SUMMARY ---\n";
    cout << "Total Registered : " << count << " / " << MAX_STUDENTS << "\n";
    cout << "Checked In       : " << checkedInCount << " (" << attendanceRate << "%)\n";
    cout << "Seats Available  : " << (MAX_STUDENTS - count) << "\n";
    cout << "---------------------\n";
}

int main() {
    array<Student, MAX_STUDENTS> students;
    int count = 0;
    bool keepRunning = true;

    cout << "=================================\n";
    cout << "    Student Event Registration   \n";
    cout << "=================================\n";

    while (keepRunning) {
        cout << "\n1. Register a Student\n";
        cout << "2. View All Registrations\n";
        cout << "3. Search Student by Name\n";
        cout << "4. Check In a Student\n";
        cout << "5. Cancel a Registration\n";
        cout << "6. View Event Summary\n";
        cout << "0. Exit\n";
        std::cout << "---------------------------------\n";

        int choice = getValidatedMenuChoice();

        switch (choice) {
            case 1:
                registerStudent(students, count);
                break;
            case 2:
                viewAllRegistrations(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                checkInStudent(students, count);
                break;
            case 5:
                cancelRegistration(students, count);
                break;
            case 6:
                displaySummary(students, count);
                break;
            case 0:
                keepRunning = false;
                break;
        }
    }

    cout << "\nThank you for using the Student Event Registration System!\n";
    return 0;
}