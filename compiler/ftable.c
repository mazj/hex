/*
 * HEX Programming Language
 * Copyright (C) 2012  Yanzheng Li
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <errno.h>
#include "../base/memory.h"
#include "../base/assert.h"
#include "../base/utils.h"
#include "../base/strbuf.h"
#include "../base/hash.h"
#include "../base/hashmap.h"
#include "ftable.h"


#define FTABLE_DEFAULT_CAPACITY 10


struct HexFtable {
  Hashmap hashmap;
};

static
inline int _ftable_keycmpfunc(void *key1, void *key2)
{
  HEX_ASSERT(key1);
  HEX_ASSERT(key2);

  char *_key1 = (char*)key1;
  char *_key2 = (char*)key2;

  return strcmp(_key1, _key2) == 0; 
}

static
inline int _ftable_hashfunc(void *key)
{
  HEX_ASSERT(key);
  return (hash_t)hash_str((char*)key);
}

char* ftable_mingle_name(FtableEntry entry)
{
  HEX_ASSERT(entry);
  HEX_ASSERT(entry->name);

  Strbuf strbuf = strbuf_create();
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, (const char*)entry->name);

  ParameterList paramlist = (ParameterList)entry->paramlist;
  while(paramlist) {
    Parameter param = paramlist->parameter;

    HEX_ASSERT(param);
    HEX_ASSERT(param->parameter_name);

    strbuf_append(strbuf, "_");
    strbuf_append(strbuf, (const char*)param->parameter_name);
    strbuf_append(strbuf, "-");

    if(param->type_specifier) {
      char buf[10];
      snprintf(buf, sizeof(buf), "%d", param->type_specifier);
      strbuf_append(strbuf, buf);
    } else {
      strbuf_append(strbuf, (const char*)param->custom_type);
    }

    paramlist = paramlist->next;
  }

  char *mingled_name = strdup(strbuf_cstr(strbuf));

  HEX_ASSERT(mingled_name);

  HEX_FREE(strbuf);

  return mingled_name;
}

Ftable ftable_create()
{
  Hashmap hashmap = hashmap_create(
    FTABLE_DEFAULT_CAPACITY,
    _ftable_hashfunc,
    _ftable_keycmpfunc
  );

  if(!hashmap) {
    errno = ENOMEM;
    return NULL;
  }

  Ftable ftable = HEX_MALLOC(struct HexFtable);

  if(!ftable) {
    errno = ENOMEM;
    hashmap_free(&hashmap);
    return NULL;
  }

  ftable->hashmap = hashmap;
  
  return ftable;
}
 
size_t ftable_size(Ftable ftable)
{
  HEX_ASSERT(ftable);
  return hashmap_size(ftable->hashmap);
}

size_t ftable_capacity(Ftable ftable)
{
  HEX_ASSERT(ftable);
  return hashmap_capacity(ftable->hashmap);
}

FtableEntry ftable_put(
  Ftable ftable,
  char *name,
  hex_type_t return_type,
  void *paramlist)
{
  HEX_ASSERT(ftable);
  HEX_ASSERT(name);

  FtableEntry entry = HEX_MALLOC(struct HexFtableEntry);
  RETURN_VAL_IF_NULL(entry, NULL);

  memset(entry, 0, sizeof(struct HexFtableEntry));

  entry->name = name;
  entry->return_type = return_type;
  entry->paramlist = paramlist;

  entry->mingled_name = ftable_mingle_name(entry);

  return (FtableEntry)hashmap_put(ftable->hashmap, entry->mingled_name, entry);
}

typedef struct HexFtableLookupArg {
  char *mingled_name;
} *FtableLookupArg;

static
int _ftable_lookup(void *key, void *value, void *arg)
{
  HEX_ASSERT(key);
  HEX_ASSERT(arg);

  FtableLookupArg _arg = (FtableLookupArg)arg;
  char *_key = (char*)key;
 
  HEX_ASSERT(_key);
  HEX_ASSERT(_arg->mingled_name);

  return strcmp(_key, _arg->mingled_name) == 0;
}

FtableEntry ftable_lookup(Ftable ftable, char *name, void *paramlist)
{
  HEX_ASSERT(ftable);
  HEX_ASSERT(name);

  FtableEntry _entry = HEX_MALLOC(struct HexFtableEntry);
  HEX_ASSERT(_entry);

  _entry->name = name;
  _entry->paramlist = paramlist;

  char *mingled_name = ftable_mingle_name(_entry);
  HEX_ASSERT(mingled_name);

  struct HexFtableLookupArg arg = {
    .mingled_name = mingled_name
  };

  FtableEntry entry = (FtableEntry)hashmap_lookup(ftable->hashmap, _ftable_lookup, &arg);

  HEX_FREE(mingled_name);

  return entry;
}

static
int _ftable_lookup_by_name(void *key, void *value, void *arg)
{
  HEX_ASSERT(key);
  HEX_ASSERT(arg);

  char *_name = (char*)arg;
  FtableEntry _entry = (FtableEntry)value;

  return strcmp(_name, _entry->name) == 0;
}

FtableEntry ftable_lookup_by_name(Ftable ftable, char *name)
{
  HEX_ASSERT(ftable);
  HEX_ASSERT(name);

  FtableEntry entry = (FtableEntry)hashmap_lookup(
    ftable->hashmap,
    _ftable_lookup_by_name,
    name
  );

  return entry;
}

void ftable_free(Ftable *ftable)
{
  Ftable _ftable = *ftable;

  HEX_ASSERT(_ftable);

  hashmap_free(&_ftable->hashmap);

  HEX_FREE(_ftable);

  *ftable = _ftable;
}
