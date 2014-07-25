#ifndef AVLAddress_H
#define AVLAddress_H
#include "manageAVL.h"
typedef struct NodeHeader NodeHeader;

struct NodeHeader{
  int balance;
  NodeHeader *leftChild;
  NodeHeader *rightChild;
  void *Header;
};

#define avlAddHeader(root, nodeToAdd) avlAdd((Node *)(root), (Node *)(nodeToAdd), compareHeader)

int compareHeader(void *nodeInTree, void *nodeToCompare);
#endif // AVLAddress_H
