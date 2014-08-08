#include "unity.h"
#include "Allocator.h"
#include <malloc.h>
#include "AVLAddress.h"
#include "manageAVL.h"
#include "SupportiveFunction.h"

void setUp(void)
{
}


void tearDown(void)
{
}

void test_initialization_will_initial_allocatedPool_become_NULL()
{
	
	initialization();
	TEST_ASSERT_NULL(allocatedPool);
	free(theMemoryPool);
	destroyMemory();
}

void test_initialization_will_initial_freePool_to_point_to_the_start_location_of_the_available_memory_pool()
{
	
	initialization();
	TEST_ASSERT_NOT_NULL(freePool);
	TEST_ASSERT_EQUAL(MEMORY_SIZE,getMemorySize(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(freePool));
	free(theMemoryPool);
	destroyMemory();
	
}

void test_allocateMemory_will_add_the_first_location_of_the_memory_pool_into_the_allocated_pool_when_there_do_not_have_any_allocated_data()
{
	initialization();
	//findBlock_ExpectAndReturn (50,theMemoryPool);
	void  *testAllocateData;
	testAllocateData = allocateMemory(50);
	TEST_ASSERT_EQUAL(theMemoryPool,testAllocateData);
	
	// Test the allocatedPool contain node or not.
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_NULL(allocatedPool->rightChild);
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	destroyMemory();
	
}

void test_allocateMemory_will_update_the_freePool_after_data_been_allocated()
{
		
	initialization();
	//findBlock_ExpectAndReturn (50,theMemoryPool);
	void  *testAllocateData;
	testAllocateData = allocateMemory(50);
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE-50,getMemorySize(freePool));
	destroyMemory();
}

void test_allocateMemory_will_update_the_freePool_and_allocatedPool_if_two_range_memory_been_allocated()
{
	
	initialization();
	//findBlock_ExpectAndReturn (50,theMemoryPool);
	void  *testAllocateData;
	testAllocateData = allocateMemory(50);
	
	TEST_ASSERT_EQUAL(theMemoryPool,testAllocateData);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_NULL(allocatedPool->rightChild);
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE-50,getMemorySize(freePool));
	
	//findBlock_ExpectAndReturn (150,theMemoryPool+50);
	testAllocateData = allocateMemory(150);
	//Since 50 +150 memories been allocated.
	TEST_ASSERT_EQUAL(theMemoryPool+200,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE-200,getMemorySize(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(allocatedPool->rightChild));
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	TEST_ASSERT_NULL(allocatedPool->rightChild->leftChild);
	TEST_ASSERT_NULL(allocatedPool->rightChild->rightChild);
	destroyMemory();
}

void test_allocatedMemory_will_update_the_pools_correctly_when_three_part_of_memories_is_been_allocated()
{

	initialization();
	//findBlock_ExpectAndReturn (50,theMemoryPool);
	void  *testAllocateData;
	testAllocateData = allocateMemory(50);
	
	TEST_ASSERT_EQUAL(theMemoryPool,testAllocateData);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_NULL(allocatedPool->rightChild);
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE-50,getMemorySize(freePool));
	
	//findBlock_ExpectAndReturn (150,theMemoryPool+50);
	testAllocateData = allocateMemory(150);
	//Since 50 +150 memories been allocated.
	TEST_ASSERT_EQUAL(theMemoryPool+200,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE-200,getMemorySize(freePool));
	//Check the starting location of the memory allocated.
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(allocatedPool->rightChild));
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	TEST_ASSERT_NULL(allocatedPool->rightChild->leftChild);
	TEST_ASSERT_NULL(allocatedPool->rightChild->rightChild);
	//Check the size of each parts of memories
	TEST_ASSERT_EQUAL(50,getMemorySize(allocatedPool));
	TEST_ASSERT_EQUAL(150,getMemorySize(allocatedPool->rightChild));
	
	
	//findBlock_ExpectAndReturn (200,theMemoryPool+200);
	testAllocateData = allocateMemory(200);
	//Since 50 + 150 + 200 memories been allocated.
	TEST_ASSERT_EQUAL(theMemoryPool+400,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE-400,getMemorySize(freePool));
	//Check the starting location of the memory allocated.
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(allocatedPool));
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool->leftChild));
	TEST_ASSERT_EQUAL(theMemoryPool+200,getMemoryAddress(allocatedPool->rightChild));
	//Check the size of each parts of memories
	TEST_ASSERT_EQUAL(150,getMemorySize(allocatedPool));
	TEST_ASSERT_EQUAL(50,getMemorySize(allocatedPool->leftChild));
	TEST_ASSERT_EQUAL(200,getMemorySize(allocatedPool->rightChild));
	destroyMemory();
}
//allocateMemory test will be added in future.

void test_deallocateMemory_will_remove_the_node_from_the_allocatedPool_and_merge_back_to_the_freePool()
{
	//Allocate some data first........
	initialization();
	//findBlock_ExpectAndReturn (100,theMemoryPool);
	void  *testAllocateData;
	testAllocateData = allocateMemory(100);
	// Start to deallocate it and test the freePool and allocatedPool
	
	deallocateMemory(theMemoryPool);
	
	TEST_ASSERT_NULL(allocatedPool);
	
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(freePool));
	
	TEST_ASSERT_EQUAL(MEMORY_SIZE,getMemorySize(freePool));
	
	destroyMemory();
	
}

void test_deallocateMemory_will_remove_the_node_where_three_parts_of_memory_is_allocated()
{
	//Simply allocate three datas.
	initialization();
	//findBlock_ExpectAndReturn (50,theMemoryPool);
	//findBlock_ExpectAndReturn (100,theMemoryPool+50);
	//findBlock_ExpectAndReturn (150,theMemoryPool+150);
	void  *testAllocateData;
	testAllocateData = allocateMemory(50);
	testAllocateData = allocateMemory(100);
	testAllocateData = allocateMemory(150);
	
	deallocateMemory(theMemoryPool+50);
	
	//The memory with size of 100 which start at theMemoryPool+50 will be deallocated and it will be dissapear.
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_EQUAL(theMemoryPool+150,getMemoryAddress(allocatedPool->rightChild));
	TEST_ASSERT_EQUAL(NULL,allocatedPool->leftChild);
	//Done with the allocated pool , which work as expected.
	//Start to test with the freePool , which the freePool will contain two Node.
	TEST_ASSERT_EQUAL(theMemoryPool+300,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(freePool->leftChild));
	TEST_ASSERT_NULL(freePool->rightChild);
	
	destroyMemory();
	
}

//Since the program for the allocatedPool is just same with the AVLRemove and AVLAdd,
//the testing for the allocatedPool is done in manageAVL.
//The following will start to test the freePool only which requires to merge if the freeNode is connected.

void test_deallocateMemory_will_merge_the_node_when_the_address_is_continuous_downward()
{
	//Simply allocate three datas.
	initialization();
	//findBlock_ExpectAndReturn (50,theMemoryPool);
	//findBlock_ExpectAndReturn (100,theMemoryPool+50);
	//findBlock_ExpectAndReturn (150,theMemoryPool+150);
	void  *testAllocateData;
	testAllocateData = allocateMemory(50);
	testAllocateData = allocateMemory(100);
	testAllocateData = allocateMemory(150);

	/*
	for MEMORY_SIZE=500
	
	|50 |
	|100|
	|150|
	(200)
	
	()freeMemory
	||allocatedMemory
	*/
	
	deallocateMemory(theMemoryPool+50);
	
	/*
	after deallocate
	
	|50 |
	(100)
	|150|
	(200)
	
	()freeMemory
	||allocatedMemory
	*/
	//After one node been deallocated.
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_EQUAL(theMemoryPool+150,getMemoryAddress(allocatedPool->rightChild));
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	TEST_ASSERT_NULL(allocatedPool->rightChild->leftChild);
	TEST_ASSERT_NULL(allocatedPool->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(theMemoryPool+300,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(200,getMemorySize(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(freePool->leftChild));
	TEST_ASSERT_EQUAL(100,getMemorySize(freePool->leftChild));
	TEST_ASSERT_NULL(freePool->rightChild);
	TEST_ASSERT_NULL(freePool->leftChild->rightChild);
	TEST_ASSERT_NULL(freePool->leftChild->leftChild);
	deallocateMemory(theMemoryPool);
	TEST_ASSERT_EQUAL(theMemoryPool+300,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(200,getMemorySize(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(freePool->leftChild));
	TEST_ASSERT_EQUAL(150,getMemorySize(freePool->leftChild));
	TEST_ASSERT_NULL(freePool->rightChild);
	/*
	after deallocate
	
	(50 )         (150)
	(100)   =>    |150|
	|150|         (200)
	(200)
	
	()freeMemory
	||allocatedMemory
	*/
	destroyMemory();
}

void test_deallocateMemory_will_merge_the_node_when_the_address_is_continuous_from_the_top()
{
	//Simply allocate three datas.
	initialization();
	//findBlock_ExpectAndReturn (50,theMemoryPool);
	//findBlock_ExpectAndReturn (100,theMemoryPool+50);
	//findBlock_ExpectAndReturn (150,theMemoryPool+150);
	void  *testAllocateData;
	testAllocateData = allocateMemory(50);
	testAllocateData = allocateMemory(100);
	testAllocateData = allocateMemory(150);

	/*
	for MEMORY_SIZE=500
	
	|50 |
	|100|
	|150|
	(200)
	
	()freeMemory
	||allocatedMemory
	*/
	
	deallocateMemory(theMemoryPool);
	
	/*
	after deallocate
	
	(50 )
	|100|
	|150|
	(200)
	
	()freeMemory
	||allocatedMemory
	*/
	//After one node been deallocated.
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(allocatedPool));
	TEST_ASSERT_EQUAL(theMemoryPool+150,getMemoryAddress(allocatedPool->rightChild));
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	TEST_ASSERT_NULL(allocatedPool->rightChild->leftChild);
	TEST_ASSERT_NULL(allocatedPool->rightChild->rightChild);
	
	TEST_ASSERT_EQUAL(theMemoryPool+300,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(200,getMemorySize(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(freePool->leftChild));
	TEST_ASSERT_EQUAL(50,getMemorySize(freePool->leftChild));
	TEST_ASSERT_NULL(freePool->rightChild);
	TEST_ASSERT_NULL(freePool->leftChild->rightChild);
	TEST_ASSERT_NULL(freePool->leftChild->leftChild);
	deallocateMemory(theMemoryPool+50);
	TEST_ASSERT_EQUAL(theMemoryPool+300,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(200,getMemorySize(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(freePool->leftChild));
	TEST_ASSERT_EQUAL(150,getMemorySize(freePool->leftChild));
	TEST_ASSERT_NULL(freePool->rightChild);
	/*
	after deallocate
	
	(50 )         (150)
	(100)   =>    |150|
	|150|         (200)
	(200)
	
	()freeMemory
	||allocatedMemory
	*/
	destroyMemory();
}

void test_deallocateMemory_will_merge_the_node_when_the_address_is_in_between_of_two_nodes()
{
	//Simply allocate three datas.
	initialization();
	//findBlock_ExpectAndReturn (50,theMemoryPool);
	//findBlock_ExpectAndReturn (100,theMemoryPool+50);
	//findBlock_ExpectAndReturn (150,theMemoryPool+150);
	//findBlock_ExpectAndReturn (50,theMemoryPool+300);
	void  *testAllocateData;
	testAllocateData = allocateMemory(50);
	testAllocateData = allocateMemory(100);
	testAllocateData = allocateMemory(150);
	testAllocateData = allocateMemory(50);

	/*
	for MEMORY_SIZE=500
	
	|50 |
	|100|
	|150|
	|50 |
	(150)
	
	()freeMemory
	||allocatedMemory
	*/
	//Make sure the allocatedPool is follow the AVL pattern
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(allocatedPool));
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool->leftChild));
	TEST_ASSERT_EQUAL(theMemoryPool+150,getMemoryAddress(allocatedPool->rightChild));
	TEST_ASSERT_EQUAL(theMemoryPool+300,getMemoryAddress(allocatedPool->rightChild->rightChild));
	
	TEST_ASSERT_EQUAL(theMemoryPool+350,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(150,getMemorySize(freePool));
	
	//Test plan , deallocate first 50 and 150 and deallocate 100 lastly.
	deallocateMemory(theMemoryPool);
	deallocateMemory(theMemoryPool+150);
	
	//After the two deallocation.
	/*
	for MEMORY_SIZE=500
	
	(50 )
	|100|
	(150)
	|50 |
	(150)
	
	()freeMemory
	||allocatedMemory
	*/
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(allocatedPool));
	TEST_ASSERT_EQUAL(theMemoryPool+300,getMemoryAddress(allocatedPool->rightChild));
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	
	TEST_ASSERT_EQUAL(theMemoryPool+150,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(freePool->leftChild));
	TEST_ASSERT_EQUAL(theMemoryPool+350,getMemoryAddress(freePool->rightChild));
	
	//Test situation ready, going to the real testing part
	deallocateMemory(theMemoryPool+50);
	
	TEST_ASSERT_EQUAL(theMemoryPool+300,getMemoryAddress(allocatedPool));
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	TEST_ASSERT_NULL(allocatedPool->rightChild);
	
	TEST_ASSERT_EQUAL(theMemoryPool+350,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(150,getMemorySize(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(freePool->leftChild));
	TEST_ASSERT_EQUAL(300,getMemorySize(freePool->leftChild));
	TEST_ASSERT_NULL(freePool->rightChild);
	//Deallocated 100
	/*
	for MEMORY_SIZE=500
	
	(300)
	|50 |
	(150)
	
	()freeMemory
	||allocatedMemory
	*/
	
	//Deallocate the last node and make sure the allocatedPool will be NULL
	//freePool will only contain one node with size = MEMORY_SIZE
	deallocateMemory(theMemoryPool+300);
	TEST_ASSERT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE,getMemorySize(freePool));
}

void test_deallocateMemory_and_allocateMemory_at_the_same_time_will_not_affect_the_performance_of_the_allocator()
{
	void * testAllocateData1,
						*testAllocateData2,
						*testAllocateData3,
						*testAllocateData4;
						
	testAllocateData1 = allocateMemory(50);
	testAllocateData2 = allocateMemory(100);
	testAllocateData3 = allocateMemory(150);
	testAllocateData4 = allocateMemory(75);
	
	deallocateMemory(theMemoryPool+50);
	TEST_ASSERT_EQUAL(theMemoryPool+375,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(freePool->leftChild));
	
}






