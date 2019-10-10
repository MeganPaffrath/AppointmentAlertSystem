
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
    bool testMode = true; // true = won't actuall send messages
    
    KeyGetter keyGetter;
    keyGetter.setValues();
    string megansPhoneNumber = keyGetter.getMegansPhoneNumber();
    string twilioPhoneNumber = keyGetter.getTwilioPhoneNumber();
    
    auto twilioObj = std::make_shared<twilio::Twilio>(keyGetter.getTwilioSID(), keyGetter.getTwilioToken());
    
    SendSMS sendText;
    sendText.sendMessage(megansPhoneNumber, twilioPhoneNumber, "Megan", "never", "neverOClock", *twilioObj, testMode);
    
    // MESSAGE SENDING FUNCTION USE - END ---------------------------------------------------------^
    
    
    // NEXT PROGRAMMER: initialize LL from text file using following funtions ----------------------V
    DoublyLinkedList ourPatients;
    ourPatients.initializeList("Bob", "Smith", "8937238294", "long string of apt information to be included later");
    ourPatients.initializeList("Abby", "Jones", "3237238294", "long string of apt information to be included later");
    ourPatients.initializeList("Anna", "Zavier", "1237238294", "long string of apt information to be included later");
    ourPatients.viewPatients();
    
    // DLL done being initialized from txt file ---------------------------------------------------^
    
    
    
    // USER CAN NOW MAKE CHANGES ------------------------------------- V
    
            ourPatients.appendPatient();
            ourPatients.viewPatients();
        //    ourPatients.appendPatient();
        //    ourPatients.viewPatients();
        //    ourPatients.appendPatient();
        //    ourPatients.viewPatients();
    
    // USER IS DONE MAKING CHANGES ------------------------------------ ^
    
    
    
    // LINKED LIST IS SAVED BACK INTO TEXT FILE -------------------------------------V
    // ..
    // TEXT FILE DONE BEING RECREATED------------------------------------------------^
    
    return 0;
}


