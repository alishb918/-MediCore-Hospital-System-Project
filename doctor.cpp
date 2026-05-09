#include "Doctor.h"
#include <iostream>
using namespace std;



Doctor::Doctor() : Person() {
    specialization = "none";
    contact = "none";
    fee = 0.0;
}

Doctor::Doctor(int id, const string& name, const string& password,const string& specialization, const string& contact, float fee): Person(id, name, password) {
    this->specialization = specialization;
    this->contact = contact;
    this->fee = fee;
}


Doctor::~Doctor() {

}


string Doctor::getSpecialization() const {
    return specialization;
}

string Doctor::getContact() const {
    return contact;
}

float Doctor::getFee() const {
    return fee;
}

void Doctor::setContact(const string& c) {
    contact = c;
}

void Doctor::setFee(float f) {
    fee = f;
}

 
bool Doctor::operator==(const Doctor& other) const {
    return this->id == other.id;
}
 
void Doctor::displayMenu() {
    cout << "\n          DOCTOR PANEL           " << endl;
    cout << "Welcome, Dr. " << name << endl;
    cout << "Specialization: " << specialization << endl;
    cout << "Consultation Fee: PKR " << fee << endl;
    cout << "                                " << endl;
    cout << "1. View My Appointments" << endl;
    cout << "2. Mark Appointment as Completed" << endl;
    cout << "3. Cancel Appointment" << endl;
    cout << "4. Add Prescription" << endl;
    cout << "5. View My Prescriptions" << endl;
    cout << "6. View Patient Details" << endl;
    cout << "7. Logout" << endl;
    cout << "                                  " << endl;
    cout << "Enter choice: ";
}

void Doctor::display() {
    cout << id << " | " << name << " | "<< specialization << " | "<< contact << " | " << "pkr " << fee << endl;
}


ostream& operator<<(ostream& out, const Doctor& d) {
    out << "                                      " << endl;
    out << "Doctor ID        : " << d.id << endl;
    out << "Name             : " << d.name << endl;
    out << "Specialization   : " << d.specialization << endl;
    out << "Contact          : " << d.contact << endl;
    out << "Consultation Fee : PKR " << d.fee << endl;
    out << "                               " << endl;
    return out;
}