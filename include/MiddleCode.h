#ifndef MIDDLECODE_H
#define MIDDLECODE_H

#include <vector>
#include <string>
#include "QuaterInstr.h"
#include "SymbolTable.h"
#include "Block.h"

class MiddleCode
{
    public:
        MiddleCode();
        virtual ~MiddleCode();
		bool isJumpOrBranch(Opcode _op);		// 判断四元式的操作数是否为 jump or branch, 具体为 BGT BGE BLT BLE BEQ BNE BNZ BEZ JUMP
		void updateFlag(QuaterInstr * new_quater_instr);	// 根据生成的指令更新flag数组
		QuaterInstr* gen(Opcode _op, struct symbolItem* _des = NULL, struct symbolItem* _src1 = NULL, struct symbolItem* _src2 = NULL);
		QuaterInstr* gen(Opcode _op, std::string label, struct symbolItem* _src1 = NULL, struct symbolItem* _src2 = NULL);

		void clear();	// 清空中间代码缓冲区 和 基本块数组 和 flag数组
		void printMiddleCode();	// [调试] 输出这段中间代码
		void optimize(); // 优化中间代码
		void load(); // 将中间代码分为基本块, 并加载到基本块数组中
		void store(); // 将基本块数组中的值, 装回中间代码缓冲区
        
		std::vector<int> flag;	// 判断该指令是否是基本块的入口
		std::vector<Block *> basicBlocks;	// 基本块数组
        std::vector<QuaterInstr *> middle_codes;	// 中间代码缓冲
    protected:
    private:
		bool preQuaterInstructionIsJumpOrBranch = false;
};

#endif // MIDDLECODE_H
