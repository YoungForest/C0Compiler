#ifndef MIPSINSTRGEN_H
#define MIPSINSTRGEN_H

#include <string>
#include <vector>
#include "QuaterInstr.h"
#include "Block.h"
#include "Error.h"
#include "Instruction.h"

// useless until now
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
	// ����������ϵͳ(��) ? ȫ�ֱ��� ?
	$k0,
	$k1,

	$gp,
	$sp,
	$fp,

	$ra,
};

class MipsInstrGen
{
public:
	MipsInstrGen(Error &_error_handle) : error_handle(_error_handle) {};
	virtual ~MipsInstrGen();
	MipsCode branchNeg(MipsCode _op);	// ��ָ֧��ȡ��
	void appendInstruction(std::string label);	// ����final code
	void appendInstruction(MipsCode _op, std::string _des = "", std::string _src1 = "", std::string _src2 = "");
	void generateInstruction(std::vector<Block *> &blocks);	// �Ի�����Ϊ��λ����Ŀ�����
	void generateInstruction(std::vector<QuaterInstr*>& middleCodes);	// �����м��������Ŀ�����
	void dss(QuaterInstr* current, MipsCode _op);	// dss ����Ԫʽ des src src
	void lss(QuaterInstr* current, MipsCode _op);	// lss ����Ԫʽ label src src
	std::string to_string(int i);	// �޸�code blocks g++ (tdm-1) 4.7.1 bug
	void holeOptimize();    // �����Ż�

	std::vector<Instruction> finalCodes;	// Ŀ����뻺����
	Error& error_handle;      // ���������
protected:
private:
};

#endif // MIPSINSTRGEN_H
