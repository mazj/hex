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
  "char",
  "short",
  "int",
  "long",
  "float",
  "double",
  "uchar",
  "ushort",
  "uint",
  "ulong"
};

#define HEX_TYPE_QUALIFIERS_COUNT 3
char *HEX_TYPE_QUALIFIERS[HEX_TYPE_QUALIFIERS_COUNT] =
{
  "const",
  "volatile",
  "static"
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

void hex_ast_type_qualifier_list_to_text(TypeQualifierList type_qualifier_list, Strbuf strbuf)
{
  HEX_ASSERT(type_qualifier_list);
  HEX_ASSERT(strbuf);

  TypeQualifierList _list = type_qualifier_list;

  while(_list) {
    TypeQualifier type_qualifier = _list->type_qualifier;

    HEX_ASSERT(type_qualifier >= 0);
    HEX_ASSERT(type_qualifier < HEX_TYPE_QUALIFIERS_COUNT);

    strbuf_append(strbuf, HEX_TYPE_QUALIFIERS[type_qualifier]);

    if(_list->next) {
      strbuf_append(strbuf, " ");
    }

    _list = _list->next;
  }
}

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
    case literal_type_char:
      {
        char buf[2];
        snprintf(buf, sizeof(buf), "%c", literal->literal_char);
        strbuf_append(strbuf, "'");
        strbuf_append(strbuf, buf);
        strbuf_append(strbuf, "'");
      }
      break;
    case literal_type_float:
      {
        char buf[10];
        snprintf(buf, sizeof(buf), "%f", literal->literal_float);
        strbuf_append(strbuf, buf);
      }
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
  strbuf_append(strbuf, (char*)expr->accessor);
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

void hex_ast_map_initializer_to_text(MapInitializer map, Strbuf strbuf)
{
  HEX_ASSERT(map);
  HEX_ASSERT(strbuf);
  HEX_ASSERT(map->map_initializer_list);

  strbuf_append(strbuf, "{");

  MapInitializerList list = map->map_initializer_list;
  while(list) {
    MapInitializerSingle map_initializer_single = list->map_initializer_single;
    HEX_ASSERT(map_initializer_single);

    hex_ast_expr_to_text(map_initializer_single->key, strbuf);
    strbuf_append(strbuf, ": ");
    hex_ast_expr_to_text(map_initializer_single->value, strbuf);

    if(list->next) {
      strbuf_append(strbuf, ", ");
    }

    list = list->next;
  }

  strbuf_append(strbuf, "}");
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
    case initializer_type_map:
      hex_ast_map_initializer_to_text(initializer->map_initializer, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexInitializer type");
      break;
  }
}

void hex_ast_parameter_to_text(Parameter parameter, Strbuf strbuf)
{
  HEX_ASSERT(parameter);
  HEX_ASSERT(strbuf);
  HEX_ASSERT(parameter->parameter_name);

  if(parameter->is_ref) {
    strbuf_append(strbuf, "ref ");
  }

  if(parameter->type_qualifier_list) {
    hex_ast_type_qualifier_list_to_text(parameter->type_qualifier_list, strbuf);
    strbuf_append(strbuf, " ");
  }

  if(parameter->custom_type) {
    strbuf_append(strbuf, parameter->custom_type);
    strbuf_append(strbuf, " ");
  } else if(parameter->type_specifier >= 0) {
    HEX_ASSERT(parameter->type_specifier < HEX_TYPE_SPECIFIERS_COUNT);

    char *type = HEX_TYPE_SPECIFIERS[parameter->type_specifier];

    strbuf_append(strbuf, type);
    strbuf_append(strbuf, " ");
  }

  strbuf_append(strbuf, (char*)parameter->parameter_name);

  if(parameter->alias) {
    strbuf_append(strbuf, " as ");
    strbuf_append(strbuf, parameter->alias);
  }
}

void hex_ast_parameter_list_to_text(ParameterList paramlist, Strbuf strbuf)
{
  HEX_ASSERT(paramlist);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "(");

  ParameterList list = paramlist;
  while(list) {
    Parameter parameter = list->parameter;
    HEX_ASSERT(parameter);

    hex_ast_parameter_to_text(parameter, strbuf);

    if(list->next) {
      strbuf_append(strbuf, ", ");
    }

    list = list->next;
  }

  strbuf_append(strbuf, ")");
}

void hex_ast_lambda_expr_to_text(LambdaExpr lambda, Strbuf strbuf)
{
  HEX_ASSERT(lambda);
  HEX_ASSERT(strbuf);

  switch(lambda->lambda_type)
  {
    case lambda_type_simple:
      if(lambda->lambda_param_list) {
        hex_ast_parameter_list_to_text(lambda->lambda_param_list, strbuf);
      }

      strbuf_append(strbuf, " => ");

      strbuf_append(strbuf, "[");
      hex_ast_simple_stmt_list_to_text(lambda->lambda_simple_stmt_list, strbuf);
      strbuf_append(strbuf, "]");
      break;
    case lambda_type_suite:
      if(lambda->lambda_param_list) {
        hex_ast_parameter_list_to_text(lambda->lambda_param_list, strbuf);
      }

      strbuf_append(strbuf, " => ");

      hex_ast_suite_to_text(lambda->lambda_suite, 1, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexLambdaExpr type");
      break;
  }
}

void hex_ast_declaration_to_text(Declaration declaration, Strbuf strbuf)
{
  HEX_ASSERT(declaration);
  HEX_ASSERT(strbuf);

  if(declaration->type_qualifier_list) {
    hex_ast_type_qualifier_list_to_text(declaration->type_qualifier_list, strbuf);
    strbuf_append(strbuf, " ");
  }

  if(declaration->custom_type) {
    strbuf_append(strbuf, declaration->custom_type);
    strbuf_append(strbuf, " ");
  } else if(declaration->type_specifier >= 0) {
    hex_ast_type_specifier_to_text(declaration->type_specifier, strbuf);
  }

  hex_ast_exprlist_to_text(declaration->expr_list, strbuf);
}

void hex_ast_func_declaration_to_text(FuncDec func_dec, Strbuf strbuf)
{
  HEX_ASSERT(func_dec);
  HEX_ASSERT(func_dec->func_name);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "def ");

  if(func_dec->return_type_qualifier_list) {
    hex_ast_type_qualifier_list_to_text(func_dec->return_type_qualifier_list, strbuf);
    strbuf_append(strbuf, " ");
  }

  if(func_dec->custom_return_type) {
    strbuf_append(strbuf, func_dec->custom_return_type);
    strbuf_append(strbuf, " ");
  } else if(func_dec->return_type_specifier >= 0) {
    hex_ast_type_specifier_to_text(func_dec->return_type_specifier, strbuf);
  }

  strbuf_append(strbuf, func_dec->func_name);

  if(func_dec->parameter_list) {
    hex_ast_parameter_list_to_text(func_dec->parameter_list, strbuf);
  } else {
    strbuf_append(strbuf, "()");
  }
}

void hex_ast_module_list_to_text(ModuleList module_list, Strbuf strbuf)
{
  HEX_ASSERT(module_list);
  HEX_ASSERT(strbuf);

  ModuleList list = module_list;
  while(list) {
    Module module = list->module;
    HEX_ASSERT(module);
    HEX_ASSERT(module->module_identifier);

    strbuf_append(strbuf, module->module_identifier);

    if(list->next) {
      strbuf_append(strbuf, ".");
    }

    list = list->next;
  }
}

void hex_ast_direct_import_stmt_to_text(DirectImportStmt stmt, Strbuf strbuf)
{
  HEX_ASSERT(stmt);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "import ");

  hex_ast_module_list_to_text(stmt->module_list, strbuf);

  if(stmt->alias) {
    strbuf_append(strbuf, " as ");
    strbuf_append(strbuf, stmt->alias);
  }
}

void hex_ast_relative_import_stmt_to_text(RelativeImportStmt stmt, Strbuf strbuf)
{
  HEX_ASSERT(stmt);
  HEX_ASSERT(stmt->module);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "from ");

  hex_ast_module_list_to_text(stmt->module_list, strbuf);

  strbuf_append(strbuf, " import ");
  strbuf_append(strbuf, stmt->module->module_identifier);

  if(stmt->alias) {
    strbuf_append(strbuf, " as ");
    strbuf_append(strbuf, stmt->alias);
  }
}

void hex_ast_import_stmt_to_text(ImportStmt import_stmt, Strbuf strbuf)
{
  HEX_ASSERT(import_stmt);
  HEX_ASSERT(strbuf);

  switch(import_stmt->import_stmt_type)
  {
    case import_stmt_type_direct:
      hex_ast_direct_import_stmt_to_text(import_stmt->import_stmt_direct_import_stmt, strbuf);
      break;
    case import_stmt_type_relative:
      hex_ast_relative_import_stmt_to_text(import_stmt->import_stmt_relative_import_stmt, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexImportStmt type");
      break;
  }
}

void hex_ast_compiler_property_to_text(CompilerProperty compiler_property, Strbuf strbuf)
{
  HEX_ASSERT(compiler_property);
  HEX_ASSERT(strbuf);

  HEX_ASSERT(compiler_property->compiler_property_name);
  HEX_ASSERT(compiler_property->compiler_property_value);

  strbuf_append(strbuf, "#");
  strbuf_append(strbuf, compiler_property->compiler_property_name);
  strbuf_append(strbuf, "=");
  strbuf_append(strbuf, compiler_property->compiler_property_value);
}

void hex_ast_attribute_to_text(Attribute attribute, Strbuf strbuf)
{
  HEX_ASSERT(attribute);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "@");
  hex_ast_expr_to_text(attribute->expr, strbuf);
}

void hex_ast_decorator_to_text(Decorator decorator, Strbuf strbuf)
{
  HEX_ASSERT(decorator);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "[");

  DecoratorList decorator_list = decorator->decorator_list;
  while(decorator_list) {
    DecoratorListSingle decorator_list_single = decorator_list->decorator_list_single;
    HEX_ASSERT(decorator_list_single);

    switch(decorator_list_single->decorator_list_single_type)
    {
      case decorator_list_single_type_attribute:
        hex_ast_attribute_to_text(
          decorator_list_single->decorator_list_single_attribute, strbuf);
        break;
      case decorator_list_single_type_compiler_property:
        hex_ast_compiler_property_to_text(
          decorator_list_single->decorator_list_single_compiler_property, strbuf);
        break;
      default:
        AST_TO_TEXT_ERROR("Unknown HexDecorator type");
        break;
    }

    if(decorator_list->next) {
      strbuf_append(strbuf, ", ");
    }

    decorator_list = decorator_list->next;
  }

  strbuf_append(strbuf, "]");
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
    case assignment_type_lambda:
      strbuf_append(strbuf, " ");
      strbuf_append(strbuf, operator);
      strbuf_append(strbuf, " ");
      hex_ast_lambda_expr_to_text(assignment->assignment_lambda, strbuf);
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
      break;
    case simple_stmt_type_func_declaration:
      hex_ast_func_declaration_to_text(stmt->simple_stmt_func_declaration, strbuf);
      break;
    case simple_stmt_type_import_stmt:
      hex_ast_import_stmt_to_text(stmt->simple_stmt_import_stmt, strbuf);
      break;
    case simple_stmt_type_decorator:
      hex_ast_decorator_to_text(stmt->simple_stmt_decorator, strbuf);
      break;
    case simple_stmt_type_declaration:
      hex_ast_declaration_to_text(stmt->simple_stmt_declaration, strbuf);
      break;
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

    if(list->next) {
      strbuf_append(strbuf, "; ");
    }

    list = list->next;
  }
}

void hex_ast_if_stmt_to_text(IfStmt if_stmt, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(if_stmt);
  HEX_ASSERT(if_stmt->if_expr);
  HEX_ASSERT(if_stmt->if_suite);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "if ");
  hex_ast_expr_to_text(if_stmt->if_expr, strbuf);
  strbuf_append(strbuf, ":");
  hex_ast_suite_to_text(if_stmt->if_suite, indent_level+1, strbuf);

  if(if_stmt->elif_group) {
    hex_ast_elif_group_to_text(if_stmt->elif_group, indent_level, strbuf);
  }

  if(if_stmt->else_stmt) {
    strbuf_append(strbuf, "else:");
    hex_ast_suite_to_text(if_stmt->else_stmt, indent_level+1, strbuf);
  }
}

void hex_ast_elif_group_to_text(ElifGroup elif_group, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(elif_group);
  HEX_ASSERT(strbuf);

  ElifGroup _elif_group = elif_group;
  while(_elif_group) {
    ElifStmt elif_stmt = _elif_group->elif_stmt;
    HEX_ASSERT(elif_stmt);

    strbuf_append(strbuf, "elif ");
    hex_ast_expr_to_text(elif_stmt->elif_expr, strbuf);
    strbuf_append(strbuf, ":");
    hex_ast_suite_to_text(elif_stmt->elif_suite, indent_level+1, strbuf);

    _elif_group = _elif_group->next;
  }
}

void hex_ast_while_stmt_to_text(WhileStmt while_stmt, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(while_stmt);
  HEX_ASSERT(while_stmt->while_expr);
  HEX_ASSERT(while_stmt->while_suite);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "while ");
  hex_ast_expr_to_text(while_stmt->while_expr, strbuf);
  strbuf_append(strbuf, ":");
  hex_ast_suite_to_text(while_stmt->while_suite, indent_level+1, strbuf);
}

void hex_ast_iterable_to_text(Iterable iterable, Strbuf strbuf)
{
  HEX_ASSERT(iterable);
  HEX_ASSERT(strbuf);

  switch(iterable->iterable_type)
  {
    case iterable_type_expr:
      hex_ast_expr_to_text(iterable->iterable_expr, strbuf);
      break;
    case iterable_type_initializer:
      hex_ast_initializer_to_text(iterable->iterable_initializer, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexIterable type");
      break;
  }
}

void hex_ast_for_stmt_to_text(ForStmt for_stmt, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(for_stmt);
  HEX_ASSERT(for_stmt->expr);
  HEX_ASSERT(for_stmt->iterable);
  HEX_ASSERT(for_stmt->suite);

  strbuf_append(strbuf, "for ");
  hex_ast_expr_to_text(for_stmt->expr, strbuf);
  strbuf_append(strbuf, " in ");
  hex_ast_iterable_to_text(for_stmt->iterable, strbuf);

  if(for_stmt->where_expr) {
    strbuf_append(strbuf, " where ");
    hex_ast_expr_to_text(for_stmt->where_expr, strbuf);
  }

  strbuf_append(strbuf, ":");
  hex_ast_suite_to_text(for_stmt->suite, indent_level+1, strbuf);
}

void hex_ast_catch_stmt_to_text(CatchStmt catch_stmt, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(catch_stmt);
  HEX_ASSERT(strbuf);

  unsigned char _indent_level = indent_level;
  while(_indent_level > 0) {
    strbuf_append(strbuf, "  ");
    _indent_level--;
  }

  strbuf_append(strbuf, "catch");

  switch(catch_stmt->catch_stmt_type)
  {
    case catch_stmt_type_none:
      break;
    case catch_stmt_type_identifier:
      strbuf_append(strbuf, " ");
      strbuf_append(strbuf, "(");
      strbuf_append(strbuf, catch_stmt->catch_identifier);
      strbuf_append(strbuf, ")");
      break;
    case catch_stmt_type_declaration:
      strbuf_append(strbuf, " ");
      strbuf_append(strbuf, "(");
      hex_ast_declaration_to_text(catch_stmt->catch_declaration, strbuf);
      strbuf_append(strbuf, ")");
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexCatchStmt type");
      break;
  }

  strbuf_append(strbuf, ":");

  hex_ast_suite_to_text(catch_stmt->catch_suite, indent_level+1, strbuf);
}

void hex_ast_try_stmt_to_text(TryStmt try_stmt, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(try_stmt);
  HEX_ASSERT(try_stmt->try_suite);
  HEX_ASSERT(try_stmt->catch_stmt_group);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "try:");
  hex_ast_suite_to_text(try_stmt->try_suite, indent_level+1, strbuf);

  CatchStmtGroup catch_stmt_group = try_stmt->catch_stmt_group;
  while(catch_stmt_group) {
    CatchStmt catch_stmt = catch_stmt_group->catch_stmt;
    HEX_ASSERT(catch_stmt);

    hex_ast_catch_stmt_to_text(catch_stmt, indent_level, strbuf);

    catch_stmt_group = catch_stmt_group->next;
  }

  if(try_stmt->finally_stmt) {
    strbuf_append(strbuf, "finally:");
    hex_ast_suite_to_text(try_stmt->finally_stmt->finally_suite, indent_level+1, strbuf);
  }
}

void hex_ast_func_def_to_text(FuncDef func_def, Strbuf strbuf)
{
  HEX_ASSERT(func_def);
  HEX_ASSERT(func_def->func_declaration);
  HEX_ASSERT(func_def->func_suite);

  hex_ast_func_declaration_to_text(func_def->func_declaration, strbuf);
  strbuf_append(strbuf, ":");
  hex_ast_suite_to_text(func_def->func_suite, 1, strbuf);
}

void hex_ast_compound_stmt_to_text(CompoundStmt compound_stmt, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(compound_stmt);
  HEX_ASSERT(strbuf);

  switch(compound_stmt->compound_stmt_type)
  {
    case compound_stmt_type_if_stmt:
      hex_ast_if_stmt_to_text(compound_stmt->compound_stmt_if_stmt, indent_level, strbuf);
      break;
    case compound_stmt_type_while_stmt:
      hex_ast_while_stmt_to_text(compound_stmt->compound_stmt_while_stmt, indent_level, strbuf);
      break;
    case compound_stmt_type_for_stmt:
      hex_ast_for_stmt_to_text(compound_stmt->compound_stmt_for_stmt, indent_level, strbuf);
      break;
    case compound_stmt_type_try_stmt:
      hex_ast_try_stmt_to_text(compound_stmt->compound_stmt_try_stmt, indent_level, strbuf);
      break;
    case compound_stmt_type_func_def:
      hex_ast_func_def_to_text(compound_stmt->compound_stmt_func_def, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexCompoundStmt type");
      break;
  }
}

void hex_ast_return_stmt_to_text(ReturnStmt return_stmt, Strbuf strbuf)
{
  HEX_ASSERT(return_stmt);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "return");

  switch(return_stmt->return_stmt_type)
  {
    case return_stmt_type_none:
      break;
    case return_stmt_type_expr_list:
      strbuf_append(strbuf, " ");
      hex_ast_exprlist_to_text(return_stmt->return_expr_list, strbuf);
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexReturnStmt type");
      break;
  }
}

void hex_ast_control_simple_stmt_to_text(ControlSimpleStmt stmt, Strbuf strbuf)
{
  HEX_ASSERT(stmt);
  HEX_ASSERT(strbuf);

  switch(stmt->control_simple_stmt_type)
  {
    case control_simple_stmt_return:
      hex_ast_return_stmt_to_text(stmt->control_simple_stmt_return_stmt, strbuf);
      break;
    case control_simple_stmt_continue:
      strbuf_append(strbuf, "continue");
      break;
    case control_simple_stmt_break:
      strbuf_append(strbuf, "break");
      break;
    default:
      AST_TO_TEXT_ERROR("Unknown HexControlSimpleStmt type");
      break;
  }
}

void hex_ast_stmt_to_text(Stmt stmt, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(stmt);
  HEX_ASSERT(strbuf);

  switch(stmt->stmt_type)
  {
    case stmt_type_simple_stmt_list:
      hex_ast_simple_stmt_list_to_text(stmt->stmt_simple_stmt_list, strbuf);
      break;
    case stmt_type_compound_stmt:
      hex_ast_compound_stmt_to_text(stmt->stmt_compound_stmt, indent_level, strbuf);
      break;
    case stmt_type_control_simple_stmt:
      hex_ast_control_simple_stmt_to_text(stmt->stmt_control_simple_stmt, strbuf);
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

void hex_ast_stmt_group_to_text(StmtGroup group, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(group);
  HEX_ASSERT(strbuf);

  while(group) {
    Stmt stmt = group->stmt;

    HEX_ASSERT(stmt);
    unsigned char _indent_level = indent_level;
    while(_indent_level > 0) {
      strbuf_append(strbuf, "  ");
      _indent_level--;
    }
    hex_ast_stmt_to_text(stmt, indent_level, strbuf);

    if(group->next) {
      strbuf_append(strbuf, "\n");
    }

    group = group->next;
  }
}

void hex_ast_suite_to_text(Suite suite, unsigned char indent_level, Strbuf strbuf)
{
  HEX_ASSERT(suite);
  HEX_ASSERT(strbuf);

  strbuf_append(strbuf, "\n");
  hex_ast_stmt_group_to_text(suite->stmt_group, indent_level, strbuf);
  strbuf_append(strbuf, "\n");
}
