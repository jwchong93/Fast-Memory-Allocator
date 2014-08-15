#include "unity.h"
#include "Allocator.h"
#include "manageAVL.h"
#include "AVLAddress.h"
#include "SupportiveFunction.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_avlFindNode_will_find_the_element_that_being_in_front_of_the_target_node()
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
	
	
	//since realData3 contain address of 600, then the node returned should end in 600
	TEST_ASSERT_NOT_NULL(testRoot1);
	TEST_ASSERT_EQUAL((void*)500,getMemoryAddress(testRoot1));
	TEST_ASSERT_EQUAL(100,getMemorySize(testRoot1));
	//start location = 500 + 100(size)=600
	//returned a correct node.
}


void test_avlFindNode_will_find_the_element_that_being_back_of_the_target_node()
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
	
	//since realData3 contain address of 600 and end in 750, node that contain 600 as end or 750 as start should be returned.
	TEST_ASSERT_NOT_NULL(testRoot1);
	TEST_ASSERT_EQUAL(750,getMemoryAddress(testRoot1));
	TEST_ASSERT_EQUAL(200,getMemorySize(testRoot1));
	//start location = 750
	//where this node can merge with the realData3
}


void test_mergeMemoryBlock_will_merge_two_nodes_into_one_for_the_first_node_address_is_smaller_than_the_second_node()
{
	MemoryBlockHeader testHeader1={.address=(void*)300,.size=200};
	MemoryBlockHeader testHeader2={.address=(void*)500,.size=100};
	NodeHeader * testRoot=NULL;
	NodeHeader * testRoot1=NULL;
	NodeHeader realData1 = {.data = &testHeader1};
	NodeHeader realData2 = {.data = &testHeader2};
	testRoot1 = mergeMemoryBlock(&realData1,&realData2);
	TEST_ASSERT_NOT_NULL(testRoot1);
	//address should start with the smaller one.
	TEST_ASSERT_EQUAL(300,getMemoryAddress(testRoot1));
	//size = 200+100
	TEST_ASSERT_EQUAL(300,getMemorySize(testRoot1));
}

void test_mergeMemoryBlock_will_merge_two_nodes_into_one_for_the_first_node_address_is_bigger_than_the_second_node()
{
	MemoryBlockHeader testHeader1={.address=(void*)500,.size=100};
	MemoryBlockHeader testHeader2={.address=(void*)300,.size=200};
	NodeHeader * testRoot=NULL;
	NodeHeader * testRoot1=NULL;
	NodeHeader realData1 = {.data = &testHeader1};
	NodeHeader realData2 = {.data = &testHeader2};
	testRoot1 = mergeMemoryBlock(&realData1,&realData2);
	TEST_ASSERT_NOT_NULL(testRoot1);
	//address should start with the smaller one.
	TEST_ASSERT_EQUAL(300,getMemoryAddress(testRoot1));
	//size = 200+100
	TEST_ASSERT_EQUAL(300,getMemorySize(testRoot1));
}

