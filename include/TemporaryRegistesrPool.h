#ifndef TEMPORARYREGISTESRPOOL_H
#define TEMPORARYREGISTESRPOOL_H

#include <string>
#include "SymbolTable.h"

#define POOL_SIZE (10)

class TemporaryRegistesrPool
{
    public:
		TemporaryRegistesrPool();
        virtual ~TemporaryRegistesrPool();

		bool occupy[POOL_SIZE];
		symbolItem * objects[POOL_SIZE];
    protected:
    private:
};

#endif // TEMPORARYREGISTESRPOOL_H
