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
    while (laxer.sym == INT || laxer.sym == CHAR)
    {
        int type = laxer.sys;
        laxer.getsym();
        if(laxer.sym == IDENTIFIER)
        {
            string iden = laxer.getToken();
            laxer.getsym();
            if (laxer.sym == SEMICOLON || laxer.sym == COMMA || laxer.sym == LSQUARE)
            {
                varietyDenote(globalTable, type, ident);
            }
            else if (laxer.sym == LPARENT)
            {
                defineReturnFunction(type, indent);
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
            defineReturnFunction();
        }
    }
}

void Parser::defineVoidFunction()
{
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
                    parserTestPrint("return function define")
                }
            }
        }
    }
}

void Parser::compoundStatement()
{
    if (laxer.sym == CONST)
    {
        constantDenote(localTable);
    }
    if (laxer.sym == INT || laxer.sym == CHAR)
    {
        varietyDenote(localTable);
    }
    statementList();
    parserTestPrint("compound statement");
}

void Parser::varietyDenote(SymbolTable *table)
{
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
        parserTestPrint("int constant define");
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
                    if (laxer.sym == CHARACTOR)
                    {
                        laxer.getsym();
                    }
                }
            }
        }
        while (laxer.sym == COMMA);
        parserTestPrint("char constant define");
    }
}

void Parser::integer()
{
    if (laxer.sym == PLUS)
    {
        laxer.getsym();
    }
    else if (laxer.sym == SUB)
    {
        laxer.getsym();
    }
    else
        ; 
    if(laxer.sym == ZERO_NUMBER)
    {
        laxer.getsym();
        parserTestPrint("integer");
    }
    else if (laxer.sym == UNSIGNED_INGEGER)
    {
        laxer.getsym();
        parserTestPrint("integer");
    }
    else
        ;
} 

void Parser::statement()
{
    if (laxer.sym == IF)
    {
        branchStatement();
    }
    else if (laxer.sym == DO)
    {
        doCycleStatement();
        if (laxer.sym == SEMICOLON)
        {
            laxer.getsym();
        }
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
        ident = laxer.getToken();
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
    if (laxer.sym = FOR)
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
                                        if (laxer.sym == PLUS || laxer.sym == SUB)
                                        {
                                            laxer.getsym();
                                            step();
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
        parserTestPrint("for cycle statement");
    }
}

void Parser::assignStatement()
{
    if (laxer.sym == IDENTIFIER)
    {
        laxer.getsym();
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
}

void Parser::callFunction()
{
    if (laxer.sym == IDENTIFIER)
    {
        laxer.getsym();
        if (laxer.sym == LPARENT)
        {
            laxer.getsym();
            valueParameterTable();
            if (laxer.sym == RPARENT)
            {

            }
        }
        parserTestPrint("function call");
    }
}

void Parser::valueParameterTable()
{
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
    while (laxer.sym == IF || laxer.sym == DO || laxer.sym == FOR || laxer.sym == LCURLY || laxer.sym == SCANF || laxer.sym == PRINTF || laxer.sym == SEMICOLON || laxer.sym == IDENTIFIER || laxer.sym == RETURN)
    {
        statement();
    }
    parserTestPrint("statement list");
}

void Parser::read()
{
    if (laxer.sym == SCANF)
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

void Parser::write()
{
    if (laxer.sym == PRINTF)
    {
        laxer.getsym();
        if (laxer.sym == LPARENT)
        {
            laxer.getsym();
            if (laxer.sym == STRING)
            {
                laxer.getsym();
                if (laxer.sym == COMMA)
                {
                    laxer.getsym();
                    expression();
                }
                if (laxer.sym == RPARENT)
                {
                    laxer.getsym();
                }
            }
            else
            {
                expression();
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
    if (laxer.sym == RETURN)
    {
        laxer.getsym();
        if (laxer.sym == LPARENT)
        {
            laxer.getsym();
            expression();
            if (laxer.sym == RPARENT)
                laxer.getsym();
        }
        parserTestPrint("return statement");
    }
}

void Parser::expression()
{
    if (laxer.sym == PLUS || laxer.sym == SUB)
    {
        laxer.getsym();
    }
    item();
    while (laxer.sym == PLUS || laxer.sym == SUB)
    {
        laxer.getsym();
        item();
    }
    parserTestPrint("expression");
}

void Parser::factor()
{
    if (laxer.sym ==IDENTIFIER)
    {
        string ident = laxer.getToken();
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
        else if (laxer.sym == LPARENT)
        {
            callFunction2(ident);
        }
    }
    else if (laxer.sym == CHARACTOR)
    {

    }
    else if (laxer.sym == LPARENT)
    {
        laxer.getsym();
        expression();
        if (laxer.sym == RPARENT)
        {
            laxer.getsym();
        }
    }
    else if (laxer.sym == PLUS || laxer.sym == SUB || laxer.sym == UNSIGNED_INGEGER)
    {
        integer();
    }
    else
    {

    }
    parserTestPrint("factor");
}

void Parser::item()
{
    factor();
    while (laxer.sym == PLUS || laxer.sym == DIVI)
    {
        laxer.getsym();
        factor();
    }
    parserTestPrint("item");
}