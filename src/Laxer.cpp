#include "Laxer.h"

Laxer::Laxer()
{
    //ctor
}

Laxer::~Laxer()
{
    //dtor
}
// 向全局变量ch中读入一个字符, 由语法分析程序getsym调用
void Laxer::getChar()
{
    ch = fgetc(filein);
}
// 清除token字符串缓冲区
void Laxer::chearToken()
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
int isComma()
{
    return ch == ',';
}
// 判断ch是否是 分号
int isSemi()
{
    return ch == ';';
}
// 判断ch是否是 等于号
int isEqu()
{
    return ch == '=';
}
// 判断ch是否是 小于号
int isLess()
{
    return ch == '<';
}
// 判断ch是否是 大于号
int isGreat()
{
    return ch == '>';
}
// 判断ch是否是 加号
int isPlus()
{
    return ch == '+';
}
// 判断ch是否是 减号
int isMinus()
{
    return ch == '-';
}
// 判断ch是否是 反斜杠(除号)
int isDivi()
{
    return ch == '/';
}
// 判断ch是否是 星号(乘号)
int isStar()
{
    return ch == '*';
}
// 判断ch是否是 左括号
int isLpar()
{
    return ch == '(';
}
// 判断ch是否是 右括号
int isRpar()
{
    return ch == ')';
}
// 判断ch是否是 感叹号
int isExclamation()
{
    return ch == '!';
}
// 把字符ch追加到 token 末尾
void catToken()
{
    if (indexOfToken >= WORD_LENGTH-1)
    {
        printf("Word %s is too loog than %d.\n", token, WORD_LENGTH);
        chearToken();
    }
    token[indexOfToken++] = ch;
    token[indexOfToken] = '\0';
}
// 回退一个字符
void retract()
{
    ungetc(ch, filein);
}
// 判别保留字
int reserver()
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
    else if (strcmp(token, " return") == 0)
        return RETURN;
    else if (strcmp(token, "const") == 0)
        return CONST;
    else
        return NUL;
}
// 将toekn中的 字符数字 转换为 数字
int transNum()
{
    return atoi(token);
}

// 词法分析程序
int getsym()
{
    // 清除 字符缓冲区
    chearToken();
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
        retract();
        int resultValue = reserver();
        if (resultValue == 0) // 读到的 单词不是 保留字, 是未定义字符
            sym = IDENTIFIER;
        else // 读到的单词是保留字
            sym = resultValue;
    }
    else if (isDigit())
    {   //读一个数字
        // while (isDigit())
        // {
        //  catToken();
        //  getChar();
        // }
        // retract();
        num = transNum();
        if(ch == '0')
            syn = ZERO_NUMBER
        else
            sym = NOT_ZERO_NUMBER;
    }
    else if (isEqu())   // =
    {
        getChar();
        if (isEqu())
            sym = EQL;
        else
        {
            retract();
            sym = BECOMES;
        }
    }
    else if (isLess())  // <
    {
        getChar();
        if (isEqu())
            sym = LEQ;  // <=
        else
        {
            retract();
            sym = LSS;  // <
        }
    }
    else if (isGreat()) // >
    {
        getChar();
        if (isEqu())
            sym = GEQ;  // >=
        else
        {
            retract();
            sym = GTR;  // >
        }
    }
    else if (isExclamation()) // !
    {
        getChar();
        if (isEqu())
            sym = NEQ;
        else
        {
            retract();
            error(2);
        }
    }
    else if (isPlus())  // +
        sym = PLUS;
    else if (isMinus()) // -
        sym = SUB;
    else if (isStar())  // *
        sym = MULIT;
    else if (isDivi())  // /
        sym = DIVI;
    else if (isLpar())  // (
        sym = LPARENT;
    else if (isRpar())  // )
        sym = RPARENT;
    else if (ch == '[') // [
        sym = LSQUARE;
    else if (ch == ']') // ]
        sym = RSQUARE;
    else if (ch == '{') // {
        sym = LCURLY;
    else if (ch == '}') // }
        sym = RCURLY;
    else if (isComma()) // ,
        sym = COMMA;
    else if (isSemi())  // ;
        sym = SEMICOLON;
    else if (ch == '\'') // '
        sym = APOSTROPHE;
    else if (ch == '\"') // "
        sym = DOUBLE_QUOTE;
    else if (ch == EOF)
        sym = ENDOFFILEIN;
    else
        error(2);

    return 0;
}

