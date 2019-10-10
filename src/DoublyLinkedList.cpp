
#include <stdio.h>
#include <iostream>
#include "DoublyLinkedList.h"
using namespace std;



DoublyLinkedList::DoublyLinkedList() {
    this->head = nullptr;
    this->location = nullptr;
}
DoublyLinkedList::~DoublyLinkedList() { // DO
    // remove all
}

// INSERT:
void DoublyLinkedList::appendPatient() {
    // Prepare new patient 'node'
    Patient *newPatient = new Patient;
    string lastName;
    cout << "Last Name: ";
    cin >> lastName;
    newPatient->lName = lastName;
    
    
    // Find location to insert after:
    location = head;
    prevLoc = nullptr;
    while ((location != nullptr) && (lastName > location->lName)) { // next location
        cout << lastName << " > " << location->lName << endl;
        prevLoc = location;
        location = location->next;

    }

    cout << "out of if" << endl;
    
    // Insert 'node' between prevLoc and location
    if (prevLoc == nullptr && location == nullptr) { // make only first 'node'
        cout << "1" << endl;
        head = newPatient;
        newPatient->next = nullptr;
        newPatient->prev = nullptr;
    } else if (location == nullptr) { // if at end
        cout << "3" << endl;
        prevLoc->next = newPatient;
        newPatient->prev = prevLoc;
        newPatient->next = nullptr;
    } else if (prevLoc == nullptr) { // insert first node before location
        cout << "2" << endl;
        head = newPatient;
        newPatient->next = location;
        location->prev = newPatient;
        newPatient->prev = nullptr;
    } else { // in the middle and before location
        cout << "4" << endl;
        prevLoc->next = newPatient;
        location->prev = newPatient;
        newPatient->prev = prevLoc;
        newPatient->next = location;
    }
    
    cout << "made" << endl;
}

// EDIT:
void DoublyLinkedList::editAppointmentForPatient() {
    
}

// REMOVE:
void DoublyLinkedList::removePatient() {
    
}

// VIEW:
void DoublyLinkedList::viewPatients() {
    location = head;
    if (head == nullptr) {
        cout << "List is empty" << endl;
    } else {
        while (location->next != nullptr) {
            cout << location->lName << ", ";
            location = location->next;
        }
        cout << location->lName << endl;
    }
}

// SORTS:
//    void alphabeticSort(); // sorts list in alphabetical order
//    void dateSort(); // sort in order of upcoming appointments

// TEXT:
void DoublyLinkedList::textSender() {
    
}
