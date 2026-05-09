#include "Admin.h"
#include <iostream>
using namespace std;

Admin::Admin() : Person() {
}


Admin::Admin(int id, const string& name, const string& password) : Person(id, name, password) {
}

Admin::~Admin() {
}

void Admin::displayMenu() {
    cout << "\n          ADMIN PANEL             " << endl;
    cout << "Welcome, " << name << endl;
    cout << "                             " << endl;
    cout << "1. Add New Doctor" << endl;
    cout << "2. Remove Doctor" << endl;
    cout << "3. View All Doctors" << endl;
    cout << "4. View All Patients" << endl;
    cout << "5. View All Appointments" << endl;
    cout << "6. View All Bills" << endl;
    cout << "7. View Patient Records" << endl;
    cout << "8. Generate Hospital Report" << endl;
    cout << "9. Logout" << endl;
    cout << "                              " << endl;
    cout << "Enter choice: ";
}

void Admin::display() {
    cout << "Admin ID: " << id << " | Name: " << name << endl;
}

ostream& operator<<(ostream& out, const Admin& a) {
    out << "                                      " << endl;
    out << "Admin ID  : " << a.id << endl;
    out << "Name      : " << a.name << endl;
    out << "                                    " << endl;
    return out;
}