//  SendSMS.h
//  Created Megan Paffrath
//  Used to send text message to patients


#ifndef SendSMS_h
#define SendSMS_h

#include <iostream>
#include "../include/twilio.h"
#include "KeyGetter.h"
using namespace std;


class SendSMS{
public:
    //    SendSMS(); // initiate twilio object
    bool sendMessage(string toNumber, string fromNumber, string toName, string aptDate, string time, twilio::Twilio twilioObj, bool testMode);
    
    
};
#endif /* SendSMS_h */
