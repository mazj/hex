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

#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <stddef.h>
#include "assert.h"
#include "memory.h"
#include "utils.h"
#include "hashmap.h"


#define LOAD_FACTOR 0.75f


/* Hashmap entry(bucket) */
typedef struct HexHashMapEntry_s {
  void *key;
  int hash;
  void *value;
  struct HexHashMapEntry_s *next;
} Entry;


/* hashmap */
typedef struct HexHashmap_s {
  Entry** buckets;
  size_t bucketCount;
  HashFunc hash;
  KeyCmpFunc keycmp;
  pthread_mutex_t lock;
  size_t size;
} *Hashmap;


Hashmap hashmap_create(size_t initial_capacity,
  HashFunc hashfunc, KeyCmpFunc keycmpfunc)
{
  HEX_ASSERT(hashfunc);
  HEX_ASSERT(keycmpfunc);

  Hashmap hashmap = HEX_MALLOC(struct HexHashmap_s);

  if(!hashmap) {
    errno = ENOMEM;
    return NULL;
  }

  size_t min_bucket_count = initial_capacity * LOAD_FACTOR;

  hashmap->bucketCount = 1;

  while(hashmap->bucketCount <= min_bucket_count) {
    hashmap->bucketCount <<= 1; // bucket count must be power of 2
  }

  hashmap->buckets = calloc(hashmap->bucketCount, sizeof(Entry*));
  if(!hashmap->buckets) {
    HEX_FREE(hashmap);
    return NULL;
  }

  hashmap->size = 0;
  hashmap->hash = hashfunc;
  hashmap->keycmp = keycmpfunc;

  pthread_mutex_init(&hashmap->lock, 0);

  return hashmap;
}

/*
 * Secondary hashing against bad hashses.
 */
static
inline int _hash_key(Hashmap hashmap, void *key)
{
  HEX_ASSERT(hashmap);

  RETURN_VAL_IF_NULL(key, -1);

  int h = hashmap->hash(key);

  h += ~(h << 9);
  h ^= (((unsigned int) h) >> 14);
  h += (h << 4);
  h ^= (((unsigned int) h) >> 10);

  return h;
}

size_t hashmap_size(Hashmap hashmap)
{
  HEX_ASSERT(hashmap);
  return hashmap->size;
}

static
inline size_t _calculate_index(size_t bucketCount, int hash)
{
  return ((size_t)hash) & (bucketCount - 1);
}

static
void _hashmap_expand(Hashmap hashmap)
{
  HEX_ASSERT(hashmap);

  if(hashmap->size > (hashmap->bucketCount * LOAD_FACTOR)) {
    size_t newBucketCount = hashmap->bucketCount << 1;
    Entry **newBuckets = calloc(newBucketCount, sizeof(Entry*));

    RETURN_IF_NULL(newBuckets);

    size_t i;
    for(i = 0; i < hashmap->bucketCount; ++i) {
      Entry *entry = hashmap->buckets[i];
      while(entry) {
        Entry *next = entry->next;
        size_t index = _calculate_index(newBucketCount, entry->hash);
        entry->next = newBuckets[index];
        newBuckets[index] = entry;
        entry = next;
    	}
    }

    HEX_FREE(hashmap->buckets);
    hashmap->buckets = newBuckets;
    hashmap->bucketCount = newBucketCount;
  }
}

void hashmap_lock(Hashmap hashmap)
{
  HEX_ASSERT(hashmap);
  pthread_mutex_lock(&hashmap->lock);
}

void hashmap_unlock(Hashmap hashmap)
{
  HEX_ASSERT(hashmap);
  pthread_mutex_unlock(&hashmap->lock);
}

void hashmap_free(Hashmap hashmap)
{
  HEX_ASSERT(hashmap);

  size_t i;
  for(i = 0; i < hashmap->bucketCount; ++i) {
    Entry *entry = hashmap->buckets[i];
    while(entry) {
      Entry *next = entry->next;
      HEX_FREE(entry);
      entry = next;
    }
  }

  HEX_FREE(hashmap->buckets);
  pthread_mutex_destroy(&hashmap->lock);

  HEX_FREE(hashmap);
}

int hashmap_hash(void *key, size_t key_size)
{
  int h = key_size;
  char *data = (char*)key;

  size_t i;
  for(i = 0; i < key_size; i++) {
    h = h * 31 + *data;
    data++;@
  }

  return h;
}

static
Entry* _create_entry(void *key, int hash, void *val)
{
  Entry *entry = HEX_MALLOC(struct HexHashMapEntry_s);

  if(entry == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  entry->key = key;
  entry->hash = hash;
  entry->value = val;
  entry->next = 0;

  return entry;
}

static
inline int _equals_key(void *keyA, int hashA, void *keyB, int hashB,
  KeyCmpFunc keycmp)
{
  RETURN_VAL_IF_EQUALS(keyA, keyB, 1);
  RETURN_VAL_IF_TRUE(hashA != hashB, 0);

  return keycmp(keyA, keyB);
}

void* hashmap_put(Hashmap hashmap, void *key, void *val)
{
  HEX_ASSERT(hashmap);

  RETURN_VAL_IF_NULL(key, NULL);
  RETURN_VAL_IF_NULL(val, NULL);

  int hash = _hash_key(hashmap, key);
  size_t index = _calculate_index(hashmap->bucketCount, hash);

  Entry **p = &(hashmap->buckets[index]);

  while(1) {
    Entry *current = *p;

    if(!current) {
      *p = _create_entry(key, hash, val);

      if(*p == NULL) {
        errno = ENOMEM;
        return NULL;
      }

      hashmap->size++;
      _hashmap_expand(hashmap);
      return NULL;
    }

    if(_equals_key(
      current->key,
      current->hash,
      key,
      hash,
      hashmap->keycmp)
    ) {
      void *oldValue = current->value;
      current->value = val;
      return oldValue;
    }

    p = &current->next;
  }

  return NULL;
}

void* hashmap_get(Hashmap hashmap, void *key)
{
  HEX_ASSERT(hashmap);

  RETURN_VAL_IF_NULL(key, NULL);

  int hash = _hash_key(hashmap, key);
  int index = _calculate_index(hashmap->bucketCount, hash);

  Entry *entry = hashmap->buckets[index];

  while(entry) {
    if(_equals_key(entry->key, entry->hash, key, hash, hashmap->keycmp))
    {
      return entry->value;
    }
    entry = entry->next;
  }

  return NULL;
}

int
hashmap_contains_key(Hashmap hashmap, void *key)
{
  HEX_ASSERT(hashmap);

  RETURN_VAL_IF_NULL(key, 0);

  int hash = _hash_key(hashmap, key);
  int index = _calculate_index(hashmap->bucketCount, hash);

  Entry *entry = hashmap->buckets[index];

  while(entry) {
    if(_equals_key(entry->key, entry->hash, key, hash, hashmap->keycmp))
    {
      return 1;
    }
    entry = entry->next;
  }

  return 0;
}

void* hashmap_remove(Hashmap hashmap, void *key)
{
  HEX_ASSERT(hashmap);

  RETURN_VAL_IF_NULL(key, NULL);

  int hash = _hash_key(hashmap, key);
  int index = _calculate_index(hashmap->bucketCount, hash);

  Entry **p = &(hashmap->buckets[index]);
  Entry *current = NULL;

  while((current = *p)) {
    if(_equals_key(current->key, current->hash, key, hash, hashmap->keycmp))
    {
      void *value = current->value;

      *p = current->next;
      HEX_FREE(current);
      hashmap->size--;

      return value;
    }

    p = &current->next;
  }

  return NULL;
}

void hashmap_iterate(Hashmap hashmap, int(*callback)(void *key, void *value))
{
  HEX_ASSERT(hashmap);
  HEX_ASSERT(callback);

  size_t i;
  for (i = 0; i < hashmap->bucketCount; i++) {
    Entry* entry = hashmap->buckets[i];
    while(entry != NULL) {
      Entry *next = entry->next;
      if(!callback(entry->key, entry->value)) {
        return;
      }
      entry = next;
    }
  } /* end of for-loop */
}

size_t hashmap_bucketcount(Hashmap hashmap)
{
  HEX_ASSERT(hashmap);

  return hashmap->bucketCount;
}

size_t hashmap_capacity(Hashmap hashmap)
{
  HEX_ASSERT(hashmap);

  size_t bucketCount = hashmap->bucketCount;
  return bucketCount * LOAD_FACTOR;
}

size_t hashmap_count_collisions(Hashmap hashmap)
{
  HEX_ASSERT(hashmap);

  size_t collisions = 0;
  size_t i;

  for(i = 0; i < hashmap->bucketCount; ++i) {
    Entry *entry = hashmap->buckets[i];
    while(entry) {
      if(entry->next) {
        collisions++;
      }
      entry = entry->next;
    }
  }

  return collisions;
}

int hashmap_int_hash(void *key)
{
  HEX_ASSERT(key);
  return DEREF_VOID(int, key);
}

int
hashmap_int_equals(void *keyA, void *keyB)
{
  HEX_ASSERT(keyA);
  HEX_ASSERT(keyB);

  int a = DEREF_VOID(int, keyA);
  int b = DEREF_VOID(int, keyB);

  return a == b;
}

int hashmap_equal(Hashmap hashmap1, Hashmap hashmap2)
{
  HEX_ASSERT(hashmap1);
  HEX_ASSERT(hashmap2);

  if(hashmap_bucketcount(hashmap1) != hashmap_bucketcount(hashmap2)) {
    return 0;
  }

  int i;
  for(i = 0; i < hashmap1->bucketCount; i++) {
    Entry* entry = hashmap1->buckets[i];
    void *key = entry->key;
    while(entry != NULL) {
      Entry *next = entry->next;
      if(hashmap_get(hashmap2, entry->key)==NULL) {
        return 0;
      }
      entry = next;
    }
  } /* end of for-loop */

  for(i = 0; i < hashmap2->bucketCount; i++) {
    Entry* entry = hashmap2->buckets[i];
    void *key = entry->key;
    while(entry != NULL) {
      Entry *next = entry->next;
      if(hashmap_get(hashmap1, entry->key)==NULL) {
        return 0;
      }
      entry = next;
    }
  } /* end of for-loop */

  return 1;
}