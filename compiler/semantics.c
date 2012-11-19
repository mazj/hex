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


#include "../base/utils.h"
#include "ast.h"
#include "vtable.h"
#include "ftable.h"
#include "ttable.h"
#include "scope.h"
#include "types.h"


hex_type_qualifier_t
hex_semantics_translate_type_qualifier_list(TypeQualifierList list)
{
  HEX_ASSERT(list);
  hex_type_qualifier_t type_qualifier = 0;

  while(list) {
    TypeQualifier qualifier = list->type_qualifier;
    type_qualifier |= qualifier;
    list = list->next;
  }

  return type_qualifier;
}

static
inline PrimaryExpr _hex_semantics_get_primary_expr(Expr expr)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(expr->expr_type == expr_type_primary);

  PrimaryExpr primary_expr = expr->primary_expr;
  
  HEX_ASSERT(primary_expr);
  
  return primary_expr;
}

void
hex_semantics_check_declaration(
    Vtable vtable, Ttable ttable, Declaration declaration,
    hex_scope_type_t scope_type, unsigned int indent_level, unsigned int *var_counter)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(declaration);

  hex_type_qualifier_t type_qualifier = 0;
  
  if(declaration->type_qualifier_list) {
    type_qualifier = hex_semantics_translate_type_qualifier_list(declaration->type_qualifier_list);
  }

  /*
   * TODO: check declaration type from ttable
   */

  ExprList exprlist = declaration->expr_list;
  
  HEX_ASSERT(exprlist);

  while(exprlist) {
    Expr expr = exprlist->expr;

    HEX_ASSERT(expr);

    PrimaryExpr primary_expr = _hex_semantics_get_primary_expr(expr);

    HEX_ASSERT(primary_expr);
    HEX_ASSERT(primary_expr->primary_expr_type == primary_expr_type_identifier);

    char *identifier = pri_expr->primary_expr_identifier;

    VtableEntry entry = (VtableEntry)vtable_lookup(vtable, identifier, indent_level);

    if(entry) {
      // abort
    }

    (*var_counter)++;

    entry = vtable_put(vtable, scope_type, identifier, type_qualifier,
      indent_level, *var_counter
    );

    HEX_ASSERT(entry);

    exprlist = exprlist->next;
  } /* end of while(exprlist) */
}

void
hex_semantics_check_parameter_list(Vtable vtable, Ftable ftable,
  Ttable ttable, hex_scope_type_t scope_type,
  unsigned int indent_level, unsigned int *var_counter, ParameterList paramlist)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ftable);
  HEX_ASSERT(ttable);
  HEX_ASSERT(paramlist);

  while(paramlist) {
    Parameter param = paramlist->parameter;

    HEX_ASSERT(param);
    HEX_ASSERT(parameter->name);

    /* TODO: check for type */
    hex_type_t param_type = 0;

    VtableEntry entry = (VtableEntry)vtable_lookup(vtable, parameter_name, indent_level);

    if(entry) {
      /* abort */
    }

    hex_type_qualifier_t type_qualifier = 0;
    
    if(param->type_qualifier_list) {
      type_qualifier = _hex_semantics_translate_type_qualifier_list(param->type_qualifier_list)
    }

    (*var_counter)++;

    entry = vtable_put(vtable, scope_type, param->parameter_name,
      param_type, type_qualifier, indent_level, *var_counter
    );

    HEX_ASSERT(entry);

    paramlist = paramlist->next;
  } /* end of while(paramlist) */
}

void
hex_semantics_check_assignment_stmt(Vtable vtable, Ttable ttable, AssignmentStmt assignment_stmt)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ttable);
  HEX_ASSERT(assignment_stmt);

  AssignmentList assignment_list = assignment_stmt->assignment_list;

  HEX_ASSERT(assignemnt_list);

  /* check the assignment targets */
  int assignment_stmt_type = assignment_stmt->assignment_stmt_type;
  if(assignment_stmt_type == assignment_stmt_type_declaration) {
    Declaration declaration = assignment_stmt->assignment_stmt_declaration;
    HEX_ASSERT(declaration);
    hex_semantics_check_declaration(vtable, declaration);
  } else if (assignment_stmt_type == assignment_stmt_type_expr_list) {
    ExprList exprlist = assignment->assignment_stmt_expr_list;
    HEX_ASSERT(exprlist);
    hex_semantics_check_expr_list(vtable, exprlist);
  }

  /* check the assignment list */
  while(assignment_list) {
    Assignment assignment = assingment_list->assignment;

    HEX_ASSERT(assignment);

    int assignment_type = assignment->assignment_type;

    switch(assignment_type)
    {
      case assignment_type_expr:
        {
          Expr expr = assignment->assignment_expr;
          /* TODO: check expr */
        }
        break;
      case assignment_type_initializer:
        {
          /* TODO: check initializer */
        }
        break;
      case assignment_type_lambda:
        {
          /* TODO: check lambda */
        }
        break;
      default:
        /* abort */
        break;
    }

    assignment_list = assignment_list->next;
  } /* end of while(assignment_list) */
}

void
hex_semantics_check_function(
  Vtable vtable, Ftable ftable, Ttable ttable, FuncDef func,
  unsigned int indent_level, unsigned int *var_counter)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ftable);
  HEX_ASSERT(ttable);
  HEX_ASSERT(func);

  FuncDec func_declaration = func->declaration;

  HEX_ASSERT(func_declaration);

  hex_scope_t scope = HEX_VAR_SCOPE_TYPE_LOCAL;

  hex_semantics_check_func_dec(vtable, ftable, ttable, func_declaration, scope, indent_level, var_counter);

  Suite func_suite = func->func_suite;

  HEX_ASSERT(func_suite);

  hex_semantics_check_func_body(vtable, ttable, func_suite, scope, indent_level, var_counter);
}

void
hex_semantics_check_func_dec(Vtable vtable, Ftable ftable, Ttable ttable,
  FuncDec func_declaration, hex_scope_t scope, unsigned int indent_level, unsigned int *var_counter)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ftable);
  HEX_ASSERT(ttable);
  HEX_ASSERT(func_dec);

  char *func_name = func_dec->func_name;

  HEX_ASSERT(func_name);
  
  ParameterList paramlist = func_dec->parameter_list;

  if(paramlist) {
    hex_sementics_check_paramlist(vtable, ftable, ttable,
      scope, indent_level, var_counter, paramlist);
  }

  FuncEntry entry = ftable_lookup(ftable, func_name, paramlist);

  if(entry) {
    /* TODO: abort */
  }

  entry = ftable_put(ftable, func_name, /* return_type */, paramlist);

  HEX_ASSERT(entry);
}

void
hex_semantics_check_func_body(Vtable vtable, Ttable ttable, Suite func_suite,
  hex_scope_t scope, unsigned int indent_level, unsigned int *var_counter)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ftable);
  HEX_ASSERT(ttable);
  HEX_ASSERT(func_suite);

  StmtGroup stmt_group = func_suite->stmt_group;

  HEX_ASSERT(stmt_group);

  hex_semantics_check_stmt_group(vtable, ttable, stmt_group, scope, indent_level, var_counter);
}

void
hex_semantics_check_stmt_group(Vtable vtable, Tttable ttable, StmtGroup stmt_group,
  hex_scope_t scope, unsigned int indent_level, unsigned int *var_counter)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ttable);
  HEX_ASSERT(stmt_group);

  while(stmt_group) {
    Stmt stmt = stmt_group->stmt;
    HEX_ASSERT(stmt);
    hex_semantics_check_stmt(vtable, ttable, stmt, scope, indent_level, var_counter);
    stmt_group = stmt_group->next;
  }
}

void
hex_semantics_check_stmt(Vtable vtable, Ttable ttable, Stmt stmt,
  hex_scope_t scope, unsigned int indent_level, unsigned int *var_counter)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ttable);
  HEX_ASSERT(stmt);

  switch(stmt->stmt_type)
  {
    case stmt_type_simple_stmt_list:
      {
        SimpleStmtList simple_stmt_list = stmt->stmt_simple_stmt_list;

        HEX_ASSERT(simple_stmt_list);

        hex_semantics_check_simple_stmt_list(vtable, ttable,
          simple_stmt_list, scope, indent_level, var_counter);
      }
      break;
    case stmt_type_compound_stmt:
      {
        CompoundStmt compound_stmt = stmt->stmt_compound_stmt;

        HEX_ASSERT(compound_stmt);

        hex_semantics_check_compound_stmt(vtable, ttable,
          compound_stmt, scope, indent_level, var_counter);
      }
      break;
    case stmt_type_control_simple_stmt:
      {
        ControlSimpleStmt control_simple_stmt = stmt->stmt_control_simple_stmt;

        HEX_ASSERT(control_simple_stmt);

        hex_semantics_check_control_simple_stmt(vtable, ttable,
          control_simple_stmt, scope, indent_level, var_counter);
      }
      break;
    default:
      /* TODO: abort */
      break;
  }
}

void
hex_semantics_check_simple_stmt_list(Vtable vtable, Ttable ttable,
  SimpleStmtList simple_stmt_list, hex_scope_t scope,
  unsigned int indent_level, unsigned int *var_counter)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ttable);
  HEX_ASSERT(simple_stmt_list);

  while(simple_stmt_list) {
    SimpleStmt simple_stmt = simple_stmt_list->simple_stmt;
    
    HEX_ASSERT(simple_stmt);

    hex_semantics_check_simple_stmt(vtable, ttable, simple_stmt, scope, indent_level, var_counter);

    simple_stmt_list = simple_stmt_list->next;
  }
}

void
hex_semantics_check_simple_stmt(Vtable vtable, Ttable ttable, SimpleStmt simple_stmt,
  hex_scope_t scope_type, unsigned int indent_level, unsigned int *var_counter)
{
  HEX_ASSERT(vtable);
  HEX_ASSERT(ttable);
  HEX_ASSERT(simple_stmt);

  int type = simple_stmt->simple_stmt_type;

  switch(type)
  {
    case simple_stmt_type_expr_list:
      {
        ExprList expr_list = simple_stmt->simple_stmt_expr_list;
        HEX_ASSERT(expr_list);
        hex_semantics_check_expr_list(vtable, ttable, expr_list,
          scope_type, indent_level, var_counter);
      }
      break;
    case simple_stmt_type_declaration:
      {
        Declaration declaration = simple_stmt->simple_stmt_declaration;
        HEX_ASSERT(declaration);
        hex_semantics_check_declaration(vtable, ttable, declaration,
          scope_type, indent_level, var_counter);
      }
      break;
    case simple_stmt_type_assignment_stmt:
      {
        AssignmentStmt assignment_stmt = simple_stmt->simple_stmt_assignment_stmt;
        HEX_ASSERT(assignment_stmt);
        hex_semantics_check_assignment_stmt(vtable, ttable, assignment_stmt,
          scope_type, indent_level, var_counter);
      }
      break;
    case simple_stmt_type_import_stmt:
      {
        /* TODO: to be implemented */
      }
      break;
    case simple_stmt_type_if_stmt_simple:
      {
        /* TODO: to be implemented */
      }
      break;
    case simple_stmt_type_func_declaration:
      {
        FuncDec func_declaration = simple_stmt->func_declaration;
        HEX_ASSERT(func_declaration);
        hex_semantics_check_func_declaration(vtable, ftable, ttable,
          func_declaration, scope_type, indent_level, var_counter);
      }
      break;
    case simple_stmt_type_decorator:
      {
        /* TODO: to be implemented */
      }
      break;
    default:
      /* TODO: abort */
      break;
  } /* end of switch(type) */
}
