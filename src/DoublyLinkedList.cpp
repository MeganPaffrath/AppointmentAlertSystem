
#include <stdio.h>
#include <iostream>
#include <fstream>
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
    
    // parse apts string into apts **********************FINISH, might be better way

    istringstream iss(apts);
    string word;
    // Make new appointment before each comma (and if a comma is found
    while(iss >> word) {
        if (word.find("/") != string::npos) {
            Appointment *newAppointment = new Appointment;
            newAppointment->date = word;
            bool endFound = false;
            while (!endFound && iss >> word) { // go to next word
                if (word.find("at") != string::npos) {
                    // ignore
                } else if (word.find(":") != string::npos) { // is time
                    endFound = true;
                    if (word.find(",") != string::npos) {
                        // remove comma from string
                        word.erase(word.end()-1, word.end());
                    }
                    newAppointment->time = word;
                }
            }
            newPatient->appointments.push_back(*newAppointment);
//            cout << "appended " << newAppointment->date << " at " << newAppointment->time << endl;
        }
    }
    
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
    
    cout << "Appended " << newPatient->fName << " " << newPatient->lName << endl;
}
void DoublyLinkedList::appendPatient(twilio::Twilio twilioObj, string fromNumber, bool testMode) { // Assumes all names start w/ capital letters (fix)
    // Prepare new patient 'node'
    cout << "ADD A NEW PATIENT: " << endl;
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
    
    cout << "Patient Added!" << endl;
    sendMessage(newPatient->phoneNumber, fromNumber, newPatient->fName, newAppointment->date, newAppointment->time, twilioObj, testMode);
    
    
    // Find location to insert after:
    location = head;
    prevLoc = nullptr;
    while ((location != nullptr) && (newPatient->lName > location->lName)) { // next location
//        cout << newPatient->lName << " > " << location->lName << endl;
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
    
//    cout << "END" <<endl;
}

void DoublyLinkedList::findPatient() { // sets location to node to be edited
    string lName, fName;
    cout << "Last Name: ";
    cin >> lName;
    cout << "First Name: ";
    cin >> fName;
    
    location = head;
    if (location != nullptr) {
        while (location != nullptr) {
            if (location->lName == lName && location->fName == fName) {
                return;
            }
            location = location->next;
        }
    }
}

// EDIT:
void DoublyLinkedList::editAppointmentForPatient(twilio::Twilio twilioObj, string fromNumber, bool testMode) { // currently only lets user add an appointment
    cout << "Find patient in system to edit: " << endl;
    findPatient();
    
    if (location == nullptr) {
        cout << "The Patient was not found." << endl;
    } else {
        cout << "Patient Found: " << location->fName << " " << location->lName << endl;
    }
    
    Appointment *newAppointment = new Appointment;
    cout << "\tAdd Apt Date: ";
    cin >> newAppointment->date;
    cout << "\tAdd Apt Time: ";
    cin >> newAppointment->time;
    
    location->appointments.push_back(*newAppointment);
    
    sendMessage(location->phoneNumber, fromNumber, location->fName, newAppointment->date, newAppointment->time, twilioObj, testMode);
}

// REMOVE:
void DoublyLinkedList::removePatient() {
    
}

// VIEW:
void DoublyLinkedList::viewPatients() {
    cout << "\n--- All Patients and Appointments ---\n" << endl;
    location = head;
    if (head == nullptr) {
        cout << "List is empty" << endl;
    } else {
        while (location != nullptr) {
            cout << location->lName << ", " << location->fName << endl;
            cout << "\tPhone: " << location->phoneNumber << endl;;
            cout << "\tAppointments and times: " << endl;
            for (int i = 0; i < location->appointments.size(); i++) {
                cout << "\t\t" << location->appointments[i].date << " at " << location->appointments[i].time << endl;
            }
            location = location->next;
        }
    }
    cout << "-----------------------------------------\n" << endl;
}

// SORTS:
//    void alphabeticSort(); // sorts list in alphabetical order
//    void dateSort(); // sort in order of upcoming appointments


// File Reader:
void DoublyLinkedList::fileReader() {
    string line;
    int phraseLength;
    ifstream readFile("Patients.txt");
    if (readFile.is_open()) {
        getline(readFile,line); // ignore first line
        while(getline(readFile,line)) {
            string fName, lName, phone, aptInfo;
            // prep each line section:
            istringstream iss(line);
            string word;
            if(iss >> word) {
                word.erase(word.end()-1, word.end());
//                cout << "lName: " << word << endl;
                lName = word;
                phraseLength = int(word.length());
//                cout << "LEN: " << phraseLength << endl;
                line.erase(line.begin(), line.begin()+phraseLength);
            }
            if(iss >> word) {
//                cout << "fName: " << word << endl;
                fName = word;
                phraseLength = int(word.length()) + 1;
//                cout << "LEN: " << phraseLength << endl;
                line.erase(line.begin(), line.begin()+phraseLength);
            }
            if (iss >> word) {
//                cout << "Phone: " << word << endl;
                phone = word;
                phraseLength = int(word.length()) + 1;
//                cout << "LEN: " << phraseLength << endl;
                line.erase(line.begin(), line.begin()+phraseLength);
            }
//            cout << "D: " << line << endl;
            aptInfo = line;
            
            
            
//            cout << line << endl; // break up each line into inputs for initialize
            initializeList(fName, lName, phone, aptInfo);
        }
        readFile.close();
    } else {
        cout << "Could not read from file."; 
    }
}
// File Writer:
void DoublyLinkedList::fileWriter() {
    
    ofstream writeFile ("Patients.txt");
    if (writeFile.is_open()) {
        // Write string:
        string firstString = "lName, fName Phone Appointments \n";
        writeFile << firstString;
        
        // Prepare & write one string per patient
        location = head;
        if (head == nullptr) {
            cout << "List is empty, nothing to write" << endl;
        } else {
            while (location != nullptr) {
                string appendLine;
                appendLine = location->lName + ", " + location->fName + " " + location->phoneNumber + " "; // needs better formatting than tabs probably
                // figure out how to implement and add location->appointments
                
                // String of appointments:
                for (int i = 0; i < location->appointments.size()-1; i++) {
                    appendLine = appendLine + location->appointments[i].date + " at " + location->appointments[i].time + ", ";
                }
                // Last appointment
                int lastApt = int(location->appointments.size()-1);
                appendLine = appendLine + location->appointments[lastApt].date + " at " + location->appointments[lastApt].time + " ";
                
                appendLine = appendLine + "\n";
                
                cout << "Appending: " << appendLine; // idea of what will be appended
                writeFile << appendLine;
                // APPEND LINE TO TEXT DOC HERE ----------------------------------------------------------------
                
                location = location->next;
            }
        }
    } else {
        cout << "Unable to open file to write to. " << endl;
    }
    

    
}
