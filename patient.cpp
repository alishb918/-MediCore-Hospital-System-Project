#include "Patient.h"
#include <iostream>
using namespace std;

Patient::Patient() : Person() {
    age = 0;
    gender = 'M';
    contact = "none";
    balance = 0.0f;
}

Patient::Patient(int id, const string& name, const string& password,
    int age, char gender, const string& contact, float balance)
    : Person(id, name, password) {
    this->age = age;
    this->gender = gender;
    this->contact = contact;
    this->balance = balance;
}

Patient::~Patient() {}

int Patient::getAge() const { return age; }
char Patient::getGender() const { return gender; }
string Patient::getContact() const { return contact; }
float Patient::getBalance() const { return balance; }

void Patient::setContact(const string& c) { contact = c; }
void Patient::setBalance(float b) { balance = b; }

// Operator Overloads
Patient& Patient::operator+=(float amount) {
    if (amount > 0) {
        balance += amount;
    }
    return *this;
}

Patient& Patient::operator-=(float amount) {
    if (amount > 0) {
        balance -= amount;
    }
    return *this;
}

bool Patient::operator==(const Patient& other) const {
    return this->id == other.id;
}

void Patient::displayMenu() {
    cout << "\n          PATIENT PANEL           " << endl;
    cout << "Welcome, " << name << endl;
    cout << "Balance: PKR " << balance << endl;
    cout << "==================================" << endl;
    cout << "1. Book Appointment" << endl;
    cout << "2. Cancel Appointment" << endl;
    cout << "3. View My Appointments" << endl;
    cout << "4. View My Medical Records" << endl;
    cout << "5. View My Bills" << endl;
    cout << "6. Pay Bill" << endl;
    cout << "7. Top Up Balance" << endl;
    cout << "8. Logout" << endl;
    cout << "==================================" << endl;
    cout << "Enter choice: ";
}

void Patient::display() {
    cout << id << " | " << name << " | " << age << " | "
        << gender << " | " << contact << " | PKR " << balance << endl;
}

ostream& operator<<(ostream& out, const Patient& p) {
    out << "---------------------------------" << endl;
    out << "Patient ID : " << p.id << endl;
    out << "Name       : " << p.name << endl;
    out << "Age        : " << p.age << endl;
    out << "Gender     : " << p.gender << endl;
    out << "Contact    : " << p.contact << endl;
    out << "Balance    : PKR " << p.balance << endl;
    out << "---------------------------------" << endl;
    return out;
}