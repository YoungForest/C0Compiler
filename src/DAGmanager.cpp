#include "DAGmanager.h"

using namespace std;

DAGmanager::~DAGmanager()
{
    //dtor
}


int DAGmanager::findsymbol(symbolItem *needfind)
{
	bool find = false;
	for (auto it = symbollist.cbegin(); it != symbollist.cend(); it++)
	{
		if ((*it).item == needfind)	// ÕÒµ½ ·ûºÅÏî
		{
			find = true;
			return (*it).index;
		}
	}
return -1;
}

int DAGmanager::addsymbolandnode(symbolItem * needadd)
{
	node new_node;
	if (needadd->kind == VARIABLE)
		new_node.name = needadd->name + "0";
	else
		new_node.name = needadd->name;
	symbol new_symbol;
	new_symbol.index = nodelist.size();
	nodelist.push_back(new_node);
	new_symbol.item = needadd;
	symbollist.push_back(new_symbol);
	return 0;
}

int DAGmanager::addsymbol(symbolItem * needadd, int index)
{
	symbol new_symbol;
	new_symbol.index = index;
	new_symbol.item = needadd;
	symbollist.push_back(new_symbol);
	return symbollist.size() - 1;
}

void DAGmanager::updateDesInSymbolList(symbolItem * des, int k)
{
	if (findsymbol(des) == -1)
	{
		symbollist[findsymbol(des)].index = k;
	}
	else
	{
		addsymbol(des, k);
	}
}

int DAGmanager::findSrcInSymbolList(symbolItem * src)
{
	if (findsymbol(src) == -1)
	{
		return symbollist[addsymbolandnode(src)].index;
	}
	else
	{
		return symbollist[findsymbol(src)].index;
	}
}

int DAGmanager::findOprator(string _op, int left, int right)
{
	int k;	// symbol.index
	bool find = false;
	for (int i = 0; i < nodelist.size(); i++)
	{
		if (nodelist[i].name == _op && nodelist[i].leftchild == left && nodelist[i].rightchild == right)	// ÕÒµ½op
		{
			find = true;
			k = i;
			break;
		}
	}
	if (!find)
	{
		node new_node;
		new_node.leftchild = left;
		new_node.rightchild = right;
		new_node.name = _op;
		k = nodelist.size();
	}
	return k;
}

void DAGmanager::buildDAG()
{
	for (auto it = block.cbegin(); it != block.cend(); it++)
	{
		int left, right, k;
		if ((*it)->op == Opcode::ADD || (*it)->op == Opcode::SUB || (*it)->op == Opcode::MUL || (*it)->op == Opcode::DIV)
		{
			// left x
			left = findSrcInSymbolList((*it)->src1);
			//right y
			right = findSrcInSymbolList((*it)->src2);
			// op
			k = findOprator((*it)->getOpcode(), left, right);
			// update z
			updateDesInSymbolList((*it)->des, k);
		}
		else if ((*it)->op == Opcode::NEG)
		{
			left = findSrcInSymbolList((*it)->src1);
			k = findOprator((*it)->getOpcode(), left);
			updateDesInSymbolList((*it)->des, k);
		}
		else if ((*it)->op == Opcode::ASS)
		{
			k = findSrcInSymbolList((*it)->src1);
			updateDesInSymbolList((*it)->des, k);
		}
		else if ((*it)->op == Opcode::LAV)
		{

		}
		else
		{

		}
	}
}
