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

//Define some macro to implement the AVL tree program into different cases which require different rule to compare.

#define avlAddHeader(root, nodeToAdd) (NodeHeader*)avlAdd((Node *)(root), (Node *)(nodeToAdd), compareHeader)
#define avlRemoveHeader(root, nodeToRemove) (NodeHeader*)AVLRemove((Node **) (root),(Node *)(nodeToRemove),compareHeader)
#define avlFindHeader(root,data) (NodeHeader*)AVLFind((Node *)(root),(Node *) (data),compareHeader)
#define avlFindNode(root,data) (NodeHeader*)AVLFind((Node *)(root),(Node *) (data),compareNode)

//To compare the address of the node to find out bigger smaller or equal.
int compareHeader(void *nodeInTree, void *nodeToCompare);
//To compare and find out the address that can merge.
int compareNode(void *nodeInTree, void *nodeToCompare);
#endif // AVLAddress_H
