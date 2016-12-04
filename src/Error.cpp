#include "Error.h"
#include <sstream>
#include <iostream>
#include <cstdlib>

#define _ERROR_FATAL

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
	Message << "error occurs at (line: " << line << ", column: " << column << ") : ";
	error_count++;
    switch (errortype)
    {
    case 4: Message << "Find ! which is not followed by =." << endl; break;
	case 6: Message << "expected a ';' or ',' or '[' or '(' after identifier" << endl; break;
	case 8: Message << "expected a 'main' or identifier after void" << endl; break;
	case 10: Message << "expected a identifier after int or char" << endl; break;
	case 12: Message << "expected a '(' here" << endl; break;
	case 14: Message << "expected a ')' here" << endl; break;
	case 16: Message << "expected a '{' here" << endl; break;
	case 18: Message << "expected a '}' here" << endl; break;
	case 20: Message << "expected a identifier here" << endl; break;
	case 22: Message << "expected an unsigned integer here" << endl; break;
	case 24: Message << "expected a ']' here" << endl; break;
	case 26: Message << "expected a ';' here" << endl; break;
	case 28: Message << "expected a int or char here" << endl; break;
	case 30: Message << "expected a '=' here" << endl; break;
	case 32: Message << "expected a charactor here" << endl; break;
	case 34: Message << "expected a '+' or '-' or digit here" << endl; break;
	case 36: Message << "expected a statement here" << endl; break;
	case 38: Message << "expected a '=' or '[' or '(' here" << endl; break;
	case 40: Message << "expected a if here" << endl; break;
	case 42: Message << "unallowed compare operation" << endl; break;
	case 44: Message << "expected a do here" << endl; break;
	case 46: Message << "expected a while here" << endl; break;
	case 48: Message << "expected a for here" << endl; break;
	case 50: Message << "expected a '+' or '-' here" << endl; break;
	case 52: Message << "expected a '=' or '['" << endl; break;
	case 54: Message << "expected a scanf" << endl; break;
	case 56: Message << "expected a printf" << endl; break;
	case 58: Message << "expected a return" << endl; break;
	case 60: Message << "expected a identifier or interger or charactor or function call or '(' here" << endl; break;
    default: Message << "Unhandled error " << errortype << " !" << endl;
        break;
    }
    error_messages.push_back(Message.str());
#ifdef _ERROR_FATAL
	printWarnings();
	printErrors();
#ifdef CB
	system("pause");
#endif // CB
	exit(0);
#endif
}

void Error::errorMessage(int errortype, int line, int column, string message1) {
    stringstream Message;
	Message << "error occurs at (line: " << line << ", column: " << column << ") : ";
    error_count++;
    switch (errortype)
    {
	case 1: Message << message1 << endl; break;
    case 101: Message << "Parse error " << message1 << " !" << endl; break;
    case 102: Message << "Can't recongnize this token " << message1 << endl; break;
	case 103: Message << "Undefined identifier : " << message1 << " !" << endl; break;
	case 104: Message << message1 << " parameters needed while more are given !" << endl; break;
	case 106: Message <<  message1 << " parameters needed while fewer are given !" << endl; break;
	case 108: Message << message1 << " is a void function while not a return function, which can not using in a expression!" << endl; break;

	default: Message << "Unhandled error " << errortype << " !" << endl;
        break;
    }
    error_messages.push_back(Message.str());

#ifdef _ERROR_FATAL
	printWarnings();
	printErrors();
#ifdef CB
	system("pause");
#endif // CB
	exit(0);
#endif
}

void Error::errorMessage(int errortype, int line, int column, string message1, string message2) {
    stringstream Message;
	Message << "error occurs at (line: " << line << ", column: " << column << ") : ";
    error_count++;
    switch (errortype)
    {
	case 200: Message << "identifier " << message1 << " multi-defined, first defined at line " << message2 << "." << endl; break;
    default: Message << "Unhandled error " << errortype << " !" << endl;
        break;
    }
    error_messages.push_back(Message.str());
#ifdef _ERROR_FATAL
	printWarnings();
	printErrors();
#ifdef CB
	system("pause");
#endif // CB
	exit(0);
#endif
}

void Error::warningMessage(int warningtype, int line, int column, std::string message1)
{
	stringstream Message;
	Message << "warning generates at (line: " << line << ", column: " << column << ") : ";
	warning_count++;
	switch (warningtype)
	{
	case 301: Message <<  "out range of int " << message1 << endl; break;
	default: Message << "Unhandled error " << warningtype << " !" << endl;
		break;
	}
	warning_messages.push_back(Message.str());
}

void Error::printErrors() {
    vector<string>::iterator it = error_messages.begin();
    while (it != error_messages.end()) {
        cout << (*it);
        it++;
    }
}

void Error::printWarnings()
{
	vector<string>::iterator it = warning_messages.begin();
	while (it != warning_messages.end()) {
		cout << (*it);
		it++;
	}
}
