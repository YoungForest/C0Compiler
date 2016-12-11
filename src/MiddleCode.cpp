#include "MiddleCode.h"
#include "DAGmanager.h"
#include <iostream>

using namespace std;

MiddleCode::MiddleCode()
{
    //ctor
}

MiddleCode::~MiddleCode()
{
    //dtor
}

bool MiddleCode::isJumpOrBranch(Opcode _op)
{
	return _op == Opcode::BGT || _op == Opcode::BGE || _op == Opcode::BLT || _op == Opcode::BLE || _op == Opcode::BEQ || _op == Opcode::BNE || _op == Opcode::BNZ || _op == Opcode::BEZ || _op == Opcode::JUMP;
}

void MiddleCode::updateFlag(QuaterInstr* new_quater_instr)
{
	if (new_quater_instr->op == Opcode::DEC || new_quater_instr->op == Opcode::SET || preQuaterInstructionIsJumpOrBranch == true)
		flag.push_back(1);
	else
		flag.push_back(0);
	if (isJumpOrBranch(new_quater_instr->op) || new_quater_instr->op == Opcode::RET)
		preQuaterInstructionIsJumpOrBranch = true;
	else
		preQuaterInstructionIsJumpOrBranch = false;
}

QuaterInstr* MiddleCode::gen(Opcode _op, struct symbolItem* _des, struct symbolItem* _src1, struct symbolItem* _src2) {
    QuaterInstr* new_quater_instr = new QuaterInstr(_op, _des, _src1, _src2);
    //add the quater code to the middle code.
    middle_codes.push_back(new_quater_instr);
	updateFlag(new_quater_instr);
	return new_quater_instr;
}

QuaterInstr * MiddleCode::gen(Opcode _op, std::string label, symbolItem * _src1, symbolItem * _src2)
{
	QuaterInstr *new_quater_instr = new QuaterInstr(_op, label, _src1, _src2);
	//add the quater code to the middle code.
	middle_codes.push_back(new_quater_instr);
	updateFlag(new_quater_instr);
	return new_quater_instr;
}

void MiddleCode::clear()
{
	middle_codes.clear();
	flag.clear();
	basicBlocks.clear();
}

void MiddleCode::printMiddleCode()
{
#ifdef PRINT_MIDDLECODE
    vector<QuaterInstr*>::iterator it = middle_codes.begin();
    while (it != middle_codes.end()) 
	{
        (*it)->printQuater();
        it++;
    }
	cout << endl;
#endif
}

void MiddleCode::optimize()
{
	load();

	for (auto it = basicBlocks.begin(); it != basicBlocks.end(); it++)
	{
		DAGmanager dag(*(*it), (*it)->st);
		dag.buildDAG();
		dag.regenerateMiddleCode();
	}

	// reaching define

	// live-variable analysis

	store();
}

void MiddleCode::load()
{
	Block *newblock = nullptr, *preblock = nullptr;
	functionDeclaration = middle_codes[0];
	initalStack = middle_codes[1];
	newblock = new Block();
	basicBlocks.push_back(newblock);

	for (int i = 2; i < flag.size(); i++)
	{
		if (flag[i] == 1)
		{
			preblock = newblock;
			if (i > 2)	//	解决第一条指令就是 标签指令
				newblock = new Block();
			newblock->middleCode.push_back(middle_codes[i]);
			if (preblock != nullptr && preblock->middleCode.back()->op != Opcode::JUMP && preblock->middleCode.back()->op != Opcode::RET)	// 更新前驱和后继
			{
				newblock->before.push_back(preblock);
				preblock->after.push_back(newblock);
			}
			basicBlocks.push_back(newblock);
		}
		else
		{
			newblock->middleCode.push_back(middle_codes[i]);
		}
	}
	for (auto it = basicBlocks.begin(); it != basicBlocks.end(); it++)
	{	// 筛选出最后一条指令为跳转或分支指令的基本块
		if (isJumpOrBranch((*it)->middleCode.back()->op))
		{
			for (auto it2 = basicBlocks.begin(); it != basicBlocks.end(); it2++)
			{	// 筛选出 第一条指令为set指令, 并且与跳转或分支指令的标签相同 的基本块
				if ((*it2)->middleCode.front()->op == Opcode::SET || (*it2)->middleCode.front()->label == (*it)->middleCode.back()->label)
				{
					(*it2)->before.push_back(*it);
					(*it)->after.push_back(*it2);
				}
			}
		}
	}
}

void MiddleCode::store()
{
	middle_codes.clear();
	middle_codes.push_back(functionDeclaration);
	middle_codes.push_back(initalStack);
	for (auto it = basicBlocks.cbegin(); it != basicBlocks.cend(); it++)
	{
		for (auto it2 = (*it)->middleCode.cbegin(); it2 != (*it)->middleCode.cend(); it2++)
		{
			middle_codes.push_back(*it2);	// 两次循环, 逐个添加
		}
	}
}
