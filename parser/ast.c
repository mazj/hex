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

/* Abstract Syntax Tree */

#include "ast.h"
#include "../base/assert.h"
#include "../base/memory.h"


Integer
hex_ast_create_integer(int type, int is_signed, int value)
{
  Integer integer = HEX_MALLOC(struct HexInteger);

  integer->integer_type = type;
  integer->is_signed = is_signed;

  if(is_signed) {
    integer->signed_integer = value;
  } else {
    integer->unsigned_integer = (unsigned int)value;
  }

  return integer;
}

Literal
hex_ast_create_literal(int type, void *value)
{
  HEX_ASSERT(value != NULL);

  Literal literal = HEX_MALLOC(struct HexLiteral);

  switch(type)
  {
    case literal_type_char:
      {
        literal->literal_type = literal_type_char;
        literal->literal_char = DEREF_VOID(char, value);
      }
      break;
    case literal_type_string:
      {
        literal->literal_type = literal_type_string;
        literal->literal_string = (char*)value;
      }
      break;
    case literal_type_integer:
      {
        literal->literal_type = literal_type_integer;
        literal->literal_integer = (Integer)value;
      }
      break;
    case literal_type_float:
      {
        literal->literal_type = literal_type_float;
        literal->literal_float = DEREF_VOID(double, value);
      }
      break;
    default:
      AST_ERROR(0, "Unknown literal type");
      break;
  }

  return literal;
}

Expr
hex_ast_create_primary_expr(int type, void *value)
{
  HEX_ASSERT(value != NULL);

  PrimaryExpr primary_expr = HEX_MALLOC(struct HexPrimaryExpr);

  switch(type)
  {
    case primary_expr_type_identifier:
      {
        primary_expr->primary_expr_type = primary_expr_type_identifier;
        primary_expr->primary_expr_identifier = (char*)value;
      }
      break;
    case primary_expr_type_literal:
      {
        primary_expr->primary_expr_type = primary_expr_type_literal;
        primary_expr->primary_expr_literal = (Literal)value;
      }
      break;
    default:
      AST_ERROR(0, "Unknown primary expression type");
      break;
  }

  Expr expr = hex_ast_create_expr(expr_type_primary, primary_expr);

  return expr;
}

PostfixIndexExpr
hex_ast_create_postfix_index_expr(int type, void *value, ListInitializer indeces)
{
  HEX_ASSERT(value != NULL);
  HEX_ASSERT(indeces != NULL);

  PostfixIndexExpr postfix_index_expr = HEX_MALLOC(struct HexPostfixIndexExpr);

  switch(type)
  {
    case postfix_index_expr_type_identifier:
      {
        postfix_index_expr->postfix_index_expr_type = postfix_index_expr_type_identifier;
        postfix_index_expr->identifier = (char*)value;
        postfix_index_expr->indeces = indeces;
      }
      break;
    case postfix_index_expr_type_expr:
      {
        postfix_index_expr->postfix_index_expr_type = postfix_index_expr_type_expr;
        postfix_index_expr->index_expr = (Expr)value;
        postfix_index_expr->indeces = indeces;
      }
      break;
    default:
      AST_ERROR(0, "Unknown postfix index expression type");
      break;
  }

  return postfix_index_expr;
}

PostfixAccessorExpr
hex_ast_create_postfix_accessor_expr(Expr caller, Expr accessor)
{
  HEX_ASSERT(caller != NULL);
  HEX_ASSERT(accessor != NULL);

  PostfixAccessorExpr postfix_accessor_expr = HEX_MALLOC(struct HexPostfixAccessorExpr);

  postfix_accessor_expr->caller = caller;
  postfix_accessor_expr->accessor = accessor;

  return postfix_accessor_expr;
}

PostfixInvocationWithArgsExpr
hex_ast_create_postfix_invocation_with_args_expr(int type, void *value, ExprList arg_list)
{
  HEX_ASSERT(value != NULL);
  HEX_ASSERT(arg_list != NULL);

  PostfixInvocationWithArgsExpr postfix_invocation_with_args_expr = HEX_MALLOC(struct HexPostfixInvocationWithArgsExpr);

  switch(type)
  {
    case postfix_invocation_expr_with_args_type_identifier:
      {
        postfix_invocation_with_args_expr->postfix_invocation_expr_with_args_type = postfix_invocation_expr_with_args_type_identifier;
        postfix_invocation_with_args_expr->invocation_name = (char*)value;
      }
      break;
    case postfix_invocation_expr_with_args_type_expr:
      {
        postfix_invocation_with_args_expr->postfix_invocation_expr_with_args_type = postfix_invocation_expr_with_args_type_expr;
        postfix_invocation_with_args_expr->invocation_expr = (Expr)value;
      }
      break;
    default:
      AST_ERROR(0, "Unknown postfix invocation with args expression type");
      break;
  }

  postfix_invocation_with_args_expr->arg_list = arg_list;

  return postfix_invocation_with_args_expr;
}

PostfixInvocationExpr
hex_ast_create_postfix_invocation_expr(int type, void *invocation_src)
{
  HEX_ASSERT(invocation_src != NULL);

  PostfixInvocationExpr postfix_invocation_expr = HEX_MALLOC(struct HexPostfixInvocationExpr);

  switch(type)
  {
    case postfix_invocation_expr_type_identifier:
      {
        postfix_invocation_expr->postfix_invocation_expr_type = postfix_invocation_expr_type_identifier;
        postfix_invocation_expr->invocation_name = (char*)invocation_src;
      }
      break;
    case postfix_invocation_expr_type_expr:
      {
        postfix_invocation_expr->postfix_invocation_expr_type = postfix_invocation_expr_type_expr;
        postfix_invocation_expr->invocation_expr = (Expr)invocation_src;
      }
      break;
    default:
      AST_ERROR(0, "Unknown invocation expression type");
      break;
  }

  return postfix_invocation_expr;
}

Expr
hex_ast_create_postfix_expr(int type, int type2, void *value, void *value1)
{
  HEX_ASSERT(value != NULL);

  PostfixExpr postfix_expr = HEX_MALLOC(struct HexPostfixExpr);

  switch(type)
  {
    case postfix_expr_type_index:
      {
        postfix_expr->postfix_expr_type = postfix_expr_type_index;
        PostfixIndexExpr postfix_index_expr = hex_ast_create_postfix_index_expr(type2, value, (ListInitializer)value1);
        postfix_expr->postfix_expr_index_expr = postfix_index_expr;
      }
      break;
    case postfix_expr_type_postfix_inc:
      {
        postfix_expr->postfix_expr_type = postfix_expr_type_postfix_inc;
        postfix_expr->postfix_expr_postfix_inc_expr = (Expr)value;
      }
      break;
    case postfix_expr_type_postfix_dec:
      {
        postfix_expr->postfix_expr_type = postfix_expr_type_postfix_dec;
        postfix_expr->postfix_expr_postfix_dec_expr = (Expr)value;
      }
      break;
    case postfix_expr_type_accessor:
      {
        postfix_expr->postfix_expr_type = postfix_expr_type_accessor;
        PostfixAccessorExpr postfix_accessor_expr = hex_ast_create_postfix_accessor_expr((Expr)value, (Expr)value1);
        postfix_expr->postfix_expr_accessor_expr = postfix_accessor_expr;
      }
      break;
    case postfix_expr_type_invocation:
      {
        postfix_expr->postfix_expr_type = postfix_expr_type_invocation;
        PostfixInvocationExpr postfix_invocation_expr = hex_ast_create_postfix_invocation_expr(type2, value);
        postfix_expr->postfix_expr_invocation_expr = postfix_invocation_expr;
      }
      break;
    case postfix_expr_type_invocation_with_args:
      {
        postfix_expr->postfix_expr_type = postfix_expr_type_invocation_with_args;
        PostfixInvocationWithArgsExpr postfix_invocation_with_args_expr = hex_ast_create_postfix_invocation_with_args_expr(type2, value, (ExprList)value1);
        postfix_expr->postfix_expr_invocation_with_args_expr = postfix_invocation_with_args_expr;
      }
      break;
    default:
      AST_ERROR(0, "Unknown postfix type");
      break;
  }

  Expr expr = hex_ast_create_expr(expr_type_postfix, postfix_expr);

  return expr;
}

Expr
hex_ast_create_unary_expr(int type, Expr expr)
{
  HEX_ASSERT(expr != NULL);

  UnaryExpr unary_expr = HEX_MALLOC(struct HexUnaryExpr);

  switch(type)
  {
    case unary_expr_type_prefix_inc:
      {
        unary_expr->unary_expr_type = unary_expr_type_prefix_inc;
        unary_expr->unary_expr_prefix_inc_expr = expr;
      }
      break;
    case unary_expr_type_prefix_dec:
      {
        unary_expr->unary_expr_type = unary_expr_type_prefix_dec;
        unary_expr->unary_expr_prefix_dec_expr = expr;
      }
      break;
    case unary_expr_type_unary_minus:
      {
        unary_expr->unary_expr_type = unary_expr_type_unary_minus;
        unary_expr->unary_expr_unary_expr = expr;
      }
      break;
    case unary_expr_type_bitwise_not:
      {
        unary_expr->unary_expr_type = unary_expr_type_bitwise_not;
        unary_expr->unary_expr_bitwise_not = expr;
      }
      break;
    default:
      AST_ERROR(0, "Unknown unary expression type");
      break;
  }

  Expr _expr = hex_ast_create_expr(expr_type_unary, unary_expr);

  return _expr;
}

Expr
hex_ast_create_cast_expr(int type, void *value, Expr expr)
{
  HEX_ASSERT(value != NULL);
  HEX_ASSERT(expr != NULL);

  CastExpr cast_expr = HEX_MALLOC(struct HexCastExpr);

  switch(type)
  {
    case cast_expr_type_type_specifier:
      {
        cast_expr->cast_expr_type = cast_expr_type_type_specifier;
        cast_expr->type_specifier = DEREF_VOID(int, value);
        cast_expr->expr = expr;
      }
      break;
    case cast_expr_type_custom_type:
      {
        cast_expr->cast_expr_type = cast_expr_type_custom_type;
        cast_expr->identifier = (char*)value;
        cast_expr->expr = expr;
      }
      break;
    default:
      AST_ERROR(0, "Unknown cast expression type");
      break;
  }

  Expr _expr = hex_ast_create_expr(expr_type_cast, cast_expr);

  return _expr;
}

Expr
hex_ast_create_multiplicative_expr(int type, Expr left_expr, Expr right_expr)
{
  HEX_ASSERT(left_expr != NULL);
  HEX_ASSERT(right_expr != NULL);

  MultiplicativeExpr multi_expr = HEX_MALLOC(struct HexMultiplicativeExpr);

  switch(type)
  {
    case multiplicative_expr_type_mul:
      {
        multi_expr->multi_expr_type = multiplicative_expr_type_mul;
      }
      break;
    case multiplicative_expr_type_div:
      {
        multi_expr->multi_expr_type = multiplicative_expr_type_div;
      }
      break;
    case multiplicative_expr_type_mod:
      {
        multi_expr->multi_expr_type = multiplicative_expr_type_mod;
      }
      break;
    default:
      AST_ERROR(0, "Internal AST error");
      break;
  }

  multi_expr->left_expr = left_expr;
  multi_expr->right_expr = right_expr;

  ArithmeticExpr arithmetic_expr = hex_ast_create_arithmetic_expr(arithmetic_expr_type_multiplicative, multi_expr);

  Expr expr = hex_ast_create_expr(expr_type_arithmetic, arithmetic_expr);

  return expr;
}

Expr
hex_ast_create_additive_expr(int type, Expr left_expr, Expr right_expr)
{
  HEX_ASSERT(left_expr != NULL);
  HEX_ASSERT(right_expr != NULL);

  AdditiveExpr additive_expr = HEX_MALLOC(struct HexAdditiveExpr);

  switch(type)
  {
    case additive_expr_type_plus:
      {
        additive_expr->additive_expr_type = additive_expr_type_plus;
      }
      break;
    case additive_expr_type_minus:
      {
        additive_expr->additive_expr_type = additive_expr_type_minus;
      }
      break;
    default:
      AST_ERROR(0, "Internal AST error");
      break;
  }

  additive_expr->left_expr = left_expr;
  additive_expr->right_expr = right_expr;

  ArithmeticExpr arithmetic_expr = hex_ast_create_arithmetic_expr(arithmetic_expr_type_additive, additive_expr);

  Expr expr = hex_ast_create_expr(expr_type_arithmetic, arithmetic_expr);

  return expr;
}

ArithmeticExpr
hex_ast_create_arithmetic_expr(int type, void *expr)
{
  HEX_ASSERT(expr != NULL);

  ArithmeticExpr arithmetic_expr = HEX_MALLOC(struct HexArithmeticExpr);

  switch(type)
  {
    case arithmetic_expr_type_multiplicative:
      {
        arithmetic_expr->arithmetic_expr_type  = arithmetic_expr_type_multiplicative;
        arithmetic_expr->arithmetic_expr_multiplicative_expr = (MultiplicativeExpr)expr;
      }
      break;
    case arithmetic_expr_type_additive:
      {
        arithmetic_expr->arithmetic_expr_type = arithmetic_expr_type_additive;
        arithmetic_expr->arithmetic_expr_additive_expr = (AdditiveExpr)expr;
      }
      break;
    default:
      AST_ERROR(0, "Unknown arithmetic expression type");
      break;
  }

  return arithmetic_expr;
}

Expr
hex_ast_create_equality_expr(int type, Expr left_expr, Expr right_expr)
{
  HEX_ASSERT(left_expr != NULL);
  HEX_ASSERT(right_expr != NULL);

  EqualityExpr equality_expr = HEX_MALLOC(struct HexEqualityExpr);

  switch(type)
  {
    case equality_expr_type_eq:
      {
        equality_expr->equality_expr_type = equality_expr_type_eq;
      }
      break;
    case equality_expr_type_neq:
      {
        equality_expr->equality_expr_type = equality_expr_type_neq;
      }
      break;
    case equality_expr_type_less:
      {
        equality_expr->equality_expr_type = equality_expr_type_less;
      }
      break;
    case equality_expr_type_greater:
      {
        equality_expr->equality_expr_type = equality_expr_type_greater;
      }
      break;
    case equality_expr_type_le:
      {
        equality_expr->equality_expr_type = equality_expr_type_le;
      }
      break;
    case equality_expr_type_ge:
      {
        equality_expr->equality_expr_type = equality_expr_type_ge;
      }
      break;
    case equality_expr_type_is:
      {
        equality_expr->equality_expr_type = equality_expr_type_is;
      }
      break;
    case equality_expr_type_is_not:
      {
        equality_expr->equality_expr_type = equality_expr_type_is_not;
      }
      break;
    default:
      AST_ERROR(0, "Unknown equality type");
      break;
  }

  equality_expr->left_expr = left_expr;
  equality_expr->right_expr = right_expr;

  Expr expr = hex_ast_create_expr(expr_type_equality, equality_expr);

  return expr;
}

Expr
hex_ast_create_logic_expr(int type, Expr left_expr, Expr right_expr)
{
  HEX_ASSERT(left_expr != NULL);
  HEX_ASSERT(right_expr != NULL);

  LogicExpr logic_expr = HEX_MALLOC(struct HexLogicExpr);

  switch(type)
  {
    case logic_expr_type_logic_and:
      {
        logic_expr->logic_expr_type = logic_expr_type_logic_and;
      }
      break;
    case logic_expr_type_logic_or:
      {
        logic_expr->logic_expr_type = logic_expr_type_logic_or;
      }
      break;
    default:
      AST_ERROR(0, "Unknown logic expression type");
      break;
  }

  logic_expr->left_expr = left_expr;
  logic_expr->right_expr = right_expr;

  Expr expr = hex_ast_create_expr(expr_type_logic, logic_expr);

  return expr;
}

Expr
hex_ast_create_bitwise_expr(int type, Expr left_expr, Expr right_expr)
{
  HEX_ASSERT(left_expr != NULL);
  HEX_ASSERT(right_expr != NULL);

  BitwiseExpr bitwise_expr = HEX_MALLOC(struct HexBitwiseExpr);

  switch(type)
  {
    case bitwise_expr_type_shift_left:
      {
        bitwise_expr->bitwise_expr_type = bitwise_expr_type_shift_left;
      }
      break;
    case bitwise_expr_type_shift_right:
      {
        bitwise_expr->bitwise_expr_type = bitwise_expr_type_shift_right;
      }
      break;
    case bitwise_expr_type_bitwise_and:
      {
        bitwise_expr->bitwise_expr_type = bitwise_expr_type_bitwise_and;
      }
      break;
    case bitwise_expr_type_bitwise_or:
      {
        bitwise_expr->bitwise_expr_type = bitwise_expr_type_bitwise_or;
      }
      break;
    case bitwise_expr_type_bitwise_xor:
      {
        bitwise_expr->bitwise_expr_type = bitwise_expr_type_bitwise_xor;
      }
      break;
    default:
      AST_ERROR(0, "Unknown bitwise expression type");
      break;
  }

  bitwise_expr->left_expr = left_expr;
  bitwise_expr->right_expr = right_expr;

  Expr expr = hex_ast_create_expr(expr_type_bitwise, bitwise_expr);

  return expr;
}

Expr
hex_ast_create_conditional_expr(Expr predicate_expr, Expr consequent_expr, Expr alternative_expr)
{
  HEX_ASSERT(predicate_expr != NULL);
  HEX_ASSERT(consequent_expr != NULL);
  HEX_ASSERT(alternative_expr != NULL);

  ConditionalExpr conditional_expr = HEX_MALLOC(struct HexConditionalExpr);

  conditional_expr->consequent_expr = consequent_expr;
  conditional_expr->predicate_expr = predicate_expr;
  conditional_expr->alternative_expr = alternative_expr;

  Expr expr = hex_ast_create_expr(expr_type_conditional, conditional_expr);

  return expr;
}

Expr
hex_ast_create_range_expr(Expr left_expr, Expr right_expr)
{
  HEX_ASSERT(left_expr != NULL);
  HEX_ASSERT(right_expr != NULL);

  RangeExpr range_expr = HEX_MALLOC(struct HexRangeExpr);

  range_expr->left_expr = left_expr;
  range_expr->right_expr = right_expr;

  Expr expr = hex_ast_create_expr(expr_type_range, range_expr);

  return expr;
}

Expr
hex_ast_create_lock_expr(int is_lock, Expr expr)
{
  HEX_ASSERT(expr != NULL);

  LockExpr lock_expr = HEX_MALLOC(struct HexLockExpr);

  lock_expr->is_lock = is_lock;
  lock_expr->expr = expr;

  Expr _expr = hex_ast_create_expr(expr_type_lock, lock_expr);

  return _expr;
}

Expr
hex_ast_create_weakref_expr(Expr expr)
{
  HEX_ASSERT(expr != NULL);

  WeakrefExpr weakref_expr = HEX_MALLOC(struct HexWeakrefExpr);

  weakref_expr->expr = expr;

  Expr _expr = hex_ast_create_expr(expr_type_weakref, weakref_expr);

  return _expr;
}

Expr
hex_ast_create_expr(int type, void *value)
{
  Expr expr = HEX_MALLOC(struct HexExpr);

  switch(type)
  {
    case expr_type_primary:
      {
        expr->expr_type = expr_type_primary;
        expr->primary_expr = (PrimaryExpr)value;
      }
      break;
    case expr_type_postfix:
      {
        expr->expr_type = expr_type_postfix;
        expr->postfix_expr = (PostfixExpr)value;
      }
      break;
    case expr_type_unary:
      {
        expr->expr_type = expr_type_unary;
        expr->unary_expr = (UnaryExpr)value;
      }
      break;
    case expr_type_cast:
      {
        expr->expr_type = expr_type_cast;
        expr->cast_expr = (CastExpr)value;
      }
      break;
    case expr_type_arithmetic:
      {
        expr->expr_type = expr_type_arithmetic;
        expr->arithmetic_expr = (ArithmeticExpr)value;
      }
      break;
    case expr_type_equality:
      {
        expr->expr_type = expr_type_equality;
        expr->equality_expr = (EqualityExpr)value;
      }
      break;
    case expr_type_logic:
      {
        expr->expr_type = expr_type_logic;
        expr->logic_expr = (LogicExpr)value;
      }
      break;
    case expr_type_bitwise:
      {
        expr->expr_type = expr_type_bitwise;
        expr->bitwise_expr = (BitwiseExpr)value;
      }
      break;
    case expr_type_conditional:
      {
        expr->expr_type = expr_type_conditional;
        expr->conditional_expr = (ConditionalExpr)value;
      }
      break;
    case expr_type_range:
      {
        expr->expr_type = expr_type_range;
        expr->range_expr = (RangeExpr)value;
      }
      break;
    case expr_type_lock:
      {
        expr->expr_type = expr_type_lock;
        expr->lock_expr = (LockExpr)value;
      }
      break;
    case expr_type_weakref:
      {
        expr->expr_type = expr_type_weakref;
        expr->weakref_expr = (WeakrefExpr)value;
      }
      break;
    default:
      AST_ERROR(0, "Unknown expression type");
      break;
  }

  return expr;
}

ExprList
hex_ast_create_expr_list(Expr expr, ExprList parent_list)
{
  HEX_ASSERT(expr != NULL);

  ExprList expr_list = HEX_MALLOC(struct HexExprList);
  expr_list->expr = expr;

  if(parent_list) {
    parent_list->next = expr_list;
    return parent_list;
  } else {
    return expr_list;
  }
}

TypeQualifierList
hex_ast_create_type_qualifier_list(TypeQualifier qualifier, TypeQualifierList parent_list)
{
  TypeQualifierList qualifier_list = HEX_MALLOC(struct HexTypeQualifierList);
  qualifier_list->type_qualifier = qualifier;
  qualifier_list->next = 0;

  if(parent_list) {
    parent_list->next = qualifier_list;
    return parent_list;
  } else {
    return qualifier_list;
  }
}

Declaration
hex_ast_create_declaration(TypeQualifierList type_qualifier_list,
  int type_specifier, char *custom_type, ExprList expr_list, char *alias)
{
  Declaration declaration = HEX_MALLOC(struct HexDeclaration);

  declaration->type_qualifier_list = type_qualifier_list;
  declaration->type_specifier = type_specifier;
  declaration->custom_type = custom_type;
  declaration->expr_list = expr_list;
  declaration->alias = alias;

  return declaration;
}

Parameter
hex_ast_create_parameter(TypeQualifierList type_qualifier_list, int type_specifier,
  char *custom_type, char *parameter_name, char *alias, int is_ref)
{
  Parameter parameter = HEX_MALLOC(struct HexParameter);

  parameter->type_qualifier_list = type_qualifier_list;
  parameter->type_specifier = type_specifier;
  parameter->custom_type = custom_type;
  parameter->parameter_name = parameter_name;
  parameter->is_ref = is_ref;

  return parameter;
}

ParameterList
hex_ast_create_parameter_list(Parameter parameter, ParameterList parent_list)
{
  HEX_ASSERT(parameter != NULL);

  ParameterList param_list = HEX_MALLOC(struct HexParameterList);
  param_list->parameter = parameter;
  param_list->next = 0;

  if(parent_list) {
    parent_list->next = param_list;
    return parent_list;
  } else {
    return param_list;
  }
}

ListInitializer
hex_ast_create_list_initializer(ExprList expr_list)
{
  HEX_ASSERT(expr_list != NULL);

  ListInitializer list_initializer = HEX_MALLOC(struct HexListInitializer);
  list_initializer->expr_list = expr_list;

  return list_initializer;
}

ArrayInitializer
hex_ast_create_array_initializer(ExprList expr_list)
{
  HEX_ASSERT(expr_list != NULL);

  ArrayInitializer array_initializer = HEX_MALLOC(struct HexArrayInitializer);
  array_initializer->expr_list = expr_list;

  return array_initializer;
}

TupleInitializer
hex_ast_create_tuple_initializer(ExprList expr_list)
{
  HEX_ASSERT(expr_list != NULL);

  TupleInitializer tuple_initializer = HEX_MALLOC(struct HexTupleInitializer);
  tuple_initializer->expr_list = expr_list;

  return tuple_initializer;
}

StructInitializer
hex_ast_create_struct_initializer(AssignmentStmtList assignment_stmt_list)
{
  HEX_ASSERT(assignment_stmt_list != NULL);

  StructInitializer struct_initializer = HEX_MALLOC(struct HexStructInitializer);
  struct_initializer->assignment_stmt_list = assignment_stmt_list;

  return struct_initializer;
}

SetInitializer
hex_ast_create_set_initializer(ExprList expr_list)
{
  HEX_ASSERT(expr_list != NULL);

  SetInitializer set_initializer = HEX_MALLOC(struct HexSetInitializer);
  set_initializer->expr_list = expr_list;

  return set_initializer;
}

MapMultimapInitializerSingle
hex_ast_create_map_multimap_initializer_single(Expr key, Expr value)
{
  HEX_ASSERT(key != NULL);
  HEX_ASSERT(value != NULL);

  MapMultimapInitializerSingle map_initializer_single = HEX_MALLOC(struct HexMapMultimapInitializerSingle);
  map_initializer_single->key = key;
  map_initializer_single->value = value;

  return map_initializer_single;
}

MapMultimapInitializerList
hex_ast_create_map_multimap_initializer_list(MapMultimapInitializerSingle map_initializer_single, MapMultimapInitializerList parent_list)
{
  HEX_ASSERT(map_initializer_single != NULL);

  MapMultimapInitializerList map_initializer_list = HEX_MALLOC(struct HexMapMultimapInitializerList);
  map_initializer_list->map_initializer_single = map_initializer_single;
  map_initializer_list->next = 0;

  if(parent_list) {
    parent_list->next = map_initializer_list;
    return parent_list;
  } else {
    return map_initializer_list;
  }
}

MapMultimapInitializer
hex_ast_create_map_multimap_initializer(MapMultimapInitializerList map_initializer_list)
{
  HEX_ASSERT(map_initializer_list != NULL);

  MapMultimapInitializer map_initializer = HEX_MALLOC(struct HexMapMultimapInitializer);
  map_initializer->map_initializer_list = map_initializer_list;

  return map_initializer;
}

Initializer
hex_ast_create_initializer(int type, void *value)
{
  HEX_ASSERT(value != NULL);

  Initializer initializer = HEX_MALLOC(struct HexInitializer);

  switch(type)
  {
    case initializer_type_list:
      {
        initializer->initializer_type = initializer_type_list;
        initializer->list_initializer = (ListInitializer)value;
      }
      break;
    case initializer_type_array:
      {
        initializer->initializer_type = initializer_type_array;
        initializer->array_initializer = (ArrayInitializer)value;
      }
      break;
    case initializer_type_tuple:
      {
        initializer->initializer_type = initializer_type_tuple;
        initializer->tuple_initializer = (TupleInitializer)value;
      }
      break;
    case initializer_type_struct:
      {
        initializer->initializer_type = initializer_type_struct;
        initializer->struct_initializer = (StructInitializer)value;
      }
      break;
    case initializer_type_set:
      {
        initializer->initializer_type = initializer_type_set;
        initializer->set_initialier = (SetInitializer)value;
      }
      break;
    case initializer_type_mapmultimap:
      {
        initializer->initializer_type = initializer_type_mapmultimap;
        initializer->map_multimap_initializer = (MapMultimapInitializer)value;
      }
      break;
    default:
      AST_ERROR(0, "Unknown initializer type");
      break;
  }

  return initializer;
}

Assignment
hex_ast_create_assignment(int type, void *target)
{
  HEX_ASSERT(target != NULL);

  Assignment assignment = HEX_MALLOC(struct HexAssignment);

  switch(type)
  {
    case assignment_type_expr:
      {
        assignment->assignment_type = assignment_type_expr;
        assignment->assignment_expr = (Expr)target;
      }
      break;
    case assignment_type_initializer:
      {
        assignment->assignment_type = assignment_type_initializer;
        assignment->assignment_initializer = (Initializer)target;
      }
      break;
    case assignment_type_lambda:
      {
        assignment->assignment_type = assignment_type_lambda;
        assignment->assignment_lambda = (LambdaExpr)target;
      }
      break;
    default:
      AST_ERROR(0, "Unknown assignment type");
      break;
  }

  return assignment;
}

AssignmentList
hex_ast_create_assignment_list(Assignment assignment, AssignmentList parent_list)
{
  HEX_ASSERT(assignment != NULL);

  AssignmentList assignment_list = HEX_MALLOC(struct HexAssignmentList);
  assignment_list->assignment = assignment;
  assignment_list->next = 0;

  if(parent_list) {
    parent_list->next = assignment_list;
    return parent_list;
  } else {
    return assignment_list;
  }
}

AssignmentStmt
hex_ast_create_assignment_stmt(int type, void *value, AssignmentList assignment_list)
{
  HEX_ASSERT(value != NULL);
  HEX_ASSERT(assignment_list != NULL);

  AssignmentStmt assignment_stmt = HEX_MALLOC(struct HexAssignmentStmt);

  switch(type)
  {
    case assignment_stmt_type_declaration:
      {
        assignment_stmt->assignment_stmt_type = assignment_stmt_type_declaration;
        assignment_stmt->assignment_stmt_declaration = (Declaration)value;
        assignment_stmt->assignment_list = assignment_list;
      }
      break;
    case assignment_stmt_type_expr_list:
      {
        assignment_stmt->assignment_stmt_type = assignment_stmt_type_expr_list;
        assignment_stmt->assignment_stmt_expr_list = (ExprList)value;
        assignment_stmt->assignment_list = assignment_list;
      }
      break;
    default:
      AST_ERROR(0, "Unknown assignment statement type");
      break;
  }

  return assignment_stmt;
}

AssignmentStmtList
hex_ast_create_assignment_stmt_list(AssignmentStmt assignment_stmt, AssignmentStmtList parent_list)
{
  HEX_ASSERT(assignment_stmt != NULL);

  AssignmentStmtList assignment_stmt_list = HEX_MALLOC(struct HexAssignmentStmtList);
  assignment_stmt_list->assignment_stmt = assignment_stmt;
  assignment_stmt_list->next = 0;

  if(parent_list) {
    parent_list->next = assignment_stmt_list;
    return parent_list;
  } else {
    return assignment_stmt_list;
  }
}

FuncDec
hex_ast_create_func_dec(TypeQualifierList type_qualifier_list,
  int type_specifier, char *custom_return_type, char *func_name, ParameterList parameter_list)
{

  FuncDec func_declaration = HEX_MALLOC(struct HexFuncDec);
  func_declaration->return_type_qualifier_list = type_qualifier_list;
  func_declaration->return_type_specifier = type_specifier;
  func_declaration->custom_return_type = custom_return_type;
  func_declaration->func_name = func_name;
  func_declaration->parameter_list = parameter_list;

  return func_declaration;
}

FuncDef
hex_ast_create_func_def(FuncDec func_declaration, Suite func_suite)
{
  HEX_ASSERT(func_declaration != NULL);
  HEX_ASSERT(func_suite != NULL);

  FuncDef func_def = HEX_MALLOC(struct HexFuncDef);

  func_def->func_declaration = func_declaration;
  func_def->func_suite = func_suite;

  return func_def;
}

LambdaExpr
hex_ast_create_lambda_expr(int type, ParameterList param_list, void *body)
{
  HEX_ASSERT(param_list != NULL);
  HEX_ASSERT(body != NULL);

  LambdaExpr lambda_expr = HEX_MALLOC(struct HexLambdaExpr);

  switch(lambda_expr->lambda_type)
  {
    case lambda_type_simple:
      {
        lambda_expr->lambda_type = lambda_type_simple;
        lambda_expr->lambda_simple_stmt_list = (SimpleStmtList)body;
      }
      break;
    case lambda_type_suite:
      {
        lambda_expr->lambda_type = lambda_type_suite;
        lambda_expr->lambda_suite = (Suite)body;
      }
      break;
    default:
      AST_ERROR(0, "Unknown lambda expression type");
      break;
  }

  return lambda_expr;
}

Attribute
hex_ast_create_attribute(Expr expr)
{
  HEX_ASSERT(expr != NULL);

  Attribute attribute = HEX_MALLOC(struct HexAttribute);

  attribute->expr = expr;

  return attribute;
}

CompilerProperty
hex_ast_create_compiler_property(char *compiler_property_name, char *compiler_property_value)
{
  HEX_ASSERT(compiler_property_name != NULL);
  HEX_ASSERT(compiler_property_value != NULL);

  CompilerProperty compiler_property = HEX_MALLOC(struct HexCompilerProperty);

  compiler_property->compiler_property_name = compiler_property_name;
  compiler_property->compiler_property_value = compiler_property_value;

  return compiler_property;
}

DecoratorListSingle
hex_ast_create_decorator_list_single(int type, void *value)
{
  HEX_ASSERT(value != NULL);

  DecoratorListSingle decorator_list_single = HEX_MALLOC(struct HexDecoratorListSingle);

  switch(type)
  {
    case decorator_list_single_type_attribute:
      {
        decorator_list_single->decorator_list_single_type = decorator_list_single_type_attribute;
        decorator_list_single->decorator_list_single_attribute = (Attribute)value;
      }
      break;
    case decorator_list_single_type_compiler_property:
      {
        decorator_list_single->decorator_list_single_type = decorator_list_single_type_compiler_property;
        decorator_list_single->decorator_list_single_compiler_property = (CompilerProperty)value;
      }
      break;
    default:
      AST_ERROR(0, "Internal AST error");
      break;
  }

  return decorator_list_single;
}

DecoratorList
hex_ast_create_decorator_list(DecoratorListSingle decorator_list_single, DecoratorList parent_list)
{
  HEX_ASSERT(decorator_list_single != NULL);

  DecoratorList decorator_list = HEX_MALLOC(struct HexDecoratorList);
  decorator_list->decorator_list_single = decorator_list_single;
  decorator_list->next = 0;

  if(parent_list) {
    parent_list->next = decorator_list;
    return parent_list;
  } else {
    return decorator_list;
  }
}

Decorator
hex_ast_create_decorator(DecoratorList decorator_list)
{
  HEX_ASSERT(decorator_list != NULL);

  Decorator decorator = HEX_MALLOC(struct HexDecorator);
  decorator->decorator_list = decorator_list;

  return decorator;
}

ClassDeclaration
hex_ast_create_class_declaration(char *name, ExprList expr_list)
{
  HEX_ASSERT(name != NULL);

  ClassDeclaration class_declaration = HEX_MALLOC(struct HexClassDeclaration);
  class_declaration->name = name;
  class_declaration->expr_list = expr_list;

  return class_declaration;
}

ClassSection
hex_ast_create_class_section(int class_access_specifier, Suite suite)
{
  HEX_ASSERT(suite != NULL);

  ClassSection class_section = HEX_MALLOC(struct HexClassSection);
  class_section->class_access_specifier = class_access_specifier;
  class_section->suite = suite;

  return class_section;
}

Module
hex_ast_create_module(char *module_identifier)
{
  HEX_ASSERT(module_identifier != NULL);

  Module module = HEX_MALLOC(struct HexModule);
  module->module_identifier = module_identifier;

  return module;
}

ModuleList
hex_ast_create_module_list(Module module, ModuleList parent_list)
{
  HEX_ASSERT(module != NULL);

  ModuleList module_list = HEX_MALLOC(struct HexModuleList);
  module_list->module = module;
  module_list->next = 0;

  if(parent_list) {
    parent_list->next = module_list;
    return parent_list;
  } else {
    return module_list;
  }
}

DirectImportStmt
hex_ast_create_direct_import_stmt(ModuleList module_list, char *alias)
{
  HEX_ASSERT(module_list != NULL);

  DirectImportStmt direct_import_stmt = HEX_MALLOC(struct HexDirectImportStmt);
  direct_import_stmt->module_list = module_list;
  direct_import_stmt->alias = alias;

  return direct_import_stmt;
}

RelativeImportStmt
hex_ast_create_relative_import_stmt(ModuleList module_list, Module module, char *alias)
{
  HEX_ASSERT(module_list != NULL);
  HEX_ASSERT(module != NULL);

  RelativeImportStmt relative_import_stmt = HEX_MALLOC(struct HexRelativeImportStmt);
  relative_import_stmt->module_list = module_list;
  relative_import_stmt->module = module;
  relative_import_stmt->alias = alias;

  return relative_import_stmt;
}

ImportStmt
hex_ast_create_import_stmt(int type, void *value)
{
  HEX_ASSERT(value != NULL);

  ImportStmt import_stmt = HEX_MALLOC(struct HexImportStmt);

  switch(type)
  {
    case import_stmt_type_direct:
      {
        import_stmt->import_stmt_type = import_stmt_type_direct;
        import_stmt->import_stmt_direct_import_stmt = (DirectImportStmt)value;
      }
      break;
    case import_stmt_type_relative:
      {
        import_stmt->import_stmt_type = import_stmt_type_relative;
        import_stmt->import_stmt_relative_import_stmt = (RelativeImportStmt)value;
      }
      break;
    default:
      AST_ERROR(0, "Unknown import statement type");
      break;
  }

  return import_stmt;
}

ElifStmt
hex_ast_create_elif_stmt(Expr elif_expr, Suite elif_suite)
{
  HEX_ASSERT(elif_expr != NULL);
  HEX_ASSERT(elif_suite != NULL);

  ElifStmt elif_stmt = HEX_MALLOC(struct HexElifStmt);
  elif_stmt->elif_expr = elif_expr;
  elif_stmt->elif_suite = elif_suite;

  return elif_stmt;
}

ElifGroup
hex_ast_create_elif_group(ElifStmt elif_stmt, ElifGroup parent_list)
{
  HEX_ASSERT(elif_stmt != NULL);

  ElifGroup elif_group = HEX_MALLOC(struct HexElifGroup);
  elif_group->elif_stmt = elif_stmt;
  elif_group->next = 0;

  if(parent_list) {
    parent_list->next = elif_group;
    return parent_list;
  } else {
    return elif_group;
  }
}

IfStmt
hex_ast_create_if_stmt(Expr if_expr, Suite if_suite, ElifGroup elif_group, Suite else_stmt)
{
  HEX_ASSERT(if_expr != NULL);
  HEX_ASSERT(if_suite != NULL);

  IfStmt if_stmt = HEX_MALLOC(struct HexIfStmt);
  if_stmt->if_expr = if_expr;
  if_stmt->elif_group = elif_group;
  if_stmt->else_stmt = else_stmt;

  return if_stmt;
}

IfStmtSimple
hex_ast_create_if_stmt_simple(int type, Expr expr, ExprList expr_list)
{
  HEX_ASSERT(expr != NULL);
  HEX_ASSERT(expr_list != NULL);

  IfStmtSimple if_stmt_simple = HEX_MALLOC(struct HexIfStmtSimple);

  switch(type)
  {
    case if_stmt_simple_type_expr:
      {
        if_stmt_simple->if_stmt_simple_type = if_stmt_simple_type_expr;
        if_stmt_simple->expr = expr;
        if_stmt_simple->expr_list = expr_list;
      }
      break;
    case if_stmt_simple_type_return:
      {
        if_stmt_simple->if_stmt_simple_type = if_stmt_simple_type_return;
        if_stmt_simple->expr = expr;
        if_stmt_simple->expr_list = expr_list;
      }
      break;
    default:
      AST_ERROR(0, "Unknown if statement type");
      break;
  }

  return if_stmt_simple;
}

WhileStmt
hex_ast_create_while_stmt(Expr while_expr, Suite while_suite)
{
  HEX_ASSERT(while_expr != NULL);
  HEX_ASSERT(while_suite != NULL);

  WhileStmt while_stmt = HEX_MALLOC(struct HexWhileStmt);

  while_stmt->while_expr = while_expr;
  while_stmt->while_suite = while_suite;

  return while_stmt;
}

Iterable
hex_ast_create_iterable(int type, void *value)
{
  HEX_ASSERT(value != NULL);

  Iterable iterable = HEX_MALLOC(struct HexIterable);

  switch(type)
  {
    case iterable_type_expr:
      {
        iterable->iterable_type = iterable_type_expr;
        iterable->iterable_expr = (Expr)value;
      }
      break;
    case iterable_type_initializer:
      {
        iterable->iterable_type = iterable_type_initializer;
        iterable->iterable_initializer = (Initializer)value;
      }
      break;
    default:
      AST_ERROR(0, "Internal AST error");
      break;
  }

  return iterable;
}

ForStmt
hex_ast_create_for_stmt(Iterable iterable, Expr expr, Expr where_expr, Suite suite)
{
  HEX_ASSERT(iterable != NULL);
  HEX_ASSERT(expr != NULL);
  HEX_ASSERT(suite != NULL);

  ForStmt for_stmt = HEX_MALLOC(struct HexForStmt);

  for_stmt->iterable = iterable;
  for_stmt->expr = expr;
  for_stmt->where_expr = expr;
  for_stmt->suite = suite;

  return for_stmt; 
}

CatchStmt
hex_ast_create_catch_stmt(int type, void *value, Suite suite)
{
  HEX_ASSERT(suite != NULL);

  CatchStmt catch_stmt = HEX_MALLOC(struct HexCatchStmt);

  switch(type)
  {
    case catch_stmt_type_none:
      {
        catch_stmt->catch_stmt_type = catch_stmt_type_none;
      }
      break;
    case catch_stmt_type_identifier:
      {
        catch_stmt->catch_stmt_type = catch_stmt_type_identifier;
        catch_stmt->catch_identifier = (char*)value;
      }
      break;
    case catch_stmt_type_declaration:
      {
        catch_stmt->catch_stmt_type = catch_stmt_type_declaration;
        catch_stmt->catch_declaration = (Declaration)value;
      }
      break;
    default:
      AST_ERROR(0, "Unknown catch statement type");
      break;
  }

  return catch_stmt;
}

CatchStmtGroup
hex_ast_create_catch_stmt_group(CatchStmt catch_stmt, CatchStmtGroup parent_group)
{
  HEX_ASSERT(catch_stmt != NULL);

  CatchStmtGroup catch_stmt_group = HEX_MALLOC(struct HexCatchStmtGroup);

  catch_stmt_group->catch_stmt = catch_stmt;
  catch_stmt_group->next = 0;

  if(parent_group) {
    parent_group->next = catch_stmt_group;
    return parent_group;
  }

  return catch_stmt_group;
}

FinallyStmt
hex_ast_create_finally_stmt(Suite suite)
{
  HEX_ASSERT(suite != NULL);

  FinallyStmt finally_stmt = HEX_MALLOC(struct HexFinallyStmt);
  finally_stmt->finally_suite = suite;

  return finally_stmt;
}

TryStmt
hex_ast_create_try_stmt(Suite try_suite, CatchStmtGroup catch_stmt_group, FinallyStmt finally_stmt)
{
  HEX_ASSERT(try_suite != NULL);

  TryStmt try_stmt = HEX_MALLOC(struct HexTryStmt);
  try_stmt->try_suite = try_suite;
  try_stmt->catch_stmt_group = catch_stmt_group;
  try_stmt->finally_stmt = finally_stmt;

  return try_stmt;
}

CompoundStmt
hex_ast_create_compound_stmt(int type, void *value)
{
  HEX_ASSERT(value != NULL);

  CompoundStmt compound_stmt = HEX_MALLOC(struct HexCompoundStmt);

  switch(type)
  {
    case compound_stmt_type_if_stmt:
      {
        compound_stmt->compound_stmt_type = compound_stmt_type_if_stmt;
        compound_stmt->compound_stmt_if_stmt = (IfStmt)value;
      }
      break;
    case compound_stmt_type_while_stmt:
      {
        compound_stmt->compound_stmt_type = compound_stmt_type_while_stmt;
        compound_stmt->compound_stmt_while_stmt = (WhileStmt)value;
      }
      break;
    case compound_stmt_type_for_stmt:
      {
        compound_stmt->compound_stmt_type = compound_stmt_type_for_stmt;
        compound_stmt->compound_stmt_for_stmt = (ForStmt)value;
      }
      break;
    case compound_stmt_type_try_stmt:
      {
        compound_stmt->compound_stmt_type = compound_stmt_type_try_stmt;
        compound_stmt->compound_stmt_try_stmt = (TryStmt)value;
      }
      break;
    case compound_stmt_type_func_def:
      {
        compound_stmt->compound_stmt_type = compound_stmt_type_func_def;
        compound_stmt->compound_stmt_func_def = (FuncDef)value;
      }
      break;
    default:
      AST_ERROR(0, "Unknown compound statement type");
      break;
  }

  return compound_stmt;
}

ReturnStmt
hex_ast_create_return_stmt(int type, ExprList expr_list)
{
  ReturnStmt return_stmt = HEX_MALLOC(struct HexReturnStmt);

  switch(type)
  {
    case return_stmt_type_none:
      {
        return_stmt->return_stmt_type = return_stmt_type_none;
      }
      break;
    case return_stmt_type_expr_list:
      {
        return_stmt->return_stmt_type = return_stmt_type_expr_list;
        return_stmt->return_expr_list = (ExprList)expr_list;
      }
      break;
    default:
      AST_ERROR(0, "Unknown return statement type");
      break;
  }

  return return_stmt;
}

ControlSimpleStmt
hex_ast_create_control_simple_stmt(int type, void *value)
{
  ControlSimpleStmt control_simple_stmt = HEX_MALLOC(struct HexControlSimpleStmt);

  switch(type)
  {
    case control_simple_stmt_return:
      {
        control_simple_stmt->control_simple_stmt_type = control_simple_stmt_return;
        control_simple_stmt->control_simple_stmt_return_stmt = (ReturnStmt)value;
      }
      break;
    case control_simple_stmt_continue:
      {
        control_simple_stmt->control_simple_stmt_type = control_simple_stmt_continue;
      }
      break;
    case control_simple_stmt_break:
      {
        control_simple_stmt->control_simple_stmt_type = control_simple_stmt_break;
      }
      break;
    default:
      AST_ERROR(0, "Internal AST error");
      break;
  }

  return control_simple_stmt;
}

SimpleStmt
hex_ast_create_simple_stmt(int type, void *value)
{
  HEX_ASSERT(value != NULL);

  SimpleStmt simple_stmt = HEX_MALLOC(struct HexSimpleStmt);

  switch(type)
  {
    case simple_stmt_type_expr_list:
      {
        simple_stmt->simple_stmt_type = simple_stmt_type_expr_list;
        simple_stmt->simple_stmt_expr_list = (ExprList)value;
      }
      break;
    case simple_stmt_type_declaration:
      {
        simple_stmt->simple_stmt_type = simple_stmt_type_declaration;
        simple_stmt->simple_stmt_declaration = (Declaration)value;
      }
      break;
    case simple_stmt_type_assignment_stmt:
      {
        simple_stmt->simple_stmt_type = simple_stmt_type_assignment_stmt;
        simple_stmt->simple_stmt_assignment_stmt = (AssignmentStmt)value;
      }
      break;
    case simple_stmt_type_import_stmt:
      {
        simple_stmt->simple_stmt_type = simple_stmt_type_import_stmt;
        simple_stmt->simple_stmt_import_stmt = (ImportStmt)value;
      }
      break;
    case simple_stmt_type_if_stmt_simple:
      {
        simple_stmt->simple_stmt_type = simple_stmt_type_if_stmt_simple;
        simple_stmt->simple_stmt_if_stmt_simple = (IfStmtSimple)value;
      }
      break;
    case simple_stmt_type_func_declaration:
      {
        simple_stmt->simple_stmt_type = simple_stmt_type_func_declaration;
        simple_stmt->simple_stmt_func_declaration = (FuncDec)value;
      }
      break;
    case simple_stmt_type_decorator:
      {
        simple_stmt->simple_stmt_type = simple_stmt_type_decorator;
        simple_stmt->simple_stmt_decorator = (Decorator)value;
      }
      break;
    default:
      AST_ERROR(0, "Unknown simple statement type");
      break;
  }

  return simple_stmt;
}

SimpleStmtList
hex_ast_create_simple_stmt_list(SimpleStmt simple_stmt, SimpleStmtList parent_list)
{
  HEX_ASSERT(simple_stmt != NULL);

  SimpleStmtList simple_stmt_list = HEX_MALLOC(struct HexSimpleStmtList);
  simple_stmt_list->simple_stmt = simple_stmt;
  simple_stmt_list->next = 0;

  if(parent_list) {
    parent_list->next = simple_stmt_list;
    return parent_list;
  } else {
    return simple_stmt_list;
  }
}

Stmt
hex_ast_create_stmt(int type, void *value)
{
  HEX_ASSERT(value != NULL);

  Stmt stmt = HEX_MALLOC(struct HexStmt);

  switch(type)
  {
    case stmt_type_simple_stmt_list:
      {
        stmt->stmt_type = stmt_type_simple_stmt_list;
        stmt->stmt_simple_stmt_list = (SimpleStmtList)value;
      }
      break;
    case stmt_type_compound_stmt:
      {
        stmt->stmt_type = stmt_type_compound_stmt;
        stmt->stmt_compound_stmt = (CompoundStmt)value;
      }
      break;
    case stmt_type_control_simple_stmt:
      {
        stmt->stmt_type = stmt_type_control_simple_stmt;
        stmt->stmt_control_simple_stmt = (ControlSimpleStmt)value;
      }
    default:
      AST_ERROR(0, "Unknown statement type");
      break;
  }

  return stmt;
}

StmtGroup
hex_ast_create_stmt_group(Stmt stmt, StmtGroup parent_group)
{
  HEX_ASSERT(stmt != NULL);

  StmtGroup stmt_group = HEX_MALLOC(struct HexStmtGroup);
  stmt_group->stmt = stmt;
  stmt_group->next = 0;

  if(parent_group) {
    parent_group->next = stmt_group;
    return parent_group;
  } else {
    return stmt_group;
  }
}

Suite
hex_ast_create_suite(StmtGroup stmt_group)
{
  HEX_ASSERT(stmt_group != NULL);

  Suite suite = HEX_MALLOC(struct HexSuite);
  suite->stmt_group = stmt_group;

  return suite;
}