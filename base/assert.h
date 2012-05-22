#include <stdio.h>
#include <stdlib.h>

#define HEX_ASSERT(expr)										\
	do {														\
		if(expr == 0) {											\
		   fprintf(stderr, "Assertion %s failed, "				\
		   		"at %s[line %d]\n", #expr, __FILE__, __LINE__);	\
		   abort();												\
		}														\
	} while(0)
