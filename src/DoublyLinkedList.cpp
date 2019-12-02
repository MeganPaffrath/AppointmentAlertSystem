
#include <stdio.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <fstream>
#include <limits>
#include "DoublyLinkedList.h"
#include "../include/fencrypt.h"
#undef max

typedef std::chrono::system_clock Clock;

//#include <vector>
using namespace std;


// Done by: Megan Paffrath
DoublyLinkedList::DoublyLinkedList() {
	this->head = nullptr;
	this->location = nullptr;
}

DoublyLinkedList::~DoublyLinkedList() {
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

// Done by: Megan Paffrath
void DoublyLinkedList::initializeList(string fName, string lName, string phone, string apts) {
	
	//Create a new patient instance (Node)
	Patient* newPatient = new Patient;
	newPatient->fName = fName;
	newPatient->lName = lName;
	newPatient->phoneNumber = phone;


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
}

bool DoublyLinkedList::numberValidator(string phoneInput) {
    // parse phone number:
    string tempNumber = phoneInput;
    vector <string> tokens;
    stringstream parseDate(tempNumber);
    
    string parsedItem;
    
    while(getline(parseDate, parsedItem, '-'))
    {
     //           cout << "x: " << parsedItem << endl;
        tokens.push_back(parsedItem);
    }
    
//    cout << tokens[0] << " . " << tokens[1] << " . " << tokens[2] << endl;
    
    // not right number of '-'
    if (tokens.size() !=  3) {
        return false;
    }
    
    // bad formatting
    if (tokens[0].size() != 3 || tokens[1].size() != 3 || tokens[2].size() != 4) {
        return false;
    }
    
    return true;
}

// Done by: Megan Paffrath
bool DoublyLinkedList::oldDate(string dateInput) {
    bool oldDate = false;
    // Set current date
    // scr: stack overflow
    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);
    int thisYear = 1900 + parts->tm_year;
    int thisMonth = parts->tm_mon + 1;
    int thisDay = parts->tm_mday;
//    cout << "Year : " << thisYear << " Month: " << thisMonth << " Day: " << thisDay << endl;

    // convert input stringto date:
    string tempDate = dateInput;
    vector <string> tokens;
    stringstream parseDate(tempDate);
    
    string parsedItem;
    
    while(getline(parseDate, parsedItem, '/'))
    {
//        cout << "x: " << parsedItem << endl;
        tokens.push_back(parsedItem);
    }
    
    int apptYear = stoi(tokens[2]) + 2000;
    int apptMonth = stoi(tokens[0]);
    int apptDay = stoi(tokens[1]);
    
    
//    cout << "Year given: " << apptYear << " Month: " << apptMonth << " Day: " << apptDay << endl;
    
    if (apptYear < thisYear) {
        oldDate = true;// old appt
    }
    if (apptYear == thisYear) { // if this year, check month and date
        if (apptMonth < thisMonth) {
            oldDate = true; // old appt
        }
        if (apptMonth == thisMonth) { // if this month, check date
            if (apptDay < thisDay)
                oldDate = true; // old appt
        }
        
    }
    if (oldDate) {
        cout << "\n   !!!       " << dateInput << " is on old date.       !!!" << endl;
        return true;
    }
    
    
    return false;
}

// Done by: Megan Paffrath
bool DoublyLinkedList::dateValidator(string dateInput) {
    string tempDate = dateInput;
    vector <string> tokens;
    stringstream parseDate(tempDate);
    
    string parsedItem;
    
    while(getline(parseDate, parsedItem, '/'))
    {
//        cout << "x: " << parsedItem << endl;
        tokens.push_back(parsedItem);
    }
    
    
    if (tokens.size() < 3 || tokens.size() > 3) { // not valid date input
        return false;
    }
    
    // if date is too large
    if (stoi(tokens[0]) > 12) { // cant have over 12 months
        return false;
    }
    if (stoi(tokens[1]) > 31) { // cant have over 31 days
        return false;
    }
    if (stoi(tokens[2]) > 100) { // too many digits for year
        return false;
    }
    
    // check if old date:
    if (oldDate(dateInput)) {
        return false;
    }
    
    
    return true;
}


//   Done by: Jose Javier III
bool timeValidator(std::string input_)
{
	//   time format: HH:MM[A/P]
	int tempBits1 = 0;
	int tempBits2 = 0;
	string tempString;
	string tempAMPM;
	vector<string> bits;
	stringstream temp(input_);


	while (getline(temp, tempString, ':'))
	{bits.push_back(tempString);}


	tempAMPM = toupper(bits[1][2]);


	if (tempAMPM == "A" || tempAMPM == "P")
	{
		temp.clear();
		temp.str("");
		temp << bits[1];


		if (tempAMPM == "A")
		{getline(temp, tempString, 'A');}

		else
		{getline(temp, tempString, 'P');}


		tempBits1 = stoi(bits[0]);
		tempBits2 = stoi(tempString);


		if (tempBits1 < 1 || tempBits1 > 12 || tempBits2 < 0 || tempBits2 > 59)
		{return false;}

		return true;
	}

	return false;
}

// Done by: Megan Paffrath
void DoublyLinkedList::appendPatient(twilio::Twilio twilioObj, string fromNumber, bool testMode) { // Assumes all names start w/ capital letters (fix)
	// Prepare new patient 'node'
	cout << "\n   ----------------------------------------" << endl;
	cout << "   ---         Add a New Patient        ---" << endl;
	cout << "   ----------------------------------------\n" << endl;
	Patient* newPatient = new Patient;
	cout << "     First Name: ";
	cin >> newPatient->fName;
    newPatient->fName[0] = toupper(newPatient->fName[0]);
	cout << "     Last Name: ";
	cin >> newPatient->lName;
    newPatient->lName[0] = toupper(newPatient->lName[0]);
    cout << "     Phone Number (###-###-####): ";
	cin >> newPatient->phoneNumber;
    while (!numberValidator(newPatient->phoneNumber)) { // while bad phone number
		cout << "\n   !!!       Invalid input. Please try again.       !!!\n" << endl;
        cout << "     Phone Number (###-###-####): ";
        cin >> newPatient->phoneNumber;
    }
    

	Appointment* newAppointment = new Appointment;
	cout << "     Appointment Date (MM/DD/YY): ";
	cin >> newAppointment->date;
    while (!dateValidator(newAppointment->date)) { // while bad appt date
		cout << "\n   !!!       Invalid input. Please try again.       !!!\n" << endl;
        cout << "     Appointment Date (MM/DD/YY): ";
        cin >> newAppointment->date;
    }
    cout << "     Appointment Time (HH:MM[a or p]): ";
	cin >> newAppointment->time;


	while (!timeValidator(newAppointment->time))
	{
		cout << "\n   !!!       Invalid input. Please try again.       !!!\n" << endl;
		cout << "     Appointment Time (HH:MM[a or p]): ";
		cin >> newAppointment->time;
	}

	cout << endl;

	newPatient->appointments.push_back(*newAppointment);

	cout << "\n   ---       Patient Added!       ---\n" << endl;
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
}

//   Created by Jose Javier III
void DoublyLinkedList::deletePatient()   // sets location to node to be edited
{
	string phoneNumber;
	
	cout << "     Enter phone number: ";
	cin >> phoneNumber;


	if (!numberValidator(phoneNumber))
	{
		cout << "\n   !!!       Invalid Input. Please try again.       !!!\n" << endl;
		cout << "     Phone Number: ";
		cin >> phoneNumber;
	}
	

	cout << "\n" << endl;

	prevLoc = nullptr;
	location = head;

	if (location != nullptr) {
		while (location != nullptr) {
			if (location->phoneNumber == phoneNumber) {
				removePatient(location, prevLoc);	//if found, call the removePatient method passing location of the trailer and current pointers
				return;
			}
			prevLoc = location;
			location = location->next;
		}
	}
    
    // no patient was deleted
    cout << "\n   !!!       Error: Patient not found to delete.       !!!" << endl << endl;
}

void DoublyLinkedList::findPatient() { // sets location to node to be edited
	string phoneNumber;
	

	cout << "     Enter in the Patient's Phone Number: ";
	cin >> phoneNumber;

	if (!numberValidator(phoneNumber))
	{
		cout << "\n   !!!       Invalid Input. Please try again.       !!!\n" << endl;
		cout << "     Phone Number: ";
		cin >> phoneNumber;
	}

	cout << "\n" << endl;

	prevLoc = nullptr;
	location = head;

	if (location != nullptr) {
		while (location != nullptr) {
			if (location->phoneNumber == phoneNumber) {
				break;
			}
			prevLoc = location;
			location = location->next;
		}
	}
}

// Done by: Megan Paffrath
void DoublyLinkedList::editAppointmentForPatient(twilio::Twilio twilioObj, string fromNumber, bool testMode) { // currently only lets user add an appointment
	if (head == nullptr)
	{
		cout << "\n   !!!       List is empty.       !!!\n" << endl;
		return;
	}

	else
	{
		
		cout << "\n   ------------------------------------------------" << endl;
		cout << "   ---            Edit an Appointment           ---" << endl;
		cout << "   ------------------------------------------------\n" << endl;
		cout << "   !!!       NOTE: Unable to modify appointments.       !!!\n" << endl;

		findPatient();

		if (location == nullptr) {
			cout << "\n   !!!       Patient not found.       !!!\n" << endl;
		}
		else {
			cout << "     Patient Found: " << location->fName << " " << location->lName << endl << endl;


			Appointment* newAppointment = new Appointment;
			cout << "\tAdd Apt Date: ";
			cin >> newAppointment->date;
			while (!dateValidator(newAppointment->date)) { // while bad appt date
				cout << "\n   !!!       Invalid input. Please try again.       !!!\n" << endl;
				cout << "     Appointment Date (MM/DD/YY): ";
				cin >> newAppointment->date;
			}

			cout << "\tAdd Apt Time: ";
			cin >> newAppointment->time;
			while (!timeValidator(newAppointment->time))
			{
				cout << "\n   !!!       Invalid input. Please try again.       !!!\n" << endl;
				cout << "     Appointment Time (HH:MM[a or p]): ";
				cin >> newAppointment->time;
			}

			location->appointments.push_back(*newAppointment);

			sendMessage(location->phoneNumber, fromNumber, location->fName, newAppointment->date, newAppointment->time, twilioObj, testMode);

		}
	}
}


// REMOVE: takes in pointers to the current location and previous location, if found, from findPatient() method
// Done by: Megan Paffrath
void DoublyLinkedList::removePatient(Patient* patientLoc, Patient* trailerLoc) {

	//Edge case: Empty (no patients)
	if (isEmpty()) {
		cout << "No patients to remove..\n";
	}
	else {
		//remove the node that was found
		Patient* curr = patientLoc;	//set a temporary pointer to the location at which findPatient() location stopped
		Patient* trail = trailerLoc;

		cout << "   ---       " << curr->fName << " " << curr->lName << " has been removed.       ---\n" << endl;
		//relink our doubly link

		if (curr == head)
		{
			delete curr;
			head = nullptr;
			curr = nullptr;
			trail = nullptr;
		}

		else
		{
			trail->next = curr->next;
			curr->prev = trail;
			delete curr;
		}
	}
}

// VIEW:
// Done by: Megan Paffrath
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




// :
// Done by: Megan Paffrath
void DoublyLinkedList::removeOldAppointments() {
    cout << "\n--- Removing old Appointments: ---\n" << endl;
    location = head;
    if (head == nullptr) {
        cout << "List is empty, no appointments to remove." << endl;
    }
    else {
        while (location != nullptr) {
            cout << location->lName << ", " << location->fName << endl;
            cout << "\tAppointments and times: " << endl;
            // iterate through appts:
            for (int i = 0; i < location->appointments.size(); i++) {
                string currDateCheck = location->appointments[i].date;
                cout << "Checking: " << currDateCheck;
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
	string line, password, temp;
	int phraseLength;

	ifstream readFile("Patients.txt");

	if (readFile.is_open()) {

		cout << "     Enter Password: ";
		cin >> password;

		getline(readFile, line); // ignore first line


		decrypt(line, "*=+tHe_+Bar4v1Ath_Gr0uP!+_ro0c35!!");


		if (password != line)
		{
			cout << "\n   !!!       Incorrect password.       !!!\n" << endl;
			failPW_ = true;
			return;
		}

		cout << "\n   ---       Data decrypted.       ---\n" << endl;

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
		cout << "\n     Welcome to the Baraviath Group's Appointment Alert System!" << endl;
		cout << "     This is a program used to keep track of appointment information" << endl;
		cout << "     for patients, and notify them when appointments are imminent.\n" << endl;
		cout << "     To get started, enter in any key and press Enter...\n" << endl;
		cout << "     > ";
		cin >> temp;
		cout << "\n" << endl;
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
			// cout << "List is empty, nothing to write" << endl;
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


				//cout << "Appending: " << appendLine; // idea of what will be appended

				encrypt(appendLine, password_);

				writeFile << appendLine << endl;
				// APPEND LINE TO TEXT DOC HERE ----------------------------------------------------------------

				location = location->next;
			}
		}
	}
	else {
		cout << "\n   !!!       Error: Unable to save file.       !!!\n " << endl;
	}

}

bool DoublyLinkedList::isEmpty() const
{
	return head == nullptr;
}
