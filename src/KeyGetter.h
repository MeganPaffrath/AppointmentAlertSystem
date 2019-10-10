//  KeyGetter.h
//  Created Megan Paffrath
//  Used to gather keys to gain ability to send messages

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

