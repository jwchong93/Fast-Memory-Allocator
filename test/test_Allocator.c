#include "unity.h"
#include "Allocator.h"
#include <malloc.h>
#include "AVLAddress.h"
#include "manageAVL.h"
#include "mock_SupportiveFunction.h"

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
	findBlock_ExpectAndReturn (50,theMemoryPool);
	MemoryBlockHeader *testAllocateData;
	testAllocateData = allocateMemory(50);
	TEST_ASSERT_EQUAL(theMemoryPool,testAllocateData->address);
	TEST_ASSERT_EQUAL(50,testAllocateData->size);
	
	//Test the allocatedPool contain node or not.
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_NULL(allocatedPool->rightChild);
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	destroyMemory();
	
}

void test_allocateMemory_will_update_the_freePool_after_data_been_allocated()
{
	initialization();
	findBlock_ExpectAndReturn (50,theMemoryPool);
	MemoryBlockHeader *testAllocateData;
	testAllocateData = allocateMemory(50);
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE-50,getMemorySize(freePool));
	destroyMemory();
}

void test_allocateMemory_will_update_the_freePool_and_allocatedPool_if_two_range_memory_been_allocated()
{
	initialization();
	findBlock_ExpectAndReturn (50,theMemoryPool);
	MemoryBlockHeader *testAllocateData;
	testAllocateData = allocateMemory(50);
	
	TEST_ASSERT_EQUAL(theMemoryPool,testAllocateData->address);
	TEST_ASSERT_EQUAL(50,testAllocateData->size);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_NULL(allocatedPool->rightChild);
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE-50,getMemorySize(freePool));
	
	findBlock_ExpectAndReturn (150,theMemoryPool+50);
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
	findBlock_ExpectAndReturn (50,theMemoryPool);
	MemoryBlockHeader *testAllocateData;
	testAllocateData = allocateMemory(50);
	
	TEST_ASSERT_EQUAL(theMemoryPool,testAllocateData->address);
	TEST_ASSERT_EQUAL(50,testAllocateData->size);
	
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	TEST_ASSERT_NULL(allocatedPool->rightChild);
	TEST_ASSERT_NULL(allocatedPool->leftChild);
	TEST_ASSERT_EQUAL(theMemoryPool+50,getMemoryAddress(freePool));
	TEST_ASSERT_EQUAL(MEMORY_SIZE-50,getMemorySize(freePool));
	
	findBlock_ExpectAndReturn (150,theMemoryPool+50);
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
	
	
	findBlock_ExpectAndReturn (200,theMemoryPool+200);
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
	findBlock_ExpectAndReturn (100,theMemoryPool);
	MemoryBlockHeader *testAllocateData;
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
	findBlock_ExpectAndReturn (50,theMemoryPool);
	findBlock_ExpectAndReturn (100,theMemoryPool+50);
	findBlock_ExpectAndReturn (150,theMemoryPool+150);
	MemoryBlockHeader *testAllocateData;
	testAllocateData = allocateMemory(50);
	testAllocateData = allocateMemory(100);
	testAllocateData = allocateMemory(150);
	deallocateMemory(theMemoryPool+50);
	//The memory with size of 100 which start at theMemoryPool+50 will be deallocated and it will be dissapear.
	TEST_ASSERT_NOT_NULL(allocatedPool);
	TEST_ASSERT_EQUAL(theMemoryPool,getMemoryAddress(allocatedPool));
	destroyMemory();
}


