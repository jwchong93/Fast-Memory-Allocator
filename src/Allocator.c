#include "Allocator.h"
#include "manageAVL.h"
#include "stdio.h"
#include <malloc.h>
#include "AVLAddress.h"
#include "SupportiveFunction.h"
#include "CException.h"

/************************************************************************************************
* Initialize the global variables
*
*	Input: none
*	Output: none
*	
*	Global variables affected: freePool, allocatedPool, theMemoryPool
*
*************************************************************************************************/
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

/*************************************************************************************************
* Destroy the data inside the global variables.
*
*	Input: none
*	Output: none
*
*	Destroy: freePool,allocatedPool,theMemoryPool
*	
**************************************************************************************************/
void destroyMemory()
{
	free(theMemoryPool);
	destroyHeaderAVL(freePool);
	// free(freePool);
	freePool=NULL;
	destroyHeaderAVL(allocatedPool);
	// free(allocatedPool);
	allocatedPool = NULL;
}

/***************************************************************************************************
* Allocate certain size of memory from theMemoryPool
*                                                       *******************************************
*	Input: 		size									*size of the memory that going to allocate*
*	Output: 	getMemoryAddress(newAllocatedNode)		*address of the allocated memory          *
*                                                       *******************************************
*	Modify: freePool,allocatedPool
*		
***************************************************************************************************/
void *allocateMemory(int size)
{
	if(size>MEMORY_SIZE||freePool==NULL)
	{
		return NULL;
	}
	void * freeSpace =NULL;
	
	NodeHeader *tempNode=NULL;
	//Handle the allocatedPool first.
	NodeHeader *newAllocatedNode= malloc(sizeof(NodeHeader));
	MemoryBlockHeader *newAllocatedHeader= malloc(sizeof(MemoryBlockHeader));
	
	freeSpace = findBlock(size); //Get the suitable address.
	if(freeSpace==NULL)
	{
		free(newAllocatedHeader);
		free(newAllocatedNode);
		return NULL;
	}
	newAllocatedHeader->address = freeSpace;
	newAllocatedHeader->size = size;
	newAllocatedNode->data = newAllocatedHeader;
	newAllocatedNode->leftChild=NULL;
	newAllocatedNode->rightChild=NULL;
	newAllocatedNode->balance=0;
	
	
	allocatedPool = avlAddHeader(allocatedPool, newAllocatedNode);
	/**
	############################################################################
	#                                                                          #
	#						Done on allocatedPool                              #
	#						                                                   #
	############################################################################
	**/
	
	//Starting on the freePool
	tempNode = findSpace(freePool,size); //Get the respective node.
	if(tempNode==NULL)
	{
		avlRemoveHeader(&allocatedPool, newAllocatedNode);
		free(newAllocatedHeader);
		free(newAllocatedNode);
		return NULL;
	}
	if(getMemorySize(tempNode)>size)
	{
		getMemoryAddress(tempNode) += size;
		getMemorySize(tempNode) -= size;
	}
	else if (getMemorySize(tempNode)==size)
	{
		avlRemoveHeader(&freePool, tempNode);
	}

	/**
	############################################################################
	#                                                                          #
	#						End of editing freePool                            #
	#						                                                   #
	############################################################################
	**/
	return getMemoryAddress(newAllocatedNode);
	
}
/*********************************************************************************
* Deallocate specific memory
*
*	Input: 		memoryLocation		the allocated location
*	Output: 	none
*
*	Modify: freePool,allocatedPool
*	
**********************************************************************************/
void deallocateMemory(void* memoryLocation)
{
	int size = getMemorySize(allocatedPool);
	NodeHeader * newFreePoolNode=NULL;
	NodeHeader * checkNode=NULL;
	if(memoryLocation==NULL)
	{
		return;
	}
	//Edit allocatedPool 
	MemoryBlockHeader tempHeader={.address=memoryLocation};
	NodeHeader tempNode = {.data = &tempHeader};
	newFreePoolNode = avlFindHeader (allocatedPool,&tempNode);
	if(newFreePoolNode==NULL)
	{
		return;
	}
	newFreePoolNode = avlRemoveHeader(&allocatedPool, newFreePoolNode);
	/**
	############################################################################
	#                                                                          #
	#						Done on allocatedPool                              #
	#						                                                   #
	############################################################################
	**/
	
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
			checkNode->leftChild=NULL;
			checkNode->rightChild=NULL;
			newFreePoolNode = mergeMemoryBlock(checkNode,newFreePoolNode);
			if(freePool==NULL)
			{
				break;
			}
			checkNode = avlFindNode(freePool,newFreePoolNode);
				
		}
			newFreePoolNode->balance=0;
			freePool =avlAddHeader(freePool,newFreePoolNode);
	}
	else
	{
			newFreePoolNode->balance=0;
			freePool =avlAddHeader(freePool,newFreePoolNode);
	}
	
	/**
	############################################################################
	#                                                                          #
	#						End of editing freePool                            #
	#						                                                   #
	############################################################################
	**/
}

/********************************************************************************
* Merge two node into one
*
*	Input: 		targetNode,nodeToMerge		two nodes to merge
*	Output: 	targetNode(merged)			merged to the first node
*
*	Destroy: none
*	
********************************************************************************/

NodeHeader *mergeMemoryBlock(NodeHeader*targetNode,NodeHeader *nodeToMerge)
{

	getMemorySize(targetNode)+=getMemorySize(nodeToMerge);
	
	//if(getMemoryAddress(targetNode)>getMemoryAddress(nodeToMerge))
	//{
		getMemoryAddress(targetNode)=getMemoryAddress(nodeToMerge);
//	}
	free(nodeToMerge);
	
	return targetNode;
	
}

/********************************************************************************
* Destroy/Delete an AVL tree which contains header inside
*
*	Input: root			the root of the AVL tree
*	Output: none
*
*	Destroy: none
*	
********************************************************************************/
void destroyHeaderAVL(NodeHeader *root)
{
	if(root==NULL)
	{
		return;
	}
	if(root->leftChild!=NULL)
	{
		destroyHeaderAVL(root->leftChild);
		root->leftChild=NULL;
		if(root->rightChild!=NULL)
		{
			destroyHeaderAVL(root->rightChild);
			root->rightChild=NULL;
		}
	}
	else if(root->rightChild!=NULL)
	{
		destroyHeaderAVL(root->rightChild);
		root->rightChild=NULL;
		if(root->leftChild!=NULL)
		{
			destroyHeaderAVL(root->leftChild);
			root->leftChild=NULL;
		}
	}
	else
	{
	
		free(root->data);
		free(root);
	}
	
}

/*********************************************************************************
* Find a space from the AVL which suitable to allocate certain memory
*
*	Input: root			the root of the AVL tree
			size		size of memory going to allocate
*	Output: tempNode	Contain the address of the suitable memory location
						NULL if there are no suitable location
*
*	Destroy: none
*	
*********************************************************************************/

NodeHeader *findSpace(NodeHeader *root,int size)
{
	NodeHeader *tempNode=NULL;
	if(getMemorySize(root)>=size)
		tempNode=root;
	else if(root->leftChild!=NULL)
	{
		tempNode=findSpace(root->leftChild,size);
		if(tempNode==NULL&&root->rightChild!=NULL)
		{
			tempNode=findSpace(root->rightChild,size);
		}
	}
	else if(root->rightChild!=NULL)
	{
		tempNode=findSpace(root->rightChild,size);
		if(tempNode==NULL&&root->leftChild!=NULL)
		{
			tempNode=findSpace(root->leftChild,size);
		}
	}	
	return tempNode;

}













