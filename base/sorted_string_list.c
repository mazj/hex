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
#include "assert.h"
#include "memory.h"
#include "bst.h"

struct HexStl_s {
  Bst bst;
};


Stl stl_create()
{
  Stl stl = HEX_MALLOC(struct HexStl_s);

  if(stl == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  Bst bst = bst_create();

  if(bst == NULL) {
    errno = ENOMEM;
    HEX_FREE(bst);
    return NULL;
  }

  stil->bst = bst;

  return stl;
}

size_t stl_size(Stl stl)
{
  HEX_ASSERT(stl);

  return bst_size(stl->bst);
}

void stl_clear(Stl stl)
{
  HEX_ASSERT(stl);
  //bst_clear(stl->bst);
}

int
stl_insert(Stl stl, const char *value)
{
  HEX_ASSERT(stl);
  HEX_ASSERT(value);

  return bst_insert(stl->bst, value, strlen(value), strcmp);
}

char*
stl_find(Stl stl, const char *value)
{
  HEX_ASSERT(stl);
  HEX_ASSERT(value);

  return (char*)bst_find(stl->bst, value, strcmp);
}

char*
stl_remove(Stl stl, const char* value)
{
  HEX_ASSERT(stl);
  HEX_ASSERT(value);

  return (char*)bst_remove(stl->bst, value, strcmp);
}