
#include <fstream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "GUI.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "Storage.h"
#include "FileHandler.h"
#include "Validator.h"
using namespace std;

enum Screen {
    MAIN_MENU,
    PATIENT_LOGIN,
    PATIENT_MENU,
    REGISTER_PATIENT,
    DOCTOR_LOGIN,
    DOCTOR_MENU,
    ADMIN_LOGIN,
    ADMIN_MENU
};

// forward declarations
string getTodayDate();
int getMaxId(const string& filename);
void sortAppointmentsByDate(Appointment* arr, int n, bool ascending);
void sortPrescriptionsByDate(Prescription* arr, int n);



int main() {
    // Load all data
    Storage<Patient>      patients;
    Storage<Doctor>       doctors;
    Storage<Appointment>  appointments;
    Storage<Bill>         bills;
    Storage<Prescription> prescriptions;
    Admin                 admin;


    FileHandler::loadPatients(patients);
    FileHandler::loadDoctors(doctors);
    FileHandler::loadAppointments(appointments);
    FileHandler::loadBills(bills);
    FileHandler::loadPrescriptions(prescriptions);
    FileHandler::loadAdmin(admin);
    // Create window
    sf::RenderWindow window(
        sf::VideoMode(900, 650),
        "MediCore Hospital System",
        sf::Style::Close | sf::Style::Titlebar
    );
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        if (!font.loadFromFile(
            "C:\\Windows\\Fonts\\arial.ttf")) {
            return -1;
        }
    }

    // Colors
    sf::Color bgColor(20, 30, 48);
    sf::Color bgColor2(30, 45, 70);
    sf::Color btnBlue(41, 128, 185);
    sf::Color btnHover(52, 152, 219);
    sf::Color btnGreen(39, 174, 96);
    sf::Color btnGreenHover(46, 204, 113);
    sf::Color btnRed(192, 57, 43);
    sf::Color btnRedHover(231, 76, 60);
    sf::Color btnGray(80, 80, 80);
    sf::Color btnGrayHover(110, 110, 110);

    Screen currentScreen = MAIN_MENU;
    Patient* loggedPatient = nullptr;
    Doctor* loggedDoctor = nullptr;
    string   messageText = "";
    bool     messageIsError = false;

    // top bar
    sf::RectangleShape topBar(sf::Vector2f(900, 60));
    topBar.setFillColor(sf::Color(15, 20, 35));
    topBar.setPosition(0, 0);

    // title
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("MediCore Hospital System");
    titleText.setCharacterSize(26);
    titleText.setFillColor(sf::Color(41, 128, 185));
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(20, 15);

    // subtitle on main menu
    sf::Text subtitleText;
    subtitleText.setFont(font);
    subtitleText.setString("Select an option to continue");
    subtitleText.setCharacterSize(16);
    subtitleText.setFillColor(sf::Color(150, 150, 150));
    subtitleText.setPosition(300, 120);

    // message text
    sf::Text msgText;
    msgText.setFont(font);
    msgText.setCharacterSize(16);
    msgText.setPosition(50, 580);

    // background card
    sf::RectangleShape card(sf::Vector2f(500, 420));
    card.setFillColor(sf::Color(30, 45, 70));
    card.setOutlineThickness(1);
    card.setOutlineColor(sf::Color(41, 128, 185));
    card.setPosition(200, 100);

    // ?? MAIN MENU ??
    Button btnPatientLogin, btnDoctorLogin,
        btnAdminLogin, btnRegister, btnExit;

    btnPatientLogin.setup(325, 150, 250, 50,
        "Patient Login", font, btnBlue, btnHover);
    btnDoctorLogin.setup(325, 220, 250, 50,
        "Doctor Login", font, btnBlue, btnHover);
    btnAdminLogin.setup(325, 290, 250, 50,
        "Admin Login", font, btnBlue, btnHover);
    btnRegister.setup(325, 360, 250, 50,
        "Register as Patient", font,
        btnGreen, btnGreenHover);
    btnExit.setup(325, 430, 250, 50,
        "Exit", font, btnRed, btnRedHover);

    // ?? PATIENT LOGIN ??
    sf::Text loginTitle;
    loginTitle.setFont(font);
    loginTitle.setCharacterSize(24);
    loginTitle.setFillColor(sf::Color::White);
    loginTitle.setStyle(sf::Text::Bold);
    loginTitle.setPosition(320, 110);

    sf::Text idLabel, passLabel;
    idLabel.setFont(font);
    idLabel.setString("Patient ID:");
    idLabel.setCharacterSize(16);
    idLabel.setFillColor(sf::Color(200, 200, 200));
    idLabel.setPosition(250, 195);

    passLabel.setFont(font);
    passLabel.setString("Password:");
    passLabel.setCharacterSize(16);
    passLabel.setFillColor(sf::Color(200, 200, 200));
    passLabel.setPosition(250, 285);

    InputBox idBox, passBox;
    idBox.setup(250, 215, 400, 45, "Enter ID", font);
    passBox.setup(250, 305, 400, 45,
        "Enter Password", font, true);

    Button btnLoginSubmit, btnBack;
    btnLoginSubmit.setup(250, 375, 185, 45,
        "Login", font, btnGreen, btnGreenHover);
    btnBack.setup(465, 375, 185, 45,
        "Back", font, btnRed, btnRedHover);

    // ?? PATIENT MENU ??
    sf::Text patientWelcome;
    patientWelcome.setFont(font);
    patientWelcome.setCharacterSize(20);
    patientWelcome.setFillColor(sf::Color::White);
    patientWelcome.setStyle(sf::Text::Bold);
    patientWelcome.setPosition(20, 70);

    sf::Text balanceText;
    balanceText.setFont(font);
    balanceText.setCharacterSize(16);
    balanceText.setFillColor(sf::Color(46, 204, 113));
    balanceText.setPosition(20, 100);

    Button btnBook, btnCancelApp, btnViewApp,
        btnRecords, btnBills, btnPay,
        btnTopUp, btnLogout;

    btnBook.setup(50, 145, 370, 48,
        "Book Appointment", font, btnBlue, btnHover);
    btnCancelApp.setup(480, 145, 370, 48,
        "Cancel Appointment", font, btnRed, btnRedHover);
    btnViewApp.setup(50, 210, 370, 48,
        "View My Appointments", font, btnBlue, btnHover);
    btnRecords.setup(480, 210, 370, 48,
        "View Medical Records", font, btnBlue, btnHover);
    btnBills.setup(50, 275, 370, 48,
        "View My Bills", font, btnBlue, btnHover);
    btnPay.setup(480, 275, 370, 48,
        "Pay Bill", font, btnGreen, btnGreenHover);
    btnTopUp.setup(50, 340, 370, 48,
        "Top Up Balance", font, btnGreen, btnGreenHover);
    btnLogout.setup(480, 340, 370, 48,
        "Logout", font, btnRed, btnRedHover);

    // info display area
    sf::RectangleShape infoBox(sf::Vector2f(800, 200));
    infoBox.setFillColor(sf::Color(25, 38, 58));
    infoBox.setOutlineThickness(1);
    infoBox.setOutlineColor(sf::Color(41, 128, 185));
    infoBox.setPosition(50, 405);

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(14);
    infoText.setFillColor(sf::Color(200, 200, 200));
    infoText.setPosition(60, 415);
    string infoContent = "";

    // ?? REGISTER ??
    sf::Text regTitle;
    regTitle.setFont(font);
    regTitle.setString("Patient Registration");
    regTitle.setCharacterSize(24);
    regTitle.setFillColor(sf::Color::White);
    regTitle.setStyle(sf::Text::Bold);
    regTitle.setPosition(290, 75);

    sf::Text regNameLabel, regAgeLabel,
        regGenderLabel, regContactLabel,
        regPassLabel;

    regNameLabel.setFont(font);
    regNameLabel.setString("Full Name:");
    regNameLabel.setCharacterSize(15);
    regNameLabel.setFillColor(sf::Color(200, 200, 200));
    regNameLabel.setPosition(200, 118);

    regAgeLabel.setFont(font);
    regAgeLabel.setString("Age:");
    regAgeLabel.setCharacterSize(15);
    regAgeLabel.setFillColor(sf::Color(200, 200, 200));
    regAgeLabel.setPosition(200, 178);

    regGenderLabel.setFont(font);
    regGenderLabel.setString("Gender (M/F):");
    regGenderLabel.setCharacterSize(15);
    regGenderLabel.setFillColor(sf::Color(200, 200, 200));
    regGenderLabel.setPosition(200, 238);

    regContactLabel.setFont(font);
    regContactLabel.setString("Contact (11 digits):");
    regContactLabel.setCharacterSize(15);
    regContactLabel.setFillColor(sf::Color(200, 200, 200));
    regContactLabel.setPosition(200, 298);

    regPassLabel.setFont(font);
    regPassLabel.setString("Password (min 6 chars):");
    regPassLabel.setCharacterSize(15);
    regPassLabel.setFillColor(sf::Color(200, 200, 200));
    regPassLabel.setPosition(200, 358);

    InputBox regName, regAge, regGender,
        regContact, regPass;
    regName.setup(200, 135, 500, 38,
        "Enter full name", font);
    regAge.setup(200, 195, 500, 38,
        "Enter age", font);
    regGender.setup(200, 255, 500, 38,
        "M or F", font);
    regContact.setup(200, 315, 500, 38,
        "03XXXXXXXXX", font);
    regPass.setup(200, 375, 500, 38,
        "Enter password", font, true);

    Button btnRegSubmit, btnRegBack;
    btnRegSubmit.setup(200, 430, 230, 45,
        "Register", font, btnGreen, btnGreenHover);
    btnRegBack.setup(470, 430, 230, 45,
        "Back", font, btnRed, btnRedHover);

    // ?? DOCTOR LOGIN ??
    sf::Text docLoginTitle;
    docLoginTitle.setFont(font);
    docLoginTitle.setString("Doctor Login");
    docLoginTitle.setCharacterSize(24);
    docLoginTitle.setFillColor(sf::Color::White);
    docLoginTitle.setStyle(sf::Text::Bold);
    docLoginTitle.setPosition(340, 110);

    sf::Text docIdLabel, docPassLabel;
    docIdLabel.setFont(font);
    docIdLabel.setString("Doctor ID:");
    docIdLabel.setCharacterSize(16);
    docIdLabel.setFillColor(sf::Color(200, 200, 200));
    docIdLabel.setPosition(250, 195);

    docPassLabel.setFont(font);
    docPassLabel.setString("Password:");
    docPassLabel.setCharacterSize(16);
    docPassLabel.setFillColor(sf::Color(200, 200, 200));
    docPassLabel.setPosition(250, 285);

    InputBox docIdBox, docPassBox;
    docIdBox.setup(250, 215, 400, 45,
        "Enter Doctor ID", font);
    docPassBox.setup(250, 305, 400, 45,
        "Enter Password", font, true);

    Button btnDocLogin, btnDocBack;
    btnDocLogin.setup(250, 375, 185, 45,
        "Login", font, btnGreen, btnGreenHover);
    btnDocBack.setup(465, 375, 185, 45,
        "Back", font, btnRed, btnRedHover);

    // ?? DOCTOR MENU ??
    sf::Text doctorWelcome;
    doctorWelcome.setFont(font);
    doctorWelcome.setCharacterSize(20);
    doctorWelcome.setFillColor(sf::Color::White);
    doctorWelcome.setStyle(sf::Text::Bold);
    doctorWelcome.setPosition(20, 70);

    sf::Text doctorFeeText;
    doctorFeeText.setFont(font);
    doctorFeeText.setCharacterSize(16);
    doctorFeeText.setFillColor(sf::Color(46, 204, 113));
    doctorFeeText.setPosition(20, 100);

    Button btnViewToday, btnMarkComplete,
        btnMarkNoShow, btnWritePresc,
        btnViewHistory, btnDocLogout;

    btnViewToday.setup(50, 145, 370, 48,
        "View Today Appointments",
        font, btnBlue, btnHover);
    btnMarkComplete.setup(480, 145, 370, 48,
        "Mark Appointment Complete",
        font, btnGreen, btnGreenHover);
    btnMarkNoShow.setup(50, 210, 370, 48,
        "Mark No Show",
        font, btnGray, btnGrayHover);
    btnWritePresc.setup(480, 210, 370, 48,
        "Write Prescription",
        font, btnBlue, btnHover);
    btnViewHistory.setup(50, 275, 370, 48,
        "View Patient History",
        font, btnBlue, btnHover);
    btnDocLogout.setup(480, 275, 370, 48,
        "Logout", font, btnRed, btnRedHover);

    // ?? ADMIN LOGIN ??


    sf::Text adminMenuTitle;
    adminMenuTitle.setFont(font);
    adminMenuTitle.setString("Admin Panel");
    adminMenuTitle.setCharacterSize(24);
    adminMenuTitle.setFillColor(sf::Color::White);
    adminMenuTitle.setStyle(sf::Text::Bold);
    adminMenuTitle.setPosition(20, 70);
    sf::Text adminLoginTitle;
    adminLoginTitle.setFont(font);
    adminLoginTitle.setString("Admin Login");
    adminLoginTitle.setCharacterSize(24);
    adminLoginTitle.setFillColor(sf::Color::White);
    adminLoginTitle.setStyle(sf::Text::Bold);
    adminLoginTitle.setPosition(350, 110);

    sf::Text adminIdLabel, adminPassLabel;
    adminIdLabel.setFont(font);
    adminIdLabel.setString("Admin ID:");
    adminIdLabel.setCharacterSize(16);
    adminIdLabel.setFillColor(sf::Color(200, 200, 200));
    adminIdLabel.setPosition(250, 195);

    adminPassLabel.setFont(font);
    adminPassLabel.setString("Password:");
    adminPassLabel.setCharacterSize(16);
    adminPassLabel.setFillColor(sf::Color(200, 200, 200));
    adminPassLabel.setPosition(250, 285);

    InputBox adminIdBox, adminPassBox;
    adminIdBox.setup(250, 215, 400, 45,
        "Enter Admin ID", font);
    adminPassBox.setup(250, 305, 400, 45,
        "Enter Password", font, true);

    Button btnAdminLogin2, btnAdminBack;
    Button btnAddDoctor, btnRemoveDoctor,
        btnViewPatients, btnViewDoctors,
        btnViewAllApp, btnViewUnpaid,
        btnDischarge, btnSecLog,
        btnDailyReport, btnAdminLogout;
    btnAdminLogin2.setup(250, 375, 185, 45,
        "Login", font, btnGreen, btnGreenHover);
    btnAdminBack.setup(465, 375, 185, 45,
        "Back", font, btnRed, btnRedHover);
    btnAddDoctor.setup(50, 145, 370, 48,
        "Add Doctor", font, btnGreen, btnGreenHover);
    btnRemoveDoctor.setup(480, 145, 370, 48,
        "Remove Doctor", font, btnRed, btnRedHover);
    btnViewPatients.setup(50, 210, 370, 48,
        "View All Patients", font, btnBlue, btnHover);
    btnViewDoctors.setup(480, 210, 370, 48,
        "View All Doctors", font, btnBlue, btnHover);
    btnViewAllApp.setup(50, 275, 370, 48,
        "View All Appointments", font, btnBlue, btnHover);
    btnViewUnpaid.setup(480, 275, 370, 48,
        "View Unpaid Bills", font, btnBlue, btnHover);
    btnDischarge.setup(50, 340, 370, 48,
        "Discharge Patient", font, btnGray, btnGrayHover);
    btnSecLog.setup(480, 340, 370, 48,
        "Security Log", font, btnGray, btnGrayHover);
    btnDailyReport.setup(50, 405, 370, 48,
        "Daily Report", font, btnBlue, btnHover);
    btnAdminLogout.setup(480, 405, 370, 48,
        "Logout", font, btnRed, btnRedHover);
    // main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // input box events
            if (currentScreen == PATIENT_LOGIN) {
                idBox.handleEvent(event, window);
                passBox.handleEvent(event, window);
            }
            if (currentScreen == REGISTER_PATIENT) {
                regName.handleEvent(event, window);
                regAge.handleEvent(event, window);
                regGender.handleEvent(event, window);
                regContact.handleEvent(event, window);
                regPass.handleEvent(event, window);
            }
            if (currentScreen == DOCTOR_LOGIN) {
                docIdBox.handleEvent(event, window);
                docPassBox.handleEvent(event, window);
            }
            if (currentScreen == ADMIN_LOGIN) {
                adminIdBox.handleEvent(event, window);
                adminPassBox.handleEvent(event, window);
            }

            // click events
            if (event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button
                == sf::Mouse::Left) {

                // MAIN MENU clicks
                if (currentScreen == MAIN_MENU) {
                    if (btnPatientLogin.isHovered(window)) {
                        currentScreen = PATIENT_LOGIN;
                        idBox.clear();
                        passBox.clear();
                        messageText = "";
                    }
                    if (btnDoctorLogin.isHovered(window)) {
                        currentScreen = DOCTOR_LOGIN;
                        docIdBox.clear();
                        docPassBox.clear();
                        messageText = "";
                    }
                    if (btnAdminLogin.isHovered(window)) {
                        currentScreen = ADMIN_LOGIN;
                        adminIdBox.clear();
                        adminPassBox.clear();
                        messageText = "";
                    }
                    if (btnRegister.isHovered(window)) {
                        currentScreen = REGISTER_PATIENT;
                        regName.clear();
                        regAge.clear();
                        regGender.clear();
                        regContact.clear();
                        regPass.clear();
                        messageText = "";
                    }
                    if (btnExit.isHovered(window))
                        window.close();
                }

                // PATIENT LOGIN clicks
                if (currentScreen == PATIENT_LOGIN) {
                    if (btnLoginSubmit.isHovered(window)) {
                        string idStr = idBox.getValue();
                        string pass = passBox.getValue();
                        if (idStr.empty() || pass.empty()) {
                            messageText = "Please fill all fields!";
                            messageIsError = true;
                        }
                        else {
                            try {
                                int id = stoi(idStr);
                                Patient* p =
                                    patients.findById(id);
                                if (p != nullptr &&
                                    p->checkPassword(pass)) {
                                    loggedPatient = p;
                                    currentScreen = PATIENT_MENU;
                                    patientWelcome.setString(
                                        "Welcome, " +
                                        p->getName());
                                    balanceText.setString(
                                        "Balance: PKR " +
                                        to_string((int)
                                            p->getBalance()));
                                    infoContent =
                                        "Select an option above.";
                                    infoText.setString(
                                        infoContent);
                                    messageText = "";
                                }
                                else {
                                    messageText =
                                        "Invalid ID or Password!";
                                    messageIsError = true;
                                    FileHandler::logSecurityEvent(
                                        "Patient", idStr,
                                        "FAILED");
                                }
                            }
                            catch (...) {
                                messageText =
                                    "ID must be a number!";
                                messageIsError = true;
                            }
                        }
                    }
                    if (btnBack.isHovered(window)) {
                        currentScreen = MAIN_MENU;
                        messageText = "";
                    }
                }

                // PATIENT MENU clicks
                if (currentScreen == PATIENT_MENU
                    && loggedPatient != nullptr) {

                    if (btnViewApp.isHovered(window)) {
                        infoContent = "";
                        Appointment temp[100];
                        int count = 0;
                        for (int i = 0;
                            i < appointments.size(); i++) {
                            Appointment* a =
                                &appointments.getAll()[i];
                            if (a->getPatientId() ==
                                loggedPatient->getId()) {
                                temp[count++] = *a;
                            }
                        }
                        if (count == 0) {
                            infoContent =
                                "No appointments found.";
                        }
                        else {
                            sortAppointmentsByDate(
                                temp, count, true);
                            infoContent =
                                "ID | Doctor | Date"
                                " | Time | Status\n";
                            infoContent +=
                                "-----------------------------"
                                "-------------------\n";
                            for (int i = 0; i < count; i++) {
                                Doctor* d =
                                    doctors.findById(
                                        temp[i].getDoctorId());
                                string dName = (d != nullptr)
                                    ? d->getName()
                                    : "Unknown";
                                infoContent +=
                                    to_string(
                                        temp[i].getAppointmentId())
                                    + " | " + dName
                                    + " | " + temp[i].getDate()
                                    + " | " +
                                    temp[i].getTimeSlot()
                                    + " | " +
                                    temp[i].getStatus() + "\n";
                            }
                        }
                        infoText.setString(infoContent);
                    }

                    if (btnBills.isHovered(window)) {
                        infoContent = "";
                        float totalUnpaid = 0.0;
                        bool found = false;
                        infoContent =
                            "Bill ID | Amount"
                            " | Status | Date\n";
                        infoContent +=
                            "-----------------------------\n";
                        for (int i = 0;
                            i < bills.size(); i++) {
                            Bill* b = &bills.getAll()[i];
                            if (b->getPatientId() ==
                                loggedPatient->getId()) {
                                infoContent +=
                                    to_string(b->getBillId())
                                    + " | PKR " +
                                    to_string((int)
                                        b->getAmount())
                                    + " | " + b->getStatus()
                                    + " | " + b->getDate()
                                    + "\n";
                                if (b->getStatus() == "unpaid")
                                    totalUnpaid +=
                                    b->getAmount();
                                found = true;
                            }
                        }
                        if (!found)
                            infoContent = "No bills found.";
                        else
                            infoContent +=
                            "Total Unpaid: PKR " +
                            to_string((int)totalUnpaid);
                        infoText.setString(infoContent);
                    }

                    if (btnTopUp.isHovered(window)) {
                        infoContent =
                            "Top Up: Enter amount"
                            " in console window.";
                        infoText.setString(infoContent);
                        float amount;
                        cout << "Enter amount to top up: ";
                        cin >> amount;
                        if (amount > 0) {
                            *loggedPatient += amount;
                            FileHandler::updatePatient(
                                *loggedPatient);
                            balanceText.setString(
                                "Balance: PKR " +
                                to_string((int)
                                    loggedPatient->getBalance()));
                            infoContent =
                                "Balance updated! New"
                                " balance: PKR " +
                                to_string((int)
                                    loggedPatient->getBalance());
                            infoText.setString(infoContent);
                        }
                    }
                    if (btnBook.isHovered(window)) {
                        infoContent = "Available Doctors:\n";
                        infoContent += "ID | Name | Specialization | Fee\n";
                        infoContent += "---------------------------------\n";
                        for (int i = 0; i < doctors.size(); i++) {
                            Doctor* d = &doctors.getAll()[i];
                            infoContent += to_string(d->getId())
                                + " | " + d->getName()
                                + " | " + d->getSpecialization()
                                + " | PKR " + to_string((int)d->getFee())
                                + "\n";
                        }
                        infoContent += "\nEnter details in console window.";
                        infoText.setString(infoContent);
                        int doctorId;
                        string date, timeSlot;
                        cout << "\n--- Book Appointment ---" << endl;
                        cout << "Enter Doctor ID: ";
                        cin >> doctorId;
                        Doctor* doc = doctors.findById(doctorId);
                        if (doc == nullptr) {
                            infoContent = "Doctor not found!";
                        }
                        else if (loggedPatient->getBalance() < doc->getFee()) {
                            infoContent = "Insufficient balance! Top up first.";
                        }
                        else {
                            cout << "Enter Date (DD-MM-YYYY): ";
                            cin >> date;
                            if (!Validator::isValidDate(date)) {
                                infoContent = "Invalid date format!";
                            }
                            else {
                                cout << "Slots: 09:00 10:00 11:00 12:00"
                                    " 13:00 14:00 15:00 16:00" << endl;
                                cout << "Enter Time Slot: ";
                                cin >> timeSlot;
                                if (!Validator::isValidTimeSlot(timeSlot)) {
                                    infoContent = "Invalid time slot!";
                                }
                                else {
                                    bool slotTaken = false;
                                    for (int i = 0; i < appointments.size(); i++) {
                                        Appointment* a = &appointments.getAll()[i];
                                        if (a->getDoctorId() == doctorId &&
                                            a->getDate() == date &&
                                            a->getTimeSlot() == timeSlot &&
                                            a->getStatus() == "pending") {
                                            slotTaken = true;
                                            break;
                                        }
                                    }
                                    if (slotTaken) {
                                        infoContent = "Slot already booked! Choose another.";
                                    }
                                    else {
                                        *loggedPatient -= doc->getFee();
                                        FileHandler::updatePatient(*loggedPatient);
                                        int newAppId = getMaxId("appointments.txt") + 1;
                                        Appointment newApp(newAppId,
                                            loggedPatient->getId(),
                                            doctorId, date, timeSlot, "pending");
                                        appointments.add(newApp);
                                        FileHandler::saveAppointment(newApp);
                                        int newBillId = getMaxId("bills.txt") + 1;
                                        Bill newBill(newBillId,
                                            loggedPatient->getId(),
                                            newAppId, doc->getFee(), "paid", date);
                                        bills.add(newBill);
                                        FileHandler::saveBill(newBill);
                                        balanceText.setString(
                                            "Balance: PKR " +
                                            to_string((int)loggedPatient->getBalance()));
                                        infoContent = "Appointment booked! ID: "
                                            + to_string(newAppId)
                                            + " | PKR "
                                            + to_string((int)doc->getFee())
                                            + " deducted.";
                                    }
                                }
                            }
                        }
                        infoText.setString(infoContent);
                    }

                    if (btnCancelApp.isHovered(window)) {
                        infoContent = "Pending Appointments:\n";
                        infoContent += "ID | Doctor | Date | Time\n";
                        infoContent += "-------------------------\n";
                        bool found = false;
                        for (int i = 0; i < appointments.size(); i++) {
                            Appointment* a = &appointments.getAll()[i];
                            if (a->getPatientId() == loggedPatient->getId() &&
                                a->getStatus() == "pending") {
                                Doctor* d = doctors.findById(a->getDoctorId());
                                string dName = (d != nullptr)
                                    ? d->getName() : "Unknown";
                                infoContent += to_string(a->getAppointmentId())
                                    + " | " + dName
                                    + " | " + a->getDate()
                                    + " | " + a->getTimeSlot() + "\n";
                                found = true;
                            }
                        }
                        if (!found) {
                            infoContent = "No pending appointments.";
                            infoText.setString(infoContent);
                        }
                        else {
                            infoText.setString(infoContent);
                            int appId;
                            cout << "Enter Appointment ID to cancel: ";
                            cin >> appId;
                            Appointment* app = appointments.findById(appId);
                            if (app == nullptr ||
                                app->getPatientId() != loggedPatient->getId() ||
                                app->getStatus() != "pending") {
                                infoContent = "Invalid appointment ID!";
                            }
                            else {
                                Doctor* d = doctors.findById(app->getDoctorId());
                                float refund = (d != nullptr) ? d->getFee() : 0.0f;
                                app->setStatus("cancelled");
                                FileHandler::updateAppointment(*app);
                                *loggedPatient += refund;
                                FileHandler::updatePatient(*loggedPatient);
                                for (int i = 0; i < bills.size(); i++) {
                                    Bill* b = &bills.getAll()[i];
                                    if (b->getAppointmentId() == appId) {
                                        b->setStatus("cancelled");
                                        FileHandler::updateBill(*b);
                                        break;
                                    }
                                }
                                balanceText.setString(
                                    "Balance: PKR " +
                                    to_string((int)loggedPatient->getBalance()));
                                infoContent = "Appointment cancelled! PKR "
                                    + to_string((int)refund) + " refunded.";
                            }
                            infoText.setString(infoContent);
                        }
                    }

                    if (btnRecords.isHovered(window)) {
                        infoContent = "My Medical Records:\n";
                        infoContent += "Date | Doctor | Medicines | Notes\n";
                        infoContent += "---------------------------------\n";
                        bool found = false;
                        for (int i = 0; i < prescriptions.size(); i++) {
                            Prescription* pr = &prescriptions.getAll()[i];
                            if (pr->getPatientId() == loggedPatient->getId()) {
                                Doctor* d = doctors.findById(pr->getDoctorId());
                                string dName = (d != nullptr)
                                    ? d->getName() : "Unknown";
                                infoContent += pr->getDate()
                                    + " | " + dName
                                    + " | " + pr->getMedicines()
                                    + " | " + pr->getNotes() + "\n";
                                found = true;
                            }
                        }
                        if (!found)
                            infoContent = "No medical records found.";
                        infoText.setString(infoContent);
                    }

                    if (btnPay.isHovered(window)) {
                        infoContent = "Unpaid Bills:\n";
                        infoContent += "ID | Amount | Date\n";
                        infoContent += "-------------------\n";
                        bool found = false;
                        for (int i = 0; i < bills.size(); i++) {
                            Bill* b = &bills.getAll()[i];
                            if (b->getPatientId() == loggedPatient->getId() &&
                                b->getStatus() == "unpaid") {
                                infoContent += to_string(b->getBillId())
                                    + " | PKR " + to_string((int)b->getAmount())
                                    + " | " + b->getDate() + "\n";
                                found = true;
                            }
                        }
                        if (!found) {
                            infoContent = "No unpaid bills.";
                            infoText.setString(infoContent);
                        }
                        else {
                            infoText.setString(infoContent);
                            int billId;
                            cout << "Enter Bill ID to pay: ";
                            cin >> billId;
                            Bill* bill = bills.findById(billId);
                            if (bill == nullptr ||
                                bill->getPatientId() != loggedPatient->getId() ||
                                bill->getStatus() != "unpaid") {
                                infoContent = "Invalid bill ID!";
                            }
                            else if (loggedPatient->getBalance() < bill->getAmount()) {
                                infoContent = "Insufficient balance! Top up first.";
                            }
                            else {
                                *loggedPatient -= bill->getAmount();
                                bill->setStatus("paid");
                                FileHandler::updateBill(*bill);
                                FileHandler::updatePatient(*loggedPatient);
                                balanceText.setString(
                                    "Balance: PKR " +
                                    to_string((int)loggedPatient->getBalance()));
                                infoContent = "Bill paid successfully!";
                            }
                            infoText.setString(infoContent);
                        }
                    }

                    // logout stays last
                    if (btnLogout.isHovered(window)) {
                        loggedPatient = nullptr;
                        currentScreen = MAIN_MENU;
                        messageText = "";
                    }
                    if (btnLogout.isHovered(window)) {
                        loggedPatient = nullptr;
                        currentScreen = MAIN_MENU;
                        messageText = "";
                    }
                }

                // REGISTER clicks
                if (currentScreen == REGISTER_PATIENT) {
                    if (btnRegSubmit.isHovered(window)) {
                        string name = regName.getValue();
                        string ageStr = regAge.getValue();
                        string gender = regGender.getValue();
                        string contact = regContact.getValue();
                        string pass = regPass.getValue();

                        if (name.empty() || ageStr.empty() ||
                            gender.empty() ||
                            contact.empty() || pass.empty()) {
                            messageText = "Fill all fields!";
                            messageIsError = true;
                        }
                        else if (
                            !Validator::isValidContact(
                                contact)) {
                            messageText =
                                "Contact must be 11 digits!";
                            messageIsError = true;
                        }
                        else if (
                            !Validator::isValidPassword(pass)) {
                            messageText =
                                "Password min 6 characters!";
                            messageIsError = true;
                        }
                        else {
                            try {
                                int age = stoi(ageStr);
                                char g =
                                    toupper(gender[0]);
                                int newId =
                                    getMaxId("patients.txt")
                                    + 1;
                                Patient newP(newId, name,
                                    pass, age, g,
                                    contact, 0.0f);
                                patients.add(newP);
                                FileHandler::savePatient(newP);
                                messageText =
                                    "Registered! Your ID: "
                                    + to_string(newId)
                                    + " - Please login now.";
                                messageIsError = false;
                                regName.clear();
                                regAge.clear();
                                regGender.clear();
                                regContact.clear();
                                regPass.clear();
                            }
                            catch (...) {
                                messageText =
                                    "Age must be a number!";
                                messageIsError = true;
                            }
                        }
                    }
                    if (btnRegBack.isHovered(window)) {
                        currentScreen = MAIN_MENU;
                        messageText = "";
                    }
                }

                // DOCTOR LOGIN clicks
                if (currentScreen == DOCTOR_LOGIN) {
                    if (btnDocLogin.isHovered(window)) {
                        string idStr = docIdBox.getValue();
                        string pass = docPassBox.getValue();
                        if (idStr.empty() || pass.empty()) {
                            messageText =
                                "Please fill all fields!";
                            messageIsError = true;
                        }
                        else {
                            try {
                                int id = stoi(idStr);
                                Doctor* d =
                                    doctors.findById(id);
                                if (d != nullptr &&
                                    d->checkPassword(pass)) {
                                    loggedDoctor = d;
                                    currentScreen = DOCTOR_MENU;
                                    doctorWelcome.setString(
                                        "Welcome, Dr. " +
                                        d->getName());
                                    doctorFeeText.setString(
                                        "Specialization: " +
                                        d->getSpecialization()
                                        + "  |  Fee: PKR " +
                                        to_string((int)
                                            d->getFee()));
                                    infoContent =
                                        "Select an option.";
                                    infoText.setString(
                                        infoContent);
                                    messageText = "";
                                }
                                else {
                                    messageText =
                                        "Invalid ID or"
                                        " Password!";
                                    messageIsError = true;
                                }
                            }
                            catch (...) {
                                messageText =
                                    "ID must be a number!";
                                messageIsError = true;
                            }
                        }
                    }
                    if (btnDocBack.isHovered(window)) {
                        currentScreen = MAIN_MENU;
                        messageText = "";
                    }
                }

                // DOCTOR MENU clicks
                if (currentScreen == DOCTOR_MENU
                    && loggedDoctor != nullptr) {

                    if (btnViewToday.isHovered(window)) {
                        string today = getTodayDate();
                        infoContent =
                            "Today's Appointments ("
                            + today + "):\n";
                        infoContent +=
                            "ID | Patient | Time | Status\n";
                        infoContent +=
                            "-----------------------------\n";
                        bool found = false;
                        for (int i = 0;
                            i < appointments.size(); i++) {
                            Appointment* a =
                                &appointments.getAll()[i];
                            if (a->getDoctorId() ==
                                loggedDoctor->getId() &&
                                a->getDate() == today) {
                                Patient* p =
                                    patients.findById(
                                        a->getPatientId());
                                string pName =
                                    (p != nullptr)
                                    ? p->getName()
                                    : "Unknown";
                                infoContent +=
                                    to_string(
                                        a->getAppointmentId())
                                    + " | " + pName
                                    + " | " + a->getTimeSlot()
                                    + " | " + a->getStatus()
                                    + "\n";
                                found = true;
                            }
                        }
                        if (!found)
                            infoContent +=
                            "No appointments today.";
                        infoText.setString(infoContent);
                    }
                    if (btnMarkComplete.isHovered(window)) {
                        infoContent = "Enter Appointment ID in console.";
                        infoText.setString(infoContent);
                        int appId;
                        cout << "Enter Appointment ID to mark complete: ";
                        cin >> appId;
                        Appointment* app = appointments.findById(appId);
                        if (app == nullptr ||
                            app->getDoctorId() != loggedDoctor->getId() ||
                            app->getStatus() != "pending") {
                            infoContent = "Invalid appointment ID!";
                        }
                        else {
                            app->setStatus("completed");
                            FileHandler::updateAppointment(*app);
                            infoContent = "Appointment marked as completed!";
                        }
                        infoText.setString(infoContent);
                    }

                    if (btnMarkNoShow.isHovered(window)) {
                        infoContent = "Enter Appointment ID in console.";
                        infoText.setString(infoContent);
                        int appId;
                        cout << "Enter Appointment ID to mark no-show: ";
                        cin >> appId;
                        Appointment* app = appointments.findById(appId);
                        if (app == nullptr ||
                            app->getDoctorId() != loggedDoctor->getId() ||
                            app->getStatus() != "pending") {
                            infoContent = "Invalid appointment ID!";
                        }
                        else {
                            app->setStatus("no-show");
                            FileHandler::updateAppointment(*app);
                            for (int i = 0; i < bills.size(); i++) {
                                Bill* b = &bills.getAll()[i];
                                if (b->getAppointmentId() == appId) {
                                    b->setStatus("cancelled");
                                    FileHandler::updateBill(*b);
                                    break;
                                }
                            }
                            infoContent = "Appointment marked as no-show!";
                        }
                        infoText.setString(infoContent);
                    }

                    if (btnWritePresc.isHovered(window)) {
                        infoContent = "Enter details in console window.";
                        infoText.setString(infoContent);
                        int appId;
                        cout << "Enter Appointment ID: ";
                        cin >> appId;
                        Appointment* app = appointments.findById(appId);
                        if (app == nullptr ||
                            app->getDoctorId() != loggedDoctor->getId() ||
                            app->getStatus() != "completed") {
                            infoContent = "Invalid appointment ID or"
                                " appointment not completed!";
                            infoText.setString(infoContent);
                        }
                        else {
                            bool alreadyExists = false;
                            for (int i = 0; i < prescriptions.size(); i++) {
                                if (prescriptions.getAll()[i]
                                    .getAppointmentId() == appId) {
                                    alreadyExists = true;
                                    break;
                                }
                            }
                            if (alreadyExists) {
                                infoContent =
                                    "Prescription already written!";
                                infoText.setString(infoContent);
                            }
                            else {
                                string medicines, notes;
                                cin.ignore();
                                cout << "Enter medicines: ";
                                getline(cin, medicines);
                                cout << "Enter notes: ";
                                getline(cin, notes);
                                int newPrescId =
                                    getMaxId("prescriptions.txt") + 1;
                                string today = getTodayDate();
                                Prescription newPres(newPrescId, appId,
                                    app->getPatientId(),
                                    loggedDoctor->getId(),
                                    today, medicines, notes);
                                prescriptions.add(newPres);
                                FileHandler::savePrescription(newPres);
                                infoContent = "Prescription saved!";
                                infoText.setString(infoContent);
                            }
                        }
                    }

                    if (btnViewHistory.isHovered(window)) {
                        infoContent = "Enter Patient ID in console.";
                        infoText.setString(infoContent);
                        int patientId;
                        cout << "Enter Patient ID: ";
                        cin >> patientId;
                        bool hasAccess = false;
                        for (int i = 0; i < appointments.size(); i++) {
                            Appointment* a = &appointments.getAll()[i];
                            if (a->getPatientId() == patientId &&
                                a->getDoctorId() == loggedDoctor->getId() &&
                                a->getStatus() == "completed") {
                                hasAccess = true;
                                break;
                            }
                        }
                        if (!hasAccess) {
                            infoContent = "Access denied! You can only"
                                " view your own patients.";
                        }
                        else {
                            infoContent = "Patient History:\n";
                            infoContent += "Date | Medicines | Notes\n";
                            infoContent += "-------------------------\n";
                            bool found = false;
                            for (int i = 0; i < prescriptions.size(); i++) {
                                Prescription* pr =
                                    &prescriptions.getAll()[i];
                                if (pr->getPatientId() == patientId &&
                                    pr->getDoctorId() ==
                                    loggedDoctor->getId()) {
                                    infoContent += pr->getDate()
                                        + " | " + pr->getMedicines()
                                        + " | " + pr->getNotes() + "\n";
                                    found = true;
                                }
                            }
                            if (!found)
                                infoContent += "No records found.";
                        }
                        infoText.setString(infoContent);
                    }

                    if (btnDocLogout.isHovered(window)) {
                        loggedDoctor = nullptr;
                        currentScreen = MAIN_MENU;
                        messageText = "";
                    }
                    if (btnDocLogout.isHovered(window)) {
                        loggedDoctor = nullptr;
                        currentScreen = MAIN_MENU;
                        messageText = "";
                    }
                }
                // ADMIN MENU clicks
                if (currentScreen == ADMIN_MENU) {
                    if (btnViewPatients.isHovered(window)) {
                        infoContent = "All Patients:\n";
                        infoContent += "ID | Name | Age | Balance\n";
                        infoContent += "-------------------------\n";
                        for (int i = 0; i < patients.size(); i++) {
                            Patient* p = &patients.getAll()[i];
                            infoContent += to_string(p->getId())
                                + " | " + p->getName()
                                + " | " + to_string(p->getAge())
                                + " | PKR " +
                                to_string((int)p->getBalance()) + "\n";
                        }
                        infoText.setString(infoContent);
                    }
                    if (btnViewDoctors.isHovered(window)) {
                        infoContent = "All Doctors:\n";
                        infoContent += "ID | Name | Specialization | Fee\n";
                        infoContent += "--------------------------------\n";
                        for (int i = 0; i < doctors.size(); i++) {
                            Doctor* d = &doctors.getAll()[i];
                            infoContent += to_string(d->getId())
                                + " | " + d->getName()
                                + " | " + d->getSpecialization()
                                + " | PKR " +
                                to_string((int)d->getFee()) + "\n";
                        }
                        infoText.setString(infoContent);
                    }
                    if (btnViewAllApp.isHovered(window)) {
                        infoContent = "All Appointments:\n";
                        infoContent += "ID | Patient | Doctor | Date | Status\n";
                        infoContent += "-------------------------------------\n";
                        for (int i = 0; i < appointments.size(); i++) {
                            Appointment* a = &appointments.getAll()[i];
                            Patient* p = patients.findById(a->getPatientId());
                            Doctor* d = doctors.findById(a->getDoctorId());
                            string pName = (p != nullptr) ? p->getName() : "Unknown";
                            string dName = (d != nullptr) ? d->getName() : "Unknown";
                            infoContent += to_string(a->getAppointmentId())
                                + " | " + pName
                                + " | " + dName
                                + " | " + a->getDate()
                                + " | " + a->getStatus() + "\n";
                        }
                        infoText.setString(infoContent);
                    }
                    if (btnViewUnpaid.isHovered(window)) {
                        infoContent = "Unpaid Bills:\n";
                        infoContent += "ID | Patient | Amount | Date\n";
                        infoContent += "----------------------------\n";
                        for (int i = 0; i < bills.size(); i++) {
                            Bill* b = &bills.getAll()[i];
                            if (b->getStatus() == "unpaid") {
                                Patient* p = patients.findById(b->getPatientId());
                                string pName = (p != nullptr) ? p->getName() : "Unknown";
                                infoContent += to_string(b->getBillId())
                                    + " | " + pName
                                    + " | PKR " + to_string((int)b->getAmount())
                                    + " | " + b->getDate() + "\n";
                            }
                        }
                        infoText.setString(infoContent);
                    }
                    if (btnAddDoctor.isHovered(window)) {
                        infoContent = "Enter doctor details in console.";
                        infoText.setString(infoContent);
                        string name, spec, contact, password;
                        float fee;
                        cin.ignore();
                        cout << "Enter Name: ";
                        getline(cin, name);
                        cout << "Enter Specialization: ";
                        getline(cin, spec);
                        cout << "Enter Contact (11 digits): ";
                        cin >> contact;
                        cout << "Enter Password (min 6 chars): ";
                        cin >> password;
                        cout << "Enter Fee: ";
                        cin >> fee;
                        int newId = getMaxId("doctors.txt") + 1;
                        Doctor newDoc(newId, name, password, spec, contact, fee);
                        doctors.add(newDoc);
                        FileHandler::saveDoctor(newDoc);
                        infoContent = "Doctor added! ID: " + to_string(newId);
                        infoText.setString(infoContent);
                    }
                    if (btnRemoveDoctor.isHovered(window)) {
                        infoContent = "Enter Doctor ID in console.";
                        infoText.setString(infoContent);
                        int id;
                        cout << "Enter Doctor ID to remove: ";
                        cin >> id;
                        bool hasPending = false;
                        for (int i = 0; i < appointments.size(); i++) {
                            Appointment* a = &appointments.getAll()[i];
                            if (a->getDoctorId() == id &&
                                a->getStatus() == "pending") {
                                hasPending = true; break;
                            }
                        }
                        if (hasPending)
                            infoContent = "Cannot remove! Doctor has pending appointments.";
                        else {
                            doctors.removeById(id);
                            FileHandler::deleteDoctor(id);
                            infoContent = "Doctor removed successfully!";
                        }
                        infoText.setString(infoContent);
                    }
                    if (btnDischarge.isHovered(window)) {
                        infoContent = "Enter Patient ID in console.";
                        infoText.setString(infoContent);
                        int id;
                        cout << "Enter Patient ID to discharge: ";
                        cin >> id;
                        Patient* p = patients.findById(id);
                        if (p == nullptr) {
                            infoContent = "Patient not found!";
                        }
                        else {
                            bool hasUnpaid = false, hasPending = false;
                            for (int i = 0; i < bills.size(); i++) {
                                if (bills.getAll()[i].getPatientId() == id &&
                                    bills.getAll()[i].getStatus() == "unpaid") {
                                    hasUnpaid = true; break;
                                }
                            }
                            for (int i = 0; i < appointments.size(); i++) {
                                if (appointments.getAll()[i].getPatientId() == id &&
                                    appointments.getAll()[i].getStatus() == "pending") {
                                    hasPending = true; break;
                                }
                            }
                            if (hasUnpaid)
                                infoContent = "Cannot discharge! Unpaid bills exist.";
                            else if (hasPending)
                                infoContent = "Cannot discharge! Pending appointments exist.";
                            else {
                                FileHandler::archivePatient(id, patients,
                                    appointments, bills, prescriptions);
                                patients.removeById(id);
                                infoContent = "Patient discharged successfully!";
                            }
                        }
                        infoText.setString(infoContent);
                    }
                    if (btnSecLog.isHovered(window)) {
                        infoContent = "Security Log:\n--------------\n";
                        ifstream file("security_log.txt");
                        string line;
                        while (getline(file, line))
                            infoContent += line + "\n";
                        file.close();
                        infoText.setString(infoContent);
                    }
                    if (btnDailyReport.isHovered(window)) {
                        string today = getTodayDate();
                        int total = 0, pending = 0, completed = 0, noShow = 0;
                        float revenue = 0.0;
                        for (int i = 0; i < appointments.size(); i++) {
                            Appointment* a = &appointments.getAll()[i];
                            if (a->getDate() == today) {
                                total++;
                                if (a->getStatus() == "pending") pending++;
                                if (a->getStatus() == "completed") completed++;
                                if (a->getStatus() == "no-show") noShow++;
                            }
                        }
                        for (int i = 0; i < bills.size(); i++) {
                            Bill* b = &bills.getAll()[i];
                            if (b->getDate() == today &&
                                b->getStatus() == "paid")
                                revenue += b->getAmount();
                        }
                        infoContent = "Daily Report - " + today + "\n";
                        infoContent += "Total: " + to_string(total) + "\n";
                        infoContent += "Pending: " + to_string(pending) + "\n";
                        infoContent += "Completed: " + to_string(completed) + "\n";
                        infoContent += "No-Show: " + to_string(noShow) + "\n";
                        infoContent += "Revenue: PKR " + to_string((int)revenue);
                        infoText.setString(infoContent);
                    }
                    if (btnAdminLogout.isHovered(window)) {
                        currentScreen = MAIN_MENU;
                        messageText = "";
                    }
                }
                // ADMIN LOGIN clicks
                if (currentScreen == ADMIN_LOGIN) {
                    if (btnAdminLogin2.isHovered(window)) {
                        string idStr =
                            adminIdBox.getValue();
                        string pass =
                            adminPassBox.getValue();
                        if (idStr.empty() || pass.empty()) {
                            messageText =
                                "Please fill all fields!";
                            messageIsError = true;
                        }
                        else {
                            try {
                                int id = stoi(idStr);
                                if (admin.getId() == id &&
                                    admin.checkPassword(pass)) {
                                    currentScreen = ADMIN_MENU;
                                    messageText = "";
                                    infoContent = "Select an option.";
                                    infoText.setString(infoContent);
                                }
                                else {
                                    messageText =
                                        "Invalid Admin ID"
                                        " or Password!";
                                    messageIsError = true;
                                }
                            }
                            catch (...) {
                                messageText =
                                    "ID must be a number!";
                                messageIsError = true;
                            }
                        }
                    }
                    if (btnAdminBack.isHovered(window)) {
                        currentScreen = MAIN_MENU;
                        messageText = "";
                    }
                }
            }
        }

        // update hover effects
        if (currentScreen == MAIN_MENU) {
            btnPatientLogin.update(window);
            btnDoctorLogin.update(window);
            btnAdminLogin.update(window);
            btnRegister.update(window);
            btnExit.update(window);
        }
        if (currentScreen == PATIENT_LOGIN) {
            btnLoginSubmit.update(window);
            btnBack.update(window);
        }
        if (currentScreen == PATIENT_MENU) {
            btnBook.update(window);
            btnCancelApp.update(window);
            btnViewApp.update(window);
            btnRecords.update(window);
            btnBills.update(window);
            btnPay.update(window);
            btnTopUp.update(window);
            btnLogout.update(window);
        }
        if (currentScreen == REGISTER_PATIENT) {
            btnRegSubmit.update(window);
            btnRegBack.update(window);
        }
        if (currentScreen == DOCTOR_LOGIN) {
            btnDocLogin.update(window);
            btnDocBack.update(window);
        }
        if (currentScreen == DOCTOR_MENU) {
            btnViewToday.update(window);
            btnMarkComplete.update(window);
            btnMarkNoShow.update(window);
            btnWritePresc.update(window);
            btnViewHistory.update(window);
            btnDocLogout.update(window);
        }
        if (currentScreen == ADMIN_MENU) {
            btnAddDoctor.update(window);
            btnRemoveDoctor.update(window);
            btnViewPatients.update(window);
            btnViewDoctors.update(window);
            btnViewAllApp.update(window);
            btnViewUnpaid.update(window);
            btnDischarge.update(window);
            btnSecLog.update(window);
            btnDailyReport.update(window);
            btnAdminLogout.update(window);
        }

        // draw everything
        window.clear(bgColor);
        window.draw(topBar);
        window.draw(titleText);

        if (currentScreen == MAIN_MENU) {
            window.draw(subtitleText);
            btnPatientLogin.draw(window);
            btnDoctorLogin.draw(window);
            btnAdminLogin.draw(window);
            btnRegister.draw(window);
            btnExit.draw(window);
        }

        if (currentScreen == PATIENT_LOGIN) {
            window.draw(loginTitle);
            window.draw(idLabel);
            window.draw(passLabel);
            idBox.draw(window);
            passBox.draw(window);
            btnLoginSubmit.draw(window);
            btnBack.draw(window);
        }

        if (currentScreen == PATIENT_MENU) {
            window.draw(patientWelcome);
            window.draw(balanceText);
            btnBook.draw(window);
            btnCancelApp.draw(window);
            btnViewApp.draw(window);
            btnRecords.draw(window);
            btnBills.draw(window);
            btnPay.draw(window);
            btnTopUp.draw(window);
            btnLogout.draw(window);
            window.draw(infoBox);
            window.draw(infoText);
        }

        if (currentScreen == REGISTER_PATIENT) {
            window.draw(regTitle);
            window.draw(regNameLabel);
            window.draw(regAgeLabel);
            window.draw(regGenderLabel);
            window.draw(regContactLabel);
            window.draw(regPassLabel);
            regName.draw(window);
            regAge.draw(window);
            regGender.draw(window);
            regContact.draw(window);
            regPass.draw(window);
            btnRegSubmit.draw(window);
            btnRegBack.draw(window);
        }

        if (currentScreen == DOCTOR_LOGIN) {
            window.draw(docLoginTitle);
            window.draw(docIdLabel);
            window.draw(docPassLabel);
            docIdBox.draw(window);
            docPassBox.draw(window);
            btnDocLogin.draw(window);
            btnDocBack.draw(window);
        }

        if (currentScreen == DOCTOR_MENU) {
            window.draw(doctorWelcome);
            window.draw(doctorFeeText);
            btnViewToday.draw(window);
            btnMarkComplete.draw(window);
            btnMarkNoShow.draw(window);
            btnWritePresc.draw(window);
            btnViewHistory.draw(window);
            btnDocLogout.draw(window);
            window.draw(infoBox);
            window.draw(infoText);
        }

        if (currentScreen == ADMIN_LOGIN) {
            window.draw(adminLoginTitle);
            window.draw(adminIdLabel);
            window.draw(adminPassLabel);
            adminIdBox.draw(window);
            adminPassBox.draw(window);
            btnAdminLogin2.draw(window);
            btnAdminBack.draw(window);
        }
        if (currentScreen == ADMIN_MENU) {
            window.draw(adminMenuTitle);
            btnAddDoctor.draw(window);
            btnRemoveDoctor.draw(window);
            btnViewPatients.draw(window);
            btnViewDoctors.draw(window);
            btnViewAllApp.draw(window);
            btnViewUnpaid.draw(window);
            btnDischarge.draw(window);
            btnSecLog.draw(window);
            btnDailyReport.draw(window);
            btnAdminLogout.draw(window);
            window.draw(infoBox);
            window.draw(infoText);
        }
        // draw message at bottom
        if (!messageText.empty()) {
            msgText.setString(messageText);
            msgText.setFillColor(messageIsError ?
                sf::Color(231, 76, 60) :
                sf::Color(46, 204, 113));
            window.draw(msgText);
        }

        window.display();
    }
   

    return 0;
}
string getTodayDate() {
    time_t now = time(0);
    char buffer[15];
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", &timeInfo);
    return string(buffer);
}

int getMaxId(const string& filename) {
    ifstream file(filename);
    int maxId = 0;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        int id = stoi(line.substr(0, line.find(',')));
        if (id > maxId) maxId = id;
    }
    file.close();
    return maxId;
}

void sortAppointmentsByDate(Appointment* arr, int n,
    bool ascending) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool shouldSwap;
            if (ascending)
                shouldSwap =
                arr[j].getDate() > arr[j + 1].getDate();
            else
                shouldSwap =
                arr[j].getDate() < arr[j + 1].getDate();
            if (shouldSwap) {
                Appointment temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sortPrescriptionsByDate(Prescription* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].getDate() < arr[j + 1].getDate()) {
                Prescription temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}