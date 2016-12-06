#include "MipsInstrGen.h"
#include "SymbolTable.h"

#include <sstream>

using namespace std;

MipsInstrGen::MipsInstrGen()
{
    //ctor
}

MipsInstrGen::~MipsInstrGen()
{
    //dtor
}

string MipsInstrGen::to_string(int i)
{
	stringstream ss;
	ss << i;
	string s = ss.str();
	return s;
}
// 专门为 set label
void MipsInstrGen::appendInstruction(string label)
{
	Instruction newone(label);
	finalCodes.push_back(newone);
}

void MipsInstrGen::appendInstruction(MipsCode _op, std::string _des, std::string _src1, std::string _src2)
{
	Instruction newone(_op, _des, _src1, _src2);
	finalCodes.push_back(newone);
}

void MipsInstrGen::lss(QuaterInstr* current, MipsCode _op)
{
	string t0 = "$t0";
	string t1 = "$t1";
	string t2 = "$t2";
	if (current->src1->kind == CONSTANT && current->src2->kind == CONSTANT)
	{
		switch (_op)
		{
		case bgt:
			if (current->src1->valueoroffset > current->src2->valueoroffset)
				appendInstruction(MipsCode::j, current->label);
			break;
		case bge:
			if (current->src1->valueoroffset >= current->src2->valueoroffset)
				appendInstruction(MipsCode::j, current->label);
			break;
		case blt:
			if (current->src1->valueoroffset < current->src2->valueoroffset)
				appendInstruction(MipsCode::j, current->label);
			break;
		case ble:
			if (current->src1->valueoroffset <= current->src2->valueoroffset)
				appendInstruction(MipsCode::j, current->label);
			break;
		case beq:
			if (current->src1->valueoroffset == current->src2->valueoroffset)
				appendInstruction(MipsCode::j, current->label);
			break;
		case bne:
			if (current->src1->valueoroffset != current->src2->valueoroffset)
				appendInstruction(MipsCode::j, current->label);
			break;
		default:
			break;
		}
		appendInstruction(MipsCode::li, t1, to_string(current->src1->valueoroffset + current->src2->valueoroffset));
	}
	else if (current->src1->kind == CONSTANT && current->src2->kind != CONSTANT)
	{
		if (current->src2->scope == GLOBAL)
			appendInstruction(MipsCode::lw, t2, current->src2->name);
		else
			appendInstruction(MipsCode::lw, t2, to_string(current->src2->valueoroffset) +"($fp)");
		appendInstruction(_op, t2, to_string(current->src1->valueoroffset), current->label);
	}
	else if (current->src1->kind != CONSTANT && current->src2->kind == CONSTANT)
	{
		if (current->src1->scope == GLOBAL)
			appendInstruction(MipsCode::lw, t1, current->src1->name);
		else
			appendInstruction(MipsCode::lw, t1, to_string(current->src1->valueoroffset) +"($fp)");
		appendInstruction(_op, t1, to_string(current->src2->valueoroffset), current->label);
	}
	else
	{
		if (current->src1->scope == GLOBAL)
			appendInstruction(MipsCode::lw, t1, current->src1->name);
		else
			appendInstruction(MipsCode::lw, t1, to_string(current->src1->valueoroffset) +"($fp)");
		if (current->src2->scope == GLOBAL)
			appendInstruction(MipsCode::lw, t2, current->src2->name);
		else
			appendInstruction(MipsCode::lw, t2, to_string(current->src2->valueoroffset) +"($fp)");
		appendInstruction(_op, t1, t2, current->label);
	}
}

void MipsInstrGen::dss(QuaterInstr* current, MipsCode _op)
{
	string t0 = "$t0";
	string t1 = "$t1";
	string t2 = "$t2";
	if (current->src1->kind == CONSTANT && current->src2->kind == CONSTANT)
		appendInstruction(MipsCode::li, t0, to_string(current->src1->valueoroffset + current->src2->valueoroffset));
	else if (current->src1->kind == CONSTANT && current->src2->kind != CONSTANT)
	{
		if (current->src2->scope == GLOBAL)
			appendInstruction(MipsCode::lw, t2, current->src2->name);
		else
			appendInstruction(MipsCode::lw, t2, to_string(current->src2->valueoroffset) +"($fp)");
		appendInstruction(_op, t0, t2, to_string(current->src1->valueoroffset));
	}
	else if (current->src1->kind != CONSTANT && current->src2->kind == CONSTANT)
	{
		if (current->src1->scope == GLOBAL)
			appendInstruction(MipsCode::lw, t1, current->src1->name);
		else
			appendInstruction(MipsCode::lw, t1, to_string(current->src1->valueoroffset) +"($fp)");
		appendInstruction(_op, t0, t1, to_string(current->src2->valueoroffset));
	}
	else
	{
		if (current->src1->scope == GLOBAL)
			appendInstruction(MipsCode::lw, t1, current->src1->name);
		else
			appendInstruction(MipsCode::lw, t1, to_string(current->src1->valueoroffset) + "($fp)");
		if (current->src2->scope == GLOBAL)
			appendInstruction(MipsCode::lw, t2, current->src2->name);
		else
			appendInstruction(MipsCode::lw, t2, to_string(current->src2->valueoroffset) + "($fp)");
		appendInstruction(_op, t0, t1, t2);
	}
	// 将des存入内存
	if (current->des->scope == GLOBAL)
		appendInstruction(MipsCode::sw, t0, current->des->name);
	else
		appendInstruction(MipsCode::sw, t0, to_string(current->des->valueoroffset) + "($fp)");
}

void MipsInstrGen::generateInstruction(vector<QuaterInstr*>& middleCodes)
{
	vector<QuaterInstr*>::iterator it = middleCodes.begin();
	// 所使用的3个寄存器
	string t0 = "$t0";
	string t1 = "$t1";
	string t2 = "$t2";
	while (it != middleCodes.end())
	{
		QuaterInstr* current = (*it);

		// 由四元式生成目标代码
		switch (current->op)	
		{
		case ADD:
			dss(current, MipsCode::add);
			break;
		case SUB:
			dss(current, MipsCode::sub);
			break;
		case MUL: 
			dss(current, MipsCode::mul);
			break;
		case DIV:
			dss(current, MipsCode::divi);
			break;
		case LAV:
			if (current->src1->scope == GLOBAL && current->src2->kind == CONSTANT)
			{
				appendInstruction(MipsCode::lw, t0, current->src1->name + "+" +to_string(4 * current->src2->valueoroffset));
			}
			else if (current->src1->scope == GLOBAL && current->src2->kind != CONSTANT)
			{
				if (current->src2->scope == GLOBAL)
					appendInstruction(MipsCode::lw, t1, current->src2->name);
				else
					appendInstruction(MipsCode::lw, t1, to_string(current->src2->valueoroffset) +"($fp)");
				appendInstruction(MipsCode::mul, t1, t1, "4");
				appendInstruction(MipsCode::lw, t0, current->src1->name + "(" + t1 + ")");
			}
			else
			{
				if (current->src2->kind == CONSTANT)
					appendInstruction(MipsCode::lw, t0, to_string(current->src1->valueoroffset - 4 * current->src2->valueoroffset) +"($fp)");
				else
				{
					if (current->src2->scope == GLOBAL)
						appendInstruction(MipsCode::lw, t1, current->src2->name);
					else
						appendInstruction(MipsCode::lw, t1, to_string(current->src2->valueoroffset) +"($fp)");
					appendInstruction(MipsCode::mul, t1, t1, "4");
					appendInstruction(MipsCode::sub, t1, "$fp", t1);
					appendInstruction(MipsCode::lw, t0, to_string(current->src1->valueoroffset) + "(" + t1 + ")");
				}
			}
			appendInstruction(MipsCode::sw, t0, to_string(current->des->valueoroffset) +"($fp)");
			break;
		case SAV:
			if (current->des->kind == CONSTANT)
				appendInstruction(MipsCode::li, t0, to_string(current->des->valueoroffset));
			else
			{
				if (current->des->scope == GLOBAL)
					appendInstruction(MipsCode::lw, t0, current->des->name);
				else
					appendInstruction(MipsCode::lw, t0, to_string(current->des->valueoroffset) +"($fp)");
			}
			if (current->src1->scope == GLOBAL)
			{
				if (current->src2->kind == CONSTANT)
					appendInstruction(MipsCode::sw, t0, current->src1->name + "+" + to_string(4 * current->src2->valueoroffset));
				else
				{
					if (current->src2->scope == GLOBAL)
						appendInstruction(MipsCode::lw, t1, current->src2->name);
					else
						appendInstruction(MipsCode::lw, t1, to_string(current->src2->valueoroffset) +"($fp)");
					appendInstruction(MipsCode::mul, t1, t1, "4");
					appendInstruction(MipsCode::sw, t0, current->src1->name + "(" + t1 + ")");
				}
			}
			else
			{
				if (current->src2->kind == CONSTANT)
					appendInstruction(MipsCode::sw, t0, to_string(current->src1->valueoroffset - 4 * current->src2->valueoroffset) +"($fp)");
				else
				{
					if (current->src2->scope == GLOBAL)
						appendInstruction(MipsCode::lw, t1, current->src2->name);
					else
						appendInstruction(MipsCode::lw, t1, to_string(current->src2->valueoroffset) +"($fp)");
					appendInstruction(MipsCode::mul, t1, t1, "4");
					appendInstruction(MipsCode::sub, t1, "$fp", t1);
					appendInstruction(MipsCode::sw, t0, to_string(current->src1->valueoroffset) + "(" + t1 + ")");
				}
			}
			break;
		case NEG:
			if (current->src1->kind == CONSTANT)
			{
				appendInstruction(MipsCode::li, t0, to_string(-current->src1->valueoroffset));
				if (current->des->scope == GLOBAL)
					appendInstruction(MipsCode::sw, t0, current->des->name);
				else
					appendInstruction(MipsCode::sw, t0, to_string(current->des->valueoroffset) +"($fp)");
			}
			else
			{
				if (current->src1->scope == GLOBAL)
					appendInstruction(MipsCode::lw, t1, current->src1->name);
				else
					appendInstruction(MipsCode::lw, t1, to_string(current->src1->valueoroffset) +"($fp)");
				appendInstruction(MipsCode::neg, t0, t1);
				if (current->des->scope == GLOBAL)
					appendInstruction(MipsCode::sw, t0, current->des->name);
				else
					appendInstruction(MipsCode::sw, t0, to_string(current->des->valueoroffset) +"($fp)");
			}
			break;
		case ASS:
			if (current->src1->kind == CONSTANT)
			{
				appendInstruction(MipsCode::li, t0, to_string(current->src1->valueoroffset));
				if (current->des->scope == GLOBAL)
					appendInstruction(MipsCode::sw, t0, current->des->name);
				else
					appendInstruction(MipsCode::sw, t0, to_string(current->des->valueoroffset) +"($fp)");
			}
			else
			{
				if (current->src1->scope == GLOBAL)
					appendInstruction(MipsCode::lw, t0, current->src1->name);
				else
					appendInstruction(MipsCode::lw, t0, to_string(current->src1->valueoroffset) +"($fp)");
				if (current->des->scope == GLOBAL)
					appendInstruction(MipsCode::sw, t0, current->des->name);
				else
					appendInstruction(MipsCode::sw, t0, to_string(current->des->valueoroffset) +"($fp)");
			}
			break;
		case BGT:
			lss(current, MipsCode::bgt);
			break;
		case BGE:
			lss(current, MipsCode::bge);
			break;
		case BLT:
			lss(current, MipsCode::blt);
			break;
		case BLE:
			lss(current, MipsCode::ble);
			break;
		case BEQ:
			lss(current, MipsCode::beq);
			break;
		case BNE:
			lss(current, MipsCode::bne);
			break;
		case BNZ:
			if (current->src1->kind == CONSTANT)
				if (current->src1->valueoroffset != 0)
					appendInstruction(MipsCode::j, current->label);
				else
					;
			else
			{
				if (current->src1->scope == GLOBAL)
					appendInstruction(MipsCode::lw, t0, current->src1->name);
				else
					appendInstruction(MipsCode::lw, t0, to_string(current->src1->valueoroffset) +"($fp)");
				appendInstruction(MipsCode::bnez, t0, current->label);
			}
			break;
		case BEZ:
			if (current->src1->kind == CONSTANT)
				if (current->src1->valueoroffset == 0)
					appendInstruction(MipsCode::j, current->label);
				else
					;
			else
			{
				if (current->src1->scope == GLOBAL)
					appendInstruction(MipsCode::lw, t0, current->src1->name);
				else
					appendInstruction(MipsCode::lw, t0, to_string(current->src1->valueoroffset) +"($fp)");
				appendInstruction(MipsCode::beqz, t0, current->label);
			}
			break;
		case JUMP:
			appendInstruction(MipsCode::j, current->label);
			break;
		case SET:
			appendInstruction(current->label);
			break;
		case CALL:
			appendInstruction(MipsCode::jal, current->label);
			break;
		case DEC:
			appendInstruction(current->des->name);
			appendInstruction(MipsCode::sw, "$ra", "0($sp)");
			appendInstruction(MipsCode::sw, "$fp", "-4($sp)");
			appendInstruction(MipsCode::move, "$fp", "$sp");
			appendInstruction(MipsCode::sw, "$v1", "-8($sp)");
			appendInstruction(MipsCode::sw, "$a0", "-12($sp)");
			appendInstruction(MipsCode::sw, "$a1", "-16($sp)");
			appendInstruction(MipsCode::sw, "$a2", "-20($sp)");
			appendInstruction(MipsCode::sw, "$a3", "-24($sp)");
			appendInstruction(MipsCode::sw, "$t0", "-28($sp)");
			appendInstruction(MipsCode::sw, "$t1", "-32($sp)");
			appendInstruction(MipsCode::sw, "$t2", "-36($sp)");
			appendInstruction(MipsCode::sw, "$t3", "-40($sp)");
			appendInstruction(MipsCode::sw, "$t4", "-44($sp)");
			appendInstruction(MipsCode::sw, "$t5", "-48($sp)");
			appendInstruction(MipsCode::sw, "$t6", "-52($sp)");
			appendInstruction(MipsCode::sw, "$t7", "-56($sp)");
			appendInstruction(MipsCode::sw, "$s0", "-60($sp)");
			appendInstruction(MipsCode::sw, "$s1", "-64($sp)");
			appendInstruction(MipsCode::sw, "$s2", "-68($sp)");
			appendInstruction(MipsCode::sw, "$s3", "-72($sp)");
			appendInstruction(MipsCode::sw, "$s4", "-76($sp)");
			appendInstruction(MipsCode::sw, "$s5", "-80($sp)");
			appendInstruction(MipsCode::sw, "$s6", "-84($sp)");
			appendInstruction(MipsCode::sw, "$s7", "-88($sp)");
			appendInstruction(MipsCode::sw, "$t8", "-92($sp)");
			appendInstruction(MipsCode::sw, "$t9", "-96($sp)");
			appendInstruction(MipsCode::sw, "$k0", "-100($sp)");
			appendInstruction(MipsCode::sw, "$k1", "-104($sp)");
			appendInstruction(MipsCode::subi, "$sp", "$sp", to_string(BASE_OFFSET));
			break;
		case RET:
			if (current->des == NULL)
			{
				appendInstruction(MipsCode::li, "$v0", "0");
			}
			else
			{
				if (current->des->kind == CONSTANT)
					appendInstruction(MipsCode::li, "$v0", to_string(current->des->valueoroffset));
				else
				{
					if (current->des->scope == GLOBAL)
						appendInstruction(MipsCode::lw, "$v0", current->des->name);
					else
						appendInstruction(MipsCode::lw, "$v0", to_string(current->des->valueoroffset) +"($fp)");
				}
			}
			appendInstruction(MipsCode::lw, "$v1", "-8($fp)");
			appendInstruction(MipsCode::lw, "$a0", "-12($fp)");
			appendInstruction(MipsCode::lw, "$a1", "-16($fp)");
			appendInstruction(MipsCode::lw, "$a2", "-20($fp)");
			appendInstruction(MipsCode::lw, "$a3", "-24($fp)");
			appendInstruction(MipsCode::lw, "$t0", "-28($fp)");
			appendInstruction(MipsCode::lw, "$t1", "-32($fp)");
			appendInstruction(MipsCode::lw, "$t2", "-36($fp)");
			appendInstruction(MipsCode::lw, "$t3", "-40($fp)");
			appendInstruction(MipsCode::lw, "$t4", "-44($fp)");
			appendInstruction(MipsCode::lw, "$t5", "-48($fp)");
			appendInstruction(MipsCode::lw, "$t6", "-52($fp)");
			appendInstruction(MipsCode::lw, "$t7", "-56($fp)");
			appendInstruction(MipsCode::lw, "$s0", "-60($fp)");
			appendInstruction(MipsCode::lw, "$s1", "-64($fp)");
			appendInstruction(MipsCode::lw, "$s2", "-68($fp)");
			appendInstruction(MipsCode::lw, "$s3", "-72($fp)");
			appendInstruction(MipsCode::lw, "$s4", "-76($fp)");
			appendInstruction(MipsCode::lw, "$s5", "-80($fp)");
			appendInstruction(MipsCode::lw, "$s6", "-84($fp)");
			appendInstruction(MipsCode::lw, "$s7", "-88($fp)");
			appendInstruction(MipsCode::lw, "$t8", "-92($fp)");
			appendInstruction(MipsCode::lw, "$t9", "-96($fp)");
			appendInstruction(MipsCode::lw, "$k0", "-100($fp)");
			appendInstruction(MipsCode::lw, "$k1", "-104($fp)");
			appendInstruction(MipsCode::lw, "$ra", "0($fp)");
			appendInstruction(MipsCode::move, "$sp", "$fp");
			appendInstruction(MipsCode::lw, "$fp", "-4($fp)");
			appendInstruction(MipsCode::jr, "$ra");
			break;
		case DSP:
			appendInstruction(MipsCode::subi, "$sp", "$sp", current->label);
			break;
		case READ:
			if (current->des->type == INT_TYPE)
			{
				appendInstruction(MipsCode::li, "$v0", "5");
				appendInstruction(MipsCode::syscall);
				if (current->des->scope == GLOBAL)
					appendInstruction(MipsCode::sw, "$v0", current->des->name);
				else
					appendInstruction(MipsCode::sw, "$v0", to_string(current->des->valueoroffset) +"($fp)");
			}
			else
			{
				appendInstruction(MipsCode::li, "$v0", "12");
				appendInstruction(MipsCode::syscall);
				if (current->des->scope == GLOBAL)
					appendInstruction(MipsCode::sw, "$v0", current->des->name);
				else
					appendInstruction(MipsCode::sw, "$v0", to_string(current->des->valueoroffset) +"($fp)");
			}
			break;
		case WRITE:
			if (current->des->kind == CONSTANT)
			{
				if (current->des->type == INT_TYPE)
				{
					appendInstruction(MipsCode::li, "$a0", to_string(current->des->valueoroffset));
					appendInstruction(MipsCode::li, "$v0", "1");
				}
				else if (current->des->type == CHAR_TYPE)
				{
					appendInstruction(MipsCode::li, "$a0", to_string(current->des->valueoroffset));
					appendInstruction(MipsCode::li, "$v0", "11");
				}
				else if (current->des->type == STRING_TYPE)
				{
					appendInstruction(MipsCode::li, "$v0", "4");
					appendInstruction(MipsCode::la, "$a0", current->des->name);
				}
				else
					;
			}
			else
			{
				if (current->des->type == INT_TYPE)
				{
					if (current->des->scope == GLOBAL)
						appendInstruction(MipsCode::lw, "$a0", current->des->name);
					else
						appendInstruction(MipsCode::lw, "$a0", to_string(current->des->valueoroffset) + "($fp)");
					appendInstruction(MipsCode::li, "$v0", "1");
				}
				else if (current->des->type == CHAR_TYPE)
				{
					if (current->des->scope == GLOBAL)
						appendInstruction(MipsCode::lw, "$a0", current->des->name);
					else
						appendInstruction(MipsCode::lw, "$a0", to_string(current->des->valueoroffset) + "($fp)");
					appendInstruction(MipsCode::li, "$v0", "11");
				}
				else
					;
			}
			appendInstruction(MipsCode::syscall);
			break;
		case PUSH:
			if (current->des->kind == CONSTANT)
				appendInstruction(MipsCode::li, t0, to_string(current->des->valueoroffset));
			else
			{
				if (current->des->scope == GLOBAL)
					appendInstruction(MipsCode::lw, t0, current->des->name);
				else
					appendInstruction(MipsCode::lw, t0, to_string(current->des->valueoroffset) + "($fp)");
			}
			appendInstruction(MipsCode::sw, t0, to_string(current->src1->valueoroffset) + "($sp)");
			break;
		case PUT:
			appendInstruction(MipsCode::sw, "$v0", to_string(current->des->valueoroffset) +"($fp)");
			break;
		default:
			break;
		}

		it++;
	}
}
