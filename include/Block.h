#ifndef BLOCK_H
#define BLOCK_H

#include <QuaterInstr.h>
#include <vector>

class Block
{
    public:
        Block();
        virtual ~Block();

		std::vector<QuaterInstr *> middleCode;
		std::vector<Block *> before;
		std::vector<Block *> after;
    protected:
    private:
};

#endif // BLOCK_H
