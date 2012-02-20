#include "unittest.h"
#include "stack.h"

int main(int argc, char const *argv[])
{
	int i = 0;

	Stack *s = 0;
	assert(s == 0);
	assert(stack_size(s) == 0);
	assert(stack_top(s) == 0);
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 1
	sleep(1);

	s = (Stack*)malloc(sizeof(Stack));
	assert(s != 0);
	assert(stack_size(s) == 0);
	assert(stack_top(s) == 0);
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 2
	sleep(1);

	stack_push(s, "1");
	assert(s != 0);
	assert(stack_size(s) == 1);
	assert(stack_top(s) == "1");
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 3
	sleep(1);

	stack_push(s, "2");
	assert(s != 0);
	assert(stack_size(s) == 2);
	assert(stack_top(s) == "2");
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 4
	sleep(1);

	char *v = stack_pop(s);
	assert(s != 0);
	assert(stack_size(s) == 1);
	assert(stack_top(s) == "1");
	assert(v == "2");
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 5
	sleep(1);

	v = stack_pop(s);
	assert(s != 0);
	assert(stack_size(s) == 0);
	assert(stack_top(s) == 0);
	assert(v == "1");
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 6
	sleep(1);

	v = stack_pop(s);
	assert(s != 0);
	assert(stack_size(s) == 0);
	assert(stack_top(s) == 0);
	assert(v == 0);
	i++;
	printf("TEST[%d]: PASS\n", i);	// TEST 6
	sleep(1);

	// End of test.
	printf("TEST SUCCESSFUL...\n");
	return 0;
}