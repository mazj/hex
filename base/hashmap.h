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


/* Hashmap */

#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stddef.h>


typedef struct HexHashmap_s *Hashmap;


/* hash function */
typedef int(*HashFunc)(void *key);


/* key comparison function */
typedef int(*KeyCmpFunc)(void *keyA, void *keyB);


Hashmap hashmap_create(size_t initial_capacity,
  HashFunc hashfunc, KeyCmpFunc keycmpfunc);

size_t hashmap_size(Hashmap hashmap);

void hashmap_lock(Hashmap hashmap);

void hashmap_unlock(Hashmap hashmap);

void hashmap_free(Hashmap hashmap);

int hashmap_hash(void *key, size_t key_size);

void* hashmap_put(Hashmap hashmap, void *key, void *val);

void* hashmap_get(Hashmap hashmap, void *key);

int hashmap_contains_key(Hashmap hashmap, void *key);

void* hashmap_remove(Hashmap hashmap, void *key);

void* hashmap_lookup(Hashmap hashmap, int(*callback)(void *key, void *value, void* arg), void *arg);

void hashmap_iterate(Hashmap hashmap, int(*callback)(void *key, void *value));

size_t hashmap_bucketcount(Hashmap hashmap);

size_t hashmap_capacity(Hashmap hashmap);

size_t hashmap_count_collisions(Hashmap hashmap);

int hashmap_int_hash(void *key);

int hashmap_int_equals(void *keyA, void *keyB);

int hashmap_equal(Hashmap hashmap1, Hashmap hashmap2);


#endif /* _HASHMAP_H_ */