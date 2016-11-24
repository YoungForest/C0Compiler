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
        void printMiddleCode();
        int addDataSeg(std::string _stringconst);  // 添加常量字符串到data区
        std::vector<QuaterInstr*>* getMiddleCode();

        std::vector<QuaterInstr *> middle_codes;
        std::vector<std::string> data_const_string;
    protected:
    private:
};

#endif // MIDDLECODE_H
