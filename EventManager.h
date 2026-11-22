#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <array>

using namespace std;

// Constants
const int MAX_STUDENTS = 30;
const int MIN_MENU = 0;
const int MAX_MENU = 6;

// Class Definition
class Student {
private:
    string fullName;
    string email;
    string classname;
    string phonenumber;
    bool checkedIn;

public:
    Student() : fullName(""), email(""), classname(""), phonenumber(""), checkedIn(false) {}

    Student(string name, string mail, string cls, string phone)
        : fullName(name), email(mail), classname(cls), phonenumber(phone), checkedIn(false) {}

    string getFullName() const { return fullName; }
    string getEmail() const { return email; }
    string getClassname() const { return classname; }
    string getPhonenumber() const { return phonenumber; }
    bool isCheckedIn() const { return checkedIn; }

    void setCheckedIn(bool status) { checkedIn = status; }
};

// Function Declarations
int getValidatedMenuChoice();
string getValidatedText(const string& prompt);
void registerStudent(array<Student, MAX_STUDENTS>& students, int& count);
void viewAllRegistrations(const array<Student, MAX_STUDENTS>& students, int count);
void searchStudent(const array<Student, MAX_STUDENTS>& students, int count);
void checkInStudent(array<Student, MAX_STUDENTS>& students, int count);
void cancelRegistration(array<Student, MAX_STUDENTS>& students, int& count);
void displaySummary(const array<Student, MAX_STUDENTS>& students, int count);

#endif