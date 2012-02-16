#include <stdio.h>
#include "sorted_string_list.h"
#include "assert.h"
#include "time.h"

int main() {
	int i = 0;

	/*
			(head) = 0
	*/
	BinaryNode* head;
	assert(!head);
	assert(!bst_left(head));
	assert(!bst_right(head));
	assert(!bst_value(head));
	assert(bst_empty(head));
	assert(bst_isleafnode(head));
	assert(!bst_isfullnode(head));
	assert(bst_size(head) == 0);
	assert(bst_height(head) == -1);  // fails on zero
	assert(bst_front(head) == 0);
	assert(bst_back(head) == 0);
	assert(!stl_find(head, ""));
	assert(!stl_remove(head, 0, ""));
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 2
	sleep(1);

	/*
			(head->v=0)
			 /        \
			/          \
		   0            0
	*/
	head = bst_create_node();
	assert(head);
	assert(!bst_left(head));
	assert(!bst_right(head));
	assert(!bst_value(head));
	assert(bst_empty(head));
	assert(bst_isleafnode(head));
	assert(!bst_isfullnode(head));
	assert(bst_size(head) == 1);
	assert(bst_height(head) == 0);
	assert(bst_front(head) == 0);
	assert(bst_back(head) == 0);
	assert(!stl_find(head, ""));
	assert(!stl_remove(head, 0, ""));
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 2
	sleep(1);

	/*
			(head->v="abc")
			 /        \
			/          \
		   0            0
	*/
	head->value = "abc";
	assert(head);
	assert(!bst_left(head));
	assert(!bst_right(head));
	assert(bst_value(head));
	assert(bst_empty(head));
	assert(bst_isleafnode(head));
	assert(!bst_isfullnode(head));
	assert(bst_size(head) == 1);
	assert(bst_height(head) == 0);
	assert(strcmp((char*)bst_front(head), (char*)head->value) == 0);
	assert(strcmp((char*)bst_back(head), (char*)head->value) == 0);
	assert(stl_find(head, head->value));
	assert(!stl_remove(head, 0, ""));
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 3
	sleep(1);

	/*
			(head->v="abc")
			 /        \
			/          \
		   0            0
	*/
	BinaryNode* left = 0;
	assert(!stl_insert_node(head, left));
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 4
	sleep(1);

	/*
			(head->v="abc")
			 /        \
			/          \
		 (left->v=0)    0
		  /      \
		 /        \
	    0          0
	*/
	left = bst_create_node();
	head->left = left;
	assert(bst_left(head));
	assert(!bst_right(head));
	assert(bst_value(head));
	assert(!bst_empty(head));
	assert(!bst_isleafnode(head));
	assert(!bst_isfullnode(head));
	assert(bst_size(head) == 2);
	assert(bst_height(head) == 1);
	assert(strcmp((char*)bst_front(head), (char*)head->value) == 0);
	assert(strcmp((char*)bst_back(head), (char*)head->value) == 0);
	assert(stl_find(head, head->value) == head);
	assert(!stl_remove(head, 0, ""));
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 5
	sleep(1);


	/*
			(head->v="abc")
			 /        \
			/          \
		 (left->v=ab)   0
		  /      \
		 /        \
	    0          0
	*/
	BinaryNode* left_node = stl_insert(head, "ab");
	assert(bst_left(head));
	assert(!bst_right(head));
	assert(bst_value(head));
	assert(!bst_empty(head));
	assert(!bst_isleafnode(head));
	assert(!bst_isfullnode(head));
	assert(bst_size(head) == 2);
	assert(bst_height(head) == 1);
	assert(left_node == (BinaryNode*)head->left);
	assert(strcmp((char*)bst_front(head), (char*)bst_left(head)->value) == 0);
	assert(strcmp((char*)bst_back(head), (char*)head->value) == 0);
	assert(stl_find(head, (char*)head->value) == head);
	assert(stl_find(head, bst_left(head)->value) == bst_left(head));
	// assert(!stl_remove(head, 0, ""));
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 6
	sleep(1);

	/*
			(head->v="abc")
			 /           \
			/             \
		 (left->v=ab)   (right->v=ad)
		  /      \        /     \
 		 /        \      /       \
	    0          0    0         0
	*/
	BinaryNode* right = stl_insert(head, "ad");
	assert(bst_left(head));
	assert(bst_right(head));
	assert(bst_value(head));
	assert(bst_value(bst_left(head)));
	assert(bst_value(bst_right(head)));
	assert(!bst_empty(head));
	assert(!bst_isleafnode(head));
	assert(bst_isfullnode(head));
	assert(bst_size(head) == 3);
	assert(bst_height(head) == 1);
	assert(left_node == (BinaryNode*)head->left);
	assert(right == (BinaryNode*)head->right);
	assert(strcmp((char*)bst_front(head), (char*)bst_left(head)->value) == 0);
	assert(strcmp((char*)bst_back(head), (char*)bst_right(head)->value) == 0);
	assert(stl_find(head, (char*)head->value) == head);
	assert(stl_find(head, bst_left(head)->value) == bst_left(head));
	assert(stl_find(head, bst_right(head)->value) == bst_right(head));
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 7
	sleep(1);

	// End of test.
	printf("TEST SUCCESSFUL...\n");
	return 0;
}