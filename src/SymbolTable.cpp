#include "SymbolTable.h"
#include <sstream>

using namespace std;

SymbolTable::SymbolTable()
{
    //ctor
    offset = 0;
}

SymbolTable::~SymbolTable()
{
    //dtor
}

struct symbolItem* SymbolTable::searchItem(string name)
{
    if (symbolList.count(name))
        return symbolList[name];
    else
        return NULL;
}

struct symbolItem* SymbolTable::insertItem(string name, int line, int kind, int type, int val = 0, int length = 0)
{
	struct symbolItem* item = new struct symbolItem();
    item->name = name;
    item->line = line;
    item->kind = kind;
    item->type = type;
	item->length = length;
    if (item->kind == CONSTANT)
        item->valueoroffset = val;
    else if (item->kind == VARIABLE)
    {
        int grow;
        if (length == 0)   // no array
            grow = 1;
        else
            grow = length;
        if (item->type == CHAR_TYPE)
            grow *= 4;  // change 1 to 4 for more easy deal
        else if (item->type == INT_TYPE)
            grow *= 4;
        item->valueoroffset = offset;
        offset += grow;
    }
    else if (item->kind == FUNCTION)
    {
        // nothing to do if function
        // length is the number of value table?
    }
    else
    {

    }
    symbolList.insert(pair<string, struct symbolItem*>(item->name, item));
    return item;
}

struct symbolItem* SymbolTable::generateTemp()
{
    static int tvc = 0; // temp varieties count
    stringstream name;
    name << "!temp" << tvc;
    struct symbolItem* r = insertItem(name.str(), -1, VARIABLE, INT_TYPE);
    return r;
}

struct symbolItem* SymbolTable::generateTempConstant(int value)
{
	static int tvc = 0; // temp varieties count
	stringstream name;
	name << "!tempConstant" << tvc;
	struct symbolItem* r = insertItem(name.str(), -1, CONSTANT, INT_TYPE, value);
	return r;
}