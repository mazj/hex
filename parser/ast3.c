/* Abstract Syntax Tree */

#include "ast3.h"


//===========================================================================
// createInteger() - construct an AST node of type Integer.
//===========================================================================
Integer* createInteger(int type, int is_signed, int value) {
	Integer *integer = MALLOC(Integer);

	integer->integer_type = type;
	integer->is_signed = is_signed;

	if(is_signed)
		integer->signed_integer = value;
	else
		integer->unsigned_integer = (unsigned int)value;

	return integer;
}


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
			literal->literal_integer = (Integer*)value;
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
		default:
			AST_ERROR();
			break;
	}

	Expr* expr = createExpr(expr_type_primary, primary_expr);

	return expr;
}


//===========================================================================
// createPostfixIndexExpr() - construct an AST node of type PostfixIndexExpr.
//===========================================================================
PostfixIndexExpr* createPostfixIndexExpr(int type, void *value, ListInitializer* indeces) {
	PostfixIndexExpr *postfix_index_expr = MALLOC(PostfixIndexExpr);

	switch(type) {
		case postfix_index_expr_type_identifier:
			postfix_index_expr->postfix_index_expr_type = postfix_index_expr_type_identifier;
			postfix_index_expr->identifier = (char*)value;
			postfix_index_expr->indeces = indeces;
			break;
		case postfix_index_expr_type_expr:
			postfix_index_expr->postfix_index_expr_type = postfix_index_expr_type_expr;
			postfix_index_expr->index_expr = (Expr*)value;
			postfix_index_expr->indeces = indeces;
			break;
		default:
			AST_ERROR();
			break;
	}

	return postfix_index_expr;
}


//===========================================================================
// createPostfixAccessorExpr() - construct an AST node of type PostfixAccessorExpr.
//===========================================================================
PostfixAccessorExpr* createPostfixAccessorExpr(Expr *caller, Expr* accessor) {
	PostfixAccessorExpr *postfix_accessor_expr = MALLOC(PostfixAccessorExpr);

	postfix_accessor_expr->caller = caller;
	postfix_accessor_expr->accessor = accessor;

	return postfix_accessor_expr;
}


//===========================================================================
// createPostfixInvocationWithArgsExpr() - construct an AST node of type PostfixInvocationWithArgsExpr.
//===========================================================================
PostfixInvocationWithArgsExpr* createPostfixInvocationWithArgsExpr(int type, void *value, ExprList* arg_list) {
	PostfixInvocationWithArgsExpr *postfix_invocation_with_args_expr = MALLOC(PostfixInvocationWithArgsExpr);

	switch(type) {
		case postfix_invocation_expr_with_args_type_identifier:
			postfix_invocation_with_args_expr->postfix_invocation_expr_with_args_type = postfix_invocation_expr_with_args_type_identifier;
			postfix_invocation_with_args_expr->invocation_name = (char*)value;
			break;
		case postfix_invocation_expr_with_args_type_expr:
			postfix_invocation_with_args_expr->postfix_invocation_expr_with_args_type = postfix_invocation_expr_with_args_type_expr;
			postfix_invocation_with_args_expr->invocation_expr = (Expr*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	postfix_invocation_with_args_expr->arg_list = arg_list;

	return postfix_invocation_with_args_expr;
}


//===========================================================================
// createPostfixInvocationExpr() - construct an AST node of type PostfixInvocationExpr.
//===========================================================================
PostfixInvocationExpr* createPostfixInvocationExpr(int type, void *invocation_src) {
	PostfixInvocationExpr *postfix_invocation_expr = MALLOC(PostfixInvocationExpr);

	switch(type) {
		case postfix_invocation_expr_type_identifier:
			postfix_invocation_expr->postfix_invocation_expr_type = postfix_invocation_expr_type_identifier;
			postfix_invocation_expr->invocation_name = (char*)invocation_src;
			break;
		case postfix_invocation_expr_type_expr:
			postfix_invocation_expr->postfix_invocation_expr_type = postfix_invocation_expr_type_expr;
			postfix_invocation_expr->invocation_expr = (Expr*)invocation_src;
			break;
		default:
			AST_ERROR();
	}

	return postfix_invocation_expr;
}



//===========================================================================
// createPostfixExpr() - construct an AST node of type PostfixExpr.
//===========================================================================
Expr* createPostfixExpr(int type, int type2, void* value, void* value1) {
	PostfixExpr *postfix_expr = MALLOC(PostfixExpr);

	switch(type) {
		case postfix_expr_type_index:
			postfix_expr->postfix_expr_type = postfix_expr_type_index;
			PostfixIndexExpr* postfix_index_expr = createPostfixIndexExpr(type2, value, (ListInitializer*)value1);
			postfix_expr->postfix_expr_index_expr = postfix_index_expr;
			break;
		case postfix_expr_type_postfix_inc:
			postfix_expr->postfix_expr_type = postfix_expr_type_postfix_inc;
			postfix_expr->postfix_expr_postfix_inc_expr = (Expr*)value;
			break;
		case postfix_expr_type_postfix_dec:
			postfix_expr->postfix_expr_type = postfix_expr_type_postfix_dec;
			postfix_expr->postfix_expr_postfix_dec_expr = (Expr*)value;
			break;
		case postfix_expr_type_accessor:
			postfix_expr->postfix_expr_type = postfix_expr_type_accessor;
			PostfixAccessorExpr* postfix_accessor_expr = createPostfixAccessorExpr((Expr*)value, (Expr*)value1);
			postfix_expr->postfix_expr_accessor_expr = postfix_accessor_expr;
			break;
		case postfix_expr_type_invocation:
			postfix_expr->postfix_expr_type = postfix_expr_type_invocation;
			PostfixInvocationExpr* postfix_invocation_expr = createPostfixInvocationExpr(type2, value);
			postfix_expr->postfix_expr_invocation_expr = postfix_invocation_expr;
		case postfix_expr_type_invocation_with_args:
			postfix_expr->postfix_expr_type = postfix_expr_type_invocation_with_args;
			PostfixInvocationWithArgsExpr *postfix_invocation_with_args_expr;
			postfix_invocation_with_args_expr = createPostfixInvocationWithArgsExpr(type2, value, (ExprList*)value1);
			postfix_expr->postfix_expr_invocation_with_args_expr = postfix_invocation_with_args_expr;
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
Expr* createUnaryExpr(int type, Expr *expr) {
	UnaryExpr *unary_expr = MALLOC(UnaryExpr);

	switch(type) {
		case unary_expr_type_prefix_inc:
			unary_expr->unary_expr_type = unary_expr_type_prefix_inc;
			unary_expr->unary_expr_prefix_inc_expr = expr;
			break;
		case unary_expr_type_prefix_dec:
			unary_expr->unary_expr_type = unary_expr_type_prefix_dec;
			unary_expr->unary_expr_prefix_dec_expr = expr;
			break;
		case unary_expr_type_unary_minus:
			unary_expr->unary_expr_type = unary_expr_type_unary_minus;
			unary_expr->unary_expr_unary_expr = expr;
			break;
		case unary_expr_type_bitwise_not:
			unary_expr->unary_expr_type = unary_expr_type_bitwise_not;
			unary_expr->unary_expr_bitwise_not = expr;
			break;
		default:
			AST_ERROR();
			break;
	}

	Expr* _expr = createExpr(expr_type_unary, unary_expr);

	return _expr;
}


//===========================================================================
// createCastExpr() - construct an AST node of type CastExpr.
//===========================================================================
Expr* createCastExpr(int type, void* value, Expr *expr) {
	CastExpr *cast_expr = MALLOC(CastExpr);

	switch(type) {
		case cast_expr_type_type_specifier:
			cast_expr->cast_expr_type = cast_expr_type_type_specifier;
			cast_expr->type_specifier = DEREF_VOID(int, value);\
			cast_expr->expr = expr;
			break;
		case cast_expr_type_custom_type:
			cast_expr->cast_expr_type = cast_expr_type_custom_type;
			cast_expr->identifier = (char*)value;
			cast_expr->expr = expr;
			break;
		default:
			AST_ERROR();
			break;
	}

	Expr* _expr = createExpr(expr_type_cast, cast_expr);

	return _expr;
}


//===========================================================================
// createMultiplcativeExpr() - construct an AST node of type MultiplcativeExpr.
//===========================================================================
Expr* createMultiplicativeExpr(int type, Expr *left_expr, Expr *right_expr) {
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

	multi_expr->left_expr = left_expr;
	multi_expr->right_expr = right_expr;

	ArithmeticExpr *arithmetic_expr = createArithmeticExpr(arithmetic_expr_type_multiplicative, multi_expr);

	Expr *expr = createExpr(expr_type_arithmetic, arithmetic_expr);

	return expr;
}


//===========================================================================
// createAdditiveExpr() - construct an AST node of type AdditiveExpr.
//===========================================================================
Expr* createAdditiveExpr(int type, Expr *left_expr, Expr *right_expr) {
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

	additive_expr->left_expr = left_expr;
	additive_expr->right_expr = right_expr;

	ArithmeticExpr *arithmetic_expr = createArithmeticExpr(arithmetic_expr_type_additive, additive_expr);

	Expr *expr = createExpr(expr_type_arithmetic, arithmetic_expr);

	return expr;
}


//===========================================================================
// createArithmeticExpr() - construct an AST node of type ArithmeticExpr.
//===========================================================================
ArithmeticExpr* createArithmeticExpr(int type, void *expr) {
	ArithmeticExpr *arithmetic_expr = MALLOC(ArithmeticExpr);

	switch(type) {
		case arithmetic_expr_type_multiplicative:
			arithmetic_expr->arithmetic_expr_type = arithmetic_expr_type_multiplicative;
			arithmetic_expr->arithmetic_expr_multiplicative_expr = (MultiplicativeExpr*)expr;
			break;
		case arithmetic_expr_type_additive:
			arithmetic_expr->arithmetic_expr_type = arithmetic_expr_type_additive;
			arithmetic_expr->arithmetic_expr_additive_expr = (AdditiveExpr*)expr;
			break;
		default:
			AST_ERROR();
			break;
	}

	return arithmetic_expr;
}


//===========================================================================
// createEqualityExpr() - construct an AST node of type EqualityExpr.
//===========================================================================
Expr* createEqualityExpr(int type, Expr *left_expr, Expr *right_expr) {
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
		case equality_expr_type_is:
			equality_expr->equality_expr_type = equality_expr_type_is;
			break;
		case equality_expr_type_is_not:
			equality_expr->equality_expr_type = equality_expr_type_is_not;
			break;
		default:
			AST_ERROR();
			break;
	}

	equality_expr->left_expr = left_expr;
	equality_expr->right_expr = right_expr;

	Expr *expr = createExpr(expr_type_equality, equality_expr);

	return expr;
}


//===========================================================================
// createLogicExpr() - construct an AST node of type LogicExpr.
//===========================================================================
Expr* createLogicExpr(int type, Expr *left_expr, Expr *right_expr) {
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

	logic_expr->left_expr = left_expr;
	logic_expr->right_expr = right_expr;

	Expr* expr = createExpr(expr_type_logic, logic_expr);

	return expr;
}


//===========================================================================
// createBitwiseExpr() - construct an AST node of type BitwiseExpr.
//===========================================================================
Expr* createBitwiseExpr(int type, Expr *left_expr, Expr *right_expr) {
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

	bitwise_expr->left_expr = left_expr;
	bitwise_expr->right_expr = right_expr;

	Expr *expr = createExpr(expr_type_bitwise, bitwise_expr);

	return expr;
}


//===========================================================================
// createConditionalExpr() - construct an AST node of type ConditionalExpr.
//===========================================================================
Expr* createConditionalExpr(Expr *predicate_expr, Expr *consequent_expr, Expr *alternative_expr) {
	ConditionalExpr* conditional_expr = MALLOC(ConditionalExpr);

	conditional_expr->consequent_expr = consequent_expr;
	conditional_expr->predicate_expr = predicate_expr;
	conditional_expr->alternative_expr = alternative_expr;

	Expr *expr = createExpr(expr_type_conditional, conditional_expr);

	return expr;
}


//===========================================================================
// createRangeExpr() - construct an AST node of type RangeExpr.
//===========================================================================
Expr* createRangeExpr(Expr *left_expr, Expr *right_expr) {
	RangeExpr *range_expr = MALLOC(RangeExpr);

	range_expr->left_expr = left_expr;
	range_expr->right_expr = right_expr;

	Expr *expr = createExpr(expr_type_range, range_expr);

	return expr;
}


//===========================================================================
// createLockExpr() - construct an AST node of type LockExpr.
//===========================================================================
Expr* createLockExpr(int is_lock, Expr *expr) {
	LockExpr *lock_expr = MALLOC(LockExpr);

	lock_expr->is_lock = is_lock;
	lock_expr->expr = expr;

	Expr *_expr = createExpr(expr_type_lock, lock_expr);

	return _expr;
}


//===========================================================================
// createWeakref() - construct an AST node of type WeakrefExpr.
//===========================================================================
Expr* createWeakref(Expr *expr) {
	WeakrefExpr *weakref_expr = MALLOC(WeakrefExpr);

	weakref_expr->expr = expr;

	Expr *_expr = createExpr(expr_type_weakref, weakref_expr);

	return _expr;
}


//===========================================================================
// createAssignmentExpr() - construct an AST node of type AssignmentExpr.
//===========================================================================
// Expr* createAssignmentExpr(int type, void* value1, void* value2) {
// 	AssignmentExpr* assignment_expr = MALLOC(AssignmentExpr);

// 	switch(type) {
// 		case assign_op:
// 			assignment_expr->assignment_expr_op = assign_op;
// 			break;
// 		case assign_op_new:
// 			assignment_expr->assignment_expr_op = assign_op_new;
// 			break;
// 		case assign_op_lazy_new:
// 			assignment_expr->assignment_expr_op = assign_op_lazy_new;
// 			break;
// 		case assign_op_mul:
// 			assignment_expr->assignment_expr_op = assign_op_mul;
// 			break;
// 		case assign_op_div:
// 			assignment_expr->assignment_expr_op = assign_op_div;
// 			break;
// 		case assign_op_mod:
// 			assignment_expr->assignment_expr_op = assign_op_mod;
// 			break;
// 		case assign_op_plus:
// 			assignment_expr->assignment_expr_op = assign_op_plus;
// 			break;
// 		case assign_op_minus:
// 			assignment_expr->assignment_expr_op = assign_op_minus;
// 			break;
// 		case assign_op_shift_left:
// 			assignment_expr->assignment_expr_op = assign_op_shift_left;
// 			break;
// 		case assign_op_shift_right:
// 			assignment_expr->assignment_expr_op = assign_op_shift_right;
// 			break;
// 		case assign_op_bitwise_not:
// 			assignment_expr->assignment_expr_op = assign_op_bitwise_not;
// 			break;
// 		case assign_op_bitwise_and:
// 			assignment_expr->assignment_expr_op = assign_op_bitwise_and;
// 			break;
// 		case assign_op_bitwise_or:
// 			assignment_expr->assignment_expr_op = assign_op_bitwise_or;
// 			break;
// 		case assign_op_bitwise_xor:
// 			assignment_expr->assignment_expr_op = assign_op_bitwise_xor;
// 			break;
// 		default:
// 			AST_ERROR();
// 			break;
// 	}

// 	assignment_expr->left_expr = (Expr*)value1;
// 	assignment_expr->right_expr = (Expr*)value2;

// 	Expr *expr = createExpr(expr_type_assignment, assignment_expr);

// 	return expr;
// }


//===========================================================================
// createExpr() - construct an AST node of type Expr.
//===========================================================================
Expr* createExpr(int type, void* value) {
	Expr* expr = MALLOC(Expr);

	switch(type) {
		case expr_type_primary:
			expr->expr_type = expr_type_primary;
			expr->primary_expr = (PrimaryExpr*)value;
			break;
		case expr_type_postfix:
			expr->expr_type = expr_type_postfix;
			expr->postfix_expr = (PostfixExpr*)value;
			break;
		case expr_type_unary:
			expr->expr_type = expr_type_unary;
			expr->unary_expr = (UnaryExpr*)value;
			break;
		case expr_type_cast:
			expr->expr_type = expr_type_cast;
			expr->cast_expr = (CastExpr*)value;
			break;
		case expr_type_arithmetic:
			expr->expr_type = expr_type_arithmetic;
			expr->arithmetic_expr = (ArithmeticExpr*)value;
			break;
		case expr_type_equality:
			expr->expr_type = expr_type_equality;
			expr->equality_expr = (EqualityExpr*)value;
			break;
		case expr_type_logic:
			expr->expr_type = expr_type_logic;
			expr->logic_expr = (LogicExpr*)value;
			break;
		case expr_type_bitwise:
			expr->expr_type = expr_type_bitwise;
			expr->bitwise_expr = (BitwiseExpr*)value;
			break;
		case expr_type_conditional:
			expr->expr_type = expr_type_conditional;
			expr->conditional_expr = (ConditionalExpr*)value;
			break;
		case expr_type_range:
			expr->expr_type = expr_type_range;
			expr->range_expr = (RangeExpr*)value;
			break;
		case expr_type_lock:
			expr->expr_type = expr_type_lock;
			expr->lock_expr = (LockExpr*)value;
			break;
		case expr_type_weakref:
			expr->expr_type = expr_type_weakref;
			expr->weakref_expr = (WeakrefExpr*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	return expr;
}


//===========================================================================
// createExprList() - construct an AST node of type ExprList.
//===========================================================================
ExprList *createExprList(Expr* expr, ExprList* parent_list) {
	ExprList* expr_list = MALLOC(ExprList);
	expr_list->expr = expr;

	if(parent_list) {
		parent_list->next = expr_list;
		return parent_list;
	} else {
		return expr_list;
	}
}


//===========================================================================
// createTypeQualifierList() - construct an AST node of type TypeQualifierList.
//===========================================================================
TypeQualifierList* createTypeQualifierList(TypeQualifier qualifier, TypeQualifierList* parent_list) {
	TypeQualifierList *qualifier_list = MALLOC(TypeQualifierList);
	qualifier_list->type_qualifier = qualifier;
	qualifier_list->next = 0;

	if(parent_list) {
		parent_list->next = qualifier_list;
		return parent_list;
	} else {
		return qualifier_list;
	}
}


//===========================================================================
// createDeclaration() - construct an AST node of type Declaration.
//===========================================================================
Declaration* createDeclaration(TypeQualifierList *type_qualifier_list,
    int type_specifier, char *custom_type, ExprList *expr_list, char *alias) {
	Declaration *declaration = MALLOC(Declaration);

	declaration->type_qualifier_list = type_qualifier_list;
	declaration->type_specifier = type_specifier;
	declaration->custom_type = custom_type;
	declaration->expr_list = expr_list;
	declaration->alias = alias;

	return declaration;
}


//===========================================================================
// createParameter() - construct an AST node of type Parameter.
//===========================================================================
Parameter* createParameter(TypeQualifierList *type_qualifier_list, int type_specifier,
    char *custom_type, char *parameter_name, char *alias, int is_ref) {
	Parameter *parameter = MALLOC(Parameter);

	parameter->type_qualifier_list = type_qualifier_list;
	parameter->type_specifier = type_specifier;
	parameter->custom_type = custom_type;
	parameter->parameter_name = parameter_name;
	parameter->is_ref = is_ref;

	return parameter;
}


//===========================================================================
// createParameterList() - construct an AST node of type ParameterList.
//===========================================================================
ParameterList *createParameterList(Parameter *parameter, ParameterList* parent_list) {
	ParameterList *param_list = MALLOC(ParameterList);
	param_list->parameter = parameter;
	param_list->next = 0;

	if(parent_list) {
		parent_list->next = param_list;
		return parent_list;
	} else {
		return param_list;
	}
}


//===========================================================================
// createListInitializer() - construct an AST node of type ListInitializer.
//===========================================================================
ListInitializer *createListInitializer(ExprList *expr_list) {
	ListInitializer *list_initializer = MALLOC(ListInitializer);
	list_initializer->expr_list = expr_list;
	return list_initializer;
}


//===========================================================================
// createArrayInitializer() - construct an AST node of type ArrayInitializer.
//===========================================================================
ArrayInitializer *createArrayInitializer(ExprList *expr_list) {
	ArrayInitializer *array_initializer = MALLOC(ArrayInitializer);
	array_initializer->expr_list = expr_list;
	return array_initializer;
}


//===========================================================================
// createTupleInitializer() - construct an AST node of type TupleInitializer.
//===========================================================================
TupleInitializer *createTupleInitializer(ExprList *expr_list) {
	TupleInitializer *tuple_initializer = MALLOC(TupleInitializer);
	tuple_initializer->expr_list = expr_list;
	return tuple_initializer;
}


//===========================================================================
// createStructInitializer() - construct an AST node of type StructInitializer.
//===========================================================================
StructInitializer *createStructInitializer(AssignmentStmtList *assignment_stmt_list) {
	StructInitializer *struct_initializer = MALLOC(StructInitializer);
	struct_initializer->assignment_stmt_list = assignment_stmt_list;
	return struct_initializer;
}


//===========================================================================
// createSetInitializer() - construct an AST node of type SetInitializer.
//===========================================================================
SetInitializer *createSetInitializer(ExprList *expr_list) {
	SetInitializer *set_initializer = MALLOC(SetInitializer);
	set_initializer->expr_list = expr_list;
	return set_initializer;
}


//===========================================================================
// createMapMultimapInitializerSingle() - construct an AST node of type MapMultimapInitializerSingle.
//===========================================================================
MapMultimapInitializerSingle *createMapMultimapInitializerSingle(Expr *key, Expr *value) {
	MapMultimapInitializerSingle *map_initializer_single = MALLOC(MapMultimapInitializerSingle);
	map_initializer_single->key = key;
	map_initializer_single->value = value;
	return map_initializer_single;
}


//===========================================================================
// createMapMultimapInitializerList() - construct an AST node of type MapMultimapInitializerList.
//===========================================================================
MapMultimapInitializerList *createMapMultimapInitializerList(
    MapMultimapInitializerSingle *map_initializer_single,
    MapMultimapInitializerList *parent_list)
{
	MapMultimapInitializerList *map_initializer_list = MALLOC(MapMultimapInitializerList);
	map_initializer_list->map_initializer_single = map_initializer_single;
	map_initializer_list->next = 0;

	if(parent_list) {
		parent_list->next = map_initializer_list;
		return parent_list;
	} else {
		return map_initializer_list;
	}
}


//===========================================================================
// createMapMultimapInitializer() - construct an AST node of type MapMultimapInitializer.
//===========================================================================
MapMultimapInitializer *createMapMultimapInitializer(
    MapMultimapInitializerList *map_initializer_list) {
	MapMultimapInitializer *map_initializer = MALLOC(MapMultimapInitializer);
	map_initializer->map_initializer_list = map_initializer_list;
	return map_initializer;
}


//===========================================================================
// createInitializer() - construct an AST node of type Initializer.
//===========================================================================
Initializer* createInitializer(int type, void* value) {
	Initializer* initializer = MALLOC(Initializer);

	switch(type) {
		case initializer_type_list:
			initializer->initializer_type = initializer_type_list;
			initializer->list_initializer = (ListInitializer*)value;
			break;
		case initializer_type_array:
			initializer->initializer_type = initializer_type_array;
			initializer->array_initializer = (ArrayInitializer*)value;
			break;
		case initializer_type_tuple:
			initializer->initializer_type = initializer_type_tuple;
			initializer->tuple_initializer = (TupleInitializer*)value;
			break;
		case initializer_type_struct:
			initializer->initializer_type = initializer_type_struct;
			initializer->struct_initializer = (StructInitializer*)value;
			break;
		case initializer_type_set:
			initializer->initializer_type = initializer_type_set;
			initializer->set_initialier = (SetInitializer*)value;
			break;
		case initializer_type_mapmultimap:
			initializer->initializer_type = initializer_type_mapmultimap;
			initializer->map_multimap_initializer = (MapMultimapInitializer*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	return initializer;
}


//===========================================================================
// createAssignment() - construct an AST node of type Assignment.
//===========================================================================
Assignment* createAssignment(int type, void* target) {
	Assignment *assignment = MALLOC(Assignment);

	switch(type) {
		case assignment_type_expr:
			assignment->assignment_type = assignment_type_expr;
			assignment->assignment_expr = (Expr*)target;
			break;
		case assignment_type_initializer:
			assignment->assignment_type = assignment_type_initializer;
			assignment->assignment_initializer = (Initializer*)target;
			break;
		case assignment_type_lambda:
			assignment->assignment_type = assignment_type_lambda;
			assignment->assignment_lambda = (LambdaExpr*)target;
			break;
		default:
			AST_ERROR();
			break;
	}

	return assignment;
}


//===========================================================================
// createAssignmentList() - construct an AST node of type AssignmentList.
//===========================================================================
AssignmentList* createAssignmentList(Assignment *assignment, AssignmentList *parent_list) {
	AssignmentList *assignment_list = MALLOC(AssignmentList);
	assignment_list->assignment = assignment;
	assignment_list->next = 0;

	if(parent_list) {
		parent_list->next = assignment_list;
		return parent_list;
	} else {
		return assignment_list;
	}
}


//===========================================================================
// createAssignmentStmt() - construct an AST node of type AssignmentStmt.
//===========================================================================
AssignmentStmt* createAssignmentStmt(int type, void* value, AssignmentList* assignment_list) {
	AssignmentStmt *assignment_stmt = MALLOC(AssignmentStmt);

	switch(type) {
		case assignment_stmt_type_declaration:
			assignment_stmt->assignment_stmt_type = assignment_stmt_type_declaration;
			assignment_stmt->assignment_stmt_declaration = (Declaration*)value;
			assignment_stmt->assignment_list = assignment_list;
			break;
		case assignment_stmt_type_expr_list:
			assignment_stmt->assignment_stmt_type = assignment_stmt_type_expr_list;
			assignment_stmt->assignment_stmt_expr_list = (ExprList*)value;
			assignment_stmt->assignment_list = assignment_list;
			break;
		default:
			AST_ERROR();
			break;
	}

	return assignment_stmt;
}


//===========================================================================
// createAssignmentStmtList() - construct an AST node of type AssignmentStmtList.
//===========================================================================
AssignmentStmtList* createAssignmentStmtList(AssignmentStmt *assignment_stmt,
    AssignmentStmtList *parent_list) {
	AssignmentStmtList *assignment_stmt_list = MALLOC(AssignmentStmtList);
	assignment_stmt_list->assignment_stmt = assignment_stmt;
	assignment_stmt_list->next = 0;

	if(parent_list) {
		parent_list->next = assignment_stmt_list;
		return parent_list;
	} else {
		return assignment_stmt_list;
	}
}


//===========================================================================
// createFuncDec() - construct an AST node of type FuncDec.
//===========================================================================
FuncDec* createFuncDec(TypeQualifierList *type_qualifier_list,
    int type_specifier, char *custom_return_type, char *func_name,
    ParameterList *parameter_list)
{
	FuncDec *func_declaration = MALLOC(FuncDec);
	func_declaration->return_type_qualifier_list = type_qualifier_list;
	func_declaration->return_type_specifier = type_specifier;
	func_declaration->custom_return_type = custom_return_type;
	func_declaration->func_name = func_name;
	func_declaration->parameter_list = parameter_list;

	return func_declaration;
}


//===========================================================================
// createFuncDef() - construct an AST node of type FuncDef.
//===========================================================================
FuncDef* createFuncDef(FuncDec *func_declaration, Suite *func_suite) {
	FuncDef *func_def = MALLOC(FuncDef);

	func_def->func_declaration = func_declaration;
	func_def->func_suite = func_suite;

	return func_def;
}


//===========================================================================
// createLambdaExpr() - construct an AST node of type LambdaExpr.
//===========================================================================
LambdaExpr* createLambdaExpr(int type, ParameterList* param_list, void* body) {
	LambdaExpr* lambda_expr = MALLOC(LambdaExpr);

	switch(lambda_expr->lambda_type) {
		case lambda_type_simple:
			lambda_expr->lambda_type = lambda_type_simple;
			lambda_expr->lambda_simple_stmt_list = (SimpleStmtList*)body;
			break;
		case lambda_type_suite:
			lambda_expr->lambda_type = lambda_type_suite;
			lambda_expr->lambda_suite = (Suite*)body;
			break;
		default:
			AST_ERROR();
			break;
	}

	return lambda_expr;
}


//===========================================================================
// createAttribute() - construct an AST node of type Attribute.
//===========================================================================
Attribute* createAttribute(Expr *expr) {
	Attribute *attribute = MALLOC(Attribute);

	attribute->expr = expr;

	return attribute;
}


//===========================================================================
// createCompilerProperty() - construct an AST node of type CompilerProperty.
//===========================================================================
CompilerProperty* createCompilerProperty(char *compiler_property_name, char *compiler_property_value) {
	CompilerProperty *compiler_property = MALLOC(CompilerProperty);

	compiler_property->compiler_property_name = compiler_property_name;
	compiler_property->compiler_property_value = compiler_property_value;

	return compiler_property;
}


//===========================================================================
// createDecoratorListSingle() - construct an AST node of type DecoratorListSingle.
//===========================================================================
DecoratorListSingle* createDecoratorListSingle(int type, void* value) {
	DecoratorListSingle *decorator_list_single = MALLOC(DecoratorListSingle);

	switch(type) {
		case decorator_list_single_type_attribute:
			decorator_list_single->decorator_list_single_type = decorator_list_single_type_attribute;
			decorator_list_single->decorator_list_single_attribute = (Attribute*)value;
			break;
		case decorator_list_single_type_compiler_property:
			decorator_list_single->decorator_list_single_type = decorator_list_single_type_compiler_property;
			decorator_list_single->decorator_list_single_compiler_property = (CompilerProperty*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	return decorator_list_single;
}


//===========================================================================
// createDecoratorList() - construct an AST node of type DecoratorList.
//===========================================================================
DecoratorList* createDecoratorList(DecoratorListSingle *decorator_list_single, DecoratorList* parent_list) {
	DecoratorList *decorator_list = MALLOC(DecoratorList);
	decorator_list->decorator_list_single = decorator_list_single;
	decorator_list->next = 0;

	if(parent_list) {
		parent_list->next = decorator_list;
		return parent_list;
	} else {
		return decorator_list;
	}
}


//===========================================================================
// createDecorator() - construct an AST node of type Decorator.
//===========================================================================
Decorator* createDecorator(DecoratorList* decorator_list) {
	Decorator *decorator = MALLOC(Decorator);
	decorator->decorator_list = decorator_list;
	return decorator;
}


//===========================================================================
// createClassDeclaration() - construct an AST node of type ClassDeclaration.
//===========================================================================
ClassDeclaration *createClassDeclaration(char *name, ExprList* expr_list) {
	ClassDeclaration *class_declaration = MALLOC(ClassDeclaration);
	class_declaration->name = name;
	class_declaration->expr_list = expr_list;
	return class_declaration;
}


//===========================================================================
// createClassSection() - construct an AST node of type ClassSection.
//===========================================================================
ClassSection *createClassSection(int class_access_specifier, Suite *suite) {
	ClassSection *class_section = MALLOC(ClassSection);
	class_section->class_access_specifier = class_access_specifier;
	class_section->suite = suite;
	return class_section;
}


//===========================================================================
// createModule() - construct an AST node of type Module.
//===========================================================================
Module* createModule(char *module_identifier) {
	Module *module = MALLOC(Module);
	module->module_identifier = module_identifier;
	return module;
}


//===========================================================================
// createModuleList() - construct an AST node of type ModuleList.
//===========================================================================
ModuleList* createModuleList(Module *module, ModuleList *parent_list) {
	ModuleList *module_list = MALLOC(ModuleList);
	module_list->module = module;
	module_list->next = 0;

	if(parent_list) {
		parent_list->next = module_list;
		return parent_list;
	} else {
		return module_list;
	}
}


//===========================================================================
// createDirectImportStmt() - construct an AST node of type DirectImportStmt.
//===========================================================================
DirectImportStmt* createDirectImportStmt(ModuleList *module_list, char *alias) {
	DirectImportStmt *direct_import_stmt = MALLOC(DirectImportStmt);
	direct_import_stmt->module_list = module_list;
	direct_import_stmt->alias = alias;
	return direct_import_stmt;
}


//===========================================================================
// createRelativeImportStmt() - construct an AST node of type RelativeImportStmt.
//===========================================================================
RelativeImportStmt* createRelativeImportStmt(ModuleList *module_list, Module *module, char *alias) {
	RelativeImportStmt *relative_import_stmt = MALLOC(RelativeImportStmt);
	relative_import_stmt->module_list = module_list;
	relative_import_stmt->module = module;
	relative_import_stmt->alias = alias;
	return relative_import_stmt;
}


//===========================================================================
// createImportStmt() - construct an AST node of type ImportStmt.
//===========================================================================
ImportStmt* createImportStmt(int type, void* value) {
	ImportStmt *import_stmt = MALLOC(ImportStmt);

	switch(type) {
		case import_stmt_type_direct:
			import_stmt->import_stmt_type = import_stmt_type_direct;
			import_stmt->import_stmt_direct_import_stmt = (DirectImportStmt*)value;
			break;
		case import_stmt_type_relative:
			import_stmt->import_stmt_type = import_stmt_type_relative;
			import_stmt->import_stmt_relative_import_stmt = (RelativeImportStmt*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	return import_stmt;
}


//===========================================================================
// createElifStmt() - construct an AST node of type ElifStmt.
//===========================================================================
ElifStmt* createElifStmt(Expr *elif_expr, Suite *elif_suite) {
	ElifStmt *elif_stmt = MALLOC(ElifStmt);
	elif_stmt->elif_expr = elif_expr;
	elif_stmt->elif_suite = elif_suite;
	return elif_stmt;
}


//===========================================================================
// createElifGroup() - construct an AST node of type ElifGroup.
//===========================================================================
ElifGroup* createElifGroup(ElifStmt* elif_stmt, ElifGroup *parent_list) {
	ElifGroup *elif_group = MALLOC(ElifGroup);
	elif_group->elif_stmt = elif_stmt;
	elif_group->next = 0;

	if(parent_list) {
		parent_list->next = elif_group;
		return parent_list;
	} else {
		return elif_group;
	}
}


//===========================================================================
// createIfStmt() - construct an AST node of type IfStmt.
//===========================================================================
IfStmt* createIfStmt(Expr *if_expr, Suite *if_suite, ElifGroup *elif_group, Suite *else_stmt) {
	IfStmt *if_stmt = MALLOC(IfStmt);
	if_stmt->if_expr = if_expr;
	if_stmt->elif_group = elif_group;
	if_stmt->else_stmt = else_stmt;

	return if_stmt;
}


//===========================================================================
// createIfStmtSimple() - construct an AST node of type IfStmtSimple.
//===========================================================================
IfStmtSimple* createIfStmtSimple(int type, Expr *expr, ExprList *expr_list) {
	IfStmtSimple *if_stmt_simple = MALLOC(IfStmtSimple);

	switch(type) {
		case if_stmt_simple_type_expr:
			if_stmt_simple->if_stmt_simple_type = if_stmt_simple_type_expr;
			if_stmt_simple->expr = expr;
			if_stmt_simple->expr_list = expr_list;
			break;
		case if_stmt_simple_type_return:
			if_stmt_simple->if_stmt_simple_type = if_stmt_simple_type_return;
			if_stmt_simple->expr = expr;
			if_stmt_simple->expr_list = expr_list;
			break;
		default:
			AST_ERROR();
			break;
	}

	return if_stmt_simple;
}


//===========================================================================
// createWhileStmt() - construct an AST node of type WhileStmt.
//===========================================================================
WhileStmt* createWhileStmt(Expr *while_expr, Suite *while_suite) {
	WhileStmt *while_stmt = MALLOC(WhileStmt);

	while_stmt->while_expr = while_expr;
	while_stmt->while_suite = while_suite;

	return while_stmt;
}


//===========================================================================
// createIterable() - construct an AST node of type Iterable.
//===========================================================================
Iterable* createIterable(int type, void* value) {
	Iterable *iterable = MALLOC(Iterable);

	switch(type) {
		case iterable_type_expr:
			iterable->iterable_type = iterable_type_expr;
			iterable->iterable_expr = (Expr*)value;
			break;
		case iterable_type_initializer:
			iterable->iterable_type = iterable_type_initializer;
			iterable->iterable_initializer = (Initializer*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	return iterable;
}


//===========================================================================
// createForStmt() - construct an AST node of type ForStmt.
//===========================================================================
ForStmt* createForStmt(Iterable *iterable, Expr *expr, Expr *where_expr, Suite *suite) {
	ForStmt *for_stmt = MALLOC(ForStmt);

	for_stmt->iterable = iterable;
	for_stmt->expr = expr;
	for_stmt->where_expr = expr;
	for_stmt->suite = suite;

	return for_stmt; 
}


//===========================================================================
// createCatchStmt() - construct an AST node of type CatchStmt.
//===========================================================================
CatchStmt* createCatchStmt(int type, void* value, Suite *suite) {
	CatchStmt *catch_stmt = MALLOC(CatchStmt);

	switch(type) {
		case catch_stmt_type_none:
			catch_stmt->catch_stmt_type = catch_stmt_type_none;
			break;
		case catch_stmt_type_identifier:
			catch_stmt->catch_stmt_type = catch_stmt_type_identifier;
			catch_stmt->catch_identifier = (char*)value;
			break;
		case catch_stmt_type_declaration:
			catch_stmt->catch_stmt_type = catch_stmt_type_declaration;
			catch_stmt->catch_declaration = (Declaration*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	return catch_stmt;
}


//===========================================================================
// createCatchStmtGroup() - construct an AST node of type CatchStmtGroup.
//===========================================================================
CatchStmtGroup* createCatchStmtGroup(CatchStmt* catch_stmt, CatchStmtGroup* parent_group) {
	CatchStmtGroup *catch_stmt_group = MALLOC(CatchStmtGroup);

	catch_stmt_group->catch_stmt = catch_stmt;
	catch_stmt_group->next = 0;

	if(parent_group) {
		parent_group->next = catch_stmt_group;
		return parent_group;
	}

	return catch_stmt_group;
}


//===========================================================================
// createFinallyStmt() - construct an AST node of type FinallyStmt.
//===========================================================================
FinallyStmt* createFinallyStmt(Suite* suite) {
	FinallyStmt *finally_stmt = MALLOC(FinallyStmt);
	finally_stmt->finally_suite = suite;
	return finally_stmt;
}


//===========================================================================
// createTryStmt() - construct an AST node of type TryStmt.
//===========================================================================
TryStmt* createTryStmt(Suite* try_suite, CatchStmtGroup *catch_stmt_group,
    FinallyStmt *finally_stmt) {
	TryStmt *try_stmt = MALLOC(TryStmt);
	try_stmt->try_suite = try_suite;
	try_stmt->catch_stmt_group = catch_stmt_group;
	try_stmt->finally_stmt = finally_stmt;
	return try_stmt;
}


//===========================================================================
// createCompoundStmt() - construct an AST node of type CompoundStmt.
//===========================================================================
CompoundStmt* createCompoundStmt(int type, void* value) {
	CompoundStmt *compound_stmt = MALLOC(CompoundStmt);

	switch(type) {
		case compound_stmt_type_if_stmt:
			compound_stmt->compound_stmt_type = compound_stmt_type_if_stmt;
			compound_stmt->compound_stmt_if_stmt = (IfStmt*)value;
			break;
		case compound_stmt_type_while_stmt:
			compound_stmt->compound_stmt_type = compound_stmt_type_while_stmt;
			compound_stmt->compound_stmt_while_stmt = (WhileStmt*)value;
			break;
		case compound_stmt_type_for_stmt:
			compound_stmt->compound_stmt_type = compound_stmt_type_for_stmt;
			compound_stmt->compound_stmt_for_stmt = (ForStmt*)value;
			break;
		case compound_stmt_type_try_stmt:
			compound_stmt->compound_stmt_type = compound_stmt_type_try_stmt;
			compound_stmt->compound_stmt_try_stmt = (TryStmt*)value;
			break;
		case compound_stmt_type_func_def:
			compound_stmt->compound_stmt_type = compound_stmt_type_func_def;
			compound_stmt->compound_stmt_func_def = (FuncDef*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	return compound_stmt;
}


//===========================================================================
// createReturnStmt() - construct an AST node of type ReturnStmt.
//===========================================================================
ReturnStmt* createReturnStmt(int type, ExprList *expr_list) {
	ReturnStmt *return_stmt = MALLOC(ReturnStmt);

	switch(type) {
		case return_stmt_type_none:
			return_stmt->return_stmt_type = return_stmt_type_none;
			break;
		case return_stmt_type_expr_list:
			return_stmt->return_stmt_type = return_stmt_type_expr_list;
			return_stmt->return_expr_list = (ExprList*)expr_list;
			break;
		default:
			AST_ERROR();
			break;
	}

	return return_stmt;
}


//===========================================================================
// createContinueStmt() - construct an AST node of type ContinueStmt.
//===========================================================================
// ContinueStmt* createContinueStmt() {
// 	ContinueStmt *continue_stmt = MALLOC(ContinueStmt);
// 	return continue_stmt;
// }


//===========================================================================
// createBreakStmt() - construct an AST node of type BreakStmt.
//===========================================================================
// BreakStmt* createBreakStmt() {
// 	BreakStmt *break_stmt = MALLOC(BreakStmt);
// 	return break_stmt;
// }


//===========================================================================
// createControlSimpleStmt() - construct an AST node of type ControlSimpleStmt.
//===========================================================================
ControlSimpleStmt* createControlSimpleStmt(int type, void* value) {
	ControlSimpleStmt *control_simple_stmt = MALLOC(ControlSimpleStmt);

	switch(type) {
		case control_simple_stmt_return:
			control_simple_stmt->control_simple_stmt_type = control_simple_stmt_return;
			control_simple_stmt->control_simple_stmt_return_stmt = (ReturnStmt*)value;
			break;
		case control_simple_stmt_continue:
			control_simple_stmt->control_simple_stmt_type = control_simple_stmt_continue;
			// control_simple_stmt->control_simple_stmt_continue_stmt = (ContinueStmt*)value;
			break;
		case control_simple_stmt_break:
			control_simple_stmt->control_simple_stmt_type = control_simple_stmt_break;
			// control_simple_stmt->control_simple_stmt_break_stmt = (BreakStmt*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	return control_simple_stmt;
}


//===========================================================================
// createPassStmt() - construct an AST node of type PassStmt.
//===========================================================================
SimpleStmt* createSimpleStmt(int type, void* value) {
	SimpleStmt *simple_stmt = MALLOC(SimpleStmt);

	switch(type) {
		case simple_stmt_type_expr_list:
			simple_stmt->simple_stmt_type = simple_stmt_type_expr_list;
			simple_stmt->simple_stmt_expr_list = (ExprList*)value;
			break;
		case simple_stmt_type_declaration:
			simple_stmt->simple_stmt_type = simple_stmt_type_declaration;
			simple_stmt->simple_stmt_declaration = (Declaration*)value;
			break;
		case simple_stmt_type_assignment_stmt:
			simple_stmt->simple_stmt_type = simple_stmt_type_assignment_stmt;
			simple_stmt->simple_stmt_assignment_stmt = (AssignmentStmt*)value;
			break;
		case simple_stmt_type_import_stmt:
			simple_stmt->simple_stmt_type = simple_stmt_type_import_stmt;
			simple_stmt->simple_stmt_import_stmt = (ImportStmt*)value;
			break;
		case simple_stmt_type_if_stmt_simple:
			simple_stmt->simple_stmt_type = simple_stmt_type_if_stmt_simple;
			simple_stmt->simple_stmt_if_stmt_simple = (IfStmtSimple*)value;
			break;
		case simple_stmt_type_func_declaration:
			simple_stmt->simple_stmt_type = simple_stmt_type_func_declaration;
			simple_stmt->simple_stmt_func_declaration = (FuncDec*)value;
			break;
		case simple_stmt_type_decorator:
			simple_stmt->simple_stmt_type = simple_stmt_type_decorator;
			simple_stmt->simple_stmt_decorator = (Decorator*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	return simple_stmt;
}


//===========================================================================
// createSimpleStmtList() - construct an AST node of type SimpleStmtList.
//===========================================================================
SimpleStmtList* createSimpleStmtList(SimpleStmt *simple_stmt, SimpleStmtList *parent_list) {
	SimpleStmtList *simple_stmt_list = MALLOC(SimpleStmtList);
	simple_stmt_list->simple_stmt = simple_stmt;
	simple_stmt_list->next = 0;

	if(parent_list) {
		parent_list->next = simple_stmt_list;
		return parent_list;
	} else {
		return simple_stmt_list;
	}
}


//===========================================================================
// createStmt() - construct an AST node of type Stmt.
//===========================================================================
Stmt* createStmt(int type, void* value) {
	Stmt *stmt = MALLOC(Stmt);

	switch(type) {
		case stmt_type_simple_stmt_list:
			stmt->stmt_type = stmt_type_simple_stmt_list;
			stmt->stmt_simple_stmt_list = (SimpleStmtList*)value;
			break;
		case stmt_type_compound_stmt:
			stmt->stmt_type = stmt_type_compound_stmt;
			stmt->stmt_compound_stmt = (CompoundStmt*)value;
			break;
		case stmt_type_control_simple_stmt:
			stmt->stmt_type = stmt_type_control_simple_stmt;
			stmt->stmt_control_simple_stmt = (ControlSimpleStmt*)value;
		default:
			AST_ERROR();
			break;
	}

	return stmt;
}


//===========================================================================
// createStmtGroup() - construct an AST node of type StmtGroup.
//===========================================================================
StmtGroup* createStmtGroup(Stmt *stmt, StmtGroup *parent_group) {
	StmtGroup *stmt_group = MALLOC(StmtGroup);
	stmt_group->stmt = stmt;
	stmt_group->next = 0;

	if(parent_group) {
		parent_group->next = stmt_group;
		return parent_group;
	} else {
		return stmt_group;
	}
}


//===========================================================================
// createSuite() - construct an AST node of type Suite.
//===========================================================================
Suite* createSuite(StmtGroup *stmt_group) {
	Suite *suite = MALLOC(Suite);
	suite->stmt_group = stmt_group;
	return suite;
}