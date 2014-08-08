#include "AVLAddress.h"
#include "Allocator.h"

int compareHeader(void *nodeInTree, void *nodeToCompare){
  if(getMemoryAddress(nodeInTree) > getMemoryAddress(nodeToCompare))
    return 1;
  else if(getMemoryAddress(nodeInTree) < getMemoryAddress(nodeToCompare))
    return -1;
  else 
    return 0;
}

int compareNode(void *nodeInTree, void *nodeToCompare)
{
	if((getMemoryAddress(nodeInTree)+getMemorySize(nodeInTree)==getMemoryAddress(nodeToCompare))|| \
	(getMemoryAddress(nodeInTree)==getMemoryAddress(nodeToCompare)+getMemorySize(nodeToCompare))|| \
	getMemoryAddress(nodeInTree)==getMemoryAddress(nodeToCompare))
		return 0;
	else if(getMemoryAddress(nodeInTree) < getMemoryAddress(nodeToCompare))
		return -1;
	else if(getMemoryAddress(nodeInTree) > getMemoryAddress(nodeToCompare))
		return 1;
}
