#include "AVLInt.h"
#include "manageAVL.h"

/**********************************************************************
* Compare the integer contain in two node
*
*	Input: nodeInTree		the node inside the AVL tree
*			nodeToCompare	the incoming node that might added to AVL tree
*	Output: 1			indicated integer contain in nodeIntree is bigger
*			-1			indicated integer contain in nodeToCompare is bigger
*			0			integer in both node are the same
*	
*	Destroy: none
*
***********************************************************************/

int compareInt(void*nodeInTree,void* nodeToCompare)
{
	Node* nodeA=(Node*)nodeInTree;
	Node* nodeB=(Node*)nodeToCompare;
	if(nodeA->data>nodeB->data)
	{
		return 1;
	}
	else if (nodeA->data<nodeB->data)
	{
		return -1;
	}
	else if (nodeA->data==nodeB->data)
	{
		return 0;
	}
	
}
