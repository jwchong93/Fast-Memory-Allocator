#include "Allocator.h"
#include "manageAVL.h"
#include "stdio.h"
#include <malloc.h>
#include "AVLAddress.h"

void initialization ()
{
	NodeHeader * newHeader = malloc(sizeof(NodeHeader));
	theMemoryPool = malloc (sizeof(void)*MEMORY_SIZE);
	newHeader->Header = theMemoryPool;
	freePool =(NodeHeader*)avlAddHeader(freePool,newHeader);
	allocatedPool = NULL;
	
	
}

void destroyMemory()
{
	free(theMemoryPool);
	freePool=NULL;
	allocatedPool = NULL;
}

MemoryBlockHeader *allocateMemory(int size)
{

}

