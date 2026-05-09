#include "HospitalException.h"
#include <iostream>
#include <string>
using namespace std;


HospitalException::HospitalException() {
    message = "An error occurred in the hospital system.";
}

HospitalException::HospitalException(const string& msg) {
    message = msg;
}

HospitalException::~HospitalException() {
}

string HospitalException::what() const {
    return message;
}


FileNotFoundException::FileNotFoundException()
    : HospitalException("File not found.") {
}

FileNotFoundException::FileNotFoundException(const string& filename)
    : HospitalException("File not found: " + filename) {
}

string FileNotFoundException::what() const {
    return message;
}

InsufficientFundsException::InsufficientFundsException()
    : HospitalException("Insufficient funds in account.") {
    required = 0.0;
    available = 0.0;
}

InsufficientFundsException::InsufficientFundsException(float required, float available)
    : HospitalException("Insufficient funds. Required: PKR " +
        to_string(required) + " Available: PKR " +
        to_string(available)) {
    this->required = required;
    this->available = available;
}

string InsufficientFundsException::what() const {
   return message;
}


InvalidInputException::InvalidInputException()
    : HospitalException("Invalid input provided.") {
}

InvalidInputException::InvalidInputException(const string& inputType)
    : HospitalException("Invalid input for: " + inputType) {
}

string InvalidInputException::what() const {
    return message;
}



SlotUnavailableException::SlotUnavailableException()
    : HospitalException("This time slot is not available.") {
    slot = "";
}

SlotUnavailableException::SlotUnavailableException(const string& slot)
    : HospitalException("Time slot " + slot + " is already booked. Please choose another slot.") {
    this->slot = slot;
}

string SlotUnavailableException::what() const {
    return message;
}