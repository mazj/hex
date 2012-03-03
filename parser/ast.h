/* Abstract Syntax Tree */

#ifndef _AST_H_
#define _AST_H_

#include <string.h>

/***********************************************************************
 *  Expression definitions
 ***********************************************************************/

typedef struct HexExpr Expr;

/* Unary operator */
typedef enum HexUnaryOp {
    plus,
    minus,
    inc,
    dec,
    not_bitwise,
    not
} UnaryOp;

/* Assignment operator */
typedef enum HexAssignmentOp {
    assignop,               /* = */
    assignop_assign_new,    /* = new */
    assignop_lazy_new,      /* = lazy new */
    assign_mul,             /* *= */
    assign_div,             /* /= */
    assign_mod,             /* %= */
    assign_plus,            /* += */
    assign_minus,           /* -= */
    assign_shift_left,      /* <<= */
    assign_shift_right,     /* >>= */
    assign_bitwise_not,     /* != */
    assign_bitwise_and,     /* &= */
    assign_bitwise_or,      /* |= */
    assign_bitwise_xor      /* ^= */
} AssignmentOp; 


/* Arithmetic expression
 *
 * Types:
 *  id_expr: identifier
 *  int_litr_expr: integer literal
 *  float_litr_expr: floating number literal
 *  char_litr_expr: character literal
 *  string_litr_expr: string literal
 */
typedef struct HexPrimaryExpr {
    enum {id_expr, int_litr_expr, float_litr_expr, char_litr_expr, string_litr_expr} type;
    union {
        char* id;
        int int_litr;
        double float_litr;
        char char_litr;
        char* string_litr;
    };
} PrimaryExpr;


/* Postfix expression
 *
 * Types:
 *  index: index expression
 *  inc_or_dec_post: post increment or post decrement   '++' or '--'
 *
 * Syntax:
 *  expr[index]
 *  expr()
 *  expr(arg_expr_list)
 *  expr.idenfitier
 *  expr++
 *  expr--
 */
typedef struct HexPostfixExpr {
    enum {postfix_index, postfix_inc_or_dec} type;
    union {
        struct {Expr* expr; int index;} index_expr;
        struct {Expr* expr; int inc_or_dec;} inc_or_dec_expr;
    };
} PostfixExpr;


/* Unary expression
 *
 * Types:
 *
 *
 *
 * Syntax:
 *
 */
typedef struct HexUnaryExpr {
    enum {inc_or_dec_pre, unary_op, size_of} type;
    union {
        struct {Expr* expr; int inc_or_dec;} inc_or_dec_expr;
        struct {Expr* expr; UnaryOp unary_op;} unary_op_expr;
        Expr* sizeof_expr;
    };
} UnaryExpr;


/*  Cast expression 
 *  
 * Syntax:
 *  target_expr = (cast_type)expr
 */
typedef struct HexCastExpr {
    Expr* expr;
    char* cast_type;
} CastExpr;


/* Arithmetic expression
 *
 * Types:
 *  multiplicative: multiplication and division '*' or '/'
 *  additive: addition and subtraction          '+' or '-'
 *
 * Syntax:
 *  target_expr = left_expr [ * | - | * | / ] right_expr
 */
typedef struct HexArithmeticExpr {
    enum {multiplicative, additive} type;
    Expr* left_expr;
    Expr* right_expr;
} ArithmeticExpr;


/* Equality expression
 *
 * Types:
 *  eq: equal               '=='
 *  neq: not equal          "not"
 *  less: less than         '<'
 *  greater: greater than   '>'
 *  le: less or equal       "<="
 *  ge: greater or equal    ">="
 *
 * Syntax:
 *  target_expr = left_expr [ == | not | < | > | <= | >= ] right_expr
 */
typedef struct HexEqualityExpr {
    enum {eq, neq, less, greater, le, ge} type;
    Expr* left_expr;
    Expr* right_expr;
} EqualityExpr;


/* Logic expression 
 *  
 * Types:
 *  logic_and: logic and    "and"
 *  logic_or:  logic or     "or"
 *
 * Syntax:
 *  target_expr = left_expr [ and | or ] right_expr
 */
typedef struct HexLogicExpr {
    enum {logic_and, logic_or} type;
    Expr* left_expr;
    Expr* right_expr;
} LogicExpr;


/* Bitwise expression 
 *  
 * Types:
 *  shift_left: left bitwise shift      "<<"
 *  shift_right: right bitwise shift    ">>"
 *  bitwise_and: bitwise AND            '&'
 *  bitwise_or: bitwise OR              '|'
 *  bitwise_xor: bitwise XOR            '^'
 *
 * Syntax:
 *  target_expr = left_expr [ >> | << | & | | | ^ ] right_expr
 */
typedef struct HexBitwiseExpr {
    enum {shift_left, shift_right, bitwise_and, bitwise_or, bitwise_xor} type;
    Expr* left_expr;
    Expr* right_expr;
} BitwiseExpr;


/* Conditional expression 
 *  
 * Syntax:
 *  target_expr = consequent if predicate else alternative
 */
typedef struct HexConditionalExpr {
    Expr* consequent;
    Expr* predicate;
    Expr* alternative;
} ConditionalExpr;


/* Assignment expression 
 *  
 * Syntax:
 *  target_expr [ = | new | lazy new | *= | /= | += | -= | <<= | >>= | != | &= | |= | ^= ] expr
 */
typedef struct HexAssignmentExpr {
    AssignmentOp op;
    Expr* left_expr;
    Expr* right_expr;
} AssignmentExpr;


/*
 * Argument expression
 *
 * Syntax:
 *  arg = assignmentExpr()
 *  arg = assignmentExpr() as alias
 */
typedef struct HexArgExpr {
    AssignmentExpr* assign_expr;    /* Assignment expression */
    char *alias;                    /* The identifier alias for that assignment expression. */
} ArgExpr;


/*
 * Argument expression list
 *
 *  A list of argument expressions.
 *
 * Syntax:
 *  (arg1, arg2 = assignmentExpr2(), arg3 = assignmentExpr3() as alias) 
 */
typedef struct HexArgExprList {                  
    size_t arg_count;               /* Number of argument expressions. */
    ArgExpr **next_arg;             /* An array of argument expressions. */
} ArgExprList;


/* Lambda expression 
 *  
 * Syntax:
 *  target_expr = (arg_init_list) => expr
 */
typedef struct HexLambdaExpr {
    ArgExprList* arg_list;
    Expr* expr;
} LambdaExpr;


/*
 * Expression.
 */
struct HexExpr {
    enum {primary, postfix, unary, cast, arithmetic, logic, bitwise, lambda} type;
    union {
        PrimaryExpr primary_expr;
        PostfixExpr postfix_expr;
        UnaryExpr unary_expr;
        CastExpr cast_expr;
        ArithmeticExpr arithmetic_expr;
        EqualityExpr equality_expr;
        LogicExpr logic_expr;
        BitwiseExpr bitwise_expr;
        ConditionalExpr conditional_expr;
        LambdaExpr lambda_expr;
    };
};


/***********************************************************************
 *  Declaration definitions
 ***********************************************************************/

/*
 * Storage class specifier
 */
typedef enum HexStorageClassSpecifier {
    storage_class_specifier_static  /* storage class specifier static */
} StorageClassSpecifier;


/*
 * Type specifier
 */
typedef enum HexTypeSpecifier {
    type_specifier_char,            /* type char */
    type_specifier_short,           /* type short */
    type_specifier_int,             /* type int */
    type_specifier_long,            /* type long */
    type_specifier_float,           /* type float */
    type_specifier_double,          /* type double */
    type_specifier_uchar,           /* type uchar */
    type_specifier_ushort,          /* type ushort */
    type_specifier_uint,            /* type uint */
    type_specifier_ulong,           /* type ulong */
    type_specifier_identifier       /* custom type */
} TypeSpecifier;

/*
 * Type qualifier
 */
typedef enum HexTypeQualifier {
    type_qualifier_const,           /* qualifier const */
    type_qualifier_volatile         /* qualifier volatile */
} TypeQualifier;

#endif // _AST_H_