/*
 * HEX Programming Language
 * Copyright (C) 2012  Yanzheng Li
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/* Abstract Syntax Tree */

#ifndef _AST_H_
#define _AST_H_

#include <stdlib.h>


#define AST_ERROR(level, errstr)        \
  do {                                  \
    fprintf(                            \
      stderr,                           \
      "AST ERROR: %s at %d\n",          \
      errstr,                           \
      __LINE__                          \
    );                                  \
                                        \
    exit(EXIT_FAILURE);                 \
  } while(0)


//===========================================================================
// global typedefs
//===========================================================================

/*
 * Expression
 */
typedef struct HexExpr *Expr;


/*
 * Expr list
 */
typedef struct HexExprList *ExprList;

/*
 * Tuple initializer
 */
typedef struct HexTupleInitializer *TupleInitializer;

/*
 * List initializer
 */
typedef struct HexListInitializer *ListInitializer;


/*
 * Lambda expression
 */
typedef struct HexLambdaExpr *LambdaExpr;

/*
 * Assignment statement list
 */
typedef struct HexAssignmentStmtList *AssignmentStmtList;

/*
 * Simple statement list 
 */
typedef struct HexSimpleStmtList *SimpleStmtList;


/*
 * Statement
 */
typedef struct HexStmt *Stmt;


/*
 * Compound statement
 */
typedef struct HexCompoundStmt *CompoundStmt;

/*
 * Suite
 */
typedef struct HexSuite *Suite;


//===========================================================================
// global typedefs
//===========================================================================


#define HEX_PARSE_TREE_ROOT_TYPE_STMT_GROUP     0x0001
#define HEX_PARSE_TREE_ROOT_TYPE_CLASS          0x0002
#define HEX_PARSE_TREE_ROOT_TYPE_CLASS_SECTION  0x0004

void* hex_ast_get_parse_tree_root(int *root_type);
void hex_ast_set_parse_tree_root(void *p, int root_type);


/*
 * Integer
 */
typedef struct HexInteger {
  enum {
    integer_type_decimal,               /* decimal integer */
    integer_type_binary,                /* binary integer */
    integer_type_octal,                 /* octal decimal integer */
    integer_type_hexadecimal            /* hexa decimal integer */
  } integer_type;
  int is_signed;                        /* integer signness */
  int integer;                          /* underlying integer number */
  union {
    int signed_integer;
    unsigned int unsigned_integer;
  };
} *Integer;


//===========================================================================
// hex_ast_create_integer()
// construct an AST node of type HexInteger.
//===========================================================================
Integer
hex_ast_create_integer(int type, int is_signed, int value);


/*
 * Literal
 */
typedef struct HexLiteral {
  enum {
    literal_type_char,                  /* character literal */
    literal_type_string,                /* string literal */
    literal_type_integer,               /* integer literal */
    literal_type_float,                 /* floating number literal */
  } literal_type;
  union {
    char literal_char;                  /* character literal */
    char* literal_string;               /* string literal */
    Integer literal_integer;           /* integer literal */
    double literal_float;               /* floating number literal */
  };
} *Literal;


//===========================================================================
// hex_ast_create_literal()
// construct an AST node of type HexLiteral.
//===========================================================================
Literal
hex_ast_create_literal(int type, void *value);


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
    Literal primary_expr_literal;       /* literal */
  };
} *PrimaryExpr;


//===========================================================================
// hex_ast_create_primary_expr()
// construct an AST node of type HexPrimaryExpr.
//===========================================================================
Expr
hex_ast_create_primary_expr(int type, void *value);


/*
 * Postfix index expression
 */
typedef struct HexPostfixIndexExpr {
  enum {
    postfix_index_expr_type_identifier,
    postfix_index_expr_type_expr
  } postfix_index_expr_type;
  union {
    char *identifier;
    Expr index_expr;
  };
  ExprList indeces_list;
} *PostfixIndexExpr;


//===========================================================================
// hex_ast_create_postfix_index_expr()
// construct an AST node of type HexPostfixIndexExpr.
//===========================================================================
PostfixIndexExpr
hex_ast_create_postfix_index_expr(int type, void *value, ExprList indeces_list); 


/*
 * Postfix accessor expression
 */
typedef struct HexPostfixAccessorExpr {
  Expr caller;
  Expr accessor;
} *PostfixAccessorExpr;


//===========================================================================
// hex_ast_create_postfix_accessor_expr()
// construct an AST node of type HexPostfixAccessorExpr.
//===========================================================================
PostfixAccessorExpr
hex_ast_create_postfix_accessor_expr(Expr caller, char *accessor);


/*
 * Postfix invocation with args expression
 */
typedef struct HexPostfixInvocationExpr {
  enum {
    postfix_invocation_expr_type_identifier,
    postfix_invocation_expr_type_expr
  } postfix_invocation_expr_type;
  union {
    char *invocation_name;
    Expr invocation_expr;
  };
} *PostfixInvocationExpr;


//===========================================================================
// hex_ast_create_postfix_invocation_expr()
// construct an AST node of type HexPostfixInvocationExpr.
//===========================================================================
PostfixInvocationExpr
hex_ast_create_postfix_invocation_expr(int type, void *invocation_src);


/*
 * Postfix invocation with args expression
 */
typedef struct HexPostfixInvocationWithArgsExpr {
  enum {
    postfix_invocation_expr_with_args_type_identifier,
    postfix_invocation_expr_with_args_type_expr  
  } postfix_invocation_expr_with_args_type;
  union {
    char *invocation_name;
    Expr invocation_expr;
  };
  ExprList arg_list;
} *PostfixInvocationWithArgsExpr;


//===========================================================================
// hex_ast_create_postfix_invocation_with_args_expr()
// construct an AST node of type HexPostfixInvocationWithArgsExpr.
//===========================================================================
PostfixInvocationWithArgsExpr
hex_ast_create_postfix_invocation_with_args_expr(int type, void *value, TupleInitializer arg_list_tuple);


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
typedef struct HexPostfixExpr {
  enum {
    postfix_expr_type_index,                                                    /* index */
    postfix_expr_type_postfix_inc,                                              /* increment */
    postfix_expr_type_postfix_dec,                                              /* decrement */
    postfix_expr_type_accessor,                                                 /* accessor */
    postfix_expr_type_invocation,                                               /* function invocation */
    postfix_expr_type_invocation_with_args                                      /* function invocation with args */
  } postfix_expr_type;
  union {
    PostfixIndexExpr postfix_expr_index_expr;                                   /* index */
    Expr postfix_expr_postfix_inc_expr;                                         /* increment */
    Expr postfix_expr_postfix_dec_expr;                                         /* decrement */            
    PostfixAccessorExpr postfix_expr_accessor_expr;                             /* accessor */
    PostfixInvocationExpr postfix_expr_invocation_expr;                         /* function invocation */
    PostfixInvocationWithArgsExpr postfix_expr_invocation_with_args_expr;       /* function invocation with args */
  };
} *PostfixExpr;


//===========================================================================
// hex_ast_create_postfix_expr()
// construct an AST node of type HexPostfixExpr.
//===========================================================================
Expr
hex_ast_create_postfix_expr(int type, int type2, void *value, void *value1);


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
    Expr unary_expr_prefix_inc_expr;        /* prefix increment */
    Expr unary_expr_prefix_dec_expr;        /* prefix decrement */
    Expr unary_expr_unary_expr;             /* unary minus */
    Expr unary_expr_not;                    /* unary not */
    Expr unary_expr_bitwise_not;            /* unary bitwise not */
  };
} *UnaryExpr;


//===========================================================================
// hex_ast_create_unary_expr()
// construct an AST node of type HexUnaryExpr.
//===========================================================================
Expr
hex_ast_create_unary_expr(int type, Expr expr);


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
  Expr expr;
  enum {
    cast_expr_type_type_specifier,
    cast_expr_type_custom_type
  } cast_expr_type;
  union {
    int type_specifier;
    char* identifier;
  };
} *CastExpr;


//===========================================================================
// hex_ast_create_cast_expr()
// construct an AST node of type HexCastExpr.
//===========================================================================
Expr
hex_ast_create_cast_expr(int type, void* value, Expr expr);


/*
 * Multiplcative expression
 */
typedef struct HexMultiplicativeExpr {
  enum {
    multiplicative_expr_type_mul,
    multiplicative_expr_type_div,
    multiplicative_expr_type_mod
  } multi_expr_type;
  Expr left_expr;
  Expr right_expr;
} *MultiplicativeExpr;


//===========================================================================
// hex_ast_create_multiplicative_expr()
// construct an AST node of type HexMultiplcativeExpr.
//===========================================================================
Expr
hex_ast_create_multiplicative_expr(int type, Expr left_expr, Expr right_expr);


/*
 * Additive expression
 */
typedef struct HexAdditiveExpr {
  enum {
    additive_expr_type_plus,
    additive_expr_type_minus
  } additive_expr_type;
  Expr left_expr;
  Expr right_expr;
} *AdditiveExpr;


//===========================================================================
// hex_ast_create_additive_expr()
// construct an AST node of type HexAdditiveExpr.
//===========================================================================
Expr
hex_ast_create_additive_expr(int type, Expr left_expr, Expr right_expr);


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
    MultiplicativeExpr arithmetic_expr_multiplicative_expr;
    AdditiveExpr arithmetic_expr_additive_expr;
  };
} *ArithmeticExpr;


//===========================================================================
// hex_ast_create_arithmetic_expr()
// construct an AST node of type HexArithmeticExpr.
//===========================================================================
ArithmeticExpr
hex_ast_create_arithmetic_expr(int type, void *expr);


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
    equality_expr_type_ge,          /* >= */
    equality_expr_type_is,          /* is */
    equality_expr_type_is_not       /* is not */
  } equality_expr_type;
  Expr left_expr;
  Expr right_expr;
} *EqualityExpr;


//===========================================================================
// hex_ast_create_equality_expr()
// construct an AST node of type HexEqualityExpr.
//===========================================================================
Expr
hex_ast_create_equality_expr(int type, Expr left_expr, Expr right_expr);


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
  Expr left_expr;
  Expr right_expr;
} *LogicExpr;


//===========================================================================
// hex_ast_create_logic_expr()
// construct an AST node of type HexLogicExpr.
//===========================================================================
Expr
hex_ast_create_logic_expr(int type, Expr left_expr, Expr right_expr);


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
  Expr left_expr;
  Expr right_expr;
} *BitwiseExpr;


//===========================================================================
// hex_ast_create_bitwise_expr()
// construct an AST node of type HexBitwiseExpr.
//===========================================================================
Expr
hex_ast_create_bitwise_expr(int type, Expr left_expr, Expr right_expr);


/*
 * Conditional expression 
 *  
 * Syntax:
 *  target_expr = if predicate then consequent else alternative
 */
typedef struct HexConditionalExpr {
  Expr predicate_expr;
  Expr alternative_expr;
  Expr consequent_expr;
} *ConditionalExpr;


//===========================================================================
// hex_ast_create_conditional_expr()
// construct an AST node of type HexConditionalExpr.
//===========================================================================
Expr
hex_ast_create_conditional_expr(Expr predicate_expr, Expr alternative_expr, Expr consequent_expr);


/*
 * Range expression
 *
 * A range expression uses a beginning and an end expression
 * to denote a range, using the ellipsis operator.
 */
typedef struct HexRangeExpr {
  Expr left_expr;
  Expr right_expr;
} *RangeExpr;


//===========================================================================
// hex_ast_create_range_expr()
// construct an AST node of type HexRangeExpr.
//===========================================================================
Expr
hex_ast_create_range_expr(Expr left_expr, Expr right_expr);


/*
 * Lock/unlock expression
 */
typedef struct HexLockExpr {
  int is_lock;
  Expr expr;
} *LockExpr;


//===========================================================================
// hex_ast_create_lock_expr()
// construct an AST node of type HexLockExpr.
//===========================================================================
Expr
hex_ast_create_lock_expr(int is_lock, Expr expr);


/*
 * Weakref expression
 */
typedef struct HexWeakrefExpr {
  Expr expr;
} *WeakrefExpr;


//===========================================================================
// hex_ast_create_weakref_expr()
// construct an AST node of type HexWeakrefExpr.
//===========================================================================
Expr
hex_ast_create_weakref_expr(Expr expr);


/*
 * HEX expression
 */
struct HexExpr {
  enum {
    expr_type_primary,
    expr_type_postfix,
    expr_type_unary,
    expr_type_cast,
    expr_type_arithmetic,
    expr_type_equality,
    expr_type_logic,
    expr_type_bitwise,
    expr_type_conditional,
    expr_type_range,
    expr_type_lock,
    expr_type_weakref,
    expr_type_this,
    expr_type_base
  } expr_type;
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
    RangeExpr range_expr;
    LockExpr lock_expr;
    WeakrefExpr weakref_expr;
  };
};


//===========================================================================
// hex_ast_create_expr()
// construct an AST node of type HexExpr.
//===========================================================================
Expr
hex_ast_create_expr(int type, void *value);


/*
 * Assignment operator
 */
typedef enum HexAssignmentOp {
  assign_op,                  /* = */
  assign_op_weakref,          /* ~= */
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
  Expr expr;
  struct HexExprList *next;
};


//===========================================================================
// hex_ast_create_expr_list()
// construct an AST node of type HexExprList.
//===========================================================================
ExprList
hex_ast_create_expr_list(Expr expr, ExprList parent_list);


/***********************************************************************
 * Declaration definitions
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
} *TypeQualifierList;


//===========================================================================
// hex_ast_create_type_qualifier_list()
// construct an AST node of type HexTypeQualifierList.
//===========================================================================
TypeQualifierList
hex_ast_create_type_qualifier_list(TypeQualifier qualifier, TypeQualifierList parent_list);


/*
 *  Declaration
 */
typedef struct HexDeclaration {
  TypeQualifierList type_qualifier_list;
  int type_specifier;
  char *custom_type;
  ExprList expr_list;
  char *alias;
} *Declaration;


//===========================================================================
// hex_ast_create_declaration()
// construct an AST node of type HexDeclaration.
//===========================================================================
Declaration
hex_ast_create_declaration(TypeQualifierList type_qualifier_list,
  int type_specifier, char *custom_type, ExprList expr_list, char *alias);


/***********************************************************************
 *  Parameter definitions
 ***********************************************************************/


/*
 *  Declaration
 */
typedef struct HexParameter {
  TypeQualifierList type_qualifier_list;
  int type_specifier;
  char *custom_type;
  char *parameter_name;
  char *alias;
  int is_ref;
} *Parameter;


//===========================================================================
// hex_ast_create_parameter()
// construct an AST node of type HexParameter.
//===========================================================================
Parameter
hex_ast_create_parameter(TypeQualifierList type_qualifier_list, int type_specifier,
  char *custom_type, char *parameter_name, char *alias, int is_ref);


/*
 * Parameter list
 */
typedef struct HexParameterList {
  Parameter parameter;
  struct HexParameterList *next;
} *ParameterList;


//===========================================================================
// hex_ast_create_parameter_list()
// construct an AST node of type HexParameterList.
//===========================================================================
ParameterList
hex_ast_create_parameter_list(Parameter parameter, ParameterList parent_list);


/***********************************************************************
 *  Initializer definitions
 ***********************************************************************/


/*
 * List initializer
 */
struct HexListInitializer {
  ExprList expr_list;
};


//===========================================================================
// hex_ast_create_list_initializer()
// construct an AST node of type HexListInitializer.
//===========================================================================
ListInitializer
hex_ast_create_list_initializer(ExprList expr_list);


/*
 * Array initializer
 */
typedef struct HexArrayInitializer {
  ExprList expr_list; 
} *ArrayInitializer;


//===========================================================================
// hex_ast_create_array_initializer()
// construct an AST node of type HexArrayInitializer.
//===========================================================================
ArrayInitializer
hex_ast_create_array_initializer(ExprList expr_list);


/*
 * Tuple initializer
 */
struct HexTupleInitializer {
  ExprList expr_list;
};


//===========================================================================
// hex_ast_create_tuple_initializer()
// construct an AST node of type HexTupleInitializer.
//===========================================================================
TupleInitializer
hex_ast_create_tuple_initializer(ExprList expr_list);


/*
 * Struct initializer
 */
typedef struct HexStructInitializer {
  AssignmentStmtList assignment_stmt_list;
} *StructInitializer;


//===========================================================================
// hex_ast_create_struct_initializer()
// construct an AST node of type HexStructInitializer.
//===========================================================================
StructInitializer
hex_ast_create_struct_initializer(AssignmentStmtList assignment_stmt_list);


/*
 * Set initializer
 */
typedef struct HexSetInitializer {
  ExprList expr_list;
} *SetInitializer;


//===========================================================================
// hex_ast_create_set_initializer()
// construct an AST node of type HexSetInitializer.
//===========================================================================
SetInitializer
hex_ast_create_set_initializer(ExprList expr_list);


/*
 *  MapInitializerSingle
 */
typedef struct HexMapInitializerSingle {
  Expr key;
  Expr value;
} *MapInitializerSingle;


//===========================================================================
// hex_ast_create_map_initializer_single()
// construct an AST node of type HexMapInitializerSingle.
//===========================================================================
MapInitializerSingle
hex_ast_create_map_initializer_single(Expr key, Expr value);


/*
 * MapInitializerList
 */
typedef struct HexMapInitializerList {
  MapInitializerSingle map_initializer_single;
  struct HexMapInitializerList *next;
} *MapInitializerList;


//===========================================================================
// hex_ast_create_map_initializer_list()
// construct an AST node of type HexMapInitializerList.
//===========================================================================
MapInitializerList
hex_ast_create_map_initializer_list(
  MapInitializerSingle map_initializer_single, MapInitializerList parent_list);


/*
 * MapInitializer
 */
typedef struct HexMapInitializer {
  MapInitializerList map_initializer_list;
} *MapInitializer;


//===========================================================================
// hex_ast_create_map_initializer()
// construct an AST node of type HexMapInitializer.
//===========================================================================
MapInitializer
hex_ast_create_map_initializer(MapInitializerList map_initializer_list);


/*
 * Initializer
 */
typedef struct HexInitializer {
  enum {
    initializer_type_list,                              /* list initializer    */
    initializer_type_array,                             /* array initializer   */
    initializer_type_tuple,                             /* tuple initializer   */
    initializer_type_struct,                            /* struct initializer  */
    initializer_type_set,                               /* set initializer     */
    initializer_type_map                                /* map initializer     */
  } initializer_type;
  union {
    ListInitializer list_initializer;                   /* list initializer    */
    ArrayInitializer array_initializer;                 /* array initializer   */
    TupleInitializer tuple_initializer;                 /* tuple initializer   */
    StructInitializer struct_initializer;               /* struct initializer  */
    SetInitializer set_initializer;                     /* set initializer     */
    MapInitializer map_initializer;                     /* map initializer     */
    };
} *Initializer;


//===========================================================================
// hex_ast_create_initializer()
// construct an AST node of type HexInitializer.
//===========================================================================
Initializer
hex_ast_create_initializer(int type, void *value);


/***********************************************************************
 *  Statement definitions
 ***********************************************************************/

/*
 * Assignment
 */
typedef struct HexAssignment {
  AssignmentOp assignment_op;
  enum {
    assignment_type_expr,
    assignment_type_initializer,
    assignment_type_lambda
  } assignment_type;
  union {
    Expr assignment_expr;                         /* target assignment expression */
    Initializer assignment_initializer;           /* target assignment initializer */
    LambdaExpr assignment_lambda;                 /* target assignment lambda */
  };
} *Assignment;


//===========================================================================
// hex_ast_create_assignment()
// construct an AST node of type HexAssignment.
//===========================================================================
Assignment
hex_ast_create_assignment(AssignmentOp assignment_op, int type, void *target);


/*
 * Assignment list
 */
typedef struct HexAssignmentList {
  Assignment assignment;
  struct HexAssignmentList *next;
} *AssignmentList;


//===========================================================================
// hex_ast_create_assignment_list()
// construct an AST node of type HexAssignmentList.
//===========================================================================
AssignmentList
hex_ast_create_assignment_list(Assignment assignment, AssignmentList parent_list);


/*
 * Assignment statement
 */
typedef struct HexAssignmentStmt {
  enum {
    assignment_stmt_type_declaration,
    assignment_stmt_type_expr_list
  } assignment_stmt_type;
  union {
    Declaration assignment_stmt_declaration;
    ExprList assignment_stmt_expr_list;
  };
  AssignmentList assignment_list;
} *AssignmentStmt;


//===========================================================================
// hex_ast_create_assignment_stmt()
// construct an AST node of type HexAssignmentStmt.
//===========================================================================
AssignmentStmt
hex_ast_create_assignment_stmt(int type, void *value, AssignmentList assignment_list);


/*
 * Assignment statement list
 */
struct HexAssignmentStmtList {
  AssignmentStmt assignment_stmt;
  struct HexAssignmentStmtList *next;
};


//===========================================================================
// hex_ast_create_assignment_stmt_list()
// construct an AST node of type HexAssignmentStmtList.
//===========================================================================
AssignmentStmtList
hex_ast_create_assignment_stmt_list(AssignmentStmt assignment_stmt, AssignmentStmtList parent_list);


/*
 * Function declaration
 */
typedef struct HexFuncDec {
  TypeQualifierList return_type_qualifier_list;
  int return_type_specifier;
  char *custom_return_type;
  char *func_name;
  ParameterList parameter_list;
} *FuncDec;


//===========================================================================
// hex_ast_create_func_dec()
// construct an AST node of type HexFuncDec.
//===========================================================================
FuncDec
hex_ast_create_func_dec(TypeQualifierList type_qualifier_list,
  int type_specifier, char *custom_return_type, char *func_name, ParameterList parameter_list);


/*
 * Function definition
 */
typedef struct HexFuncDef {
  FuncDec func_declaration;
  Suite func_suite;
} *FuncDef;


//===========================================================================
// hex_ast_create_func_def()
// construct an AST node of type HexFuncDef.
//===========================================================================
FuncDef
hex_ast_create_func_def(FuncDec func_declaration, Suite func_suite);


/*
 * Lambda expression 
 *  
 * Syntax:
 *  target_expr = (arg_init_list) => expr
 */
struct HexLambdaExpr {
  ParameterList lambda_param_list;
  enum {
    lambda_type_simple,                     /* simple stmt list */
    lambda_type_suite                       /* suite */
  } lambda_type;
  union {
    SimpleStmtList lambda_simple_stmt_list;
    Suite lambda_suite;
  };
};


//===========================================================================
// hex_ast_create_lambda_expr()
// construct an AST node of type HexLambdaExpr.
//===========================================================================
LambdaExpr
hex_ast_create_lambda_expr(int type, ParameterList param_list, void *body);


/*
 * Attribute
 */
typedef struct HexAttribute {
  Expr expr;
} *Attribute;


//===========================================================================
// hex_ast_create_attribute()
// construct an AST node of type HexAttribute.
//===========================================================================
Attribute
hex_ast_create_attribute(Expr expr);


/*
 * Compiler property
 */
typedef struct HexCompilerProperty {
  char *compiler_property_name;
  char *compiler_property_value;
} *CompilerProperty;


//===========================================================================
// createCompilerProperty()
// construct an AST node of type HexCompilerProperty.
//===========================================================================
CompilerProperty
hex_ast_create_compiler_property(char *compiler_property_name, char *compiler_property_value);


/*
 * Decorator list single
 */
typedef struct HexDecoratorListSingle {
  enum {
    decorator_list_single_type_attribute,                           /* attribute */
    decorator_list_single_type_compiler_property                    /* compiler property */
  } decorator_list_single_type;
  union {
    Attribute decorator_list_single_attribute;                      /* attribute */
    CompilerProperty decorator_list_single_compiler_property;       /* compiler property */
  };
} *DecoratorListSingle;


//===========================================================================
// hex_ast_create_decorator_list_single()
// construct an AST node of type HexDecoratorListSingle.
//===========================================================================
DecoratorListSingle
hex_ast_create_decorator_list_single(int type, void *value);


/*
 * Decorator list
 */
typedef struct HexDecoratorList {
  DecoratorListSingle decorator_list_single;
  struct HexDecoratorList* next;
} *DecoratorList;


//===========================================================================
// hex_ast_create_decorator_list()
// construct an AST node of type HexDecoratorList.
//===========================================================================
DecoratorList
hex_ast_create_decorator_list(DecoratorListSingle decorator_list_single, DecoratorList parent_list);


/*
 * Decorator
 */
typedef struct HexDecorator {
  DecoratorList decorator_list;
} *Decorator;


//===========================================================================
// hex_ast_create_decorator()
// construct an AST node of type HexDecorator.
//===========================================================================
Decorator
hex_ast_create_decorator(DecoratorList decorator_list);


/*
 * Class declaration
 */
typedef struct HexClassDeclaration {
  char *name;
  ExprList expr_list;
} *ClassDeclaration;


//===========================================================================
// hex_ast_create_class_declaration()
// construct an AST node of type HexClassDeclaration.
//===========================================================================
ClassDeclaration
hex_ast_create_class_declaration(char *name, ExprList expr_list);


/*
 * Class access specifier
 */
typedef enum HexClassAccessSpecifier {
  class_access_specifier_private,           /* private */
  class_access_specifier_protected,         /* protected */
  class_access_specifier_public             /* public */
} ClassAccessSpecifier;


/*
 * Class section
 */
typedef struct HexClassSection {
  int class_access_specifier;
  Suite suite;
} *ClassSection;


//===========================================================================
// hex_ast_create_class_section()
// construct an AST node of type HexClassSection.
//===========================================================================
ClassSection
hex_ast_create_class_section(int class_access_specifier, Suite suite);


/*
 * Module
 */
typedef struct HexModule {
  char *module_identifier;
} *Module;


//===========================================================================
// hex_ast_create_module()
// construct an AST node of type HexModule.
//===========================================================================
Module
hex_ast_create_module(char *module_identifier);


/*
 * Module list
 */
typedef struct HexModuleList {
  Module module;
  struct HexModuleList *next;
} *ModuleList;


//===========================================================================
// hex_ast_create_module_list()
// construct an AST node of type HexModuleList.
//===========================================================================
ModuleList
hex_ast_create_module_list(Module module, ModuleList parent_list);


/*
 * Direct import statement
 */
typedef struct HexDirectImportStmt {
  ModuleList module_list;
  char *alias;
} *DirectImportStmt;


//===========================================================================
// hex_ast_create_direct_import_stmt()
// construct an AST node of type HexDirectImportStmt.
//===========================================================================
DirectImportStmt
hex_ast_create_direct_import_stmt(ModuleList module_list, char *alias);


/*
 * Relative import statement
 */
typedef struct HexRelativeImportStmt {
  ModuleList module_list;
  Module module;
  char *alias;
} *RelativeImportStmt;


//===========================================================================
// hex_ast_create_relative_import_stmt()
// construct an AST node of type HexRelativeImportStmt.
//===========================================================================
RelativeImportStmt
hex_ast_create_relative_import_stmt(ModuleList module_list, Module module, char *alias);


/*
 * Import statement
 */
typedef struct HexImportStmt {
  enum {
    import_stmt_type_direct,
    import_stmt_type_relative
  } import_stmt_type;
  union {
    DirectImportStmt import_stmt_direct_import_stmt;
    RelativeImportStmt import_stmt_relative_import_stmt;
  };
} *ImportStmt;


//===========================================================================
// hex_ast_create_import_stmt()
// construct an AST node of type HexImportStmt.
//===========================================================================
ImportStmt
hex_ast_create_import_stmt(int type, void *value);


/*
 * Elif statement
 */
typedef struct HexElifStmt {
  Expr elif_expr;
  Suite elif_suite;
} *ElifStmt;


//===========================================================================
// hex_ast_create_elif_stmt()
// construct an AST node of type HexElifStmt.
//===========================================================================
ElifStmt
hex_ast_create_elif_stmt(Expr elif_expr, Suite elif_suite);


/*
 * Elif group
 */
typedef struct HexElifGroup {
  ElifStmt elif_stmt;
  struct HexElifGroup *next;
} *ElifGroup;


//===========================================================================
// hex_ast_create_elif_group()
// construct an AST node of type HexElifGroup.
//===========================================================================
ElifGroup
hex_ast_create_elif_group(ElifStmt elif_stmt, ElifGroup parent_list);


/*
 * If statement
 */
typedef struct HexIfStmt {
  Expr if_expr;
  Suite if_suite;
  ElifGroup elif_group;
  Suite else_stmt;
} *IfStmt;


//===========================================================================
// hex_ast_create_if_stmt()
// construct an AST node of type HexIfStmt.
//===========================================================================
IfStmt
hex_ast_create_if_stmt(Expr if_expr, Suite if_suite, ElifGroup elif_group, Suite else_stmt);


/*
 * If statement simple
 */
typedef struct HexIfStmtSimple {
  enum {
    if_stmt_simple_type_expr,
    if_stmt_simple_type_return
  } if_stmt_simple_type;
  Expr expr;
  ExprList expr_list;
} *IfStmtSimple;


//===========================================================================
// hex_ast_create_if_stmt_simple()
// construct an AST node of type HexIfStmtSimple.
//===========================================================================
IfStmtSimple
hex_ast_create_if_stmt_simple(int type, Expr expr, ExprList expr_list);


/*
 * While statement
 */
typedef struct HexWhileStmt {
  Expr while_expr;
  Suite while_suite;
} *WhileStmt;


//===========================================================================
// hex_ast_create_while_stmt()
// construct an AST node of type HexWhileStmt.
//===========================================================================
WhileStmt
hex_ast_create_while_stmt(Expr while_expr, Suite while_suite);


/*
 * Iterable
 */
typedef struct HexIterable {
  enum {
    iterable_type_expr,
    iterable_type_initializer
  } iterable_type;
  union {
    Expr iterable_expr;
    Initializer iterable_initializer;
  };
} *Iterable;


//===========================================================================
// hex_ast_create_iterable()
// construct an AST node of type HexIterable.
//===========================================================================
Iterable
hex_ast_create_iterable(int type, void *value);


/*
 * For statement
 */
typedef struct HexForStmt {
  Iterable iterable;
  Expr expr;
  Expr where_expr;
  Suite suite;
} *ForStmt;


//===========================================================================
// hex_ast_create_for_stmt()
// construct an AST node of type HexForStmt.
//===========================================================================
ForStmt
hex_ast_create_for_stmt(Iterable iterable, Expr expr, Expr where_expr, Suite suite);


/*
 * Catch statement
 */
typedef struct HexCatchStmt {
  enum {
    catch_stmt_type_none,
    catch_stmt_type_identifier,
    catch_stmt_type_declaration
  } catch_stmt_type;
  union {
    char *catch_identifier;
    Declaration catch_declaration;
  };
  Suite catch_suite;
} *CatchStmt;


//===========================================================================
// hex_ast_create_catch_stmt()
// construct an AST node of type HexCatchStmt.
//===========================================================================
CatchStmt
hex_ast_create_catch_stmt(int type, void *value, Suite suite);


/*
 * Catch statement group
 */
typedef struct HexCatchStmtGroup {
  CatchStmt catch_stmt;
  struct HexCatchStmtGroup *next;
} *CatchStmtGroup;


//===========================================================================
// hex_ast_create_catch_stmt_group()
// construct an AST node of type HexCatchStmtGroup.
//===========================================================================
CatchStmtGroup
hex_ast_create_catch_stmt_group(CatchStmt catch_stmt, CatchStmtGroup parent_group);


/*
 * Finally statement
 */
typedef struct HexFinallyStmt {
  Suite finally_suite;
} *FinallyStmt;


//===========================================================================
// hex_ast_create_finally_stmt()
// construct an AST node of type HexFinallyStmt.
//===========================================================================
FinallyStmt
hex_ast_create_finally_stmt(Suite suite);


/*
 * Try statement
 */
typedef struct HexTryStmt {
  Suite try_suite;
  CatchStmtGroup catch_stmt_group;
  FinallyStmt finally_stmt;
} *TryStmt;


//===========================================================================
// hex_ast_create_try_stmt()
// construct an AST node of type HexTryStmt.
//===========================================================================
TryStmt
hex_ast_create_try_stmt(Suite try_suite, CatchStmtGroup catch_stmt_group, FinallyStmt finally_stmt);


/*
 * Compound statement
 */
struct HexCompoundStmt {
  enum {
    compound_stmt_type_if_stmt,             /* if statement */
    compound_stmt_type_while_stmt,          /* while statement */
    compound_stmt_type_try_stmt,            /* try statement */
    compound_stmt_type_for_stmt,            /* for statement */
    compound_stmt_type_func_def             /* function definition */
  } compound_stmt_type;
  union {
    IfStmt compound_stmt_if_stmt;           /* if statement */
    WhileStmt compound_stmt_while_stmt;     /* while statement */
    ForStmt compound_stmt_for_stmt;         /* for statement */
    TryStmt compound_stmt_try_stmt;         /* try statement */
    FuncDef compound_stmt_func_def;         /* function definition */
  };
};


//===========================================================================
// hex_ast_create_compound_stmt()
// construct an AST node of type HexCompoundStmt.
//===========================================================================
CompoundStmt
hex_ast_create_compound_stmt(int type, void *value);


/*
 * Return statement
 */
typedef struct HexReturnStmt {
  enum {
    return_stmt_type_none,
    return_stmt_type_expr_list
  } return_stmt_type;
  ExprList return_expr_list;
} *ReturnStmt;


//===========================================================================
// hex_ast_create_return_stmt()
// construct an AST node of type HexReturnStmt.
//===========================================================================
ReturnStmt
hex_ast_create_return_stmt(int type, ExprList expr_list);


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
    ReturnStmt control_simple_stmt_return_stmt;
  };
} *ControlSimpleStmt;


//===========================================================================
// hex_ast_create_control_simple_stmt()
// construct an AST node of type HexControlSimpleStmt.
//===========================================================================
ControlSimpleStmt
hex_ast_create_control_simple_stmt(int type, void *value);


/*
 * Simple statement
 */
typedef struct HexSimpleStmt {
  enum {
    simple_stmt_type_expr_list,                     /* expression list */
    simple_stmt_type_declaration,                   /* declaration */
    simple_stmt_type_assignment_stmt,               /* assignment statement */
    simple_stmt_type_import_stmt,                   /* import statement */
    simple_stmt_type_if_stmt_simple,                /* simple if statement */
    simple_stmt_type_func_declaration,              /* function declaration */
    simple_stmt_type_decorator                      /* decorator */
  } simple_stmt_type;
  union {
    ExprList simple_stmt_expr_list;                 /* expression list */
    Declaration simple_stmt_declaration;            /* declaration */
    AssignmentStmt simple_stmt_assignment_stmt;     /* assignment statement */
    ImportStmt simple_stmt_import_stmt;             /* import statement */
    IfStmtSimple simple_stmt_if_stmt_simple;        /* simple if statement */
    FuncDec simple_stmt_func_declaration;           /* function declaration */
    Decorator simple_stmt_decorator;                /* decorator */   
  };
} *SimpleStmt;


//===========================================================================
// hex_ast_create_simple_stmt()
// construct an AST node of type HexSimpleStmt.
//===========================================================================
SimpleStmt
hex_ast_create_simple_stmt(int type, void *value);


/*
 * Simple statement list
 */
struct HexSimpleStmtList {
  SimpleStmt simple_stmt;
  struct HexSimpleStmtList *next;
};


//===========================================================================
// hex_ast_create_simple_stmt_list()
// construct an AST node of type HexSimpleStmtList.
//===========================================================================
SimpleStmtList
hex_ast_create_simple_stmt_list(SimpleStmt simple_stmt, SimpleStmtList parent_list);


/*
 * Statement
 */
struct HexStmt {
  enum {
    stmt_type_simple_stmt_list,                       /* statement list */
    stmt_type_compound_stmt,                          /* compound statement */
    stmt_type_control_simple_stmt                     /* control_simple_stmt */
  } stmt_type;
  union {
    SimpleStmtList stmt_simple_stmt_list;             /* simple statement list */
    CompoundStmt stmt_compound_stmt;                  /* compound statement */
    ControlSimpleStmt stmt_control_simple_stmt;       /* control simple statement */
  };
};


//===========================================================================
// hex_ast_create_stmt()
// construct an AST node of type HexStmt.
//===========================================================================
Stmt
hex_ast_create_stmt(int type, void *value);


/*
 * Statement group
 */
typedef struct HexStmtGroup {
  Stmt stmt;
  struct HexStmtGroup *next;
} *StmtGroup;


//===========================================================================
// hex_ast_create_stmt_group()
// construct an AST node of type HexStmtGroup.
//===========================================================================
StmtGroup
hex_ast_create_stmt_group(Stmt stmt, StmtGroup parent_group);


/*
 * Suite
 */
struct HexSuite {
  StmtGroup stmt_group;
};


//===========================================================================
// hex_ast_create_suite()
// construct an AST node of type HexSuite.
//===========================================================================
Suite
hex_ast_create_suite(StmtGroup stmt_group);


#endif /* _AST_H_ */
