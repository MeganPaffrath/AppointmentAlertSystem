
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
    bool testMode = true; // true = won't actuall send messages
    
    KeyGetter keyGetter;
    keyGetter.setValues();
    string megansPhoneNumber = keyGetter.getMegansPhoneNumber();
    string twilioPhoneNumber = keyGetter.getTwilioPhoneNumber();
    
    auto twilioObj = std::make_shared<twilio::Twilio>(keyGetter.getTwilioSID(), keyGetter.getTwilioToken());
    
    SendSMS sendText;
    sendText.sendMessage(megansPhoneNumber, twilioPhoneNumber, "Megan", "never", "neverOClock", *twilioObj, testMode);
    
    DoublyLinkedList ourPatients;
    
    ourPatients.appendPatient();
    ourPatients.viewPatients();
    ourPatients.appendPatient();
    ourPatients.viewPatients();
    ourPatients.appendPatient();
    ourPatients.viewPatients();
    
    return 0;
}


