#include "Allocator.h"
#include "SupportiveFunction.h"
#include <stdio.h>

/**********************************************************************
* 	Find a suitable memory location from theMemoryPool(global variable)
*	which can fit certain size
*
*	This function rely on AVLFindSpace()
*
*	Input: size								the size of the memory going to be allocated
*	Output: getMemoryAddress(tempNode)		the address that suitable for allocation
*			NULL							There are no suitable location to allocate
*	
*	Destroy: none
*
***********************************************************************/

void* findBlock(int size)
{
	NodeHeader* tempNode=NULL;
	tempNode = AVLFindSpace(freePool,size);
	if(tempNode!=NULL)
	{
		return getMemoryAddress(tempNode);
	}
	else
	{
		return NULL;
	}
	// return theMemoryPool;
}

/**********************************************************************
* Find from the node that which the size is bigger or equal to the input data
*
*	Input: root				the root of the tree
			data			the size that requires.
*	Output: tempNode		the address of a node that contain suitable size for data
*	
*	Destroy: none
*
***********************************************************************/
NodeHeader* AVLFindSpace(NodeHeader* root,int data)
{
	NodeHeader* tempNode=NULL;
	
	if(getMemorySize(root)>=data)
	{
		tempNode=root;
	}
	else if (root->leftChild!=NULL&&getMemorySize(root)<data)
	{
		tempNode = AVLFindSpace(root->leftChild,data);
		if(root->rightChild!=NULL&&tempNode==NULL)
		{
			tempNode = AVLFindSpace(root->rightChild,data);
		}
			
	}
	else if (root->rightChild!=NULL&&getMemorySize(root)<data)
	{
		tempNode = AVLFindSpace(root->rightChild,data);
		if(root->leftChild!=NULL&&tempNode==NULL)
		{
			tempNode = AVLFindSpace(root->leftChild,data);
		}
			
	}

		return tempNode;
}