#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "MyHeader.h"

// ȫ�ֱ�������
char ch;                           // ���ڴʷ�������������һ�δ��ļ��ж������ַ�
char token[WORD_LENGTH];			// �洢��ǰ����
int indexOfToken = 0;				// ��ǰ��token�±�
int num;                          // ������һ��ʶ�����������
int cc;                           // ��ĸ��������ָ�룩
int err;							// ��¼����������
int sym;                 // ������һ��ʶ�������token����

// ��ȫ�ֱ���ch�ж���һ���ַ�, ���﷨��������getsym����
void getChar()
{
	ch = fgetc(filein);
}
// ���token�ַ���������
void chearToken()
{
	token[0] = '\0';
	indexOfToken = 0;
}
// �ж�ch�Ƿ��ǿո��
int isSpace()
{
	return ch == ' ';
}
// �ж�ch�Ƿ��� ���з� �� �س���
int isNewline()
{
	return ch == '\n' || ch == '\r';
}
// �ж�ch�Ƿ��� �Ʊ��tab
int isTab()
{
	return ch == '\t';
}
// �ж�ch�Ƿ�����ĸ, ���� �»���
int isLetter()
{
	return isalpha(ch) || ch == '_';
}
// �ж�ch�Ƿ�������, 0,1,2,...,9
int isDigit()
{
	return isdigit(ch);
}
// �ж�ch�Ƿ��� ����
int isComma()
{
	return ch == ',';
}
// �ж�ch�Ƿ��� �ֺ�
int isSemi()
{
	return ch == ';';
}
// �ж�ch�Ƿ��� ���ں�
int isEqu()
{
	return ch == '=';
}
// �ж�ch�Ƿ��� С�ں�
int isLess()
{
	return ch == '<';
}
// �ж�ch�Ƿ��� ���ں�
int isGreat()
{
	return ch == '>';
}
// �ж�ch�Ƿ��� �Ӻ�
int isPlus()
{
	return ch == '+';
}
// �ж�ch�Ƿ��� ����
int isMinus()
{
	return ch == '-';
}
// �ж�ch�Ƿ��� ��б��(����)
int isDivi()
{
	return ch == '/';
}
// �ж�ch�Ƿ��� �Ǻ�(�˺�)
int isStar()
{
	return ch == '*';
}
// �ж�ch�Ƿ��� ������
int isLpar()
{
	return ch == '(';
}
// �ж�ch�Ƿ��� ������
int isRpar()
{
	return ch == ')';
}
// �ж�ch�Ƿ��� ��̾��
int isExclamation()
{
	return ch == '!';
}
// ���ַ�ch׷�ӵ� token ĩβ
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
// ����һ���ַ�
void retract()
{
	ungetc(ch, filein);
}
// �б�����
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
// ��toekn�е� �ַ����� ת��Ϊ ����
int transNum()
{
	return atoi(token);
}

// �ʷ���������
int getsym()
{
	// ��� �ַ�������
	chearToken();
	// �������� �հ׷�
	while (isSpace() || isNewline() || isTab() || ch == '\0')
		getChar();
	// ����������ַ�����ĸ
	if (isLetter())
	{
		while (isLetter() || isDigit())
		{
			catToken();
			getChar();
		}
		retract();
		int resultValue = reserver();
		if (resultValue == 0) // ������ ���ʲ��� ������, ��δ�����ַ�
			sym = IDENTIFIER;
		else // �����ĵ����Ǳ�����
			sym = resultValue;
	}
	else if (isDigit())
	{	//��һ������
		// while (isDigit())
		// {
		// 	catToken();
		// 	getChar();
		// }
		// retract();
		num = transNum();
		if(ch == '0')
			syn = ZERO_NUMBER
		else
			sym = NOT_ZERO_NUMBER;
	}
	else if (isEqu())	// =
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
	else if (isLess())	// <
	{
		getChar();
		if (isEqu())
			sym = LEQ;	// <=
		else
		{
			retract();
			sym = LSS;	// <
		}
	}
	else if (isGreat())	// >
	{
		getChar();
		if (isEqu())
			sym = GEQ;	// >=
		else
		{
			retract();
			sym = GTR;	// >
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
	else if (isPlus())	// +
		sym = PLUS;
	else if (isMinus())	// -
		sym = SUB;
	else if (isStar())	// *
		sym = MULIT;
	else if (isDivi())	// /
		sym = DIVI;
	else if (isLpar())	// (
		sym = LPARENT;
	else if (isRpar())	// )
		sym = RPARENT;
	else if (ch == '[')	// [
		sym = LSQUARE;
	else if (ch == ']')	// ]
		sym = RSQUARE;
	else if (ch == '{')	// {
		sym = LCURLY;
	else if (ch == '}')	// }
		sym = RCURLY;
	else if (isComma())	// ,
		sym = COMMA;
	else if (isSemi())	// ;
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
// �ķ��������� ���Գ���
int testGetsym()
{
	static long count = 0;
	static char* symbol[] = {
		"NUL",
		"PLUS",
		"SUB",
		"MULIT",
		"DIVI",
		"LSS",
		"LEQ",
		"GTR",
		"GEQ",
		"NEQ",
		"EQL",
		"DOUBLE_QUOTE",
		"APOSTROPHE",
		"SEMICOLON",
		"COMMA",
		"LPARENT",
		"RPARENT",
		"LSQUARE",
		"RSQUARE",
		"LCURLY",
		"RCURLY",
		"DO",
		"WHILE",
		"FOR",
		"IF",
		"ELSE",
		"VOID",
		"INT",
		"CHAR",
		"MAIN",
		"SCANF",
		"PRINTF",
		"RETURN",
		"CONST",
		"IDENTIFIER",
		"NUMBER",
		"BECOMES",
		"ENDOFFILEIN"
	};
	do
	{
		getChar();
		getsym();
		printf("%ld %s %s\n", ++count, symbol[sym], token);
	} while (ch != EOF);
	return 0;
}
