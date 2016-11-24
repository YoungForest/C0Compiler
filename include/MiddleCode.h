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
        QuaterInstr* gen(Opcode _op, struct symbolItem* _des  , struct symbolItem* _src1  , struct symbolItem* _src2 );
        void printMiddleCode();
        void addDataSeg(std::string _stringconst);  // 添加常量字符串到data区
        vector<QuaterInstr*>* getMiddleCode();

        std::vector<QuaterInstr *> middle_code;
        std::vector<std::string> data_const_string;
    protected:
    private:
};

#endif // MIDDLECODE_H
