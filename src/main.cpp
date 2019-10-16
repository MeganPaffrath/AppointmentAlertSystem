
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
#include <unistd.h>
#include <vector>

#include "SendSMS.h"
#include "KeyGetter.h"
#include "DoublyLinkedList.h"
#include "../include/twilio.h"

using namespace std;


int main()
{
    // MESSAGE SENDING ABILITY -------------------------------------------------------------V
    bool testMode = true; // true = won't actualy send messages
    
    KeyGetter keyGetter;
    keyGetter.setValues();
    string megansPhoneNumber = keyGetter.getMegansPhoneNumber();
    string twilioPhoneNumber = keyGetter.getTwilioPhoneNumber();
    
    auto twilioObj = std::make_shared<twilio::Twilio>(keyGetter.getTwilioSID(), keyGetter.getTwilioToken());
    
//    sendMessage(megansPhoneNumber, twilioPhoneNumber, "Megan", "1/20/20", "11:00am", *twilioObj, testMode);
    
    // MESSAGE SENDING ABILITY - END ---------------------------------------------------------^
    
    
    // NEXT PROGRAMMER: initialize LL from text file using following funtions ----------------------V
    DoublyLinkedList ourPatients; // create DLL
    
    cout << "****READING FILE: " << endl;
    ourPatients.fileReader(); // put initializeList function within this function when you read from it plz
    cout << "****FILE DONE BEING READ " << endl;
    ourPatients.viewPatients(); // this should show exactly what is in txt file when you are done
    
    
    
    // DLL done being initialized from txt file ---------------------------------------------------^
    
    
    // USER CAN NOW MAKE CHANGES ------------------------------------- V
    
    // MENU:
    char menuItem = 'x';
    while (menuItem != 'Q') {
        cout << "Menu --------------" << endl;
        cout << "\tP: Add a patient" << endl;
        cout << "\tA: Edit/add appointment info" << endl;
        cout << "\tV: View all Patients" << endl;
        cout << "\tQ: Quit" << endl;
        cout << "\n\tSelection: ";
        cin >> menuItem;
        cout << endl;
        
        if (menuItem == 'Q' || menuItem == 'q') {
            cout << "Quitting program...\n" << endl;
            break;
        } else if (menuItem == 'P' || menuItem == 'p') {
            ourPatients.appendPatient(*twilioObj, twilioPhoneNumber, testMode); // do not input names starting w/ lowercase (fix later)
        } else if (menuItem == 'A' || menuItem == 'a') {
            cout << "You currently can only add apointments." << endl; // add in text function when apt added
            ourPatients.editAppointmentForPatient(*twilioObj, twilioPhoneNumber, testMode);
        } else if (menuItem == 'V' || menuItem == 'v') {
            ourPatients.viewPatients();
        } else {
            cout << "Invalid input. Try again" << endl;
        }
    }
    
    // USER IS DONE MAKING CHANGES ------------------------------------ ^
    
    
    
    // LINKED LIST IS SAVED BACK INTO TEXT FILE -------------------------------------V
    ourPatients.fileWriter(); // not complete. Just basics of how DLL works are shown
    // TEXT FILE DONE BEING RECREATED------------------------------------------------^
    
    return 0;
}


