#include "Allocator.h"
#include "SupportiveFunction.h"
#include <stdio.h>
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