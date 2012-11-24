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

#ifndef _AST_TO_TEXT_H_
#define _AST_TO_TEXT_H

#include "../base/strbuf.h"
#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

void hex_ast_literal_to_text(Literal literal, Strbuf strbuf);

void hex_ast_primary_expr_to_text(PrimaryExpr expr, Strbuf strbuf);

void hex_ast_postfix_accessor_expr_to_text(PostfixAccessorExpr expr, Strbuf strbuf);

void hex_ast_postfix_index_expr_to_text(PostfixIndexExpr expr, Strbuf strbuf);

void hex_ast_postfix_invocation_expr_to_text(PostfixInvocationExpr expr, Strbuf strbuf);

void hex_ast_postfix_invocation_with_args_expr_to_text(PostfixInvocationWithArgsExpr expr, Strbuf strbuf);

void hex_ast_postfix_expr_to_text(PostfixExpr expr, Strbuf strbuf);

void hex_ast_unary_expr_to_text(UnaryExpr expr, Strbuf strbuf);

void hex_ast_additive_expr_to_text(AdditiveExpr expr, Strbuf strbuf);

void hex_ast_multiplicative_to_text(MultiplicativeExpr expr, Strbuf strbuf);

void hex_ast_arithmetic_expr_to_text(ArithmeticExpr expr, Strbuf strbuf);

void hex_ast_equality_expr_to_text(EqualityExpr expr, Strbuf strbuf);

void hex_ast_logic_expr_to_text(LogicExpr expr, Strbuf strbuf);

void hex_ast_bitwise_expr_to_text(BitwiseExpr expr, Strbuf strbuf);

void hex_ast_conditional_expr_to_text(ConditionalExpr expr, Strbuf strbuf);

void hex_ast_range_expr_to_text(RangeExpr expr, Strbuf strbuf);

void hex_ast_lock_expr_to_text(LockExpr expr, Strbuf strbuf);

void hex_ast_weakref_expr_to_text(WeakrefExpr expr, Strbuf strbuf);

void hex_ast_cast_expr_to_text(CastExpr expr, Strbuf strbuf);

void hex_ast_expr_to_text(Expr expr, Strbuf strbuf);

void hex_ast_exprlist_to_text(ExprList exprlist, Strbuf strbuf);

void hex_ast_list_initializer_to_text(ListInitializer list, Strbuf strbuf);

void hex_ast_array_initializer_to_text(ArrayInitializer array, Strbuf strbuf);

void hex_ast_tuple_initializer_to_text(TupleInitializer tuple, Strbuf strbuf);

void hex_ast_struct_initializer_to_text(StructInitializer struct_initializer, Strbuf strbuf);

void hex_ast_set_initializer_to_text(SetInitializer set, Strbuf strbuf);

void hex_ast_initializer_to_text(Initializer initializer, Strbuf strbuf);

void hex_ast_declaration_to_text(Declaration declaration, Strbuf strbuf);

void hex_ast_assignment_to_text(Assignment assignment, Strbuf strbuf);

void hex_ast_assignment_list_to_text(AssignmentList list, Strbuf strbuf);

void hex_ast_assignment_stmt_to_text(AssignmentStmt stmt, Strbuf strbuf);

void hex_ast_assignment_stmt_list_to_text(AssignmentStmtList stmt_list, Strbuf strbuf);

void hex_ast_simple_stmt_to_text(SimpleStmt stmt, Strbuf strbruf);

void hex_ast_simple_stmt_list_to_text(SimpleStmtList list, Strbuf strbuf);

void hex_ast_stmt_to_text(Stmt stmt, Strbuf strbuf);

void hex_ast_stmt_group_to_text(StmtGroup group, Strbuf strbuf);

#ifdef __cplusplus
}
#endif

#endif /* _AST_TO_TEXT_H_ */
