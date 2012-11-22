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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../base/assert.h"
#include "../../base/utils.h"
#include "../../base/strbuf.h"
#include "../parser.h"
#include "../ast_to_text.h"

void *_root=NULL;
FILE *_f=NULL;
int _root_type=0;
int _res=0;
Strbuf _strbuf=NULL;

unsigned int _passed_test_count=0;
unsigned int _total_test_count=0;


void setup(char *path)
{
  _root=NULL;
  _root_type=0;
  _res=0;

  _strbuf=strbuf_create();
  HEX_ASSERT(_strbuf);
  
  _f = fopen(path, "r");
  HEX_ASSERT(_f);
}

void teardown()
{
  _root=NULL;
  fclose(_f);
  strbuf_free(&_strbuf);
  HEX_ASSERT(_strbuf == NULL);
}

char* read_file(char *path)
{
  HEX_ASSERT(path);

  Strbuf strbuf = strbuf_create();

  HEX_ASSERT(strbuf);

  char c;
  while( (c = fgetc(_f) ) != EOF ) {
    if(c == '\n') continue;
    char s[2];
    memset(s, 0, sizeof(s));
    snprintf(s, sizeof(s), "%c", c);
    strbuf_append(strbuf, s);
  }

  char *str = strdup(strbuf_cstr(strbuf));

  HEX_ASSERT(str);

  strbuf_free(&strbuf);

  return str;
}

#define TEST_PATH "./parser_tests/parser_test_"
#define TEST_EXT ".hex"

#define AST_UNITTEST(TEST_NAME)                                                 \ 
  {                                                                             \
    char path[] = TEST_PATH #TEST_NAME TEST_EXT;                                \
    setup(path);                                                                \
                                                                                \
    _res = parse(path, &_root, &_root_type);                                    \
                                                                                \
    HEX_ASSERT(_res==0);                                                        \
    HEX_ASSERT(_root);                                                          \
    HEX_ASSERT(_root_type);                                                     \
                                                                                \
    hex_ast_stmt_group_to_text((StmtGroup)_root, _strbuf);                      \ 
                                                                                \
    char *expected_str = read_file(path);                                       \
    char *actual_str = strbuf_cstr(_strbuf);                                    \
                                                                                \
    printf("\033[0;m");                                                         \
                                                                                \
    _total_test_count++;                                                        \
                                                                                \
    if(strcmp(expected_str, actual_str) == 0) {                                 \
      printf("\033[22;32m");                                                    \
      printf("PASS: %s\n", #TEST_NAME);                                         \
      _passed_test_count++;                                                     \
    } else {                                                                    \
      printf("\033[22;31m");                                                    \
      printf("FAILED: %s\n", #TEST_NAME);                                       \
                                                                                \
      printf("\033[22;35m");                                                    \
      printf("Expected string: %s\n", expected_str);                            \
                                                                                \
      printf("\033[22;36m");                                                    \
      printf("Actual string: %s\n", actual_str);                                \
    }                                                                           \
                                                                                \
    printf("\033[0;m");                                                         \
                                                                                \
    teardown();                                                                 \
  }
/* end of #define AST_UNITTEST(TEST_NAME) */

int main()
{
  printf("HEX AST test\n\n");

  AST_UNITTEST(simple_assignment_1);
  AST_UNITTEST(simple_assignment_2);
  AST_UNITTEST(simple_assignment_3);
  AST_UNITTEST(simple_assignment_4);
  AST_UNITTEST(simple_assignment_5);

  AST_UNITTEST(postfix_expr_1);
  AST_UNITTEST(postfix_expr_2);
  AST_UNITTEST(postfix_expr_3);
  AST_UNITTEST(postfix_expr_4);
  AST_UNITTEST(postfix_expr_5);
  AST_UNITTEST(postfix_expr_6);
  AST_UNITTEST(postfix_expr_7);

  AST_UNITTEST(unary_expr_1);
  AST_UNITTEST(additive_expr_1);
  AST_UNITTEST(multiplicative_expr_1);
  AST_UNITTEST(equality_expr_1);
  AST_UNITTEST(logic_expr_1);
  AST_UNITTEST(bitwise_expr_1);
  AST_UNITTEST(conditional_expr_1);
  AST_UNITTEST(range_expr_1);
  AST_UNITTEST(lock_expr_1);
  AST_UNITTEST(weakref_expr_1);
  AST_UNITTEST(cast_expr_1);

  AST_UNITTEST(list_initializer);
  AST_UNITTEST(array_initializer);
  AST_UNITTEST(struct_initializer);
  AST_UNITTEST(set_initializer);

  if(_passed_test_count == _total_test_count) {
    printf("\033[22;32m");
    printf("\nPASS: %u/%u TESTS PASS :)\n", _passed_test_count, _total_test_count);
  } else {
    printf("\033[22;31m");
    printf("\nFAILED: %u/%u TESTS PASS :(\n", _passed_test_count, _total_test_count);
  }

  return 0;
}
