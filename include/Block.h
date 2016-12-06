#ifndef BLOCK_H
#define BLOCK_H

#include "QuaterInstr.h"
#include <vector>
#include <set>

class Block
{
    public:
        Block();
        virtual ~Block();

		std::vector<QuaterInstr *> middleCode;	// 基本块中包含的四元式
		std::vector<Block *> before;	// 前驱基本块数组
		std::vector<Block *> after;		// 后继基本块数组

		// Reaching Definetion 
		std::vector<QuaterInstr *> rdOut;
		std::vector<QuaterInstr *> rdIn;
		std::vector<QuaterInstr *> gen;
		std::vector<QuaterInstr *> kill;

		// live-variable analysis	in[B] = use[B] U (out[B] - def[B]); out[B] = U{in[P]},P为B的后继块
		std::set<symbolItem *> lvOut;
		std::set<symbolItem *> lvIn;
		std::set<symbolItem *> use;
		std::set<symbolItem *> def;

		SymbolTable st;	// 存临时变量和临时常量
    protected:
    private:
};

#endif // BLOCK_H
