#include "Parser.h"
#include "Error.h"
#include "SymbolTable.h"
#include <ctype.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>

//#define OPTIMIZE

using namespace std;

Parser::~Parser()
{
	//dtor
}

string Parser::to_string(int i)
{
	stringstream ss;
	ss << i;
	string s = ss.str();
	return s;
}

// [错误处理]
void Parser::errorGenerate(int errortype)
{
	error_handler.errorMessage(errortype, laxer.lastlinenum, laxer.lastcc);
}

// [错误处理]
void Parser::errorGenerate(int errortype, std::string message1)
{
	error_handler.errorMessage(errortype, laxer.lastlinenum, laxer.lastcc, message1);
}

void Parser::errorGenerate(int errortype, std::string message1, std::string message2)
{
	error_handler.errorMessage(errortype, laxer.lastlinenum, laxer.lastcc, message1, message2);
}

void Parser::warningGenerate(int warningtype, std::string message1)
{
	error_handler.warningMessage(warningtype, laxer.lastlinenum, laxer.lastcc, message1);
}

// [调试]
void Parser::parserTestPrint(string s)
{
#ifdef DEBUG
	//cout << "Line : " << laxer.linenum << " column : " << laxer.cc << ".   This is a " << s << " ! " << endl;
#endif // DEBUG
}

// [调试]
void Parser::functionIn(string s)
{
#ifdef DEBUG
	//cout << "Function in " << s << endl;
#endif // DEBUG
}

// 根据变量名, 查找符号表, 如果未找到报错
struct symbolItem* Parser::test(string ident)
{
	SymbolTable* st;
	st = &localTable;
#ifdef DEBUG
	//cout << ident << endl;
#endif // DEBUG

	struct symbolItem* re = st->searchItem(ident);
	if (re == NULL)
	{
		st = &globalTable;
		re = st->searchItem(ident);
		if (re == NULL)
		{
			errorGenerate(103, ident);
			re = globalTable.insertItem(ident, laxer.linenum, VARIABLE, INT_TYPE, 0, laxer.num);	// 如果未找到, 容错处理
		}
	}
	return re;
}

// 根据变量名, 查找符号表, 如果找到报错(重复定义)
void Parser::test2(string ident, SymbolTable *st)
{
	struct symbolItem* re = st->searchItem(ident);
	if (re != NULL)
		errorGenerate(200, ident, to_string(re->line));
}


void Parser::parser(string fileout)
{
	laxer.getsym();
	program();	// 进入语法分析程序入口, 同时语义分析, 生成中间代码, 生成目标代码
	if (error_handler.warning_count > 0)
	{
		error_handler.printWarnings();
		cout << endl << "Warnings count: " << error_handler.warning_count << endl;
	}
	if (!error_handler.isSuccess())
	{
		error_handler.printErrors();
		cout << endl << "Compiled error! exit code -1. error count: " << error_handler.getErrorCount() << endl;
	}
	else
	{
		cout << endl << "Compiled success!" << endl;

		// 将全局变量输出到.data缓冲数组中
		vector<struct symbolItem*>::iterator it = globalTable.symbolList.begin();
		while (it != globalTable.symbolList.end())
		{
			if ((*it)->kind == VARIABLE && (*it)->length == 0)
				addDataGlobal((*it)->name + ": .word 0");
			else if ((*it)->kind == VARIABLE && (*it)->length > 0)
				addDataGlobal((*it)->name + ": .space " + to_string(4 * ((*it)->length)));
			else
				;
			it++;
		}
		fstream fo(fileout, ios::out);
#ifdef VS
		// print date and time, make it easier to debug
		fo << "# generate time: " << __TIME__ << " " << __DATE__ << endl;
#endif // VS
		// print data segament
		fo << ".data" << endl;
		for (int i = 0; i < data_global_v.size(); i++)
			fo << data_global_v[i] << endl;
		for (int i = 0; i < data_const_string.size(); i++)
			fo << "yangsen_string" << i << ": .asciiz \"" << data_const_string[i] << "\"" << endl;
		// runtime error message
		fo << "divi0errorMessage: .asciiz \"Runtime Error: divide by 0.\"" << endl;
		fo << "arrayOutOfRangeMeaage: .asciiz \"Runtime Error: the index of array is out of range.\"" << endl;
		// print text segament
		fo << ".text" << endl;
		fo << "move $fp, $sp" << endl;
		fo << "j end" << endl;
		// runtime error process
		fo << "divi0error:" << endl;
		fo << "li $v0 4" << endl;
		fo << "la $a0 divi0errorMessage" << endl;
		fo << "syscall" << endl;
		fo << "j endOfAll" << endl;
		fo << "arrayOutOfRange:" << endl;
		fo << "li $v0 4" << endl;
		fo << "la $a0 arrayOutOfRangeMeaage" << endl;
		fo << "syscall" << endl;
		fo << "j endOfAll" << endl;
		// 生成的目标代码
		mipsInstrGen.holeOptimize();	// 窥孔优化
		for (int i = 0; i < mipsInstrGen.finalCodes.size(); i++)
			fo << mipsInstrGen.finalCodes[i].getInstr() << endl;
		// 程序结束控制指令
		fo << "end:" << endl;
		fo << "jal main" << endl;
		fo << "endOfAll:" << endl;
	}
}

void Parser::generateFinalCode()
{
	if (error_handler.isSuccess())
	{
#ifdef OPTIMIZE
		middleCode.optimize();
#endif // OPTIMIZE
		middleCode.printMiddleCode();
		mipsInstrGen.generateInstruction(middleCode.middle_codes);
	}
	middleCode.clear();
	localTable.clear();
}

// <程序>    ::= ［<常量说明>］［<变量说明>］{(int|char) <标识符> <有返回值函数定义>| void <无返回值函数定义>} void <主函数>
void Parser::program()
{
	functionIn("program");
	if (laxer.sym == CONST)
		constantDenote(globalTable);
	while (laxer.sym == INT || laxer.sym == CHAR)
	{
		int type = laxer.sym;
		laxer.getsym();
		if (laxer.sym == IDENTIFIER)
		{
			string ident = laxer.getToken();
			laxer.getsym();
			if (laxer.sym == SEMICOLON || laxer.sym == COMMA || laxer.sym == LSQUARE)
			{
				varietyDenote(globalTable, type, ident);
			}
			else if (laxer.sym == LPARENT)
			{
				defineReturnFunction(type, ident);
				break;	// 跳出循环, 函数声明后只能有其他函数声明和main函数
			}
			else
			{
				errorGenerate(6);
			}
		}
		else
		{
			errorGenerate(4);
		}
	}
	while (laxer.sym == INT || laxer.sym == CHAR || laxer.sym == VOID)
	{
		if (laxer.sym == VOID)
		{
			laxer.getsym();
			if (laxer.sym == MAIN)
			{
				mainFunction();
				parserTestPrint("program");
				break;
			}
			else if (laxer.sym == IDENTIFIER)
			{
				defineVoidFunction();
			}
			else
			{
				errorGenerate(8);
			}
		}
		else
		{
			int type = laxer.sym;
			laxer.getsym();
			if (laxer.sym == IDENTIFIER)
			{
				string ident = laxer.getToken();
				laxer.getsym();
				defineReturnFunction(type, ident);
			}
			else
			{
				errorGenerate(10);
			}
		}
	}
}

// <无返回值函数定义>  ::= <标识符> ‘(’<参数表>‘)’‘{’<复合语句>‘}’
void Parser::defineVoidFunction()
{
	functionIn("defineVoidFunction");
	returnFlag = false;
	string ident;
	int length = 0;
	if (laxer.sym == IDENTIFIER)	// have to be true
	{
		ident = laxer.getToken();
		laxer.getsym();
		if (laxer.sym == LPARENT)
		{
			laxer.getsym();
			test2(ident, &globalTable);
			struct symbolItem* f = globalTable.insertItem(ident, laxer.linenum, FUNCTION, VOID_TYPE, 0, length);
			length = parameterTable(ident);
			f->length = length;
			if (laxer.sym == RPARENT)
			{
				middleCode.gen(Opcode::DEC, f);
				laxer.getsym();
				if (laxer.sym == LCURLY)
				{
					laxer.getsym();
					compoundStatement();
					if (laxer.sym == RCURLY)
					{
						laxer.getsym();
						parserTestPrint("void function define");
					}
					else
					{
						errorGenerate(18);
					}
				}
				else
				{
					errorGenerate(16);
				}
			}
			else
			{
				errorGenerate(14);
			}
		}
		else
		{
			errorGenerate(12);
		}
	}
	middleCode.gen(Opcode::RET);
	generateFinalCode();
}

// <有返回值函数定义>  ::= '(' <参数表>‘)’ ‘{’<复合语句>‘}’
void Parser::defineReturnFunction(int type, string ident)
{
	returnFlag = true;
	int length = 0;
	functionIn("defineReturnFunction");

	if (laxer.sym == LPARENT)
	{
		laxer.getsym();
		test2(ident, &globalTable);
		struct symbolItem* f = globalTable.insertItem(ident, laxer.linenum, FUNCTION, type, 0, length);
		length = parameterTable(ident);
		f->length = length;
		middleCode.gen(Opcode::DEC, f);
		if (laxer.sym == RPARENT)
		{
			laxer.getsym();
			if (laxer.sym == LCURLY)
			{
				laxer.getsym();
				compoundStatement();
				if (laxer.sym == RCURLY)
				{
					laxer.getsym();
					parserTestPrint("return function define");
				}
				else
				{
					errorGenerate(18);
				}
			}
			else
			{
				errorGenerate(16);
			}
		}
		else
		{
			errorGenerate(14);
		}
	}
	else
	{
		errorGenerate(12);
	}
	middleCode.gen(Opcode::RET);
	generateFinalCode();
}

// <复合语句>   :: = ［<常量说明>］［<变量说明>］<语句列>
void Parser::compoundStatement()
{
	functionIn("compoundStatement");
	if (laxer.sym == CONST)
	{
		constantDenote(localTable);
	}
	if (laxer.sym == INT || laxer.sym == CHAR)
	{
		varietyDenote(localTable);
	}
	//int offset = localTable.offset;
#ifdef OPTIMIZE
	middleCode.gen(Opcode::DSP, to_string(FRAME_LEN));
	//middleCode.gen(Opcode::DSP, to_string(localTable.offset));
#else
	middleCode.gen(Opcode::DSP);
#endif // OPTIMIZE
	statementList();
	parserTestPrint("compound statement");
}

// <变量定义>  :: = <类型标识符>(<标识符> | <标识符>‘[’<无符号整数>‘]’) { , (<标识符> | <标识符>‘[’<无符号整数>‘]’) }
void Parser::varietyDenote(SymbolTable &table)
{
	string ident;
	int type;
	functionIn("varietyDenote");
	while (laxer.sym == INT || laxer.sym == CHAR)
	{
		type = laxer.sym;
		do
		{
			laxer.getsym();
			if (laxer.sym == IDENTIFIER)
			{
				ident = laxer.getToken();
				test2(ident, &table);
				laxer.getsym();
				if (laxer.sym == LSQUARE)
				{
					laxer.getsym();
					if (laxer.sym == UNSIGNED_INGEGER)
					{
						table.insertItem(ident, laxer.linenum, VARIABLE, type, 0, laxer.num);
						laxer.getsym();
					}
					else
					{
						table.insertItem(ident, laxer.linenum, VARIABLE, type, 0, 20);	// 容错处理, 设数组长度为20
						errorGenerate(22);
					}
					if (laxer.sym == RSQUARE)
					{
						laxer.getsym();
					}
					else
					{
						errorGenerate(24);
					}
				}
				else
				{
					table.insertItem(ident, laxer.linenum, VARIABLE, type);
				}
			}
			else
			{
				errorGenerate(20);
			}
		} while (laxer.sym == COMMA);
		if (laxer.sym == SEMICOLON)
		{
			laxer.getsym();
			parserTestPrint("variety define");
		}
		else
		{
			errorGenerate(26);
		}
	}
	parserTestPrint("variety denote");
}

// 全局变量声明, 为了避免回溯 <变量说明>  ::= <变量定义>;{<变量定义>;}
void Parser::varietyDenote(SymbolTable &table, int type, string ident)
{
	functionIn("varietyDenote");
	test2(ident, &table);
	if (laxer.sym == LSQUARE)
	{
		laxer.getsym();
		if (laxer.sym == UNSIGNED_INGEGER)
		{
			table.insertItem(ident, laxer.linenum, VARIABLE, type, 0, laxer.num);
			laxer.getsym();
		}
		else
		{
			table.insertItem(ident, laxer.linenum, VARIABLE, type, 0, 20);	// 容错处理, 设数组长度为20
			errorGenerate(22);
		}
		if (laxer.sym == RSQUARE)
		{
			laxer.getsym();
		}
		else
		{
			errorGenerate(24);
		}
	}
	else
	{
		table.insertItem(ident, laxer.linenum, VARIABLE, type);
	}
	while (laxer.sym == COMMA)
	{
		string ident2;
		laxer.getsym();
		if (laxer.sym == IDENTIFIER)
		{
			ident2 = laxer.getToken();
			test2(ident2, &table);
			laxer.getsym();
			if (laxer.sym == LSQUARE)
			{
				laxer.getsym();
				if (laxer.sym == UNSIGNED_INGEGER)
				{
					table.insertItem(ident2, laxer.linenum, VARIABLE, type, 0, laxer.num);
					laxer.getsym();
				}
				else
				{
					table.insertItem(ident2, laxer.linenum, VARIABLE, type, 0, 20);	// 容错处理, 设数组长度为20
					errorGenerate(22);
				}
				if (laxer.sym == RSQUARE)
				{
					laxer.getsym();
				}
				else
				{
					errorGenerate(24);
				}
			}
			else
			{
				table.insertItem(ident2, laxer.linenum, VARIABLE, type);
			}
		}
		else
		{
			errorGenerate(20);
		}

	}
	if (laxer.sym == SEMICOLON)
	{
		laxer.getsym();
		parserTestPrint("global variety define");
	}
	else
	{
		errorGenerate(26);
	}
}

// [返回值] 参数数量
int Parser::parameterTable(string functionName)
{
	int count = 0;
	int type;
	string ident;
	functionIn("parameterTable");
	if (laxer.sym == INT || laxer.sym == CHAR)
	{
		if (laxer.sym == INT)
			type = INT_TYPE;
		else
			type = CHAR_TYPE;
		laxer.getsym();
		if (laxer.sym == IDENTIFIER)
		{
			count++;
			ident = laxer.getToken();
			laxer.getsym();
			if (ident == functionName)
				errorGenerate(114, ident);
			test2(ident, &localTable);
			struct symbolItem * para = localTable.insertItem(ident, laxer.linenum, PARAMETER, type);
			globalTable.insertItem(ident, laxer.linenum, PARAMETER, type, para->valueoroffset);
		}
		else
		{
			errorGenerate(20);
		}
		while (laxer.sym == COMMA)
		{
			laxer.getsym();
			if (laxer.sym == INT || laxer.sym == CHAR)
			{
				if (laxer.sym == INT)
					type = INT_TYPE;
				else
					type = CHAR_TYPE;
				laxer.getsym();
				if (laxer.sym == IDENTIFIER)
				{
					ident = laxer.getToken();
					count++;
					laxer.getsym();
					struct symbolItem * para = localTable.insertItem(ident, laxer.linenum, PARAMETER, type);
					globalTable.insertItem(ident, laxer.linenum, PARAMETER, type, para->valueoroffset);
				}
				else
				{
					errorGenerate(20);
				}
			}
			else
			{
				errorGenerate(28);
			}
		}
	}
	return count;
	parserTestPrint("parameter table");
}

// <主函数>    :: = main‘(’‘)’ ‘ { ’<复合语句>‘ }’
void Parser::mainFunction()
{
	functionIn("mainFunction");
	returnFlag = false;
	if (laxer.sym == MAIN)
	{
		struct symbolItem *main = new symbolItem();
		main->name = "main";
		middleCode.gen(Opcode::DEC, main);
		//middleCode.gen(Opcode::SET, "main");
		laxer.getsym();
		if (laxer.sym == LPARENT)
		{
			laxer.getsym();
			if (laxer.sym == RPARENT)
			{
				laxer.getsym();
				if (laxer.sym == LCURLY)
				{
					laxer.getsym();
					compoundStatement();
					if (laxer.sym == RCURLY)
					{
						parserTestPrint("main function");
						laxer.getsym();
					}
					else
					{
						errorGenerate(18);
					}
				}
				else
				{
					errorGenerate(16);
				}
			}
			else
			{
				errorGenerate(14);
			}
		}
		else
		{
			errorGenerate(12);
		}
	}
	middleCode.gen(Opcode::RET);
	generateFinalCode();
}

// <常量说明> :: = const<常量定义>; { const<常量定义>; }
void Parser::constantDenote(SymbolTable &table)
{
	functionIn("constantDenote");
	if (laxer.sym == CONST)
	{
		do
		{
			laxer.getsym();
			constantDefine(table);
			if (laxer.sym == SEMICOLON)
			{
				laxer.getsym();
			}
			else
			{
				errorGenerate(26);
			}
		} while (laxer.sym == CONST);
		parserTestPrint("constant denote");
	}
}

// <常量定义>   ::=   int<标识符>＝<整数>{,<标识符>＝<整数>} | char<标识符>＝<字符>{,<标识符>＝<字符>}
void Parser::constantDefine(SymbolTable &table)
{
	functionIn("constantDefine");
	int type, value;
	int kind = CONSTANT;
	string name;
	if (laxer.sym == INT)
	{
		type = INT_TYPE;
		do
		{
			laxer.getsym();
			if (laxer.sym == IDENTIFIER)
			{
				name = laxer.getToken();
				test2(name, &table);
				laxer.getsym();
				if (laxer.sym == BECOMES)
				{
					laxer.getsym();
					value = integer();
					table.insertItem(name, laxer.linenum, kind, type, value);
				}
				else
				{
					errorGenerate(30);
				}
			}
			else
			{
				errorGenerate(20);
			}
		} while (laxer.sym == COMMA);
		parserTestPrint("int constant define");
	}
	else if (laxer.sym == CHAR)
	{
		type = CHAR_TYPE;
		do
		{
			laxer.getsym();
			if (laxer.sym == IDENTIFIER)
			{
				name = laxer.getToken();
				laxer.getsym();
				if (laxer.sym == BECOMES)
				{
					laxer.getsym();
					if (laxer.sym == CHARACTOR)
					{
						value = laxer.token[0];
						laxer.getsym();
						table.insertItem(name, laxer.linenum, kind, type, value);
					}
					else
					{
						errorGenerate(32);
					}
				}
				else
				{
					errorGenerate(30);
				}
			}
			else
			{
				errorGenerate(20);
			}
		} while (laxer.sym == COMMA);
		parserTestPrint("char constant define");
	}
	else
	{
		errorGenerate(28);
	}
}

// <整数> ::= ［+｜-］<无符号整数>｜０
int Parser::integer()
{
	functionIn("integer");
	int re;
	bool minus = false;
	if (laxer.sym == ZERO_NUMBER)
	{
		laxer.getsym();
		parserTestPrint("integer");
		return 0;
	}
	else if (laxer.sym == PLUS || laxer.sym == MINUS || laxer.sym == UNSIGNED_INGEGER)
	{
		if (laxer.sym == PLUS)
		{
			laxer.getsym();
		}
		else if (laxer.sym == MINUS)
		{
			laxer.getsym();
			minus = true;
		}
		else
			;

		if (laxer.sym == UNSIGNED_INGEGER)
		{
			re = laxer.num;
			if (minus)
				re = -re;
			laxer.getsym();
			parserTestPrint("integer");

			return re;
		}
		else
		{
			errorGenerate(22);
		}
	}
	else
	{
		errorGenerate(34);
	}
	return 0;
}

// <语句>    ::= <条件语句>｜<do循环语句> | <for循环语句>｜‘{’<语句列>‘}’｜<函数调用语句>;｜<赋值语句>;｜<读语句>;｜<写语句>;｜<空>;｜<返回语句>;
void Parser::statement()
{
	functionIn("statement");
	if (laxer.sym == IF)
	{
		branchStatement();
	}
	else if (laxer.sym == DO)
	{
		doCycleStatement();
	}
	else if (laxer.sym == FOR)
	{
		forCycleStatement();
	}
	else if (laxer.sym == LCURLY)
	{
		laxer.getsym();
		statementList();
		if (laxer.sym == RCURLY)
		{
			laxer.getsym();
		}
		else
		{
			errorGenerate(18);
		}
	}
	else if (laxer.sym == SCANF)
	{
		read();
		if (laxer.sym == SEMICOLON)
		{
			laxer.getsym();
		}
		else
		{
			errorGenerate(26);
		}
	}
	else if (laxer.sym == PRINTF)
	{
		write();
		if (laxer.sym == SEMICOLON)
		{
			laxer.getsym();
		}
		else
		{
			errorGenerate(26);
		}
	}
	else if (laxer.sym == SEMICOLON)
	{
		laxer.getsym();
	}
	else if (laxer.sym == RETURN)
	{
		returnStatement();
		if (laxer.sym == SEMICOLON)
		{
			laxer.getsym();
		}
		else
		{
			errorGenerate(26);
		}
	}
	else if (laxer.sym == IDENTIFIER)
	{
		string ident = laxer.getToken();
		laxer.getsym();
		if (laxer.sym == BECOMES || laxer.sym == LSQUARE)
		{
			assignStatement(ident);
			if (laxer.sym == SEMICOLON)
			{
				laxer.getsym();
			}
			else
			{
				errorGenerate(26);
			}
		}
		else if (laxer.sym == LPARENT)
		{
			callFunction(ident);
			if (laxer.sym == SEMICOLON)
			{
				laxer.getsym();
			}
			else
			{
				errorGenerate(26);
			}
		}
		else
		{
			errorGenerate(38);
		}
	}
	else
	{
		errorGenerate(36);
	}
	parserTestPrint("statement");
}

// <条件>    ::=  <表达式><关系运算符><表达式>
void Parser::condition(struct symbolItem *&cmp1, struct symbolItem* &cmp2, int &cmpOp)
{
	functionIn("condition");

	cmp1 = expression();
	if (laxer.sym == LSS || laxer.sym == LEQ || laxer.sym == GTR || laxer.sym == GEQ || laxer.sym == NEQ || laxer.sym == EQL)
	{
		cmpOp = laxer.sym;
		laxer.getsym();
		cmp2 = expression();
	}
	else if (laxer.sym == RPARENT)
	{
		cmpOp = NULL;
		cmp2 = NULL;
	}
	else
	{
		errorGenerate(68);
	}
	parserTestPrint("condition");
}

// if '(' <条件> ')' <语句> [else <语句>]
void Parser::branchStatement()
{
	static int countif = -1;
	countif++;
	int count = countif;
	struct symbolItem *cmpl, *cmpr;
	int cmpOp;
	functionIn("branchStatement");
	if (laxer.sym == IF)
	{
		laxer.getsym();
		if (laxer.sym == LPARENT)
		{
			laxer.getsym();
			condition(cmpl, cmpr, cmpOp);
			if (laxer.sym == RPARENT)
			{
				switch (cmpOp)
				{
				case NULL: middleCode.gen(Opcode::BEZ, "elsebegin" + to_string(count), cmpl); break;	// 所有取反
				case LSS: middleCode.gen(Opcode::BGE, "elsebegin" + to_string(count), cmpl, cmpr); break;
				case LEQ: middleCode.gen(Opcode::BGT, "elsebegin" + to_string(count), cmpl, cmpr); break;
				case GTR: middleCode.gen(Opcode::BLE, "elsebegin" + to_string(count), cmpl, cmpr); break;
				case GEQ: middleCode.gen(Opcode::BLT, "elsebegin" + to_string(count), cmpl, cmpr); break;
				case NEQ: middleCode.gen(Opcode::BEQ, "elsebegin" + to_string(count), cmpl, cmpr); break;
				case EQL: middleCode.gen(Opcode::BNE, "elsebegin" + to_string(count), cmpl, cmpr); break;
				default:	errorGenerate(42); // error
					break;
				}
				laxer.getsym();
				statement();
				middleCode.gen(Opcode::JUMP, "ifend" + to_string(count));
				middleCode.gen(Opcode::SET, "elsebegin" + to_string(count));
				if (laxer.sym == ELSE)
				{
					laxer.getsym();
					statement();
				}
				middleCode.gen(Opcode::SET, "ifend" + to_string(count));
			}
			else
			{
				errorGenerate(14);
			}
		}
		else
		{
			errorGenerate(12);
		}
		parserTestPrint("branch statement");
	}
	else
	{
		errorGenerate(40);
	}
}

// do <语句> while '(' <条件> ')'
void Parser::doCycleStatement()
{
	static int countdo = -1;
	countdo++;
	int count = countdo;
	struct symbolItem *cmpl, *cmpr;
	int cmpOp;
	functionIn("doCycleStatement");
	if (laxer.sym == DO)
	{
		laxer.getsym();
		middleCode.gen(Opcode::SET, "dobegin" + to_string(count));
		statement();
		if (laxer.sym == WHILE)
		{
			laxer.getsym();
			if (laxer.sym == LPARENT)
			{
				laxer.getsym();
				condition(cmpl, cmpr, cmpOp);
				// LSS || LEQ || GTR || GEQ || NEQ || EQL
				switch (cmpOp)
				{
				case NULL: middleCode.gen(Opcode::BNZ, "dobegin" + to_string(count), cmpl); break;
				case LSS: middleCode.gen(Opcode::BLT, "dobegin" + to_string(count), cmpl, cmpr); break;
				case LEQ: middleCode.gen(Opcode::BLE, "dobegin" + to_string(count), cmpl, cmpr); break;
				case GTR: middleCode.gen(Opcode::BGT, "dobegin" + to_string(count), cmpl, cmpr); break;
				case GEQ: middleCode.gen(Opcode::BGE, "dobegin" + to_string(count), cmpl, cmpr); break;
				case NEQ: middleCode.gen(Opcode::BNE, "dobegin" + to_string(count), cmpl, cmpr); break;
				case EQL: middleCode.gen(Opcode::BEQ, "dobegin" + to_string(count), cmpl, cmpr); break;
				default: errorGenerate(42);	// error
					break;
				}
				if (laxer.sym == RPARENT)
				{
					laxer.getsym();
				}
				else
				{
					errorGenerate(14);
				}
			}
			else
			{
				errorGenerate(12);
			}
		}
		else
		{
			errorGenerate(46);
		}
		parserTestPrint("do cycle statement");
	}
	else
	{
		errorGenerate(44);
	}
	count++;
}

// for '(' <标识符>=<表达式>; <条件>; <标识符>=<标识符>(+|-)<无符号整数> ')' <语句>
void Parser::forCycleStatement()
{
	static int countfor = -1;
	countfor++;
	int count = countfor;
	struct symbolItem* ident1, *cmpl, *cmpr, *ident2, *ident3, *usdint;
	int cmpOp, uint;
	functionIn("forCycleStatement");
	if (laxer.sym == FOR)
	{
		laxer.getsym();
		if (laxer.sym == LPARENT)
		{
			laxer.getsym();
			if (laxer.sym == IDENTIFIER)
			{
				ident1 = test(laxer.getToken());
				laxer.getsym();
				if (laxer.sym == BECOMES)
				{
					laxer.getsym();
					struct symbolItem* init = expression();
					middleCode.gen(Opcode::ASS, ident1, init);
					if (laxer.sym == SEMICOLON)
					{
						laxer.getsym();
						middleCode.gen(Opcode::SET, "forcmp" + to_string(count));
						condition(cmpl, cmpr, cmpOp);
						// LSS || LEQ || GTR || GEQ || NEQ || EQL
						switch (cmpOp)
						{
						case NULL: middleCode.gen(Opcode::BEZ, "forend" + to_string(count), cmpl); break;
						case LSS: middleCode.gen(Opcode::BGE, "forend" + to_string(count), cmpl, cmpr); break;
						case LEQ: middleCode.gen(Opcode::BGT, "forend" + to_string(count), cmpl, cmpr); break;
						case GTR: middleCode.gen(Opcode::BLE, "forend" + to_string(count), cmpl, cmpr); break;
						case GEQ: middleCode.gen(Opcode::BLT, "forend" + to_string(count), cmpl, cmpr); break;
						case NEQ: middleCode.gen(Opcode::BEQ, "forend" + to_string(count), cmpl, cmpr); break;
						case EQL: middleCode.gen(Opcode::BNE, "forend" + to_string(count), cmpl, cmpr); break;
						default: errorGenerate(42);	// error
							break;
						}
						if (laxer.sym == SEMICOLON)
						{
							laxer.getsym();
							if (laxer.sym == IDENTIFIER)
							{
								ident2 = test(laxer.getToken());
								laxer.getsym();
								if (laxer.sym == BECOMES)
								{
									laxer.getsym();
									if (laxer.sym == IDENTIFIER)
									{
										ident3 = test(laxer.getToken());
										laxer.getsym();
										if (laxer.sym == PLUS || laxer.sym == MINUS)
										{
											bool plus;
											if (laxer.sym == PLUS)
												plus = true;
											else
												plus = false;
											laxer.getsym();
											if (laxer.sym == UNSIGNED_INGEGER)
											{
												uint = laxer.num;
												usdint = localTable.generateTempConstant(uint, INT_TYPE);
												laxer.getsym();
												if (laxer.sym == RPARENT)
												{
													laxer.getsym();
													statement();
													if (plus)
														middleCode.gen(Opcode::ADD, ident2, ident3, usdint);
													else
														middleCode.gen(Opcode::SUB, ident2, ident3, usdint);
													middleCode.gen(Opcode::JUMP, "forcmp" + to_string(count));
													middleCode.gen(Opcode::SET, "forend" + to_string(count));
												}
												else
												{
													errorGenerate(14);
												}
											}
											else
											{
												errorGenerate(22);
											}
										}
										else
										{
											errorGenerate(50);
										}
									}
									else
									{
										errorGenerate(20);
									}
								}
								else
								{
									errorGenerate(30);
								}
							}
							else
							{
								errorGenerate(20);
							}
						}
						else
						{
							errorGenerate(26);
						}
					}
					else
					{
						errorGenerate(26);
					}
				}
				else
				{
					errorGenerate(30);
				}
			}
			else
			{
				errorGenerate(20);
			}
		}
		else
		{
			errorGenerate(12);
		}
		parserTestPrint("for cycle statement");
	}
	else
	{
		errorGenerate(48);
	}
	count++;
}

void Parser::assignStatement(string ident)
{
	functionIn("assignStatement");
	struct symbolItem* des = test(ident);
	if (des->kind != VARIABLE && des->kind != PARAMETER)
		errorGenerate(112, ident);
	if (laxer.sym == BECOMES)
	{
		laxer.getsym();
		struct symbolItem* src = expression();
		middleCode.gen(Opcode::ASS, des, src);
	}
	else if (laxer.sym == LSQUARE)	// 数组元素
	{
		laxer.getsym();
		struct symbolItem* index = expression();
		if (index->kind == CONSTANT)	// 如果下标是常数, 进行越界检查
		{
			if (index->valueoroffset < 0 || index->valueoroffset >= des->length)
			{
				errorGenerate(118, to_string(index->valueoroffset));
			}
		}
		if (laxer.sym == RSQUARE)
		{
			laxer.getsym();
			if (laxer.sym == BECOMES)
			{
				laxer.getsym();
				struct symbolItem* src = expression();
				middleCode.gen(Opcode::SAV, src, des, index);
			}
			else
			{
				errorGenerate(30);
			}
		}
		else
		{
			errorGenerate(24);
		}
	}
	else
	{
		errorGenerate(52);
	}
	parserTestPrint("assign statement");
}

// <函数调用> ::= <标识符> '(' <值参数> ')'
struct symbolItem* Parser::callFunction(string ident)
{
	functionIn("callFunction");
	struct symbolItem* func = test(ident);
	if (func == NULL)
		errorGenerate(116, ident);
	struct symbolItem* re = NULL;
	if (laxer.sym == LPARENT)
	{
		laxer.getsym();
#ifdef OPTIMIZE
		middleCode.gen(Opcode::CALL, func->name);	// 先调用函数, 后填参数. 优化后顺序颠倒
#endif // OPTIMIZE

		valueParameterTable(func);
		if (laxer.sym == RPARENT)
		{
			laxer.getsym();
#ifndef OPTIMIZE
			middleCode.gen(Opcode::CALL, func->name);	// 先调用函数, 后填参数. 优化后顺序颠倒
#endif // !OPTIMIZE
			if (func->type != VOID_TYPE)
			{
				if (func->type == INT_TYPE)
					re = localTable.generateTemp();
				else
					re = localTable.generateTempChar();
				middleCode.gen(Opcode::PUT, re);
			}
		}
		else
		{
			errorGenerate(14);
		}
	}
	else
	{
		errorGenerate(12);
	}
	parserTestPrint("function call");
	return re;
}

// <值参数表> := <表达式> {,<表达式>} | 空
void Parser::valueParameterTable(struct symbolItem* func)
{
	functionIn("valueParameterTable");
	if (laxer.sym == RPARENT)
	{
		if (func->length > 0)
		{
			errorGenerate(106, to_string(func->length));
		}
	}
	else
	{
		int count = 0;
		int base = globalTable.getPosition(func);
		struct symbolItem* re = expression();
		if (func->length == 0)
			errorGenerate(104, to_string(func->length));
		else
		{
			struct symbolItem* index = globalTable.symbolList[base + (++count)];
			middleCode.gen(Opcode::PUSH, re, index);
			while (laxer.sym == COMMA)
			{
				if (count > func->length)
				{
					errorGenerate(104, to_string(func->length));	//error
				}
				laxer.getsym();
				re = expression();
				index = globalTable.symbolList[base + (++count)];
				middleCode.gen(Opcode::PUSH, re, index);
			}
			if (count < func->length)
			{
				errorGenerate(106, to_string(func->length));
			}
		}
	}
	parserTestPrint("value parameter table");
}

// <语句列>   ::=｛<语句>｝
void Parser::statementList()
{
	functionIn("statementList");
	while (laxer.sym == IF || laxer.sym == DO || laxer.sym == FOR || laxer.sym == LCURLY || laxer.sym == SCANF || laxer.sym == PRINTF || laxer.sym == SEMICOLON || laxer.sym == IDENTIFIER || laxer.sym == RETURN)
	{
		statement();
	}
	parserTestPrint("statement list");
}

// <读语句>    ::=  scanf ‘(’<标识符>{,<标识符>}‘)’
void Parser::read()
{
	functionIn("read");
	if (laxer.sym == SCANF)
	{
		laxer.getsym();
		if (laxer.sym == LPARENT)
		{
			laxer.getsym();
			if (laxer.sym == IDENTIFIER)
			{
				string ident = laxer.getToken();
				struct symbolItem* re = test(ident);
                if (!(re->kind == VARIABLE || re->kind == PARAMETER))
                {
                    errorGenerate(67);
                }
				middleCode.gen(Opcode::READ, re);
				laxer.getsym();
				while (laxer.sym == COMMA)
				{
					laxer.getsym();
					if (laxer.sym == IDENTIFIER)
					{
						string ident = laxer.getToken();
						struct symbolItem* re = test(ident);
                        if (!(re->kind == VARIABLE || re->kind == PARAMETER))
                        {
                            errorGenerate(67);
                        }
						middleCode.gen(Opcode::READ, re);
						laxer.getsym();
					}
					else
					{
						errorGenerate(20);
					}
				}
				if (laxer.sym == RPARENT)
				{
					laxer.getsym();
				}
				else
				{
					errorGenerate(14);
				}
			}
			else
			{
				errorGenerate(20);
			}
			parserTestPrint("read statement");
		}
		else
		{
			errorGenerate(12);
		}
	}
	else
	{
		errorGenerate(54);
	}
}

// <写语句>    ::=  printf‘(’<字符串>,<表达式>‘)’|printf ‘(’<字符串>‘)’|printf ‘(’<表达式>‘)’
void Parser::write()
{
	functionIn("write");
	if (laxer.sym == PRINTF)
	{
		laxer.getsym();
		if (laxer.sym == LPARENT)
		{
			laxer.getsym();
			if (laxer.sym == STRING)
			{
				int index = addDataSeg(laxer.getToken());
				struct symbolItem* str_ = localTable.insertItem("yangsen_string" + to_string(index), laxer.linenum, CONSTANT, STRING_TYPE);
				middleCode.gen(Opcode::WRITE, str_);
				laxer.getsym();
				if (laxer.sym == COMMA)
				{
					laxer.getsym();
					middleCode.gen(Opcode::WRITE, expression());
				}
				if (laxer.sym == RPARENT)
				{
					laxer.getsym();
				}
				else
				{
					errorGenerate(14);
				}
			}
			else
			{
				middleCode.gen(Opcode::WRITE, expression());
				if (laxer.sym == RPARENT)
				{
					laxer.getsym();
				}
				else
				{
					errorGenerate(14);
				}
			}
		}
		else
		{
			errorGenerate(14);
		}
		parserTestPrint("write statement");
	}
	else
	{
		errorGenerate(56);
	}
}

// <返回语句>   ::=  return[‘(’<表达式>‘)’]
void Parser::returnStatement()
{
	functionIn("return");
	if (laxer.sym == RETURN)
	{
		laxer.getsym();
		if (laxer.sym == LPARENT)
		{
			if (!returnFlag)
				errorGenerate(63);
			laxer.getsym();
			struct symbolItem* returnValue = expression();
			if (laxer.sym == RPARENT)
			{
				laxer.getsym();
				middleCode.gen(Opcode::RET, returnValue);
			}
			else
			{
				errorGenerate(14);
			}
		}
		else
		{
			if (returnFlag)
				errorGenerate(65);
			middleCode.gen(Opcode::RET);
		}
		parserTestPrint("return statement");
	}
	else
	{
		errorGenerate(58);
	}
}

// <表达式>    ::= ［＋｜－］<项>{<加法运算符><项>}
struct symbolItem* Parser::expression()
{
	functionIn("expression");
	struct symbolItem* re;
	bool minus = false;
	if (laxer.sym == PLUS || laxer.sym == MINUS)
	{
		if (laxer.sym == MINUS)
			minus = true;
		laxer.getsym();
	}
	struct symbolItem* item1 = item();
	if (minus)
	{
		re = localTable.generateTemp();
		middleCode.gen(Opcode::NEG, re, item1);
		item1 = re;
	}
	else
		re = item1;
	while (laxer.sym == PLUS || laxer.sym == MINUS)
	{
		bool add;
		if (laxer.sym == PLUS)
			add = true;
		else
			add = false;
		laxer.getsym();
		struct symbolItem* item2 = item();
		re = localTable.generateTemp();
		if (add)
			middleCode.gen(Opcode::ADD, re, item1, item2);
		else
			middleCode.gen(Opcode::SUB, re, item1, item2);
		item1 = re;
	}
	parserTestPrint("expression");
	return re;
}

// <因子>    ::= <标识符>｜<标识符>‘[’<表达式>‘]’｜<整数>|<字符>｜<有返回值函数调用语句>|‘(’<表达式>‘)’
struct symbolItem* Parser::factor()
{
	functionIn("factor");
	struct symbolItem* f;
	if (laxer.sym == IDENTIFIER)
	{
		string ident = laxer.getToken();
		f = test(ident);
		laxer.getsym();
		if (f->length > 0 && f->kind == VARIABLE)	// 数组
		{
			if (laxer.sym == LSQUARE)
			{
				laxer.getsym();
				struct symbolItem* item1 = expression();
				if (item1 == NULL)
                    item1 = localTable.generateTemp();
				if (laxer.sym == RSQUARE)
				{
					laxer.getsym();
					struct symbolItem* re = localTable.generateTemp();
					if (item1->kind == CONSTANT)	// 如果下标是常数, 进行越界检查
					{
						if (item1->valueoroffset < 0 || item1->valueoroffset >= f->length)
						{
							errorGenerate(118, to_string(item1->valueoroffset));
						}
					}
					middleCode.gen(Opcode::LAV, re, f, item1);
					return re;
				}
				else
				{
					errorGenerate(24);
				}
			}
			else
			{
				errorGenerate(62);
			}
		}
		else if (f->kind == FUNCTION) // 函数
		{
			if (laxer.sym == LPARENT)
			{
				if (f->type == CHAR_TYPE || f->type == INT_TYPE)
				{
					return callFunction(ident);
				}
				else
				{
					errorGenerate(108, f->name);
					callFunction(ident);
					return localTable.generateTempConstant(108, INT_TYPE);
				}
			}
			else
			{
				errorGenerate(12);
			}
		}
		else // 普通变量 或 参数
		{
			return f;
		}
	}
	else if (laxer.sym == CHARACTOR)
	{
		int value = laxer.token[0];
		laxer.getsym();
		return localTable.generateTempConstant(value, CHAR_TYPE);
	}
	else if (laxer.sym == LPARENT)
	{
		laxer.getsym();
		struct symbolItem* re = expression();
		if (laxer.sym == RPARENT)
		{
			laxer.getsym();
			return re;
		}
		return NULL;
	}
	else if (laxer.sym == PLUS || laxer.sym == MINUS || laxer.sym == UNSIGNED_INGEGER || laxer.sym == ZERO_NUMBER)
	{
		int value = integer();
		return localTable.generateTempConstant(value, INT_TYPE);
	}
	else
	{
		errorGenerate(60);
		return NULL;
	}
	parserTestPrint("factor");
	return NULL;
}

// <项>     ::= <因子>{<乘法运算符><因子>}
struct symbolItem* Parser::item()
{
	functionIn("item");
	struct symbolItem* re;
	struct symbolItem* item1 = factor();
	while (laxer.sym == MULIT || laxer.sym == DIVI)
	{
		bool mul;
		if (laxer.sym == MULIT)
			mul = true;
		else
			mul = false;
		laxer.getsym();
		struct symbolItem* item2 = factor();
		re = localTable.generateTemp();
		if (mul)
			middleCode.gen(Opcode::MUL, re, item1, item2);
		else
		{
			if (item2->kind == CONSTANT && item2->valueoroffset == 0)
				errorGenerate(61);
			middleCode.gen(Opcode::DIV, re, item1, item2);
		}
		item1 = re;
	}
	re = item1;
	parserTestPrint("item");
	return re;
}

// 将字符串常量存入数组
int Parser::addDataSeg(string _stringconst)
{
	int length = data_const_string.size();
	data_const_string.push_back(_stringconst);
	return length;
}

// 将全局变量声明存入数组
void Parser::addDataGlobal(string _str)
{
	data_global_v.push_back(_str);
}


