/* Abstract Syntax Tree */

#include "ast3.h"


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
			postfix_expr->postfix_expr_accessor_expr->expr = (char*)value1;
			postfix_expr->postfix_expr_accessor_expr->accessor = (char*)value2;
			break;
		case postfix_expr_type_invocation:
			postfix_expr->postfix_expr_type = postfix_expr_type_invocation;
			postfix_expr->postfix_expr_invocation_expr = (char*)value1;
		case postfix_expr_type_invocation_with_args:
			postfix_expr->postfix_expr_type = postfix_expr_type_invocation_with_args;
			postfix_expr->postfix_expr_invocation_with_args_expr = MALLOC(PostfixInvocationWithArgsExpr);
			postfix_expr->postfix_expr_invocation_with_args_expr->expr = (Expr*)value1;
			postfix_expr->postfix_expr_invocation_with_args_expr->arg_list = (ExprList*)value2;
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

	Expr* expr = createExpr(expr_type_unary, unary_expr);

	return expr;
}


//===========================================================================
// createCastExpr() - construct an AST node of type CastExpr.
//===========================================================================
Expr* createCastExpr(int type, void* value) {
	CastExpr *cast_expr = MALLOC(CastExpr);

	switch(type) {
		case cast_expr_type_type_specifier:
			cast_expr->cast_expr_type = cast_expr_type_type_specifier;
			cast_expr->type_specifier = DEREF_VOID(int, value);
			break;
		case cast_expr_type_custom_type:
			cast_expr->cast_expr_type = cast_expr_type_custom_type;
			cast_expr->identifier = (char*)value;
			break;
		default:
			AST_ERROR();
			break;
	}

	Expr* expr = createExpr(expr_type_cast, cast_expr);

	return expr;
}


//===========================================================================
// createMultiplcativeExpr() - construct an AST node of type MultiplcativeExpr.
//===========================================================================
Expr* createMultiplicativeExpr(int type, Expr *left_expr, Expr *right_expr); {
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

	Expr *expr = createExpr(expr_type_arithmetic_expr, arithmetic_expr);

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

	Expr *expr = createExpr(expr_type_arithmetic_expr, arithmetic_expr);

	return expr;
}


//===========================================================================
// createArithmeticExpr() - construct an AST node of type ArithmeticExpr.
//===========================================================================
Expr* createArithmeticExpr(int type, void *expr) {
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

	Expr* expr = createExpr(expr_type_arithmetic, arithmetic_expr);

	return expr;
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
// createLambdaExpr() - construct an AST node of type LambdaExpr.
//===========================================================================
Expr* createLambdaExpr(ParameterList *param_list, Suite* lambda_suite) {
	LambdaExpr* lambda_expr = MALLOC(LambdaExpr);

	lambda_expr->lambda_param_list = param_list;
	lambda_expr->lambda_suite = lambda_suite;

	Expr *expr = createExpr(expr_type_lambda, lambda_expr);

	return expr;
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
		case expr_type_equality:
			expr->expr_type = expr_type_equality;
			EqualityExpr* equality_expr = (EqualityExpr*)value;
			expr->equality_expr = equality_expr;
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
		// case expr_type_assignment:
		// 	expr->expr_type = expr_type_assignment;
		// 	AssignmentExpr* assignment_expr = (AssignmentExpr*)value;
		// 	expr->assignment_expr = assignment_expr;
		// 	break;
		// case expr_type_const:
		// 	expr->expr_type = expr_type_const;
		// 	ConstExpr* const_expr = (ConstExpr*)value;
		// 	expr->const_expr = const_expr;
		// 	break;
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
    TypeSpecifier *type_specifier, char *custom_type, ExprList *expr_list, char *alias) {
	Declaration *declaration = MALLOC(Declaration);

	declaration->type_qualifier_list = type_qualifier_list;
	if(type_specifier)
		declaration->type_specifier = type_specifier;
	else
		declaration->custom_type = custom_type;

	declaration->expr_list = expr_list;
	declaration->alias = alias;

	return declaration;
}


//===========================================================================
// createParameterList() - construct an AST node of type ParameterList.
//===========================================================================
ParameterList *createParameterList(Declaration *declaration, ParameterList* parent_list) {
	ParameterList *param_list = MALLOC(ParameterList);
	param_list->param_declaration = declaration;
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
ArraytInitializer *createArrayInitializer(ExprList *expr_list) {
	ArraytInitializer *array_initializer = MALLOC(ArraytInitializer);
	array_initializer->expr_list = expr_list;
	return array_initializer;
}


//===========================================================================
// createTupleInitializer() - construct an AST node of type TupleInitializer.
//===========================================================================
TupleInitializer *createTupleInitializer(ExprList *expr_list) {
	TupletInitializer *tuple_initializer = MALLOC(TupleInitializer);
	tuple_initializer->expr_list = expr_list;
	return tuple_initializer;
}


//===========================================================================
// createStructInitializer() - construct an AST node of type StructInitializer.
//===========================================================================
StructInitializer *createTupleInitializer(AssignmentStmtList *assignment_stmt_list) {
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
	MapMultimapInitializerSingle map_initializer_single = MALLOC(MapMultimapInitializerSingle);
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
	MapMultimapInitializer *map_initializer = MALLO(MapMultimapInitializer);
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
			initializer->map_multimap_initialize = (MapMultimapInitializerList*)value;
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
Assignment* createAssignment(Expr *expr) {
	Assignment *assignment = MALLOC(Assignment);
	assignment->expr = expr;
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
		return parent_list
	} else {
		return assignment_list;
	}
}


//===========================================================================
// createAssignmentStmt() - construct an AST node of type AssignmentStmt.
//===========================================================================
AssignmentStmt* createAssignmentStmt(int type, void* value) {
	AssignmentStmt *assignment_stmt = MALLOC(AssignmentStmt);

	switch(assignment_stmt) {
		case assignment_stmt_type_declaration:
			assignment_stmt->assignment_stmt_type = assignment_stmt_type_declaration;
			assignment_stmt->assignment_stmt_declaration = (Declaration*)value;
			break;
		case assignment_stmt_type_expr_list:
			assignment_stmt->assignment_stmt_type = assignment_stmt_type_expr_list;
			assignment_stmt->assignment_stmt_expr_list = (ExprList*)value;
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
// createFuncDeclaration() - construct an AST node of type FuncDeclaration.
//===========================================================================
FuncDeclaration* createFuncDeclaration(TypeQualifierList *type_qualifier_list,
    int type_specifier, char *custom_return_type, char *func_name,
    ParameterList *parameter_list)
{
	FuncDeclaration *func_declaration = MALLOC(FuncDeclaration);
	func_declaration->return_type_qualifier_list = type_qualifier_list;
	if(type_specifier)
		func_declaration->return_type_specifier = type_specifier;
	else if(custom_return_type)
		func_declaration->custom_return_type = custom_return_type;
	func_declaration->func_name = func_name;
	func_declaration->parameter_list = parameter_list;

	return func_declaration;
}


//===========================================================================
// createFuncDefinition() - construct an AST node of type FuncDefinition.
//===========================================================================
FuncDefinition* createFuncDefinition(FuncDeclaration *func_declaration, Suite *func_suite) {
	FuncDefinition *func_def = MALLOC(FuncDefinition);
	func_def->func_declaration = func_declaration;
	func_def->func_suite = func_suite;

	return func_def;
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
RelativeImportStmt* createRelativeImportStmt(ModuleList *module_list, Module *module char *alias) {
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
// createElseStmt() - construct an AST node of type ElseStmt.
//===========================================================================
ElseStmt* createElseStmt(Suite *else_suite) {
	ElseStmt *else_stmt = MALLOC(else_stmt);
	else_stmt->else_suite = else_suite;
	return else_stmt;
}


//===========================================================================
// createIfStmt() - construct an AST node of type IfStmt.
//===========================================================================
IfStmt* createIfStmt(Expr *if_expr, Suite *if_suite, ElifGroup *elif_group, ElseStmt *else_stmt) {
	IfStmt *if_stmt = MALLOC(IfStmt);
	if_stmt->if_expr = if_expr;
	if_stmt->elif_group = elif_group;
	if_stmt->else_stmt = else_stmt;

	return if_stmt;
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
// createForStmt() - construct an AST node of type ForStmt.
//===========================================================================
ForStmt* createForStmt() {
	ForStmt *for_stmt = MALLOC(ForStmt);
	return for_stmt; 
}


//===========================================================================
// createCatchStmt() - construct an AST node of type CatchStmt.
//===========================================================================
CatchStmt* createCatchStmt(Declaration *declaration, char *catch_type,
    char *identifier, Suite *suite); {
	CatchStmt *catch_stmt = MALLOC(CatchStmt);

	catch_stmt->catch_declaration = declaration;
	catch_stmt->catch_type = catch_type;
	catch_stmt->catch_identifier = identifier;
	catch_stmt->catch_suite = suite;

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
		case compound_stmt_type_dowhile_stmt:
			compound_stmt->compound_stmt_type = compound_stmt_type_dowhile_stmt;
			compound_stmt->compount_stmt_dowhile_stmt = (DoWhileStmt*)value;
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
// createPassStmt() - construct an AST node of type PassStmt.
//===========================================================================
SimpleStmt* createSimpleStmt(int type, void* value) {
	SimpleStmt *simple_stmt = MALLOC(SimpleStmt);

	switch(type) {
		case simple_stmt_type_declaration:
			simple_stmt->simple_stmt_type = simple_stmt_type_declaration;
			simple_stmt->simple_stmt_declaration = (Declaration*)value;
			break;
		case simple_stmt_type_assignment_stmt_list:
			simple_stmt->simple_stmt_type = simple_stmt_type_assignment_stmt_list;
			simple_stmt->simple_stmt_assignment_stmt_list = (AssignmentList*)value;
			break;
		case simple_stmt_type_return_stmt:
			simple_stmt->simple_stmt_type = simple_stmt_type_return_stmt;
			simple_stmt->simple_stmt_return_stmt = (ReturnStmt*)value;
			break;
		case simple_stmt_type_break_stmt:
			simple_stmt->simple_stmt_type = simple_stmt_type_break_stmt;
			// simple_stmt->simple_stmt_break_stmt = (BreakStmt*)value;
			break;
		case simple_stmt_type_continue_stmt:
			simple_stmt->simple_stmt_type = simple_stmt_type_continue_stmt;
			simple_stmt->simple_stmt_continue_stmt = (ContinueStmt*)value;
			break;
		case simple_stmt_type_import_stmt:
			simple_stmt->simple_stmt_type = simple_stmt_type_import_stmt;
			simple_stmt->simple_stmt_import_stmt = (ImportStmt*)value;
			break;
		case simple_stmt_type_func_declaration:
			simple_stmt->simple_stmt_type = simple_stmt_type_func_declaration;
			simple_stmt->simple_stmt_type_func_declaration = (FuncDeclaration*)value;
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