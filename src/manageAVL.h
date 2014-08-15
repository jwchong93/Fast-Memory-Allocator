#ifndef manageAVL_H
#define manageAVL_H


//The node that will carry data and children.
typedef struct node 
{
	int balance;
	struct node*leftChild;
	struct node*rightChild;
	int data;
}Node;
typedef enum error {INVALID_INPUT}Error;

/**
#############################################################################
#	To use this program, the following is the guide                         #
#   Step 1: Create a pointer which is pointing to NULL                      #
#   Step 2: Create a node object to store the data                          #
#   Step 3: Add this node to the root using avlAdd                          #
#   Step 4: To Remove use AVLRemove, find use AVLFind                       #
#                                                                           #
#   P/S: Remember to destroy all the node before ending the program         #
#############################################################################
**/
int getHeight(Node *elem);
Node* rightRotate(Node *elem);
Node* leftRotate(Node *elem);
Node* doubleRightRotate(Node *elem);
Node* doubleLeftRotate(Node *elem);
Node * AVLBalance(Node *root);

Node * avlAdd(Node *root,Node *nodeToAdd,int (*compare)(void*,void*));
Node * AVLRemove(Node ** root,Node *nodeToRemove,int(*compare)(void*,void *));
Node * AVLFind(Node *root,Node *data,int(*compare)(void*,void *));
Node * getReplacer(Node ** root);




#endif // manageAVL_H
