#include "unittest.h"
#include "stack.h"

int main(int argc, char const *argv[])
{
	TEST_INIT(__FILE__);

	Stack *s = 0;
	assert(s == 0);
	assert(stack_size(s) == 0);
	assert(stack_top(s) == 0);
	TEST_CHECK();

	s = (Stack*)malloc(sizeof(Stack));
	assert(s != 0);
	assert(stack_size(s) == 0);
	assert(stack_top(s) == 0);
	TEST_CHECK();

	stack_push(s, "1");
	assert(s != 0);
	assert(stack_size(s) == 1);
	assert(stack_top(s) == "1");
	TEST_CHECK();

	stack_push(s, "2");
	assert(s != 0);
	assert(stack_size(s) == 2);
	assert(stack_top(s) == "2");
	TEST_CHECK();

	char *v = stack_pop(s);
	assert(s != 0);
	assert(stack_size(s) == 1);
	assert(stack_top(s) == "1");
	assert(v == "2");
	TEST_CHECK();

	v = stack_pop(s);
	assert(s != 0);
	assert(stack_size(s) == 0);
	assert(stack_top(s) == 0);
	assert(v == "1");
	TEST_CHECK();

	v = stack_pop(s);
	assert(s != 0);
	assert(stack_size(s) == 0);
	assert(stack_top(s) == 0);
	assert(v == 0);
	TEST_CHECK();

	free(s);

	// End of test.
	TEST_END();
	return 0;
}