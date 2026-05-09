#include "Appointment.h"
#include <iostream>
using namespace std;

Appointment::Appointment() {
    appointmentId = 0;
    patientId = 0;
    doctorId = 0;
    date = "";
    timeSlot = "";
    status = "pending";
}

Appointment::Appointment(int appointmentId, int patientId, int doctorId,
    const string& date, const string& timeSlot,
    const string& status) {
    this->appointmentId = appointmentId;
    this->patientId = patientId;
    this->doctorId = doctorId;
    this->date = date;
    this->timeSlot = timeSlot;
    this->status = status;
}

Appointment::~Appointment() {}

int Appointment::getId() const {
    return appointmentId;
}

int Appointment::getAppointmentId() const {
    return appointmentId;
}

int Appointment::getPatientId() const {
    return patientId;
}

int Appointment::getDoctorId() const {
    return doctorId;
}

string Appointment::getDate() const {
    return date;
}

string Appointment::getTimeSlot() const {
    return timeSlot;
}

string Appointment::getStatus() const {
    return status;
}

void Appointment::setStatus(const string& s) {
    status = s;
}

void Appointment::setDate(const string& d) {
    date = d;
}

void Appointment::setTimeSlot(const string& t) {
    timeSlot = t;
}

bool Appointment::operator==(const Appointment& other) const {
    bool sameSlot = (date == other.date) &&
        (timeSlot == other.timeSlot) &&
        (doctorId == other.doctorId);
    bool notCancelled = (status != "cancelled") &&
        (other.status != "cancelled");
    return sameSlot && notCancelled;
}

ostream& operator<<(ostream& out, const Appointment& a) {
    out << "---------------------------------" << endl;
    out << "Appointment ID : " << a.appointmentId << endl;
    out << "Patient ID : " << a.patientId << endl;
    out << "Doctor ID : " << a.doctorId << endl;
    out << "Date : " << a.date << endl;
    out << "Time Slot : " << a.timeSlot << endl;
    out << "Status : " << a.status << endl;
    out << "---------------------------------" << endl;
    return out;
}

istream& operator>>(istream& in, Appointment& a) {
    cout << "Enter Appointment ID: ";
    in >> a.appointmentId;
    cout << "Enter Patient ID: ";
    in >> a.patientId;
    cout << "Enter Doctor ID: ";
    in >> a.doctorId;
    cout << "Enter Date (DD-MM-YYYY): ";
    in >> a.date;
    cout << "Enter Time Slot (HH:MM): ";
    in >> a.timeSlot;
    cout << "Enter Status: ";
    in >> a.status;
    return in;
}