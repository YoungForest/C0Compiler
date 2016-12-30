#include "TemporaryRegistesrPool.h"

TemporaryRegistesrPool::~TemporaryRegistesrPool()
{
    //dtor
}

std::string TemporaryRegistesrPool::alloc(symbolItem * item)
{
	static int index = 0;
	int i;
	for (i = 0; i < POOL_SIZE; i++)
	{
		if (occupy[i] == false)
		{
			occupy[i] = true;
			finalCodeGenerater.loadWord(item, getRegString(i));
			return getRegString(i);
		}
	}
	finalCodeGenerater.saveWord(item, getRegString(index));
	index = (index + 1) % POOL_SIZE;
	return std::string();
}

std::string TemporaryRegistesrPool::search(symbolItem * item)
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (occupy[i] == true && objects[i] == item)
			return getRegString(i);
	}
	return "";
}

std::string TemporaryRegistesrPool::getRegString(int r)
{
	const std::string regs[] = {
		"$t0",
		"$t1",
		"$t2",
		"$t3",
		"$t4",
		"$t5",
		"$t6",
		"$t7",
		"$t8",
		"$t9"
	};
	return regs[r];
}

void TemporaryRegistesrPool::clear()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (occupy[i] == true)
		{ 
			finalCodeGenerater.saveWord(objects[i], getRegString(i));
			objects[i] = nullptr;
			occupy[i] = false;
		}
	}
}
