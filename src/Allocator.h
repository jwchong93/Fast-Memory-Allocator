#ifndef Allocator_H
#define Allocator_H

#include "manageAVL.h"
#include "AVLAddress.h"

#define MEMORY_SIZE (150)

#define getMemoryAddress(node)	(((MemoryBlockHeader*)((NodeHeader *)(node))->Header)->address)
#define getMemorySize(node)	(((MemoryBlockHeader*)((NodeHeader *)(node))->Header)->size)

void *theMemoryPool;
NodeHeader *freePool;
NodeHeader *allocatedPool;

typedef struct{
	int size;
	void *address;
}MemoryBlockHeader;

void initialization ();
MemoryBlockHeader *allocateMemory(int size);
void *findBlock(int size);
#endif // Allocator_H
