#pragma once

#ifndef _MYHEADER
#define _MYHEADER

// ���� ����� �� �����
#define NUL 0	// δ��������

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

#define IDENTIFIER 34 // ��ʶ��, ����鿴token����
#define NOT_ZERO_NUMBER 35	// ����������

#define BECOMES 36 // = ��ֵ

#define ENDOFFILEIN 37 // �ļ�������

#define ZERO_NUMBER 38 // ����0
// END ���� ����� �� �����

#define WORD_LENGTH (100)			// ����ʳ���

// ���ű�
// �������� kind
#define CONSTANT 1
#define VARIABLE 2
#define FUNCTION 3

// ������������ type
#define INT_TYPE 1
#define CHAR_TYPE 2
#define VOID_TYPE 3

// ȫ�ֱ�������
extern FILE *filein;
extern char ch;                           // ���ڴʷ�������������һ�δ��ļ��ж������ַ�
extern char token[WORD_LENGTH];			// �洢��ǰ����
extern int indexOfToken;				// ��ǰ��token�±�
extern int num;                          // ������һ��ʶ�����������
extern int cc;                           // ��ĸ��������ָ�룩
extern int err;							// ��¼����������
extern int sym;                 // ������һ��ʶ�������token����

// ��������
int getsym();
int testGetsym();
void error(int n);

#endif // !_MYHEADER
