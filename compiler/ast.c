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

#include <string.h>
#include "ast.h"
#include "../base/assert.h"
#include "../base/memory.h"
#include "../base/utils.h"

static void *_ast_root_=NULL;
static int _root_type_=0;

void* hex_ast_get_parse_tree_root(int *root_type)
{
  HEX_ASSERT(root_type);
  *root_type = _root_type_;
  return _ast_root_;
}

void hex_ast_set_parse_tree_root(void *p, int root_type)
{
  HEX_ASSERT(p);
  HEX_ASSERT(root_type);
  _ast_root_=p;
  _root_type_=root_type;
}

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
  HEX_ASSERT(value);

  Literal literal = HEX_MALLOC(struct HexLiteral);
  HEX_ASSERT(literal);
  memset(literal, 0, sizeof(struct HexLiteral));

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
        literal->literal_string = strdup((char*)value);
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
  HEX_ASSERT(value);

  PrimaryExpr primary_expr = HEX_MALLOC(struct HexPrimaryExpr);
  HEX_ASSERT(primary_expr);
  memset(primary_expr, 0, sizeof(struct HexPrimaryExpr));

  switch(type)
  {
    case primary_expr_type_identifier:
      {
        primary_expr->primary_expr_type = primary_expr_type_identifier;
        primary_expr->primary_expr_identifier = strdup((char*)value);
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
hex_ast_create_postfix_index_expr(int type, void *value, ExprList indeces_list) 
{
  HEX_ASSERT(value);
  HEX_ASSERT(indeces_list);

  PostfixIndexExpr postfix_index_expr = HEX_MALLOC(struct HexPostfixIndexExpr);
  HEX_ASSERT(postfix_index_expr);
  memset(postfix_index_expr, 0, sizeof(struct HexPostfixIndexExpr));

  switch(type)
  {
    case postfix_index_expr_type_identifier:
      {
        postfix_index_expr->postfix_index_expr_type = postfix_index_expr_type_identifier;
        postfix_index_expr->identifier = strdup((char*)value);
        postfix_index_expr->indeces_list = indeces_list;
      }
      break;
    case postfix_index_expr_type_expr:
      {
        postfix_index_expr->postfix_index_expr_type = postfix_index_expr_type_expr;
        postfix_index_expr->index_expr = (Expr)value;
        postfix_index_expr->indeces_list = indeces_list;
      }
      break;
    default:
      AST_ERROR(0, "Unknown postfix index expression type");
      break;
  }

  return postfix_index_expr;
}

PostfixAccessorExpr
hex_ast_create_postfix_accessor_expr(Expr caller, char *accessor)
{
  HEX_ASSERT(caller);
  HEX_ASSERT(accessor);

  PostfixAccessorExpr postfix_accessor_expr = HEX_MALLOC(struct HexPostfixAccessorExpr);
  HEX_ASSERT(postfix_accessor_expr);
  memset(postfix_accessor_expr, 0, sizeof(struct HexPostfixAccessorExpr));

  postfix_accessor_expr->caller = caller;
  postfix_accessor_expr->accessor = (char*)strdup(accessor);

  return postfix_accessor_expr;
}

PostfixInvocationWithArgsExpr
hex_ast_create_postfix_invocation_with_args_expr(int type, void *value, TupleInitializer arg_list_tuple)
{
  HEX_ASSERT(value);
  HEX_ASSERT(arg_list_tuple);

  PostfixInvocationWithArgsExpr postfix_invocation_with_args_expr = HEX_MALLOC(struct HexPostfixInvocationWithArgsExpr);
  HEX_ASSERT(postfix_invocation_with_args_expr);
  memset(postfix_invocation_with_args_expr, 0, sizeof(struct HexPostfixInvocationWithArgsExpr));

  switch(type)
  {
    case postfix_invocation_expr_with_args_type_identifier:
      {
        postfix_invocation_with_args_expr->postfix_invocation_expr_with_args_type = postfix_invocation_expr_with_args_type_identifier;
        postfix_invocation_with_args_expr->invocation_name = strdup((char*)value);
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

  postfix_invocation_with_args_expr->arg_list = arg_list_tuple->expr_list;

  return postfix_invocation_with_args_expr;
}

PostfixInvocationExpr
hex_ast_create_postfix_invocation_expr(int type, void *invocation_src)
{
  HEX_ASSERT(invocation_src);

  PostfixInvocationExpr postfix_invocation_expr = HEX_MALLOC(struct HexPostfixInvocationExpr);
  HEX_ASSERT(postfix_invocation_expr);
  memset(postfix_invocation_expr, 0, sizeof(struct HexPostfixInvocationExpr));

  switch(type)
  {
    case postfix_invocation_expr_type_identifier:
      {
        postfix_invocation_expr->postfix_invocation_expr_type = postfix_invocation_expr_type_identifier;
        postfix_invocation_expr->invocation_name = strdup((char*)invocation_src);
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
  HEX_ASSERT(value);

  PostfixExpr postfix_expr = HEX_MALLOC(struct HexPostfixExpr);
  HEX_ASSERT(postfix_expr);
  memset(postfix_expr, 0, sizeof(struct HexPostfixExpr));

  switch(type)
  {
    case postfix_expr_type_index:
      {
        postfix_expr->postfix_expr_type = postfix_expr_type_index;
        ListInitializer list_initializer = (ListInitializer)value1;
        HEX_ASSERT(list_initializer);
        PostfixIndexExpr postfix_index_expr = hex_ast_create_postfix_index_expr(type2, value, list_initializer->expr_list); 
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
        PostfixAccessorExpr postfix_accessor_expr = hex_ast_create_postfix_accessor_expr((Expr)value, (char*)value1);
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
        PostfixInvocationWithArgsExpr postfix_invocation_with_args_expr = hex_ast_create_postfix_invocation_with_args_expr(type2, value, value1);
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
  HEX_ASSERT(expr);

  UnaryExpr unary_expr = HEX_MALLOC(struct HexUnaryExpr);
  HEX_ASSERT(unary_expr);
  memset(unary_expr, 0, sizeof(struct HexUnaryExpr));

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
    case unary_expr_type_not:
      {
        unary_expr->unary_expr_type = unary_expr_type_not;
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
  HEX_ASSERT(value);
  HEX_ASSERT(expr);

  CastExpr cast_expr = HEX_MALLOC(struct HexCastExpr);
  HEX_ASSERT(cast_expr);
  memset(cast_expr, 0, sizeof(struct HexCastExpr));

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
        cast_expr->identifier = strdup((char*)value);
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
  HEX_ASSERT(left_expr);
  HEX_ASSERT(right_expr);

  MultiplicativeExpr multi_expr = HEX_MALLOC(struct HexMultiplicativeExpr);
  HEX_ASSERT(multi_expr);
  memset(multi_expr, 0, sizeof(struct HexMultiplicativeExpr));

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
  HEX_ASSERT(left_expr);
  HEX_ASSERT(right_expr);

  AdditiveExpr additive_expr = HEX_MALLOC(struct HexAdditiveExpr);
  HEX_ASSERT(additive_expr);
  memset(additive_expr, 0, sizeof(struct HexAdditiveExpr));

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
  HEX_ASSERT(expr);

  ArithmeticExpr arithmetic_expr = HEX_MALLOC(struct HexArithmeticExpr);
  HEX_ASSERT(arithmetic_expr);
  memset(arithmetic_expr, 0, sizeof(struct HexArithmeticExpr));

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
  HEX_ASSERT(left_expr);
  HEX_ASSERT(right_expr);

  EqualityExpr equality_expr = HEX_MALLOC(struct HexEqualityExpr);
  HEX_ASSERT(equality_expr);
  memset(equality_expr, 0, sizeof(struct HexEqualityExpr));

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
  HEX_ASSERT(left_expr);
  HEX_ASSERT(right_expr);

  LogicExpr logic_expr = HEX_MALLOC(struct HexLogicExpr);
  HEX_ASSERT(logic_expr);
  memset(logic_expr, 0, sizeof(struct HexLogicExpr));

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
  HEX_ASSERT(left_expr);
  HEX_ASSERT(right_expr);

  BitwiseExpr bitwise_expr = HEX_MALLOC(struct HexBitwiseExpr);
  HEX_ASSERT(bitwise_expr);
  memset(bitwise_expr, 0, sizeof(struct HexBitwiseExpr));

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
  HEX_ASSERT(predicate_expr);
  HEX_ASSERT(consequent_expr);
  HEX_ASSERT(alternative_expr);

  ConditionalExpr conditional_expr = HEX_MALLOC(struct HexConditionalExpr);
  HEX_ASSERT(conditional_expr);
  memset(conditional_expr, 0, sizeof(struct HexConditionalExpr));

  conditional_expr->consequent_expr = consequent_expr;
  conditional_expr->predicate_expr = predicate_expr;
  conditional_expr->alternative_expr = alternative_expr;

  Expr expr = hex_ast_create_expr(expr_type_conditional, conditional_expr);

  return expr;
}

Expr
hex_ast_create_range_expr(Expr left_expr, Expr right_expr)
{
  HEX_ASSERT(left_expr);
  HEX_ASSERT(right_expr);

  RangeExpr range_expr = HEX_MALLOC(struct HexRangeExpr);
  HEX_ASSERT(range_expr);
  memset(range_expr, 0, sizeof(struct HexRangeExpr));

  range_expr->left_expr = left_expr;
  range_expr->right_expr = right_expr;

  Expr expr = hex_ast_create_expr(expr_type_range, range_expr);

  return expr;
}

Expr
hex_ast_create_lock_expr(int is_lock, Expr expr)
{
  HEX_ASSERT(expr);

  LockExpr lock_expr = HEX_MALLOC(struct HexLockExpr);
  HEX_ASSERT(lock_expr);
  memset(lock_expr, 0, sizeof(struct HexLockExpr));

  lock_expr->is_lock = is_lock;
  lock_expr->expr = expr;

  Expr _expr = hex_ast_create_expr(expr_type_lock, lock_expr);

  return _expr;
}

Expr
hex_ast_create_weakref_expr(Expr expr)
{
  HEX_ASSERT(expr);

  WeakrefExpr weakref_expr = HEX_MALLOC(struct HexWeakrefExpr);
  HEX_ASSERT(weakref_expr);
  memset(weakref_expr, 0, sizeof(struct HexWeakrefExpr));

  weakref_expr->expr = expr;

  Expr _expr = hex_ast_create_expr(expr_type_weakref, weakref_expr);

  return _expr;
}

Expr
hex_ast_create_this_expr(Expr expr)
{
  HEX_ASSERT(expr);

  ThisExpr this_expr = HEX_MALLOC(struct HexThisExpr);
  HEX_ASSERT(this_expr);
  memset(this_expr, 0, sizeof(struct HexThisExpr));

  this_expr->expr = expr;

  Expr _expr = hex_ast_create_expr(expr_type_this, this_expr);

  return _expr;
}

Expr
hex_ast_create_base_expr(Expr expr)
{
  HEX_ASSERT(expr);

  BaseExpr base_expr = HEX_MALLOC(struct HexBaseExpr);
  HEX_ASSERT(base_expr);
  memset(base_expr, 0, sizeof(struct HexBaseExpr));

  base_expr->expr = expr;

  Expr _expr = hex_ast_create_expr(expr_type_base, base_expr);

  return _expr;
}

Expr
hex_ast_create_expr(int type, void *value)
{
  Expr expr = HEX_MALLOC(struct HexExpr);
  memset(expr, 0, sizeof(struct HexExpr));

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
    case expr_type_this:
      {
        expr->expr_type = expr_type_this;
        expr->this_expr = (ThisExpr)value;
      }
      break;
    case expr_type_base:
      {
        expr->expr_type = expr_type_base;
        expr->base_expr = (BaseExpr)value;
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
  HEX_ASSERT(expr);

  ExprList expr_list = HEX_MALLOC(struct HexExprList);
  memset(expr_list, 0, sizeof(struct HexExprList));

  expr_list->expr = expr;
  expr_list->next = NULL;

  RETURN_VAL_IF_NULL(parent_list, expr_list);

  ExprList _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = expr_list;

  return parent_list;
}

TypeQualifierList
hex_ast_create_type_qualifier_list(TypeQualifier qualifier, TypeQualifierList parent_list)
{
  TypeQualifierList type_qualifier_list = HEX_MALLOC(struct HexTypeQualifierList);
  HEX_ASSERT(type_qualifier_list);
  memset(type_qualifier_list, 0, sizeof(struct HexTypeQualifierList));

  type_qualifier_list->type_qualifier = qualifier;
  type_qualifier_list->next = 0;

  RETURN_VAL_IF_NULL(parent_list, type_qualifier_list);

  TypeQualifierList _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = type_qualifier_list;

  return parent_list;
}

Declaration
hex_ast_create_declaration(TypeQualifierList type_qualifier_list,
  int type_specifier, char *custom_type, ExprList expr_list, char *alias)
{
  Declaration declaration = HEX_MALLOC(struct HexDeclaration);
  HEX_ASSERT(declaration);
  memset(declaration, 0, sizeof(struct HexDeclaration));

  declaration->type_qualifier_list = type_qualifier_list;
  declaration->type_specifier = type_specifier;
  declaration->custom_type = custom_type ? strdup(custom_type) : NULL;
  declaration->expr_list = expr_list;
  declaration->alias = alias ? strdup(alias) : NULL;

  return declaration;
}

Parameter
hex_ast_create_parameter(TypeQualifierList type_qualifier_list, int type_specifier,
  char *custom_type, char *parameter_name, char *alias, int is_ref)
{
  Parameter parameter = HEX_MALLOC(struct HexParameter);
  HEX_ASSERT(parameter);
  memset(parameter, 0, sizeof(struct HexParameter));

  parameter->type_qualifier_list = type_qualifier_list;
  parameter->type_specifier = type_specifier;
  parameter->custom_type = custom_type ? strdup(custom_type) : NULL;
  parameter->parameter_name = parameter_name ? strdup(parameter_name) : NULL;
  parameter->alias = alias ? strdup(alias) : NULL;
  parameter->is_ref = is_ref;

  return parameter;
}

ParameterList
hex_ast_create_parameter_list(Parameter parameter, ParameterList parent_list)
{
  HEX_ASSERT(parameter);

  ParameterList paramlist = HEX_MALLOC(struct HexParameterList);
  HEX_ASSERT(paramlist);
  memset(paramlist, 0, sizeof(struct HexParameterList));

  paramlist->parameter = parameter;
  paramlist->next = 0;

  RETURN_VAL_IF_NULL(parent_list, paramlist);

  ParameterList _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = paramlist;

  return parent_list;
}

ListInitializer
hex_ast_create_list_initializer(ExprList expr_list)
{
  HEX_ASSERT(expr_list);

  ListInitializer list_initializer = HEX_MALLOC(struct HexListInitializer);
  HEX_ASSERT(list_initializer);
  memset(list_initializer, 0, sizeof(struct HexListInitializer));

  list_initializer->expr_list = expr_list;

  return list_initializer;
}

ArrayInitializer
hex_ast_create_array_initializer(ExprList expr_list)
{
  HEX_ASSERT(expr_list);

  ArrayInitializer array_initializer = HEX_MALLOC(struct HexArrayInitializer);
  HEX_ASSERT(array_initializer);
  memset(array_initializer, 0, sizeof(struct HexArrayInitializer));

  array_initializer->expr_list = expr_list;

  return array_initializer;
}

TupleInitializer
hex_ast_create_tuple_initializer(ExprList expr_list)
{
  HEX_ASSERT(expr_list);

  TupleInitializer tuple_initializer = HEX_MALLOC(struct HexTupleInitializer);
  HEX_ASSERT(tuple_initializer);
  memset(tuple_initializer, 0, sizeof(struct HexTupleInitializer));

  tuple_initializer->expr_list = expr_list;

  return tuple_initializer;
}

StructInitializer
hex_ast_create_struct_initializer(AssignmentStmtList assignment_stmt_list)
{
  HEX_ASSERT(assignment_stmt_list);

  StructInitializer struct_initializer = HEX_MALLOC(struct HexStructInitializer);
  HEX_ASSERT(struct_initializer);
  memset(struct_initializer, 0, sizeof(struct HexStructInitializer));

  struct_initializer->assignment_stmt_list = assignment_stmt_list;

  return struct_initializer;
}

SetInitializer
hex_ast_create_set_initializer(ExprList expr_list)
{
  HEX_ASSERT(expr_list);

  SetInitializer set_initializer = HEX_MALLOC(struct HexSetInitializer);
  HEX_ASSERT(set_initializer);
  memset(set_initializer, 0, sizeof(struct HexSetInitializer));

  set_initializer->expr_list = expr_list;

  return set_initializer;
}

MapInitializerSingle
hex_ast_create_map_initializer_single(Expr key, Expr value)
{
  HEX_ASSERT(key);
  HEX_ASSERT(value);

  MapInitializerSingle map_initializer_single = HEX_MALLOC(struct HexMapInitializerSingle);
  map_initializer_single->key = key;
  map_initializer_single->value = value;

  return map_initializer_single;
}

MapInitializerList
hex_ast_create_map_initializer_list(
  MapInitializerSingle map_initializer_single, MapInitializerList parent_list)
{
  HEX_ASSERT(map_initializer_single);

  MapInitializerList map_initializer_list = HEX_MALLOC(struct HexMapInitializerList);
  HEX_ASSERT(map_initializer_list);
  memset(map_initializer_list, 0 , sizeof(struct HexMapInitializerList));

  map_initializer_list->map_initializer_single = map_initializer_single;
  map_initializer_list->next = 0;

  RETURN_VAL_IF_NULL(parent_list, map_initializer_list);

  MapInitializerList _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = map_initializer_list;

  return parent_list;
}

MapInitializer
hex_ast_create_map_initializer(MapInitializerList map_initializer_list)
{
  HEX_ASSERT(map_initializer_list);

  MapInitializer map_initializer = HEX_MALLOC(struct HexMapInitializer);
  HEX_ASSERT(map_initializer);
  memset(map_initializer, 0, sizeof(struct HexMapInitializer));

  map_initializer->map_initializer_list = map_initializer_list;

  return map_initializer;
}

Initializer
hex_ast_create_initializer(int type, void *value)
{
  HEX_ASSERT(value);

  Initializer initializer = HEX_MALLOC(struct HexInitializer);
  HEX_ASSERT(initializer);
  memset(initializer, 0, sizeof(struct HexInitializer));

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
        initializer->set_initializer = (SetInitializer)value;
      }
      break;
    case initializer_type_map:
      {
        initializer->initializer_type = initializer_type_map;
        initializer->map_initializer = (MapInitializer)value;
      }
      break;
    default:
      AST_ERROR(0, "Unknown initializer type");
      break;
  }

  return initializer;
}

Assignment
hex_ast_create_assignment(AssignmentOp assignment_op, int type, void *target)
{
  HEX_ASSERT(target);

  Assignment assignment = HEX_MALLOC(struct HexAssignment);
  HEX_ASSERT(assignment);
  memset(assignment, 0 , sizeof(struct HexAssignment));

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

  assignment->assignment_op = assignment_op;

  return assignment;
}

AssignmentList
hex_ast_create_assignment_list(Assignment assignment, AssignmentList parent_list)
{
  HEX_ASSERT(assignment);

  AssignmentList assignment_list = HEX_MALLOC(struct HexAssignmentList);
  HEX_ASSERT(assignment_list);
  memset(assignment_list, 0, sizeof(struct HexAssignmentList));

  assignment_list->assignment = assignment;
  assignment_list->next = 0;

  RETURN_VAL_IF_NULL(parent_list, assignment_list);

  AssignmentList _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = assignment_list;

  return parent_list;
}

AssignmentStmt
hex_ast_create_assignment_stmt(int type, void *value, AssignmentList assignment_list)
{
  HEX_ASSERT(value);
  HEX_ASSERT(assignment_list);

  AssignmentStmt assignment_stmt = HEX_MALLOC(struct HexAssignmentStmt);
  HEX_ASSERT(assignment_stmt);
  memset(assignment_stmt, 0, sizeof(struct HexAssignmentStmt));

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
  HEX_ASSERT(assignment_stmt);

  AssignmentStmtList assignment_stmt_list = HEX_MALLOC(struct HexAssignmentStmtList);
  HEX_ASSERT(assignment_stmt_list);
  memset(assignment_stmt_list, 0, sizeof(struct HexAssignmentStmtList));

  assignment_stmt_list->assignment_stmt = assignment_stmt;
  assignment_stmt_list->next = 0;

  RETURN_VAL_IF_NULL(parent_list, assignment_stmt_list);

  AssignmentStmtList _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = assignment_stmt_list;

  return parent_list;
}

FuncDec
hex_ast_create_func_dec(TypeQualifierList type_qualifier_list,
  int type_specifier, char *custom_return_type, char *func_name, ParameterList parameter_list)
{
  HEX_ASSERT(func_name);

  FuncDec func_declaration = HEX_MALLOC(struct HexFuncDec);
  HEX_ASSERT(func_declaration);
  memset(func_declaration, 0, sizeof(struct HexFuncDec));

  func_declaration->return_type_qualifier_list = type_qualifier_list;
  func_declaration->return_type_specifier = type_specifier;
  func_declaration->custom_return_type = custom_return_type ? strdup(custom_return_type) : NULL;
  func_declaration->func_name = strdup(func_name);
  func_declaration->parameter_list = parameter_list;

  return func_declaration;
}

FuncDef
hex_ast_create_func_def(FuncDec func_declaration, Suite func_suite)
{
  HEX_ASSERT(func_declaration);
  HEX_ASSERT(func_suite);

  FuncDef func_def = HEX_MALLOC(struct HexFuncDef);
  HEX_ASSERT(func_def);
  memset(func_def, 0, sizeof(struct HexFuncDef));

  func_def->func_declaration = func_declaration;
  func_def->func_suite = func_suite;

  return func_def;
}

LambdaExpr
hex_ast_create_lambda_expr(int type, ParameterList param_list, void *body)
{
  HEX_ASSERT(param_list);
  HEX_ASSERT(body);

  LambdaExpr lambda_expr = HEX_MALLOC(struct HexLambdaExpr);
  HEX_ASSERT(lambda_expr);
  memset(lambda_expr, 0, sizeof(struct HexLambdaExpr));

  lambda_expr->lambda_param_list = param_list;

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
  HEX_ASSERT(expr);

  Attribute attribute = HEX_MALLOC(struct HexAttribute);
  HEX_ASSERT(attribute);
  memset(attribute, 0, sizeof(struct HexAttribute));

  attribute->expr = expr;

  return attribute;
}

CompilerProperty
hex_ast_create_compiler_property(char *compiler_property_name, char *compiler_property_value)
{
  HEX_ASSERT(compiler_property_name);
  HEX_ASSERT(compiler_property_value);

  CompilerProperty compiler_property = HEX_MALLOC(struct HexCompilerProperty);
  HEX_ASSERT(compiler_property);
  memset(compiler_property, 0, sizeof(struct HexCompilerProperty));

  compiler_property->compiler_property_name = strdup(compiler_property_name);
  compiler_property->compiler_property_value = strdup(compiler_property_value);

  return compiler_property;
}

DecoratorListSingle
hex_ast_create_decorator_list_single(int type, void *value)
{
  HEX_ASSERT(value);

  DecoratorListSingle decorator_list_single = HEX_MALLOC(struct HexDecoratorListSingle);
  HEX_ASSERT(decorator_list_single);
  memset(decorator_list_single, 0 , sizeof(struct HexDecoratorListSingle));

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
  HEX_ASSERT(decorator_list_single);

  DecoratorList decorator_list = HEX_MALLOC(struct HexDecoratorList);
  HEX_ASSERT(decorator_list);
  memset(decorator_list, 0, sizeof(struct HexDecoratorList));

  decorator_list->decorator_list_single = decorator_list_single;
  decorator_list->next = 0;

  RETURN_VAL_IF_NULL(parent_list, decorator_list);

  DecoratorList _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = decorator_list;

  return parent_list;
}

Decorator
hex_ast_create_decorator(DecoratorList decorator_list)
{
  HEX_ASSERT(decorator_list);

  Decorator decorator = HEX_MALLOC(struct HexDecorator);
  HEX_ASSERT(decorator);
  memset(decorator, 0, sizeof(struct HexDecorator));

  decorator->decorator_list = decorator_list;

  return decorator;
}

ClassDeclaration
hex_ast_create_class_declaration(char *name, ExprList expr_list)
{
  HEX_ASSERT(name);

  ClassDeclaration class_declaration = HEX_MALLOC(struct HexClassDeclaration);
  HEX_ASSERT(class_declaration);
  memset(class_declaration, 0, sizeof(struct HexClassDeclaration));

  class_declaration->name = strdup(name);
  class_declaration->expr_list = expr_list;

  return class_declaration;
}

ClassSection
hex_ast_create_class_section(int class_access_specifier, Suite suite)
{
  HEX_ASSERT(suite);

  ClassSection class_section = HEX_MALLOC(struct HexClassSection);
  HEX_ASSERT(class_section);
  memset(class_section, 0, sizeof(struct HexClassSection));

  class_section->class_access_specifier = class_access_specifier;
  class_section->suite = suite;

  return class_section;
}

Module
hex_ast_create_module(char *module_identifier)
{
  HEX_ASSERT(module_identifier);

  Module module = HEX_MALLOC(struct HexModule);
  HEX_ASSERT(module);
  memset(module, 0, sizeof(struct HexModule));

  module->module_identifier = strdup(module_identifier);

  return module;
}

ModuleList
hex_ast_create_module_list(Module module, ModuleList parent_list)
{
  HEX_ASSERT(module);

  ModuleList module_list = HEX_MALLOC(struct HexModuleList);
  HEX_ASSERT(module_list);
  memset(module_list, 0, sizeof(struct HexModuleList));

  module_list->module = module;
  module_list->next = 0;

  RETURN_VAL_IF_NULL(parent_list, module_list);

  ModuleList _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = module_list;

  return parent_list;
}

DirectImportStmt
hex_ast_create_direct_import_stmt(ModuleList module_list, char *alias)
{
  HEX_ASSERT(module_list);

  DirectImportStmt direct_import_stmt = HEX_MALLOC(struct HexDirectImportStmt);
  HEX_ASSERT(direct_import_stmt);
  memset(direct_import_stmt, 0, sizeof(struct HexDirectImportStmt));

  direct_import_stmt->module_list = module_list;
  direct_import_stmt->alias = alias ? strdup(alias) : NULL;

  return direct_import_stmt;
}

RelativeImportStmt
hex_ast_create_relative_import_stmt(ModuleList module_list, Module module, char *alias)
{
  HEX_ASSERT(module_list);
  HEX_ASSERT(module);

  RelativeImportStmt relative_import_stmt = HEX_MALLOC(struct HexRelativeImportStmt);
  HEX_ASSERT(relative_import_stmt);
  memset(relative_import_stmt, 0, sizeof(struct HexRelativeImportStmt));

  relative_import_stmt->module_list = module_list;
  relative_import_stmt->module = module;
  relative_import_stmt->alias = alias ? strdup(alias) : NULL;

  return relative_import_stmt;
}

ImportStmt
hex_ast_create_import_stmt(int type, void *value)
{
  HEX_ASSERT(value);

  ImportStmt import_stmt = HEX_MALLOC(struct HexImportStmt);
  HEX_ASSERT(import_stmt);
  memset(import_stmt, 0, sizeof(struct HexImportStmt));

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
  HEX_ASSERT(elif_expr);
  HEX_ASSERT(elif_suite);

  ElifStmt elif_stmt = HEX_MALLOC(struct HexElifStmt);
  HEX_ASSERT(elif_stmt);
  memset(elif_stmt, 0, sizeof(struct HexElifStmt));

  elif_stmt->elif_expr = elif_expr;
  elif_stmt->elif_suite = elif_suite;

  return elif_stmt;
}

ElifGroup
hex_ast_create_elif_group(ElifStmt elif_stmt, ElifGroup parent_list)
{
  HEX_ASSERT(elif_stmt);

  ElifGroup elif_group = HEX_MALLOC(struct HexElifGroup);
  HEX_ASSERT(elif_group);
  memset(elif_group, 0, sizeof(struct HexElifGroup));

  elif_group->elif_stmt = elif_stmt;
  elif_group->next = 0;

  RETURN_VAL_IF_NULL(parent_list, elif_group);

  ElifGroup _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = elif_group;

  return parent_list;
}

IfStmt
hex_ast_create_if_stmt(Expr if_expr, Suite if_suite, ElifGroup elif_group, Suite else_stmt)
{
  HEX_ASSERT(if_expr);
  HEX_ASSERT(if_suite);

  IfStmt if_stmt = HEX_MALLOC(struct HexIfStmt);
  HEX_ASSERT(if_stmt);
  memset(if_stmt, 0, sizeof(struct HexIfStmt));

  if_stmt->if_suite = if_suite;
  if_stmt->if_expr = if_expr;
  if_stmt->elif_group = elif_group;
  if_stmt->else_stmt = else_stmt;

  return if_stmt;
}

IfStmtSimple
hex_ast_create_if_stmt_simple(int type, Expr expr, ExprList expr_list)
{
  HEX_ASSERT(expr);
  HEX_ASSERT(expr_list);

  IfStmtSimple if_stmt_simple = HEX_MALLOC(struct HexIfStmtSimple);
  HEX_ASSERT(if_stmt_simple);
  memset(if_stmt_simple, 0, sizeof(struct HexIfStmtSimple));

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
  HEX_ASSERT(while_expr);
  HEX_ASSERT(while_suite);

  WhileStmt while_stmt = HEX_MALLOC(struct HexWhileStmt);
  HEX_ASSERT(while_stmt);
  memset(while_stmt, 0, sizeof(struct HexWhileStmt));

  while_stmt->while_expr = while_expr;
  while_stmt->while_suite = while_suite;

  return while_stmt;
}

Iterable
hex_ast_create_iterable(int type, void *value)
{
  HEX_ASSERT(value);

  Iterable iterable = HEX_MALLOC(struct HexIterable);
  HEX_ASSERT(iterable);
  memset(iterable, 0, sizeof(struct HexIterable));

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
  HEX_ASSERT(iterable);
  HEX_ASSERT(expr);
  HEX_ASSERT(suite);

  ForStmt for_stmt = HEX_MALLOC(struct HexForStmt);
  HEX_ASSERT(for_stmt);
  memset(for_stmt, 0, sizeof(struct HexForStmt));

  for_stmt->iterable = iterable;
  for_stmt->expr = expr;
  for_stmt->where_expr = where_expr;
  for_stmt->suite = suite;

  return for_stmt; 
}

CatchStmt
hex_ast_create_catch_stmt(int type, void *value, Suite suite)
{
  HEX_ASSERT(suite);

  CatchStmt catch_stmt = HEX_MALLOC(struct HexCatchStmt);
  HEX_ASSERT(catch_stmt);
  memset(catch_stmt, 0, sizeof(struct HexCatchStmt));

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
        catch_stmt->catch_identifier = value ? strdup((char*)value) : NULL;
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

  catch_stmt->catch_suite = suite;

  return catch_stmt;
}

CatchStmtGroup
hex_ast_create_catch_stmt_group(CatchStmt catch_stmt, CatchStmtGroup parent_group)
{
  HEX_ASSERT(catch_stmt);

  CatchStmtGroup catch_stmt_group = HEX_MALLOC(struct HexCatchStmtGroup);
  HEX_ASSERT(catch_stmt_group);
  memset(catch_stmt_group, 0, sizeof(struct HexCatchStmtGroup));

  catch_stmt_group->catch_stmt = catch_stmt;
  catch_stmt_group->next = 0;

  RETURN_VAL_IF_NULL(parent_group, catch_stmt_group);

  CatchStmtGroup _p = parent_group;
  while(_p->next) { _p = _p->next; }
  _p->next = catch_stmt_group;

  return parent_group;
}

FinallyStmt
hex_ast_create_finally_stmt(Suite suite)
{
  HEX_ASSERT(suite);

  FinallyStmt finally_stmt = HEX_MALLOC(struct HexFinallyStmt);
  HEX_ASSERT(finally_stmt);
  memset(finally_stmt, 0, sizeof(struct HexFinallyStmt));

  finally_stmt->finally_suite = suite;

  return finally_stmt;
}

TryStmt
hex_ast_create_try_stmt(Suite try_suite, CatchStmtGroup catch_stmt_group, FinallyStmt finally_stmt)
{
  HEX_ASSERT(try_suite);

  TryStmt try_stmt = HEX_MALLOC(struct HexTryStmt);
  HEX_ASSERT(try_stmt);
  memset(try_stmt, 0, sizeof(struct HexTryStmt));

  try_stmt->try_suite = try_suite;
  try_stmt->catch_stmt_group = catch_stmt_group;
  try_stmt->finally_stmt = finally_stmt;

  return try_stmt;
}

CompoundStmt
hex_ast_create_compound_stmt(int type, void *value)
{
  HEX_ASSERT(value);

  CompoundStmt compound_stmt = HEX_MALLOC(struct HexCompoundStmt);
  HEX_ASSERT(compound_stmt);
  memset(compound_stmt, 0, sizeof(struct HexCompoundStmt));

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
  HEX_ASSERT(return_stmt);
  memset(return_stmt, 0, sizeof(struct HexReturnStmt));

  switch(type)
  {
    case return_stmt_type_none:
      {
        return_stmt->return_stmt_type = return_stmt_type_none;
        return_stmt->return_expr_list = NULL;
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
  HEX_ASSERT(control_simple_stmt);
  memset(control_simple_stmt, 0, sizeof(struct HexControlSimpleStmt));

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
  HEX_ASSERT(value);

  SimpleStmt simple_stmt = HEX_MALLOC(struct HexSimpleStmt);
  HEX_ASSERT(simple_stmt);
  memset(simple_stmt, 0, sizeof(struct HexSimpleStmt));

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
  HEX_ASSERT(simple_stmt);

  SimpleStmtList simple_stmt_list = HEX_MALLOC(struct HexSimpleStmtList);
  HEX_ASSERT(simple_stmt_list);
  memset(simple_stmt_list, 0, sizeof(struct HexSimpleStmtList));

  simple_stmt_list->simple_stmt = simple_stmt;
  simple_stmt_list->next = 0;

  RETURN_VAL_IF_NULL(parent_list, simple_stmt_list);

  SimpleStmtList _p = parent_list;
  while(_p->next) { _p = _p->next; }
  _p->next = simple_stmt_list;

  return parent_list;
}

Stmt
hex_ast_create_stmt(int type, void *value)
{
  HEX_ASSERT(value);

  Stmt stmt = HEX_MALLOC(struct HexStmt);
  HEX_ASSERT(stmt);
  memset(stmt, 0, sizeof(struct HexStmt));

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
      break;
    default:
      AST_ERROR(0, "Unknown statement type");
      break;
  }

  return stmt;
}

StmtGroup
hex_ast_create_stmt_group(Stmt stmt, StmtGroup parent_group)
{
  HEX_ASSERT(stmt);

  StmtGroup stmt_group = HEX_MALLOC(struct HexStmtGroup);
  HEX_ASSERT(stmt_group);
  memset(stmt_group, 0, sizeof(struct HexStmtGroup));

  stmt_group->stmt = stmt;
  stmt_group->next = NULL;

  RETURN_VAL_IF_NULL(parent_group, stmt_group);

  StmtGroup _p = parent_group;
  while(_p->next) { _p = _p->next; }
  _p->next = stmt_group;

  return parent_group;
}

Suite
hex_ast_create_suite(StmtGroup stmt_group)
{
  HEX_ASSERT(stmt_group);

  Suite suite = HEX_MALLOC(struct HexSuite);
  suite->stmt_group = stmt_group;

  return suite;
}
