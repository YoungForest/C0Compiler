#include <stdio.h>
#include "MyHeader.h"

char* err_msg[] =                  // 错误信息
{
	/*  0  */   "",
	/*  1  */	"The word is too loog than limit WORD_LENT.",
	/*  2  */	"Getsym error."
};

void error(int n)                 // 打印错误信息
{
	int i;
	printf("Error=>");
	for (i = 1; i <= cc - 1; i++)
	{
		printf(" ");
	}
	printf("|%s(%d)\n", err_msg[n], n);
	err++;
}