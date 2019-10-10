//  KeyGetter.cpp
//  Created Megan Paffrath
//  Used to gather keys to gain ability to send messages

#include <stdio.h>
#include "KeyGetter.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;



void KeyGetter::setValues() {
    string line;
    ifstream myfile ("keys.txt");
    if (myfile.is_open())
    {
        if (getline (myfile,line)) {
            twilioSID = line.substr(0, line.find(' '));
        }
        if (getline (myfile,line)) {
            twilioToken = line.substr(0, line.find(' '));
        }
        if (getline (myfile,line)) {
            twilioPhoneNumber = line.substr(0, line.find(' '));
        }
        if (getline (myfile,line)) {
            megansPhoneNumber = line.substr(0, line.find(' '));
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}

string KeyGetter::getTwilioSID() {
    return twilioSID;
}
string KeyGetter::getTwilioToken() {
    return twilioToken;
}
string KeyGetter::getTwilioPhoneNumber() {
    return twilioPhoneNumber;
}
string KeyGetter::getMegansPhoneNumber() {
    return megansPhoneNumber;
}

