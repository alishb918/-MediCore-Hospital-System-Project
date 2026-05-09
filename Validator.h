#pragma once
#pragma once
#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <iostream>
#include <string>
using namespace std;

class Validator {
public:
    // Validate date format DD-MM-YYYY
    static bool isValidDate(const string& date);

    // Validate time slot is one of the 8 fixed slots
    static bool isValidTimeSlot(const string& slot);

    // Validate contact is exactly 11 digits
    static bool isValidContact(const string& contact);

    // Validate password is at least 6 characters
    static bool isValidPassword(const string& password);

    // Validate amount is a positive number greater than 0
    static bool isValidAmount(float amount);

    // Validate menu choice is within range
    static bool isValidMenuChoice(int choice, int min, int max);

    // Validate ID is a positive number
    static bool isValidId(int id);

    // Convert string to lowercase manually
    static string toLowerCase(const string& str);

    // Compare two strings case-insensitively
    static bool equalsIgnoreCase(const string& str1, const string& str2);

    // Check if string contains only digits
    static bool isAllDigits(const string& str);

    // Check if string is a valid positive float
    static bool isValidPositiveFloat(const string& str);
};

#endif
