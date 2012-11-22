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
    if(c == '\n') {
      strbuf_append(strbuf, "\n");
      continue;
    }
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
    strbuf_append(_strbuf, "\n"); /* due to a limitation in the parser. */      \
    hex_ast_stmt_group_to_text((StmtGroup)_root, 0, _strbuf);                   \ 
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
      printf("Expected string[size: %zu]:\n%s\n",                               \
        strlen(expected_str), expected_str);                                    \
                                                                                \
      printf("\033[22;36m");                                                    \
      printf("Actual string[size: %zu]:\n%s\n",                                 \
        strlen(actual_str), actual_str);                                        \
    }                                                                           \
    printf("\033[0;m");                                                         \
                                                                                \
    teardown();                                                                 \
  }
/* end of #define AST_UNITTEST(TEST_NAME) */

int main()
{
  printf("HEX AST test\n\n");

  AST_UNITTEST(postfix_expr);
  AST_UNITTEST(unary_expr);
  AST_UNITTEST(additive_expr);
  AST_UNITTEST(multiplicative_expr);
  AST_UNITTEST(equality_expr);
  AST_UNITTEST(logic_expr);
  AST_UNITTEST(bitwise_expr);
  AST_UNITTEST(conditional_expr);
  AST_UNITTEST(range_expr);
  AST_UNITTEST(lock_expr);
  AST_UNITTEST(weakref_expr);
  AST_UNITTEST(cast_expr);
  AST_UNITTEST(lambda_expr_1);
  AST_UNITTEST(list_initializer);
  AST_UNITTEST(array_initializer);
  AST_UNITTEST(struct_initializer);
  AST_UNITTEST(tuple_initializer);
  AST_UNITTEST(set_initializer);
  AST_UNITTEST(map_initializer);
  AST_UNITTEST(declaration);
  AST_UNITTEST(parameter);
  AST_UNITTEST(func_dec);
  AST_UNITTEST(import_stmt);
  AST_UNITTEST(decorator);
  AST_UNITTEST(simple_assignment);
  //AST_UNITTEST(if_stmt_1);
  //AST_UNITTEST(if_stmt_2);
  //AST_UNITTEST(if_stmt_3);
  //AST_UNITTEST(if_stmt_4);
  //AST_UNITTEST(while_stmt);
  //AST_UNITTEST(for_stmt_1);
  //AST_UNITTEST(for_stmt_2);
  //AST_UNITTEST(for_stmt_3);
  //AST_UNITTEST(for_stmt_4);
  //AST_UNITTEST(try_stmt_1);
  //AST_UNITTEST(try_stmt_2);
  //AST_UNITTEST(try_stmt_3);
  //AST_UNITTEST(try_stmt_4);
  //AST_UNITTEST(func_def_1);
  //AST_UNITTEST(func_def_2);
  //AST_UNITTEST(func_def_3);
  //AST_UNITTEST(func_def_4);
  //AST_UNITTEST(func_def_5);
  //AST_UNITTEST(func_def_6);
  //AST_UNITTEST(func_def_7);
  //AST_UNITTEST(func_def_8);
  //AST_UNITTEST(func_def_9);
  //AST_UNITTEST(func_def_10);
  //AST_UNITTEST(func_def_11);
  //AST_UNITTEST(return_stmt_1);
  //AST_UNITTEST(return_stmt_2);
  //AST_UNITTEST(break_stmt);
  //AST_UNITTEST(continue_stmt);

  if(_passed_test_count == _total_test_count) {
    printf("\033[22;32m");
    printf("\nPASS: %u/%u TESTS PASS :)\n", _passed_test_count, _total_test_count);
  } else {
    printf("\033[22;31m");
    printf("\nFAILED: %u/%u TESTS PASS :(\n", _passed_test_count, _total_test_count);
  }

  return 0;
}
