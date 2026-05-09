#include "Person.h"

Person::Person() : id(0), name(""), password("") {}

Person::Person(int id, const string& name, const string& password) {
    this->id = id;
    this->name = name;
    this->password = password;
}

Person::~Person() {}

int Person::getId() const { return id; }
string Person::getName() const { return name; }
string Person::getPassword() const { return password; }

bool Person::checkPassword(const string& entered) const {
    return password == entered;
}