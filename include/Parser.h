#ifndef PARSER_H
#define PARSER_H

#include "Laxer.h"
#include "SymbolTable.h"
#include "Error.h"

class Parser
{
    public:
        Parser(string filein) : laxer(filein, error_handler) {};
        virtual ~Parser();

        void parserTestPrint(string s);  // 语法分析程序测试程序, 输出 语法成分
        void test(SymbolTable st);  // 检查词法分析程序得到的标识符是否有效

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
        void globalVarietyDenote(int type, string ident);
        int typeIndentify();    // <类型标识符>      ::=  int | char


        // struct symbolItem* defineReturnFunction(); // <有返回值函数定义>  ::=  <声明头部>‘(’<参数>‘)’ ‘{’<复合语句>‘}’
        void defineReturnFunction();
        // struct symbolItem* defineVoidFunction(); // <无返回值函数定义>  ::= void<标识符>‘(’<参数>‘)’‘{’<复合语句>‘}’
        void defineVoidFunction();

        void compoundStatement();   // <有返回值函数定义>  ::=  <声明头部>‘(’<参数>‘)’ ‘{’<复合语句>‘}’
        void parameterTable();  // <参数表>    ::=  <类型标识符><标识符>{,<类型标识符><标识符>}| <空>
        void mainFunction();    // <主函数>    ::= void main‘(’‘)’ ‘{’<复合语句>‘}’

        struct symbolItem* item();  // <因子>{<乘法运算符><因子>}
        struct symbolItem* expression();    // <表达式>    ::= ［＋｜－］<项>{<加法运算符><项>}
        struct symbolItem* factor();    // <因子>    ::= <标识符>｜<标识符>‘[’<表达式>‘]’｜<整数>|<字符>｜<有返回值函数调用语句>|‘(’<表达式>‘)’

        void statement();   // <语句>    ::= <条件语句>｜<循环语句>｜‘{’<语句列>‘}’｜<函数调用语句>;｜<赋值语句>;｜<读语句>;｜<写语句>;｜<空>;｜<返回语句>;
        void assignStatement(); // <赋值语句>   ::=  <标识符>＝<表达式>|<标识符>‘[’<表达式>‘]’=<表达式>
        void branchStatement(); // <条件语句>  ::=  if ‘(’<条件>‘)’<语句>［else<语句>］
        struct symbolItem* condition(); // <条件>    ::=  <表达式><关系运算符><表达式>｜<表达式> //表达式为0条件为假，否则为真
        void cycleStatement();  // <循环语句>   ::=  do<语句>while ‘(’<条件>‘)’ |for‘(’<标识符>＝<表达式>;<条件>;<标识符>＝<标识符>(+|-)<步长>‘)’<语句>
        int step(); // <步长>::= <无符号整数>

        void callFunction();    // <函数调用语句> ::= <标识符>‘(’<值参数表>‘)’
        struct symbolItem* callReturnFunction();    // <有返回值函数调用语句> ::= <标识符>‘(’<值参数表>‘)’
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
