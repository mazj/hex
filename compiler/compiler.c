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
#include "parser.h"
#include "ast.h"
#include "semantics.h"
#include "vtable.h"
#include "../base/assert.h"
#include "../base/utils.h"


int
main(int argc, char **argv)
{
  int res = 0;

  void *root=NULL;
  int root_type=0;

  res = parse(argv[1], &root, &root_type);

  if(res == 0) {
    printf("Hex Parsing successful.\n");
  } else if(res == 1) {
    printf("Hex Parse error!!!\n");
    exit(EXIT_FAILURE);
  } else if(res == 2) {
    printf("Hex insufficient memory for parsing!\n");
    exit(EXIT_FAILURE);
  } 

  HEX_ASSERT(root);
  HEX_ASSERT(root_type);

  /* semantics analysis... */

  RETURN_VAL_IF_NE(root_type, HEX_PARSE_TREE_ROOT_TYPE_STMT_GROUP, 0);

  Vtable vtable = vtable_create();
  StmtGroup stmt_group = (StmtGroup)root;
  hex_scope_type_t scope_type = HEX_VAR_SCOPE_TYPE_LOCAL;
  unsigned int indent_level = 1;

  HEX_ASSERT(vtable);
  HEX_ASSERT(stmt_group);

  //hex_semantics_check_stmt_group(vtable, stmt_group, scope_type, indent_level);

  return 0;
}
