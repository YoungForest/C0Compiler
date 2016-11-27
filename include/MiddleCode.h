#ifndef MIDDLECODE_H
#define MIDDLECODE_H

#include <vector>
#include <string>
#include "QuaterInstr.h"
#include "SymbolTable.h"

class MiddleCode
{
    public:
        MiddleCode();
        virtual ~MiddleCode();
        QuaterInstr* gen(Opcode _op, struct symbolItem* _des = NULL, struct symbolItem* _src1 = NULL, struct symbolItem* _src2 = NULL);
		QuaterInstr* gen(Opcode _op, std::string label, struct symbolItem* _src1 = NULL, struct symbolItem* _src2 = NULL);

		void clear();	// 清空中间代码缓冲区
		void printMiddleCode();	// [调试] 输出这段中间代码
        
        std::vector<QuaterInstr*> middle_codes;	// 中间代码缓冲
    protected:
    private:
};

#endif // MIDDLECODE_H
