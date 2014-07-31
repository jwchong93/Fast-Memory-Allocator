#ifndef AVLAddress_H
#define AVLAddress_H
#include "manageAVL.h"
typedef struct NodeHeader NodeHeader;

struct NodeHeader{
  int balance;
  NodeHeader *leftChild;
  NodeHeader *rightChild;
  void *data;
};

#define avlAddHeader(root, nodeToAdd) (NodeHeader*)avlAdd((Node *)(root), (Node *)(nodeToAdd), compareHeader)
#define avlRemoveHeader(root, nodeToRemove) (NodeHeader*)AVLRemove((Node **) (root),(Node *)(nodeToRemove),compareHeader)
#define avlFindHeader(root,data) (NodeHeader*)AVLFind((Node *)(root),(Node *) (data),compareHeader)
int compareHeader(void *nodeInTree, void *nodeToCompare);
#endif // AVLAddress_H