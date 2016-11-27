#ifndef MIPSINSTRGEN_H
#define MIPSINSTRGEN_H

#include <string>
#include <vector>
#include "QuaterInstr.h"

enum MipsCode
{
	la,
	lw,
	sw,
	sb,
	add,
	addi,
	sub,
	subi,
	mul,
	div,
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
	syscall
};

// useless
enum Register
{
	$zero,
	$at,
	$v0,

	$v1,
	$a0,
	$a1,
	$a2,
	$a3,
	$t0,
	$t1,
	$t2,
	$t3,
	$t4,
	$t5,
	$t6,
	$t7,
	$s0,
	$s1,
	$s2,
	$s3,
	$s4,
	$s5,
	$s6,
	$s7,
	$t8,
	$t9,
	$k0,
	$k1,

	$gp,
	$sp,
	$fp,

	$ra,
};
class Instruction
{
public:
	std::string op;
	std::string des;	// ��Ϊ �п����Ǳ���, ��ǩ, �� �Ĵ���
	std::string src1;
	std::string src2;

	Instruction(std::string label)
	{
		op = label + ":";
		des = "";
		src1 = "";
		src2 = "";
	}
	Instruction(MipsCode _op, std::string _des = "", std::string _src1 = "", std::string _src2 = "") {
		op = getOpName(_op);
		des = _des;
		src1 = _src1;
		src2 = _src2;
	}
	std::string getOpName(MipsCode _opcode) {
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
			return "add";
		case addi:
			return "addi";
		case sub:
			return "sub";
		case subi:
			return "subi";
		case mul:
			return "mul";
		case MipsCode::div:
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
		default:
			return "null";
		}
	}
	std::string getInstr() {
		return op + " " + des + " " + src1 + " " + src2;
	}
};
class MipsInstrGen
{
    public:
        MipsInstrGen();
        virtual ~MipsInstrGen();
		void appendInstruction(std::string label);
		void appendInstruction(MipsCode _op, std::string _des = "", std::string _src1 = "", std::string _src2 = "");
		void generateInstruction(std::vector<QuaterInstr*>& middleCodes);
		void MipsInstrGen::dss(QuaterInstr* current, MipsCode _op);	// dss ����Ԫʽ
		void MipsInstrGen::lss(QuaterInstr* current, MipsCode _op);	// lss ����Ԫʽ


		std::vector<Instruction> finalCodes;	// Ŀ����뻺����
    protected:
    private:
};

#endif // MIPSINSTRGEN_H
