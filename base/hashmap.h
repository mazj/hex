/* Hashmap */

#ifndef _HASHMAP_H_
#define _HASHMAP_H_

/*
 * Hashmap entry(bucket).
 */
typedef struct HexHashMapEntry_s {
	void *key;
	int hash;
	void *value;
	struct HexHashMapEntry_s *next;
} Entry;

/* hash function */
typedef int (*hash)(void *key) HashFunc;

/* key comparison function */
typedef int (*keycmp)(void *keyA, void *keyB) KeyCmpFunc;

/* hashmap */
typedef struct HexHashmap_s {
	Entry** buckets;
	size_t bucketCount;
	HashFunc hash;
	KeyCmpFunc keycmp;
	mutex_t lock;
	size_t size;
} Hashmap;


Hashmap*
hashmapCreate(size_t initialCapacity,
	HashFunc hashfunc, KeyCmpFunc keycmpfunc);

size_t
hashmapSize(Hashmap *map);

void
hashmapLock(Hashmap *map);

void
hashmapUnlock(Hashmap *map);

void
hashmapFree(Hashmap *map);

int
hashmapHash(void *key, size_t keySize);

void*
hashmapPut(Hashmap *map, void *key, void *value);

void*
hashmapGet(Hashmap *map, void *key);

int
hashmapContainsKey(Hashmap *map, void *key);

void*
hashmapRemove(Hashmap *map, void *key);

void
hashmapIterate(Hashmap *map, int(*callback)(void *key, void *value));

size_t
hashmapCurrentCapacity(Hashmap *map);

size_t
hashmapCountCollisions(Hashmap *map);

int
hashmapIntHash(void *key);

int
hashmapIntEquals(void *keyA, void *keyB);


#endif /* _HASHMAP_H_ */