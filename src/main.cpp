#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Too few or many arguments.\n");
		exit(1);
	}
#ifdef DEBUG
	cout << "debuging" << __LINE__ << __FILE__ << endl;
#endif


	string filein;
	filein = argv[1];
	string fileout;
	fileout = argv[2];

	Parser *parser0 = new Parser(filein);
    parser0->parser(fileout);

	system("pause");

	return 0;
}
