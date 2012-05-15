#include <string.h>
#include <stddef.h>
#include "ctype.h"

char*
strtoupper(char* s)
{
	while(s) {
		*s = toupper(*s);
		s++;
	}
	return s;
}

char*
strtolower(char *s)
{
	while(s) {
		*s = tolower(*s);
		s++;
	}
	return s;
}

/*
 * Copies the source to the destination.
 * If the destination length is shorter than the source
 * length, then the destination is re-allocated.
 */
char*
strcpy_hard(char* destination, const char* source)
{
	if(strlen(destination) < strlen(source)) {
		free(destination);
		destination = (char*)malloc(strlen(source) * sizeof(char));
	}
	return strcpy(destination, source);
}

/*
 * Trims whitespaces on the given null-terminated string.
 * The original string is modified and returned.
 */
char*
trim_hard(char * s)
{
	size_t l = strlen(s);
	while(l > 1 && isspace(s[l-1])) s[--l] = '\0';
	while(*s && isspace(*s)) *s = '\0', ++s;
	return s;
}

/*
 * Copy src to string dst of size size.  At most size-1 characters
 * will be copied.  Always NUL terminates (unless size == 0).
 * Returns strlen(src); if retval >= size, truncation occurred.
 */
size_t
strlcpy(char *dst, const char *src, size_t size)
{
	char *d = dst;
	const char *s = src;
	size_t n = size;

	if(n > 0) {
		while(--n != 0) {
			if((*d++ = *s++) == '\0') {
				break;
			}
		}
	}

	if(n == 0) {
		if(size != 0) {
			*d = '\0';
		}
		while(*s++) {
			// do nothing
		}
	}

	return s - src - 1;
}

/*
 * A strcpy which ensures NULL terminated string and never overruns the output.
 */
void
safe_strcpy(char *out, long outlen, const char *in, long inlen)
{
    if(inlen >= (outlen - 1)) {
        strncpy(out, in, outlen - 1);
        out[outlen - 1] = 0;
    } else {
        strcpy(out, in);
    }
}