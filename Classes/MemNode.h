#pragma once

class MemoryPool;

typedef unsigned int size_t;

class MemNode
{
	friend MemoryPool;

private:
	MemNode *prev, *next;

	void* operator new(size_t t) {};
	void operator delete(void *p) {};

public:
	MemNode(MemoryPool *pool);
	virtual ~MemNode();
};
