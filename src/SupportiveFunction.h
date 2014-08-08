#ifndef SupportiveFunction_H
#define SupportiveFunction_H

#include "Allocator.h"
void* findBlock(int size);
NodeHeader* AVLFindSpace(NodeHeader* root,int data);
#endif // SupportiveFunction_H
