#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include <iostream>
#include <cstring>
using namespace std;

class Admin : public Person {

public:
   
    Admin();
    Admin(int id, const string& name, const string& password);

  
    ~Admin();

 
    void displayMenu() override;
    void display() override;

    friend ostream& operator<<(ostream& out, const Admin& a);
};

#endif
