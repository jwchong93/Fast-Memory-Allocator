#ifndef Allocator_H
#define Allocator_H

#include "manageAVL.h"
#include "AVLAddress.h"

//Define the Memory Size for the allocator use.

#define MEMORY_SIZE (500)

/*
	If the user requires bigger size.

	Originally: 	#define MEMORY_SIZE (500)
	Change it to: 	#define MEMORY_SIZE (x)
	
	Where the x = to the size require.
	
	P/S: Please consider the available RAM when define the memory size.
*/

//For easy programming, these macro is been defined.
/*
	Where,
	getMemoryAddress(node) will access to the address in the Header. 
	
	and, 
		the data store in this format: 	*Node* contain *Header*
										*Header* contain *Address*
*/
#define getMemoryAddress(node)	(((MemoryBlockHeader*)((NodeHeader *)(node))->data)->address)
/*

	getMemorySize(node) will access to the Size in the Header. 
	
	and, 
		the data store in this format: 	*Node* contain *Header*
										*Header* contain *Size*
*/

#define getMemorySize(node)	(((MemoryBlockHeader*)((NodeHeader *)(node))->data)->size)
/*
	Where,
	getMemoryAddress(node) will access to the address in the Header. 
	
	and, 
		the data store in this format: 	*Node* contain *Header*
										*Header* contain *Address*
*/

//Define some global variable use internally for the allocator and deallocator.
void *theMemoryPool; 			//All memory is being here and the size is rely on MEMORY_SIZE

NodeHeader *freePool;			//This is an AVL tree, the member of the tree increase when there 
								//are portions of memory free and ready for allocation.


NodeHeader *allocatedPool;		//This is an AVL tree, the member of the tree increase when there 
								//are increasing in the allocated range of memory.


//This is the header that going to store the address and size and handle by the node.
//Lastly, the node will add to the AVL tree.
typedef struct{
	int size;
	void *address;
}MemoryBlockHeader;

/*
########################################################################################################
#	Guide to use this program.                                                                         #
#	Step 1: Simply call the function initialization().                                                 #
#	Step 2: Call the function allocateMemory(size) to allocate certain size.                           #
#			*Remember save the returned address from this function.                                    #
#	Step 3: Use the function deallocateMemory(address) to free the specific address if not needed.     #
#	Step 4: call the function destroyMemory() to kill all the created memory as an ending.             #
########################################################################################################
*/
void initialization ();
void *allocateMemory(int size);
void deallocateMemory(void* memoryLocation);
void destroyHeaderAVL(NodeHeader *root);
NodeHeader *mergeMemoryBlock(NodeHeader *targetNode,NodeHeader *nodeToMerge);
NodeHeader *findSpace(NodeHeader *root,int size);
void destroyMemory();
#endif // Allocator_H
