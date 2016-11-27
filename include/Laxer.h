#ifndef LAXER_H
#define LAXER_H

#include "Error.h"
#include <string>
#include <fstream>

#define WORD_LENGTH (100)           // 最长单词长度
#define LINEMAX (1024)              // 最长行长度

class Laxer
{
    public:
        Laxer(std::string filename, Error &_error_handle);
        virtual ~Laxer();

        std::string getToken();  // 获取单词

        void getChar(); // 向全局变量ch中读入一个字符, 由语法分析程序getsym调用
        void clearToken();  // 清除token字符串缓冲区
        int isSpace();  // 判断ch是否是空格符
        int isNewline();    // 判断ch是否是 换行符 或 回车符
        int isTab();    // 判断ch是否是 制表符tab
        int isLetter(); // 判断ch是否是字母, 包括 下划线
        int isDigit();  // 判断ch是否是数字, 0,1,2,...,9
        int isComma();  // 判断ch是否是 逗号
        int isSemi();   // 判断ch是否是 分号
        int isEqu();    // 判断ch是否是 等于号
        int isLess();   // 判断ch是否是 小于号
        int isGreat();  // 判断ch是否是 大于号
        int isPlus();   // 判断ch是否是 加号
        int isMinus();  // 判断ch是否是 减号
        int isDivi();   // 判断ch是否是 反斜杠(除号)
        int isStar();   // 判断ch是否是 星号(乘号)
        int isLpar();   // 判断ch是否是 左括号
        int isRpar();   // 判断ch是否是 右括号
        int isExclamation();    // 判断ch是否是 感叹号
        void catToken();    // 把字符ch追加到 token 末尾
        // void retract();     // 回退一个字符
        int reserver();     // 判别保留字
        int transNum();     // 将toekn中的 字符数字 转换为 数字
        int getsym();       // 词法分析程序

        char ch;                           // 用于词法分析，存放最近一次从文件中读出的字符
        int num;                          // 存放最近一次识别出来的数字
        int linenum;                     // 目前编译到的行数
        int sym;                 // 存放最近一次识别出来的token类型
        int cc;                           // 字母计数（列指针）
        char token[WORD_LENGTH];            // 存储当前单词
        
    protected:
    private:
        char buf[LINEMAX];                  // 读缓冲区
        int indexOfToken;               // 当前的token下标
        int ll;                         // 记录行末尾
        Error& error_handle;      // 绑定错误处理程序
        std::ifstream infile;    // 读文件流
};


// 定义 记忆符 和 类别编号
#define NUL 0   // 未定义类型

#define PLUS 1  // +
#define MINUS 2   // -
#define MULIT 3 // *
#define DIVI 4 // /

#define LSS 5 // <
#define LEQ 6 // <=
#define GTR 7 // >
#define GEQ 8 // >=
#define NEQ 9 // !=
#define EQL 10 // ==

#define STRING 11 // "<字符串>
#define CHARACTOR 12   // '<字符>
#define SEMICOLON 13    // ;
#define COMMA 14        // ,
#define LPARENT 15      // (
#define RPARENT 16      // )
#define LSQUARE 17      // [
#define RSQUARE 18      // ]
#define LCURLY 19       // {
#define RCURLY 20       // }

#define DO 21       // do
#define WHILE 22    // while
#define FOR 23      // for
#define IF 24       // if
#define ELSE 25     //else

#define VOID 26     // void
#define INT 27      // int
#define CHAR 28     // char

#define MAIN 29     // main
#define SCANF 30    // scanf
#define PRINTF 31   // printf
#define RETURN 32   // return

#define CONST 33    // const

#define IDENTIFIER 34 // 标识符, 具体查看token内容
#define UNSIGNED_INGEGER 35  // 无符号整数

#define BECOMES 36 // = 赋值

#define ENDOFFILEIN 37 // 文件结束符

#define ZERO_NUMBER 38 // 数字0

#endif // LAXER_H
