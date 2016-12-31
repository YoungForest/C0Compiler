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
	// 保留给操作系统(我) ? 全局变量 ?
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
	MipsCode branchNeg(MipsCode _op);	// 分支指令取反
	void appendInstruction(std::string label);	// 生成final code
	void appendInstruction(MipsCode _op, std::string _des = "", std::string _src1 = "", std::string _src2 = "");
	void generateInstruction(std::vector<Block *> &blocks);	// 以基本块为单位生成目标代码
	void generateInstruction(std::vector<QuaterInstr*>& middleCodes);	// 根据中间代码生成目标代码
	void dss(QuaterInstr* current, MipsCode _op);	// dss 型四元式 des src src
	void lss(QuaterInstr* current, MipsCode _op);	// lss 型四元式 label src src
	std::string to_string(int i);	// 修复code blocks g++ (tdm-1) 4.7.1 bug
	void holeOptimize();    // 窥孔优化

	std::vector<Instruction> finalCodes;	// 目标代码缓冲区
	Error& error_handle;      // 错误处理程序
protected:
private:
};

#endif // MIPSINSTRGEN_H
