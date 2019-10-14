
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
    // MESSAGE SENDING FUNCTION USE - IMPLEMENT LATER --------------------------------------------V
    bool testMode = true; // true = won't actualy send messages
    
    KeyGetter keyGetter;
    keyGetter.setValues();
    string megansPhoneNumber = keyGetter.getMegansPhoneNumber();
    string twilioPhoneNumber = keyGetter.getTwilioPhoneNumber();
    
    auto twilioObj = std::make_shared<twilio::Twilio>(keyGetter.getTwilioSID(), keyGetter.getTwilioToken());
    
    SendSMS sendText;
    sendText.sendMessage(megansPhoneNumber, twilioPhoneNumber, "Megan", "1/20/20", "11:00am", *twilioObj, testMode);
    
    // MESSAGE SENDING FUNCTION USE - END ---------------------------------------------------------^
    
    
    // NEXT PROGRAMMER: initialize LL from text file using following funtions ----------------------V
    DoublyLinkedList ourPatients; // create DLL
    
    cout << "****READING FILE: " << endl;
    ourPatients.fileReader(); // put initializeList function within this function when you read from it plz
    cout << "****FILE DONE BEING READ " << endl;
    ourPatients.viewPatients(); // this should show exactly what is in txt file when you are done
    
    
    
    // DLL done being initialized from txt file ---------------------------------------------------^
    
    
    // USER CAN NOW MAKE CHANGES ------------------------------------- V
    
    // MAKE A MENU:
//
//    ourPatients.appendPatient(); // do not input names starting w/ lowercase (fix later)
//    ourPatients.viewPatients();
//    ourPatients.editAppointmentForPatient(); // only lets user add an appt as of now to ensure vector works, not fully functional yet
//    ourPatients.viewPatients();
    
    // USER IS DONE MAKING CHANGES ------------------------------------ ^
    
    
    
    // LINKED LIST IS SAVED BACK INTO TEXT FILE -------------------------------------V
    ourPatients.fileWriter(); // not complete. Just basics of how DLL works are shown
    // TEXT FILE DONE BEING RECREATED------------------------------------------------^
    
    return 0;
}


