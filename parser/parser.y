%{
#include <stdio.h>
#include "ast.h"

#define YYERROR_VERBOSE
#define TRACE printf("reduce at line %d\n", __LINE__);
%}

%union {
  char character;
  char* string;
  int integer;
  double floating;
};

%token <string> AND AS
%token <string> BASE BOOL BREAK
%token <string> CASE CATCH CHAR CLASS CONST CONTINUE COROUTINE
%token <string> DEF DEFER DEFAULT DO DOUBLE
%token <string> ELIF ELSE ENUM EXT
%token <string> FLOAT FOR FROM
%token <string> IF IMPORT
%token <string> IN INT INTERFACE
%token <string> LAZY LONG
%token <string> NEW NOT
%token <string> OR
%token <string> PASS PRIVATE PROTECTED PUBLIC
%token <string> RETURN
%token <string> SHORT SIZEOF STACKALLOC STATIC STRING STRUCT SWITCH
%token <string> TASK THIS THROW TRY TYPEOF UCHAR UINT ULONG USHORT
%token <string> VIRTUAL VOLATILE
%token <string> WHERE WHILE
%token <string> FINALLY

%token <string>     IDENTIFIER
%token <character>  CHARACTER_LITERAL
%token <string>     STRING_LITERAL
%token <string>     COMMENT
%token <integer>    DECIMALINTEGER BININTEGER OCTINTEGER HEXINTEGER
%token <floating>   FLOATINGNUM
%token <string>     PLUS_OP MINUS_OP MUL_OP DIV_OP MOD_OP
%token <string>     ASSIGN_OP ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD
%token <string>     BITWISE_NOT BITWISE_AND BITWISE_OR BITWISE_XOR BITWISE_SHIFTLEFT BITWISE_SHIFTRIGHT
%token <string>     ASSIGN_NOT ASSIGN_AND ASSIGN_OR ASSIGN_XOR ASSIGN_SHIFTLEFT ASSIGN_SHIFTRIGHT
%token <string>     EQ_OP NEQ_OP GREATER_OP LESS_OP GEQ_OP LEQ_OP
%token <string>     INC_OP DEC_OP
%token <string>     LAMBDA_OP
%token <string>     DOT
%token <string>     COMMA
%token <string>     COLON
%token <string>     SEMICOLON
%token <string>     LPAREN
%token <string>     RPAREN
%token <string>     LBRACKET
%token <string>     RBRACKET
%token <string>     LBRACE
%token <string>     RBRACE
%token <string>     ELLIPSIS
%token <string>     POND
%token <string>     NEWLINE
%token <string>     INDENT
%token <string>     DEDENT

%type <integer> INTEGER

%error-verbose
%%

input: /* empty line */
  ;

INTEGER
  : DECIMALINTEGER
  | BININTEGER
  | OCTINTEGER
  | HEXINTEGER
  ;

LITERAL
  : CHARACTER_LITERAL
  | STRING_LITERAL
  | INTEGER
  | FLOATINGNUM
  ;

unary_operator
  : PLUS_OP
  | MINUS_OP
  | INC_OP
  | DEC_OP
  | BITWISE_NOT
  | NOT
  ;

assignment_operator
  : ASSIGN_OP
  | ASSIGN_OP NEW
  | ASSIGN_OP LAZY NEW
  | ASSIGN_MUL
  | ASSIGN_DIV
  | ASSIGN_MOD
  | ASSIGN_PLUS
  | ASSIGN_MINUS
  | ASSIGN_SHIFTLEFT
  | ASSIGN_SHIFTRIGHT
  | ASSIGN_NOT
  | ASSIGN_AND
  | ASSIGN_OR
  | ASSIGN_XOR
  ;

/*************************************************************************
 ******************************* expressions *****************************
 *************************************************************************/

/* 
 *  Primary expressions
 */
primary_expr
  : IDENTIFIER
  | LITERAL
  | expr
  ;

/*
 *  Postfix expression
 *
 *  Postfix expression consist of primary expressions in which
 *  postfix operators follow a primary expression. The postfix
 *  operator. The postfix operators are listed below:
 *
 *  Operator Name                |         Operator Notation
 *  _____________________________|____________________________
 *                               |
 *  Subscript operator           |         []
 *  Function call operators      |         ()
 *  Member access                |         .
 *  Postfix increment operator   |         ++
 *  Postfix decrement operator   |         --
 *
 */
postfix_expr
  : primary_expr
  | postfix_expr LBRACKET expr RBRACKET
  | postfix_expr LPAREN RPAREN
  | postfix_expr LPAREN arg_expr_list RPAREN
  | postfix_expr DOT IDENTIFIER
  | postfix_expr INC_OP
  | postfix_expr DEC_OP
  ;

/*
 *  Argument expression list
 */
arg_expr_list
  : assignment_expr
  | assignment_expr AS IDENTIFIER
  | arg_expr_list COMMA assignment_expr
  | arg_expr_list COMMA assignment_expr AS IDENTIFIER
  ;

/*
 *  Unary expression
 */
unary_expr
  : postfix_expr
  | INC_OP unary_expr
  | DEC_OP unary_expr
  | unary_operator cast_expr
  | SIZEOF IDENTIFIER
  | SIZEOF LPAREN IDENTIFIER RPAREN
  ;

/*
 *  Cast expression
 */
cast_expr
  : unary_expr
  | LPAREN IDENTIFIER RPAREN cast_expr
  ;

/*
 *  Multiplicative expression
 */
multiplicative_expr
  : cast_expr
  | multiplicative_expr MUL_OP cast_expr
  | multiplicative_expr DIV_OP cast_expr
  | multiplicative_expr MOD_OP cast_expr
  ;

/*
 *  Additive expression
 */
additive_expr
  : multiplicative_expr
  | additive_expr PLUS_OP multiplicative_expr
  | additive_expr MINUS_OP multiplicative_expr
  ;

/*
 * Shift expression
 */
shift_expr
  : additive_expr
  | shift_expr BITWISE_SHIFTLEFT additive_expr
  | shift_expr BITWISE_SHIFTRIGHT additive_expr
  ;

/*
 * Relational expression
 */
relational_expr
  : shift_expr
  | relational_expr LESS_OP shift_expr
  | relational_expr GREATER_OP shift_expr
  | relational_expr LEQ_OP shift_expr
  | relational_expr GEQ_OP shift_expr
  ;

/*
 *  Equality expression
 */
equality_expr
  : relational_expr
  | equality_expr EQ_OP relational_expr
  | equality_expr NEQ_OP relational_expr
  ;

/*
 *  Bitwise AND expression
 */
and_expr
  : equality_expr
  | and_expr BITWISE_AND equality_expr
  ;

/*
 *  Bitwise XOR expression
 */
exclusive_or_expr
  : and_expr
  | exclusive_or_expr BITWISE_XOR and_expr
  ;

/*
 *  Bitwise OR expression
 */
inclusive_or_expr
  : exclusive_or_expr
  | inclusive_or_expr BITWISE_OR exclusive_or_expr
  ;

/*
 *  Logical AND expression
 */
logical_and_expr
  : inclusive_or_expr
  | logical_and_expr AND inclusive_or_expr
  ;

/*
 *  Logical OR expression
 */
logical_or_expr
  : logical_and_expr
  | logical_or_expr OR logical_and_expr
  ;

/*
 *  Conditional expression
 */
conditional_expr
  : logical_or_expr
  | expr IF logical_or_expr ELSE conditional_expr
  ;

/*
 * Constant expression
 */
const_expr
  : conditional_expr
  ;

/*
 *  Assignment expression
 */
assignment_expr
  : conditional_expr
  | unary_expr assignment_operator assignment_expr
  ;

/*
 *  Lambda expression
 */
lambda_expr
  : parameter_list LAMBDA_OP expr
  ;

/* 
 *  expression
 */
expr
  : assignment_expr
  | expr COMMA assignment_expr
  ;

/*
 * Expression list
 */
expr_list
  : expr
  | expr_list COMMA expr
  ;


/*************************************************************************
 ******************************* declarations ****************************
 *************************************************************************/


/*
 *  Declaration
 */
declaration
  : declaration_specifiers NEWLINE
  | declaration_specifiers init_declarator_list NEWLINE
  ;

/*
 *  Declaration specifiers
 */
declaration_specifiers
  : storage_class_specifier
  | storage_class_specifier declaration_specifiers
  | type_specifier
  | type_specifier declaration_specifiers
  | type_qualifier
  | type_qualifier declaration_specifiers
  ;

/*
 *  Init declaration list
 */
init_declarator_list
  : init_declarator
  | init_declarator_list COMMA init_declarator
  ;

/*
 *  Init declarator
 */
init_declarator
  : declarator
  | init_declarator_list COMMA init_declarator
  ;

/*
 *  Declarator
 */
declarator
  : direct_declarator
  ;

/*
 *  Direct declarator
 */
direct_declarator
  : IDENTIFIER
  | LPAREN declarator RPAREN
  | direct_declarator LBRACKET const_expr RBRACKET
  | direct_declarator LBRACKET RBRACKET
  ;

/*
 *  Storage class specifier 
 */
storage_class_specifier
  : STATIC
  ;

/*
 *  Type specifier
 */
type_specifier
  : CHAR
  | SHORT
  | INT
  | LONG
  | FLOAT
  | DOUBLE
  | UCHAR
  | USHORT
  | UINT
  | ULONG
  | IDENTIFIER
  ;

/*
 *  Type qualifier
 */
type_qualifier
  : CONST
  | VOLATILE
  ;

/*
 *  Type qualifier list
 */
 type_qualifier_list
  : type_qualifier
  | type_qualifier_list type_qualifier
  ;

/*
 *  Identifier list
 */
identifier_list
  : IDENTIFIER
  | identifier_list COMMA IDENTIFIER
  ;

/*
 * Parameter type list
 */
paramter_type_list
  : parameter_list
  | parameter_list COMMA ELLIPSIS
  ;

/*
 *  Parameter list
 */
parameter_list
  : parameter_declaration
  | parameter_list COMMA parameter_declaration
  ;

/*
 *  Parameter declaration
 */
parameter_declaration
  : IDENTIFIER
  | declaration_specifiers declarator
  ;


/*************************************************************************
 ******************************* initializers ****************************
 *************************************************************************/

/*
 *  Initializer
 *
 *  Initializers for basic data structures supported by HEX.
 *
 *  Examples of these basic structures:
 *
 *  Type          |   Literal Example                                               |       Description
 *  ______________|_________________________________________________________________|________________________________________
 *                |                                                                 |
 *  list          |   ["HEX", 5, 'e']                                               |   Mutable array-type list
 *  array         |   int numbers[5] = {1,2,3,4,5}                                  |   Immutable sequence of data
 *  tuple         |   ("HEX", 5, 'e')                                               |   Immutable tuple
 *  struct        |   {name = "HEX", version = 0.1}                                 |   Mutable struct
 *  set           |   [("HEX", 5, 'e')]                                             |   Unordered collection of unique data
 *  map           |   {"apple" : "sweet", "orange" : "sour"}                        |   Key-value dictionary
 *  multimap      |   {"apple" : ("sweet", "red"), "orange" : ("sour", "orange")}   |   Single key multiple value dictionary 
 */
initializer
  : assignment_expr
  | LBRACKET list_initializer_list RBRACKET                       /* list */
  | LBRACKET list_initializer_list COMMA RBRACKET                 /* list */
  | LBRACE array_initializer_list RBRACE                          /* array */
  | LBRACE array_initializer_list COMMA RBRACE                    /* array */
  | LPAREN tuple_initializer_list RPAREN                          /* tuple */
  | LPAREN tuple_initializer_list COMMA RPAREN                    /* tuple */
  | LBRACE struct_initializer_list RBRACE                         /* struct */
  | LBRACE struct_initializer_list COMMA RBRACE                   /* struct */
  | LPAREN LBRACKET set_initializer_list  RBRACKET RPAREN         /* set */
  | LPAREN LBRACKET set_initializer_list COMMA RBRACKET RPAREN    /* set */
  | LBRACE map_initializer_list RBRACE                            /* map */
  | LBRACE map_initializer_list COMMA RBRACE                      /* map */
  | LBRACE multimap_initializer_list RBRACE                       /* multimap */
  | LBRACE multimap_initializer_list COMMA RBRACE                 /* multimap */
  ;

/*
 *  List initializer list
 */
list_initializer_list
  : initializer
  | list_initializer_list COMMA initializer
  ;

/*
 *  Array initializer list
 */
array_initializer_list
  : list_initializer_list
  | array_initializer_list COMMA list_initializer_list
  ;

/*
 *  Tuple initializer list
 */
tuple_initializer_list
  : array_initializer_list
  | tuple_initializer_list COMMA array_initializer_list
  ;

/*
 *  Struct initializer list
 */
struct_initializer_list
  : IDENTIFIER ASSIGN_OP LITERAL
  | IDENTIFIER ASSIGN_OP initializer
  | struct_initializer_list COMMA IDENTIFIER '=' LITERAL
  | struct_initializer_list COMMA IDENTIFIER '=' initializer
  ;

/*
 *  Set initializer list
 */
set_initializer_list
  : tuple_initializer_list
  | set_initializer_list COMMA tuple_initializer_list
  ;

/*
 *  Map initializer list
 */
map_initializer_list
  : LITERAL COLON LITERAL
  | LITERAL COLON set_initializer_list
  | IDENTIFIER COLON LITERAL
  | IDENTIFIER COLON set_initializer_list
  | map_initializer_list COMMA LITERAL COLON LITERAL
  | map_initializer_list COMMA LITERAL COLON set_initializer_list
  | map_initializer_list COMMA IDENTIFIER COLON LITERAL
  | map_initializer_list COMMA IDENTIFIER COLON set_initializer_list
  ;

/*
 *  Multimap initializer list
 */
multimap_initializer_list
  : LITERAL COLON LPAREN RPAREN
  | LITERAL COLON LPAREN map_initializer_list RPAREN
  | IDENTIFIER COLON LPAREN RPAREN
  | IDENTIFIER COLON LPAREN map_initializer_list RPAREN
  | multimap_initializer_list COMMA LITERAL COLON LPAREN RPAREN
  | multimap_initializer_list COMMA LITERAL COLON LPAREN map_initializer_list RPAREN
  | multimap_initializer_list COMMA IDENTIFIER COLON LPAREN RPAREN
  | multimap_initializer_list COMMA IDENTIFIER COLON set_initializer_list
  ;


/*************************************************************************
 ******************************* statements ******************************
 *************************************************************************/

/*
 *  Statement group
 */
stmt_group
  : stmt
  | stmt_group stmt
  ;

/*
 *  Suite
 */
suite
  : stmt_list NEWLINE
  | NEWLINE INDENT stmt_group DEDENT
  ;

/*
 *  Statement
 */
stmt
  : stmt_list NEWLINE
  | compound_stmt
  ;

/*
 *  Statement list
 */
stmt_list
  : simple_stmt
  | stmt_list SEMICOLON simple_stmt
  ;

/*
 *  Simple statement
 */
simple_stmt
  : expr_stmt
  | assignment_expr
  | pass_stmt
  | return_stmt
  | break_stmt
  | continue_stmt
  | import_stmt
  ;

/*
 * Module
 */
module
  : IDENTIFIER
  | IDENTIFIER DOT module
  ;

/*
 * Relative module
 */
relative_module
  : module
  ;

/*
 * Import alias
 */
import_alias
  : module
  | module AS IDENTIFIER 
  ;

/*
 * Import alias list
 */
import_alias_list
  : import_alias
  | import_alias_list COMMA import_alias
  ;

/*
 * Import statement
 */
import_stmt
  : IMPORT import_alias_list
  | FROM relative_module IMPORT import_alias_list
  ;

/*
 *  Expression statement
 */
expr_stmt
  : expr_list
  ;

/*
 * Elif statment group
 */
elif_group
  : ELIF expr COLON suite
  | elif_group ELIF expr COLON suite
  ;

/*
 * If statement
 */
if_stmt
  : IF expr COLON suite elif_group
  | IF expr COLON suite elif_group ELSE COLON suite
  ;

/*
 *
 */
target_list
  :
  ;

/*
 *  For statement
 */
for_stmt
  : FOR target_list IN expr_list suite
  : FOR target_list IN expr_list WHERE equality_expr suite
  ;

/*
 *  While statement
 */
while_stmt
  : WHILE expr COLON suite
  ;

/*
 *  Do-while statement
 */
dowhile_stmt
  : DO suite WHILE expr
  ;

/*
 * Catch statement
 */
catch_stmt
  : CATCH expr COLON suite
  ;

/*
 * Catch statement group
 */
catch_stmt_group
  : catch_stmt
  | catch_stmt_group catch_stmt
  ;

/*
 * Finally statement
 */
finally_stmt
  : FINALLY COLON suite
  ;

/*
 *  Try statement
 */
try_stmt
  : TRY COLON suite catch_stmt_group
  : TRY COLON suite catch_stmt_group 
  | TRY COLON suite finally_stmt
  ;

/*
 *  Return statement
 */
return_stmt
  : RETURN NEWLINE
  | RETURN expr_list NEWLINE
  ;

/*
 * Continue statement
 */
continue_stmt
  : CONTINUE NEWLINE
  ;

/*
 * Break statement
 */
break_stmt
  : BREAK NEWLINE
  ;

/*
 *  Pass statement
 */
pass_stmt
  : PASS NEWLINE
  ;

/*
 * Return statement
 */
return_stmt
  : RETURN expr_list
  ;

/*
 * Compound statement
 */
compound_stmt
  : if_stmt
  | while_stmt
  | dowhile_stmt
  | try_stmt
  | func_def
  ;


/*************************************************************************
 ******************************* function ********************************
 *************************************************************************/


/*
 *  Function declaration specifier
 */
func_declaration_specifiers
  : declaration_specifiers
  ;

/*
 *  function_definition
 */
func_def
  : DEF func_declaration_specifiers IDENTIFIER LPAREN parameter_list RPAREN COLON suite
  ;


%%

int yyerror(char* s) {
	printf("%s\n", s);
}

/* Return 1 stops at EOF,
 * return 0 continues reading. 
 */
int yywrap() {
  return 1;
}

int main() {
	yyparse();
}