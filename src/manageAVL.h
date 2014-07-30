#ifndef manageAVL_H
#define manageAVL_H



typedef struct node 
{
	int balance;
	struct node*leftChild;
	struct node*rightChild;
	int data;
}Node;
typedef enum error {INVALID_INPUT}Error;

int getHeight(Node *elem);
Node* rightRotate(Node *elem);
Node* leftRotate(Node *elem);
Node* doubleRightRotate(Node *elem);
Node* doubleLeftRotate(Node *elem);
Node * AVLBalance(Node *root);

Node * avlAdd(Node *root,Node *nodeToAdd,int (*compare)(void*,void*));
Node * AVLRemove(Node ** root,Node *nodeToRemove);
Node * AVLFind(Node**,void*data,int(*compare)(Node *node,void *data));
Node * getReplacer(Node ** root);



#endif // manageAVL_H
