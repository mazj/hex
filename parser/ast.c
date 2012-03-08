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
Expr* createPrimaryExpr(int type, void* value) {
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

	Expr* expr = createExpr(expr_type_primary, primary_expr);

	return expr;
}


//===========================================================================
// createPostfixExpr() - construct an AST node of type PostfixExpr.
//===========================================================================
Expr* createPostfixExpr(int type, void* value1, void* value2) {
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

	Expr* expr = createExpr(expr_type_postfix, postfix_expr);

	return expr;
}


//===========================================================================
// createUnaryExpr() - construct an AST node of type UnaryExpr.
//===========================================================================
Expr* createUnaryExpr(int type, void* value1, void* value2) {
	UnaryExpr *unary_expr = MALLOC(UnaryExpr);

	switch(type) {
		case unary_expr_type_prefix_inc:
			unary_expr->unary_expr_type = unary_expr_type_prefix_inc;
			unary_expr->unary_expr_prefix_inc_expr = (Expr*)value1;
			break;
		case unary_expr_type_prefix_dec:
			unary_expr->unary_expr_type = unary_expr_type_prefix_dec;
			unary_expr->unary_expr_prefix_dec_expr = (Expr*)value1;
			break;
		case unary_expr_type_unary_op:
			unary_expr->unary_expr_type = unary_expr_type_unary_op;
			unary_expr->unary_expr_unary_op_expr = MALLOC(PrefixUnaryOpExpr);
			unary_expr->unary_expr_unary_op_expr->expr = (Expr*)value1;
			unary_expr->unary_expr_unary_op_expr->unary_op = DEREF_VOID(int, value2);
			break;
		case unary_expr_type_sizeof:
			unary_expr->unary_expr_type = unary_expr_type_sizeof;
			unary_expr->unary_expr_sizeof_expr = (Expr*)value1;
			break;
		default:
			AST_ERROR();
			break;
	}

	Expr* expr = createExpr(expr_type_unary, unary_expr);

	return expr;
}


//===========================================================================
// createCastExpr() - construct an AST node of type CastExpr.
//===========================================================================
Expr* createCastExpr(void* value1, void* value2) {
	CastExpr *cast_expr = MALLOC(CastExpr);

	cast_expr->cast_expr = (Expr*)value1;
	cast_expr->cast_type = (char*)value2;

	Expr* expr = createExpr(expr_type_cast, cast_expr);

	return expr;
}


//===========================================================================
// createMultiplcativeExpr() - construct an AST node of type MultiplcativeExpr.
//===========================================================================
MultiplicativeExpr* createMultiplicativeExpr(int type, void* value1, void* value2) {
	MultiplicativeExpr *multi_expr = MALLOC(MultiplicativeExpr);

	switch(type) {
		case multiplicative_expr_type_mul:
			multi_expr->multi_expr_type = multiplicative_expr_type_mul;
			break;
		case multiplicative_expr_type_div:
			multi_expr->multi_expr_type = multiplicative_expr_type_div;
			break;
		case multiplicative_expr_type_mod:
			multi_expr->multi_expr_type = multiplicative_expr_type_mod;
			break;
		default:
			AST_ERROR();
			break;
	}

	multi_expr->left_expr = (Expr*)value1;
	multi_expr->right_expr = (Expr*)value2;

	return multi_expr;
}


//===========================================================================
// createAdditiveExpr() - construct an AST node of type AdditiveExpr.
//===========================================================================
AdditiveExpr* createAdditiveExpr(int type, void* value1, void* value2) {
	AdditiveExpr *additive_expr = MALLOC(AdditiveExpr);

	switch(type) {
		case additive_expr_type_plus:
			additive_expr->additive_expr_type = additive_expr_type_plus;
			break;
		case additive_expr_type_minus:
			additive_expr->additive_expr_type = additive_expr_type_minus;
			break;
		default:
			AST_ERROR();
			break;
	}

	additive_expr->left_expr = (Expr*)value1;
	additive_expr->right_expr = (Expr*)value2;

	return additive_expr;
}


//===========================================================================
// createArithmeticExpr() - construct an AST node of type ArithmeticExpr.
//===========================================================================
Expr* createArithmeticExpr(int type, void* value1, void* value2) {
	ArithmeticExpr *arithmetic_expr = MALLOC(ArithmeticExpr);

	switch(type) {
		case arithmetic_expr_type_multiplicative:
			arithmetic_expr->arithmetic_expr_type = arithmetic_expr_type_multiplicative;
			break;
		case arithmetic_expr_type_additive:
			arithmetic_expr->arithmetic_expr_type = arithmetic_expr_type_additive;
			break;
		default:
			AST_ERROR();
			break;
	}

	arithmetic_expr->left_expr = (Expr*)value1;
	arithmetic_expr->right_expr = (Expr*)value2;

	Expr* expr = createExpr(expr_type_arithmetic, arithmetic_expr);

	return expr;
}


//===========================================================================
// createEqualityExpr() - construct an AST node of type EqualityExpr.
//===========================================================================
EqualityExpr* createEqualityExpr(int type, void* value1, void* value2) {
	EqualityExpr* equality_expr = MALLOC(EqualityExpr);

	switch(type) {
		case equality_expr_type_eq:
			equality_expr->equality_expr_type = equality_expr_type_eq;
			break;
		case equality_expr_type_neq:
			equality_expr->equality_expr_type = equality_expr_type_neq;
			break;
		case equality_expr_type_less:
			equality_expr->equality_expr_type = equality_expr_type_less;
			break;
		case equality_expr_type_greater:
			equality_expr->equality_expr_type = equality_expr_type_greater;
			break;
		case equality_expr_type_le:
			equality_expr->equality_expr_type = equality_expr_type_le;
			break;
		case equality_expr_type_ge:
			equality_expr->equality_expr_type = equality_expr_type_ge;
			break;
		default:
			AST_ERROR();
			break;
	}

	equality_expr->left_expr = (Expr*)value1;
	equality_expr->right_expr = (Expr*)value2;

	return equality_expr;
}


//===========================================================================
// createLogicExpr() - construct an AST node of type LogicExpr.
//===========================================================================
LogicExpr* createLogicExpr(int type, void* value1, void* value2) {
	LogicExpr* logic_expr = MALLOC(LogicExpr);

	switch(type) {
		case logic_expr_type_logic_and:
			logic_expr->logic_expr_type = logic_expr_type_logic_and;
			break;
		case logic_expr_type_logic_or:
			logic_expr->logic_expr_type = logic_expr_type_logic_or;
			break;
		default:
			AST_ERROR();
			break;
	}

	logic_expr->left_expr = (Expr*)value1;
	logic_expr->right_expr = (Expr*)value2;

	return logic_expr;
}


//===========================================================================
// createBitwiseExpr() - construct an AST node of type BitwiseExpr.
//===========================================================================
BitwiseExpr* createBitwiseExpr(int type, void* value1, void* value2) {
	BitwiseExpr* bitwise_expr = MALLOC(BitwiseExpr);

	switch(type) {
		case bitwise_expr_type_shift_left:
			bitwise_expr->bitwise_expr_type = bitwise_expr_type_shift_left;
			break;
		case bitwise_expr_type_shift_right:
			bitwise_expr->bitwise_expr_type = bitwise_expr_type_shift_right;
			break;
		case bitwise_expr_type_bitwise_and:
			bitwise_expr->bitwise_expr_type = bitwise_expr_type_bitwise_and;
			break;
		case bitwise_expr_type_bitwise_or:
			bitwise_expr->bitwise_expr_type = bitwise_expr_type_bitwise_or;
			break;
		case bitwise_expr_type_bitwise_xor:
			bitwise_expr->bitwise_expr_type = bitwise_expr_type_bitwise_xor;
			break;
		default:
			AST_ERROR();
			break;
	}

	bitwise_expr->left_expr = (Expr*)value1;
	bitwise_expr->right_expr = (Expr*)value2;

	return bitwise_expr;
}


//===========================================================================
// createConditionalExpr() - construct an AST node of type ConditionalExpr.
//===========================================================================
ConditionalExpr* createConditionalExpr(void* value1, void* value2, void* value3) {
	ConditionalExpr* conditional_expr = MALLOC(ConditionalExpr);

	conditional_expr->consequent_expr = (Expr*)value1;
	conditional_expr->predicate_expr = (Expr*)value2;
	conditional_expr->alternative_expr = (Expr*)value3;

	return conditional_expr;
}


//===========================================================================
// createAssignmentExpr() - construct an AST node of type AssignmentExpr.
//===========================================================================
AssignmentExpr* createAssignmentExpr(int type, void* value1, void* value2) {
	AssignmentExpr* assignment_expr = MALLOC(AssignmentExpr);

	switch(type) {
		case assign_op:
			assignment_expr->assignment_expr_op = assign_op;
			break;
		case assign_op_new:
			assignment_expr->assignment_expr_op = assign_op_new;
			break;
		case assign_op_lazy_new:
			assignment_expr->assignment_expr_op = assign_op_lazy_new;
			break;
		case assign_op_mul:
			assignment_expr->assignment_expr_op = assign_op_mul;
			break;
		case assign_op_div:
			assignment_expr->assignment_expr_op = assign_op_div;
			break;
		case assign_op_mod:
			assignment_expr->assignment_expr_op = assign_op_mod;
			break;
		case assign_op_plus:
			assignment_expr->assignment_expr_op = assign_op_plus;
			break;
		case assign_op_minus:
			assignment_expr->assignment_expr_op = assign_op_minus;
			break;
		case assign_op_shift_left:
			assignment_expr->assignment_expr_op = assign_op_shift_left;
			break;
		case assign_op_shift_right:
			assignment_expr->assignment_expr_op = assign_op_shift_right;
			break;
		case assign_op_bitwise_not:
			assignment_expr->assignment_expr_op = assign_op_bitwise_not;
			break;
		case assign_op_bitwise_and:
			assignment_expr->assignment_expr_op = assign_op_bitwise_and;
			break;
		case assign_op_bitwise_or:
			assignment_expr->assignment_expr_op = assign_op_bitwise_or;
			break;
		case assign_op_bitwise_xor:
			assignment_expr->assignment_expr_op = assign_op_bitwise_xor;
			break;
		default:
			AST_ERROR();
			break;
	}

	assignment_expr->left_expr = (Expr*)value1;
	assignment_expr->right_expr = (Expr*)value2;

	return assignment_expr;
}


//===========================================================================
// createLambdaExpr() - construct an AST node of type LambdaExpr.
//===========================================================================
LambdaExpr* createLambdaExpr(void* value1, void* value2) {
	LambdaExpr* lambda_expr = MALLOC(LambdaExpr);

	lambda_expr->lambda_param_list = (ParameterList*)value1;
	lambda_expr->lambda_suite = (Suite*)value2;

	return lambda_expr;
}


//===========================================================================
// createExpr() - construct an AST node of type Expr.
//===========================================================================
Expr* createExpr(int type, void* value) {
	Expr* expr = MALLOC(Expr);

	switch(type) {
		case expr_type_primary:
			expr->expr_type = expr_type_primary;
			PrimaryExpr* primary_expr = (PrimaryExpr*)value;
			expr->primary_expr = primary_expr;
			break;
		case expr_type_postfix:
			expr->expr_type = expr_type_postfix;
			PostfixExpr* postfix_expr = (PostfixExpr*)value;
			expr->postfix_expr = postfix_expr;
			break;
		case expr_type_unary:
			expr->expr_type = expr_type_unary;
			UnaryExpr* unary_expr = (UnaryExpr*)value;
			expr->unary_expr = unary_expr;
			break;
		case expr_type_cast:
			expr->expr_type = expr_type_cast;
			CastExpr* cast_expr = (CastExpr*)value;
			expr->cast_expr = cast_expr;
			break;
		case expr_type_arithmetic:
			expr->expr_type = expr_type_arithmetic;
			ArithmeticExpr* arithmetic_expr = (ArithmeticExpr*)value;
			expr->arithmetic_expr = arithmetic_expr;
			break;
		case expr_type_logic:
			expr->expr_type = expr_type_logic;
			LogicExpr* logic_expr = (LogicExpr*)value;
			expr->logic_expr = logic_expr;
			break;
		case expr_type_bitwise:
			expr->expr_type = expr_type_bitwise;
			BitwiseExpr* bitwise_expr = (BitwiseExpr*)value;
			expr->bitwise_expr = bitwise_expr;
			break;
		case expr_type_conditional:
			expr->expr_type = expr_type_conditional;
			ConditionalExpr* conditional_expr = (ConditionalExpr*)value;
			expr->conditional_expr = conditional_expr;
			break;
		case expr_type_const:
			expr->expr_type = expr_type_const;
			ConstExpr* const_expr = (ConstExpr*)value;
			expr->const_expr = const_expr;
			break;
		case expr_type_lambda:
			expr->expr_type = expr_type_lambda;
			LambdaExpr* lambda_expr = (LambdaExpr*)value;
			expr->lambda_expr = lambda_expr;
			break;
		default:
			AST_ERROR();
			break;
	}

	return expr;
}