#include "customAssert.h"
#include "manageAVL.h"
#include "unity.h"
void assertAVLNode(const Node* expectedLeftChild,
					const Node* expectedRightChild,
					const int balanceFactor,
					const Node *actual,
					const UNITY_LINE_TYPE lineNumber)
{

	if(actual==NULL)
		UNITY_TEST_FAIL(lineNumber,"The 'actual' node is NULL.");
	UNITY_TEST_ASSERT_EQUAL_PTR(expectedLeftChild,actual->leftChild,lineNumber,"The leftChild not the same.");
	UNITY_TEST_ASSERT_EQUAL_PTR(expectedRightChild,actual->rightChild,lineNumber,"The rightChild not the same.");
	UNITY_TEST_ASSERT_EQUAL_INT(balanceFactor,actual->balance,lineNumber,"Balance factor not the same.");
}