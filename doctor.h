#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <iostream>
#include <cstring>
using namespace std;

class Doctor : public Person {
private:
    string specialization;
    string contact;
    float fee;

public:

    Doctor();
    Doctor(int id, const string& name, const string& password, const string& specialization, const string& contact, float fee);

    ~Doctor();

    string getSpecialization() const;
    string getContact() const;
    float getFee() const;

    void setContact(const string& c);
    void setFee(float f);

    bool operator==(const Doctor& other) const;  

    void displayMenu() override;
    void display() override;

    friend ostream& operator<<(ostream& out, const Doctor& d);
};

#endif