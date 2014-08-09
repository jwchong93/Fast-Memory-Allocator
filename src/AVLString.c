#include "AVLString.h"
#include <String.h>

/**********************************************************************
* Compare the string contain in two node
*
*	Input: nodeInTree		the node inside the AVL tree
*			nodeToCompare	the incoming node that might added to AVL tree
*	Output: 1			indicated string contain in nodeIntree is bigger
*			-1			indicated string contain in nodeToCompare is bigger
*			0			string in both node are the same
*	
*	Destroy: none
*
***********************************************************************/
int compareString(void *nodeInTree, void *nodeToCompare){
  NodeString *node1 = (NodeString *)nodeInTree;
  NodeString *node2 = (NodeString *)nodeToCompare;
  
  if(strcmp(node1->string, node2->string) > 0)
    return 1;
  else if(strcmp(node1->string, node2->string) < 0)
    return -1;
  else if(strcmp(node1->string, node2->string) == 0)
    return 0;
}
