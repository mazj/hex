#include <assert.h>

static int
_is_expr_list_identifier_list(ExprList* expr_list)
{
	if(!expr_list) {
		return 0;
	}

	while(expr_list) {
		Expr *expr = expr_list->expr;

		if(expr->expr_type == expr_type_primary) {
			PrimaryExpr *primary = expr->primary_expr;
			if(primary && primary->primary_expr_type
				!= primary_expr_type_identifier) {
				return 0;
			}
		}

		expr_list = expr_list->next;
	}

	return 1;
}

static int
_check_type_qualifier_list(TypeQualifierList *type_qualifier_list)
{
	assert(type_qualifier_list);

	int type_qualifier_const_count = 0;
	int type_qualifier_volatile_count = 0;
	int type_qualifier_static_count = 0;

	while(type_qualifier_list) {
		int qualifier = type_qualifier_list->type_qualifier;

		if(qualifier == type_qualifier_const)
			type_qualifier_const_count++;
		else if(qualifier == type_qualifier_volatile)
			type_qualifier_volatile_count++;
		else
			type_qualifier_static_count++;

		type_qualifier_list = type_qualifier_list->next;
	}

	if(type_qualifier_const_count > 1)
		return 0;
	else if(type_qualifier_volatile_count > 1)
		return 0;
	else if(type_qualifier_static_count > 1)
		return 0;
	else
		return 1;
}