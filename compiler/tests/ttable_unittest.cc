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
#include "../../base/memory.h"
#include "../../base/utils.h"
#include "../ast.h"
#include "../vtable.h"
#include "../ftable.h"
#include "../ttable.h"


class TtableTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _ttable = ttable_create();
    HEX_ASSERT(_ttable);
  }

  virtual void TearDown() {
    ttable_free(&_ttable);
    HEX_ASSERT(_ttable == NULL);
  }

  Ttable _ttable;
};


TEST_F(TtableTest, TtableCreationTest) {
  HEX_ASSERT(_ttable);
  ASSERT_EQ(0, ttable_size(_ttable));
  ASSERT_LE(0, ttable_capacity(_ttable));
}

TEST_F(TtableTest, TtablePutAndLookupTest1) {
  char type_name[] = "MyObject";
  
  TtableEntry entry1 = (TtableEntry)ttable_put(_ttable, type_name);

  HEX_ASSERT(entry1);

  TtableEntry entry2 = ttable_lookup(_ttable, type_name);

  HEX_ASSERT(entry2);

  ASSERT_EQ(entry1, entry2);
}

TEST_F(TtableTest, TtablePutAndLookupTest2) {
  char type_name[] = "YourObject";

  TtableEntry entry1 = (TtableEntry)ttable_put(_ttable, type_name);

  HEX_ASSERT(entry1);

  TtableEntry entry2 = (TtableEntry)ttable_put(_ttable, type_name);

  HEX_ASSERT(entry2);

  ASSERT_EQ(entry1, entry2);
}

TEST_F(TtableTest, TtablePutAndLookupMemberVarTest1) {
  char type_name[] = "OurObject";

  TtableEntry entry = (TtableEntry)ttable_put(_ttable, type_name);

  HEX_ASSERT(entry);

  char member_name[] = "some_random_name";
  hex_type_t type = 1;
  hex_type_qualifier_t type_qualifier = HEX_TYPE_QUALIFIER_CONST;

  VtableEntry member = (VtableEntry)ttable_put_member_var(_ttable, type_name,
    member_name, type, type_qualifier);

  HEX_ASSERT(member);

  ASSERT_STREQ(member_name, member->name);
  ASSERT_EQ(HEX_VAR_SCOPE_TYPE_MEMBER, member->scope_type);
  ASSERT_EQ(type, member->type);
  ASSERT_EQ(type_qualifier, member->type_qualifier);

  ASSERT_TRUE(ttable_lookup_member_var(_ttable, type_name, member_name));
}

TEST_F(TtableTest, TtablePutAndLookupMemberFuncTest1) {
  char type_name[] = "OurObject";

  TtableEntry entry = (TtableEntry)ttable_put(_ttable, type_name);

  HEX_ASSERT(entry);

  char member_name[] = "do_something";
  hex_type_t return_type = 1;
  ParameterList paramlist = NULL; 

  FtableEntry member = (FtableEntry)ttable_put_member_func(_ttable, type_name,
    member_name, return_type, paramlist);

  HEX_ASSERT(member);

  ASSERT_STREQ(member_name, member->name);
  ASSERT_EQ(return_type, member->return_type);
  ASSERT_EQ(paramlist, member->paramlist);

  ASSERT_TRUE(ttable_lookup_member_func(_ttable, type_name, member_name, paramlist));
}
