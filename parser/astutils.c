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