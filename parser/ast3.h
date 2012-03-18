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
 * Statement
 */
typedef struct HexStmt Stmt;


/*
 * Suite
 */
typedef struct HexSuite Suite;
//===========================================================================
// global typedefs
//===========================================================================


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
 * Unary operator
 */
// typedef enum HexUnaryOp {
//     unary_op_minus,
//     unary_op_inc,
//     unary_op_dec,
//     unary_op_not,
//     unary_op_bitwise_not,
// } UnaryOp;


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
    type_specifier_ulong,           /* type ulong */
    type_specifier_identifier       /* custom type */
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
 *  multiplicative: multiplication and division '*' or '/'
 *  additive: addition and subtraction          '+' or '-'
 *
 * Syntax:
 *  target_expr = left_expr [ * | - | * | / ] right_expr
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
 *  target_expr = consequent if predicate else alternative
 */
typedef struct HexConditionalExpr {
    Expr* consequent_expr;
    Expr* predicate_expr;
    Expr* alternative_expr;
} ConditionalExpr;


//===========================================================================
// createConditionalExpr() - construct an AST node of type ConditionalExpr.
//===========================================================================
Expr* createConditionalExpr(Expr *predicate_expr, Expr *consequent_expr, Expr *alternative_expr);


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
 * Lambda expression 
 *  
 * Syntax:
 *  target_expr = (arg_init_list) => expr
 */
typedef struct HexLambdaExpr {
    struct ParameterList* lambda_param_list;
    Suite* lambda_suite;
} LambdaExpr;


/*
 * Parameter list
 */
typedef struct HexParameterList ParameterList;


//===========================================================================
// createLambdaExpr() - construct an AST node of type LambdaExpr.
//===========================================================================
Expr* createLambdaExpr(ParameterList *param_list, Suite* lambda_suite);


/*
 * Expression.
 */
struct HexExpr {
    enum {
        expr_type_primary,
        expr_type_postfix,
        expr_type_unary,
        expr_type_cast,
        expr_type_multilicative,
        expr_type_arithmetic,
        expr_type_logic,
        expr_type_bitwise,
        expr_type_conditional,
        expr_type_lambda
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
        LambdaExpr *lambda_expr;
    };
};


//===========================================================================
// createExpr() - construct an AST node of type Expr.
//===========================================================================
Expr* createExpr(int type, void* value);


/*
 * Expression list
 */
struct ExprList {
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
 * Parameter list
 */
struct ParameterList {
    Declaration *param_declaration;
    struct HexParameterList *next;
};


//===========================================================================
// createParameterList() - construct an AST node of type ParameterList.
//===========================================================================
ParameterList *createParameterList(Declaration *declaration, ParameterList* parent_list);


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
ListInitializer *createListInitializer(ExprList *expr_list);


/*
 * Array initializer
 */
typedef struct HexArrayInitializer {
    ExprList* expr_list; 
} ArrayInitializer;


//===========================================================================
// createArrayInitializer() - construct an AST node of type ArrayInitializer.
//===========================================================================
ArrayInitializer *createArrayInitializer(ExprList *expr_list);


/*
 * Tuple initializer
 */
typedef struct HexTupleInitializer {
    ExprList *expr_list;
} TupleInitializer;


//===========================================================================
// createTupleInitializer() - construct an AST node of type TupleInitializer.
//===========================================================================
TupleInitializer *createTupleInitializer(ExprList *expr_list);


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
StructInitializer *createStructInitializer(AssignmentStmtList *assignment_stmt_list);


/*
 * Set initializer
 */
typedef struct HexSetInitializer {
    ExprList *expr_list;
} SetInitializer;


//===========================================================================
// createSetInitializer() - construct an AST node of type SetInitializer.
//===========================================================================
SetInitializer *createSetInitializer(ExprList *expr_list);


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
MapMultimapInitializerSingle *createMapMultimapInitializerSingle(Expr *key, Expr *value);


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
MapMultimapInitializerList *createMapMultimapInitializerList(
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
    Expr *expr;
} Assignment;


//===========================================================================
// createAssignment() - construct an AST node of type Assignment.
//===========================================================================
Assignment* createAssignment(Expr *expr);


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
struct AssignmentStmtList {
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
typedef struct HexFuncDeclaration {
    TypeQualifierList *return_type_qualifier_list;
    int return_type_specifier;
    char *custom_return_type;
    char *func_name;
    ParameterList* parameter_list;
} FuncDeclaration;


//===========================================================================
// createFuncDeclaration() - construct an AST node of type FuncDeclaration.
//===========================================================================
FuncDeclaration* createFuncDeclaration(TypeQualifierList *type_qualifier_list,
    int type_specifier, char *custom_return_type, char *func_name,
    ParameterList *parameter_list);


/*
 * Function definition
 */
typedef struct HexFuncDefinition {
    FuncDeclaration *func_declaration;
    Suite *func_suite;
} FuncDefinition;


//===========================================================================
// createFuncDefinition() - construct an AST node of type FuncDefinition.
//===========================================================================
FuncDefinition* createFuncDefinition(FuncDeclaration *func_declaration, Suite *func_suite);


/*
 * Compound statement
 */
typedef struct HexCompoundStmt CompoundStmt;


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
RelativeImportStmt* createRelativeImportStmt(ModuleList *module_list, Module *module char *alias);


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
typedef struct HexElseStmt {
    Suite *else_suite;
} ElseStmt;


//===========================================================================
// createElseStmt() - construct an AST node of type ElseStmt.
//===========================================================================
ElseStmt* createElseStmt(Suite *else_suite);


/*
 * If statement
 */
typedef struct HexIfStmt {
    Expr *if_expr;
    Suite *if_suite;
    ElifGroup *elif_group;
    ElseStmt *else_stmt;
} IfStmt;


//===========================================================================
// createIfStmt() - construct an AST node of type IfStmt.
//===========================================================================
CompoundStmt* createIfStmt(Expr *if_expr, Suite *if_suite, ElifGroup *elif_group, ElseStmt *else_stmt);


/*
 * While statement
 */
typedef struct HexWhileStmt {
    Expr *while_expr;
    Suite *while_suite;
} WhileStmt;


/*
 * For statement
 */
typedef struct HexForStmt {

} ForStmt;

//===========================================================================
// createWhileStmt() - construct an AST node of type WhileStmt.
//===========================================================================
CompoundStmt* createWhileStmt(Expr *while_expr, Suite *while_suite);


/*
 * Catch statement
 */
typedef struct HexCatchStmt {
    Declaration *catch_declaration;
    char *catch_type;
    char *catch_identifier;
    Suite *catch_suite;
} CatchStmt;


//===========================================================================
// createCatchStmt() - construct an AST node of type CatchStmt.
//===========================================================================
CatchStmt* createCatchStmt(Expr* catch_expr, Suite* catch_suite);


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
CompoundStmt* createTryStmt(Suite* try_suite, CatchStmtGroup *catch_stmt_group,
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
        FuncDefinition *compound_stmt_func_def;     /* function definition */
    };
};


//===========================================================================
// createCompoundStmt() - construct an AST node of type CompoundStmt.
//===========================================================================
Stmt* createCompoundStmt(int type, void* value);


/*
 * Return statement
 */
typedef struct HexReturnStmt {
    ExprList *return_expr_list;
} ReturnStmt;


//===========================================================================
// createReturnStmt() - construct an AST node of type ReturnStmt.
//===========================================================================
Stmt* createReturnStmt(ExprList* value);


/*
 * Continue statement
 */
typedef struct HexContinueStmt ContinueStmt;


/*
 * Break statement
 */
typedef struct HexBreakStmt BreakStmt;


/*
 * Pass statement
 */
typedef struct HexPassStmt PassStmt;


/*
 * Simple statement
 */
typedef struct HexSimpleStmt {
    enum {
        simple_stmt_type_expr,                  /* expression */
        simple_stmt_type_assignment_stmt,       /* assignment statement */
        simple_stmt_type_return_stmt,           /* return statement */
        simple_stmt_type_break_stmt,            /* break statement */
        simple_stmt_type_continue_stmt,         /* continue statement */
        simple_stmt_type_import_stmt,           /* import statement */
        simple_stmt_type_func_declaration       /* function declaration */
    } simple_stmt_type;
    union {
        Expr *simple_stmt_expr;                         /* expression */
        AssignmentStmt *simple_stmt_assignment_stmt;    /* assignment statement */
        ReturnStmt *simple_stmt_return_stmt;            /* return statement */
        BreakStmt *simple_stmt_break_stmt;              /* break statement */
        ContinueStmt *simple_stmt_continue_stmt;        /* continue statement */
        ImportStmt *simple_stmt_import_stmt;            /* import statement */
        FuncDeclaration *simple_stmt_func_declaration;  /* function declaration */
    };
} SimpleStmt;


/*
 * Simple statement list
 */
typedef struct HexSimpleStmtList {
    SimpleStmt *simple_stmt;
    struct HexSimpleStmtList *next;
} SimpleStmtList;


/*
 * Statement
 */
struct HexStmt {
    enum {
        stmt_type_simple_stmt_list,         /* statement list */
        stmt_type_compound_stmt             /* compound statement */
    } stmt_type;
    union {
        SimpleStmtList *simple_stmt_list;   /* simple statement list */
        CompoundStmt* compound_stmt;        /* compound statement */
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


/*
 * Suite
 */
struct Suite {
    StmtGroup *stmt_group;
};


#endif // _AST_H_