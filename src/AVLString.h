#ifndef AVLString_H
#define AVLString_H
#include "manageAVL.h"
typedef struct NodeString NodeString;

struct NodeString{
  int balance;
  Node *leftChild;
  Node *rightChild;
  char *string;
};

#define avlAddString(root, nodeToAdd) avlAdd((Node *)(root), (Node *)(nodeToAdd), compareString)

int compareString(void *nodeInTree, void *nodeToCompare);
#endif // AVLString_H
