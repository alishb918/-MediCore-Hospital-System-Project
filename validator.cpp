#include "Validator.h"
#include <iostream>
#include <string>
using namespace std;


bool Validator::isValidDate(const string& date) {
    // Must be exactly 10 characters
    if (date.length() != 10) return false;

    // Must have dashes at positions 2 and 5
    if (date[2] != '-' || date[5] != '-') return false;

    // Extract day, month, year
    string dayStr = date.substr(0, 2);
    string monthStr = date.substr(3, 2);
    string yearStr = date.substr(6, 4);

    // Check all parts are digits
    for (int i = 0; i < 2; i++) {
        if (dayStr[i] < '0' || dayStr[i] > '9') return false;
        if (monthStr[i] < '0' || monthStr[i] > '9') return false;
    }
    for (int i = 0; i < 4; i++) {
        if (yearStr[i] < '0' || yearStr[i] > '9') return false;
    }

    // Convert to integers
    int day = stoi(dayStr);
    int month = stoi(monthStr);
    int year = stoi(yearStr);

    // Validate ranges
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 2025) return false;

    return true;
}

bool Validator::isValidTimeSlot(const string& slot) {
    string validSlots[8] = {
        "09:00", "10:00", "11:00", "12:00",
        "13:00", "14:00", "15:00", "16:00"
    };
    for (int i = 0; i < 8; i++) {
        if (slot == validSlots[i]) return true;
    }
    return false;
}


bool Validator::isValidContact(const string& contact) {
    if (contact.length() != 11) return false;
    for (int i = 0; i < contact.length(); i++) {
        if (contact[i] < '0' || contact[i] > '9') return false;
    }
    return true;
}


bool Validator::isValidPassword(const string& password) {
    return password.length() >= 6;
}

bool Validator::isValidAmount(float amount) {
    return amount > 0.0;
}

bool Validator::isValidMenuChoice(int choice, int min, int max) {
    return choice >= min && choice <= max;
}

bool Validator::isValidId(int id) {
    return id > 0;
}


string Validator::toLowerCase(const string& str) {
    string result = str;
    for (int i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z') {
            result[i] = result[i] + 32;
        }
    }
    return result;
}


bool Validator::equalsIgnoreCase(const string& str1, const string& str2) {
    return toLowerCase(str1) == toLowerCase(str2);
}

bool Validator::isAllDigits(const string& str) {
    if (str.empty()) return false;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

bool Validator::isValidPositiveFloat(const string& str) {
    if (str.empty()) return false;
    bool dotFound = false;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '.') {
            if (dotFound) return false;
            dotFound = true;
        }
        else if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return stof(str) > 0.0;
}