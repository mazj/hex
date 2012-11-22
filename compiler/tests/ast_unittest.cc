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

#include <fstream>
#include <sstream>
#include "../../base/unittest.h"
#include "../../base/assert.h"
#include "../../base/utils.h"
#include "../parser.h"
#include "../ast_to_text.h"


class AST_Test : public ::testing::Test {
protected:
  virtual void SetUp() {
    _root=NULL;
    int _root_type=0;
    int _res=0;

    _strbuf = strbuf_create();
    HEX_ASSERT(_strbuf);
  }

  virtual void TearDown() {
    strbuf_free(&_strbuf);
  }

  void *_root;
  int _root_type;
  int _res;
  Strbuf _strbuf;
};


TEST_F(AST_Test, SimpleAssignmentStmtTest) {
  char path[] = "../parser_tests/parser_test_simple_assignment.hex";
  std::ifstream ifs(path);
  std::stringstream buf;

  buf << ifs.rdbuf(); 

  _res = parse(path, &_root, &_root_type);

  HEX_ASSERT(_res==0);
  HEX_ASSERT(_root);
  HEX_ASSERT(_root_type);

  hex_ast_stmt_group_to_text((StmtGroup)_root, _strbuf);

  char *expected_str = (char*)buf.str().c_str();
  char *actual_str = strbuf_cstr(_strbuf);

  HEX_ASSERT(expected_str);
  HEX_ASSERT(actual_str);

  HEX_ASSERT(strcmp(expected_str, actual_str) == 0); 
}
