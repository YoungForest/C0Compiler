#include "QuaterInstr.h"
#include "sstream"
#include <iostream>

using namespace std;

QuaterInstr::QuaterInstr()
{
    //ctor
}

QuaterInstr::~QuaterInstr()
{
    //dtor
}

QuaterInstr::QuaterInstr(Opcode _op, struct symbolItem* _des, struct symbolItem* _src1, struct symbolItem* _src2) {
    op = _op;
    des = _des;
    src1 = _src1;
    src2 = _src2;
	label = "";
}

QuaterInstr::QuaterInstr(Opcode _op, std::string _label, symbolItem * _src1, symbolItem * _src2) : op(_op), src1(_src1), src2(_src2), label(_label)
{
	des = NULL;
}

void QuaterInstr::printQuater()
{
    stringstream output;
    output << getOpcode();
	if (!label.empty())
		output << " " << label;
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
			case BNZ: return "BNZ";
			case BEZ: return "BEZ";
			case ASS:return "ASS";
			case JUMP:return "JUMP";
			case SET:return "SET";
			case CALL: return "CALL";
			case DEC: return "DEC";
			case RET:return "RETURN";
			case READ:return "READ";
			case WRITE:return "WRITE";
			case LAV:return "LAV";
			case SAV:return "SAV";
			case PUSH: return "PUSH";
			case PUT: return "PUT";
			case DSP: return "DSP";
			default:
				return "NULL";
				break;
        }
}
