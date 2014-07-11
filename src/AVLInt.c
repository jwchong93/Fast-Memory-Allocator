#include "AVLInt.h"
#include "manageAVL.h"

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
