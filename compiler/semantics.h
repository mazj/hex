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

#ifndef _SEMANTICS_H_
#define _SEMANTICS_H_

#include "ash.h"
#include "vtable.h"
#include "ftable.h"
#include "ttable.h"
#include "types.h"
#include "scope.h"


#ifdef __cplusplus
extern "C" {
#endif

hex_type_qualifier_t 
hex_semantics_translate_type_qualifier_list(TypeQualifierList list);

void
hex_semantics_check_declaration(
    Vtable vtable, Ttable ttable, Declaration declaration,
    hex_scope_type_t scope_type, unsigned int indent_level, unsigned int *var_counter);

void
hex_semantics_check_parameter_list(Vtable vtable, Ftable ftable,
  Ttable ttable, hex_scope_type_t scope_type,
  unsigned int indent_level, unsigned int *var_counter, ParameterList paramlist);

void
hex_semantics_check_assignment_stmt(Vtable vtable, Ttable ttable,
  AssignmentStmt assignment_stmt, hex_scope_type_t scope_type,
  unsigned int indent_level, unsigned int *var_counter);

void
hex_semantics_check_function(
  Vtable vtable, Ftable ftable, Ttable ttable, FuncDef func,
  unsigned int indent_level, unsigned int *var_counter);

void
hex_semantics_check_func_body(Vtable vtable, Ttable ttable, Suite func_suite,
  hex_scope_t scope, unsigned int indent_level, unsigned int *var_counter);

void
hex_semantics_check_stmt_group(Vtable vtable, Tttable ttable, StmtGroup stmt_group,
  hex_scope_t scope, unsigned int indent_level, unsigned int *var_counter);

void
hex_semantics_check_stmt(Vtable vtable, Tttable ttable, Stmt stmt,
  hex_scope_t scope, unsigned int indent_level, unsigned int *var_counter);

void
hex_semantics_check_simple_stmt_list(Vtable vtable, Ttable ttable,
  SimpleStmtList simple_stmt_list, hex_scope_t scope,
  unsigned int indent_level, unsigned int *var_counter);

void
hex_semantics_check_simple_stmt(Vtable vtable, Ttable ttable, SimpleStmt simple_stmt,
  hex_scope_t scope, unsigned int indent_level, unsigned int *var_counter);


#ifdef __cplusplus
}
#endif

#endif /* _SEMENTICS_H_ */
