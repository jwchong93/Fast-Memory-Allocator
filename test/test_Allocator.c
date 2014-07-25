#include "unity.h"
#include "Allocator.h"
#include <malloc.h>
#include "AVLAddress.h"
#include "manageAVL.h"
#define TEST
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
	TEST_ASSERT_EQUAL(theMemoryPool,freePool->Header);
	free(theMemoryPool);
	destroyMemory();
	
}
/*
void test_destroyMemory_will_set_the_freePool_and_allocatedPool_back_to_NULL()
{
	initialization ();
	Node dumpData;
	allocatedPool = &dumpData;
	destroyMemory();
	TEST_ASSERT_NULL(freePool);
	TEST_ASSERT_NULL(allocatedPool);
}
*/
void test_allocateMemory_will_add_the_first_location_of_the_memory_pool_into_the_allocated_pool_when_there_do_not_have_any_allocated_data()
{
	
}





