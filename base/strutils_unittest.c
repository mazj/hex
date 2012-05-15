#include "strnutils.h"
#include "assert.h"

int main(int argc, char const *argv[])
{
	char testString[] = "  test string  ";
	size_t l = strlen(testString);
	char *trimmedString;
	trimmedString = trim_hard(testString);
	assert((l - 4) == strlen(trimmedString));
	return 0;
}