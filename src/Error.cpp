#include "Error.h"
#include <sstream>
#include <iostream>

using namespace std;

Error::Error()
{
    //ctor
    error_count = 0;
}

Error::~Error()
{
    //dtor
}

int Error::getErrorCount() {
    return error_count;
}

bool Error::isSuccess() {
    return error_count == 0;
}

void Error::errorMessage(int errortype,int line, int column) {
    stringstream Message;
    Message << "错误在第 " << line << "行, 第 " << column << "列 :";
    error_count++;
    switch (errortype)
    {
        //the function have defined before.
    case 3: Message << "Find ! which is not followed by =." << endl; break;
    default: Message << "Unhandled error " << errortype << " !" << endl;
        break;
    }
    error_messages.push_back(Message.str());
}

void Error::errorMessage(int errortype, int line, int column, string message1) {
    stringstream Message;
    Message << "错误在第 " << line << "行, 第 " << column << "列 :";
    error_count++;
    switch (errortype)
    {
    case 101: Message << "Parse error " << message1 << " !" << endl; break;
    case 2: Message << "Can't recongnize this token" << message1 << endl; break;
    default: Message << "Unhandled error " << errortype << " !" << endl;
        break;
    }
    error_messages.push_back(Message.str());
}

void Error::errorMessage(int errortype, int line, int column, string message1, string message2) {
    stringstream Message;
    Message << "错误在第 " << line << "行, 第 " << column << "列 :  ";
    error_count++;
    switch (errortype)
    {
        //the function have defined before.
    default: Message << "Unhandled error " << errortype << " !" << endl;
        break;
    }
    error_messages.push_back(Message.str());
}

void Error::print() {
    vector<string>::iterator it = error_messages.begin();
    while (it != error_messages.end()) {
        cout << (*it);
        it++;
    }
}
