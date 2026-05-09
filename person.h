#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    int id;
    string name;
    string password;

public:
    Person();
    Person(int id, const string& name, const string& password);
    virtual ~Person();

    int getId() const;
    string getName() const;
    string getPassword() const;

    bool checkPassword(const string& entered) const;

    virtual void displayMenu() = 0;     // Pure virtual
    virtual void display() = 0;         // Pure virtual

    friend ostream& operator<<(ostream& out, const Person& p); // Optional
};

#endif