#include "AVLString.h"
#include <String.h>
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
