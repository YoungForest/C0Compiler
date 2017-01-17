#include "Instruction.h"

Instruction::Instruction()
{
	//ctor
}

Instruction::~Instruction()
{
	//dtor
}

Instruction::Instruction(std::string label)
{
	op = label + ":";
	des = "";
	src1 = "";
	src2 = "";
}

Instruction::Instruction(MipsCode _op, std::string _des, std::string _src1, std::string _src2)
{
	op = getOpName(_op);
	des = _des;
	src1 = _src1;
	src2 = _src2;
}

std::string Instruction::getOpName(MipsCode _opcode)
{
	switch (_opcode)
	{
	case lw:
		return "lw";
	case sw:
		return "sw";
	case sb:
		return "sb";
	case li:
		return "li";
	case la:
		return "la";
	case jal:
		return "jal";
	case add:
		return "addu";
	case sub:
		return "subu";
	case mul:
		return "mul";
	case MipsCode::divi:
		return "div";
	case neg:
		return "neg";
	case beq:
		return "beq";
	case bne:
		return "bne";
	case bge:
		return "bge";
	case bgt:
		return "bgt";
	case ble:
		return "ble";
	case blt:
		return "blt";
	case bnez:
		return "bnez";
	case beqz:
		return "beqz";
	case syscall:
		return "syscall";
	case MipsCode::move:
		return "move";
	case j:
		return "j";
	case jr:
		return "jr";
	case comment:
		return "#";
	default:
		return "null";
	}
}

std::string Instruction::getInstr()
{
	return op + " " + des + " " + src1 + " " + src2;
}
