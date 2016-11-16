#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Wrong arguments.\n");
		exit(1);
	}
	freopen("14061213_out.txt", "w", stdout);

	string filein;
	filein = argv[1];

	Parser *parser0 = new Parser(filein);
    parser0->parser();
	// filein = fopen(argv[1], "r");
	// testGetsym();
	// fclose(filein);
	return 0;
}
