#include"MemoryPool.h"

#include"MemNode.h"

MemNode* MemoryPool::GetNode(size_t i)
{
	return (MemNode*)(pool + size*i);
}

MemoryPool::MemoryPool(size_t size, size_t count) : size(size), count(count)
{
	if (size <= 0 || count <= 0)
	{
		//eror
		return;
	}

	pool = new char[size*(count + 2)];

	using_nodes = GetNode(0);
	using_nodes->prev = using_nodes->next = using_nodes;

	free_nodes = GetNode(1);
	for (size_t i = 1; i < count + 2; i++)
	{
		GetNode(i)->prev = nullptr;
		GetNode(i)->next = GetNode(i + 1);
	}
	GetNode(count + 1)->next = free_nodes;
}

MemoryPool::~MemoryPool()
{
	delete[] pool;
}

void* MemoryPool::New(size_t size)
{
	if (size > this->size) {
		//error
		return nullptr;
	}

	if (free_nodes->next == free_nodes) return nullptr;

	MemNode *node = free_nodes->next;
	free_nodes->next = node->next;
	return node;
}

void MemoryPool::Delete(void *p)
{
	MemNode *node = (MemNode*)p;
	if (node->prev == nullptr) {
		//error
		return;
	}

	node->prev = nullptr;
	node->next = free_nodes->next;
	free_nodes->next = node;
}

size_t MemoryPool::GetSize()
{
	return count;
}