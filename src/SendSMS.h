//
//  SendSMS.h
//  SendText
//
//  Created by Megan Paffrath on 10/2/19.
//  Copyright © 2019 Megan Paffrath. All rights reserved.
//

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
