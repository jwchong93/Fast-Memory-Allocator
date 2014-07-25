#ifndef Allocator_H
#define Allocator_H

#include "manageAVL.h"
#include "AVLAddress.h"

#define MEMORY_SIZE (150)


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
