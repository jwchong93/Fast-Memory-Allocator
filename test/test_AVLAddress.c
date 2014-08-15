#include "unity.h"
#include "AVLAddress.h"
#include "manageAVL.h"
#include "Allocator.h"
#include "mock_SupportiveFunction.h"

//Define this macro to access to the data without typing alot of type casting.
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

//Since avlAddHeader work according to the rules.
//Done on the macro implementation.


















