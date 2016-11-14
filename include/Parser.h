#ifndef PARSER_H
#define PARSER_H

#include "MyHeader.h"

class Parser
{
    public:
        Parser();
        virtual ~Parser();

        void test(SymbolTable st);  // 检查词法分析程序得到的标识符是否有效

        char alphabet();    // <字母>   ::= ＿｜a｜．．．｜z｜A｜．．．｜Z
        int number();   // <数字>   ::= ０｜<非零数字>
        int no0number();    // <非零数字>  ::= １｜．．．｜９
        char charactor();   // <字符>    ::=  '<加法运算符>'｜'<乘法运算符>'｜'<字母>'｜'<数字>'
        void program(); // <程序>    ::= ［<常量说明>］［<变量说明>］{<有返回值函数定义>|<无返回值函数定义>}<主函数>
        void constantDenote(SymbolTable *table);    // <常量说明> ::=  const<常量定义>;{ const<常量定义>;}
        void constantDefine(SymbolTable *table);    // <常量定义>   ::=   int<标识符>＝<整数>{,<标识符>＝<整数>} | char<标识符>＝<字符>{,<标识符>＝<字符>}
        int unsignedInteger();  // <无符号整数>  ::= <非零数字>｛<数字>｝
        int Integer();  // <整数>        ::= ［+｜-］<无符号整数>｜０
        std::string identity(); // <标识符>    ::=  <字母>｛<字母>｜<数字>｝
        int declareHead();  // <声明头部>   ::=  int<标识符>|char<标识符>
        void varietyDenote(SymbolTable *table); // <变量说明>  ::= <变量定义>;{<变量定义>;}
        void varietyDefine(SymbolTable *table); // <变量定义>  ::= <类型标识符>(<标识符>|<标识符>‘[’<无符号整数>‘]’){,(<标识符>|<标识符>‘[’<无符号整数>‘]’) }

        struct symbolItem* callReturnFunction(struct symbolItem* func); 
        void callVoidFunction(struct symbolItem* func);

        struct symbolItem* item();
        struct symbolItem* expression();
        struct symbolItem* factor();




    protected:
    private:
        SymbolTable globalTable;
        Error error_handler;
};

#endif // PARSER_H
