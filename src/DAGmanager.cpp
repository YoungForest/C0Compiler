#include "DAGmanager.h"

DAGmanager::DAGmanager()
{
    //ctor
}

DAGmanager::~DAGmanager()
{
    //dtor
}

void DAGmanager::buildDAG()
{
	for (auto it = block.cbegin(); it != block.cend(); it++)
	{
		bool find;
		int left, right, k;
		if ((*it)->op == Opcode::ADD || (*it)->op == Opcode::SUB || (*it)->op == Opcode::MUL || (*it)->op == Opcode::DIV)
		{
			// left x
			find = false;
			for (auto it2 = symbollist.cbegin(); it2 != symbollist.cend(); it2++)
			{
				if ((*it2).item == (*it)->src1)	// 找到x
				{
					find = true;
					left = (*it2).index;
					break;
				}
			}
			if (!find)	// 没找到x, 新建叶节点, 并加入节点表
			{
				node new_node;
				if ((*it)->src1->kind == VARIABLE)
					new_node.name = (*it)->src1->name + "0";
				else
					new_node.name = (*it)->src1->name;
				symbol new_symbol;
				new_symbol.index = nodelist.size();
				left = new_symbol.index;
				nodelist.push_back(new_node);
				new_symbol.item = (*it)->src1;
				symbollist.push_back(new_symbol);
			}
			//right y
			find = false;
			for (auto it2 = symbollist.cbegin(); it2 != symbollist.cend(); it2++)
			{
				if ((*it2).item == (*it)->src2)	// 找到y
				{
					find = true;
					right = (*it2).index;
					break;
				}
			}
			if (!find)	// 没找到y, 新建叶节点, 并加入节点表
			{
				node new_node;
				if ((*it)->src2->kind == VARIABLE)
					new_node.name = (*it)->src2->name + "0";
				else
					new_node.name = (*it)->src2->name;
				symbol new_symbol;
				new_symbol.index = nodelist.size();
				right = new_symbol.index;
				nodelist.push_back(new_node);
				new_symbol.item = (*it)->src2;
				symbollist.push_back(new_symbol);
			}
			// op
			find = false;
			for (int i = 0; i < nodelist.size(); i++)
			{
				if (nodelist[i].name == (*it)->getOpcode() && nodelist[i].leftchild == left && nodelist[i].rightchild == right)	// 找到op
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
				new_node.name = (*it)->getOpcode();
				k = nodelist.size();
			}
			// update z
			find = false;
			for (auto it2 = symbollist.begin(); it2 != symbollist.end(); it2++)
			{
				if ((*it2).item == (*it)->des)	// 找到z
				{
					find = true;
					(*it2).index = k;
					break;
				}
			}
			if (!find)	// 没找到z, 并symbollist
			{
				symbol new_symbol;
				new_symbol.index = k;
				new_symbol.item = (*it)->des;
				symbollist.push_back(new_symbol);
			}
		}
		else if ((*it)->op == Opcode::NEG)
		{

		}
		else if ((*it)->op == Opcode::ASS)
		{

		}
		else
		{

		}
	}
}
