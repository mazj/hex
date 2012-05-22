#include "assert.h"
#include "ast.h"
#include "map.h"
#include "memory.h"

static int
_is_expr_list_identifier_list(ExprList* expr_list)
{
	HEX_ASSERT(expr_list);

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
	HEX_ASSERT(type_qualifier_list);

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

static int
_check_parameter_list(ParameterList *paramlist)
{
	HEX_ASSERT(paramlist);

	int endOfTypedParameter = 0;

	Map map;

	while(paramlist) {
		Parameter* param = paramlist->parameter;

		HEX_ASSERT(param);

		if(param->type_qualifier_list) {
			if(endOfTypedParameter) {
				return 0;
			}

			if(!_check_type_qualifier_list(
				param->type_qualifier_list)) {
				return 0;
			}
		} else {
			endOfTypedParameter = 1;
		}

		void* v;

		v = map_find(&map, param->param_name, strcmp);

		if(!v) {
			map_insert(&map, param->param_name, 1, strcmp);
		} else {
			// duplicate parameter name
			return 0;
		}

		paramlist = paramlist->next;
	}

	return 1;
}

static int
_check_assignment_list(AssignmentList *assigmentlist)
{
	HEX_ASSERT(assigmentlist);

	while(assigmentlist) {
		Assignment *assignment = assigmentlist->assignment;

		HEX_ASSERT(assignment);

		if(assignment->assignment_type == assignment_type_expr) {
			Expr *expr = assignment->assignment_expr;

			HEX_ASSERT(expr);

			// TODO: check expr...
		}

		assigmentlist = assigmentlist->next;
	}

	return 1;
}