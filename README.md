# -MediCore-Hospital-System-Project
 Hospital Management System using C++ and SFML(ok?)
# MediCore Hospital System Project:

## GitHub Repository
https://github.com/alishb918/-MediCore-Hospital-System-

## Description
Hospital Management System (sfml used)

##All  Classes used in project:
1) Person (base class)
2) Patient (inherits from Person)
3) Doctor (inherits from Person)
4) Admin (inherits from Person)
5) Appointment
6) Bill
7) Prescription
8) Storage (template class)
9) FileHandler
10) Validator
11) HospitalException

MAin concept used in  project:
1) Patient Login and Registration(booking appointment, paying bill etc)
2) Doctor Login with full menu (all appointments, prescreption, bill etc)
3)Admin Panel with all functions
 can see all Appointment Bookings and Cancellations, Bill Payment, Prescription System, Security Logging for failed login attempts


 How to Compile and Run
1. Visual Studio 2022 used
2.  SFML version 2.6.2 used
3. C/C++ - General - Additional Include Directories:
   C:\Users\YourName\Desktop\SFML-2.6.1\include
4. Linker - General - Additional Library Directories:
   C:\Users\YourName\Desktop\SFML-2.6.1\lib
5. Linker - Input - Additional Dependencies add:
   sfml-graphics-d.lib
   sfml-window-d.lib
   sfml-system-d.lib
6. Copy these DLL files to x64\Debug\ folder:
   sfml-graphics-d-2.dll
   sfml-window-d-2.dll
   sfml-system-d-2.dll
7. Build and Run

........ Login id and passwordsL:
Patient ID: 1, Password: laila1
 Patient ID: 2, Password: ahil5
 Doctor ID: 1, Password: zainab123
 Doctor ID: 2, Password: rubab123
 Doctor ID: 3, Password: marwa123
 Admin ID: 1, Password: ahmed12345

zip file contains all the the .cpp and .h files
