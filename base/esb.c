/*
 * esb.c
 * Extensible string buffer
 *
 * An extensible string buffer.
 */

#include "esb.h"

#define ESB_INITIAL_ALLOC 1024
static size_t esb_alloc_size = ESB_INITIAL_ALLOC;

static void
init_esb_string(esb_s *esb, size_t min_len)
{
    char* d;

    if(esb->esb_capacity > 0)
        return;

    if(min_len < esb_alloc_size)
        min_len = esb_alloc_size;

    d = malloc(min_len);

    if (!d) {
        exit(5);
    }

    esb->esb_c_str = d;
    esb->esb_capacity = min_len;
    esb->esb_c_str[0] = 0;
    esb->esb_size = 0;
}

/*
 * Make more room. Leaving contents unchanged, effectively.
 */
static void
allocate_more(esb_s *esb, size_t len)
{
    size_t new_capacity = esb->esb_capacity + len;
    char* c_str = 0;

    if(new_capacity < esb_alloc_size)
        new_capacity = esb_alloc_size;

    c_str = realloc(esb->esb_c_str, new_capacity);

    if(!c_str) {
        fprintf(stderr, "esb is out of memory re-allocating "
            "%lu bytes\n", (unsigned long)new_capacity);
        exit(EXIT_FAILURE);
    }

    esb->esb_c_str = c_str;
    esb->esb_capacity = new_capacity;
}

static void
esb_appendn_internal(esb_s *esb, const char * in_string, size_t len);

void
esb_appendn(esb_s *esb, const char *in_string, size_t len)
{
    size_t full_len = strlen(in_string);

    if(full_len < len) {
        fprintf(stderr, "esb internal error, bad string length "
            " %lu  < %lu \n",
            (unsigned long) full_len, (unsigned long)len);
        len = full_len;
    }

    esb_appendn_internal(esb, in_string, len);
}

void
esb_append(esb_s *esb, const char *in_string)
{
    size_t len = strlen(in_string);

    esb_appendn_internal(esb, in_string, len);
}

static void
esb_appendn_internal(esb_s *esb, const char *in_string, size_t len)
{
    size_t remaining = 0;
    size_t needed = len + 1;

    if(esb->esb_capacity == 0) {
        size_t maxlen = (len > esb_alloc_size) ? len : esb_alloc_size;
        init_esb_string(esb, maxlen);
    }

    remaining = esb->esb_capacity - esb->esb_size;

    if(remaining < needed) {
        allocate_more(esb, needed);
    }

    strncpy(&esb->esb_c_str[esb->esb_size], in_string, len);
    esb->esb_size += len;

    /* Insist on explicit NUL terminator */
    esb->esb_c_str[esb->esb_size] = 0;
}

char*
esb_get_string(esb_s *esb)
{
    // if(esb->esb_capacity == 0) {
    //     init_esb_string(esb, esb_alloc_size);
    // }
    // return esb->esb_c_str;
    if(!esb) return 0;
    return esb->esb_c_str;
}

void
esb_empty_string(esb_s *esb)
{
    if(!esb) return;
    if(esb->esb_capacity == 0) {
        init_esb_string(esb, esb_alloc_size);
    }
    esb->esb_size = 0;
    esb->esb_c_str[0] = 0;
}

size_t
esb_string_len(esb_s *esb)
{
    return esb->esb_size;
}

void
esb_constructor(esb_s *esb)
{
    memset(esb, 0, sizeof(*esb));
}

void
esb_destructor(esb_s *esb)
{
    if(!esb) return;

    if(esb->esb_c_str) {
        free(esb->esb_c_str);
        esb->esb_c_str = 0;
        esb->esb_size = 0;
        esb->esb_capacity = 0;
    }
}

void
esb_reverse(esb_s *esb)
{
    if(!esb) return;

    char *str = esb_get_string(esb);

    if(!str) return;

    int i = 0;
    int j = strlen(str) - 1;

    while(i < j) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}

void
esb_set_alloc_size(size_t size)
{
    esb_alloc_size = size;
}

size_t
esb_get_allocated_size(esb_s *esb)
{
    if(!esb) return 0;
    return esb->esb_capacity;
}

void
esb_append_printf(esb_s *esb, const char *in_string, ...)
{
    #define NULL_DEVICE_FILE "/dev/null"

    static FILE *null_file = NULL;

    int needed_size = 0;
    int length = 0;
    va_list ap;
    va_start(ap,in_string);
    if (null_file == NULL) {
        null_file = fopen(NULL_DEVICE_FILE,"w");
    }
    length = vfprintf(null_file,in_string,ap);

    /* Check if we require allocate more space */
    needed_size = esb->esb_size + length;
    if (needed_size > esb->esb_capacity) {
        allocate_more(esb,length);
    }
    vsprintf(&esb->esb_c_str[esb->esb_size],in_string,ap);
    esb->esb_size += length;
    va_end(ap);
}