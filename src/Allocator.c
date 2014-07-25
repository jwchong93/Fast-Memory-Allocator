#include "Allocator.h"
#include "manageAVL.h"
#include "stdio.h"
#include <malloc.h>
#include "AVLAddress.h"
#include "SupportiveFunction.h"

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
	void * freeSpace =NULL;
	
	//Handle the allocatedPool first.
	NodeHeader *newAllocatedNode= malloc(sizeof(NodeHeader));
	MemoryBlockHeader *newAllocatedHeader= malloc(sizeof(MemoryBlockHeader));
	
	freeSpace = findBlock(size);
	
	newAllocatedHeader->address = freeSpace;
	newAllocatedHeader->size = size;
	newAllocatedNode->Header = newHeader;
	newAllocatedNode->leftChild=NULL;
	newAllocatedNode->rightChild=NULL;
	allocatedPool = (NodeHeader*)avlAddHeader(allocatedPool, newAllocatedNode);
	/**************************************************************************
	
							Done on allocatedPool
							
	***************************************************************************/
	
	//Starting on the freePool
	
	return newHeader;
	
}

