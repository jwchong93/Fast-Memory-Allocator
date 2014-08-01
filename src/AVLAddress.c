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