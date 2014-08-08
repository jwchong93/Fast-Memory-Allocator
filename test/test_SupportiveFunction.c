#include "unity.h"
#include "SupportiveFunction.h"
#include "Allocator.h"
#include "unity.h"
#include "Allocator.h"
#include <malloc.h>
#include "AVLAddress.h"
#include "manageAVL.h"

void setUp(void)
{
}


void tearDown(void)
{
}

void test_findBlock_will_return_the_first_location_while_there_are_nothing_in_the_allocatedPool()
{
	theMemoryPool=(void*)1000;
	MemoryBlockHeader Memory1 = {.address=theMemoryPool,.size=1000};
	NodeHeader firstNode = {.data=&Memory1};
	freePool = &firstNode;
	void *testSpace = NULL;
	testSpace = findBlock(50);
	TEST_ASSERT_NOT_NULL(testSpace);
	TEST_ASSERT_EQUAL(1000,testSpace);

	
}

void test_findBlock_will_return_the_space_that_suitable_to_fit_the_memory_size()
{
	theMemoryPool=(void*)1000;
	MemoryBlockHeader Memory1 = {.address=theMemoryPool,.size=50},
					Memory2 = {.address=theMemoryPool+150,.size=100};
	NodeHeader firstNode = {.data=&Memory1},
				secondNode = {.data=&Memory2};
				firstNode.rightChild = &secondNode;
	freePool = &firstNode;
	void *testSpace = NULL;
	testSpace = findBlock(100);
	TEST_ASSERT_NOT_NULL(testSpace);
	TEST_ASSERT_EQUAL(theMemoryPool+150,testSpace);
	
}

void test_findBlock_will_return_the_earlier_space_when_there_are_two_suitable_address()
{
	theMemoryPool=(void*)1000;
	MemoryBlockHeader Memory1 = {.address=theMemoryPool,.size=50},
					Memory2 = {.address=theMemoryPool+150,.size=100},
					Memory3 = {.address=theMemoryPool+250,.size=100};
	NodeHeader firstNode = {.data=&Memory1},
				secondNode = {.data=&Memory2},
				thirdNode = {.data=&Memory3};
				firstNode.leftChild = &secondNode;
				firstNode.rightChild = &thirdNode;
	freePool = &firstNode;
	void *testSpace = NULL;
	testSpace = findBlock(100);
	TEST_ASSERT_NOT_NULL(testSpace);
	TEST_ASSERT_EQUAL(theMemoryPool+150,testSpace);
	
}
