// NEED:
//stdio.h, stdlib.h, unistd.h - C POSIX libraries
//libcurl - Client-side transfer library
// libcurl is already on mac, if you're not on a mac ... get libcurl
//iostream, sstream, string - C++ Standard Libraries

// Must run with curl linker
// Xcode: https://stackoverflow.com/questions/10269343/libcurl-wont-work-xcode

// Current working directory: src folder

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <memory.h>

#include "SendSMS.h"
#include "KeyGetter.h"
#include "DoublyLinkedList.h"
#include "../include/twilio.h"

// Windows / Mac
#ifdef __APPLE__
    #include <unistd.h>
#else
    #include <io.h>
#endif

using namespace std;



int main()
{
	// MESSAGE SENDING ABILITY -------------------------------------------------------------V
	bool testMode = true; // true = won't actually send messages

	KeyGetter keyGetter;
	keyGetter.setValues();
	string megansPhoneNumber = keyGetter.getMegansPhoneNumber();
	string twilioPhoneNumber = keyGetter.getTwilioPhoneNumber();

	auto twilioObj = std::make_shared<twilio::Twilio>(keyGetter.getTwilioSID(), keyGetter.getTwilioToken());

	//    sendMessage(megansPhoneNumber, twilioPhoneNumber, "Megan", "1/20/20", "11:00am", *twilioObj, testMode);

		// MESSAGE SENDING ABILITY - END ---------------------------------------------------------^


		// NEXT PROGRAMMER: initialize LL from text file using following funtions ----------------------V
	DoublyLinkedList ourPatients; // create DLL
	bool failPW = false;
    
//    cout << "Valid? : " << ourPatients.dateValidator("11/30/19") << endl;
//    cout << "Valid? : " << ourPatients.numberValidator("999-999-111") << endl;


	cout << "****READING FILE: " << endl;
	ourPatients.fileReader(failPW); // put initializeList function within this function when you read from it plz




	// DLL done being initialized from txt file ---------------------------------------------------^


		// USER CAN NOW MAKE CHANGES ------------------------------------- V

	// MENU:
	if (!failPW)
	{
		cout << "****FILE DONE BEING READ " << endl;
		ourPatients.viewPatients(); // this should show exactly what is in txt file when you are done


		char menuItem = 'x';
		while (menuItem != 'Q') {
			cout << "Menu --------------" << endl;
			cout << "\tA: Add a patient" << endl;
			cout << "\tE: Edit/add appointment info" << endl;
			cout << "\tV: View all Patients" << endl;
			cout << "\tR: Remove Patient" << endl;
			cout << "\tQ: Quit" << endl;
			cout << "\n\tSelection: ";
			cin >> menuItem;
			cout << endl;

			if (menuItem == 'Q' || menuItem == 'q') {
				cout << "Quitting program...\n" << endl;
				break;
			}
			else if (menuItem == 'A' || menuItem == 'a') {
				ourPatients.appendPatient(*twilioObj, twilioPhoneNumber, testMode); // do not input names starting w/ lowercase (fix later)
			}
			else if (menuItem == 'E' || menuItem == 'e') {
				cout << "You currently can only add apointments." << endl; // add in text function when apt added
				ourPatients.editAppointmentForPatient(*twilioObj, twilioPhoneNumber, testMode);
			}
			else if (menuItem == 'V' || menuItem == 'v') {
				ourPatients.viewPatients();
			}
			else if (menuItem == 'R' || menuItem == 'r') {
				ourPatients.deletePatient();
			}
			else {
				cout << "Invalid input. Try again" << endl;
			}
		}

		// USER IS DONE MAKING CHANGES ------------------------------------ ^




	// LINKED LIST IS SAVED BACK INTO TEXT FILE -------------------------------------V
		string password;
		cout << "Enter Password to secure the database: ";
		cin >> password;

		ourPatients.fileWriter(password); // not complete. Just basics of how DLL works are shown
		cout << "\n   ---       Database secured.       ---" << endl;
		// TEXT FILE DONE BEING RECREATED------------------------------------------------^

	}

	return 0;
}
