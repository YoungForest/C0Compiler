#include "MiddleCode.h"
#include <iostream>

using namespace std;

MiddleCode::MiddleCode()
{
    //ctor
}

MiddleCode::~MiddleCode()
{
    //dtor
}

QuaterInstr* MiddleCode::gen(Opcode _op, struct symbolItem* _des = NULL, struct symbolItem* _src1 = NULL, struct symbolItem* _src2 = NULL) {
    QuaterInstr* new_quater_instr = new QuaterInstr(_op, _des, _src1, _src2);
    //add the quater code to the middle code.
    middle_codes.push_back(new_quater_instr);
    return new_quater_instr;
}

void MiddleCode::printMiddleCode()
{
    vector<QuaterInstr*>::iterator it = middle_codes.begin();
    while (it != middle_codes.end()) {
        (*it)->printQuater();
        it++;
        cout << endl;
    }
}

int MiddleCode::addDataSeg(string _stringconst)
{
	int length = data_const_string.size();
	data_const_string.push_back(_stringconst);
	return length;
}
