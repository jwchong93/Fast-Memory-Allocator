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

//Define some macro to implement the AVL tree program into different cases.
#define avlAddHeader(root, nodeToAdd) (NodeHeader*)avlAdd((Node *)(root), (Node *)(nodeToAdd), compareHeader)
#define avlRemoveHeader(root, nodeToRemove) (NodeHeader*)AVLRemove((Node **) (root),(Node *)(nodeToRemove),compareHeader)
#define avlFindHeader(root,data) (NodeHeader*)AVLFind((Node *)(root),(Node *) (data),compareHeader)
#define avlFindNode(root,data) (NodeHeader*)AVLFind((Node *)(root),(Node *) (data),compareNode)

int compareHeader(void *nodeInTree, void *nodeToCompare);
int compareNode(void *nodeInTree, void *nodeToCompare);
#endif // AVLAddress_H
