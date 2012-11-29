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

#include "ast.h"


typedef struct HexSemantics *Semantics;

Semantics semantics_create();
void semantics_free(Semantics *semantics);
unsigned int semantics_get_errcode(Semantics semantics);
char* semantics_get_errmsg(Semantics semantics);


int
hex_semantics_check_stmt_group(
  StmtGroup stmt_group, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_stmt(
  Stmt stmt, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_simple_stmt_list(
  SimpleStmtList stmt_list, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_compound_stmt(
  CompoundStmt compound_stmt, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_control_simple_stmt(
  ControlSimpleStmt stmt, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_simple_stmt(
  SimpleStmt simple_stmt, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_assginment_stmt(
  AssignmentStmt assigment_stmt, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_declaration(
  Declaration declaration, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_decorator(
  Decorator decorator, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_expr_list(
  ExprList exprlist, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_func_dec(
  FuncDec func_dec, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_import_stmt(
  ImportStmt import_stmt, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_type_qualifier_list(
  TypeQualifierList qualifier_list, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_parameter_list(
  ParameterList paramlist, char *func_name, Semantics semantics);

int
hex_semantics_check_expr(
  Expr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_primary_expr(
  PrimaryExpr primary_expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_postfix_expr(
  PostfixExpr postfix_expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_postfix_index_expr(
  PostfixIndexExpr index_expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_postfix_inc_dec_expr(
  Expr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_postfix_acessor_expr(
  PostfixAccessorExpr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_postfix_invocation_expr(
  PostfixInvocationExpr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_postfix_invocation_with_args_expr(
  PostfixInvocationWithArgsExpr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_range_expr(
  RangeExpr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_arithmetic_expr(
  ArithmeticExpr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_cast_expr(
  CastExpr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_conditional_expr(
  ConditionalExpr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_unary_expr(
  UnaryExpr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_this_expr(
  ThisExpr expr, unsigned int indent_level, Semantics semantics);

int
hex_semantics_check_base_expr(
  BaseExpr expr, unsigned int indent_level, Semantics semantics);


#endif /* _SEMANTICS_H_ */
