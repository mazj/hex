/* unit test for map.h */
#include "map.h"
#include "unittest.h"
#include "string.h"

int main(int argc, char const *argv[])
{
	TEST_INIT(__FILE__);

	Map *m = 0;
	assert(m == 0);
	assert(map_size(m) == 0);
	assert(map_head(m) == 0);
	TEST_CHECK();

	m = map_createMap();
	assert(m != 0);
	assert(map_size(m) == 0);
	assert(map_head(m) == 0);
	assert(map_find(m, "key", strcmp) == 0);
	TEST_CHECK();

	BinaryNode* node = map_insert(m, "tomato", "red", strcmp);
	assert(m);
	assert(node);
	assert(map_size(m) == 1);
	assert(map_head(m) == node);
	assert((char*)map_find(m, "tomato", strcmp) == "red");
	TEST_CHECK();

	node = map_insert(m, "potato", "brown", strcmp);
	assert(m);
	assert(node);
	assert(map_size(m) == 2);
	assert(map_head(m) != node);
	assert(map_find(m, "tomato", strcmp) == "red");
	assert(map_find(m, "potato", strcmp) == "brown");
	TEST_CHECK();

	node = map_insert(m, "lettuce", "green", strcmp);
	assert(m);
	assert(node);
	assert(map_size(m) == 3);
	assert(map_head(m) != node);
	assert(map_find(m, "tomato", strcmp) == "red");
	assert(map_find(m, "potato", strcmp) == "brown");
	assert(map_find(m, "lettuce", strcmp) == "green");
	TEST_CHECK();

	node = map_insert(m, "eggplant", "purple", strcmp);
	assert(m);
	assert(node);
	assert(map_size(m) == 4);
	assert(map_head(m) != node);
	assert(map_find(m, "tomato", strcmp) == "red");
	assert(map_find(m, "potato", strcmp) == "brown");
	assert(map_find(m, "lettuce", strcmp) == "green");
	assert(map_find(m, "eggplant", strcmp) == "purple");
	TEST_CHECK();

	free(m);
	TEST_END();
	return 0;
}