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

/* Sorted string list */

#ifndef _SORTED_STRING_LIST_H_
#define _SORTED_STRING_LIST_H_

typedef struct HexStl_s *Stl;


Stl stl_create();

size_t stl_size(Stl stl);

void stl_clear(Stl stl);

ints stl_insert(Stl stl, const char *value);

char* stl_find(Stl stl, const char *value);

char* stl_remove(Stl stl, const char *value);


#endif /* _SORTED_STRING_LIST_H_ */