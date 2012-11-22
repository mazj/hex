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
#define _AST_TO_TEXT_H_

#include "../base/strbuf.h"
#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

void hex_ast_type_qualifier_list_to_text(TypeQualifierList type_qualifier_list, Strbuf strbuf);

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

void hex_ast_map_initializer_to_text(MapInitializer map, Strbuf strbuf);

void hex_ast_initializer_to_text(Initializer initializer, Strbuf strbuf);

void hex_ast_declaration_to_text(Declaration declaration, Strbuf strbuf);

void hex_ast_parameter_to_text(Parameter parameter, Strbuf strbuf);

void hex_ast_parameter_list_to_text(ParameterList paramlist, Strbuf strbuf);

void hex_ast_lambda_expr_to_text(LambdaExpr lambda, Strbuf strbuf);

void hex_ast_func_declaration_to_text(FuncDec func_dec, Strbuf strbuf);

void hex_ast_module_list_to_text(ModuleList module_list, Strbuf strbuf);

void hex_ast_direct_import_stmt_to_text(DirectImportStmt stmt, Strbuf strbuf);

void hex_ast_relative_import_stmt_to_text(RelativeImportStmt stmt, Strbuf strbuf);

void hex_ast_import_stmt_to_text(ImportStmt import_stmt, Strbuf strbuf);

void hex_ast_assignment_to_text(Assignment assignment, Strbuf strbuf);

void hex_ast_assignment_list_to_text(AssignmentList list, Strbuf strbuf);

void hex_ast_assignment_stmt_to_text(AssignmentStmt stmt, Strbuf strbuf);

void hex_ast_assignment_stmt_list_to_text(AssignmentStmtList stmt_list, Strbuf strbuf);

void hex_ast_compiler_property_to_text(CompilerProperty compiler_property, Strbuf strbuf);

void hex_ast_attribute_to_text(Attribute attribute, Strbuf strbuf);

void hex_ast_decorator_to_text(Decorator decorator, Strbuf strbuf);

void hex_ast_simple_stmt_to_text(SimpleStmt stmt, Strbuf strbruf);

void hex_ast_simple_stmt_list_to_text(SimpleStmtList list, Strbuf strbuf);

void hex_ast_if_stmt_to_text(IfStmt if_stmt, unsigned char indent_level, Strbuf strbuf);

void hex_ast_elif_group_to_text(ElifGroup elif_group, unsigned char indent_level, Strbuf strbuf);

void hex_ast_while_stmt_to_text(WhileStmt while_stmt, unsigned char indent_level, Strbuf strbuf);

void hex_ast_iterable_to_text(Iterable iterable, Strbuf strbuf);

void hex_ast_for_stmt_to_text(ForStmt for_stmt, unsigned char indent_level, Strbuf strbuf);

void hex_ast_catch_stmt_to_text(CatchStmt catch_stmt, unsigned char indent_level, Strbuf strbuf);

void hex_ast_try_stmt_to_text(TryStmt try_stmt, unsigned char indent_level, Strbuf strbuf);

void hex_ast_func_def_to_text(FuncDef func_def, Strbuf strbuf);

void hex_ast_compound_stmt_to_text(CompoundStmt compound_stmt, unsigned char indent_level, Strbuf strbuf);

void hex_ast_return_stmt_to_text(ReturnStmt return_stmt, Strbuf strbuf);

void hex_ast_control_simple_stmt_to_text(ControlSimpleStmt stmt, Strbuf strbuf);

void hex_ast_stmt_to_text(Stmt stmt, unsigned char indent_level, Strbuf strbuf);

void hex_ast_stmt_group_to_text(StmtGroup group, unsigned char indent_level, Strbuf strbuf);

void hex_ast_suite_to_text(Suite suite, unsigned char indent_level, Strbuf strbuf);

#ifdef __cplusplus
}
#endif

#endif /* _AST_TO_TEXT_H_ */
