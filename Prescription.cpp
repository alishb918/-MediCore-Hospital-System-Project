#include "Prescription.h"
#include <iostream>
using namespace std;

Prescription::Prescription() {
    prescriptionId = 0;
    appointmentId = 0;
    patientId = 0;
    doctorId = 0;
    date = "";
    medicines = "";
    notes = "";
}

Prescription::Prescription(int prescriptionId, int appointmentId, int patientId,
    int doctorId, const string& date,
    const string& medicines, const string& notes) {
    this->prescriptionId = prescriptionId;
    this->appointmentId = appointmentId;
    this->patientId = patientId;
    this->doctorId = doctorId;
    this->date = date;
    this->medicines = medicines;
    this->notes = notes;
}

Prescription::~Prescription() {}

int Prescription::getId() const {
    return prescriptionId;
}

int Prescription::getPrescriptionId() const {
    return prescriptionId;
}

int Prescription::getAppointmentId() const {
    return appointmentId;
}

int Prescription::getPatientId() const {
    return patientId;
}

int Prescription::getDoctorId() const {
    return doctorId;
}

string Prescription::getDate() const {
    return date;
}

string Prescription::getMedicines() const {
    return medicines;
}

string Prescription::getNotes() const {
    return notes;
}

void Prescription::setMedicines(const string& m) {
    medicines = m;
}

void Prescription::setNotes(const string& n) {
    notes = n;
}

bool Prescription::operator==(const Prescription& other) const {
    return this->prescriptionId == other.prescriptionId;
}

ostream& operator<<(ostream& out, const Prescription& p) {
    out << "---------------------------------" << endl;
    out << "Prescription ID : " << p.prescriptionId << endl;
    out << "Appointment ID : " << p.appointmentId << endl;
    out << "Patient ID : " << p.patientId << endl;
    out << "Doctor ID : " << p.doctorId << endl;
    out << "Date : " << p.date << endl;
    out << "Medicines : " << p.medicines << endl;
    out << "Notes : " << p.notes << endl;
    out << "---------------------------------" << endl;
    return out;
}

istream& operator>>(istream& in, Prescription& p) {
    cout << "Enter Prescription ID: ";
    in >> p.prescriptionId;
    cout << "Enter Appointment ID: ";
    in >> p.appointmentId;
    cout << "Enter Patient ID: ";
    in >> p.patientId;
    cout << "Enter Doctor ID: ";
    in >> p.doctorId;
    cout << "Enter Date (DD-MM-YYYY): ";
    in >> p.date;
    in.ignore();
    cout << "Enter Medicines: ";
    getline(in, p.medicines);
    cout << "Enter Notes: ";
    getline(in, p.notes);
    return in;
}