#include "Bill.h"
#include <iostream>
using namespace std;

Bill::Bill() {
    billId = 0;
    patientId = 0;
    appointmentId = 0;
    amount = 0.0f;
    status = "unpaid";
    date = "";
}

Bill::Bill(int billId, int patientId, int appointmentId,
    float amount, const string& status, const string& date) {
    this->billId = billId;
    this->patientId = patientId;
    this->appointmentId = appointmentId;
    this->amount = amount;
    this->status = status;
    this->date = date;
}

Bill::~Bill() {}

int Bill::getId() const {
    return billId;
}

int Bill::getBillId() const {
    return billId;
}

int Bill::getPatientId() const {
    return patientId;
}

int Bill::getAppointmentId() const {
    return appointmentId;
}

float Bill::getAmount() const {
    return amount;
}

string Bill::getStatus() const {
    return status;
}

string Bill::getDate() const {
    return date;
}

void Bill::setStatus(const string& s) {
    status = s;
}

void Bill::setAmount(float a) {
    amount = a;
}

bool Bill::operator==(const Bill& other) const {
    return this->billId == other.billId;
}

ostream& operator<<(ostream& out, const Bill& b) {
    out << "---------------------------------" << endl;
    out << "Bill ID : " << b.billId << endl;
    out << "Patient ID : " << b.patientId << endl;
    out << "Appointment ID : " << b.appointmentId << endl;
    out << "Amount : PKR " << b.amount << endl;
    out << "Status : " << b.status << endl;
    out << "Date : " << b.date << endl;
    out << "---------------------------------" << endl;
    return out;
}

istream& operator>>(istream& in, Bill& b) {
    cout << "Enter Bill ID: ";
    in >> b.billId;
    cout << "Enter Patient ID: ";
    in >> b.patientId;
    cout << "Enter Appointment ID: ";
    in >> b.appointmentId;
    cout << "Enter Amount (PKR): ";
    in >> b.amount;
    cout << "Enter Status (unpaid/paid/cancelled): ";
    in >> b.status;
    cout << "Enter Date (DD-MM-YYYY): ";
    in >> b.date;
    return in;
}