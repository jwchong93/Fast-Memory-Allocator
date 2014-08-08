#include "Allocator.h"
#include "manageAVL.h"
#include "stdio.h"
#include <malloc.h>
#include "AVLAddress.h"
#include "SupportiveFunction.h"
#include "CException.h"

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
	Error e;
	NodeHeader * newNode = malloc(sizeof(NodeHeader));
	MemoryBlockHeader *newHeader= malloc(sizeof(MemoryBlockHeader));
	theMemoryPool = malloc (sizeof(void)*MEMORY_SIZE);
	newHeader->address = theMemoryPool;
	newHeader->size = MEMORY_SIZE;
	newNode->data = newHeader;
	newNode->leftChild=NULL;
	newNode->rightChild=NULL;
	newNode->balance =0;
	
	Try
	{
		freePool =avlAddHeader(freePool,newNode);
	}
	Catch(e)
	{
		printf("Hello, you failed at initialization!.\n");
	}
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
	free(freePool);
	freePool=NULL;
	free(allocatedPool);
	allocatedPool = NULL;
}

//This function in developing, will come back to this after finish deallocate.
//Remark: Throw Error if the theMemoryPool can not support the size that requires to allocate.
MemoryBlockHeader *allocateMemory(int size)
{
	void * freeSpace =NULL;
	Error e;
	
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
	
	
		Try
		{
		allocatedPool = avlAddHeader(allocatedPool, newAllocatedNode);
		}
		Catch(e)
		{
			printf("Hello, you failed at allocateMemory!.\n");
		}
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
	NodeHeader * checkNode=NULL;
	Error e;
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
	checkNode = avlFindNode(freePool,newFreePoolNode);
	if(checkNode!=NULL)
	{
		while(checkNode!=NULL)
		{
			checkNode = avlRemoveHeader(&freePool,checkNode);
			newFreePoolNode = mergeMemoryBlock(checkNode,newFreePoolNode);
			if(freePool==NULL)
			{
				break;
			}
			checkNode = avlFindNode(freePool,newFreePoolNode);
				
		}
		 Try
		{
			freePool =avlAddHeader(freePool,newFreePoolNode);
		}
		Catch(e)
		{
			printf("Hello, you failed at deallocateMemory!.\n");
		}
	}
	else
	{
		Try
		{
		freePool =avlAddHeader(freePool,newFreePoolNode);
		}
		Catch(e)
		{
			printf("Hello, you failed at deallocateMemory!.\n");
		}
	}
	
	//Done for freePool
}


NodeHeader *mergeMemoryBlock(NodeHeader*targetNode,NodeHeader *nodeToMerge)
{
	getMemorySize(targetNode)+=getMemorySize(nodeToMerge);
	if(getMemoryAddress(targetNode)>getMemoryAddress(nodeToMerge))
	{
		getMemoryAddress(targetNode)=getMemoryAddress(nodeToMerge);
	}
	free(nodeToMerge);
	return targetNode;
	
}
