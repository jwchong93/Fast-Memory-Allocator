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
//Remark: Throw Error if the theMemoryPool can not support the size that requires to allocate.
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
	NodeHeader * newFreePoolNode=NULL;
	//Edit allocatedPool 
	MemoryBlockHeader tempHeader={.address=memoryLocation};
	NodeHeader tempNode = {.data = &tempHeader};
	newFreePoolNode = avlFindHeader (allocatedPool,&tempNode);
	newFreePoolNode = avlRemoveHeader(&allocatedPool, newFreePoolNode);
	//Done for allocatedPool
	//Make sure the Node contain no child (Those child already handle by the function)
	newFreePoolNode->leftChild = NULL;
	newFreePoolNode->rightChild = NULL;
	
	//Edit freePool
	if(getMemoryAddress(newFreePoolNode)+getMemorySize(newFreePoolNode)==getMemoryAddress(freePool))
	{
		getMemoryAddress(freePool) -= size;
		getMemorySize(freePool) += size;
		free(newFreePoolNode);
	}
	else
	{
		freePool =avlAddHeader(freePool,newFreePoolNode);
	}
	
	//Done for freePool
}


NodeHeader *mergeMemoryBlock(NodeHeader*targetNode,NodeHeader *nodeToMerge)
{
	if(getMemoryAddress(targetNode)<getMemoryAddress(nodeToMerge))
	{
		getMemorySize(targetNode)+=getMemorySize(nodeToMerge);
		free(nodeToMerge);
		return targetNode;
	}
	else if(getMemoryAddress(targetNode)>getMemoryAddress(nodeToMerge))
	{
		getMemorySize(nodeToMerge)+=getMemorySize(targetNode);
		free(targetNode);
		return nodeToMerge;
	}
	
}
