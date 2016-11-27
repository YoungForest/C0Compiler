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
	BNZ,	// != 0
	BEZ,	// == 0


	ASS,	// 赋值

	JUMP,	// 无条件跳转

	SET,	// 标签设置

	CALL,	// 函数调用
	DEC,	// 进入函数定义
	RET, // 函数返回

	READ,	// 读操作
	WRITE,	// 写操作

	LAV,	// 取数组中的值 LAV des, array, offset
	SAV,		// 向数组中存值 SAV src, array, offset

	PUSH,	// 往栈里压参数 PUSH src index
	PUT,	// 取$v0的值放到一个临时变量里 PUT des
	DSP		// 下降栈顶
};

class QuaterInstr
{
    public:
        QuaterInstr();
        virtual ~QuaterInstr();

        QuaterInstr(Opcode _op, struct symbolItem* des = NULL, struct symbolItem* _src1 = NULL, struct symbolItem* _src2 = NULL);	// 构造, 生成四元式
		QuaterInstr(Opcode _op, std::string _label, struct symbolItem* _src1 = NULL, struct symbolItem* _src2 = NULL);
		void printQuater();	// [调试]打印四元式
        std::string getOpcode();	// 将操作符转换为字符串

        Opcode op;	// 操作符
        struct symbolItem* des;	// 操作数1
        struct symbolItem* src1;	// 操作数2
        struct symbolItem* src2;	// 操作数3
		std::string label;	// 标签 jump
		
    protected:
    private:
};

#endif // QUATERINSTR_H
