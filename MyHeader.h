#pragma once

#ifndef _MYHEADER
#define _MYHEADER

// 定义 记忆符 和 类别编号
#define NUL 0	// 未定义类型

#define PLUS 1	// +
#define SUB 2	// -
#define MULIT 3 // *
#define DIVI 4 // /

#define LSS 5 // <
#define LEQ 6 // <=
#define GTR 7 // >
#define GEQ 8 // >=
#define NEQ 9 // !=
#define EQL 10 // ==

#define DOUBLE_QUOTE 11	// "
#define APOSTROPHE 12	// '
#define SEMICOLON 13	// ;
#define COMMA 14		// ,
#define LPARENT 15		// (
#define RPARENT 16		// )
#define LSQUARE 17		// [
#define RSQUARE 18		// ]
#define LCURLY 19		// {
#define RCURLY 20		// }

#define DO 21		// do
#define WHILE 22	// while
#define FOR 23		// for
#define IF 24		// if
#define ELSE 25		//else

#define VOID 26		// void
#define INT 27		// int
#define CHAR 28		// char

#define MAIN 29		// main
#define SCANF 30	// scanf
#define PRINTF 31	// printf
#define RETURN 32	// return

#define CONST 33	// const

#define IDENTIFIER 34 // 标识符, 具体查看token内容
#define NUMBER 35	// 整常数

#define BECOMES 36 // = 赋值
// END 定义 记忆符 和 类别编号

#define WORD_LENGTH (100)			// 最长单词长度

// 全局变量声明
extern FILE *filein;
extern char ch;                           // 用于词法分析，存放最近一次从文件中读出的字符
extern char token[WORD_LENGTH];			// 存储当前单词
extern int indexOfToken;				// 当前的token下标
extern int num;                          // 存放最近一次识别出来的数字
extern int cc;                           // 字母计数（列指针）
extern int err;							// 记录编译出错次数
extern int sym;                 // 存放最近一次识别出来的token类型

// 函数声明
int getsym();
int testGetsym();
void error(int n);

#endif // !_MYHEADER