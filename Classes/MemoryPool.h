#pragma once

class MemNode;

typedef unsigned int size_t;

class MemoryPool
{
	friend MemNode;

private:
	char *pool;

	MemNode *using_nodes;
	MemNode *free_nodes;

	size_t size;
	size_t count;

	//Get ith node
	MemNode* GetNode(size_t i);

public:
	MemoryPool(size_t size, size_t count);
	~MemoryPool();

	void* New(size_t size);

	void Delete(void *p);

	size_t GetSize();
};
