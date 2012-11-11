#ifndef _TTable_H_
#define _TTable_H_

#include <stddef.h>
#include "uuid.h"

typedef uuid_t hex_type_id_t;

typedef struct HexTtableEntry {
  hex_type_id_t type_id;
  struct HexType type;
} *TtableEntry;

Ttable ttable_create();

size_t ttable_size();

void* ttable_put(Ttale ttable, TtableEntry entry);

int ttable_remove(Ttable ttable, hex_type_id_t type_id);

TtableEntry ttable_lookup(Ttable ttable, char *type_name);

size_t ttable_bucketcount(Ttable ttable);

int ttable_capacity(Ttable ttable);


#endif /* _TTable_H_ */
