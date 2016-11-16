#ifndef PARSER_H
#define PARSER_H

#include "Laxer.h"
#include "SymbolTable.h"
#include "Error.h"
#include <string>

class Parser
{
    public:
        Parser(std::string filein) : laxer(filein, error_handler) {};
        virtual ~Parser();

        void parser();
        void functionIn(std::string s);
        void parserTestPrint(std::string s);  // 语法分析程序测试程序, 输出 语法成分
        void test(SymbolTable st);  // 检查词法分析程序得到的标识符是否有效

        char charactor();   // <字符>    ::=  '<加法运算符>'｜'<乘法运算符>'｜'<字母>'｜'<数字>'
        void program(); // <程序>    ::= ［<常量说明>］［<变量说明>］{<有返回值函数定义>|<无返回值函数定义>}<主函数>
        void constantDenote(SymbolTable *table);    // <常量说明> ::=  const<常量定义>;{ const<常量定义>;}
        void constantDefine(SymbolTable *table);    // <常量定义>   ::=   int<标识符>＝<整数>{,<标识符>＝<整数>} | char<标识符>＝<字符>{,<标识符>＝<字符>}
        void integer();  // <整数>        ::= ［+｜-］<无符号整数>｜０

        void varietyDenote(SymbolTable *table); // <变量说明>  ::= <变量定义>;{<变量定义>;}
        void varietyDenote(SymbolTable *table, int type, std::string ident); // <变量说明>  ::= <变量定义>;{<变量定义>;}

        // struct symbolItem* defineReturnFunction(); // <有返回值函数定义>  ::=  <声明头部>‘(’<参数>‘)’ ‘{’<复合语句>‘}’
        void defineReturnFunction(int type, std::string ident);
        // struct symbolItem* defineVoidFunction(); // <无返回值函数定义>  ::= void<标识符>‘(’<参数>‘)’‘{’<复合语句>‘}’
        void defineVoidFunction();

        void compoundStatement();  // <复合语句>   ::=  ［<常量说明>］［<变量说明>］<语句列>
        void parameterTable();  // <参数表>    ::=  <类型标识符><标识符>{,<类型标识符><标识符>}| <空>
        void mainFunction();    // <主函数>    ::= void main‘(’‘)’ ‘{’<复合语句>‘}’

        // struct symbolItem* item();  // <因子>{<乘法运算符><因子>}
        void item();
        // struct symbolItem* expression();    // <表达式>    ::= ［＋｜－］<项>{<加法运算符><项>}
        void expression();
        // struct symbolItem* factor();    // <因子>    ::= <标识符>｜<标识符>‘[’<表达式>‘]’｜<整数>|<字符>｜<有返回值函数调用语句>|‘(’<表达式>‘)’
        void factor();

        void statement();   // <语句>    ::= <条件语句>｜<循环语句>｜‘{’<语句列>‘}’｜<函数调用语句>;｜<赋值语句>;｜<读语句>;｜<写语句>;｜<空>;｜<返回语句>;
        void assignStatement(std::string ident); // <赋值语句>   ::=  <标识符>＝<表达式>|<标识符>‘[’<表达式>‘]’=<表达式>
        void branchStatement(); // <条件语句>  ::=  if ‘(’<条件>‘)’<语句>［else<语句>］
        // struct symbolItem* condition(); // <条件>    ::=  <表达式><关系运算符><表达式>｜<表达式> //表达式为0条件为假，否则为真
        void condition();
        void doCycleStatement();  // <do循环语句>   ::=  for‘(’<标识符>＝<表达式>;<条件>;<标识符>＝<标识符>(+|-)<步长>‘)’<语句>
        void forCycleStatement();  // <for循环语句>   ::=  for‘(’<标识符>＝<表达式>;<条件>;<标识符>＝<标识符>(+|-)<步长>‘)’<语句>
        int step(); // <步长>::= <无符号整数>

        void callFunction(std::string ident);    // <函数调用语句> ::= <标识符>‘(’<值参数表>‘)’
        // struct symbolItem* callReturnFunction();    // <有返回值函数调用语句> ::= <标识符>‘(’<值参数表>‘)’
        void callReturnFunction();
        void callVoidFunction();    // <无返回值函数调用语句> ::= <标识符>‘(’<值参数表>‘)’
        void valueParameterTable(); // <值参数表>   ::= <表达式>{,<表达式>}｜<空>
        void statementList();   // <语句列>   ::=｛<语句>｝
        void read();    // <读语句>    ::=  scanf ‘(’<标识符>{,<标识符>}‘)’
        void write();   // <写语句>    ::=  printf‘(’<字符串>,<表达式>‘)’|printf ‘(’<字符串>‘)’|printf ‘(’<表达式>‘)’
        void returnStatement(); // <返回语句>   ::=  return[‘(’<表达式>‘)’]

    protected:
    private:
        SymbolTable globalTable;
        SymbolTable localTable;
        Error error_handler;
        Laxer laxer;
};

#endif // PARSER_H
