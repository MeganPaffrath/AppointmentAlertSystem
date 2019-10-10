
#include <stdio.h>
#include <iostream>
#include "DoublyLinkedList.h"
//#include <vector>
using namespace std;



DoublyLinkedList::DoublyLinkedList() {
    this->head = nullptr;
    this->location = nullptr;
}
DoublyLinkedList::~DoublyLinkedList() { // DO
    // remove all
}

// INSERT:
void DoublyLinkedList::initializeList(string fName, string lName, string phone, string apts) {
    Patient *newPatient = new Patient;
    newPatient->fName = fName;
    newPatient->lName = lName;
    newPatient->phoneNumber = phone;
    
    // ADD APPOINTMENT INFORMATION IN LATER, for now ignore... ********************************************
    
    // insert node (list should be in alphabetical order from the start)
    location = head;
    if (location == nullptr) { // insert first and only node
        head = newPatient;
        newPatient->next = nullptr;
        newPatient->prev = nullptr;
        tail = newPatient; // set tail
    } else { // insert after tail.
        tail->next = newPatient;
        newPatient->prev = tail;
        newPatient->next = nullptr;
        tail = newPatient;
    }
}
void DoublyLinkedList::appendPatient() { // Assumes all names start w/ capital letters (fix)
    // Prepare new patient 'node'
    Patient *newPatient = new Patient;
    cout << "First Name: ";
    cin >> newPatient->fName;
    cout << "Last Name: ";
    cin >> newPatient->lName;
    cout << "Phone Number: ";
    cin >> newPatient->phoneNumber;

    Appointment *newAppointment = new Appointment;
    cout << "Appointment Date: ";
    cin >> newAppointment->date;
    cout << "Appointment Time: ";
    cin >> newAppointment->time;
    
    newPatient->appointments.push_back(*newAppointment);
    
    // Find location to insert after:
    location = head;
    prevLoc = nullptr;
    while ((location != nullptr) && (newPatient->lName > location->lName)) { // next location
        cout << newPatient->lName << " > " << location->lName << endl;
        prevLoc = location;
        location = location->next;
    }

    
    // Insert 'node' between prevLoc and location
    if (prevLoc == nullptr && location == nullptr) { // make only first 'node'
//        cout << "1" << endl;
        head = newPatient;
        newPatient->next = nullptr;
        newPatient->prev = nullptr;
    } else if (location == nullptr) { // if at end
//        cout << "3" << endl;
        prevLoc->next = newPatient;
        newPatient->prev = prevLoc;
        newPatient->next = nullptr;
        tail = newPatient; // set tail
    } else if (prevLoc == nullptr) { // insert first node before location
//        cout << "2" << endl;
        head = newPatient;
        newPatient->next = location;
        location->prev = newPatient;
        newPatient->prev = nullptr;
    } else { // in the middle and before location
//        cout << "4" << endl;
        prevLoc->next = newPatient;
        location->prev = newPatient;
        newPatient->prev = prevLoc;
        newPatient->next = location;
    }
}

// EDIT:
void DoublyLinkedList::editAppointmentForPatient() {
    
}

// REMOVE:
void DoublyLinkedList::removePatient() {
    
}

// VIEW:
void DoublyLinkedList::viewPatients() {
    cout << "--- All Patients and Appointments ---\n" << endl;
    location = head;
    if (head == nullptr) {
        cout << "List is empty" << endl;
    } else {
        while (location != nullptr) {
            cout << location->lName << ", " << location->fName << endl;
            cout << "\tPhone: " << location->phoneNumber << endl;;
            cout << "\tAppointments and times: " << endl;
            for (int i = 0; i < location->appointments.size(); i++) {
                cout << "\t\t" << location->appointments[0].date << " at " << location->appointments[0].time << endl;
            }
            location = location->next;
        }
    }
}

// SORTS:
//    void alphabeticSort(); // sorts list in alphabetical order
//    void dateSort(); // sort in order of upcoming appointments

// TEXT:
void DoublyLinkedList::textSender() {
    
}
