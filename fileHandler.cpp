#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;

void FileHandler::loadPatients(Storage<Patient>& storage) {
    ifstream file("patients.txt");
    if (!file.is_open()) {
        cout << "Warning: patients.txt not found. Starting fresh." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        int id, age;
        string name, password, contact;
        char gender;
        float balance;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, token, ','); age = stoi(token);
        getline(ss, token, ','); gender = token[0];
        getline(ss, contact, ',');
        getline(ss, password, ',');
        getline(ss, token, ','); balance = stof(token);

        Patient p(id, name, password, age, gender, contact, balance);
        storage.add(p);
    }
    file.close();
}

void FileHandler::loadDoctors(Storage<Doctor>& storage) {
    ifstream file("doctors.txt");
    if (!file.is_open()) {
        cout << "Warning: doctors.txt not found. Starting fresh." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        int id;
        string name, specialization, contact, password;
        float fee;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, specialization, ',');
        getline(ss, contact, ',');
        getline(ss, password, ',');
        getline(ss, token, ','); fee = stof(token);

        Doctor d(id, name, password, specialization, contact, fee);
        storage.add(d);
    }
    file.close();
}

void FileHandler::loadAppointments(Storage<Appointment>& storage) {
    ifstream file("appointments.txt");
    if (!file.is_open()) {
        cout << "Warning: appointments.txt not found. Starting fresh." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        int id, patientId, doctorId;
        string date, timeSlot, status;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, token, ','); patientId = stoi(token);
        getline(ss, token, ','); doctorId = stoi(token);
        getline(ss, date, ',');
        getline(ss, timeSlot, ',');
        getline(ss, status, ',');

        Appointment a(id, patientId, doctorId, date, timeSlot, status);
        storage.add(a);
    }
    file.close();
}

void FileHandler::loadBills(Storage<Bill>& storage) {
    ifstream file("bills.txt");
    if (!file.is_open()) {
        cout << "Warning: bills.txt not found. Starting fresh." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        int id, patientId, appointmentId;
        float amount;
        string status, date;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, token, ','); patientId = stoi(token);
        getline(ss, token, ','); appointmentId = stoi(token);
        getline(ss, token, ','); amount = stof(token);
        getline(ss, status, ',');
        getline(ss, date, ',');

        Bill b(id, patientId, appointmentId, amount, status, date);
        storage.add(b);
    }
    file.close();
}

void FileHandler::loadPrescriptions(Storage<Prescription>& storage) {
    ifstream file("prescriptions.txt");
    if (!file.is_open()) {
        cout << "Warning: prescriptions.txt not found. Starting fresh." << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        int id, appointmentId, patientId, doctorId;
        string date, medicines, notes;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, token, ','); appointmentId = stoi(token);
        getline(ss, token, ','); patientId = stoi(token);
        getline(ss, token, ','); doctorId = stoi(token);
        getline(ss, date, ',');
        getline(ss, medicines, ',');
        getline(ss, notes, ',');

        Prescription p(id, appointmentId, patientId, doctorId, date, medicines, notes);
        storage.add(p);
    }
    file.close();
}

void FileHandler::loadAdmin(Admin& admin) {
    ifstream file("admin.txt");
    if (!file.is_open()) {
        cout << "Warning: admin.txt not found." << endl;
        return;
    }
    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        string token;
        int id;
        string name, password;

        getline(ss, token, ','); id = stoi(token);
        getline(ss, name, ',');
        getline(ss, password, ',');

        admin = Admin(id, name, password);
    }
    file.close();
}

void FileHandler::savePatient(const Patient& p) {
    ofstream file("patients.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error: Cannot open patients.txt" << endl;
        return;
    }
    file << p.getId() << ","
        << p.getName() << ","
        << p.getAge() << ","
        << p.getGender() << ","
        << p.getContact() << ","
        << p.getPassword() << ","
        << p.getBalance() << "\n";
    file.close();
}

void FileHandler::saveDoctor(const Doctor& d) {
    ofstream file("doctors.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error: Cannot open doctors.txt" << endl;
        return;
    }
    file << d.getId() << ","
        << d.getName() << ","
        << d.getSpecialization() << ","
        << d.getContact() << ","
        << d.getPassword() << ","
        << d.getFee() << "\n";
    file.close();
}

void FileHandler::saveAppointment(const Appointment& a) {
    ofstream file("appointments.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error: Cannot open appointments.txt" << endl;
        return;
    }
    file << a.getAppointmentId() << ","
        << a.getPatientId() << ","
        << a.getDoctorId() << ","
        << a.getDate() << ","
        << a.getTimeSlot() << ","
        << a.getStatus() << "\n";
    file.close();
}

void FileHandler::saveBill(const Bill& b) {
    ofstream file("bills.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error: Cannot open bills.txt" << endl;
        return;
    }
    file << b.getBillId() << ","
        << b.getPatientId() << ","
        << b.getAppointmentId() << ","
        << b.getAmount() << ","
        << b.getStatus() << ","
        << b.getDate() << "\n";
    file.close();
}

void FileHandler::savePrescription(const Prescription& p) {
    ofstream file("prescriptions.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error: Cannot open prescriptions.txt" << endl;
        return;
    }
    file << p.getPrescriptionId() << ","
        << p.getAppointmentId() << ","
        << p.getPatientId() << ","
        << p.getDoctorId() << ","
        << p.getDate() << ","
        << p.getMedicines() << ","
        << p.getNotes() << "\n";
    file.close();
}

void FileHandler::updatePatient(const Patient& p) {
    Storage<Patient> temp;
    loadPatients(temp);

    ofstream file("patients.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open patients.txt" << endl;
        return;
    }
    for (int i = 0; i < temp.size(); i++) {
        Patient* current = &temp.getAll()[i];
        if (current->getId() == p.getId()) {
            file << p.getId() << ","
                << p.getName() << ","
                << p.getAge() << ","
                << p.getGender() << ","
                << p.getContact() << ","
                << p.getPassword() << ","
                << p.getBalance() << "\n";
        }
        else {
            file << current->getId() << ","
                << current->getName() << ","
                << current->getAge() << ","
                << current->getGender() << ","
                << current->getContact() << ","
                << current->getPassword() << ","
                << current->getBalance() << "\n";
        }
    }
    file.close();
}

void FileHandler::updateAppointment(const Appointment& a) {
    Storage<Appointment> temp;
    loadAppointments(temp);

    ofstream file("appointments.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open appointments.txt" << endl;
        return;
    }
    for (int i = 0; i < temp.size(); i++) {
        Appointment* current = &temp.getAll()[i];
        if (current->getAppointmentId() == a.getAppointmentId()) {
            file << a.getAppointmentId() << ","
                << a.getPatientId() << ","
                << a.getDoctorId() << ","
                << a.getDate() << ","
                << a.getTimeSlot() << ","
                << a.getStatus() << "\n";
        }
        else {
            file << current->getAppointmentId() << ","
                << current->getPatientId() << ","
                << current->getDoctorId() << ","
                << current->getDate() << ","
                << current->getTimeSlot() << ","
                << current->getStatus() << "\n";
        }
    }
    file.close();
}

void FileHandler::updateBill(const Bill& b) {
    Storage<Bill> temp;
    loadBills(temp);

    ofstream file("bills.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open bills.txt" << endl;
        return;
    }
    for (int i = 0; i < temp.size(); i++) {
        Bill* current = &temp.getAll()[i];
        if (current->getBillId() == b.getBillId()) {
            file << b.getBillId() << ","
                << b.getPatientId() << ","
                << b.getAppointmentId() << ","
                << b.getAmount() << ","
                << b.getStatus() << ","
                << b.getDate() << "\n";
        }
        else {
            file << current->getBillId() << ","
                << current->getPatientId() << ","
                << current->getAppointmentId() << ","
                << current->getAmount() << ","
                << current->getStatus() << ","
                << current->getDate() << "\n";
        }
    }
    file.close();
}

void FileHandler::deletePatient(int id) {
    Storage<Patient> temp;
    loadPatients(temp);

    ofstream file("patients.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < temp.size(); i++) {
        Patient* current = &temp.getAll()[i];
        if (current->getId() != id) {
            file << current->getId() << ","
                << current->getName() << ","
                << current->getAge() << ","
                << current->getGender() << ","
                << current->getContact() << ","
                << current->getPassword() << ","
                << current->getBalance() << "\n";
        }
    }
    file.close();
}

void FileHandler::deleteDoctor(int id) {
    Storage<Doctor> temp;
    loadDoctors(temp);

    ofstream file("doctors.txt");
    if (!file.is_open()) return;

    for (int i = 0; i < temp.size(); i++) {
        Doctor* current = &temp.getAll()[i];
        if (current->getId() != id) {
            file << current->getId() << ","
                << current->getName() << ","
                << current->getSpecialization() << ","
                << current->getContact() << ","
                << current->getPassword() << ","
                << current->getFee() << "\n";
        }
    }
    file.close();
}

void FileHandler::logSecurityEvent(const string& role,
    const string& enteredId, const string& result) {
    ofstream file("security_log.txt", ios::app);
    if (!file.is_open()) return;
    file << getCurrentDateTime() << ","
        << role << ","
        << enteredId << ","
        << result << "\n";
    file.close();
}

void FileHandler::archivePatient(int patientId,
    Storage<Patient>& patients, Storage<Appointment>& appointments,
    Storage<Bill>& bills, Storage<Prescription>& prescriptions) {
    ofstream file("discharged.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error: Cannot open discharged.txt" << endl;
        return;
    }

    Patient* p = patients.findById(patientId);
    if (p != nullptr) {
        file << p->getId() << ","
            << p->getName() << ","
            << p->getAge() << ","
            << p->getGender() << ","
            << p->getContact() << ","
            << p->getPassword() << ","
            << p->getBalance() << "\n";
    }
    file.close();

    deletePatient(patientId);
}

string FileHandler::getCurrentDateTime() {
    time_t now = time(0);
    char buffer[20];
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeInfo);
    return string(buffer);
}