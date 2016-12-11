#ifndef DAGMANAGER_H
#define DAGMANAGER_H

#include "QuaterInstr.h"
#include "SymbolTable.h"
#include "Block.h"
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
struct functionCall
{
	symbolItem *name;
	std::vector<symbolItem*> parameterTable;
	std::vector<int> nodeindex;
};
class DAGmanager
{
    public:
		DAGmanager(Block &_block, SymbolTable &_st) : basicBlock(_block), block(_block.middleCode), st(_st) {};
        virtual ~DAGmanager();

		int findsymbol(symbolItem *needfind);	// 查找结点表, 若发现, 返回结点表index, 否则-1
		int addsymbolandnode(symbolItem *needadd);	// 向DAG图中插入节点, 并向结点表, 插入项, 返回结点表index
		int addsymbol(symbolItem * needadd, int index);	// 仅向结点表添加一项
		void updateDesInSymbolList(symbolItem *des, int k);	// 更新symbolList for des
		int findSrcInSymbolList(symbolItem *src);	// 在symbollist中查找src, 返回节点号
		int findOprator(std::string _op, int left = -1, int right = -1);	// 在DAG图中寻找操作符, 如果没找到新建节点, 返回节点在nodelist中的index
		void buildDAG();	// 构建DAG图
		void regenerateMiddleCode();	// 根据DAG图重新生成中间代码
		int newFunctionCall();	// 在functionCallList中新加一项, 返回下标
		int addParameter(int functionIndex, symbolItem* formalPara, int nodeindex);	// 向函数的参数表中增加参数

		std::vector<node> nodelist;
		std::vector<symbol> symbollist;
		Block &basicBlock;
		std::vector<QuaterInstr *> &block;
		SymbolTable &st;
		std::vector<functionCall> functionCallList;
    protected:
    private:
};

#endif // DAGMANAGER_H
