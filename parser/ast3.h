/* Abstract Syntax Tree */

#ifndef _AST_H_
#define _AST_H_

#include <string.h>
#include "utils.h"


#define AST_ERROR()


//===========================================================================
// global typedefs
//===========================================================================
/*
 * Expression
 */
typedef struct HexExpr Expr;


/*
 * Expr list
 */
typedef struct HexExprList ExprList;


/*
 * Lambda expression
 */
typedef struct HexLambdaExpr LambdaExpr;


/*
 * Simple statement list 
 */
typedef struct HexSimpleStmtList SimpleStmtList;


/*
 * Statement
 */
typedef struct HexStmt Stmt;


/*
 * Compound statement
 */
typedef struct HexCompoundStmt CompoundStmt;


/*
 * Suite
 */
typedef struct HexSuite Suite;
//===========================================================================
// global typedefs
//===========================================================================

/*
 * Integer
 */
typedef struct HexInteger {
    enum {
        integer_type_decimal,       /* decimal integer */
        integer_type_binary,        /* binary integer */
        integer_type_octal,         /* octal decimal integer */
        integer_type_hexadecimal    /* hexa decimal integer */
    } integer_type;
    int is_signed;                  /* integer signness */
    int integer;                    /* underlying integer number */
} Integer;

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


//===========================================================================
// createLiteral() - construct an AST node of type Literal.
//===========================================================================
Literal* createLiteral(int type, void* value);


/*
 * Primary expression
 */
typedef struct HexPrimaryExpr {
    enum {
        primary_expr_type_identifier,       /* identifier */
        primary_expr_type_literal,          /* literal */
    } primary_expr_type;
    union {
        char *primary_expr_identifier;      /* identifier */
        Literal* primary_expr_literal;      /* literal */
    };
} PrimaryExpr;


//===========================================================================
// createPrimaryExpr() - construct an AST node of type PrimaryExpr.
//===========================================================================
Expr* createPrimaryExpr(int type, void* value);


/* 
 * Postfix expression
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
typedef struct HexPostfixIndexExpr {Expr *expr; Expr *index_expr;} PostfixIndexExpr;
typedef struct HexPostfixAccessorExpr {char *caller; char *accessor;} PostfixAccessorExpr;
typedef struct HexPostfixInvocationWithArgsExpr {Expr *expr; ExprList *arg_list;} PostfixInvocationWithArgsExpr;
typedef struct HexPostfixExpr {
    enum {
        postfix_expr_type_index,                    /* index */
        postfix_expr_type_postfix_inc,              /* increment */
        postfix_expr_type_postfix_dec,              /* decrement */
        postfix_expr_type_accessor,                 /* accessor */
        postfix_expr_type_invocation,               /* function invocation */
        postfix_expr_type_invocation_with_args      /* function invocation with args */
    } postfix_expr_type;
    union {
        PostfixIndexExpr *postfix_expr_index_expr;                              /* index */
        Expr *postfix_expr_postfix_inc_expr;                                    /* increment */
        Expr *postfix_expr_postfix_dec_expr;                                    /* decrement */            
        PostfixAccessorExpr *postfix_expr_accessor_expr;                        /* accessor */
        char *postfix_expr_invocation_expr;                                     /* function invocation */
        PostfixInvocationWithArgsExpr *postfix_expr_invocation_with_args_expr;  /* function invocation with args */
    };
} PostfixExpr;


//===========================================================================
// createPostfixExpr() - construct an AST node of type PostfixExpr.
//===========================================================================
Expr* createPostfixExpr(int type, void* value1, void* value2);


/*
 * Unary expression
 */
typedef struct HexUnaryExpr {
    enum {
        unary_expr_type_prefix_inc,             /* prefix increment */
        unary_expr_type_prefix_dec,             /* prefix decrement */
        unary_expr_type_unary_minus,            /* prefix unary minus */
        unary_expr_type_not,                    /* prefix unary not */
        unary_expr_type_bitwise_not             /* unary bitwise not */
    } unary_expr_type;
    union {
        Expr *unary_expr_prefix_inc_expr;       /* prefix increment */
        Expr *unary_expr_prefix_dec_expr;       /* prefix decrement */
        Expr *unary_expr_unary_expr;            /* unary minus */
        Expr *unary_expr_not;                   /* unary not */
        Expr *unary_expr_bitwise_not;           /* unary bitwise not */
    };
} UnaryExpr;


//===========================================================================
// createUnaryExpr() - construct an AST node of type UnaryExpr.
//===========================================================================
Expr* createUnaryExpr(int type, Expr *expr);


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
    type_specifier_ulong            /* type ulong */
} TypeSpecifier;


/*
 * Cast expression 
 *
 * Syntax:
 *  target_expr = (cast_type)expr
 */
typedef struct HexCastExpr {
    Expr* cast_expr;
    enum {
        cast_expr_type_type_specifier,
        cast_expr_type_custom_type
    } cast_expr_type;
    union {
        int type_specifier;
        char* identifier;
    };
} CastExpr;


//===========================================================================
// createCastExpr() - construct an AST node of type CastExpr.
//===========================================================================
Expr* createCastExpr(int type, void* value);


/*
 * Multiplcative expression
 */
typedef struct HexMultiplicativeExpr {
    enum {
        multiplicative_expr_type_mul,
        multiplicative_expr_type_div,
        multiplicative_expr_type_mod
    } multi_expr_type;
    Expr* left_expr;
    Expr* right_expr;
} MultiplicativeExpr;


//===========================================================================
// createMultiplcativeExpr() - construct an AST node of type MultiplcativeExpr.
//===========================================================================
Expr* createMultiplicativeExpr(int type, Expr *left_expr, Expr *right_expr);


/*
 * Additive expression
 */
typedef struct HexAdditiveExpr {
    enum {
        additive_expr_type_plus,
        additive_expr_type_minus
    } additive_expr_type;
    Expr* left_expr;
    Expr* right_expr;
} AdditiveExpr;


//===========================================================================
// createAdditiveExpr() - construct an AST node of type AdditiveExpr.
//===========================================================================
Expr* createAdditiveExpr(int type, Expr *left_expr, Expr *right_expr);


/*
 * Arithmetic expression
 *
 * Types:
 *  multiplicative: multiplication, division and modulus:   '*' and '/' and '%'
 *  additive: addition and subtraction:                     '+' and '-'
 *
 * Syntax:
 *  target_expr = left_expr [ * | / | % | + | - ] right_expr
 */
typedef struct HexArithmeticExpr {
    enum {
        arithmetic_expr_type_multiplicative,
        arithmetic_expr_type_additive
    } arithmetic_expr_type;
    union {
        MultiplicativeExpr *arithmetic_expr_multiplicative_expr;
        AdditiveExpr *arithmetic_expr_additive_expr;
    };
} ArithmeticExpr;


//===========================================================================
// createArithmeticExpr() - construct an AST node of type ArithmeticExpr.
//===========================================================================
Expr* createArithmeticExpr(int type, void *expr);


/*
 * Equality expression
 *
 * Types:
 *  eq: equal               '=='
 *  neq: not equal          "!="
 *  less: less than         '<'
 *  greater: greater than   '>'
 *  le: less or equal       "<="
 *  ge: greater or equal    ">="
 *
 * Syntax:
 *  target_expr = left_expr [ == | not | < | > | <= | >= ] right_expr
 */
typedef struct HexEqualityExpr {
    enum {
        equality_expr_type_eq,          /* == */
        equality_expr_type_neq,         /* != */
        equality_expr_type_less,        /* < */
        equality_expr_type_greater,     /* > */
        equality_expr_type_le,          /* <= */
        equality_expr_type_ge           /* >= */
    } equality_expr_type;
    Expr* left_expr;
    Expr* right_expr;
} EqualityExpr;


//===========================================================================
// createEqualityExpr() - construct an AST node of type EqualityExpr.
//===========================================================================
Expr* createEqualityExpr(int type, Expr *left_expr, Expr *right_expr);


/*
 * Logic expression 
 *  
 * Types:
 *  logic_and: logic and    "and"
 *  logic_or:  logic or     "or"
 *
 * Syntax:
 *  target_expr = left_expr [ and | or ] right_expr
 */
typedef struct HexLogicExpr {
    enum {
        logic_expr_type_logic_and,      /* and */
        logic_expr_type_logic_or        /* or */
    } logic_expr_type;
    Expr* left_expr;
    Expr* right_expr;
} LogicExpr;


//===========================================================================
// createLogicExpr() - construct an AST node of type LogicExpr.
//===========================================================================
Expr* createLogicExpr(int type, Expr *left_expr, Expr *right_expr);


/*
 * Bitwise expression 
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
    enum {
        bitwise_expr_type_shift_left,       /* << */
        bitwise_expr_type_shift_right,      /* >> */
        bitwise_expr_type_bitwise_and,      /* & */
        bitwise_expr_type_bitwise_or,       /* | */
        bitwise_expr_type_bitwise_xor       /* ^ */
    } bitwise_expr_type;
    Expr* left_expr;
    Expr* right_expr;
} BitwiseExpr;


//===========================================================================
// createBitwiseExpr() - construct an AST node of type BitwiseExpr.
//===========================================================================
Expr* createBitwiseExpr(int type, Expr *left_expr, Expr *right_expr);


/*
 * Conditional expression 
 *  
 * Syntax:
 *  target_expr = if predicate then alternative else consequent
 */
typedef struct HexConditionalExpr {
    Expr* predicate_expr;
    Expr* alternative_expr;
    Expr* consequent_expr;
} ConditionalExpr;


//===========================================================================
// createConditionalExpr() - construct an AST node of type ConditionalExpr.
//===========================================================================
Expr* createConditionalExpr(Expr *predicate_expr, Expr *alternative_expr, Expr *consequent_expr);


/*
 * Range expression
 *
 * A range expression uses a beginning and an end expression
 * to denote a range, using the ellipsis operator.
 */
typedef struct HexRangeExpr {
    Expr *left_expr;
    Expr *right_expr;
} RangeExpr;


//===========================================================================
// createRangeExpr() - construct an AST node of type RangeExpr.
//===========================================================================
Expr* createRangeExpr(Expr *left_expr, Expr *right_expr);


/*
 * Lock/unlock expression
 */
typedef struct HexLockExpr {
    int is_lock;
    Expr *expr;
} LockExpr;


//===========================================================================
// createLockExpr() - construct an AST node of type LockExpr.
//===========================================================================
Expr* createLockExpr(int is_lock, Expr *expr);


/*
 * Weakref expression
 */
typedef struct HexWeakrefExpr {
    Expr *expr;
} WeakrefExpr;


//===========================================================================
// createWeakref() - construct an AST node of type WeakrefExpr.
//===========================================================================
Expr* createWeakref(Expr *expr);


/*
 * HEX expression
 */
struct HexExpr {
    enum {
        expr_type_primary,
        expr_type_postfix,
        expr_type_unary,
        expr_type_cast,
        expr_type_multilicative,
        expr_type_arithmetic,
        expr_type_equality,
        expr_type_logic,
        expr_type_bitwise,
        expr_type_conditional,
        expr_type_range,
        expr_type_lock,
        expr_type_weakref
    } expr_type;
    union {
        PrimaryExpr *primary_expr;
        PostfixExpr *postfix_expr;
        UnaryExpr *unary_expr;
        CastExpr *cast_expr;
        ArithmeticExpr *arithmetic_expr;
        EqualityExpr *equality_expr;
        LogicExpr *logic_expr;
        BitwiseExpr *bitwise_expr;
        ConditionalExpr *conditional_expr;
        RangeExpr *range_expr;
        LockExpr *lock_expr;
        WeakrefExpr *weakref_expr;
    };
};


//===========================================================================
// createExpr() - construct an AST node of type Expr.
//===========================================================================
Expr* createExpr(int type, void* value);


/*
 * Assignment operator
 */
typedef enum HexAssignmentOp {
    assign_op,                  /* = */
    assign_op_new,              /* = new */
    assign_op_lazy_new,         /* = lazy new */
    assign_op_mul,              /* *= */
    assign_op_div,              /* /= */
    assign_op_mod,              /* %= */
    assign_op_plus,             /* += */
    assign_op_minus,            /* -= */
    assign_op_shift_left,       /* <<= */
    assign_op_shift_right,      /* >>= */
    assign_op_bitwise_not,      /* != */
    assign_op_bitwise_and,      /* &= */
    assign_op_bitwise_or,       /* |= */
    assign_op_bitwise_xor       /* ^= */
} AssignmentOp;


/*
 * Expression list
 */
struct HexExprList {
    Expr *expr;
    struct HexExprList *next;
};


//===========================================================================
// createExprList() - construct an AST node of type ExprList.
//===========================================================================
ExprList *createExprList(Expr* expr, ExprList* parent_list);


/***********************************************************************
 *  Declaration definitions
 ***********************************************************************/


/*
 * Type qualifier
 */
typedef enum HexTypeQualifier {
    type_qualifier_const,           /* qualifier const */
    type_qualifier_volatile,        /* qualifier volatile */
    type_qualifier_static           /* qualifier static */
} TypeQualifier;


/*
 * Type qualifier list
 */
typedef struct HexTypeQualifierList {
    TypeQualifier type_qualifier;
    struct HexTypeQualifierList *next;
} TypeQualifierList;


//===========================================================================
// createTypeQualifierList() - construct an AST node of type TypeQualifierList.
//===========================================================================
TypeQualifierList* createTypeQualifierList(TypeQualifier qualifier, TypeQualifierList* parent_list);


/*
 *  Declaration
 */
typedef struct HexDeclaration {
    TypeQualifierList *type_qualifier_list;
    TypeSpecifier *type_specifier;
    char *custom_type;
    ExprList *expr_list;
    char *alias;
} Declaration;


//===========================================================================
// createDeclaration() - construct an AST node of type Declaration.
//===========================================================================
Declaration* createDeclaration(TypeQualifierList *type_qualifier_list,
    TypeSpecifier *type_specifier, char *custom_type, ExprList *expr_list, char *alias);


/***********************************************************************
 *  Parameter definitions
 ***********************************************************************/


/*
 *  Declaration
 */
typedef struct HexParameter {
    TypeQualifierList *type_qualifier_list;
    TypeSpecifier *type_specifier;
    char *parameter_name;
    char *custom_type;
    char *alias;
    int is_ref;
} Parameter;


/*
 * Parameter list
 */
typedef struct HexParameterList {
    Declaration *param_declaration;
    struct HexParameterList *next;
} ParameterList;


//===========================================================================
// createParameterList() - construct an AST node of type ParameterList.
//===========================================================================
ParameterList* createParameterList(Parameter *parameter, ParameterList* parent_list);


/***********************************************************************
 *  Initializer definitions
 ***********************************************************************/


/*
 * List initializer
 */
typedef struct HexListInitializer {
    ExprList *expr_list;
} ListInitializer;


//===========================================================================
// createListInitializer() - construct an AST node of type ListInitializer.
//===========================================================================
ListInitializer* createListInitializer(ExprList *expr_list);


/*
 * Array initializer
 */
typedef struct HexArrayInitializer {
    ExprList* expr_list; 
} ArrayInitializer;


//===========================================================================
// createArrayInitializer() - construct an AST node of type ArrayInitializer.
//===========================================================================
ArrayInitializer* createArrayInitializer(ExprList *expr_list);


/*
 * Tuple initializer
 */
typedef struct HexTupleInitializer {
    ExprList *expr_list;
} TupleInitializer;


//===========================================================================
// createTupleInitializer() - construct an AST node of type TupleInitializer.
//===========================================================================
TupleInitializer* createTupleInitializer(ExprList *expr_list);


/*
 * Assignment statement list
 */
typedef struct HexAssignmentStmtList AssignmentStmtList;


/*
 * Struct initializer
 */
typedef struct HexStructInitializer {
    AssignmentStmtList *assignment_stmt_list;
} StructInitializer;


//===========================================================================
// createStructInitializer() - construct an AST node of type StructInitializer.
//===========================================================================
StructInitializer* createStructInitializer(AssignmentStmtList *assignment_stmt_list);


/*
 * Set initializer
 */
typedef struct HexSetInitializer {
    ExprList *expr_list;
} SetInitializer;


//===========================================================================
// createSetInitializer() - construct an AST node of type SetInitializer.
//===========================================================================
SetInitializer* createSetInitializer(ExprList *expr_list);


/*
 *  MapMultimapSingle
 */
typedef struct HexMapMultimapInitializerSingle {
    Expr *key;
    Expr *value;
} MapMultimapInitializerSingle;


//===========================================================================
// createMapMultimapInitializerSingle() - construct an AST node of type MapMultimapInitializerSingle.
//===========================================================================
MapMultimapInitializerSingle* createMapMultimapInitializerSingle(Expr *key, Expr *value);


/*
 * MapMultimapInitializerList
 */
typedef struct HexMapMultimapInitializerList {
    MapMultimapInitializerSingle *map_initializer_single;
    struct HexMapMultimapInitializerList *next;
} MapMultimapInitializerList;


//===========================================================================
// createMapMultimapInitializerList() - construct an AST node of type MapMultimapInitializerList.
//===========================================================================
MapMultimapInitializerList* createMapMultimapInitializerList(
    MapMultimapInitializerSingle *map_initializer_single,
    MapMultimapInitializerList *parent_list);


/*
 * MapMultimapInitializer
 */
typedef struct HexMapMultimapInitializer {
    MapMultimapInitializerList *map_initializer_list;
} MapMultimapInitializer;


//===========================================================================
// createMapMultimapInitializer() - construct an AST node of type MapMultimapInitializer.
//===========================================================================
MapMultimapInitializer *createMapMultimapInitializer(
    MapMultimapInitializerList *map_initializer_list);


/*
 * Initializer
 */
typedef struct HexInitializer {
    enum {
        initializer_type_list,                              /* list initializer */
        initializer_type_array,                             /* array initializer */
        initializer_type_tuple,                             /* tuple initializer */
        initializer_type_struct,                            /* struct initializer */
        initializer_type_set,                               /* set initializer */
        initializer_type_mapmultimap                        /* map & multimap initializer */
    } initializer_type;
    union {
        ListInitializer *list_initializer;                      /* list initializer */
        ArrayInitializer *array_initializer;                    /* array initializer */
        TupleInitializer *tuple_initializer;                    /* tuple initializer */
        StructInitializer *struct_initializer;                  /* struct initializer */
        SetInitializer *set_initialier;                         /* set initializer */
        MapMultimapInitializerList *map_multimap_initializer;   /* map & multimap initializer */
    };
} Initializer;


//===========================================================================
// createInitializer() - construct an AST node of type Initializer.
//===========================================================================
Initializer* createInitializer(int type, void* value);


/***********************************************************************
 *  Statement definitions
 ***********************************************************************/

/*
 * Assignment
 */
typedef struct HexAssignment {
    Expr *assignment_expr;                      /* target assignment expression */
    Initializer *assignment_initializer;        /* target assignment initializer */
    LambdaExpr *assignment_lambda;              /* target assignment lambda */
} Assignment;


//===========================================================================
// createAssignment() - construct an AST node of type Assignment.
//===========================================================================
Assignment* createAssignment(void* assignment_target);


/*
 * Assignment list
 */
typedef struct HexAssignmentList {
    Assignment *assignment;
    struct HexAssignmentList *next;
} AssignmentList;


//===========================================================================
// createAssignmentList() - construct an AST node of type AssignmentList.
//===========================================================================
AssignmentList* createAssignmentList(Assignment *assignment, AssignmentList *parent_list);


/*
 * Assignment statement
 */
typedef struct HexAssignmentStmt {
    enum {
        assignment_stmt_type_declaration,
        assignment_stmt_type_expr_list
    } assignment_stmt_type;
    union {
        Declaration *assignment_stmt_declaration;
        ExprList *assignment_stmt_expr_list;
    };
} AssignmentStmt;


//===========================================================================
// createAssignmentStmt() - construct an AST node of type AssignmentStmt.
//===========================================================================
AssignmentStmt* createAssignmentStmt(int type, void* value);


/*
 * Assignment statement list
 */
struct HexAssignmentStmtList {
    AssignmentStmt *assignment_stmt;
    AssignmentStmtList *next;
};


//===========================================================================
// createAssignmentStmtList() - construct an AST node of type AssignmentStmtList.
//===========================================================================
AssignmentStmtList* createAssignmentStmtList(AssignmentStmt *assignment_stmt,
    AssignmentStmtList *parent_list);


/*
 * Function declaration
 */
typedef struct HexFuncDec {
    TypeQualifierList *return_type_qualifier_list;
    int return_type_specifier;
    char *custom_return_type;
    char *func_name;
    ParameterList* parameter_list;
} FuncDec;


//===========================================================================
// createFuncDec() - construct an AST node of type FuncDec.
//===========================================================================
FuncDec* createFuncDec(TypeQualifierList *type_qualifier_list,
    int type_specifier, char *custom_return_type, char *func_name,
    ParameterList *parameter_list);


/*
 * Function definition
 */
typedef struct HexFuncDef {
    FuncDec *func_declaration;
    Suite *func_suite;
} FuncDef;


//===========================================================================
// createFuncDef() - construct an AST node of type FuncDef.
//===========================================================================
FuncDef* createFuncDef(FuncDec *func_declaration, Suite *func_suite);


/*
 * Lambda expression 
 *  
 * Syntax:
 *  target_expr = (arg_init_list) => expr
 */
struct HexLambdaExpr {
    SimpleStmtList* lambda_simple_stmt_list;
    Suite* lambda_suite;
};


//===========================================================================
// createLambdaExpr() - construct an AST node of type LambdaExpr.
//===========================================================================
LambdaExpr* createLambdaExpr(SimpleStmtList *simple_stmt_list, Suite* lambda_suite);


/*
 * Attribute
 */
typedef struct HexAttribute {
    Expr *expr;
} Attribute;


//===========================================================================
// createAttribute() - construct an AST node of type Attribute.
//===========================================================================
Attribute* createAttribute(Expr *expr);


/*
 * Compiler property
 */
typedef struct HexCompilerProperty {
    char *compiler_property_name;
    char *compiler_property_value;
} CompilerProperty;


//===========================================================================
// createCompilerProperty() - construct an AST node of type CompilerProperty.
//===========================================================================
CompilerProperty* createCompilerProperty(char *compiler_property_name, char *compiler_property_value);


/*
 * Decorator list single
 */
typedef struct DecoratorListSingle {
    enum {
        decorator_list_single_type_attribute,                           /* attribute */
        decorator_list_single_type_compiler_property                    /* compiler property */
    } decorator_list_single_type;
    union {
        Attribute* decorator_list_single_attribute;                     /* attribute */
        CompilerProperty* decorator_list_single_compiler_property;      /* compiler property */
    };
} DecoratorListSingle;


//===========================================================================
// createDecoratorListSingle() - construct an AST node of type DecoratorListSingle.
//===========================================================================
DecoratorListSingle* createDecoratorListSingle(int type, void* value);


/*
 * Decorator list
 */
typedef struct HexDecoratorList {
    DecoratorListSingle *decorator_list_single;
    struct HexDecoratorList* next;
} DecoratorList;


//===========================================================================
// createDecoratorList() - construct an AST node of type DecoratorList.
//===========================================================================
DecoratorList* createDecoratorList(DecoratorListSingle *decorator_list_single, DecoratorList* parent_list);


/*
 * Decorator
 */
typedef struct HexDecorator {
    DecoratorList *decorator_list;
} Decorator;


//===========================================================================
// createDecorator() - construct an AST node of type Decorator.
//===========================================================================
Decorator* createDecorator(DecoratorList* decorator_list);


/*
 * Module
 */
typedef struct HexModule {
    char *module_identifier;
} Module;


//===========================================================================
// createModule() - construct an AST node of type Module.
//===========================================================================
Module* createModule(char *module_identifier);


/*
 * Module list
 */
typedef struct HexModuleList {
    Module *module;
    struct HexModuleList *next;
} ModuleList;


//===========================================================================
// createModuleList() - construct an AST node of type ModuleList.
//===========================================================================
ModuleList* createModuleList(Module *module, ModuleList *parent_list);


/*
 * Direct import statement
 */
typedef struct HexDirectImportStmt {
    ModuleList *module_list;
    char *alias;
} DirectImportStmt;


//===========================================================================
// createDirectImportStmt() - construct an AST node of type DirectImportStmt.
//===========================================================================
DirectImportStmt* createDirectImportStmt(ModuleList *module_list, char *alias);


/*
 * Relative import statement
 */
typedef struct HexRelativeImportStmt {
    ModuleList* module_list;
    Module *module;
    char *alias;
} RelativeImportStmt;


//===========================================================================
// createRelativeImportStmt() - construct an AST node of type RelativeImportStmt.
//===========================================================================
RelativeImportStmt* createRelativeImportStmt(ModuleList *module_list, Module *module, char *alias);


/*
 * Import statement
 */
typedef struct HexImportStmt {
    enum {
        import_stmt_type_direct,
        import_stmt_type_relative
    } import_stmt_type;
    union {
        DirectImportStmt *import_stmt_direct_import_stmt;
        RelativeImportStmt *import_stmt_relative_import_stmt;
    };
} ImportStmt;


//===========================================================================
// createImportStmt() - construct an AST node of type ImportStmt.
//===========================================================================
ImportStmt* createImportStmt(int type, void* value);


/*
 * Elif statement
 */
typedef struct HexElifStmt {
    Expr *elif_expr;
    Suite *elif_suite;
} ElifStmt;


//===========================================================================
// createElifStmt() - construct an AST node of type ElifStmt.
//===========================================================================
ElifStmt* createElifStmt(Expr *elif_expr, Suite *elif_suite);


/*
 * Elif group
 */
typedef struct HexElifGroup {
    ElifStmt *elif_stmt;
    struct HexElifGroup *next;
} ElifGroup;


//===========================================================================
// createElifGroup() - construct an AST node of type ElifGroup.
//===========================================================================
ElifGroup* createElifGroup(ElifStmt* elif_stmt, ElifGroup *parent_list);


/*
 * Else statement
 */
// typedef struct HexElseStmt {
//     Suite *else_suite;
// } ElseStmt;


//===========================================================================
// createElseStmt() - construct an AST node of type ElseStmt.
//===========================================================================
// ElseStmt* createElseStmt(Suite *else_suite);


/*
 * If statement
 */
typedef struct HexIfStmt {
    Expr *if_expr;
    Suite *if_suite;
    ElifGroup *elif_group;
    Suite *else_stmt;
} IfStmt;


//===========================================================================
// createIfStmt() - construct an AST node of type IfStmt.
//===========================================================================
IfStmt* createIfStmt(Expr *if_expr, Suite *if_suite, ElifGroup *elif_group, Suite *else_stmt);


/*
 * If statement simple
 */
typedef struct HexIfStmtSimple {
    enum {
        if_stmt_simple_type_expr,
        if_stmt_simple_type_return
    } if_stmt_simple_type;
    Expr *expr;
} IfStmtSimple;


//===========================================================================
// createIfStmtSimple() - construct an AST node of type IfStmtSimple.
//===========================================================================
IfStmtSimple* createIfStmtSimple(ExprList *if_stmt_simple_expr_list);


/*
 * While statement
 */
typedef struct HexWhileStmt {
    Expr *while_expr;
    Suite *while_suite;
} WhileStmt;


//===========================================================================
// createWhileStmt() - construct an AST node of type WhileStmt.
//===========================================================================
WhileStmt* createWhileStmt(Expr *while_expr, Suite *while_suite);


/*
 * Iterable
 */
typedef struct HexIterable {
    enum {
        iterable_type_expr,
        iterable_type_tuple
    } iterable_type;
    union {
        Expr *iterable_expr;
        TupleInitializer *iterable_tuple;
    };
} Iterable;


//===========================================================================
// createIterable() - construct an AST node of type Iterable.
//===========================================================================
Iterable* createIterable(int type, void* value);


/*
 * For statement
 */
typedef struct HexForStmt {
    Iterable *iterble;
    Expr *expr;
    Expr *where_expr;
    Suite *suite;
} ForStmt;


//===========================================================================
// createForStmt() - construct an AST node of type ForStmt.
//===========================================================================
ForStmt* createForStmt(Iterable *iterable, Expr *expr, Expr *where_expr, Suite *suite);


/*
 * Catch statement
 */
typedef struct HexCatchStmt {
    enum {
        catch_stmt_type_single_declaration,
        cast_expr_type_multi_declaration
    } catch_stmt_type;
    union {
        Declaration *catch_declaration;
        char *catch_identifier;
    };
    Suite *catch_suite;
} CatchStmt;


//===========================================================================
// createCatchStmt() - construct an AST node of type CatchStmt.
//===========================================================================
CatchStmt* createCatchStmt(int type, void* declaration, Suite *suite);


/*
 * Catch statement group
 */
typedef struct HexCatchStmtGroup {
    CatchStmt* catch_stmt;
    struct HexCatchStmtGroup *next;
} CatchStmtGroup;


//===========================================================================
// createCatchStmtGroup() - construct an AST node of type CatchStmtGroup.
//===========================================================================
CatchStmtGroup* createCatchStmtGroup(CatchStmt* catch_stmt,
    CatchStmtGroup* parent_group);


/*
 * Finally statement
 */
typedef struct HexFinallyStmt {
    Suite* finally_suite;
} FinallyStmt;


//===========================================================================
// createFinallyStmt() - construct an AST node of type FinallyStmt.
//===========================================================================
FinallyStmt* createFinallyStmt(Suite* suite);


/*
 * Try statement
 */
typedef struct HexTryStmt {
    Suite *try_suite;
    CatchStmtGroup *catch_stmt_group;
    FinallyStmt *finally_stmt;
} TryStmt;


//===========================================================================
// createTryStmt() - construct an AST node of type TryStmt.
//===========================================================================
TryStmt* createTryStmt(Suite* try_suite, CatchStmtGroup *catch_stmt_group,
    FinallyStmt *finally_stmt);


/*
 * Compound statement
 */
struct HexCompoundStmt {
    enum {
        compound_stmt_type_if_stmt,             /* if statement */
        compound_stmt_type_while_stmt,          /* while statement */
        compound_stmt_type_try_stmt,            /* try statement */
        compound_stmt_for_stmt,                 /* for statement */
        compound_stmt_type_func_def             /* function definition */
    } compound_stmt_type;
    union {
        IfStmt *compound_stmt_if_stmt;              /* if statement */
        WhileStmt *compound_stmt_while_stmt;        /* while statement */
        ForStmt *compound_stmt_for_stmt;            /* for statement */
        TryStmt *compound_stmt_try_stmt;            /* try statement */
        FuncDef *compound_stmt_func_def;     /* function definition */
    };
};


//===========================================================================
// createCompoundStmt() - construct an AST node of type CompoundStmt.
//===========================================================================
CompoundStmt* createCompoundStmt(int type, void* value);


/*
 * Return statement
 */
typedef struct HexReturnStmt {
    ExprList *return_expr_list;
} ReturnStmt;


/*
 * Simple statement
 */
typedef struct HexSimpleStmt SimpleStmt;


/*
 * Continue statement
 */
typedef struct HexContinueStmt ContinueStmt;


/*
 * Break statement
 */
typedef struct HexBreakStmt BreakStmt;


/*
 * Control simple statement
 */
typedef struct HexControlSimpleStmt {
    enum {
        control_simple_stmt_return,
        control_simple_stmt_continue,
        control_simple_stmt_break
    } control_simple_stmt_type;
    union {
        ReturnStmt *control_simple_stmt_return_stmt;
        ContinueStmt *control_simple_stmt_continue_stmt;
        BreakStmt *control_simple_stmt_break_stmt;
    };
} ControlSimpleStmt;


//===========================================================================
// createControlSimpleStmt() - construct an AST node of type ControlSimpleStmt.
//===========================================================================
ControlSimpleStmt* createControlSimpleStmt(int type, void* value);


struct HexSimpleStmt {
    enum {
        simple_stmt_type_expr_list,             /* expression list */
        simple_stmt_type_declaration,           /* declaration */
        simple_stmt_type_assignment_stmt,       /* assignment statement */
        simple_stmt_type_import_stmt,           /* import statement */
        simple_stmt_type_if_stmt_simple,        /* simple if statement */
        simple_stmt_type_func_declaration,      /* function declaration */
        simple_stmt_type_decorator              /* decorator */
    } simple_stmt_type;
    union {
        ExprList* simple_stmt_expr_list;                /* expression list */
        Declaration *simple_stmt_declaration;           /* declaration */
        AssignmentStmt *simple_stmt_assignment_stmt;    /* assignment statement */
        ImportStmt *simple_stmt_import_stmt;            /* import statement */
        IfStmtSimple *simple_stmt_if_stmt_simple;       /* simple if statement */
        FuncDec *simple_stmt_func_declaration;          /* function declaration */
        Decorator *simple_stmt_decorator;               /* decorator */   
    };
};


//===========================================================================
// createPassStmt() - construct an AST node of type PassStmt.
//===========================================================================
SimpleStmt* createSimpleStmt(int type, void* value);


/*
 * Simple statement list
 */
struct HexSimpleStmtList {
    SimpleStmt *simple_stmt;
    struct HexSimpleStmtList *next;
};


//===========================================================================
// createSimpleStmtList() - construct an AST node of type SimpleStmtList.
//===========================================================================
SimpleStmtList* createSimpleStmtList(SimpleStmt *simple_stmt, SimpleStmtList *parent_list);


/*
 * Statement
 */
struct HexStmt {
    enum {
        stmt_type_simple_stmt_list,         /* statement list */
        stmt_type_compound_stmt,            /* compound statement */
        stmt_type_control_simple_stmt       /* control_simple_stmt */
    } stmt_type;
    union {
        SimpleStmtList *stmt_simple_stmt_list;          /* simple statement list */
        CompoundStmt* stmt_compound_stmt;               /* compound statement */
        ControlSimpleStmt *stmt_control_simple_stmt;    /* control simple statement */
    };
};


//===========================================================================
// createStmt() - construct an AST node of type Stmt.
//===========================================================================
Stmt* createStmt(int type, void* value);


/*
 * Statement group
 */
typedef struct HexStmtGroup {
    Stmt *stmt;
    struct HexStmtGroup *next;
} StmtGroup;


//===========================================================================
// createStmtGroup() - construct an AST node of type StmtGroup.
//===========================================================================
StmtGroup* createStmtGroup(Stmt *stmt, StmtGroup *parent_group);


/*
 * Suite
 */
struct HexSuite {
    StmtGroup *stmt_group;
};


//===========================================================================
// createSuite() - construct an AST node of type Suite.
//===========================================================================
Suite* createSuite(StmtGroup *stmt_group);


#endif // _AST_H_