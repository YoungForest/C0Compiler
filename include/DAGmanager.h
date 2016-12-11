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

		int findsymbol(symbolItem *needfind);	// ���ҽ���, ������, ���ؽ���index, ����-1
		int addsymbolandnode(symbolItem *needadd);	// ��DAGͼ�в���ڵ�, �������, ������, ���ؽ���index
		int addsymbol(symbolItem * needadd, int index);	// ����������һ��
		void updateDesInSymbolList(symbolItem *des, int k);	// ����symbolList for des
		int findSrcInSymbolList(symbolItem *src);	// ��symbollist�в���src, ���ؽڵ��
		int findOprator(std::string _op, int left = -1, int right = -1);	// ��DAGͼ��Ѱ�Ҳ�����, ���û�ҵ��½��ڵ�, ���ؽڵ���nodelist�е�index
		void buildDAG();	// ����DAGͼ
		void regenerateMiddleCode();	// ����DAGͼ���������м����
		int newFunctionCall();	// ��functionCallList���¼�һ��, �����±�
		int addParameter(int functionIndex, symbolItem* formalPara, int nodeindex);	// �����Ĳ����������Ӳ���

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
