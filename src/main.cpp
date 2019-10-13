
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
    sendText.sendMessage(megansPhoneNumber, twilioPhoneNumber, "Megan", "never", "neverOClock", *twilioObj, testMode);
    
    // MESSAGE SENDING FUNCTION USE - END ---------------------------------------------------------^
    
    
    // NEXT PROGRAMMER: initialize LL from text file using following funtions ----------------------V
    DoublyLinkedList ourPatients; // create DLL
    
    ourPatients.fileReader(); // put initializeList function within this function when you read from it plz
    ourPatients.viewPatients(); // this should show exactly what is in txt file when you are done
    
    // Ex of initializeList (remove this section once fileReader is completed properly):
    ourPatients.initializeList("Bob", "Smith", "999999999", "1/23/20 at 2:00pm, 2/22/20 at 11:00am"); // patient w/ 2 apts
    ourPatients.initializeList("Abby", "Jones", "8888888888", ""); // patient w/ no apts
    ourPatients.viewPatients();
    
    // DLL done being initialized from txt file ---------------------------------------------------^
    
    
    // USER CAN NOW MAKE CHANGES ------------------------------------- V
    
    ourPatients.appendPatient(); // do not input names starting w/ lowercase (fix later)
    ourPatients.viewPatients();
    ourPatients.editAppointmentForPatient(); // only lets user add an appt as of now to ensure vector works
    ourPatients.viewPatients();
    
//    ourPatients.editAppointmentForPatient();
//    ourPatients.viewPatients();
//    ourPatients.appendPatient();
//    ourPatients.viewPatients();
//    ourPatients.appendPatient();
//    ourPatients.viewPatients();
    
    // USER IS DONE MAKING CHANGES ------------------------------------ ^
    
    
    
    // LINKED LIST IS SAVED BACK INTO TEXT FILE -------------------------------------V
    ourPatients.fileWriter(); // not complete. Just basics of how DLL works are shown
    // TEXT FILE DONE BEING RECREATED------------------------------------------------^
    
    return 0;
}


