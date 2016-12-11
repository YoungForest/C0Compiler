#include "SymbolTable.h"
#include <sstream>

using namespace std;

SymbolTable::SymbolTable(int _scope)
{
    //ctor
    offset = BASE_OFFSET;
	scope = _scope;
}

SymbolTable::~SymbolTable()
{
    //dtor
}

struct symbolItem* SymbolTable::searchItem(string name)
{
	for (int i = 0; i < symbolList.size(); i++)
		if (symbolList[i]->name == name)
		{
			if (scope == LOCAL)
				return symbolList[i];
			else
			{
				if (symbolList[i]->kind == PARAMETER)
					continue;
				else
					return symbolList[i];
			}
		}
    /*if (symbolList.count(name))
        return symbolList[name];
    else
        return NULL;*/
	return NULL;
}

struct symbolItem* SymbolTable::insertItem(string name, int line, int kind, int type, int val, int length)
{
	struct symbolItem* item = new struct symbolItem();
    item->name = name;
    item->line = line;
    item->kind = kind;
    item->type = type;
	item->length = length;
	item->scope = scope;
    if (item->kind == CONSTANT || (item->kind == PARAMETER && item->scope == GLOBAL))
        item->valueoroffset = val;
    else if (item->kind == VARIABLE || (item->kind == PARAMETER && item->scope == LOCAL))
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
        item->valueoroffset = - offset;
        offset += grow;
    }
    else if (item->kind == FUNCTION)
    {
        // nothing to do if function
        // length is the number of value table? yes, but parser set it
    }
    else
    {

    }
    symbolList.push_back(item);
    return item;
}

struct symbolItem* SymbolTable::generateTemp()
{
    static int tvc = 0; // temp varieties count
    stringstream name;
    name << "yangsen_temp" << tvc++;
    struct symbolItem* r = insertItem(name.str(), -1, VARIABLE, INT_TYPE);
    return r;
}

struct symbolItem* SymbolTable::generateTempChar()
{
	static int tvc = 0; // temp varieties count
	stringstream name;
	name << "yangsen_tempchar" << tvc++;
	struct symbolItem* r = insertItem(name.str(), -1, VARIABLE, CHAR_TYPE);
	return r;
}

int SymbolTable::getPosition(struct symbolItem * elem)
{
	for (int i = 0; i < symbolList.size(); i++)
		if (symbolList[i] == elem)
			return i;
	return 0;
}

void SymbolTable::clear()
{
	offset = BASE_OFFSET;
	symbolList.clear();
}

struct symbolItem* SymbolTable::generateTempConstant(int value, int type)
{
	static int tvc = 0; // temp varieties count
	stringstream name;
	name << "yangsen_const" << tvc++;
	struct symbolItem* r = insertItem(name.str(), -1, CONSTANT, type, value);
	return r;
}