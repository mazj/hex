#include "queue.h"
#include "unittest.h"

int main(int argc, char const *argv[])
{
	TEST_INIT(__FILE__);

	Queue *q = 0;
	assert(q == 0);
	assert(queue_size(q) == 0);
	assert(queue_front(q) == 0);
	assert(queue_back(q) == 0);
	TEST_CHECK();

	q = queue_makeQueue();
	assert(q != 0);
	assert(queue_size(q) == 0);
	assert(queue_front(q) == 0);
	assert(queue_back(q) == 0);
	TEST_CHECK();

	queue_push(q, "3");
	assert(q);
	assert(queue_size(q) == 1);
	assert(queue_front(q) == "3");
	assert(queue_back(q) == "3");
	TEST_CHECK();

	queue_push(q, "2");
	assert(q);
	assert(queue_size(q) == 2);
	assert(queue_front(q) == "3");
	assert(queue_back(q) == "2");
	TEST_CHECK();

	queue_push(q, "1");
	assert(q);
	assert(queue_size(q) == 3);
	assert(queue_front(q) == "3");
	assert(queue_back(q) == "1");
	TEST_CHECK();

	char* c = queue_pop(q);
	assert(q);
	assert(c);
	assert(queue_size(q) == 2);
	assert(queue_front(q) == "2");
	assert(queue_back(q) == "1");
	TEST_CHECK();

	c = queue_pop(q);
	assert(q);
	assert(c);
	assert(queue_size(q) == 1);
	assert(queue_front(q) == "1");
	assert(queue_back(q) == "1");
	TEST_CHECK();

	c = queue_pop(q);
	assert(q);
	assert(c);
	assert(queue_size(q) == 0);
	assert(queue_front(q) == 0);
	assert(queue_back(q) == 0);
	TEST_CHECK();

	free(q);

	TEST_END();
}