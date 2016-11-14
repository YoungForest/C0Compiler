#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
    //ctor
    symbolList = new std::list<symbol>();
}

SymbolTable::~SymbolTable()
{
    //dtor
    delete(symbolList);
}
