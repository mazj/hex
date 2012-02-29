/* Abstract Syntax Tree */

#ifndef _AST_H_
#define _AST_H_

typedef struct HexExpr Expr;

typedef enum HexUnaryOp {a,b,c} UnaryOp; 

typedef struct HexPrimaryExpr {
	enum {id_expr, int_litr_expr, float_litr_expr, char_litr_expr, string_litr_expr} type;
	union {
		char* id;
		int int_litr;
		double float_litr;
		char char_litr;
		char* string_litr;
	} u;
} PrimaryExpr;

typedef struct HexPostfixExpr {
	enum {index, inc_or_dec_post} type;
	union {
		struct {Expr* expr; int index;} index_expr;
		struct {Expr* expr; int inc_or_dec;} inc_or_dec_expr;
	} u;

} PostfixExpr;

typedef struct HexUnaryExpr {
	enum {inc_or_dec_pre, unary_op, size_of} type;
	union {
		struct {Expr* expr; int inc_or_dec;} inc_or_dec_expr;
		struct {Expr* expr; UnaryOp unary_op;} unary_op_expr;
		Expr* sizeof_expr;
	} u;
} UnaryExpr;

typedef struct HexCastExpr {
	Expr* expr;
	char* cast_type;
} CastExpr;

struct HexExpr {
	enum {primary, postfix, unary, cast, arithmetic, logic, bitwise, lambda} type;
	union {
		PrimaryExpr primary_expr;
		PostfixExpr postfix_expr;
		UnaryExpr unary_expr;
		CastExpr cast_expr;
		Arithmetic arithmetic_expr;
		LogicExpr logic_expr;
		BitwiseExpr bitwise_expr;
		LambdaExpr lambda_expr;
	} u;
};

#endif // _AST_H_