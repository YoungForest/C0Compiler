#ifndef BLOCK_H
#define BLOCK_H

#include "QuaterInstr.h"
#include <vector>
#include <set>

class Block
{
    public:
		Block() : st(GLOBAL) {};
        virtual ~Block();

		std::vector<QuaterInstr *> middleCode;	// �������а�������Ԫʽ
		QuaterInstr * jump = nullptr;	// �����Ŀ��ܵ���תָ��
		QuaterInstr * initStack = nullptr;	// Ϊ���ʼ��ջ
		QuaterInstr * recoverStack = nullptr;	// ����ջ
		std::vector<Block *> before;	// ǰ������������
		std::vector<Block *> after;		// ��̻���������

		// Reaching Definetion 
		std::vector<QuaterInstr *> rdOut;
		std::vector<QuaterInstr *> rdIn;
		std::vector<QuaterInstr *> gen;
		std::vector<QuaterInstr *> kill;

		// live-variable analysis	in[B] = use[B] U (out[B] - def[B]); out[B] = U{in[P]},PΪB�ĺ�̿�
		std::set<symbolItem *> lvOut;
		std::set<symbolItem *> lvIn;
		std::set<symbolItem *> use;
		std::set<symbolItem *> def;

		SymbolTable st;	// ����ʱ��������ʱ����
    protected:
    private:
};

#endif // BLOCK_H
