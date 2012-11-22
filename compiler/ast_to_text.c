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

#include <stdio.h>
#include "../base/assert.h"
#include "../base/cutils.h"
#include "ast_to_text.h"

#define AST_TO_TEXT_ERROR(msg)                                                  \
  fprintf(stderr, "%s, at %s[line %u]\n", msg, __FILE__, __LINE__);             \
  abort();

#define HEX_TYPE_SPECIFIERS_COUNT 10
char *HEX_TYPE_SPECIFIERS[HEX_TYPE_SPECIFIERS_COUNT] =
{
  "short",
  "char",
  "int",
  "long",
  "float",
  "double",
  "uchar",
  "ushort",
  "uint",
  "ulong"
};

#define HEX_EQUALITY_OPERATORS_COUNT 8
char *HEX_EQUALITY_OPERATORS[HEX_EQUALITY_OPERATORS_COUNT] =
{
  "==",
  "!=",
  "<",
  ">",
  "<=",
  ">=",
  "is",
  "is not"
};

#define HEX_LOGIC_OPERATORS_COUNT 2
char *HEX_LOGIC_OPERATORS[HEX_LOGIC_OPERATORS_COUNT] =
{
  "and",
  "or"
};

#define HEX_BITWISE_OPERATORS_COUNT 5
char *HEX_BITWISE_OPERATORS[HEX_BITWISE_OPERATORS_COUNT] =
{
  "<<",
  ">>",
  "&",
  "|",
  "^"
};

#define HEX_ASSIGNMENT_OPERATORS_COUNT 15
char *HEX_ASSIGNMENT_OPERATORS[HEX_ASSIGNMENT_OPERATORS_COUNT] =
{
  "=",
  "~=",
  "= new",
  "= lazy new",
  "*=",
  "/=",
  "%=",
  "+=",
  "-=",
  "<<=",
  ">>=",
  "!=",
  "&=",
  "|=",
  "^="
};

void hex_ast_type_specifier_to_text(int type_specifier, Strbuf strbuf)
{
  HEX_ASSERT(strbuf);

  if(type_specifier < 0 || type_specifier >= HEX_TYPE_SPECIFIERS_COUNT) {
    AST_TO_TEXT_ERROR("Unknwon HexTypeSpecifier value");
  }

  strbuf_append(strbuf, HEX_TYPE_SPECIFIERS[type_specifier]);
  strbuf_append(strbuf, " ");
}

void hex_ast_integer_to_text(Integer integer, Strbuf strbuf)
{
  HEX_ASSERT(integer);
  HEX_ASSERT(strbuf);

  char *str=NULL;

  switch(integer->integer_type)
  {
    case integer_type_decimal:
      {
        str = itoa(integer->unsigned_integer, str, 10);
        HEX_ASSERT(str);
        strbuf_append(strbuf, str);
      }
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexInteger type");
      break;
  }
}

void hex_ast_literal_to_text(Literal literal, Strbuf strbuf)
{
  HEX_ASSERT(literal);
  HEX_ASSERT(strbuf);

  switch(literal->literal_type)
  {
    case literal_type_string:
      strbuf_append(strbuf, literal->literal_string);
      break;
    case literal_type_integer:
      hex_ast_integer_to_text(literal->literal_integer, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexLiteral type");
      break;
  }
}

void hex_ast_primary_expr_to_text(PrimaryExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  switch(expr->primary_expr_type)
  {
    case primary_expr_type_identifier:
      strbuf_append(strbuf, expr->primary_expr_identifier);
      break;
    case primary_expr_type_literal:
      hex_ast_literal_to_text(expr->primary_expr_literal, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexPrimaryExpr type");
      break;
  }
}

void hex_ast_postfix_accessor_expr_to_text(PostfixAccessorExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);
  HEX_ASSERT(expr->accessor);

  hex_ast_expr_to_text(expr->caller, strbuf);
  strbuf_append(strbuf, ".");
  strbuf_append(strbuf, expr->accessor);
}

void hex_ast_postfix_invocation_expr_to_text(PostfixInvocationExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);
  HEX_ASSERT(expr->invocation_name);

  switch(expr->postfix_invocation_expr_type)
  {
    case postfix_invocation_expr_type_expr:
      hex_ast_expr_to_text(expr->invocation_expr, strbuf);
      strbuf_append(strbuf, "()");
      break;
    case postfix_invocation_expr_type_identifier:
      strbuf_append(strbuf, expr->invocation_name);
      strbuf_append(strbuf, "()");
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexPostfixInvocationExpr type");
      break;
  }
}

void hex_ast_postfix_invocation_with_args_expr_to_text(PostfixInvocationWithArgsExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  switch(expr->postfix_invocation_expr_with_args_type)
  {
    case postfix_invocation_expr_with_args_type_expr:
      hex_ast_expr_to_text(expr->invocation_expr, strbuf);
      break;
    case postfix_invocation_expr_with_args_type_identifier:
      strbuf_append(strbuf, expr->invocation_name);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexPostfixInvocationWithArgsExpr type");
      break;
  }

  strbuf_append(strbuf, "(");
  hex_ast_exprlist_to_text(expr->arg_list, strbuf);
  strbuf_append(strbuf, ")");
}

void hex_ast_postfix_index_expr_to_text(PostfixIndexExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  switch(expr->postfix_index_expr_type)
  {
    case postfix_index_expr_type_identifier:
      strbuf_append(strbuf, expr->identifier);
      break;
    case postfix_index_expr_type_expr: 
      hex_ast_expr_to_text(expr->index_expr, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexPostfixIndexExpr type");
      break;
  }

  strbuf_append(strbuf, "[");
  hex_ast_exprlist_to_text(expr->indeces_list, strbuf);
  strbuf_append(strbuf, "]");
}

void hex_ast_postfix_expr_to_text(PostfixExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  switch(expr->postfix_expr_type)
  {
    case postfix_expr_type_index:
      hex_ast_postfix_index_expr_to_text(expr->postfix_expr_index_expr, strbuf);
      break;
    case postfix_expr_type_postfix_inc:
      hex_ast_expr_to_text(expr->postfix_expr_postfix_inc_expr, strbuf);
      strbuf_append(strbuf, "++");
      break;
    case postfix_expr_type_postfix_dec:
      hex_ast_expr_to_text(expr->postfix_expr_postfix_dec_expr, strbuf);
      strbuf_append(strbuf, "--");
      break;
    case postfix_expr_type_accessor:
      hex_ast_postfix_accessor_expr_to_text(expr->postfix_expr_accessor_expr, strbuf);
      break;
    case postfix_expr_type_invocation:
      hex_ast_postfix_invocation_expr_to_text(expr->postfix_expr_invocation_expr, strbuf);
      break;
    case postfix_expr_type_invocation_with_args:
      hex_ast_postfix_invocation_with_args_expr_to_text(expr->postfix_expr_invocation_with_args_expr, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexPostfixExpr type");
      break;
  }
}

void hex_ast_unary_expr_to_text(UnaryExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  switch(expr->unary_expr_type)
  {
    case unary_expr_type_prefix_inc:
      strbuf_append(strbuf, "++");
      hex_ast_expr_to_text(expr->unary_expr_prefix_inc_expr, strbuf);
      break;
    case unary_expr_type_prefix_dec:
      strbuf_append(strbuf, "--");
      hex_ast_expr_to_text(expr->unary_expr_prefix_dec_expr, strbuf);
      break;
    case unary_expr_type_unary_minus:
      strbuf_append(strbuf, "-");
      hex_ast_expr_to_text(expr->unary_expr_unary_expr, strbuf);
      break;
    case unary_expr_type_not:
      strbuf_append(strbuf, "not ");
      hex_ast_expr_to_text(expr->unary_expr_not, strbuf);
      break;
    case unary_expr_type_bitwise_not:
      strbuf_append(strbuf, "~");
      hex_ast_expr_to_text(expr->unary_expr_bitwise_not, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexUnaryExpr type");
      break;
  }
}

void hex_ast_additive_expr_to_text(AdditiveExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  HEX_ASSERT(expr->left_expr);
  HEX_ASSERT(expr->right_expr);

  char *operator = NULL;

  switch(expr->additive_expr_type)
  {
    case additive_expr_type_plus:
      operator = " + ";
      break;
    case additive_expr_type_minus:
      operator = " - ";
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexAdditiveExpr type");
      break;
  }

  hex_ast_expr_to_text(expr->left_expr, strbuf);
  strbuf_append(strbuf, operator);
  hex_ast_expr_to_text(expr->right_expr, strbuf);
}

void hex_ast_multiplicative_to_text(MultiplicativeExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  HEX_ASSERT(expr->left_expr);
  HEX_ASSERT(expr->right_expr);

  char *operator = NULL;

  switch(expr->multi_expr_type)
  {
    case multiplicative_expr_type_mul:
      operator = " * ";
      break;
    case multiplicative_expr_type_div:
      operator = " / ";
      break;
    case multiplicative_expr_type_mod:
      operator = " % ";
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexMultiplicativeExpr type");
      break;
  }

  hex_ast_expr_to_text(expr->left_expr, strbuf);
  strbuf_append(strbuf, operator);
  hex_ast_expr_to_text(expr->right_expr, strbuf);
}

void hex_ast_arithmetic_expr_to_text(ArithmeticExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  switch(expr->arithmetic_expr_type)
  {
    case arithmetic_expr_type_additive:
      hex_ast_additive_expr_to_text(expr->arithmetic_expr_additive_expr, strbuf);
      break;
    case arithmetic_expr_type_multiplicative:
      hex_ast_multiplicative_to_text(expr->arithmetic_expr_multiplicative_expr, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexArithmeticExpr type");
      break;
  }
}

void hex_ast_equality_expr_to_text(EqualityExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  char *operator = NULL;

  HEX_ASSERT(expr->equality_expr_type >= 0);
  HEX_ASSERT(expr->equality_expr_type < HEX_EQUALITY_OPERATORS_COUNT);

  operator = HEX_EQUALITY_OPERATORS[expr->equality_expr_type];

  hex_ast_expr_to_text(expr->left_expr, strbuf);
  strbuf_append(strbuf, " ");
  strbuf_append(strbuf, operator);
  strbuf_append(strbuf, " ");
  hex_ast_expr_to_text(expr->right_expr, strbuf);
}

void hex_ast_logic_expr_to_text(LogicExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  char *operator = NULL;

  HEX_ASSERT(expr->logic_expr_type >= 0);
  HEX_ASSERT(expr->logic_expr_type <= HEX_LOGIC_OPERATORS_COUNT);

  operator = HEX_LOGIC_OPERATORS[expr->logic_expr_type];

  hex_ast_expr_to_text(expr->left_expr, strbuf);
  strbuf_append(strbuf, " ");
  strbuf_append(strbuf, operator);
  strbuf_append(strbuf, " ");
  hex_ast_expr_to_text(expr->right_expr, strbuf);
}

void hex_ast_bitwise_expr_to_text(BitwiseExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  if(expr->bitwise_expr_type < 0 || expr->bitwise_expr_type >= HEX_BITWISE_OPERATORS_COUNT) {
    AST_TO_TEXT_ERROR("Unknwon HexBitwiseExpr type");
  }

  hex_ast_expr_to_text(expr->left_expr, strbuf);
  strbuf_append(strbuf, " ");
  strbuf_append(strbuf, HEX_BITWISE_OPERATORS[expr->bitwise_expr_type]);
  strbuf_append(strbuf, " ");
  hex_ast_expr_to_text(expr->right_expr, strbuf);
}

void hex_ast_conditional_expr_to_text(ConditionalExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  HEX_ASSERT(expr->predicate_expr);
  HEX_ASSERT(expr->alternative_expr);
  HEX_ASSERT(expr->consequent_expr);

  strbuf_append(strbuf, "if ");
  hex_ast_expr_to_text(expr->predicate_expr, strbuf);
  strbuf_append(strbuf, " then ");
  hex_ast_expr_to_text(expr->consequent_expr, strbuf);
  strbuf_append(strbuf, " else ");
  hex_ast_expr_to_text(expr->alternative_expr, strbuf);
}

void hex_ast_range_expr_to_text(RangeExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  HEX_ASSERT(expr->left_expr);
  HEX_ASSERT(expr->right_expr);

  hex_ast_expr_to_text(expr->left_expr, strbuf);
  strbuf_append(strbuf, "...");
  hex_ast_expr_to_text(expr->right_expr, strbuf);
}

void hex_ast_lock_expr_to_text(LockExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  char *keyword = expr->is_lock ? "lock " : "unlock ";

  strbuf_append(strbuf, keyword);
  hex_ast_expr_to_text(expr->expr, strbuf);
}

void hex_ast_weakref_expr_to_text(WeakrefExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "_weakref ");
  hex_ast_expr_to_text(expr->expr, strbuf);
}

void hex_ast_cast_expr_to_text(CastExpr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  char *cast_type=NULL;

  if(expr->cast_expr_type == cast_expr_type_type_specifier) {
    HEX_ASSERT(expr->type_specifier >= 0);
    HEX_ASSERT(expr->type_specifier < HEX_TYPE_SPECIFIERS_COUNT);
    cast_type = HEX_TYPE_SPECIFIERS[expr->type_specifier];
  } else if(expr->cast_expr_type == cast_expr_type_custom_type) {
    HEX_ASSERT(expr->identifier);
    cast_type = expr->identifier;
  }

  strbuf_append(strbuf, "(");
  strbuf_append(strbuf, cast_type);
  strbuf_append(strbuf, ")");
  hex_ast_expr_to_text(expr->expr, strbuf);
}

void hex_ast_expr_to_text(Expr expr, Strbuf strbuf)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(strbuf);

  switch(expr->expr_type)
  {
    case expr_type_primary:
      hex_ast_primary_expr_to_text(expr->primary_expr, strbuf);
      break;
    case expr_type_postfix:
      hex_ast_postfix_expr_to_text(expr->postfix_expr, strbuf);
      break;
    case expr_type_unary:
      hex_ast_unary_expr_to_text(expr->unary_expr, strbuf);
      break;
    case expr_type_cast:
      hex_ast_cast_expr_to_text(expr->cast_expr, strbuf);
      break;
    case expr_type_arithmetic:
      hex_ast_arithmetic_expr_to_text(expr->arithmetic_expr, strbuf);
      break;
    case expr_type_equality:
      hex_ast_equality_expr_to_text(expr->equality_expr, strbuf);
      break;
    case expr_type_logic:
      hex_ast_logic_expr_to_text(expr->logic_expr, strbuf);
      break;
    case expr_type_bitwise:
      hex_ast_bitwise_expr_to_text(expr->bitwise_expr, strbuf);
      break;
    case expr_type_conditional:
      hex_ast_conditional_expr_to_text(expr->conditional_expr, strbuf);
      break;
    case expr_type_range:
      hex_ast_range_expr_to_text(expr->range_expr, strbuf);
      break;
    case expr_type_lock:
      hex_ast_lock_expr_to_text(expr->lock_expr, strbuf);
      break;
    case expr_type_weakref:
      hex_ast_weakref_expr_to_text(expr->weakref_expr, strbuf);
      break;
    case expr_type_this:
      break;
    case expr_type_base:
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexExpr type");
      break;
  }
}

void hex_ast_exprlist_to_text(ExprList exprlist, Strbuf strbuf)
{
  HEX_ASSERT(exprlist);
  HEX_ASSERT(strbuf);

  while(exprlist) {
    Expr expr = exprlist->expr;
    hex_ast_expr_to_text(expr, strbuf);

    if(exprlist->next) {
      strbuf_append(strbuf, ", ");
    }

    exprlist = exprlist->next;
  }
}

void hex_ast_list_initializer_to_text(ListInitializer list, Strbuf strbuf)
{
  HEX_ASSERT(list);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "[");
  hex_ast_exprlist_to_text(list->expr_list, strbuf);
  strbuf_append(strbuf, "]");
}

void hex_ast_array_initializer_to_text(ArrayInitializer array, Strbuf strbuf)
{
  HEX_ASSERT(array);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "{");
  hex_ast_exprlist_to_text(array->expr_list, strbuf);
  strbuf_append(strbuf, "}");
}

void hex_ast_tuple_initializer_to_text(TupleInitializer tuple, Strbuf strbuf)
{
  HEX_ASSERT(tuple);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "(");
  hex_ast_exprlist_to_text(tuple->expr_list, strbuf);
  strbuf_append(strbuf, ")");
}

void hex_ast_struct_initializer_to_text(StructInitializer struct_initializer, Strbuf strbuf)
{
  HEX_ASSERT(struct_initializer);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "{");
  hex_ast_assignment_stmt_list_to_text(struct_initializer->assignment_stmt_list, strbuf);
  strbuf_append(strbuf, "}");
}

void hex_ast_set_initializer_to_text(SetInitializer set, Strbuf strbuf)
{
  HEX_ASSERT(set);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "[(");
  hex_ast_exprlist_to_text(set->expr_list, strbuf);
  strbuf_append(strbuf, ")]");
}

void hex_ast_initializer_to_text(Initializer initializer, Strbuf strbuf)
{
  HEX_ASSERT(initializer);
  HEX_ASSERT(strbuf);

  switch(initializer->initializer_type)
  {
    case initializer_type_list:
      hex_ast_list_initializer_to_text(initializer->list_initializer, strbuf);
      break;
    case initializer_type_array:
      hex_ast_array_initializer_to_text(initializer->array_initializer, strbuf); 
      break;
    case initializer_type_tuple:
      hex_ast_tuple_initializer_to_text(initializer->tuple_initializer, strbuf);
      break;
    case initializer_type_struct:
      hex_ast_struct_initializer_to_text(initializer->struct_initializer, strbuf);
      break;
    case initializer_type_set:
      hex_ast_set_initializer_to_text(initializer->set_initializer, strbuf);
      break;
    case initializer_type_mapmultimap:
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexInitializer type");
      break;
  }
}

void hex_ast_declaration_to_text(Declaration declaration, Strbuf strbuf)
{
  HEX_ASSERT(declaration);
  HEX_ASSERT(strbuf);

  if(declaration->custom_type) {
    strbuf_append(strbuf, declaration->custom_type);
    strbuf_append(strbuf, " ");
  } else {
    hex_ast_type_specifier_to_text(declaration->type_specifier, strbuf);
  }

  hex_ast_exprlist_to_text(declaration->expr_list, strbuf);
}

void hex_ast_assignment_to_text(Assignment assignment, Strbuf strbuf)
{
  HEX_ASSERT(assignment);
  HEX_ASSERT(strbuf);

  HEX_ASSERT(assignment->assignment_op >= 0);
  HEX_ASSERT(assignment->assignment_op < HEX_ASSIGNMENT_OPERATORS_COUNT);

  char *operator = HEX_ASSIGNMENT_OPERATORS[assignment->assignment_op];

  switch(assignment->assignment_type)
  {
    case assignment_type_expr:
      strbuf_append(strbuf, " ");
      strbuf_append(strbuf, operator);
      strbuf_append(strbuf, " ");
      hex_ast_expr_to_text(assignment->assignment_expr, strbuf);
      break;
    case assignment_type_initializer:
      strbuf_append(strbuf, " ");
      strbuf_append(strbuf, operator);
      strbuf_append(strbuf, " ");
      hex_ast_initializer_to_text(assignment->assignment_initializer, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexAssignment type");
      break;
  }
}

void hex_ast_assignment_list_to_text(AssignmentList list, Strbuf strbuf)
{
  HEX_ASSERT(list);
  HEX_ASSERT(strbuf);

  AssignmentList _list = list;

  while(list) {
    Assignment assignment = list->assignment;
    hex_ast_assignment_to_text(assignment, strbuf);
    list = list->next;
  }
}

void hex_ast_assignment_stmt_to_text(AssignmentStmt stmt, Strbuf strbuf)
{
  HEX_ASSERT(stmt);
  HEX_ASSERT(strbuf);

  switch(stmt->assignment_stmt_type)
  {
    case assignment_stmt_type_expr_list:
      hex_ast_exprlist_to_text(stmt->assignment_stmt_expr_list, strbuf);
      break;
    case assignment_stmt_type_declaration:
      hex_ast_declaration_to_text(stmt->assignment_stmt_declaration, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknwon HexAssignmentStmt type");
      break;
  }

  hex_ast_assignment_list_to_text(stmt->assignment_list, strbuf);
}

void hex_ast_simple_stmt_to_text(SimpleStmt stmt, Strbuf strbuf)
{
  HEX_ASSERT(stmt);
  HEX_ASSERT(strbuf);

  switch(stmt->simple_stmt_type)
  {
    case simple_stmt_type_assignment_stmt:
      hex_ast_assignment_stmt_to_text(stmt->simple_stmt_assignment_stmt, strbuf);
      break;
    case simple_stmt_type_expr_list:
      hex_ast_exprlist_to_text(stmt->simple_stmt_expr_list, strbuf);
    default:
      AST_TO_TEXT_ERROR("Unknown HexSimpleStmt type");
      break;
  }
}

void hex_ast_simple_stmt_list_to_text(SimpleStmtList list, Strbuf strbuf)
{
  HEX_ASSERT(list);
  HEX_ASSERT(strbuf);

  while(list) {
    SimpleStmt stmt = list->simple_stmt;
    hex_ast_simple_stmt_to_text(stmt, strbuf);

    list = list->next;
    if(list) strbuf_append(strbuf, "\n");
  }
}

void hex_ast_stmt_to_text(Stmt stmt, Strbuf strbuf)
{
  HEX_ASSERT(stmt);
  HEX_ASSERT(strbuf);

  switch(stmt->stmt_type)
  {
    case stmt_type_simple_stmt_list:
      hex_ast_simple_stmt_list_to_text(stmt->stmt_simple_stmt_list, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexStmt type");
      break;
  }
}

void hex_ast_assignment_stmt_list_to_text(AssignmentStmtList stmt_list, Strbuf strbuf)
{
  HEX_ASSERT(stmt_list);
  HEX_ASSERT(strbuf);

  AssignmentStmtList _list = stmt_list;
  while(_list) {
    AssignmentStmt stmt = _list->assignment_stmt;
    hex_ast_assignment_stmt_to_text(stmt, strbuf);

    if(_list->next) {
      strbuf_append(strbuf, ", ");
    }

    _list = _list->next;
  }
}

void hex_ast_stmt_group_to_text(StmtGroup group, Strbuf strbuf)
{
  HEX_ASSERT(group);
  HEX_ASSERT(strbuf);

  while(group) {
    Stmt stmt = group->stmt;
    hex_ast_stmt_to_text(stmt, strbuf);
    group = group->next;
  }
}
