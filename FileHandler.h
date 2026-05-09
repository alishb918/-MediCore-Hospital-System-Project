#pragma once
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Storage.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
using namespace std;

class FileHandler {
public:
    // LOAD FUNCTIONS
    static void loadPatients(Storage<Patient>& storage);
    static void loadDoctors(Storage<Doctor>& storage);
    static void loadAppointments(Storage<Appointment>& storage);
    static void loadBills(Storage<Bill>& storage);
    static void loadPrescriptions(Storage<Prescription>& storage);
    static void loadAdmin(Admin& admin);

    // SAVE (APPEND) FUNCTIONS
    static void savePatient(const Patient& p);
    static void saveDoctor(const Doctor& d);
    static void saveAppointment(const Appointment& a);
    static void saveBill(const Bill& b);
    static void savePrescription(const Prescription& p);

    // UPDATE FUNCTIONS 
    static void updatePatient(const Patient& p);
    static void updateDoctor(const Doctor& d);
    static void updateAppointment(const Appointment& a);
    static void updateBill(const Bill& b);

    //  DELETE FUNCTIONS
    static void deletePatient(int id);
    static void deleteDoctor(int id);

    //  UTILITY FUNCTIONS 
    static void logSecurityEvent(const string& role,
        const string& enteredId,
        const string& result);

    static void archivePatient(int patientId,
        Storage<Patient>& patients,
        Storage<Appointment>& appointments,
        Storage<Bill>& bills,
        Storage<Prescription>& prescriptions);

    static string getCurrentDateTime();
};

#endif
