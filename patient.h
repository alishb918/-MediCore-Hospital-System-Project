#pragma once
#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

class Patient : public Person {
private:
    int age;
    char gender;
    string contact;
    float balance;

public:
    Patient();
    Patient(int id, const string& name, const string& password,
        int age, char gender, const string& contact, float balance);

    ~Patient();

    // Getters
    int getAge() const;
    char getGender() const;
    string getContact() const;
    float getBalance() const;

    // Setters
    void setContact(const string& c);
    void setBalance(float b);

    // Required Operator Overloads
    Patient& operator+=(float amount);
    Patient& operator-=(float amount);
    bool operator==(const Patient& other) const;

    void displayMenu() override;
    void display() override;

    friend ostream& operator<<(ostream& out, const Patient& p);
};

#endif