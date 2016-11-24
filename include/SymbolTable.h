#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <string>
#include "Laxer.h"

struct symbolItem
{
    std::string name; // 标识符名字
    int line;   // 声明行数
    int kind;   // 符号的类型, 常量, 变量, 函数, 变量数组, 参数
    int type;   // int or char or void
    int valueoroffset;    // 值, 如果是常量的话/相对基地址偏移, 如果是变量或数组的话
    int length; // 数组长度
};
class SymbolTable
{
    public:
        SymbolTable();  // 构造函数
        virtual ~SymbolTable(); // 析构函数

        struct symbolItem *searchItem(std::string name);
        struct symbolItem *insertItem(std::string name, int line, int kind, int type, int val = 0, int length = 0);
        struct symbolItem *generateTemp();
		struct symbolItem* SymbolTable::generateTempConstant(int value);

    protected:
    private:
        std::map<std::string, struct symbolItem*> symbolList;
        int offset;
};

// 符号表
// 符号类型 kind
#define CONSTANT 1
#define VARIABLE 2
#define FUNCTION 3

// 符号数据类型 type
#define INT_TYPE INT
#define CHAR_TYPE CHAR
#define VOID_TYPE VOID
#define STRING_TYPE 30

#endif // SYMBOLTABLE_H
