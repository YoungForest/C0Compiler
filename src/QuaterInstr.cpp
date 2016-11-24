#include "QuaterInstr.h"

using namespace std;
#include "sstream"

QuaterInstr::QuaterInstr()
{
    //ctor
}

QuaterInstr::~QuaterInstr()
{
    //dtor
}

QuaterInstr::QuaterInstr(Opcode _op, struct symbolItem* _des=NULL, struct symbolItem* _src1=NULL, struct symbolItem* _src2=NULL) {
    op = _op;
    des = _des;
    src1 = _src1;
    src2 = _src2;
}

void QuaterInstr::printQuater()
{
    stringstream output;
    output << getOpcode();
    if (des != NULL)
        output << " " << des->name;
    if (src1 != NULL)
        output << " " << src1->name;
    if (src2 != NULL)
        output << " " << src2->name;
    output << endl;
    cout << output.str(); 
}

string QuaterInstr::getOpcode()
{
    switch (op)
        {
        case ADD:return "ADD";
        case SUB:return "SUB";
        case MUL:return "MUL";
        case DIV:return "DIV";
        case NEG:return "NEG";
        case BGT:return "BGT";
        case BGE:return "BGE";
        case BLT:return "BLT";
        case BLE:return "BLE";
        case BEQ:return "BEQ";
        case BNE:return "BNE";
        case ASS:return "ASS";
        case JUMP:return "JUMP";
        case SET:return "SET";
        case CALL:return "CALL"
        case RETURN:return "RETURN";
        case READ:return "READ";
        case WRITE:return "WRITE";
        default:
            return "NULL";
            break;
        }
}
