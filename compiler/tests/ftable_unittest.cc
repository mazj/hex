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

#include "../../base/memory.h"
#include "../../base/unittest.h"
#include "../../base/assert.h"
#include "../../base/utils.h"
#include "../ast.h"
#include "../ftable.h"


class FtableTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    _ftable = ftable_create();
  }

  virtual void TearDown() {
    ftable_free(&_ftable);
  }

  Ftable _ftable;
};


TEST_F(FtableTest, FtableCreationTest) {
  HEX_ASSERT(_ftable);
  ASSERT_EQ(0, ftable_size(_ftable));
  ASSERT_LE(0, ftable_capacity(_ftable));
}

TEST_F(FtableTest, ftable_putTest1) {
  char name[] = "do_something";
  hex_type_t return_type = 1;
  ParameterList paramlist = NULL;

  FtableEntry entry = ftable_put(_ftable, name, return_type, paramlist);

  HEX_ASSERT(entry);
  
  ASSERT_STREQ(name, entry->name);
  ASSERT_EQ(return_type, entry->return_type);
  ASSERT_EQ(paramlist, entry->paramlist);

  char *mingled_name = ftable_mingle_name(entry);
  ASSERT_STREQ(mingled_name, entry->mingled_name);

  ASSERT_EQ(1, ftable_size(_ftable));

  entry = (FtableEntry)ftable_lookup(_ftable, name, paramlist);

  HEX_ASSERT(entry);

  ASSERT_STREQ(name, entry->name);
  ASSERT_EQ(return_type, entry->return_type);
  ASSERT_EQ(paramlist, entry->paramlist);

  ASSERT_STREQ(mingled_name, entry->mingled_name);

  HEX_FREE(mingled_name);
}

TEST_F(FtableTest, ftable_putTest2) {
  char name1[] = "doSomething";
  char name2[] = "doNothing";
  hex_type_t return_type1 = 1;
  hex_type_t return_type2 = 2;
  ParameterList paramlist1 = NULL;
  ParameterList paramlist2 = NULL;

  FtableEntry entry1 = ftable_put(_ftable, name1, return_type1, paramlist1);
  FtableEntry entry2 = ftable_put(_ftable, name2, return_type2, paramlist2);

  HEX_ASSERT(entry1);
  HEX_ASSERT(entry2);

  ASSERT_NE(entry1, entry2);

  ASSERT_STREQ(name1, entry1->name);
  ASSERT_EQ(return_type1, entry1->return_type);
  ASSERT_EQ(paramlist1, entry1->paramlist);

  ASSERT_STREQ(name2, entry2->name);
  ASSERT_EQ(return_type2, entry2->return_type);
  ASSERT_EQ(paramlist2, entry2->paramlist);

  ASSERT_STRNE(entry1->mingled_name, entry2->mingled_name);

  char *mingled_name1=NULL;
  char *mingled_name2=NULL;

  mingled_name1 = ftable_mingle_name(entry1);
  mingled_name2 = ftable_mingle_name(entry2);

  ASSERT_STREQ(mingled_name1, entry1->mingled_name);
  ASSERT_STREQ(mingled_name2, entry2->mingled_name);
  ASSERT_STRNE(mingled_name1, mingled_name2);

  HEX_FREE(mingled_name1);
  HEX_FREE(mingled_name2);
}

TEST_F(FtableTest, ftable_putTest3) {
  char name1[] = "factorial";
  char name2[] = "factorial";
  hex_type_t return_type1 = 1;
  hex_type_t return_type2 = 1;
  ParameterList paramlist1 = NULL;
  ParameterList paramlist2 = HEX_MALLOC(struct HexParameterList);

  HEX_ASSERT(paramlist2);

  Parameter param = HEX_MALLOC(struct HexParameter);
  HEX_ASSERT(param);

  param->parameter_name = (char*)"myobj";
  param->type_specifier = 1;

  paramlist2->parameter = param;
  paramlist2->next = NULL;

  FtableEntry entry1 = ftable_put(_ftable, name1, return_type1, paramlist1);
  FtableEntry entry2 = ftable_put(_ftable, name2, return_type2, paramlist2);

  HEX_ASSERT(entry1);
  HEX_ASSERT(entry2);

  ASSERT_STREQ(name1, entry1->name);
  ASSERT_EQ(return_type1, entry1->return_type);
  ASSERT_EQ(paramlist1, entry1->paramlist);

  ASSERT_STREQ(name2, entry2->name);
  ASSERT_EQ(return_type2, entry2->return_type);
  ASSERT_EQ(paramlist2, entry2->paramlist);

  ASSERT_STRNE(entry1->mingled_name, entry2->mingled_name);

  char *mingled_name1=NULL;
  char *mingled_name2=NULL;

  mingled_name1 = ftable_mingle_name(entry1);
  mingled_name2 = ftable_mingle_name(entry2);

  ASSERT_STREQ(mingled_name1, entry1->mingled_name);
  ASSERT_STREQ(mingled_name2, entry2->mingled_name);
  ASSERT_STRNE(mingled_name1, mingled_name2);

  HEX_FREE(mingled_name1);
  HEX_FREE(mingled_name2);
}

TEST_F(FtableTest, ftable_putTest4) {
  char name1[] = "factorial";
  char name2[] = "factorial";
  hex_type_t return_type1 = 1;
  hex_type_t return_type2 = 1;
  ParameterList paramlist1 = HEX_MALLOC(struct HexParameterList);
  ParameterList paramlist2 = HEX_MALLOC(struct HexParameterList);

  HEX_ASSERT(paramlist1);
  HEX_ASSERT(paramlist2);

  Parameter param1 = HEX_MALLOC(struct HexParameter);
  HEX_ASSERT(param1);
  param1->parameter_name = (char*)"myobj";
  param1->type_specifier = 1;

  Parameter param2 = HEX_MALLOC(struct HexParameter);
  HEX_ASSERT(param2);
  param2->parameter_name = (char*)"yourobj";
  param2->type_specifier = param1->type_specifier;

  paramlist1->parameter = param1;
  paramlist1->next = NULL;

  paramlist2->parameter = param2;
  paramlist2->next = NULL;

  FtableEntry entry1 = ftable_put(_ftable, name1, return_type1, paramlist1);
  FtableEntry entry2 = ftable_put(_ftable, name2, return_type2, paramlist2);

  HEX_ASSERT(entry1);
  HEX_ASSERT(entry2);

  ASSERT_STREQ(name1, entry1->name);
  ASSERT_EQ(return_type1, entry1->return_type);
  ASSERT_EQ(paramlist1, entry1->paramlist);

  ASSERT_STREQ(name2, entry2->name);
  ASSERT_EQ(return_type2, entry2->return_type);
  ASSERT_EQ(paramlist2, entry2->paramlist);

  ASSERT_STRNE(entry1->mingled_name, entry2->mingled_name);

  char *mingled_name1=NULL;
  char *mingled_name2=NULL;

  mingled_name1 = ftable_mingle_name(entry1);
  mingled_name2 = ftable_mingle_name(entry2);

  ASSERT_STREQ(mingled_name1, entry1->mingled_name);
  ASSERT_STREQ(mingled_name2, entry2->mingled_name);
  ASSERT_STRNE(mingled_name1, mingled_name2);

  HEX_FREE(mingled_name1);
  HEX_FREE(mingled_name2);
}

TEST_F(FtableTest, ftable_lookup_by_nameTest) {
  char func_name[] = "calculate_mass_of_sun";

  FtableEntry entry=NULL;

  entry = ftable_put(
    _ftable, func_name, 0, NULL);

  HEX_ASSERT(entry);
  ASSERT_STREQ(func_name, entry->name);

  entry = ftable_lookup_by_name(
    _ftable,
    func_name);

  HEX_ASSERT(entry);
  ASSERT_STREQ(func_name, entry->name);

  entry = ftable_lookup_by_name(
    _ftable,
    (char*)"_some_random_function"
  );

  HEX_ASSERT(entry == NULL);
}
