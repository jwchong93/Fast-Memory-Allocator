#include "AVLAddress.h"
#include "Allocator.h"

/**********************************************************************
* Compare the address contain in two node
*
*	Input: nodeInTree		the node inside the AVL tree
*			nodeToCompare	the incoming node that might added to AVL tree
*	Output: 1			indicated address contain in nodeIntree is bigger
*			-1			indicated address contain in nodeToCompare is bigger
*			0			address in both node are the same
*	
*	Destroy: none
*
***********************************************************************/

int compareHeader(void *nodeInTree, void *nodeToCompare){
  if(getMemoryAddress(nodeInTree) > getMemoryAddress(nodeToCompare))
    return 1;
  else if(getMemoryAddress(nodeInTree) < getMemoryAddress(nodeToCompare))
    return -1;
  else 
    return 0;
}

/**********************************************************************
* Compare the address contain in two node whether it is suitable to merge
*
*	Input: nodeInTree		the node inside the AVL tree
*			nodeToCompare	the incoming node that going to merge with suitable node.
*	Output: 1			indicated address contain in nodeIntree is bigger
*			-1			indicated address contain in nodeToCompare is bigger
*			0			address contain in nodeInTree is suitable to merge
*	
*	Destroy: none
*
***********************************************************************/

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
