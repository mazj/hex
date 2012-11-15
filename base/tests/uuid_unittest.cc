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
#include "../uuid.h"
#include "../assert.h"


/**********************************
 * Test for:
 * int uuid_create(uuid_t*)
 **********************************/
TEST(uuid_createTest, UUIDCreationTest) {
  hex_uuid_t id;

  ASSERT_TRUE(uuid_create(&id));

  ASSERT_GE(id.time_u, 0);
  ASSERT_GE(id.time_l, 0);
  ASSERT_GE(id.time_h, 0);
  ASSERT_GE(id.rand_1, 0);
  ASSERT_GE(id.rand_2, 0);
}


/**********************************
 * Test for:
 * int uuid_compare(hex_uuid_t, hex_uuid_t)
 **********************************/
TEST(uuid_compareTest, UUIDCompareSameIDTest) {
  hex_uuid_t id;
  ASSERT_TRUE(uuid_create(&id));
 
  ASSERT_GE(id.time_u, 0);
  ASSERT_GE(id.time_l, 0);
  ASSERT_GE(id.time_h, 0);
  ASSERT_GE(id.rand_1, 0);
  ASSERT_GE(id.rand_2, 0);

  ASSERT_TRUE(uuid_compare(id, id));
}

TEST(uuid_compareTest, UUIDCompareDifferentIDTest) {
  hex_uuid_t id1;
  hex_uuid_t id2;

  ASSERT_TRUE(uuid_create(&id1));
  ASSERT_TRUE(uuid_create(&id2));

  ASSERT_GE(id1.time_u, 0);
  ASSERT_GE(id1.time_l, 0);
  ASSERT_GE(id1.time_h, 0);
  ASSERT_GE(id1.rand_1, 0);
  ASSERT_GE(id1.rand_2, 0);
  
  ASSERT_GE(id2.time_u, 0);
  ASSERT_GE(id2.time_l, 0);
  ASSERT_GE(id2.time_h, 0);
  ASSERT_GE(id2.rand_1, 0);
  ASSERT_GE(id2.rand_2, 0);

  /* two UUIDs should NOT be the same!!! */
  ASSERT_FALSE(uuid_compare(id1, id2));
}

/****************************************
 * Test for:
 * hash_t uuid_to_hash(const hex_uuid_t)
 ****************************************/
TEST(uuid_to_hashTest, HashOnDifferentUUIDTest1) {
  hex_uuid_t uuid1;
  hex_uuid_t uuid2;

  ASSERT_TRUE(uuid_create(&uuid1));
  ASSERT_TRUE(uuid_create(&uuid2));

  ASSERT_FALSE(uuid_compare(uuid1, uuid2));

  hash_t hash1 = uuid_to_hash((const hex_uuid_t)uuid1);
  hash_t hash2 = uuid_to_hash((const hex_uuid_t)uuid2);

  ASSERT_NE(hash1, hash2);
}

TEST(uuid_to_hashTest, HashOnDifferentUUID_STRESSTest) {
  int i;
  for(i = 0; i < 9999; i++) {
    hex_uuid_t uuid1;
    hex_uuid_t uuid2;

    ASSERT_TRUE(uuid_create(&uuid1));
    ASSERT_TRUE(uuid_create(&uuid2));

    ASSERT_FALSE(uuid_compare(uuid1, uuid2));

    ASSERT_NE(
      uuid_to_hash((const hex_uuid_t)uuid1),
      uuid_to_hash((const hex_uuid_t)uuid2)
    );
  }
}

TEST(uuid_create_and_hashTest, UUIDCreateAndHash_STRESSTest) {
  int i;
  for(i = 0; i < 9999; i++) {
    ASSERT_NE(
      uuid_create_and_hash(),
      uuid_create_and_hash()
    );
  }
}
