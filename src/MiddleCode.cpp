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

QuaterInstr* MiddleCode::gen(Opcode _op, struct symbolItem* _des, struct symbolItem* _src1, struct symbolItem* _src2) {
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

void MiddleCode::addDataSeg(string _stringconst)
{
    data_const_string.push_back(_stringconst);
}
