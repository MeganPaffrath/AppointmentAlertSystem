

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../include/twilio.h"
#include "SendSMS.h"
using namespace std;


class DoublyLinkedList {
private:
    struct Appointment {
        string date;
        string time;
    };
    struct Patient {
        string fName;
        string lName;
        string phoneNumber;
        vector<Appointment> appointments;
        Patient* next;
        Patient* prev;
    };
    
    Patient* head;
    Patient* tail;
    Patient* location; // used for iteration
    Patient* prevLoc;
    
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    
    // INSERT:
    void initializeList(string fName, string lName, string phone, string apts); // appends patients w/ info as args
    void appendPatient(twilio::Twilio twilioObj, string fromNumber, bool testMode); // adds a patient into list in alphabetical order by last name
    bool numberValidator(string phoneInput); // true if valid phone #
    bool dateValidator(string dateInput); // validates if date input is okay or not, calls old date
    bool oldDate(string dateInput); // returns true of old date
    void findPatient();
    
    // EDIT:
    void editAppointmentForPatient(twilio::Twilio twilioObj, string fromNumber, bool testMode);
    
    
    // REMOVE: takes in pointer to the location of patient if it exists via findPatient method
    void removePatient(Patient*,Patient*);
    void deletePatient(); // was written in place of removePatient? verify what way is better?
    void removeOldAppointments(); // cleans up appintment info
    
    // VIEW:
    void viewPatients(); // prints the list data
    
    // SORTS:
//    void alphabeticSort(); // sorts list in alphabetical order
//    void dateSort(); // sort in order of upcoming appointments
    


    
    
    // File Reader:
    void fileReader(bool& failPW_); // reads Patients.txt file and initializes DLL

    // FILE WRITER:
    void fileWriter(string password_); // writes Patient list Patients.txt

	bool isEmpty() const;
    
};

#endif
