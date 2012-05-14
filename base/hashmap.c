typedef struct HexHashMapEntry_s {
	void *key;
	int hash;
	void *value;
	struct HexHashMapEntry_s *next;
} Entry;

typedef int (*hash)(void *key) HashFunc;
typedef int (*equal)(void *keyA, void *keyB) EqualFunc;

typedef struct HexHashmap_s {
	Entry** buckets;
	size_t bucketCount;
	HashFunc hash;
	EqualFunc equal;
	mutex_t lock;
	size_t size;
} Hashmap;

#define LOAD_FACTOR 0.75f

Hashmap*
hashmapCreate(size_t initialCapacity, HashFunc hashfunc, EqualFunc equalfunc)
{
	assert(hashfunc);
	assert(equalfunc);

	Hashmap *map = MALLOC(Hashmap);
	if(!map) {
		return 0;
	}

	size_t minimumBucketCount = initialCapacity * LOAD_FACTOR;
	map->bucketCount = 1;
	while(map->bucketCount <= minimumBucketCount) {
		// bucket count must be power of 2
		map->bucketCount <<= 1;
	}

	map->buckets = calloc(map->bucketCount, sizeof(Entry*));
	if(!map->buckets) {
		free(map);
		return 0;
	}

	map->size = 0;
	map->hash = hashfunc;
	map->equal = equalfunc;

	mutex_init(&map->lock);

	return map;
}

static inline int
hashKey(Hashmap *map, void *key)
{
	int h = map->hash(key);

	h += ~(h << 9);
    h ^= (((unsigned int) h) >> 14);
    h += (h << 4);
    h ^= (((unsigned int) h) >> 10);

    return h;
}

size_t
hashmapSize(Hashmap *map)
{
	return map->size;
}

static inline size_t
_calculateIndex(size_t bucketCount, int hash)
{
	return ((size_t)hash) & (bucketCount - 1);
}

static void
_expand(Hashmap *map)
{
	if(map->size > (map->bucketCount * LOAD_FACTOR)) {
		size_t newBucketCount = map->bucketCount << 1;
		Entry **newBuckets = calloc(newBucketCount, sizeof(Entry*));
		if(!newBuckets) {
			return;
		}

		size_t i;
		for(i = 0; i < map->bucketCount; ++i) {
			Entry *entry = map->buckets[i];
			while(entry) {
				Entry *next = entry->next;
				size_t index = _calculateIndex(newBucketCount, entry->hash);
				entry->next = newBuckets[index];
				newBuckets[index] = entry;
				entry = next;
			}
		}

		free(map->buckets);
		map->buckets = newBuckets;
		map->bucketCount = newBucketCount;
	}
}

void
hashmapLock(Hashmap *map)
{
	assert(map);
	mutex_lock(&map->lock);
}

void
hashmapUnlock(Hashmap *map)
{
	mutex_unlock(&map->lock);
}

void
hashmapFree(Hashmap *map)
{
	size_t i;
	for(i = 0; i < map->bucketCount; ++i) {
		Entry *entry = map->buckets[i];
		while(entry) {
			Entry *next = entry->next;
			free(entry);
			entry = next;
		}
	}
	free(map->buckets);
	mutex_destroy(&map->lock);
	free(map);
}

int
hashmapHash(void *key, size_t keySize)
{
	int h = keySize;
	char *data = (char*)key;
	size_t i;
	for(i = 0; i < keySize; i++) {
		h = h * 31 + *data;
		data++;
	}
	return h;
}

static Entry*
_createEntry(void *key, int hash, void *value)
{
	Entry *entry = MALLOC(sizeof(Entry));
	if(!entry) {
		return 0;
	}
	entry->key = key;
	entry->hash = hash;
	entry->value = value;
	entry->next = 0;
	return entry;
}

static inline int
equalsKey(void *keyA, int hashA, void *keyB, int hashB, EqualFunc equal)
{
	if(keyA == keyB) {
		return 1;
	}
	if(hashA != hashB) {
		return 0;
	}
	return equal(keyA, keyB);
}

void*
hashmapPut(Hashmap *map, void *key, void *value)
{
	int hash = hashkey(map, key);
	size_t index = _calculateIndex(map->bucketCount, hash);

	Entry **p = &(map->buckets[index]);
	while(1) {
		Entry *current = *p;

		if(!current) {
			*p = createEntry(key, hash, value);
			if(*p == NULL) {
				return NULL;
			}
			map->size++;
			_expand(map);
			return NULL:
		}

		if(equalKeys(current->key, current->hash,
			key, hash, map->equal)) {
			void *oldValue = current->value;
			current->value = value;
			return oldValue;
		}

		p = &current->next;
	}
}

void*
hashmapGet(Hashmap *map, void *key)
{
	int hash = hashKey(map, key);
	int index = _calculateIndex(map->bucketCount, hash);

	Entry *entry = map->buckets[index];
	while(entry) {
		if(equalsKey(entry->key, entry->hash, key, hash, map->equal)) {
			return entry->value;
		}
		entry = entry->next;
	}

	return NULL;
}

int
hashmapContainsKey(Hashmap *map, void *key)
{
	int hash = hashKey(map, key);
	int index = _calculateIndex(map->bucketCount, hash);

	Entry *entry = map->buckets[index];
	while(entry) {
		if(equalsKey(entry->key, entry->hash, key, hash, map->equal)) {
			return 1;
		}
		entry = entry->next;
	}

	return 0;
}

void*
hashmapRemove(Hashmap *map, void *key)
{
	int hash = hashKey(map, key);
	int index = _calculateIndex(map->bucketCount, hash);

	Entry **p = &(map->buckets[index]);
	Entry *current;
	while((current = *p)) {
		if(equalsKey(current->key, current->hash, key, hash, map->equal))
		{
			void *value = current->value;
			*p = current->next;
			free(current);
			map->size--;
			return value;
		}

		p = &current->next;
	}

	return NULL;
}

size_t
hashmapCurrentCapacity(Hashmap *map)
{
	size_t bucketCount = map->bucketCount;
	return bucketCount * LOAD_FACTOR;
}

size_t
hashmapCountCollisions(Hashmap *map)
{
	size_t collisions = 0;
	size_t i;
	for(i = 0; i < map->bucketCount; ++i) {
		Entry *entry = map->buckets[i];
		while(entry) {
			if(entry->next) {
				collisions++;
			}
			entry = entry->next;
		}
	}

	return collisions;
}

int
hashmapIntHash(void *key)
{
	return DEREF_VOID(key, int);
}

int
hashmapIntEquals(void *keyA, void *keyB)
{
	int a = DEREF_VOID(keyA, int);
	int b = DEREF_VOID(keyB, int);
	return a == b;
}