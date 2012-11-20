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

#include "../../base/unittest.h"
#include "../../base/assert.h"
#include "../../base/utils.h"
#include "../vtable.h"


class VtableTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _vtable = vtable_create();
  }

  virtual void TearDown() {
    vtable_free(&_vtable);
  }

  Vtable _vtable;
};


TEST_F(VtableTest, VtableCreationTest) {
  HEX_ASSERT(_vtable);
  ASSERT_EQ(0, vtable_size(_vtable));
  ASSERT_LE(0, vtable_capacity(_vtable));
}

TEST_F(VtableTest, vtable_putTest1) {
  char name[] = "obj";
  hex_scope_type_t scope_type = HEX_VAR_SCOPE_TYPE_LOCAL;
  hex_type_t type = 1;
  hex_type_qualifier_t type_qualifier = HEX_TYPE_QUALIFIER_CONST;
  unsigned int indent_level = 1;

  VtableEntry entry = (VtableEntry)vtable_put(_vtable, scope_type,
    name, type, type_qualifier, indent_level);

  HEX_ASSERT(entry);

  ASSERT_STREQ(entry->name, name);
  ASSERT_EQ(entry->scope_type, scope_type);
  ASSERT_EQ(entry->type, type);
  ASSERT_EQ(entry->type_qualifier, type_qualifier);
  ASSERT_EQ(entry->indent_level, indent_level);

  char *mingled_name = vtable_mingle_name(entry);
  ASSERT_STREQ(mingled_name, entry->mingled_name);
}

TEST_F(VtableTest, vtable_putTest2) {
  char name1[] = "myobj";
  char name2[] = "myobj";
  hex_scope_type_t scope_type_1 = HEX_VAR_SCOPE_TYPE_LOCAL;
  hex_scope_type_t scope_type_2 = HEX_VAR_SCOPE_TYPE_GLOBAL;
  hex_type_t type_1 = 1;
  hex_type_t type_2 = 1;
  hex_type_qualifier_t type_qualifier_1 = 0;
  hex_type_qualifier_t type_qualifier_2 = 0;
  unsigned int indent_level_1 = 2;
  unsigned int indent_level_2 = 1;

  VtableEntry entry1 = (VtableEntry)vtable_put(_vtable, scope_type_1, name1,
    type_1, type_qualifier_1, indent_level_1);

  VtableEntry entry2 = (VtableEntry)vtable_put(_vtable, scope_type_2, name2,
    type_2, type_qualifier_2, indent_level_2);

  HEX_ASSERT(entry1);
  HEX_ASSERT(entry2);

  ASSERT_NE(entry1, entry2);

  ASSERT_STREQ(name1, entry1->name);
  ASSERT_EQ(scope_type_1, entry1->scope_type);
  ASSERT_EQ(type_1, entry1->type);
  ASSERT_EQ(type_qualifier_1, entry1->type_qualifier);
  ASSERT_EQ(indent_level_1, entry1->indent_level);

  ASSERT_STREQ(name2, entry2->name);
  ASSERT_EQ(scope_type_2, entry2->scope_type);
  ASSERT_EQ(type_2, entry2->type);
  ASSERT_EQ(type_qualifier_2, entry2->type_qualifier);
  ASSERT_EQ(indent_level_2, entry2->indent_level);

  ASSERT_STRNE(entry1->mingled_name, entry2->mingled_name);
}

TEST_F(VtableTest, VtableLookupTest) {
  char name[] = "obj";
  hex_scope_type_t scope_type = HEX_VAR_SCOPE_TYPE_LOCAL;
  hex_type_t type = 1;
  hex_type_qualifier_t type_qualifier = HEX_TYPE_QUALIFIER_CONST;
  unsigned int indent_level = 1;

  VtableEntry entry = (VtableEntry)vtable_put(_vtable, scope_type,
    name, type, type_qualifier, indent_level);

  HEX_ASSERT(entry);

  char *mingled_name = vtable_mingle_name(entry);
  ASSERT_STREQ(mingled_name, entry->mingled_name);

  entry = (VtableEntry)vtable_lookup(_vtable, name, indent_level); 
 
  HEX_ASSERT(entry);

  ASSERT_STREQ(entry->name, name);
  ASSERT_EQ(entry->scope_type, scope_type);
  ASSERT_EQ(entry->type, type);
  ASSERT_EQ(entry->type_qualifier, type_qualifier);
  ASSERT_EQ(entry->indent_level, indent_level);

  mingled_name = vtable_mingle_name(entry);
  ASSERT_STREQ(mingled_name, entry->mingled_name);
}
