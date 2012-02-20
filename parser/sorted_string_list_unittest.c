#include <stdio.h>
#include "sorted_string_list.h"
#include "unittest.h"

int main() {
	TEST_INIT(__FILE__);

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
	TEST_CHECK();

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
	TEST_CHECK();

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
	TEST_CHECK();

	/*
			(head->v="abc")
			 /        \
			/          \
		   0            0
	*/
	BinaryNode* left = 0;
	assert(!stl_insert_node(head, left));
	TEST_CHECK();

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
	TEST_CHECK();


	/*
			(head->v="abc")
			 /        \
			/          \
	   (left->v="ab")   0
		  /      \
		 /        \
	    0          0
	*/
	BinaryNode* left_node = stl_insert(head, "ab");
	assert(left == left_node);
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
	TEST_CHECK();

	/*
				(head->v="abc")
				 /           \
				/             \
		  (left->v="ab")   (right->v="ad")
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
	TEST_CHECK();

	/*
				(head->v="abc")
				 /           \
				/             \
			 (left->v="ab")  (right->v="ad")
			  /      \          /     \
	 		 /        \        /       \
	 	(front->="a")  0      0         0
	 	   /    \
	 	  /      \
	 	 0        0
	*/
	BinaryNode* front = stl_insert(left, "a");
	assert(bst_left(head) == left);
	assert(bst_left(left) == front);
	assert(!bst_right(left));
	assert(bst_value(bst_left(left)));
	assert(!bst_value(bst_right(left)));
	assert(bst_value(front));
	assert(!bst_value(bst_left(front)));
	assert(!bst_value(bst_right(front)));
	assert(!bst_empty(left));
	assert(bst_empty(front));
	assert(bst_empty(right));
	assert(!bst_isleafnode(left));
	assert(bst_isleafnode(front));
	assert(bst_isleafnode(right));
	assert(!bst_isfullnode(left));
	assert(!bst_isfullnode(front));
	assert(!bst_isfullnode(right));
	assert(bst_size(head) == 4);
	assert(bst_size(left) == 2);
	assert(bst_size(right) == 1);
	assert(bst_size(front) == 1);
	assert(bst_height(head) == 2);
	assert(bst_height(left) == 1);
	assert(bst_height(right) == 0);
	assert(bst_height(front) == 0);
	assert(strcmp((char*)bst_front(head), (char*)bst_left(left)->value) == 0);
	assert(strcmp((char*)bst_back(head), (char*)bst_right(head)->value) == 0);
	assert(stl_find(head, (char*)head->value) == head);
	assert(stl_find(head, bst_left(head)->value) == bst_left(head));
	assert(stl_find(head, bst_right(head)->value) == bst_right(head));
	assert(stl_find(left, bst_value(left)) == left);
	assert(stl_find(left, bst_value(left)) == bst_left(head));
	assert(stl_find(left, bst_value(front)) == bst_left(left));
	TEST_CHECK();

	/*
				(head->v="abc")
				 /           \
				/             \
			 (left->v="ab")  (right->v="ad")
			  /      \          /     \
	 		 /        \        /       \
	 	(front->="a")  0      0     (back->="b")
	 	   /    \                      /    \
	 	  /      \                    /      \
	 	 0        0                  0        0
	*/
	BinaryNode* back = stl_insert(head, "b");
	assert(bst_right(head) == right);
	assert(bst_right(right) == back);
	assert(!bst_left(right));
	assert(bst_value(bst_left(left)));
	assert(!bst_value(bst_right(left)));
	assert(!bst_value(bst_left(right)));
	assert(bst_value(bst_right(right)));
	assert(bst_value(front));
	assert(bst_value(back));
	assert(!bst_value(bst_left(front)));
	assert(!bst_value(bst_right(front)));
	assert(!bst_value(bst_left(back)));
	assert(!bst_value(bst_right(back)));
	assert(!bst_empty(left));
	assert(bst_empty(front));
	assert(!bst_empty(right));
	assert(bst_empty(back));
	assert(!bst_isleafnode(left));
	assert(bst_isleafnode(front));
	assert(!bst_isleafnode(right));
	assert(bst_isleafnode(back));
	assert(!bst_isfullnode(left));
	assert(!bst_isfullnode(front));
	assert(!bst_isfullnode(right));
	assert(!bst_isfullnode(back));
	assert(bst_size(head) == 5);
	assert(bst_size(left) == 2);
	assert(bst_size(right) == 2);
	assert(bst_size(front) == 1);
	assert(bst_size(back) == 1);
	assert(bst_height(head) == 2);
	assert(bst_height(left) == 1);
	assert(bst_height(right) == 1);
	assert(bst_height(front) == 0);
	assert(bst_height(back) == 0);
	assert(strcmp((char*)bst_front(head), (char*)bst_left(left)->value) == 0);
	assert(strcmp((char*)bst_back(head), (char*)bst_right(right)->value) == 0);
	assert(stl_find(head, (char*)head->value) == head);
	assert(stl_find(head, bst_left(head)->value) == bst_left(head));
	assert(stl_find(head, bst_right(head)->value) == bst_right(head));
	assert(stl_find(left, bst_value(left)) == left);
	assert(stl_find(left, bst_value(left)) == bst_left(head));
	assert(stl_find(left, bst_value(front)) == bst_left(left));
	assert(stl_find(right, bst_value(right)) == right);
	assert(stl_find(right, bst_value(right)) == bst_right(head));
	assert(stl_find(right, bst_value(back)) == bst_right(right));
	TEST_CHECK();

	Node* list = bst_to_list(head);
	assert(list);
	// printf("%s", (char*)list->value);
	assert(list->value);
	assert(strcmp((char*)(list->value), "a") == 0);
	list = list->next;
	assert(list);
	assert(strcmp((char*)(list->value), "ab") == 0);
	list = list->next;
	assert(list);
	assert(strcmp((char*)(list->value), "abc") == 0);
	list = list->next;
	assert(list);
	assert(strcmp((char*)(list->value), "ad") == 0);
	list = list->next;
	assert(list);
	assert(strcmp((char*)(list->value), "b") == 0);
	TEST_CHECK();

	// End of test.
	TEST_END();
	return 0;
}
