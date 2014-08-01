#include "Allocator.h"
#include "manageAVL.h"
#include "stdio.h"
#include <malloc.h>
#include "AVLAddress.h"
#include "SupportiveFunction.h"

/**********************************************************************
* Initialize the global variables
*
*	Input: none
*	Output: none
*	
*	Global variables affected: freePool, allocatedPool, theMemoryPool
*
***********************************************************************/
void initialization ()
{
	NodeHeader * newNode = malloc(sizeof(NodeHeader));
	MemoryBlockHeader *newHeader= malloc(sizeof(MemoryBlockHeader));
	theMemoryPool = malloc (sizeof(void)*MEMORY_SIZE);
	newHeader->address = theMemoryPool;
	newHeader->size = MEMORY_SIZE;
	newNode->data = newHeader;
	newNode->leftChild=NULL;
	newNode->rightChild=NULL;
	newNode->balance =0;
	freePool =avlAddHeader(freePool,newNode);
	allocatedPool = NULL;
	
	
}

/*********************************************************************
* Destroy the data inside the global variables.
*
*	Input: none
*	Output: none
*
*	Destroy: freePool,allocatedPool,theMemoryPool
*	
**********************************************************************/
void destroyMemory()
{
	free(theMemoryPool);
	freePool=NULL;
	allocatedPool = NULL;
}

//This function in developing, will come back to this after finish deallocate.
MemoryBlockHeader *allocateMemory(int size)
{
	void * freeSpace =NULL;
	
	//Handle the allocatedPool first.
	NodeHeader *newAllocatedNode= malloc(sizeof(NodeHeader));
	MemoryBlockHeader *newAllocatedHeader= malloc(sizeof(MemoryBlockHeader));
	
	freeSpace = findBlock(size);
	
	newAllocatedHeader->address = freeSpace;
	newAllocatedHeader->size = size;
	newAllocatedNode->data = newAllocatedHeader;
	newAllocatedNode->leftChild=NULL;
	newAllocatedNode->rightChild=NULL;
	newAllocatedNode->balance=0;
	
	allocatedPool = avlAddHeader(allocatedPool, newAllocatedNode);
	/**************************************************************************
	
							Done on allocatedPool
							
	***************************************************************************/
	
	//Starting on the freePool
	getMemoryAddress(freePool) += size;
	getMemorySize(freePool) -= size;
	/**************************************************************************
	
							End of editing freePool
							
	***************************************************************************/
	return newAllocatedHeader;
	
}

void deallocateMemory(void* memoryLocation)
{
	int size = getMemorySize(allocatedPool);
	NodeHeader * targetNode=NULL;
	//Edit allocatedPool 
	MemoryBlockHeader tempHeader={.address=memoryLocation};
	NodeHeader tempNode = {.data = &tempHeader};
	targetNode = avlFindHeader (allocatedPool,&tempNode);
	targetNode = avlRemoveHeader(&allocatedPool, targetNode);
	//Done for allocatedPool
	//Edit freePool
	
	
	if(getMemoryAddress(targetNode)+getMemorySize(targetNode)==getMemoryAddress(freePool))
	{
		getMemoryAddress(freePool) -= size;
		getMemorySize(freePool) += size;
		free(targetNode);
	}
	else
	{
		freePool =avlAddHeader(freePool,targetNode);
	}
	
	//Done for freePool
}
