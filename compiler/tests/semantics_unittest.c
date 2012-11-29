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
#include "../ast.h"
#include "../parser.h"
#include "../semantics.h"
#include "../semantics_errors.h"


void *_root=NULL;
int _root_type=0;
int _parse_res=0;
int _res=0;
Semantics _semantics=NULL;

unsigned int _passed_test_count=0;
unsigned int _total_test_count=0;


void setup()
{
  _root=NULL;
  _root_type=0;
  _parse_res=0;
  _res =0;
  _semantics = semantics_create();
  HEX_ASSERT(_semantics);
}

void teardown()
{
  _root=NULL;
  _root_type=0;
  _parse_res=0;
  _res=0;
  semantics_free(&_semantics);
  HEX_ASSERT(_semantics==NULL);
}

#define TEST_PATH "./semantics_tests/semantics_test_"
#define TEST_EXT ".hex"


#define SEMANTICS_UNITTEST(TEST_NAME, expected_errcode, expected_errmsg)        \
  {                                                                             \
    char path[] = TEST_PATH #TEST_NAME TEST_EXT;                                \
    setup();                                                                    \
                                                                                \
    _parse_res = parse(path, &_root, &_root_type);                              \
                                                                                \
    HEX_ASSERT(_parse_res==0);                                                  \
    HEX_ASSERT(_root);                                                          \
    HEX_ASSERT(_root_type);                                                     \
                                                                                \
    _res = hex_semantics_check_stmt_group((StmtGroup)_root, 0, _semantics);     \
                                                                                \
    printf("\033[0;m");                                                         \
                                                                                \
    _total_test_count++;                                                        \
                                                                                \
    if(semantics_get_errcode(_semantics) == expected_errcode) {                 \
      HEX_ASSERT_STREQ(semantics_get_errmsg(_semantics), expected_errmsg);      \
                                                                                \
      printf("\033[22;32m");                                                    \
      printf("PASS: %s\n", #TEST_NAME);                                         \
                                                                                \
      printf("Expected:\n");                                                    \
      printf("[SEMANTICS ERROR %u]: %s\n\n",                                    \
        semantics_get_errcode(_semantics),                                      \
        semantics_get_errmsg(_semantics)                                        \
      );                                                                        \
                                                                                \
      _passed_test_count++;                                                     \
    } else {                                                                    \
      printf("\033[22;31m");                                                    \
      printf("FAILED: %s\n", #TEST_NAME);                                       \
                                                                                \
      printf("\033[22;35m");                                                    \
      printf("Expected:\n");                                                    \
      printf("[SEMANTICS ERROR %u]: %s\n",                                      \
        expected_errcode, expected_errmsg);                                     \
                                                                                \
      printf("\033[22;36m");                                                    \
      printf("Actual:\n");                                                      \
      printf("[SEMANTICS ERROR %u]: %s\n",                                      \
        semantics_get_errcode(_semantics),                                      \
        semantics_get_errmsg(_semantics)                                        \
      );                                                                        \
                                                                                \
      printf("\n");                                                             \
    }                                                                           \
    printf("\033[0;m");                                                         \
                                                                                \
    teardown();                                                                 \
  }
/* end of #define SEMANTICS_UNITTEST(TEST_NAME, expected_errcode, expected_errcode) */

int main()
{
  printf("HEX Semantics test\n\n");

  //SEMANTICS_UNITTEST(func_dec_1, 0, "");
  //SEMANTICS_UNITTEST(func_dec_2, 0, "");
  //SEMANTICS_UNITTEST(func_dec_3, HEX_SEMANTICS_ERROR_REPEATED_TYPE_QUALIFIER, "Repeated type qualifier at 'init'");
  //SEMANTICS_UNITTEST(func_dec_4, HEX_SEMANTICS_ERROR_REPEATED_FUNCTION_DECLARATION, "Repeated declaration of function 'init'");
  //SEMANTICS_UNITTEST(func_dec_5, 0, "");
  //SEMANTICS_UNITTEST(func_dec_6, HEX_SEMANTICS_ERROR_REPEATED_FUNCTION_DECLARATION, "Repeated declaration of function 'init'");
  //SEMANTICS_UNITTEST(postfix_index_expr_1, 0, "");
  //SEMANTICS_UNITTEST(postfix_index_expr_2, 0, "");
  SEMANTICS_UNITTEST(postfix_index_expr_3, 0, "");

  if(_passed_test_count == _total_test_count) {
    printf("\033[22;32m");
    printf("\nPASS: %u/%u TESTS PASS :)\n", _passed_test_count, _total_test_count);
  } else {
    printf("\033[22;31m");
    printf("\nFAILED: %u/%u TESTS PASS :(\n", _passed_test_count, _total_test_count);
  }

  return 0;
}
