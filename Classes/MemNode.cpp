#include"MemNode.h"

#include"MemoryPool.h"

MemNode::MemNode(MemoryPool *pool)
{
	prev = pool->using_nodes->prev;
	next = pool->using_nodes;
	prev->next = next->prev = this;
}

MemNode::~MemNode()
{
	prev->next = next;
	next->prev = prev;
}