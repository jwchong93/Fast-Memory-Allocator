#ifndef Allocator_H
#define Allocator_H

typedef struct{
	int size;
	#ifdef TEST
	void *address;
	#endif
	int block[0];
}MemoryBlockHeader;

MemoryBlockHeader *allocateMemory(int size);
#endif // Allocator_H
