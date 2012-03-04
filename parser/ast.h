/* Abstract Syntax Tree */

#ifndef _AST_H_
#define _AST_H_

#include <string.h>

/***********************************************************************
 *  Expression definitions
 ***********************************************************************/

typedef struct HexExpr Expr;

/*
 * Literal
 */
typedef struct HexLiteral {
    enum {
        literal_type_char,          /* character literal */
        literal_type_string,        /* string literal */
        literal_type_integer,       /* integer literal */
        literal_type_float,         /* floating number literal */
    } literal_type;
    union {
        char literal_char;          /* character literal */
        char* literal_string;       /* string literal */
        int literal_integer;        /* integer literal */
        double literal_float;       /* floating number literal */
    };
} Literal;


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


/*
 * Const expression
 */
typedef ConditionalExpr ConstExpr;


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


/*
 * Type qualifier list
 */
typedef struct HexTypeQualifierList {
    TypeQualifier *type_qualifier;
    struct HexTypeQualifierList *type_qualifier_list;
} TypeQualifierList;


/*
 * Direct declarator
 */
typedef struct HexDirectDeclarator {
    enum {
        declarator_identifier_type,      /* corresponds to IDENTIFIER */
        declarator_const_index_type,     /* corresponds to direct_declarator '[' const_expr ']' */
        declarator_empty_index_type      /* corresponds to direct_declarator '[' ']' */
    } type;
    union {
        char *identifier;
        struct { struct DirectDeclarator* declarator; ConstExpr* const_expr;} const_index_declarator;
        struct { struct DirectDeclarator* declarator;} empty_index_declarator;
    };
} DirectDeclarator;


/*
 * Declarator
 */
typedef DirectDeclarator Declarator;


/*
 * Init declarator list
 */
typedef struct HexInitDeclaratorList {
    Declarator **declarators;
    size_t declarator_count;
} InitDeclaratorList;


/*
 * Declaration specifier
 */
typedef struct HexDeclarationSpecifiers {
    StorageClassSpecifier *storage_class_specifier;
    TypeSpecifier *type_specifier;
    struct HexDeclarationSpecifiers *declaration_specifiers;
} DeclarationSpecifiers;


/*
 *  Declaration
 */
typedef struct HexDeclaration {
    DeclarationSpecifiers *declaration_specifiers;
    size_t specifier_count;
    InitDeclaratorList *declarator_list;
} Declaration;


/*
 * Identifier list
 */
typedef struct HexIdentifierList {
    char* identifier;
    struct HexIdentifierList *identifier_list;
} IdentifierList;


/***********************************************************************
 *  Parameter definitions
 ***********************************************************************/

/*
 * Parameter declaration
 */
typedef struct HexParameterDeclaration {
    enum {
        param_declaration_type_simple,  /* single identifier parameter */
        param_declaration_type_complex  /* other types of param with optional declaration specifiers. */
    } type;
    union {
        char *identifier;
        struct {
            DeclarationSpecifiers *declaration_specifier;
            Declarator *declarator;
        };
    };
} ParameterDeclaration;


/*
 * Parameter list
 */
typedef struct HexParameterList {
    ParameterDeclaration *param_declaration;
    struct HexParameterList *next;
} ParameterList;


/*
 * Parameter type list
 */
typedef struct HexParameterTypeList {
    ParameterList *param_list;
    int is_varadic;             /* whether parameter list has elipsis at the end. */
} ParameterTypeList;


/***********************************************************************
 *  Initializer definitions
 ***********************************************************************/

/*
 * Data struct typedefs
 */
typedef struct HexListInitializerList ListInitializerList;
typedef struct HexArrayInitializerList ArrayInitializerList;
typedef struct HexTupleInitializerList TupleInitializerList;
typedef struct HexStructInitializerList StructInitializerList;
typedef struct HexSetInitializerList SetInitializerList;
typedef struct HexMapInitializerList MapInitializerList;
typedef struct HexMultimapInitializerList MultimapInitializerList;


/*
 * Initializer
 */
typedef struct HexInitializer {
    enum {
        initializer_type_assign_expr,                           /* assignment expression initializer */
        initializer_type_list,                                  /* list initializer */
        initializer_type_array,                                 /* array initializer */
        initializer_type_tuple,                                 /* tuple initializer */
        initializer_type_struct,                                /* struct initializer */
        initializer_type_set,                                   /* set initializer */
        initializer_type_map,                                   /* map initializer */
        initializer_type_multimap                               /* multimap initializer */
    } initializer_type;
    union {
        AssignmentExpr *assignment_expr;                        /* assignment expression initializer */
        ListInitializerList *list_initializer_list;             /* list initializer */
        ArrayInitializerList *array_initializer_list;           /* array initializer */
        TupleInitializerList *tuple_initializer_list;           /* tuple initializer */
        StructInitializerList *struct_initializer_list;         /* struct initializer */
        SetInitializerList *set_initialier_list;                /* set initializer */
        MapInitializerList *map_initializer_list;               /* map initializer */
        MultimapInitializerList *multimap_initializer_list;     /* multimap initializer */
    };
} Initializer;


/*
 *  List initializer list 
 */
struct ListInitializerList {
    Initializer *initializer;
    ListInitializerList *list_initializer_list;
};


/*
 * Array initializer list
 */
struct ArrayInitializerList {
    Initializer *initializer;
    ArrayInitializerList *array_initializer_list;
};


/*
 * Tuple initializer list
 */
struct TupleInitializerList {
    Initializer *initializer;
    TupleInitializerList *tuple_initializer_list;
};


/*
 * Struct initializer list
 */
struct StructInitializerList {
    enum {
        struct_value_type_literal,      /* if prop value is literal */
        struct_value_type_initializer   /* if prop value is initializer */
    } value_type;
    union {
        Literal *struct_value_literal;
        Initializer *initializer;
    };
    StructInitializerList *struct_initializer_list;
};


/*
 * Set initializer list
 */
struct SetInitializerList {
    Initializer *initializer;
    SetInitializerList *set_initializer_list;
};


/*
 * Map initializer list
 */
struct MapInitializerList {
    Literal *key;
    Initializer *value;
    MapInitializerList *map_initializer_list;
};


/*
 * Multimap initializer list
 */
struct MultimapInitializerList {
    Literal *key;
    MapInitializerList *values;
    MultimapInitializerList *multimap_initializer_list;
};


/***********************************************************************
 *  Statement definitions
 ***********************************************************************/


/*
 * Statement
 */
typedef struct HexStmt Stmt;


/*
 * Statement list
 */
typedef struct HexStmtList {
    Stmt *stmt;
    struct HexStmtList *next;
} StmtList;


/*
 * Expression statement
 */
typedef struct HexExprStmt {
    Expr *expr;
} ExprStmt;


/*
 * Elif statement
 */
typedef struct HexElifStmt {
    Expr *elif_expr;
    Stmt *elif_stmt;
    struct HexElifStmt *next_elif_stmt;
} ElifStmt;


/*
 * Else statement
 */
typedef struct HexElseStmt {
    Stmt *else_stmt;
} ElseStmt;


/*
 * If statement
 */
typedef struct HexIfStmt {
    Expr *if_expr;
    ElifStmt *elif_stmt;
    ElseStmt *else_stmt;
} IfStmt;


/*
 * While statement
 */
typedef struct HexWhileStmt {
    Expr *while_expr;
    Stmt *while_stmt;
} WhileStmt;


/*
 * Do-while statement
 */
typedef struct HexDoWhileStmt {
    Stmt *dowhile_stmt;
    Expr *dowhile_expr;
} DoWhileStmt;


/*
 * Try statement
 */
typedef struct HexTryStmt {
    Expr *try_expr;
    Expr *catch_expr;
    Expr *finally_expr;
} TryStmt;


/*
 * Return statement
 */
typedef struct HexReturnStmt {
    Expr *return_expr;
} ReturnStmt;


/*
 * Jump statement
 */
typedef struct HexJumpStmt {
    enum {
        jump_stmt_type_continue,        /* continue statement */
        jump_stmt_type_break,           /* break statement */
        jump_stmt_type_return           /* return statement */
    } jump_stmt_type;
    union {
        ReturnStmt *return_stmt;        /* return statement */
    };
} JumpStmt;


#endif // _AST_H_