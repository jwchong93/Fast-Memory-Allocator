#ifndef Allocator_H
#define Allocator_H

#include "manageAVL.h"
#include "AVLAddress.h"

#define MEMORY_SIZE (500)

#define getMemoryAddress(node)	(((MemoryBlockHeader*)((NodeHeader *)(node))->data)->address)
#define getMemorySize(node)	(((MemoryBlockHeader*)((NodeHeader *)(node))->data)->size)
#define destroyNodeAVL(node) destroyAVL((Node*)node)
void *theMemoryPool;
NodeHeader *freePool;
NodeHeader *allocatedPool;

typedef struct{
	int size;
	void *address;
}MemoryBlockHeader;

void initialization ();
MemoryBlockHeader *allocateMemory(int size);
void deallocateMemory(void* memoryLocation);
void destroyHeaderAVL(NodeHeader *root);
NodeHeader *mergeMemoryBlock(NodeHeader *targetNode,NodeHeader *nodeToMerge);
void destroyMemory();
#endif // Allocator_H
