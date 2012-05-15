/*
 * esb.h
 * Extensible string buffer
 *
 * An extensible string buffer.
 */

#ifndef _ESB_H_
#define _ESB_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

typedef struct hex_esb_s {
    char*  esb_c_str;      	/* pointer to the raw string */
    size_t  esb_capacity;  	/* size of allocated data */
    size_t  esb_size;      	/* amount of space used */
} esb_s;

/* string length taken from string itself. */
void esb_append(esb_s *esb, const char * in_string);

/* The 'len' is believed. Do not pass in strings < len bytes long. */
void esb_appendn(esb_s *esb, const char * in_string, size_t len);

static void
esb_appendn_internal(esb_s *esb, const char * in_string, size_t len);

/* Always returns an empty string or a non-empty string. Never 0. */
char* esb_get_string(esb_s *esb);


/* Sets esb_size to zero. The string is not freed and
   esb_capacity is unchanged.  */
void esb_empty_string(esb_s *esb);


/* Return esb_size. */
size_t esb_string_len(esb_s *esb);

/* The following are for testing esb, not use by dwarfdump. */

/* *data is presumed to contain garbage, not values, and
   is properly initialized. */
void esb_constructor(esb_s *esb);

/*  The string is freed, contents of *data set to zeroes. */
void esb_destructor(esb_s *esb);

/* reverse the string. */
void esb_reverse(esb_s *esb);

/* To get all paths in the code tested, this sets the
   allocation/reallocation to the given value, which can be quite small
   but must not be zero. */
void esb_set_alloc_size(size_t size);
size_t esb_get_allocated_size(esb_s *esb);

/* Append a formatted string */
void esb_append_printf(esb_s *esb, const char *in_string, ...);

#endif // _ESB_H_