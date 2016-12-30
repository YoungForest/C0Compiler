#ifndef TEMPORARYREGISTESRPOOL_H
#define TEMPORARYREGISTESRPOOL_H

#include <string>
#include "SymbolTable.h"
#include "MipsInstrGen.h"

#define POOL_SIZE sizeof(TempRegister)

enum TempRegister
{
	$t0,
	$t1,
	$t2,
	$t3,
	$t4,
	$t5,
	$t6,
	$t7,
	$t8,
	$t9,
};

class TemporaryRegistesrPool
{
    public:
		TemporaryRegistesrPool(MipsInstrGen &_finalCodeGenerater) finalCodeGenerater(finalCodeGenerater) {
			clear();
		};
        virtual ~TemporaryRegistesrPool();

		std::string alloc(symbolItem *item);
		std::string search(symbolItem *item);
		std::string getRegString(int r);
		void clear();

		MipsInstrGen &finalCodeGenerater;
		bool occupy[POOL_SIZE];
		symbolItem * objects[POOL_SIZE];
    protected:
    private:
};

#endif // TEMPORARYREGISTESRPOOL_H
