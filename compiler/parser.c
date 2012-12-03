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

/*
 * Front-end parser for HEX.
 *
 * NOTE: when parser.y gets compiled, it will overwrite this
 * file(parser.c), which is not the desired behavior.
 * To reset the override, do 'git checkout -- compiler/parser.c'.
 */

#include <stdlib.h>
#include "parser.tab.h"
#include "ast.h"
#include "../base/assert.h"
#include "../base/utils.h"

typedef void* yyscan_t;

extern FILE * yyin;
extern YY_FLUSH_BUFFER;
extern int yyparse( yyscan_t );
extern int yylex_init( yyscan_t* );

int parse(const char *path, void **root, int *root_type)
{
  int res = 0;
  if((yyin = fopen(path, "r")) == 0) {
    printf("Failed opening file %s\n", path);
    return -1;
  }

  YY_FLUSH_BUFFER;
  yylex();
  res = yyparse(yyin);

  /*
  yyscan_t scanner;
  yy_delete_buffer(NULL);
  yylex_init(&scanner);
  yylex(scanner);
  res = yyparse(scanner);
  yylex_destroy(scanner);
  */

  /*
   * yyparse() returns 0 for successful parsing, and other values
   * for unsuccessful parsing. We simply want to return here if parsing fails */
  RETURN_VAL_IF_TRUE(res != 0, res);

  int _root_type=0;
  void *_root = hex_ast_get_parse_tree_root(&_root_type);

  HEX_ASSERT(_root);
  HEX_ASSERT(_root_type);

  *root_type = _root_type; 
  *root = _root;

  return res;
}
