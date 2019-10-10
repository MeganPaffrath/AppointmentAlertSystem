

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


class DoublyLinkedList {
private:
    struct Patient {
        string fName;
        string lName;
        string phoneNumber;
        int appointmentCount = 0;
//        string aptDateTime[10][10]; // { {"MM/YY", "hh:mmxm"}, ... , {"MM/YY", "hh:mmxm"} }
//        vector<string[2]> aptDateTime;
        Patient* next;
        Patient* prev;
    };
    
    Patient* head;
    Patient* location; // used for iteration
    Patient* prevLoc;
    
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    
    // INSERT:
    void appendPatient(); // adds a patient into list in alphabetical order by last name
    
    // EDIT:
    void editAppointmentForPatient();
    
    // REMOVE:
    void removePatient();
    
    // VIEW:
    void viewPatients(); // prints the list data
    
    // SORTS:
//    void alphabeticSort(); // sorts list in alphabetical order
//    void dateSort(); // sort in order of upcoming appointments
    
    // TEXT:
    void textSender(); // if appointment is in 5 days, send reminder to patient
    
    
};

#endif
