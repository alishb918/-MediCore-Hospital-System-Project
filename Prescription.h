#pragma once
#pragma once
#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <iostream>
#include <string>
using namespace std;

class Prescription {
private:
    int prescriptionId;
    int appointmentId;
    int patientId;
    int doctorId;
    string date;
    string medicines;
    string notes;

public:
    // Constructors
    Prescription();
    Prescription(int prescriptionId, int appointmentId, int patientId,
        int doctorId, const string& date,
        const string& medicines, const string& notes);
    int getId() const;

    // Destructor
    ~Prescription();

    // Getters
    int getPrescriptionId() const;
    int getAppointmentId() const;
    int getPatientId() const;
    int getDoctorId() const;
    string getDate() const;
    string getMedicines() const;
    string getNotes() const;

    // Setters
    void setMedicines(const string& m);
    void setNotes(const string& n);

    // Operator Overloads
    bool operator==(const Prescription& other) const;

    // Friend functions
    friend ostream& operator<<(ostream& out, const Prescription& p);
    friend istream& operator>>(istream& in, Prescription& p);
};

#endif