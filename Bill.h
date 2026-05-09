#pragma once
#pragma once
#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <string>
using namespace std;

class Bill {
private:
    int billId;
    int patientId;
    int appointmentId;
    float amount;
    string status;
    string date;

public:
    Bill();
    Bill(int billId, int patientId, int appointmentId,
        float amount, const string& status, const string& date);

    ~Bill();

    // Critical for Storage<Bill>
    int getId() const;

    int getBillId() const;
    int getPatientId() const;
    int getAppointmentId() const;
    float getAmount() const;
    string getStatus() const;
    string getDate() const;

    void setStatus(const string& s);
    void setAmount(float a);

    bool operator==(const Bill& other) const;

    friend ostream& operator<<(ostream& out, const Bill& b);
    friend istream& operator>>(istream& in, Bill& b);
};

#endif