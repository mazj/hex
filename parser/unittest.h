/* Unit test macros. */
#ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_

#include <stdio.h>
#include "assert.h"
#include "time.h"



#ifndef TEST_INIT(x)
#define TEST_INIT(x) 					  \
		printf("\nUNIT TEST: %s\n", (x)); \
		int i = 0;
#endif // TEST_INIT(x)

#ifndef TEST_CHECK()
#define TEST_CHECK()					\
		i++;							\
		printf("TEST[%d]: PASS\n", i);	\
		sleep(1);
#endif  // TEST_CHECK()

#ifndef TEST_END()
#define TEST_END()						\
		printf("TEST SUCCESSFUL...\n");
#endif  // TEST_END()

#endif // _UNIT_TEST_H_