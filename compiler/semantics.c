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

#include <limits.h>
#include <stdio.h>
#include "../base/assert.h"
#include "../base/utils.h"
#include "../base/memory.h"
#include "vtable.h"
#include "ftable.h"
#include "ttable.h"
#include "types.h"
#include "scope.h"
#include "semantics.h"
#include "semantics_errors.h"


struct HexSemantics {
  Vtable vtable;
  Ftable ftable;
  Ttable ttable;
  hex_scope_type_t scope;
  unsigned int err_code;
  char err_msg[100];
};

#define HEX_SEMANTICS_CHECK_AND_RETURN(res)                                     \
  RETURN_VAL_IF_FALSE(res, 0)

#define HEX_SEMANTICS_RETURN_ERR(semantics, _err_code, err_msg_fmt, ...)        \
  do {                                                                          \
    (semantics)->err_code = (_err_code);                                        \
    snprintf((semantics)->err_msg,                                              \
      sizeof((semantics)->err_msg), (err_msg_fmt), __VA_ARGS__);                \
    return -1;                                                                  \
  } while(0)

#define HEX_SEMANTICS_ERROR(msg)                                                \
  fprintf(stderr, "%s, at %s[line %u]\n", (msg), __FILE__, __LINE__);           \
  abort();

#define HEX_SEMANTICS_CHECK_VAR_EXISTS(semantics, var_name, indent_level)       \
  do {                                                                          \
    VtableEntry entry = vtable_lookup(                                          \
      (semantics)->vtable,                                                      \
      (var_name),                                                               \
      (indent_level)                                                            \
    );                                                                          \
                                                                                \
    if(!entry) {                                                                \
      HEX_SEMANTICS_RETURN_ERR(                                                 \
        (semantics),                                                            \
        HEX_SEMANTICS_ERROR_UNKNOWN_IDENTIFIER,                                 \
        HEX_SEMANTICS_ERROR_UNKNOWN_IDENTIFIER_ERR_MSG_FMT,                     \
        (var_name)                                                              \
      );                                                                        \
    }                                                                           \
  } while(0)

#define HEX_SEMANTICS_LOOKUP_FUNCTION_BY_NAME(semantics, func_name)             \
  do {                                                                          \
    FtableEntry entry = ftable_lookup_by_name(                                  \
      (semantics)->ftable,                                                      \
      (func_name)                                                               \
    );                                                                          \
                                                                                \
    if(!entry) {                                                                \
      HEX_SEMANTICS_RETURN_ERR(                                                 \
        (semantics),                                                            \
        HEX_SEMANTICS_ERROR_UNKNOWN_FUNCTION,                                   \
        HEX_SEMANTICS_ERROR_UNKNOWN_FUNCTION_ERR_MSG_FMT,                       \
        (func_name)                                                             \
      );                                                                        \
    }                                                                           \
  } while(0)

#define HEX_SEMANTICS_CHECK_FUNC_DECLARATION_AND_RETURN(semantics, func_dec)    \
  do {                                                                          \
    FtableEntry entry = ftable_lookup(                                          \
      (semantics)->ftable,                                                      \
      (func_dec)->func_name,                                                    \
      (func_dec)->parameter_list                                                \
    );                                                                          \
                                                                                \
    if(entry) {                                                                 \
      HEX_SEMANTICS_RETURN_ERR(                                                 \
        (semantics),                                                            \
        HEX_SEMANTICS_ERROR_REPEATED_FUNCTION_DECLARATION,                      \
        HEX_SEMANTICS_ERROR_REPEATED_FUNCTION_DECLARATION_ERR_MSG_FMT,          \
        (func_dec)->func_name                                                   \
      );                                                                        \
    }                                                                           \
  } while(0)


Semantics semantics_create()
{
  Semantics semantics=NULL;
  Vtable _vtable=NULL;
  Ftable _ftable=NULL;
  Ttable _ttable=NULL;

  _vtable = vtable_create();
  _ftable = ftable_create();
  _ttable = ttable_create();

  HEX_ASSERT(_vtable);
  HEX_ASSERT(_ftable);
  HEX_ASSERT(_ttable);

  semantics = HEX_MALLOC(struct HexSemantics);

  semantics->vtable = _vtable;
  semantics->ftable = _ftable;
  semantics->ttable = _ttable;

  return semantics;
}

void semantics_free(Semantics *semantics)
{
  Semantics _semantics = *semantics;
  HEX_ASSERT(_semantics);

  vtable_free(&_semantics->vtable);
  ftable_free(&_semantics->ftable);
  ttable_free(&_semantics->ttable);

  HEX_FREE(_semantics);

  *semantics = _semantics;
}

unsigned int
semantics_get_errcode(Semantics semantics)
{
  HEX_ASSERT(semantics);

  return semantics->err_code;
}

char*
semantics_get_errmsg(Semantics semantics)
{
  HEX_ASSERT(semantics);

  return semantics->err_msg;
}

static
int _hex_semantics_check_and_get_identifier_from_expr(
  Expr expr, char **identifier, Semantics semantics)
{
  HEX_ASSERT(expr);

  if(expr->expr_type != expr_type_primary) {
    HEX_SEMANTICS_RETURN_ERR(
      semantics,
      HEX_SEMANTICS_ERROR_IDENTIFIER_EXPECTED,
      HEX_SEMANTICS_ERROR_IDENTIFIER_EXPECTED_ERR_MSG_FMT,
      ""
    );
  }

  PrimaryExpr primary_expr = expr->primary_expr;
  HEX_ASSERT(primary_expr);

  if(primary_expr->primary_expr_type != primary_expr_type_identifier) {
    HEX_SEMANTICS_RETURN_ERR(
      semantics,
      HEX_SEMANTICS_ERROR_IDENTIFIER_EXPECTED,
      HEX_SEMANTICS_ERROR_IDENTIFIER_EXPECTED_ERR_MSG_FMT,
      ""
    );
  }

  HEX_ASSERT(primary_expr->primary_expr_identifier);
  *identifier = strdup(primary_expr->primary_expr_identifier);

  return 1;
}

int
hex_semantics_check_stmt_group(StmtGroup stmt_group,
  unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(stmt_group);
  HEX_ASSERT(semantics);

  while(stmt_group) {
    Stmt stmt = stmt_group->stmt;
    HEX_ASSERT(stmt);

    HEX_SEMANTICS_CHECK_AND_RETURN(
      hex_semantics_check_stmt(
        stmt,
        indent_level,
        semantics
      )
    );

    stmt_group = stmt_group->next;
  }

  return 1;
}

int
hex_semantics_check_stmt(
  Stmt stmt, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(stmt);
  HEX_ASSERT(semantics);

  switch(stmt->stmt_type)
  {
    case stmt_type_simple_stmt_list:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_simple_stmt_list(
          stmt->stmt_simple_stmt_list,
          indent_level,
          semantics
        )
      );
      break;
    case stmt_type_compound_stmt:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_compound_stmt(
          stmt->stmt_compound_stmt,
          indent_level,
          semantics
        )
      );
      break;
    case stmt_type_control_simple_stmt:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_control_simple_stmt(
          stmt->stmt_control_simple_stmt,
          indent_level,
          semantics
        )
      );
      break;
    default:
      HEX_SEMANTICS_ERROR("Unknown type for HexStmt");
      break;
  }

  return 1;
}

int
hex_semantics_check_simple_stmt_list(
  SimpleStmtList stmt_list, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(stmt_list);
  HEX_ASSERT(semantics);

  SimpleStmtList _stmt_list = stmt_list;

  while(_stmt_list) {
    SimpleStmt simple_stmt = stmt_list->simple_stmt;

    HEX_SEMANTICS_CHECK_AND_RETURN(
      hex_semantics_check_simple_stmt(
        simple_stmt,
        indent_level,
        semantics
      )
    );

    _stmt_list = _stmt_list->next;
  }

  return 1;
}

int
hex_semantics_check_compound_stmt(
  CompoundStmt compound_stmt, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(compound_stmt);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_control_simple_stmt(
  ControlSimpleStmt control_stmt, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(control_stmt);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_simple_stmt(
  SimpleStmt simple_stmt, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(simple_stmt);
  HEX_ASSERT(semantics);

  switch(simple_stmt->simple_stmt_type)
  {
    case simple_stmt_type_assignment_stmt:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_assginment_stmt(
          simple_stmt->simple_stmt_assignment_stmt,
          indent_level,
          semantics
        )
      );
      break;
    case simple_stmt_type_expr_list:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_expr_list(
          simple_stmt->simple_stmt_expr_list,
          indent_level,
          semantics
        )
      );
      break;
    case simple_stmt_type_func_declaration:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_func_dec(
          simple_stmt->simple_stmt_func_declaration,
          indent_level,
          semantics
        )
      );
      break;
    case simple_stmt_type_import_stmt:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_import_stmt(
          simple_stmt->simple_stmt_import_stmt,
          indent_level,
          semantics
        )
      );
      break;
    case simple_stmt_type_decorator:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_decorator(
          simple_stmt->simple_stmt_decorator,
          indent_level,
          semantics
        )
      );
      break;
    case simple_stmt_type_declaration:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_declaration(
          simple_stmt->simple_stmt_declaration,
          indent_level,
          semantics
        )
      );
      break;
    default:
      HEX_SEMANTICS_ERROR("Unknown type for HexSimpleStmt");
      break;
  }

  return 1;
}

int
hex_semantics_check_assginment_stmt(
  AssignmentStmt assignment_stmt, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(assignment_stmt);
  HEX_ASSERT(semantics);

  return 1;
}


int
hex_semantics_check_declaration(
  Declaration declaration, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(declaration);
  HEX_ASSERT(semantics);

  ExprList _exprlist = declaration->expr_list;
  HEX_ASSERT(_exprlist);

  while(_exprlist->next) {
    Expr _expr = _exprlist->expr;
    HEX_ASSERT(_expr);

    char *identifier_name = NULL;

    HEX_SEMANTICS_CHECK_AND_RETURN(
      _hex_semantics_check_and_get_identifier_from_expr(
        _expr,
        &identifier_name,
        semantics
      )
    );

    HEX_ASSERT(identifier_name);

    VtableEntry entry = vtable_lookup(
      semantics->vtable,
      identifier_name,
      indent_level
    );

    if(entry) {
      HEX_SEMANTICS_RETURN_ERR(
        semantics,
        HEX_SEMANTICS_ERROR_REPEATED_VARIABLE_DECLARATION,
        HEX_SEMANTICS_ERROR_REPEATED_VARIABLE_DECLARATION_ERR_MSG_FMT,
        identifier_name
      );
    }

    void *p = vtable_put(
      semantics->vtable,
      0, /* scope type */
      identifier_name,
      0, /* type */
      0, /* type qualifier */
      indent_level
    );

    HEX_ASSERT(p);

    _exprlist = _exprlist->next;
  }

  return 1;
}

int
hex_semantics_check_decorator(
  Decorator decorator, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(decorator);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_expr_list(
  ExprList exprlist, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(exprlist);
  HEX_ASSERT(semantics);

  ExprList _exprlist = exprlist;

  while(_exprlist) {
    Expr _expr = _exprlist->expr;
    HEX_ASSERT(_expr);

    HEX_SEMANTICS_CHECK_AND_RETURN(
      hex_semantics_check_expr(
        _expr,
        indent_level,
        semantics
      )
    );

    _exprlist = _exprlist->next;
  }

  return 1;
}

int
hex_semantics_check_func_dec(
  FuncDec func_dec, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(func_dec);
  HEX_ASSERT(semantics);

  HEX_SEMANTICS_CHECK_FUNC_DECLARATION_AND_RETURN(semantics, func_dec);

  GOTO_IF_NULL(func_dec->return_type_qualifier_list, _goto_check_paramlist);

  int res=0;
  res = hex_semantics_check_type_qualifier_list(
          func_dec->return_type_qualifier_list,
          indent_level,
          semantics
        );

  if(res == 0) {
    HEX_SEMANTICS_RETURN_ERR(
      semantics,
      HEX_SEMANTICS_ERROR_REPEATED_TYPE_QUALIFIER,
      HEX_SEMANTICS_ERROR_REPEATED_TYPE_QUALIFIER_ERR_MSG_FMT,
      func_dec->func_name
    );
  }


_goto_check_paramlist:

  if(func_dec->parameter_list) {
    HEX_SEMANTICS_CHECK_AND_RETURN(
      hex_semantics_check_parameter_list(
        func_dec->parameter_list,
        func_dec->func_name,
        semantics
      )
    );
  }

  FtableEntry entry = ftable_put(
    semantics->ftable,
    func_dec->func_name,
    0, /* TODO: return type */
    func_dec->parameter_list
  );

  HEX_ASSERT(entry);

  return 1;
}

int
hex_semantics_check_import_stmt(
  ImportStmt import_stmt, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(import_stmt);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_type_qualifier_list(
  TypeQualifierList qualifier_list, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(qualifier_list);
  HEX_ASSERT(semantics);

  TypeQualifierList _qualifier_list = qualifier_list;

  TypeQualifier _and=0;

  while(_qualifier_list) {
    TypeQualifier type_qualifier = _qualifier_list->type_qualifier;

    TypeQualifier and_ = _and;
    if((_and ^= (0x01<<type_qualifier)) < and_) {
      return 0;
    }

    _qualifier_list = _qualifier_list->next;
  }

  return 1;
}

int
hex_semantics_check_parameter_list(
  ParameterList paramlist, char *func_name, Semantics semantics)
{
  HEX_ASSERT(paramlist);
  HEX_ASSERT(semantics);

  ParameterList _paramlist = paramlist;

  Vtable _vtable = vtable_create();
  HEX_ASSERT(_vtable);

  while(_paramlist) {
    Parameter param = _paramlist->parameter;
    HEX_ASSERT(param);

    VtableEntry entry = vtable_lookup(_vtable, param->parameter_name, 0);

    if(entry) {  
      HEX_SEMANTICS_RETURN_ERR(
        semantics,
        HEX_SEMANTICS_ERROR_REPEATED_PARAMETER_DECLARATION,
        HEX_SEMANTICS_ERROR_REPEATED_PARAMETER_DECLARATION_ERR_MSG_FMT,
        param->parameter_name,
        func_name
      );
    }

    /* type checking
     * ...*/

    _paramlist = _paramlist->next;
  };

  vtable_free(&_vtable);

  return 1;
}

int
hex_semantics_check_expr(
  Expr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  switch(expr->expr_type)
  {
    case expr_type_primary:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_primary_expr(
          expr->primary_expr,
          indent_level,
          semantics
        )
      );
      break;
    case expr_type_postfix:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_postfix_expr(
          expr->postfix_expr,
          indent_level,
          semantics
        )
      );
      break;
    case expr_type_unary:
      break;
    case expr_type_cast:
      break;
    case expr_type_arithmetic:
      break;
    case expr_type_equality:
      break;
    case expr_type_logic:
      break;
    case expr_type_bitwise:
      break;
    case expr_type_conditional:
      break;
    case expr_type_range:
      break;
    case expr_type_lock:
      break;
    case expr_type_weakref:
      break;
    case expr_type_this:
      break;
    case expr_type_base:
      break;
    default:
      HEX_SEMANTICS_ERROR("Unknown type for HexExpr");
      break;
  }

  return 1;
}

int
hex_semantics_check_primary_expr(
  PrimaryExpr primary_expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(primary_expr);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_postfix_expr(
  PostfixExpr postfix_expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(postfix_expr);
  HEX_ASSERT(semantics);

  switch(postfix_expr->postfix_expr_type)
  {
    case postfix_expr_type_index:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_postfix_index_expr(
          postfix_expr->postfix_expr_index_expr,
          indent_level,
          semantics
        )
      );
      break;
    case postfix_expr_type_postfix_inc:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_postfix_inc_dec_expr(
          postfix_expr->postfix_expr_postfix_inc_expr,
          indent_level,
          semantics
        )
      );
      break;
    case postfix_expr_type_postfix_dec:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_postfix_inc_dec_expr(
          postfix_expr->postfix_expr_postfix_dec_expr,
          indent_level,
          semantics
        )
      );
      break;
    case postfix_expr_type_accessor:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_postfix_accessor_expr(
          postfix_expr->postfix_expr_accessor_expr,
          indent_level,
          semantics
        )
      );
      break;
    case postfix_expr_type_invocation:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_postfix_invocation_expr(
          postfix_expr->postfix_expr_invocation_expr,
          indent_level,
          semantics
        )
      );
      break;
    case postfix_expr_type_invocation_with_args:
      HEX_SEMANTICS_CHECK_AND_RETURN(
        hex_semantics_check_postfix_invocation_with_args_expr(
          postfix_expr->postfix_expr_invocation_with_args_expr,
          indent_level,
          semantics
        )
      );
      break;
    default:
      HEX_SEMANTICS_ERROR("Unknown type for HexPostfixExpr");
      break;
  }

  return 1;
}

int
hex_semantics_check_postfix_index_expr(
  PostfixIndexExpr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  switch(expr->postfix_index_expr_type)
  {
    case postfix_index_expr_type_identifier:
      break;
    case postfix_index_expr_type_expr:
      HEX_ASSERT(expr->index_expr);
      Expr _expr = expr->index_expr;

      switch(_expr->expr_type)
      {
        case expr_type_primary:
          HEX_SEMANTICS_CHECK_AND_RETURN(
            hex_semantics_check_primary_expr(
              _expr->primary_expr,
              indent_level,
              semantics
            )
          );
          break;
        case expr_type_postfix:
          HEX_SEMANTICS_CHECK_AND_RETURN(
            hex_semantics_check_postfix_expr(
              _expr->postfix_expr,
              indent_level,
              semantics
            )
          );
          break;
        case expr_type_unary:
          HEX_SEMANTICS_CHECK_AND_RETURN(
            hex_semantics_check_unary_expr(
              _expr->unary_expr,
              indent_level,
              semantics
            )
          );
          break;
        case expr_type_cast:
          HEX_SEMANTICS_CHECK_AND_RETURN(
            hex_semantics_check_cast_expr(
              _expr->cast_expr,
              indent_level,
              semantics
            )
          );
          break;
        case expr_type_arithmetic:
          HEX_SEMANTICS_CHECK_AND_RETURN(
            hex_semantics_check_arithmetic_expr(
              _expr->arithmetic_expr,
              indent_level,
              semantics
            )
          );
          break;
        case expr_type_equality:
          HEX_SEMANTICS_RETURN_ERR(
            semantics,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND_ERR_MSG_FMT,
            "Equality expression"
          );
          break;
        case expr_type_logic:
          HEX_SEMANTICS_RETURN_ERR(
            semantics,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND_ERR_MSG_FMT,
            "Logic expression"
          );
          break;
        case expr_type_bitwise:
          HEX_SEMANTICS_RETURN_ERR(
            semantics,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND_ERR_MSG_FMT,
            "Bitwise expression"
          );
          break;
        case expr_type_conditional:
          HEX_SEMANTICS_CHECK_AND_RETURN(
            hex_semantics_check_conditional_expr(
              _expr->conditional_expr,
              indent_level,
              semantics
            )
          );
          break;
        case expr_type_range:
          HEX_SEMANTICS_CHECK_AND_RETURN(
            hex_semantics_check_range_expr(
              _expr->range_expr,
              indent_level,
              semantics
            )
          );
          break;
        case expr_type_lock:
          HEX_SEMANTICS_RETURN_ERR(
            semantics,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND_ERR_MSG_FMT,
            "Lock expression"
          );
          break;
        case expr_type_weakref:
          HEX_SEMANTICS_RETURN_ERR(
            semantics,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND,
            HEX_SEMANTICS_ERROR_WRONG_EXPR_FOUND_ERR_MSG_FMT,
            "Weakref expression"
          );
          break;
        case expr_type_this:
          HEX_SEMANTICS_CHECK_AND_RETURN(
            hex_semantics_check_this_expr(
              _expr->this_expr,
              indent_level,
              semantics
            )
          );
          break;
        case expr_type_base:
          HEX_SEMANTICS_CHECK_AND_RETURN(
            hex_semantics_check_base_expr(
              _expr->base_expr,
              indent_level,
              semantics
            )
          );
          break;
        default:
          HEX_SEMANTICS_ERROR("Unknown type for HexExpr");
      }
      break;
    default:
      HEX_SEMANTICS_ERROR("Unknown type for HexPostfixIndexExpr");
      break;
  }

  return 1;
}

int
hex_semantics_check_postfix_inc_dec_expr(
  Expr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_postfix_accessor_expr(
  PostfixAccessorExpr accessor_expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(accessor_expr);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_postfix_invocation_expr(
  PostfixInvocationExpr invocation_expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(invocation_expr);
  HEX_ASSERT(semantics);

  switch(invocation_expr->postfix_invocation_expr_type)
  {
    case postfix_invocation_expr_type_identifier:
      HEX_SEMANTICS_LOOKUP_FUNCTION_BY_NAME(
        semantics,
        invocation_expr->invocation_name
      );
      break;
    case postfix_invocation_expr_type_expr:
      break;
    default:
      HEX_SEMANTICS_ERROR("Unknown type for HexPostfixInvocationExpr");
      break;
  }


  return 1;
}

int
hex_semantics_check_postfix_invocation_with_args_expr(
  PostfixInvocationWithArgsExpr invocation_expr,
  unsigned int indent_level,
  Semantics semantics)
{
  HEX_ASSERT(invocation_expr);
  HEX_ASSERT(semantics);

  switch(invocation_expr->postfix_invocation_expr_with_args_type)
  {
    case postfix_invocation_expr_with_args_type_identifier:
      HEX_SEMANTICS_LOOKUP_FUNCTION_BY_NAME(
        semantics,
        invocation_expr->invocation_name
      );
      break;
    case postfix_invocation_expr_with_args_type_expr:
      break;
    default:
      HEX_SEMANTICS_ERROR("Unknown type for HexPostfixInvocationWithArgsExpr");
      break;
  }

  return 1;
}

int
hex_semantics_check_range_expr(
  RangeExpr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_arithmetic_expr(
  ArithmeticExpr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_cast_expr(
  CastExpr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_conditional_expr(
  ConditionalExpr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_unary_expr(
  UnaryExpr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_this_expr(
  ThisExpr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  return 1;
}

int
hex_semantics_check_base_expr(
  BaseExpr expr, unsigned int indent_level, Semantics semantics)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(semantics);

  return 1;
}
