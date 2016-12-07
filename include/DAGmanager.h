#ifndef DAGMANAGER_H
#define DAGMANAGER_H

#include "QuaterInstr.h"
#include "SymbolTable.h"
#include <string>
#include <vector>

struct node
{
	int leftchild;
	int rightchild;
	std::string name;
};
struct symbol
{
	symbolItem *item;
	int index;
};
class DAGmanager
{
    public:
		DAGmanager(std::vector<QuaterInstr *> &_block, SymbolTable &_st) : block(_block), st(_st) {};
        virtual ~DAGmanager();

		void buildDAG();	// ¹¹½¨DAGÍ¼
		void regenerateMiddleCode();

		std::vector<node> nodelist;
		std::vector<symbol> symbollist;
		std::vector<QuaterInstr *> &block;
		SymbolTable &st;
    protected:
    private:
};

#endif // DAGMANAGER_H
