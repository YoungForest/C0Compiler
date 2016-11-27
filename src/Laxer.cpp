#include <iostream>
#include <map>
#include <string>
#include <ctype.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "Laxer.h"
#include "Error.h"

using namespace std;

Laxer::Laxer(string filename, Error& _error_handle) :error_handle(_error_handle)
{
    //ctor
    infile.open(filename.c_str());
    infile.getline(buf, LINEMAX);
    ll = strlen(buf);
    cc = 0;
    clearToken();
    indexOfToken = 0;
    ch = ' ';
    linenum = 1;
    getChar();
};

Laxer::~Laxer()
{
    //dtor
}

string Laxer::getToken()
{
    string str(token);
    return str;
}

void Laxer::getChar()
{
    // cout << cc << endl;
    if (cc == ll) // 如果到达行末尾
    {
        if (infile.eof())   // 如果到达文件结束
        {
            ch = EOF;
            return;
        }
        infile.getline(buf, LINEMAX);   // 向缓冲区读入新行
        ll = strlen(buf);   // 更新行长
        linenum++;
        cc = 0;
        ch = ' ';
    }
    else if (cc == 0)
    {
        ch = buf[cc];
        cc++;
    }
    else
    {
        ch = buf[cc];
        cc++;
    }
}
// 清除token字符串缓冲区
void Laxer::clearToken()
{
    token[0] = '\0';
    indexOfToken = 0;
}
// 判断ch是否是空格符
int Laxer::isSpace()
{
    return ch == ' ';
}
// 判断ch是否是 换行符 或 回车符
int Laxer::isNewline()
{
    return ch == '\n' || ch == '\r';
}
// 判断ch是否是 制表符tab
int Laxer::isTab()
{
    return ch == '\t';
}
// 判断ch是否是字母, 包括 下划线
int Laxer::isLetter()
{
    return isalpha(ch) || ch == '_';
}
// 判断ch是否是数字, 0,1,2,...,9
int Laxer::isDigit()
{
    return isdigit(ch);
}
// 判断ch是否是 逗号
int Laxer::isComma()
{
    return ch == ',';
}
// 判断ch是否是 分号
int Laxer::isSemi()
{
    return ch == ';';
}
// 判断ch是否是 等于号
int Laxer::isEqu()
{
    return ch == '=';
}
// 判断ch是否是 小于号
int Laxer::isLess()
{
    return ch == '<';
}
// 判断ch是否是 大于号
int Laxer::isGreat()
{
    return ch == '>';
}
// 判断ch是否是 加号
int Laxer::isPlus()
{
    return ch == '+';
}
// 判断ch是否是 减号
int Laxer::isMinus()
{
    return ch == '-';
}
// 判断ch是否是 反斜杠(除号)
int Laxer::isDivi()
{
    return ch == '/';
}
// 判断ch是否是 星号(乘号)
int Laxer::isStar()
{
    return ch == '*';
}
// 判断ch是否是 左括号
int Laxer::isLpar()
{
    return ch == '(';
}
// 判断ch是否是 右括号
int Laxer::isRpar()
{
    return ch == ')';
}
// 判断ch是否是 感叹号
int Laxer::isExclamation()
{
    return ch == '!';
}
// 把字符ch追加到 token 末尾
void Laxer::catToken()
{
    if (indexOfToken >= WORD_LENGTH-1)
    {
        printf("Word %s is too loog than %d.\n", token, WORD_LENGTH);
        clearToken();
    }
    token[indexOfToken++] = ch;
    token[indexOfToken] = '\0';
}
// 回退一个字符
/*
void Laxer::retract()
{
    ungetc(ch, filein);
}
*/
// 判别保留字
int Laxer::reserver()
{
    if (strcmp(token, "do") == 0)
        return DO;
    else if (strcmp(token, "while") == 0)
        return WHILE;
    else if (strcmp(token, "for") == 0)
        return FOR;
    else if (strcmp(token, "if") == 0)
        return IF;
    else if (strcmp(token, "else") == 0)
        return ELSE;
    else if (strcmp(token, "void") == 0)
        return VOID;
    else if (strcmp(token, "int") == 0)
        return INT;
    else if (strcmp(token, "char") == 0)
        return CHAR;
    else if (strcmp(token, "main") == 0)
        return MAIN;
    else if (strcmp(token, "scanf") == 0)
        return SCANF;
    else if (strcmp(token, "printf") == 0)
        return PRINTF;
    else if (strcmp(token, "return") == 0)
        return RETURN;
    else if (strcmp(token, "const") == 0)
        return CONST;
    else
        return NUL;
}
// 将toekn中的 一个字符数字 转换为 数字(这里的数字只有一位)
int Laxer::transNum()
{
    return atoi(token);
}

// 词法分析程序
int Laxer::getsym()
{
    // 清除 字符缓冲区
    clearToken();
    // 跳过所有 空白符
    while (isSpace() || isNewline() || isTab() || ch == '\0')
        getChar();
    // 如果读到的字符是字母
    if (isLetter())
    {
        while (isLetter() || isDigit())
        {
            catToken();
            getChar();
        }
        int resultValue = reserver();
        if (resultValue == 0) // 读到的 单词不是 保留字, 是未定义字符
            sym = IDENTIFIER;
        else // 读到的单词是保留字
            sym = resultValue;
    }
    else if (isDigit() && ch != '0')
    {
        //读一个数字
        while (isDigit())
        {
            catToken();
            getChar();
        }
        num = transNum();
        sym = UNSIGNED_INGEGER;
    }
    else if (ch == '0')
    {
        num = 0;
        sym = ZERO_NUMBER;
        getChar();
    }
    else if (isEqu())   // =
    {
        getChar();
        if (isEqu())
        {
            sym = EQL;
            getChar();
        }
        else
        {
            sym = BECOMES;
        }
    }
    else if (isLess())  // <
    {
        getChar();
        if (isEqu())
        {
            sym = LEQ;  // <=
            getChar();
        }
        else
        {
            sym = LSS;  // <
        }
    }
    else if (isGreat()) // >
    {
        getChar();
        if (isEqu())
        {
            sym = GEQ;  // >=
            getChar();
        }
        else
        {
            sym = GTR;  // >
        }
    }
    else if (isExclamation()) // !
    {
        getChar();
        if (isEqu())
        {
            sym = NEQ;  // !=
            getChar();
        }
        else
        {
            error_handle.errorMessage(3, linenum, cc);
        }
    }
    else if (isPlus())  // +
    {
        sym = PLUS;
        getChar();
    }
    else if (isMinus()) // -
    {
        sym = MINUS;
        getChar();
    }
    else if (isStar())  // *
    {
        sym = MULIT;
        getChar();
    }
    else if (isDivi())  // /
    {
        sym = DIVI;
        getChar();
    }
    else if (isLpar())  // (
    {
        sym = LPARENT;
        getChar();
    }
    else if (isRpar())  // )
    {
        sym = RPARENT;
        getChar();
    }
    else if (ch == '[') // [
    {
        sym = LSQUARE;
        getChar();
    }
    else if (ch == ']') // ]
    {
        sym = RSQUARE;
        getChar();
    }
    else if (ch == '{') // {
    {
        sym = LCURLY;
        getChar();
    }
    else if (ch == '}') // }
    {
        sym = RCURLY;
        getChar();
    }
    else if (isComma()) // ,
    {
        sym = COMMA;
        getChar();
    }
    else if (isSemi())  // ;
    {
        sym = SEMICOLON;
        getChar();
    }
    else if (ch == '\'') // '
    {
        sym = NUL;
        getChar();
        if (isLetter() || isPlus() || isMinus() || isStar() || isDivi() || isDigit())
        {
            catToken();
            getChar();
            if (ch == '\'')
            {
                sym = CHARACTOR;
                getChar();
            }
        }
    }
    else if (ch == '\"') // "
    {
        sym = NUL;
        getChar();
        while (ch != '\"')
        {
            if ((ch <= 126 && ch >= 35) || ch == 32 || ch == 33)
            {
				catToken();
                getChar();
            }
        }
        getChar();
        sym = STRING;
    }
    else if (ch == EOF)
    {
        sym = ENDOFFILEIN; // 读到文件末尾
    }
    else
    {
        string str(token);
        error_handle.errorMessage(2, linenum, cc, str);
    }

    return 0;
}

