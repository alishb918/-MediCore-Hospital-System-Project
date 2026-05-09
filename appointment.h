#pragma once
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <string>
using namespace std;

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string date;
    string timeSlot;
    string status;

public:
    Appointment();
    Appointment(int appointmentId, int patientId, int doctorId,
        const string& date, const string& timeSlot,
        const string& status);
    ~Appointment();

    // Getters
    int getId() const;                    // Added for Storage<T>
    int getAppointmentId() const;
    int getPatientId() const;
    int getDoctorId() const;
    string getDate() const;
    string getTimeSlot() const;
    string getStatus() const;

    // Setters
    void setStatus(const string& s);
    void setDate(const string& d);
    void setTimeSlot(const string& t);

    bool operator==(const Appointment& other) const;

    friend ostream& operator<<(ostream& out, const Appointment& a);
    friend istream& operator>>(istream& in, Appointment& a);
};

#endif