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

#include "../unittest.h"
#include "../assert.h"
#include "../hashmap.h"
#include "../utils.h"


int simple_hash(char *s) {
  int h = 0;
  int i;

  for(i = 0; i < strlen(s); i++) {
    h = 127 * h + s[i];
  }

  return h;
}

int hashfunc(void *key) {
  RETURN_VAL_IF_NULL(key, 0);
  char *s = (char*)key;
  return simple_hash(s);
}

int keycmpfunc(void *key1, void *key2) {
  return strcmp((char*)key1, (char*)key2) == 0;  
}

#define HASHMAP_INITIAL_CAPACITY 10

typedef struct {
  char *key;
  char *val;
} KeyVal;

KeyVal fruits[] = {
  {"a", "apple"},
  {"b", "banana"},
  {"c", "coconut"}
};

KeyVal sky[] = {
  {"a", "air"},
  {"b", "balloon"},
  {"c", "cloud"}
};

KeyVal vehicles[] = {
  {"a", "airplane"},
  {"b", "boat"},
  {"c", "car"}
};


class HashmapTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _hashmap = hashmap_create(
      HASHMAP_INITIAL_CAPACITY,
      hashfunc,
      keycmpfunc
    );
  }

  virtual void TearDown() {
    if(_hashmap) {
      hashmap_free(&_hashmap);
    }
  }

  Hashmap _hashmap;
};


TEST_F(HashmapTest, HashmapCreateTest) {
  HEX_ASSERT(_hashmap);
  ASSERT_EQ(hashmap_size(_hashmap), 0);
  ASSERT_EQ(
      hashmap_bucketcount(_hashmap),
      8
  );
}

TEST_F(HashmapTest, HashmapPutSingleTest) {
  HEX_ASSERT(_hashmap);

  hashmap_put(_hashmap, fruits[0].key, fruits[0].val);
  hashmap_put(_hashmap, fruits[1].key, fruits[1].val); 
  hashmap_put(_hashmap, fruits[2].key, fruits[2].val);

  ASSERT_EQ(3, hashmap_size(_hashmap));
  ASSERT_EQ(8, hashmap_bucketcount(_hashmap));

  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[0].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[1].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[2].key));

  ASSERT_STREQ(fruits[0].val, (char*)hashmap_get(_hashmap, fruits[0].key));
  ASSERT_STREQ(fruits[1].val, (char*)hashmap_get(_hashmap, fruits[1].key));
  ASSERT_STREQ(fruits[2].val, (char*)hashmap_get(_hashmap, fruits[2].key));

  ASSERT_STREQ(fruits[0].val, (char*)hashmap_remove(_hashmap, fruits[0].key));
  ASSERT_STREQ(fruits[1].val, (char*)hashmap_remove(_hashmap, fruits[1].key));
  ASSERT_STREQ(fruits[2].val, (char*)hashmap_remove(_hashmap, fruits[2].key));

  ASSERT_EQ(0, hashmap_size(_hashmap));
  ASSERT_EQ(6, hashmap_capacity(_hashmap));
}

TEST_F(HashmapTest, HashmapPutMultipleValPerKeyTest) {
  HEX_ASSERT(_hashmap);

  /************ fruits ************/
  hashmap_put(_hashmap, fruits[0].key, fruits[0].val);
  hashmap_put(_hashmap, fruits[1].key, fruits[1].val);
  hashmap_put(_hashmap, fruits[2].key, fruits[2].val);

  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[0].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[1].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[2].key));

  ASSERT_EQ(3, hashmap_size(_hashmap));
  ASSERT_EQ(8, hashmap_bucketcount(_hashmap));

  ASSERT_STREQ(fruits[0].val, (char*)hashmap_get(_hashmap, fruits[0].key));
  ASSERT_STREQ(fruits[1].val, (char*)hashmap_get(_hashmap, fruits[1].key));
  ASSERT_STREQ(fruits[2].val, (char*)hashmap_get(_hashmap, fruits[2].key));

  ASSERT_STREQ(fruits[0].val, (char*)hashmap_remove(_hashmap, fruits[0].key));
  ASSERT_STREQ(fruits[1].val, (char*)hashmap_remove(_hashmap, fruits[1].key));
  ASSERT_STREQ(fruits[2].val, (char*)hashmap_remove(_hashmap, fruits[2].key));
 
  ASSERT_EQ(0, hashmap_size(_hashmap));

  /************* vehicles **************/ 
  hashmap_put(_hashmap, vehicles[0].key, vehicles[0].val);
  hashmap_put(_hashmap, vehicles[1].key, vehicles[1].val);
  hashmap_put(_hashmap, vehicles[2].key, vehicles[2].val);
  
  ASSERT_TRUE(hashmap_contains_key(_hashmap, vehicles[0].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, vehicles[1].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, vehicles[2].key));

  ASSERT_EQ(3, hashmap_size(_hashmap));
  
  ASSERT_STREQ(vehicles[0].val, (char*)hashmap_get(_hashmap, vehicles[0].key));
  ASSERT_STREQ(vehicles[1].val, (char*)hashmap_get(_hashmap, vehicles[1].key));
  ASSERT_STREQ(vehicles[2].val, (char*)hashmap_get(_hashmap, vehicles[2].key));

  ASSERT_STREQ(vehicles[0].val, (char*)hashmap_remove(_hashmap, vehicles[0].key));
  ASSERT_STREQ(vehicles[1].val, (char*)hashmap_remove(_hashmap, vehicles[1].key));
  ASSERT_STREQ(vehicles[2].val, (char*)hashmap_remove(_hashmap, vehicles[2].key));

  ASSERT_EQ(0, hashmap_size(_hashmap));

  /************* sky *****************/
  hashmap_put(_hashmap, sky[0].key, sky[0].val);
  hashmap_put(_hashmap, sky[1].key, sky[1].val);
  hashmap_put(_hashmap, sky[2].key, sky[2].val);

  ASSERT_TRUE(hashmap_contains_key(_hashmap, sky[0].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, sky[1].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, sky[2].key));

  ASSERT_EQ(3, hashmap_size(_hashmap));

  ASSERT_STREQ(sky[0].val, (char*)hashmap_get(_hashmap, sky[0].key));
  ASSERT_STREQ(sky[1].val, (char*)hashmap_get(_hashmap, sky[1].key));
  ASSERT_STREQ(sky[2].val, (char*)hashmap_get(_hashmap, sky[2].key));

  ASSERT_STREQ(sky[0].val, (char*)hashmap_remove(_hashmap, sky[0].key));
  ASSERT_STREQ(sky[1].val, (char*)hashmap_remove(_hashmap, sky[1].key));
  ASSERT_STREQ(sky[2].val, (char*)hashmap_remove(_hashmap, sky[2].key));

  ASSERT_EQ(0, hashmap_size(_hashmap));
}

TEST_F(HashmapTest, TestHashmapGetWithNonExistentKeys) {
  HEX_ASSERT(_hashmap);

  hashmap_put(_hashmap, fruits[0].key, fruits[0].val);
  hashmap_put(_hashmap, fruits[1].key, fruits[1].val);
  hashmap_put(_hashmap, fruits[2].key, fruits[2].val);

  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[0].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[1].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[2].key));

  ASSERT_EQ(3, hashmap_size(_hashmap));
  ASSERT_EQ(8, hashmap_bucketcount(_hashmap));

  ASSERT_STREQ(NULL, (char*)hashmap_get(_hashmap, (char*)"x"));
  ASSERT_STREQ(NULL, (char*)hashmap_get(_hashmap, (char*)"y"));
  ASSERT_STREQ(NULL, (char*)hashmap_get(_hashmap, (char*)"Z"));

  ASSERT_EQ(3, hashmap_size(_hashmap));
}

TEST_F(HashmapTest, TestHashmapFree) {
  HEX_ASSERT(_hashmap);

  hashmap_put(_hashmap, fruits[0].key, fruits[0].val);
  hashmap_put(_hashmap, fruits[1].key, fruits[1].val);
  hashmap_put(_hashmap, fruits[2].key, fruits[2].val);

  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[0].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[1].key));
  ASSERT_TRUE(hashmap_contains_key(_hashmap, fruits[2].key));

  ASSERT_EQ(3, hashmap_size(_hashmap));
  ASSERT_EQ(8, hashmap_bucketcount(_hashmap));

  hashmap_free(&_hashmap);

  ASSERT_EQ(NULL, _hashmap);
}
