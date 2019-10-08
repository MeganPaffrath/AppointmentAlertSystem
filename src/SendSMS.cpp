//
//  SendSMS.cpp
//  SendText
//
//  Created by Megan Paffrath on 10/2/19.
//  Copyright © 2019 Megan Paffrath. All rights reserved.
//

#include <stdio.h>
#include "SendSMS.h"
//#include "../include/twilio.h"


// toNumber: 0000000000 (10 digit phone number)
// toName: Name of message reciever
// aptData: MM/DD format
// aptTime: 00:00pm or 00:00am
bool SendSMS::sendMessage(string toNumber, string fromNumber, string toName, string aptDate, string time, twilio::Twilio twilioObj, bool testMode) {
    string message = "Hello " + toName + " you have an upcoming appointment scheduled for " + aptDate + " at " + time + ".";
    string response; // not sure what this is
    string picture_url; // not sure what this is
    bool verbose = false;
    
    if (!testMode) {
        bool sent = twilioObj.send_message(toNumber, fromNumber, message, response, picture_url, verbose);
        if (sent) {
            cout << "Message was sent to " + toName + " at " + toNumber <<endl;
        }
        return sent;
    } else {
        string sentMessage = "-----\nmsg would be sent to " + toName + " at " + toNumber + ": \n";
        string message = "Hello " + toName + " you have an upcoming appointment scheduled for " + aptDate + " at " + time + ".";
        sentMessage = sentMessage + message + "\n-----\n";

        cout << sentMessage;
        return false;
    }
}

