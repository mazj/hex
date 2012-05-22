#include "assert.h"
#include "unittest.h"

int main(int argc, char const *argv[])
{
	TEST_INIT(__FILE__);

	HEX_ASSERT(1 == 0);

	TEST_END();
	return 0;
}