#include "Allocator.h"
#include "manageAVL.h"
#include "stdio.h"
#include <malloc.h>
#include "AVLAddress.h"
#include "SupportiveFunction.h"

void initialization ()
{
	NodeHeader * newNode = malloc(sizeof(NodeHeader));
	MemoryBlockHeader *newHeader= malloc(sizeof(MemoryBlockHeader));
	theMemoryPool = malloc (sizeof(void)*MEMORY_SIZE);
	newHeader->address = theMemoryPool;
	newHeader->size = MEMORY_SIZE;
	newNode->Header = newHeader;
	newNode->leftChild=NULL;
	newNode->rightChild=NULL;
	newNode->balance =0;
	freePool =(NodeHeader*)avlAddHeader(freePool,newNode);
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
	newAllocatedNode->Header = newAllocatedHeader;
	newAllocatedNode->leftChild=NULL;
	newAllocatedNode->rightChild=NULL;
	newAllocatedNode->balance=0;
	
	allocatedPool = (NodeHeader*)avlAddHeader(allocatedPool, newAllocatedNode);
	/**************************************************************************
	
							Done on allocatedPool
							
	***************************************************************************/
	
	//Starting on the freePool
	getMemoryAddress(freePool) += size;
	getMemorySize(freePool) -= size;
	
	return newAllocatedHeader;
	
}

