#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <vector>
#include <string>
#include "Laxer.h"

struct symbolItem
{
    std::string name; // 标识符名字
    int line;   // 声明行数
    int kind;   // 符号的类型, 常量, 变量, 函数, 参数
    int type;   // int or char or void
    int valueoroffset;    // 值, 如果是常量的话 or 相对基地址偏移, 如果是变量或数组的话
    int length; // 数组长度, or 函数参数数量
	int scope; // 全局或局部变量
};
class SymbolTable
{
    public:
        SymbolTable(int _scope);  // 构造函数
        virtual ~SymbolTable(); // 析构函数
		struct symbolItem* searchItem(std::string ident);
        struct symbolItem* insertItem(std::string name, int line, int kind, int type, int val = 0, int length = 0);
        struct symbolItem* generateTemp();	// 生成临时变量
		struct symbolItem* generateTempChar();	// 生成临时字符类型变量
		struct symbolItem* generateTempConstant(int value, int type);	// 生成临时常量
		int getPosition(struct symbolItem* elem);	// 获取元素的下标, 为找到函数的参数
		void clear();	// 清空符号表
		
		std::vector<struct symbolItem*> symbolList;
		int offset;

    protected:
    private:
		int scope;
};

// 符号表
// 符号类型 kind
#define CONSTANT 1
#define VARIABLE 2
#define FUNCTION 3
#define PARAMETER 4

// 符号数据类型 type
#define INT_TYPE INT
#define CHAR_TYPE CHAR
#define VOID_TYPE VOID
#define STRING_TYPE STRING

// 符号作用域
#define LOCAL 2
#define GLOBAL 3

#endif // SYMBOLTABLE_H
