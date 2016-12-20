#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>

enum MipsCode
{
	la,
	lw,
	sw,
	sb,
	add,
	sub,
	mul,
	divi,
	neg,
	jal,
	j,
	jr,
	beq,
	bne,
	bge,
	bgt,
	ble,
	blt,
	bnez,
	beqz,
	move,
	li,
	syscall,
	comment
};

class Instruction
{
public:
	Instruction();
	virtual ~Instruction();

	Instruction(std::string label);
	Instruction(MipsCode _op, std::string _des = "", std::string _src1 = "", std::string _src2 = "");
	std::string getOpName(MipsCode _opcode);
	std::string getInstr();

	std::string op;
	std::string des;	// 因为 有可能是变量, 标签, 或 寄存器
	std::string src1;
	std::string src2;
	protected:
	private:
};

#endif // INSTRUCTION_H
