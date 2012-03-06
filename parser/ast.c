/* Abstract Syntax Tree */

#include "ast.h"


//===========================================================================
// createLiteral() - construct an AST node of type Literal.
//===========================================================================
Literal* createLiteral(int type, void* value) {
	Literal* literal = MALLOC(Literal);

	switch(type) {
		case literal_type_char:
			literal->literal_type = literal_type_char;
			literal->literal_char = DEREF_VOID(char, value);
			break;
		case literal_type_string:
			literal->literal_type = literal_type_string;
			literal->literal_string = (char*)value;
			break;
		case literal_type_integer:
			literal->literal_type = literal_type_integer;
			literal->literal_integer = DEREF_VOID(int, value);
			break;
		case literal_type_float:
			literal->literal_type = literal_type_float;
			literal->literal_float = DEREF_VOID(double, value);
			break;
		default:
			AST_ERROR();
			break;
	}
	return literal;
}


//===========================================================================
// createPrimaryExpr() - construct an AST node of type PrimaryExpr.
//===========================================================================
PrimaryExpr* createPrimaryExpr(int type, void* value) {
	PrimaryExpr *primary_expr = MALLOC(PrimaryExpr);

	switch(type) {
		case primary_expr_type_identifier:
			primary_expr->primary_expr_type = primary_expr_type_identifier;
			primary_expr->primary_expr_identifier = (char*)value;
			break;
		case primary_expr_type_literal:
			primary_expr->primary_expr_type = primary_expr_type_literal;
			primary_expr->primary_expr_literal = (Literal*)value;
			break;
		case primary_expr_type_expr:
			primary_expr->primary_expr_type = primary_expr_type_expr;
			primary_expr->primary_expr_expr = (Expr*)value;
			break;
		default:
			AST_ERROR();
			break;
	}
	return primary_expr;
}


//===========================================================================
// createPostfixExpr() - construct an AST node of type PostfixExpr.
//===========================================================================
PostfixExpr* createPostfixExpr(int type, void* value1, void* value2) {
	PostfixExpr *postfix_expr = MALLOC(PostfixExpr);

	switch(type) {
		case postfix_expr_type_index:
			postfix_expr->postfix_expr_type = postfix_expr_type_index;
			postfix_expr->postfix_expr_index_expr = MALLOC(PostfixIndexExpr);
			postfix_expr->postfix_expr_index_expr->index_expr = (Expr*)value1;
			postfix_expr->postfix_expr_index_expr->index = DEREF_VOID(int, value2);
			break;
		case postfix_expr_type_postfix_inc:
			postfix_expr->postfix_expr_type = postfix_expr_type_postfix_inc;
			postfix_expr->postfix_expr_postfix_inc_expr = (Expr*)value1;
			break;
		case postfix_expr_type_postfix_dec:
			postfix_expr->postfix_expr_type = postfix_expr_type_postfix_dec;
			postfix_expr->postfix_expr_postfix_dec_expr = (Expr*)value2;
			break;
		case postfix_expr_type_accessor:
			postfix_expr->postfix_expr_type = postfix_expr_type_accessor;
			postfix_expr->postfix_expr_accessor_expr = MALLOC(PostfixAccessorExpr);
			postfix_expr->postfix_expr_accessor_expr->expr = (Expr*)value1;
			postfix_expr->postfix_expr_accessor_expr->accessor = (char*)value2;
			break;
		default:
			AST_ERROR();
			break;
	}
	return postfix_expr;
}