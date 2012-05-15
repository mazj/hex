/* Helper functions on null-terminated strings. */

#ifndef _STRNUTILS_H_
#define _STRNUTILS_H_

#include <stddef.h>
#include <string.h>
#include "ctype.h"

/*
 * Converts a string to upper case.
 */
char*
strtoupper(char* c);

/*
 * Converts a string to lower case.
 */
char*
strtolower(char *s);


/*
 * Copies the source to the destination.
 * If the destination length is shorter than the source
 * length, then the destination is re-allocated.
 */
char*
strcpy_hard(char* destination, const char* source);


/*
 * Trims whitespaces on the given null-terminated string.
 * The original string is modified and returned.
 */
char*
trim_hard(char * s);

/*
 * Copy src to string dst of size size.  At most size-1 characters
 * will be copied.  Always NUL terminates (unless size == 0).
 * Returns strlen(src); if retval >= size, truncation occurred.
 */
size_t
strlcpy(char *dst, const char *src, size_t size);


/*
 * A strcpy which ensures NULL terminated string and never overruns the output.
 */
void
safe_strcpy(char *out, long outlen, const char *in, long inlen);


#endif /* _STRNUTILS_H_ */