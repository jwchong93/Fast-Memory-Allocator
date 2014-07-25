#ifndef customAssert_H
#define customAssert_H

#define TEST_ASSERT_EQUAL_AVL_Node(expectedLeft,expectedRight,balance,actual) \
									assertAVLNode(expectedLeft,expectedRight,balance,actual,__LINE__);

#endif // customAssert_H
