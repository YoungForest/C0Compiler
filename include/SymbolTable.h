#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>

struct symbolItem
{
    String name; // 标识符名字
    int line;   // 声明行数
    int kind;   // 符号的类型, 常量, 变量, 函数, 变量数组, 参数
    int type;   // int or char or void
    int valoroffset;    // 值, 如果是常量的话/相对基地址偏移, 如果是变量或数组的话
    int length; // 数组长度
};
class SymbolTable
{
    public:
        SymbolTable();  // 构造函数
        virtual ~SymbolTable(); // 析构函数

        struct symbolItem searchItem(string name);
        bool insertItem(string name, int line, int kind, int type, int val = 0, int length = 1)

    protected:
    private:
        std::map<string, struct symbolItem> symbolList;
        int offset = 0;
};

// 符号表
// 符号类型 kind
#define CONSTANT 1
#define VARIABLE 2
#define FUNCTION 3

// 符号数据类型 type
#define INT_TYPE 1
#define CHAR_TYPE 2
#define VOID_TYPE 3

#endif // SYMBOLTABLE_H
