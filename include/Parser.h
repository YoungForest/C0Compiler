#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "Laxer.h"
#include "SymbolTable.h"
#include "MiddleCode.h"
#include "MipsInstrGen.h"
#include "Error.h"

#define FRAME_LEN 1000

class Parser
{
    public:
        Parser(std::string filein) : mipsInstrGen(error_handler), laxer(filein, error_handler), globalTable(GLOBAL), localTable(LOCAL) {};
        virtual ~Parser();

        void parser(std::string fileout);
		void generateFinalCode();	// 生成目标代码, 控制优化开关
		void functionIn(std::string s);
        void parserTestPrint(std::string s);  // [调试] 语法分析程序测试程序, 输出 语法成分
		struct symbolItem* test(std::string ident);	// 测试标识符是否在符号表中
		void test2(std::string ident, SymbolTable *st);	// 变量定义, 检查是否重复定义

        // delete, because distribe this task to lexer char charactor();   // <字符>    ::=  '<加法运算符>'｜'<乘法运算符>'｜'<字母>'｜'<数字>'
        void program(); // <程序>    ::= ［<常量说明>］［<变量说明>］{<有返回值函数定义>|<无返回值函数定义>}<主函数>
        void constantDenote(SymbolTable &table);    // <常量说明> ::=  const<常量定义>;{ const<常量定义>;}
        void constantDefine(SymbolTable &table);    // <常量定义>   ::=   int<标识符>＝<整数>{,<标识符>＝<整数>} | char<标识符>＝<字符>{,<标识符>＝<字符>}
        int integer();  // <整数>        ::= ［+｜-］<无符号整数>｜０

        void varietyDenote(SymbolTable &table); // <变量说明>  ::= <变量定义>;{<变量定义>;}
        void varietyDenote(SymbolTable &table, int type, std::string ident); // <变量说明>  ::= <变量定义>;{<变量定义>;}

        // struct symbolItem* defineReturnFunction(); // <有返回值函数定义>  ::=  <声明头部>‘(’<参数>‘)’ ‘{’<复合语句>‘}’
        void defineReturnFunction(int type, std::string ident);
        // struct symbolItem* defineVoidFunction(); // <无返回值函数定义>  ::= void<标识符>‘(’<参数>‘)’‘{’<复合语句>‘}’
        void defineVoidFunction();

        void compoundStatement();  // <复合语句>   ::=  ［<常量说明>］［<变量说明>］<语句列>
        int parameterTable(std::string functionName);  // <参数表>    ::=  <类型标识符><标识符>{,<类型标识符><标识符>}| <空>
        void mainFunction();    // <主函数>    ::= void main‘(’‘)’ ‘{’<复合语句>‘}’

        struct symbolItem* item();  // <因子>{<乘法运算符><因子>}
        struct symbolItem* expression();    // <表达式>    ::= ［＋｜－］<项>{<加法运算符><项>}
        struct symbolItem* factor();    // <因子>    ::= <标识符>｜<标识符>‘[’<表达式>‘]’｜<整数>|<字符>｜<有返回值函数调用语句>|‘(’<表达式>‘)’

        void statement();   // <语句>    ::= <条件语句>｜<循环语句>｜‘{’<语句列>‘}’｜<函数调用语句>;｜<赋值语句>;｜<读语句>;｜<写语句>;｜<空>;｜<返回语句>;
        void assignStatement(std::string ident); // <赋值语句>   ::=  <标识符>＝<表达式>|<标识符>‘[’<表达式>‘]’=<表达式>
        void branchStatement(); // <条件语句>  ::=  if ‘(’<条件>‘)’<语句>［else<语句>］
        // struct symbolItem* condition(); // <条件>    ::=  <表达式><关系运算符><表达式>｜<表达式> //表达式为0条件为假，否则为真
        void condition(struct symbolItem *&cmp1, struct symbolItem* &cmp2, int &cmpOp);
        void doCycleStatement();  // <do循环语句>   ::=  for‘(’<标识符>＝<表达式>;<条件>;<标识符>＝<标识符>(+|-)<步长>‘)’<语句>
        void forCycleStatement();  // <for循环语句>   ::=  for‘(’<标识符>＝<表达式>;<条件>;<标识符>＝<标识符>(+|-)<步长>‘)’<语句>
        //int step(); // <步长>::= <无符号整数> 简化掉了

		// 由符号表检查是否有返回值
        //void callFunction(std::string ident);    // <函数调用语句> ::= <标识符>‘(’<值参数表>‘)’
        struct symbolItem* callFunction(std::string ident);   // <有返回值函数调用语句> ::= <标识符>‘(’<值参数表>‘)’
        // <无返回值函数调用语句> ::= <标识符>‘(’<值参数表>‘)’
        void valueParameterTable(struct symbolItem* func); // <值参数表>   ::= <表达式>{,<表达式>}｜<空>
        void statementList();   // <语句列>   ::=｛<语句>｝
        void read();    // <读语句>    ::=  scanf ‘(’<标识符>{,<标识符>}‘)’
        void write();   // <写语句>    ::=  printf‘(’<字符串>,<表达式>‘)’|printf ‘(’<字符串>‘)’|printf ‘(’<表达式>‘)’
        void returnStatement(); // <返回语句>   ::=  return[‘(’<表达式>‘)’]

		// 生成目标代码
		int addDataSeg(std::string _stringconst);  // 添加常量字符串到data区, 返回常量字符串标号
		void addDataGlobal(std::string _str);	// 添加全局声明到data区

		std::string to_string(int i);	// 修复code blocks g++ (tdm-1) 4.7.1 bug

		void errorGenerate(int errortype);
		void errorGenerate(int errortype, std::string message1);
		void errorGenerate(int errortype, std::string message1, std::string message2);
		void warningGenerate(int warningtype, std::string message1);

    protected:
    private:
        SymbolTable globalTable;
        SymbolTable localTable;
        MiddleCode middleCode;
		MipsInstrGen mipsInstrGen;
        Error error_handler;
        Laxer laxer;
		std::vector<std::string> data_const_string;
		std::vector<std::string> data_global_v;
		std::vector<Instruction> finalCodes;
		bool returnFlag;	// ture => char or int; false => void
};

#endif // PARSER_H
