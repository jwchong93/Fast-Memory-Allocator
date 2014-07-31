#ifndef AVLInt_H
#define AVLInt_H

#define avlAddInt(root,nodeToAdd) avlAdd(root,nodeToAdd,compareInt)

#define avlRemoveInt(root, nodeToRemove) AVLRemove((Node **) (root),(Node *)(nodeToRemove),compareInt)
int compareInt(void*nodeInTree,void* nodeToCompare);
#endif // AVLInt_H
