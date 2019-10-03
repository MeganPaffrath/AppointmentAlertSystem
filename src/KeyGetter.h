//
//  KeyGetter.h
//  SendText
//
//  Created by Megan Paffrath on 10/2/19.
//  Copyright © 2019 Megan Paffrath. All rights reserved.
//

#ifndef KeyGetter_h
#define KeyGetter_h
#include <iostream>
using namespace std;

class KeyGetter {
private:
    string megansPhoneNumber;
    string twilioSID;
    string twilioToken;
    string twilioPhoneNumber;
public:
    void setValues();
    string getTwilioSID();
    string getTwilioToken();
    string getTwilioPhoneNumber();
    string getMegansPhoneNumber();
    
    
};

#endif /* KeyGetter_h */
