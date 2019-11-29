
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "DoublyLinkedList.h"
#include "../include/fencrypt.h"
//#include <vector>
using namespace std;



DoublyLinkedList::DoublyLinkedList() {
	this->head = nullptr;
	this->location = nullptr;
}
DoublyLinkedList::~DoublyLinkedList() { // DO
	//does nothing if no nodes exist as no space is allocated 
	if (!isEmpty()) {
		//if not not empty (e.g: there are nodes existing on heap)

		//set our pointers
		location = head;
		prevLoc = location -> next;
		
		while (true) {
			delete location;
			location = prevLoc;

			if(location == nullptr)
			{break;}

			prevLoc = location -> next;
		}
	}
}

// INSERT:
void DoublyLinkedList::initializeList(string fName, string lName, string phone, string apts) {
	
	//Create a new patient instance (Node)
	Patient* newPatient = new Patient;
	newPatient->fName = fName;
	newPatient->lName = lName;
	newPatient->phoneNumber = phone;

	// parse apts string into apts **********************FINISH, might be better way

	istringstream iss(apts);	//see C++ docs on istringstream 
	string word;
	// Make new appointment before each comma (and if a comma is found
	while (iss >> word) {
		if (word.find("/") != string::npos) {
			Appointment* newAppointment = new Appointment;
			newAppointment->date = word;
			bool endFound = false;
			while (!endFound && iss >> word) { // go to next word
				if (word.find("at") != string::npos) {
					// ignore
				}
				else if (word.find(":") != string::npos) { // is time
					endFound = true;
					if (word.find(",") != string::npos) {
						// remove comma from string
						word.erase(word.end() - 1, word.end());
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
	}
	else { // insert after tail.
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
	Patient* newPatient = new Patient;
	cout << "First Name: ";
	cin >> newPatient->fName;
	cout << "Last Name: ";
	cin >> newPatient->lName;
	cout << "Phone Number: ";
	cin >> newPatient->phoneNumber;

	Appointment* newAppointment = new Appointment;
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
	}
	else if (location == nullptr) { // if at end
//        cout << "3" << endl;
		prevLoc->next = newPatient;
		newPatient->prev = prevLoc;
		newPatient->next = nullptr;
		tail = newPatient; // set tail
	}
	else if (prevLoc == nullptr) { // insert first node before location
//        cout << "2" << endl;
		head = newPatient;
		newPatient->next = location;
		location->prev = newPatient;
		newPatient->prev = nullptr;
	}
	else { // in the middle and before location
//        cout << "4" << endl;
		prevLoc->next = newPatient;
		location->prev = newPatient;
		newPatient->prev = prevLoc;
		newPatient->next = location;
	}

	//    cout << "END" <<endl;
}

//   Created by Jose Javier III
void DoublyLinkedList::deletePatient()   // sets location to node to be edited
{ 
	string lName, fName;
	cout << "Last Name: ";
	cin >> lName;
	cout << "First Name: ";
	cin >> fName;

	prevLoc = nullptr;
	location = head;

	if (location != nullptr) {
		while (location != nullptr) {
			if (location->lName == lName && location->fName == fName) {
				removePatient(location, prevLoc);	//if found, call the removePatient method passing location of the trailer and current pointers
				return;
			}
			prevLoc = location;
			location = location->next;
		}
	}
}

void DoublyLinkedList::findPatient() { // sets location to node to be edited
	string lName, fName;
	cout << "Last Name: ";
	cin >> lName;
	cout << "First Name: ";
	cin >> fName;

	prevLoc = nullptr;
	location = head;

	if (location != nullptr) {
		while (location != nullptr) {
			if (location->lName == lName && location->fName == fName) {
				break;
			}
			prevLoc = location;
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
	}
	else {
		cout << "Patient Found: " << location->fName << " " << location->lName << endl;


		Appointment* newAppointment = new Appointment;
		cout << "\tAdd Apt Date: ";
		cin >> newAppointment->date;
		cout << "\tAdd Apt Time: ";
		cin >> newAppointment->time;

		location->appointments.push_back(*newAppointment);

		sendMessage(location->phoneNumber, fromNumber, location->fName, newAppointment->date, newAppointment->time, twilioObj, testMode);
	}
}

// REMOVE: takes in pointers to the current location and previous location, if found, from findPatient() method
void DoublyLinkedList::removePatient(Patient* patientLoc, Patient* trailerLoc) {

	//Edge case: Empty (no patients)
	if (isEmpty()) {
		cout << "No patients to remove..\n";
	}
	else {
		
		//remove the node that was found
		Patient* curr = patientLoc;	//set a temporary pointer to the location at which findPatient() location stopped
		Patient* trail = trailerLoc;

		cout << curr->fName << " " << curr->lName << " has been removed\n";
		//relink our doubly link
		trail->next = curr->next;
		curr->prev = trail;
		delete curr;
	}
}

// VIEW:
void DoublyLinkedList::viewPatients() {
	cout << "\n--- All Patients and Appointments ---\n" << endl;
	location = head;
	if (head == nullptr) {
		cout << "List is empty" << endl;
	}
	else {
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
void DoublyLinkedList::fileReader(bool& failPW_) {
	string line, password;
	int phraseLength;

	ifstream readFile("Patients.txt");

	if (readFile.is_open()) {

		cout << "Enter Password: ";
		cin >> password;

		getline(readFile, line); // ignore first line


		decrypt(line, "*=+tHe_+Bar4v1Ath_Gr0uP!+_ro0c35!!");


		if (password != line)
		{
			cout << "\n   !!!       Incorrect password.       !!!\n" << endl;
			failPW_ = true;
			return;
		}

		while (true) {
			string fName, lName, phone, aptInfo;


			// prep each line section:
			getline(readFile, line);

			if (readFile.eof())
			{break;}

			decrypt(line, password);

			istringstream iss(line);
			string word;

			if (iss >> word) {
				word.erase(word.end() - 1, word.end());
				//                cout << "lName: " << word << endl;
				lName = word;
				phraseLength = int(word.length());
				//                cout << "LEN: " << phraseLength << endl;
				line.erase(line.begin(), line.begin() + phraseLength);
			}

			if (iss >> word) {
				//                cout << "fName: " << word << endl;
				fName = word;
				phraseLength = int(word.length()) + 1;
				//                cout << "LEN: " << phraseLength << endl;
				line.erase(line.begin(), line.begin() + phraseLength);
			}

			if (iss >> word) {
				//                cout << "Phone: " << word << endl;
				phone = word;
				phraseLength = int(word.length()) + 1;
				//                cout << "LEN: " << phraseLength << endl;
				line.erase(line.begin(), line.begin() + phraseLength);
			}

			//            cout << "D: " << line << endl;
			aptInfo = line;



			//            cout << line << endl; // break up each line into inputs for initialize
			initializeList(fName, lName, phone, aptInfo);
		}
		readFile.close();
	}

	else {
		cout << "Could not read from file.";
	}
}
// File Writer:
void DoublyLinkedList::fileWriter(string password_) {

	ofstream writeFile("Patients.txt");

	if (writeFile.is_open()) {

		// Write string:
		string firstString = password_;

		encrypt(firstString, "*=+tHe_+Bar4v1Ath_Gr0uP!+_ro0c35!!");


		writeFile << firstString << endl;

		// Prepare & write one string per patient
		location = head;

		if (head == nullptr) {
			cout << "List is empty, nothing to write" << endl;
		}
		else {
			while (location != nullptr) {
				string appendLine = "";
				appendLine = location->lName + ", " + location->fName + " " + location->phoneNumber + " "; // needs better formatting than tabs probably
				// figure out how to implement and add location->appointments

				// String of appointments:
				for (int i = 0; i < location->appointments.size() - 1; i++) {
					appendLine = appendLine + location->appointments[i].date + " at " + location->appointments[i].time + ", ";
				}

				// Last appointment
				int lastApt = int(location->appointments.size() - 1);
				appendLine = appendLine + location->appointments[lastApt].date + " at " + location->appointments[lastApt].time + " ";


				cout << "Appending: " << appendLine; // idea of what will be appended

				encrypt(appendLine, password_);

				writeFile << appendLine << endl;
				// APPEND LINE TO TEXT DOC HERE ----------------------------------------------------------------

				location = location->next;
			}
		}
	}
	else {
		cout << "Unable to open file to write to. " << endl;
	}



}

bool DoublyLinkedList::isEmpty() const
{
	return head == nullptr;
}
