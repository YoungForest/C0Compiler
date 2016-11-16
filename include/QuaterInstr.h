#ifndef QUATERINSTR_H
#define QUATERINSTR_H

#include <string>

enum Opcode {
	ADD,
	SUB,
	MUL,
	DIV,
	NEG,
	//calculate instructions.
	//>
	BGR,
	//>=
	BGE,
	//<
	BLS,
	//<=
	BLE,
	//==
	BEQ,
	//<>
	BNE,
	//branch if meeting the conditions.

	// des = src
	ASS,
	// [des] = src
	ASSADD,
	// temp = add of array + offset
	ARRADD,
	// des = [src]
	ARRASS,


	JUMP,
	SETL,
	READ,
	WRITE,
	BEGIN,
	END,

	CALL,
	/*
	as a result of not knowing offset in generating
	quaters.So we can't get the address of the vairable
	or the parameters.So we must generate a push var
	to do this.

	*/
	PUSH,
	PUSHVAR,

	//increment +1
	INC,
	//decrement -1
	DEC,

	RETURN

};

class QuaterInstr
{
    public:
        QuaterInstr();
        virtual ~QuaterInstr();
    protected:
    private:
        Opcode op;
        std::string des;
        std::string src1;
        std::string src2;
};

#endif // QUATERINSTR_H
