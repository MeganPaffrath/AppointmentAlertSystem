//  SendSMS.cpp
//  Created Megan Paffrath
//  Used to send text message to patients

#include <stdio.h>
#include "SendSMS.h"

// toNumber: 0000000000 (10 digit phone number)
// toName: Name of message reciever
// aptData: MM/DD format
// aptTime: 00:00pm or 00:00am
bool sendMessage(string toNumber, string fromNumber, string toName, string aptDate, string time, twilio::Twilio twilioObj, bool testMode) {
    string message = "Hello " + toName + " you have an upcoming appointment scheduled for " + aptDate + " at " + time + ".";
    string response, picture_url; // needed to work (req. by twillio)
    bool verbose = false;
    
    if (!testMode) {
        bool sent = twilioObj.send_message(toNumber, fromNumber, message, response, picture_url, verbose);
        if (sent) {
            cout << "Message was sent to " + toName + " at " + toNumber <<endl;
        }
        return sent;
    } else {
        string sentMessage = "\n-----\nmsg would be sent to " + toName + " at " + toNumber + ": \n";
        string message = "Hello " + toName + " you have an upcoming appointment scheduled for " + aptDate + " at " + time + ".";
        sentMessage = sentMessage + message + "\n-----\n";
        
        cout << sentMessage;
        return false;
    }
}


