#include "unity.h"
#include "manageAVL.h"
#include "CException.h"
#include "customAssert.h"
#include "AVLInt.h"
void setUp(void)
{
}

void tearDown(void)
{
}
/*
	180
      \
	  150
*/
void test_getReplacer_will_return_right_node_when_there_are_two_nodes()
{
	Node
	N180={.balance=0 ,.leftChild=NULL ,.rightChild=NULL,.data=180},
	N150={.balance=1 ,.leftChild=NULL ,.rightChild=&N180,.data=150}
	;

	Node *testRoot=&N150;
	Node *testNode=NULL;
	testNode=getReplacer(&testRoot);
	TEST_ASSERT_EQUAL(&N180,testNode);
	TEST_ASSERT_EQUAL(0,testRoot->balance);
}

/*
	150
     \
	  150
	   \
	   185
	   remove 185
*/
void test_getReplacer_will_return_right_node_when_there_are_three_nodes()
{
	Node
	N185={.balance=0 ,.leftChild=NULL ,.rightChild=NULL,.data=185},
	N180={.balance=1 ,.leftChild=NULL ,.rightChild=&N185,.data=180},
	N150={.balance=2 ,.leftChild=NULL ,.rightChild=&N180,.data=150}
	;

	Node *testRoot=&N150;
	Node *testNode=NULL;
	//printf("Starting....\n");
	testNode=getReplacer(&testRoot);
	//printf("Ending....\n");
	TEST_ASSERT_EQUAL(&N185,testNode);
	TEST_ASSERT_EQUAL(1,testRoot->balance);
	TEST_ASSERT_EQUAL(0,testRoot->rightChild->balance);
}


void test_getReplacer_will_return_the_root_when_there_are_no_rightChild_or_leftChild()
{
	Node
	N150={.balance=0 ,.leftChild=NULL ,.rightChild=NULL,.data=150}
	;

	Node *testRoot=&N150;
	Node *testNode=NULL;
	testNode=getReplacer(&testRoot);
	TEST_ASSERT_EQUAL(&N150,testNode);
}


void test_getReplacer_will_replace_the_root_with_leftChild_and_return_root_while_there_is_no_rightChild()
{
	Node
	N150={.balance=0 ,.leftChild=NULL ,.rightChild=NULL,.data=150},
	N180={.balance=-1 ,.leftChild=&N150 ,.rightChild=NULL,.data=180}
	;

	Node *testRoot=&N180;
	Node *testNode=NULL;
	testNode=getReplacer(&testRoot);
	TEST_ASSERT_EQUAL(&N180,testNode);
    TEST_ASSERT_EQUAL(&N150,testRoot);
	TEST_ASSERT_EQUAL(0,testRoot->balance);
}

void test_getReplacer_update_the_balance_factor_while_returning_the_node()
{
	Node
	N80={.balance=0 ,.leftChild=NULL ,.rightChild=NULL,.data=80},
	N55={.balance=0 ,.leftChild=NULL ,.rightChild=NULL,.data=55},
	N60={.balance=0 ,.leftChild=&N55 ,.rightChild=&N80,.data=60},
	N40={.balance=0 ,.leftChild=NULL,.rightChild=NULL,.data=40},
	N50={.balance=1 ,.leftChild=&N40,.rightChild=&N60,.data=50},
	N110={.balance=0 ,.leftChild=NULL,.rightChild=NULL,.data=110},
	N100={.balance=-2 ,.leftChild=&N50,.rightChild=&N110,.data=100}
	;

	Node *testRoot=&N100;
	Node *testNode=NULL;
	testNode=getReplacer(&(testRoot->leftChild));
	TEST_ASSERT_EQUAL(&N80,testNode);
	TEST_ASSERT_EQUAL_AVL_Node(&N50,&N110,-2,testRoot);
	TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,testRoot->rightChild);
	TEST_ASSERT_EQUAL_AVL_Node(&N40,&N60,1,testRoot->leftChild);
	TEST_ASSERT_EQUAL_AVL_Node(&N55,NULL,-1,testRoot->leftChild->rightChild);
	
}


void test_getReplacer_will_handle_the_balance_factor_when_the_height_of_the_tree_decreased()
{
	Node
	N55={.balance=0 ,.leftChild=NULL ,.rightChild=NULL,.data=55},
	N60={.balance=-1 ,.leftChild=&N55 ,.rightChild=NULL,.data=60},
	N40={.balance=0 ,.leftChild=NULL,.rightChild=NULL,.data=40},
	N50={.balance=1 ,.leftChild=&N40,.rightChild=&N60,.data=50},
	N110={.balance=0 ,.leftChild=NULL,.rightChild=NULL,.data=110},
	N100={.balance=-2 ,.leftChild=&N50,.rightChild=&N110,.data=100}
	;

	Node *testRoot=&N100;
	Node *testNode=NULL;
	testNode=getReplacer(&(testRoot->leftChild));
	TEST_ASSERT_EQUAL(&N60,testNode);
	TEST_ASSERT_EQUAL_AVL_Node(&N50,&N110,-2,testRoot);
	TEST_ASSERT_EQUAL_AVL_Node(NULL,NULL,0,testRoot->rightChild);
	TEST_ASSERT_EQUAL_AVL_Node(&N40,&N55,0,testRoot->leftChild);
	
}
