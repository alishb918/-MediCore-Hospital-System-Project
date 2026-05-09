#pragma once
#ifndef HOSPITALEXCEPTION_H
#define HOSPITALEXCEPTION_H

#include <iostream>
#include <string>
using namespace std;

class HospitalException {
protected:
    string message;

public:
    HospitalException();
    HospitalException(const string& msg);
    virtual ~HospitalException();
    virtual string what() const;
};


class FileNotFoundException : public HospitalException {
public:
    FileNotFoundException();
    FileNotFoundException(const string& filename);
    string what() const override;
};


class InsufficientFundsException : public HospitalException {
private:
    float required;
    float available;

public:
    InsufficientFundsException();
    InsufficientFundsException(float required, float available);
    string what() const override;
};


class InvalidInputException : public HospitalException {
public:
    InvalidInputException();
    InvalidInputException(const string& inputType);
    string what() const override;
};


class SlotUnavailableException : public HospitalException {
private:
    string slot;

public:
    SlotUnavailableException();
    SlotUnavailableException(const string& slot);
    string what() const override;
};

#endif
