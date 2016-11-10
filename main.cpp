#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "MyHeader.h"

FILE *filein;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Wrong arguments.\n");
		exit(1);
	}
	freopen("14061213_out.txt", "w", stdout);
	filein = fopen(argv[1], "r");
	testGetsym();
	fclose(filein);
	return 0;
}