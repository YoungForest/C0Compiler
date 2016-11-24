#ifndef QUATERINSTR_H
#define QUATERINSTR_H

#include <string>
#include "SymbolTable.h"

enum Opcode {
	// 算术运算符
	ADD,	// +
	SUB,	// -
	MUL,	// *
	DIV,	// /
	NEG,	// -

	// 分支跳转
	BGT,	// >
	BGE,	// >=
	BLT,	// <
	BLE,	// <=
	BEQ,	// ==
	BNE,	// !=


	ASS,	// 赋值

	JUMP,	// 无条件跳转

	SET,	// 标签设置

	CALL,	// 函数调用
	RET, // 函数返回

	READ,	// 读操作
	WRITE,	// 写操作

	LAV,	// 取数组中的值 LAV des, array, offset
	SAV		// 向数组中存值 SAV src, array, offset
};

class QuaterInstr
{
    public:
        QuaterInstr();
        virtual ~QuaterInstr();

        QuaterInstr(Opcode _op, struct symbolItem* des, struct symbolItem* src1, struct symbolItem* src2);
        void printQuater();
        std::string getOpcode();

        Opcode op;
        struct symbolItem* des;
        struct symbolItem* src1;
        struct symbolItem* src2;
    protected:
    private:
};

#endif // QUATERINSTR_H
