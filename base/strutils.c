#include <string.h>
#include <stddef.h>
#include "ctype.h"
#include "esb.h"

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

char*
itoa_fmt(int value, char *str, int base, int capital)
{
	int numDigits = 0;
	int v = value;
  	while(v >= 0) {
  		numDigits++;
    	if(v < 10) {
    		break;
    	} else {
    		v /= 10;
    	}
  	}

	#define BASE_2_LOWER 0
	#define BASE_2_UPPER 1
	#define BASE_8_LOWER 2
	#define BASE_8_UPPER 3
	#define BASE_16_LOWER 4
	#define BASE_16_UPPER 5

	const char* formats[] = {
		[BASE_2_LOWER] = "0b",
		[BASE_2_UPPER] = "0B",
		[BASE_8_LOWER] = "0o",
		[BASE_8_UPPER] = "0O",
		[BASE_16_LOWER] = "0x",
		[BASE_16_UPPER] = "0X"
	};

	if(base == 10) {
		size_t len = value >= 0 ? numDigits+1 : numDigits+2;
		char *ss = (char*)malloc(len);
		snprintf(ss, len, "%d", value);
		str = ss;
		return str;
	}

	if(base == 2|| base == 8 || base == 16) {
		int base_num = 0;
		esb_s buf;
		esb_constructor(&buf);

		int quotient = value;
		int remainder = 0;

        while(quotient != 0) {
        	remainder = quotient % base;
        	quotient /= base;
        	char c[1];
        	sprintf(c, "%d", remainder);
        	esb_append(&buf, c);
        	char *s = esb_get_string(&buf);
        }

        esb_reverse(&buf);

        char *s = esb_get_string(&buf);

		size_t len = strlen(s) + 3;
		if(value < 0) len++;

		char *ss = (char*)malloc(len);
		const char *format;
		if(base == 2 && !capital) format = formats[BASE_2_LOWER];
		if(base == 2 && capital) format = formats[BASE_2_UPPER];
		if(base == 8 && !capital) format = formats[BASE_8_LOWER];
		if(base == 8 && capital) format = formats[BASE_8_UPPER];
		if(base == 16 && !capital) format = formats[BASE_16_LOWER];
		if(base == 16 && capital) format = formats[BASE_16_UPPER];

		if(value >= 0) {
			snprintf(ss, len, "%s%s", format, s);
		} else {
			snprintf(ss, len, "-%s%s", format, s);
		}

		esb_destructor(&buf);

		str = ss;
		return str;
	}

	return 0;
}