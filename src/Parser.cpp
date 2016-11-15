#include "Parser.h"
#include "Error.h"
#include "SymbolTable.h"
#include <ctype.h>

Parser::Parser()
{
    //ctor
}

Parser::~Parser()
{
    //dtor
}

void Parser::parserTestPrint(string s)
{
    std::cout << "This is a " << s << " ! " endl;
}

void Parser::program()
{
    if (laxer.sym == CONST)
        constantDenote(globalTable);
    if (laxer.sym == INT || laxer.sym == CHAR)
    {
        int type = laxer.sys;
        laxer.getsym();
        if(laxer.sym == IDENTIFIER)
        {
            string iden = laxer.getToken();
            laxer.getsym();
            if (laxer.sym == BECOMES)
            {
                laxer.getsym();
                varietyDenote2(globalTable, type, ident);
            }
            else if (laxer.sym == LPARENT)
            {
                laxer.getsym();
                defineReturn(type, indent);
            }
        }
    }
        
    if (laxer.sym == VOID)
        defineVoidFunction();
}

void Parser::constantDenote(SymbolTable *table)
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
}

void Parser::constantDefine(SymbolTable *table)
{
    if (laxer.sym == INT)
    {
        do
        {
            laxer.getsym();
            if (laxer.sym == IDENTIFIER)
            {
                laxer.getsym();
                if (laxer.sym == BECOMES)
                {
                    laxer.getsym();
                    integer();
                }
            }
        }
        while (laxer.sym == COMMA);
    }
    else if (laxer.sym == CHAR)
    {
        do
        {
            laxer.getsym();
            if (laxer.sym == IDENTIFIER)
            {
                laxer.getsym();
                if (laxer.sym == BECOMES)
                {
                    laxer.getsym();
                    charactor();
                }
            }
        }
        while (laxer.sym == COMMA);
    }
}

void Parser::integer()
{
    if (laxer.sym == PLUS)
    {
        laxer.getsym();
        if(laxer.sym == ZERO_NUMBER)
        {
            laxer.getsym();
        }
        else if (laxer.sym == NOT_ZERO_NUMBER)
        {
            unsignedInteger();
        }
        else
            ;
    }
    else if (laxer.sym == SUB)
    {
        laxer.getsym();
        if(laxer.sym == ZERO_NUMBER)
        {
            laxer.getsym();
        }
        else if (laxer.sym == NOT_ZERO_NUMBER)
        {
            unsignedInteger();
        }
        else
            ;
    }
    else if

} 