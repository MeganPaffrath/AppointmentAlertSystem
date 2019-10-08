//
//  main.cpp
//  SendText
//
//  Created by Megan Paffrath on 10/2/19.
//  Copyright © 2019 Megan Paffrath. All rights reserved.
//

// NEED:
//stdio.h, stdlib.h, unistd.h - C POSIX libraries
//libcurl - Client-side transfer library
// libcurl is already on mac, if you're not on a mac ... get libcurl
//iostream, sstream, string - C++ Standard Libraries

// Must run with curl linker
// Xcode: https://stackoverflow.com/questions/10269343/libcurl-wont-work-xcode

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/twilio.h"
#include "SendSMS.h"
#include "KeyGetter.h"
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
    
    return 0;
}

