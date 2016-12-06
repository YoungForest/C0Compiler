#ifndef DAGMANAGER_H
#define DAGMANAGER_H

#include "QuaterInstr.h"
#include <string>
#include <vector>

struct node
{
	int leftchild;
	int rightchild;
	std::string name;
};
class DAGmanager
{
    public:
		DAGmanager(std::vector<QuaterInstr *> &_block, SymbolTable &_st) : block(_block), st(_st) {};
        virtual ~DAGmanager();

		void buildDAG();
		void regenerateMiddleCode();

		std::vector<node> nodelist;
		std::vector<QuaterInstr *> &block;
		SymbolTable &st;
    protected:
    private:
};

#endif // DAGMANAGER_H
