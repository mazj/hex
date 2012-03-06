/* Abstract Syntax Tree */

#include "ast.h"


//===========================================================================
// createLiteral() - construct an AST node of type Literal.
//===========================================================================
Literal* createLiteral(int type, void* value) {
	Literal* literal = HEX_MALLOC(Literal);
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
