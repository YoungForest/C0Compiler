#include "Parser.h"
#include "Error.h"
#include "SymbolTable.h"
#include <ctype.h>
#include <string>
#include <iostream>

using namespace std;

Parser::~Parser()
{
    //dtor
}

void Parser::parserTestPrint(string s)
{
    cout << "Line : " << laxer.linenum << " column : " << laxer.cc << ".   This is a " << s << " ! " << endl;
}

// 调试
void Parser::functionIn(string s)
{
    // cout << "Function in " << s << endl;
}

struct symbolItem* Parser::test(SymbolTable *st, std::string ident)
{
    struct symbolItem* re = st->searchItem(ident);
    if (re == NULL)
        error_handler.errorMessage(2, laxer.linenum, laxer.cc);
    return re;
}

void Parser::enterTable(SymbolTable *table, string name, int kind, int type, int valueoroffset = 0, int length = 0)
{
    table->insertItem(name, laxer.linenum, kind, type, valueoroffset, length);
}

void Parser::parser()
{
    laxer.getsym();
    program();
}

void Parser::program()
{
    functionIn("program");
    if (laxer.sym == CONST)
        constantDenote(&globalTable);
    while (laxer.sym == INT || laxer.sym == CHAR)
    {
        int type = laxer.sym;
        laxer.getsym();
        if(laxer.sym == IDENTIFIER)
        {
            string ident = laxer.getToken();
            laxer.getsym();
            if (laxer.sym == SEMICOLON || laxer.sym == COMMA || laxer.sym == LSQUARE)
            {
                varietyDenote(&globalTable, type, ident);
            }
            else if (laxer.sym == LPARENT)
            {
                defineReturnFunction(type, ident);
                break;
            }
            else
            {

            }
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
                int type = laxer.sym;
                laxer.getsym();
                if (laxer.sym == IDENTIFIER)
                {
                    string ident = laxer.getToken();
                    laxer.getsym();
                    defineReturnFunction(type, ident);
                }
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
        }
    }
}

void Parser::defineVoidFunction()
{
    functionIn("defineVoidFunction");
    if (laxer.sym == IDENTIFIER)
    {
        laxer.getsym();
        if (laxer.sym == LPARENT)
        {
            laxer.getsym();
            parameterTable();
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
                        parserTestPrint("void function define");
                    }
                }
            }
        }
    }
}

void Parser::defineReturnFunction(int type, string ident)
{
    functionIn("defineReturnFunction");
    if (laxer.sym == LPARENT)
    {
        laxer.getsym();
        parameterTable();
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
            }
        }
    }
}

void Parser::compoundStatement()
{
    functionIn("compoundStatement");
    if (laxer.sym == CONST)
    {
        constantDenote(&localTable);
    }
    if (laxer.sym == INT || laxer.sym == CHAR)
    {
        varietyDenote(&localTable);
    }
    statementList();
    parserTestPrint("compound statement");
}

void Parser::varietyDenote(SymbolTable *table)
{
    functionIn("varietyDenote");
    while (laxer.sym == INT || laxer.sym == CHAR)
    {
        do
        {
            laxer.getsym();
            if (laxer.sym == IDENTIFIER)
            {
                laxer.getsym();
                if (laxer.sym == LSQUARE)
                {
                    laxer.getsym();
                    expression();
                    if (laxer.sym == RSQUARE)
                    {
                        laxer.getsym();
                    }
                }
            }
        }
        while (laxer.sym == COMMA);
        if (laxer.sym == SEMICOLON)
        {
            laxer.getsym();
            parserTestPrint("variety define");
        }
    }
    parserTestPrint("variety denote");
}

void Parser::varietyDenote(SymbolTable *table, int type, string ident)
{
    functionIn("varietyDenote");
    if (laxer.sym == LSQUARE)
    {
        laxer.getsym();
        expression();
        if (laxer.sym == RSQUARE)
        {
            laxer.getsym();
        }
    }
    while (laxer.sym == COMMA)
    {
        laxer.getsym();
        if (laxer.sym == IDENTIFIER)
        {
            laxer.getsym();
            if (laxer.sym == LSQUARE)
            {
                laxer.getsym();
                expression();
                if (laxer.sym == RSQUARE)
                {
                    laxer.getsym();
                }
            }
        }
    }
    if (laxer.sym == SEMICOLON)
    {
        laxer.getsym();
        parserTestPrint("global variety define");
    }
}

void Parser::parameterTable()
{
    functionIn("parameterTable");
    if (laxer.sym == INT || laxer.sym == CHAR)
    {
        laxer.getsym();
        if (laxer.sym == IDENTIFIER)
        {
            laxer.getsym();
        }
        while (laxer.sym == COMMA)
        {
            laxer.getsym();
            if (laxer.sym == INT || laxer.sym == CHAR)
            {
                laxer.getsym();
                if (laxer.sym == IDENTIFIER)
                {
                    laxer.getsym();
                }
            }
        }
    }
    parserTestPrint("parameter table");
}

void Parser::mainFunction()
{
    functionIn("mainFunction");
    if (laxer.sym == MAIN)
    {
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
                }
            }
        }
    }
}
void Parser::constantDenote(SymbolTable *table)
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
        }
        while (laxer.sym == CONST);
        parserTestPrint("constant denote");
    }
}

void Parser::constantDefine(SymbolTable *table)
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
                laxer.getsym();
                if (laxer.sym == BECOMES)
                {
                    laxer.getsym();
                    value = integer();
                    enterTable(table, name, kind, type, value);
                }
            }
        }
        while (laxer.sym == COMMA);
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
                laxer.getsym();
                if (laxer.sym == BECOMES)
                {
                    laxer.getsym();
                    if (laxer.sym == CHARACTOR)
                    {
						value = laxer.token[0];
                        laxer.getsym();
                        enterTable(table, name, kind, type, value);
                    }
                }
            }
        }
        while (laxer.sym == COMMA);
        parserTestPrint("char constant define");
    }
}

int Parser::integer()
{
    functionIn("integer");
    if (laxer.sym == PLUS)
    {
        laxer.getsym();
    }
    else if (laxer.sym == MINUS)
    {
        laxer.getsym();
    }
    else
        ;
    if(laxer.sym == ZERO_NUMBER)
    {
        laxer.getsym();
        parserTestPrint("integer");
        return 0;
    }
    else if (laxer.sym == UNSIGNED_INGEGER)
    {
        laxer.getsym();
        parserTestPrint("integer");
        return laxer.num;
    }
    else
        ;
}

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
    }
    else if (laxer.sym == SCANF)
    {
        read();
        if (laxer.sym == SEMICOLON)
        {
            laxer.getsym();
        }
    }
    else if (laxer.sym == PRINTF)
    {
        write();
        if (laxer.sym == SEMICOLON)
        {
            laxer.getsym();
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
    }
    else if (laxer.sym == IDENTIFIER)
    {
        laxer.getsym();
        string ident = laxer.getToken();
        if (laxer.sym == BECOMES || laxer.sym == LSQUARE)
        {
            assignStatement(ident);
            if (laxer.sym == SEMICOLON)
            {
                laxer.getsym();
            }
        }
        else if (laxer.sym == LPARENT)
        {
            callFunction(ident);
            if (laxer.sym == SEMICOLON)
            {
                laxer.getsym();
            }
        }
        else
        {

        }
    }
    else
    {

    }
    parserTestPrint("statement");
}

void Parser::condition()
{
    functionIn("condition");
    expression();
    if (laxer.sym == LSS || laxer.sym == LEQ || laxer.sym == GTR ||laxer.sym == GEQ || laxer.sym == NEQ || laxer.sym == EQL)
    {
        laxer.getsym();
        expression();
    }
    parserTestPrint("condition");
}

void Parser::branchStatement()
{
    functionIn("branchStatement");
    if (laxer.sym == IF)
    {
        laxer.getsym();
        if (laxer.sym == LPARENT)
        {
            laxer.getsym();
            condition();
            if (laxer.sym == RPARENT)
            {
                laxer.getsym();
                statement();
                if (laxer.sym == ELSE)
                {
                    laxer.getsym();
                    statement();
                }
            }
        }
        parserTestPrint("branch statement");
    }
}

void Parser::doCycleStatement()
{
    functionIn("doCycleStatement");
    if (laxer.sym == DO)
    {
        laxer.getsym();
        statement();
        if (laxer.sym == WHILE)
        {
            laxer.getsym();
            if (laxer.sym == LPARENT)
            {
                laxer.getsym();
                condition();
                if (laxer.sym == RPARENT)
                {
                    laxer.getsym();
                }
            }
        }
        parserTestPrint("do cycle statement");
    }
}

void Parser::forCycleStatement()
{
    functionIn("forCycleStatement");
    if (laxer.sym == FOR)
    {
        laxer.getsym();
        if (laxer.sym == LPARENT)
        {
            laxer.getsym();
            if (laxer.sym == IDENTIFIER)
            {
                laxer.getsym();
                if (laxer.sym == BECOMES)
                {
                    laxer.getsym();
                    expression();
                    if (laxer.sym == SEMICOLON)
                    {
                        laxer.getsym();
                        condition();
                        if (laxer.sym == SEMICOLON)
                        {
                            laxer.getsym();
                            if (laxer.sym == IDENTIFIER)
                            {
                                laxer.getsym();
                                if (laxer.sym == BECOMES)
                                {
                                    laxer.getsym();
                                    if (laxer.sym == IDENTIFIER)
                                    {
                                        laxer.getsym();
                                        if (laxer.sym == PLUS || laxer.sym == MINUS)
                                        {
                                            laxer.getsym();
                                            if (laxer.sym == UNSIGNED_INGEGER)
                                            {
                                                laxer.getsym();
                                                if (laxer.sym == RPARENT)
                                                {
                                                    laxer.getsym();
                                                    statement();
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        parserTestPrint("for cycle statement");
    }
}

void Parser::assignStatement(string ident)
{
    functionIn("assignStatement");
    if (laxer.sym == BECOMES)
    {
        laxer.getsym();
        expression();
    }
    else if (laxer.sym == LSQUARE)
    {
        laxer.getsym();
        expression();
        if (laxer.sym == RSQUARE)
        {
            laxer.getsym();
            if (laxer.sym == BECOMES)
            {
                laxer.getsym();
                expression();
            }
        }
    }
    else
    {

    }
    parserTestPrint("assign statement");
}

struct symbolItem* Parser::callFunction(string ident)
{
	struct symbolItem* re = NULL;
    functionIn("callFunction");
    if (laxer.sym == LPARENT)
    {
        laxer.getsym();
        valueParameterTable();
        if (laxer.sym == RPARENT)
        {
            laxer.getsym();
        }
    }
    parserTestPrint("function call");
	return re;
}

void Parser::valueParameterTable()
{
    functionIn("valueParameterTable");
    if (laxer.sym == RPARENT)
    {

    }
    else
    {
        expression();
        while (laxer.sym == COMMA)
        {
            laxer.getsym();
            expression();
        }
    }
    parserTestPrint("value parameter table");
}

void Parser::statementList()
{
    functionIn("statementList");
    while (laxer.sym == IF || laxer.sym == DO || laxer.sym == FOR || laxer.sym == LCURLY || laxer.sym == SCANF || laxer.sym == PRINTF || laxer.sym == SEMICOLON || laxer.sym == IDENTIFIER || laxer.sym == RETURN)
    {
        statement();
    }
    parserTestPrint("statement list");
}

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
                do
                {
                    laxer.getsym();
                    if (laxer.sym == IDENTIFIER)
                    {
                        laxer.getsym();
                    }
                }
                while (laxer.sym == COMMA);
                if (laxer.sym == RPARENT)
                {
                    laxer.getsym();
                }
            }
            parserTestPrint("read statement");
        }
    }
}

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
				int index = middleCode.addDataSeg(laxer.getToken());
				struct symbolItem* str_ = localTable.insertItem("!string" + index, VARIABLE, STRING_TYPE);
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
            }
            else
            {
				middleCode.gen(Opcode::WRITE, expression());
                if (laxer.sym == RPARENT)
                {
                    laxer.getsym();
                }
            }
        }
        parserTestPrint("write statement");
    }
}

void Parser::returnStatement()
{
    functionIn("return");
    if (laxer.sym == RETURN)
    {
        laxer.getsym();
        if (laxer.sym == LPARENT)
        {
            laxer.getsym();
            struct symbolItem* returnValue = expression();
			if (laxer.sym == RPARENT)
			{
				laxer.getsym();
				middleCode.gen(Opcode::RET, returnValue);
			}
        }
		else
		{
			middleCode.gen(Opcode::RET);
		}
        parserTestPrint("return statement");
    }
}

struct symbolItem* Parser::expression()
{
    functionIn("expression");
    bool minus = false;
    if (laxer.sym == PLUS || laxer.sym == MINUS)
    {
        if (laxer.sym == MINUS)
            minus = true;
        laxer.getsym();
    }
    struct symbolItem* item1 = item();
    // cout << laxer.sym << endl;
    while (laxer.sym == PLUS || laxer.sym == MINUS)
    {
        bool add;
        if (laxer.sym == PLUS)
            add = true;
        else
            add = false;
        laxer.getsym();
        struct symbolItem* item2 = item();
        if (add)
            middleCode.gen(Opcode::ADD, item1, item1, item2);
        else
            middleCode.gen(Opcode::SUB, item1, item1, item2);
    }
    if (minus)
        middleCode.gen(Opcode::NEG, item1);
    parserTestPrint("expression");
    return item1;
}

struct symbolItem* Parser::factor()
{
    functionIn("factor");
    struct symbolItem* f;
    if (laxer.sym ==IDENTIFIER)
    {
        string ident = laxer.getToken();
        f = localTable.searchItem(ident);

        laxer.getsym();
        if (laxer.sym == LSQUARE && f->length > 0)
        {
            laxer.getsym();
            struct symbolItem* item1 = expression();
            if (laxer.sym == RSQUARE)
            {
                laxer.getsym();
				struct symbolItem* re = localTable.generateTemp();
				middleCode.gen(Opcode::LAV, re, f, item1);
				return re;
            }
        }
        else if (laxer.sym == LPARENT && f->kind == FUNCTION && (f->type == CHAR_TYPE || f->type == INT_TYPE))
        {
            return callFunction(ident);
        }
        else
        {
        }
    }
    else if (laxer.sym == CHARACTOR)
    {
		int value = laxer.token[0];
        laxer.getsym();
		return localTable.generateTempConstant(value);;
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
    }
    else if (laxer.sym == PLUS || laxer.sym ==	MINUS || laxer.sym == UNSIGNED_INGEGER || laxer.sym == ZERO_NUMBER)
    {
        int value = integer();
		return localTable.generateTempConstant(value);
    }
    else
    {
		return NULL;
    }
    parserTestPrint("factor");
}

struct symbolItem* Parser::item()
{
    functionIn("item");
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
        if (mul)
            middleCode.gen(Opcode::MUL, item1, item1, item2);
        else
            middleCode.gen(Opcode::DIV, item1, item1, item2);
    }
    parserTestPrint("item");
    return item1;
}
