#include "unity.h"
#include "AVLAddress.h"
#include "manageAVL.h"
#include "Allocator.h"
#include "mock_SupportiveFunction.h"

#define getHeaderAddress(node)	(((MemoryBlockHeader*)(node)->data))

void setUp(void)
{
}

void tearDown(void)
{
}

void test_avlAddHeader_will_add_a_new_element_into_the_root(void)
{
	MemoryBlockHeader testHeader={.address=(void*)100};
	NodeHeader * testRoot=NULL;
	NodeHeader realData = {.data = &testHeader};
	testRoot = avlAddHeader(testRoot,&realData);
	TEST_ASSERT_EQUAL(&realData,testRoot);
	TEST_ASSERT_EQUAL(&testHeader,getHeaderAddress(testRoot) );
}

void test_avlAddHeader_will_add_a_new_element_into_the_rightChild_of_the_root(void)
{
	MemoryBlockHeader testHeader1={.address=(void*)100};
	MemoryBlockHeader testHeader2={.address=(void*)200};
	NodeHeader * testRoot=NULL;
	NodeHeader realData1 = {.data = &testHeader1};
	NodeHeader realData2 = {.data = &testHeader2};
	testRoot = avlAddHeader(testRoot,&realData1);
	TEST_ASSERT_EQUAL(&realData1,testRoot);
	TEST_ASSERT_EQUAL(&testHeader1,getHeaderAddress(testRoot));
	testRoot = avlAddHeader(testRoot,&realData2);
	TEST_ASSERT_EQUAL(&realData2,testRoot->rightChild);
	TEST_ASSERT_EQUAL(&testHeader2,getHeaderAddress(testRoot->rightChild));
}


void test_avlFindNode_will_find_the_element_that_being_in_front_of_the_node()
{
	MemoryBlockHeader testHeader1={.address=(void*)100,.size=200};
	MemoryBlockHeader testHeader2={.address=(void*)500,.size=100};
	MemoryBlockHeader testHeader3={.address=(void*)600,.size=150};
	NodeHeader * testRoot=NULL;
	NodeHeader * testRoot1=NULL;
	NodeHeader realData1 = {.data = &testHeader1};
	NodeHeader realData2 = {.data = &testHeader2};
	NodeHeader realData3 = {.data = &testHeader3};
	testRoot = avlAddHeader(testRoot,&realData1);
	testRoot = avlAddHeader(testRoot,&realData2);
	
	
	testRoot1 = avlFindNode(testRoot,&realData3);
	
	
	TEST_ASSERT_NOT_NULL(testRoot1);
	TEST_ASSERT_EQUAL((void*)500,getMemoryAddress(testRoot1));
	TEST_ASSERT_EQUAL(100,getMemorySize(testRoot1));
}


void test_avlFindNode_will_find_the_element_that_being_back_of_the_node()
{
	MemoryBlockHeader testHeader1={.address=(void*)750,.size=200};
	MemoryBlockHeader testHeader2={.address=(void*)500,.size=100};
	MemoryBlockHeader testHeader3={.address=(void*)600,.size=150};
	NodeHeader * testRoot=NULL;
	NodeHeader * testRoot1=NULL;
	NodeHeader realData1 = {.data = &testHeader1};
	NodeHeader realData2 = {.data = &testHeader2};
	NodeHeader realData3 = {.data = &testHeader3};
	testRoot = avlAddHeader(testRoot,&realData1);
	testRoot = avlAddHeader(testRoot,&realData2);
	
	
	testRoot1 = avlFindNode(testRoot,&realData3);
	
	
	TEST_ASSERT_NOT_NULL(testRoot1);
	TEST_ASSERT_EQUAL((void*)750,getMemoryAddress(testRoot1));
	TEST_ASSERT_EQUAL(200,getMemorySize(testRoot1));
}


















