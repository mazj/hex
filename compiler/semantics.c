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


#include "ast.h"
#include "vtable.h"
#include "utils.h"
#include "types.h"

hex_type_qualifier_t
hex_semantics_translate_type_qualifier_list(TypeQualifierList list)
{
  HEX_ASSERT(list);
  hex_type_qualifier_t tq = 0;

  while(list) {
    TypeQualifier qualifier = list->type_qualifier;
    hex_set_type_qualifier(&tq, qualifier);
    list = list->next;
  }

  return tq;
}

static
inline PrimaryExpr _hex_semantics_assert_and_get_primary_expr(Expr expr)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(expr->expr_type == expr_type_primary);

  PrimaryExpr primary_expr = expr->primary_expr;
  
  HEX_ASSERT(pri_expr);
  
  return primary_expr;
}

void
hex_semantics_check_declaration(
    Vtable vtable, hex_scope_id_t scope_id, Declaration declaration)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(declaration);

  ExprList exprlist = declaration->expr_list;

  while(list) {
    Expr expr = exprlist->expr;

    PrimaryExpr primary_expr = _hex_semantics_assert_and_get_primary_expr(expr);

    HEX_ASSERT(pri_expr->primary_expr_type == primary_expr_type_identifier);

    char *identifier = pri_expr->primary_expr_identifier;

    void *p = vtable_lookup(vtable, identifier, scope_id);

    if(p) {
      // abort
    }

    vtable_put(
        vtable,
        /*scope_type*/,
        scope_id,
        identifier,
        /* token_loc */,
        /* var_type */
    );

    exprlist = exprlist->next;
  } /* end of while(expr) */
}

void
hex_semantics_check_parameter_list(Vtable vtable, Ftable ftable, ParameterList paramlist)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ftable);
  HEX_ASSERT(paramlist);

  while(paramlist) {
    Parameter param = paramlist->parameter;

    HEX_ASSERT(param);

    // TODO: check for type
    // ...

    // TODO: check for repeated parameter
    // ...

    vtable_put(
        vtable,
        /*scope_id*/,
        param->parameter_name,
        /* token_loc */,
        /* var_type */
    );

    paramlist = paramlist->next;
  } /* end of while(paramlist) */
}

void
hex_semantics_check_assignment_stmt(Vtable vtable, AssignmentStmt assignment_stmt)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(assignment_stmt);

  AssignmentList assignment_list = assignment_stmt->assignment_list;

  HEX_ASSERT(assignemnt_list);

  /* check the assignment targets */
  int type = assignment_stmt->assignment_stmt_type;
  if(type == assignment_stmt_type_declaration) {
    Declaration declaration = assignment_stmt->assignment_stmt_declaration;
    HEX_ASSERT(declaration);
    hex_semantics_check_declaration(vtable, declaration);
  } else if (type == assignment_stmt_type_expr_list) {
    ExprList exprlist = assignment->assignment_stmt_expr_list;
    HEX_ASSERT(exprlist);
    hex_semantics_check_expr_list(vtable, exprlist);
  }

  /* check the assignment list */
  while(assignment_list) {
    Assignment assignment = assingment_list->assignment;

    int type = assignment->assignment_type;

    if(type == assignment_type_expr) {
      Expr expr = assignment->assignment_expr;
      hex_semantics_check_primary_expr(vtable, declaration);
    } else if (type == assignment_type_initializer) {
      // TODO: handle assignment to initializers
    } else if (type == assignment_type_lambda) {
      // TODO: handle assignment to lambdas
    } /* end of if & else-if */

    assignment = assignment->next;
  } /* end of while(assignment_list) */
}

void
hex_semantics_check_function(Vtable vtable, Ftable ftable, FuncDef func)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ftable);
  HEX_ASSERT(func);

  FuncDec func_dec = func->declaration;

  _hex_semantics_check_func_dec(ftable, func_dec);

  // TODO: check the function body
  hex_semantics_check_func_def(vtable, func);
}

void
hex_semantics_check_func_dec(Ftable ftable, FuncDec func_dec)
{
  HEX_ASSERT(func_dec);
  HEX_ASSERT(func_dec->func_name);

  char *func_name = func_dec->func_name;

  // TODO: hex_symantics_get_func_id
  hex_func_id_t func_id = hex_semantics_get_func_id(func_name, func_dec->parameter_list);

  FuncEntry entry = ftable_lookup_by_id(ftable, func_id);

  if(entry) {
    // TODO: abort
  }

  FuncEntry new_entry = ftable_create_entry(
      func_name,
      func_dec->parameter_list,
      func_dec->return_type,
      /* token_loc */
  );

  ftable_put(ftable, new_entry);
}

void
hex_semantics_check_func_def(Vtable vtable, FuncDef func_def)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(func_def);

  Suite body = func_def->func_suite;

  _hex_semantics_check_func_suite(Vtable vtable, body);
}

static
void _hex_semantics_check_func_suite(Vtable vtable, Suite suite)
{
  // TODO: check func suite
}
