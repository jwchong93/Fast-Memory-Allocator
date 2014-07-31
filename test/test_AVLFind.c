#include "unity.h"
#include "manageAVL.h"
#include "customAssert.h"
#include "Allocator.h"
#include "AVLAddress.h"
#include "mock_SupportiveFunction.h"

#define getHeaderAddress(node)	(((MemoryBlockHeader*)(node)->data))

void setUp(void)
{
}

void tearDown(void)
{
}

void test_AVLFind_will_return_the_node_and_remain_the_tree_unchanged()
{
	MemoryBlockHeader testHeader={.address=(void*)100};
	NodeHeader * testRoot=NULL;
	NodeHeader * testRoot1=NULL;
	NodeHeader realData = {.data = &testHeader};
	testRoot = avlAddHeader(testRoot,&realData);
	testRoot1 = avlFindHeader (testRoot,&realData);
	TEST_ASSERT_EQUAL(&realData,testRoot1);
	
}

void test_AVLFind_will_return_the_node_that_being_down_of_tree_and_remain_the_tree_unchanged()
{
	MemoryBlockHeader testHeader1={.address=(void*)25},
	testHeader2={.address=(void*)50},
	testHeader3={.address=(void*)150},
	testHeader4={.address=(void*)200}
		;
		
	NodeHeader * testRoot=NULL;
	NodeHeader * testRoot1=NULL;
	NodeHeader realData1 = {.data = &testHeader1};
	NodeHeader realData2 = {.data = &testHeader2};
	NodeHeader realData3 = {.data = &testHeader3};
	NodeHeader realData4 = {.data = &testHeader4};
	
	testRoot=avlAddHeader(testRoot,&realData1);
	testRoot=avlAddHeader(testRoot,&realData2);
	testRoot=avlAddHeader(testRoot,&realData3);
	testRoot=avlAddHeader(testRoot,&realData4);
	
	testRoot1 = avlFindHeader (testRoot,&realData4);
	TEST_ASSERT_NOT_NULL(testRoot1);
	TEST_ASSERT_EQUAL(&realData4,testRoot1);
}
 /**
 *              175 
 *          /          \ 
 *        100          400 
 *       /   \       /     \
 *     50    150   250     500
 *    / \    /   /    \     / \
 *  25  65 120 200    300 450 550
 *   \          \     / \      \
 *   40         220 270 350    600
 *                      /
 *                    330
 *
 * find 400
 */
 void test_AVLRemove_will_find_400_from_a_very_large_tree()
 {
	MemoryBlockHeader H600={.address=(void*)600},
	H550={.address=(void*)550},
	H450={.address=(void*)450},
	H500={.address=(void*)500},
	H330={.address=(void*)330},
	H350={.address=(void*)350},
	H270={.address=(void*)270},
	H300={.address=(void*)300},
	H220={.address=(void*)220},
	H200={.address=(void*)200},
	H250={.address=(void*)250},
	H120={.address=(void*)120},
	H150={.address=(void*)150},
	H40={.address=(void*)40},
	H65={.address=(void*)65},
	H25={.address=(void*)25},
	H50={.address=(void*)50},
	H400={.address=(void*)400},
	H100={.address=(void*)100},
	H175={.address=(void*)175}
	
	;
	NodeHeader * testRoot=NULL;
	NodeHeader * testRoot1=NULL;
	NodeHeader D600 = {.data = &H600};
	NodeHeader D550 = {.data = &H550};
	NodeHeader D450 = {.data = &H450};
	NodeHeader D500 = {.data = &H500};
	NodeHeader D330 = {.data = &H330};
	NodeHeader D350 = {.data = &H350};
	NodeHeader D270 = {.data = &H270};
	NodeHeader D300 = {.data = &H300};
	NodeHeader D220 = {.data = &H220};
	NodeHeader D200 = {.data = &H200};
	NodeHeader D250 = {.data = &H250};
	NodeHeader D120 = {.data = &H120};
	NodeHeader D150 = {.data = &H150};
	NodeHeader D65 = {.data = &H65};
	NodeHeader D40 = {.data = &H40};
	NodeHeader D25 = {.data = &H25};
	NodeHeader D50 = {.data = &H50};
	NodeHeader D400 = {.data = &H400};
	NodeHeader D100 = {.data = &H100};
	NodeHeader D175 = {.data = &H175};
	
	
	testRoot=avlAddHeader(testRoot,&D175);
	testRoot=avlAddHeader(testRoot,&D100);
	testRoot=avlAddHeader(testRoot,&D400);
	testRoot=avlAddHeader(testRoot,&D50);
	testRoot=avlAddHeader(testRoot,&D150);
	testRoot=avlAddHeader(testRoot,&D250);
	testRoot=avlAddHeader(testRoot,&D500);
	testRoot=avlAddHeader(testRoot,&D25);
	testRoot=avlAddHeader(testRoot,&D65);
	testRoot=avlAddHeader(testRoot,&D120);
	testRoot=avlAddHeader(testRoot,&D200);
	testRoot=avlAddHeader(testRoot,&D300);
	testRoot=avlAddHeader(testRoot,&D450);
	testRoot=avlAddHeader(testRoot,&D550);
	testRoot=avlAddHeader(testRoot,&D40);
	testRoot=avlAddHeader(testRoot,&D220);
	testRoot=avlAddHeader(testRoot,&D270);
	testRoot=avlAddHeader(testRoot,&D350);
	testRoot=avlAddHeader(testRoot,&D600);
	testRoot=avlAddHeader(testRoot,&D330);
	

	TEST_ASSERT_EQUAL(&D175,testRoot);
	TEST_ASSERT_EQUAL_AVL_Node(&D100,&D400,1,testRoot);
	TEST_ASSERT_EQUAL_AVL_Node(&D50,&D150,-1,testRoot->leftChild); //100
	TEST_ASSERT_EQUAL_AVL_Node(&D25,&D65,-1,testRoot->leftChild->leftChild); //50
	TEST_ASSERT_EQUAL_AVL_Node(NULL,&D40,1,testRoot->leftChild->leftChild->leftChild); //25
	TEST_ASSERT_EQUAL_AVL_Node(&D250,&D500,-1,testRoot->rightChild); //400
	TEST_ASSERT_EQUAL_AVL_Node(&D200,&D300,1,testRoot->rightChild->leftChild); //250
	TEST_ASSERT_EQUAL_AVL_Node(NULL,&D220,1,testRoot->rightChild->leftChild->leftChild); //200
	TEST_ASSERT_EQUAL_AVL_Node(&D270,&D350,1,testRoot->rightChild->leftChild->rightChild); //300
	TEST_ASSERT_EQUAL_AVL_Node(&D330,NULL,-1,testRoot->rightChild->leftChild->rightChild->rightChild); //350
	TEST_ASSERT_EQUAL_AVL_Node(&D450,&D550,1,testRoot->rightChild->rightChild); //500
	TEST_ASSERT_EQUAL_AVL_Node(NULL,&D600,1,testRoot->rightChild->rightChild->rightChild); //550

	testRoot1=avlFindHeader(testRoot,&D400);
	TEST_ASSERT_EQUAL(&D400,testRoot1);
	
	TEST_ASSERT_EQUAL(&D175,testRoot);
	TEST_ASSERT_EQUAL_AVL_Node(&D100,&D400,1,testRoot);
	TEST_ASSERT_EQUAL_AVL_Node(&D50,&D150,-1,testRoot->leftChild); //100
	TEST_ASSERT_EQUAL_AVL_Node(&D25,&D65,-1,testRoot->leftChild->leftChild); //50
	TEST_ASSERT_EQUAL_AVL_Node(NULL,&D40,1,testRoot->leftChild->leftChild->leftChild); //25
	TEST_ASSERT_EQUAL_AVL_Node(&D250,&D500,-1,testRoot->rightChild); //400
	TEST_ASSERT_EQUAL_AVL_Node(&D200,&D300,1,testRoot->rightChild->leftChild); //250
	TEST_ASSERT_EQUAL_AVL_Node(NULL,&D220,1,testRoot->rightChild->leftChild->leftChild); //200
	TEST_ASSERT_EQUAL_AVL_Node(&D270,&D350,1,testRoot->rightChild->leftChild->rightChild); //300
	TEST_ASSERT_EQUAL_AVL_Node(&D330,NULL,-1,testRoot->rightChild->leftChild->rightChild->rightChild); //350
	TEST_ASSERT_EQUAL_AVL_Node(&D450,&D550,1,testRoot->rightChild->rightChild); //500
	TEST_ASSERT_EQUAL_AVL_Node(NULL,&D600,1,testRoot->rightChild->rightChild->rightChild); //550
	
 }























