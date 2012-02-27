%{
#include <stdio.h>
%}

%token AND AS
%token BASE BOOL BREAK
%token CASE CATCH CHAR CLASS CONST CONTINUE COROUTINE
%token DEF DEFER DEFAULT DO DOUBLE
%token ELSE ENUM EXT FLOAT FOR IF IMPORT IN INT INTERFACE
%token LAZY LONG
%token NEW NOT
%token OR
%token PASS PRIVATE PROTECTED PUBLIC
%token RETURN
%token SHORT SIZEOF STACKALLOC STATIC STRING STRUCT SWITCH
%token TASK THIS THROW TRY TYPEOF UCHAR UINT ULONG USHORT
%token VIRTUAL VOLATILE
%token WHERE WHILE
%token FINALLY

%token IDENTIFIER

%token CHARACTER_LITERAL

%token STRING_LITERAL

%token COMMENT

%token DECIMALINTEGER BININTEGER OCTINTEGER HEXINTEGER FLOATINGNUM

%token PLUS_OP MINUS_OP MUL_OP DIV_OP MOD_OP

%token ASSIGN_OP PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN

%token NOT_BITWISE AND_BITWISE OR_BITWISE XOR_BITWISE SHIFTLEFT_BITWISE SHIFTRIGHT_BITWISE
%token NOT_ASSIGN AND_ASSIGN OR_ASSIGN XOR_ASSIGN SHIFTLEFT_ASSIGN SHIFTRIGHT_ASSIGN

%token EQ_OP GREATER_OP LESS_OP GEQ_OP LEQ_OP

%token INC_OP DEC_OP

%token LAMBDA_OP

%token ELLIPSIS

%token POND

%%

input: /* empty line */

INTEGER
  : DECIMALINTEGER
  | BININTEGER
  | OCTINTEGER
  | HEXINTEGER
  ;

LITERAL
  : STRING_LITERAL
  | INTEGER
  | FLOATINGNUM
  ;

unary_operator
  : PLUS_OP
  | MINUS_OP
  | INC_OP
  | DEC_OP
  | NOT_BITWISE
  | NOT
  ;

assignment_operator
  : ASSIGN_OP
  | ASSIGN_OP [NEW]
  | ASSIGN_OP [LAZY NEW]
  | MUL_ASSIGN
  | DIV_ASSIGN
  | MOD_ASSIGN
  | PLUS_ASSIGN
  | MINUS_ASSIGN
  | SHIFTLEFT_ASSIGN
  | SHIFTRIGHT_ASSIGN
  | NOT_ASSIGN
  | AND_ASSIGN
  | OR_ASSIGN
  | XOR_ASSIGN
  | [LAZY] NEW
  ;

/******************** expressions ********************/

/* 
 *  Primary expressions
 */
primary_expr
  : IDENTIFIER
  | STRING_LITERAL
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
  | postfix_expr '[' expr ']'
  | postfix_expr '(' ')'
  | postfix_expr '(' arg_expr_list ')'
  | postfix_expr '.' IDENTIFIER
  | postfix_expr INC_OP
  | postfix_expr DEC_OP
  ;

/*
 *  Argument expression list
 */
arg_expr_list
  : assignment_expr
  | assignment_expr AS IDENTIFIER
  | arg_expr_list ',' assignment_expr
  | arg_expr_list ',' assignment_expr AS IDENTIFIER
  ;

/*
 *  Unary expression
 */
unary_expr
  : postfix_expr
  | INC_OP unary_expr
  | DEC_OP unary_expr
  | unary_operator cast_expr
  | SIZEOF IDENTIDIER | TYPE
  | SIZEOF '(' IDENTIFIER | TYPE ')'
  ;

/*
 *  Cast expression
 */
cast_expr
  : unary_expr
  | '(' typename ')' cast_expr
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
  | shift_expr SHIFTLEFT_BITWISE additive_expr
  | shift_expr SHIFTRIGHT_BITWISE additive_expr
  ;

/*
 * Relational expression
 */
relational_expr
  : shift_expr
  | relational_expr LESS_OP shift_expr
  | relational_expr GREATER_OP shift_expr
  | relational_expr LE_OP shift_expr
  | relational_expr GE_OP shift_expr
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
  | and_expr '&' equality_expr
  ;

/*
 *  Bitwise XOR expression
 */
exclusive_or_expr
  : and_expr
  | exclusive_or_expr '^' and_expr
  ;

/*
 *  Bitwise OR expression
 */
inclusive_or_expr
  : exclusive_or_expr
  | inclusive_or_expr '|' exclusive_or_expr
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
  | expression IF logical_or_expr ELSE conditional_expr
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
  : arg_expr_list LAMBDA_OP expression
  ;

/* 
 *  expression
 */
expr
  : assignment_expr
  | expression ',' assignment_expr
  ;


/******************** declarations ********************/


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
  ;

/*
 *  Init declaration list
 */
init_declarator_list
  : init_declarator
  | init_declarator_list ',' init_declarator
  ;

/*
 *  Init declarator
 */
init_declarator
  : declarator
  | init_declarator_list ',' init_declarator
  ;

/*
 *  Declarator
 */
declarator
  : direct_declarator
  ;

direct_declarator
  : IDENTIFIER
  | '(' declarator ')'
  | direct_declarator '[' const_expr ']'
  | direct_declarator '[' ']'
  ;

/*
 *  Storage class specifier 
 */
storage_class_specifier
  : CONST
  | STATIC
  | VOLATILE
  ;

/*
 * Type specifier
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
 *
 */
paramter_type_list
  : parameter_list
  | parameter_list ',' ELIPSIS
  ;

parameter_list
  : parameter_declaration
  | parameter_list, parameter_declaration
  ;

parameter_declaration
  : declaration_specifiers declarator
  | declaration_specifiers abstract_declarator
  | declaration_specifiers;
  ;


/******************** initializers ********************/


initializer
  : assignment_expr
  | '[' list_initializer_list ']'               /* list */
  | '[' list_initializer_list ',' ']'           /* list */
  | '{' array_initializer_list '}'              /* array */
  | '{' array_initializer_list ',' '}'          /* array */
  | '(' tuple_initializer_list ')'              /* tuple */
  | '(' tuple_initializer_list ',' ')'          /* tuple */
  | '{' struct_initializer_list '}'             /* struct */
  | '{' struct_initializer_list ',' '}'         /* struct */
  | '(' '[' set_initializer_list  ']' ')'       /* set */
  | '(' '[' set_initializer_list ','  ']' ')'   /* set */
  | '{' map_initializer_list '}'                /* map */
  | '{' map_initializer_list ',' '}'            /* map */
  | '{' multimap_initializer_list '}'           /* multimap */
  | '{' multimap_initializer_list ',' '}'       /* multimap */
  ;

list_initializer_list
  : initializer
  | list_initializer_list ',' initializer
  ;

array_initializer_list
  : list_initializer_list
  | array_initializer_list ',' list_initializer_list
  ;

tuple_initializer_list
  : array_initializer_list
  | tuple_initializer_list ',' array_initializer_list
  ;

struct_initializer_list
  : IDENTIFIER '=' LITERAL
  | IDENTIFIER '=' assignment_expr
  | struct_initializer_list ',' IDENTIFIER '=' LITERAL
  | struct_initializer_list ',' IDENTIFIER '=' assignment_expr
  ;

set_initializer_list
  : tuple_initializer_list
  | set_initializer_list ',' tuple_initializer_list
  ;

map_initializer_list
  : LITERAL ':' LITERAL
  | LITERAL ':' IDENTIFIER
  | IDENTIFIER ':' LITERAL
  | IDENTIFIER ':' IDENTIFIER
  | map_initializer_list ',' LITERAL ':' LITERAL
  | map_initializer_list ',' LITERAL ':' IDENTIFIER
  | map_initializer_list ',' IDENTIFIER ':' LITERAL
  | map_initializer_list ',' IDENTIFIER ':' IDENTIFIER
  ;

multimap_initializer_list
  : LITERAL ':' '(' list_initializer ')'
  ;


/******************** statements ********************/


stmr
  : expr_stmt
  | selection_stmt
  | iteration_stmt
  | jump_stmt
  ;

expr_stmt
  : expr NEWLINE
  ;

if_stmt
  : IF expr : stmt (ELIF expr ':' stmt)* [ELSE ':' stmt]
  ;

for_stmt
  : FOR target_list IN expr [WHERE comp_expr] stmt
  ;

while_stmt
  : WHILE expr ':' stmt
  ;

do_stmt
  : DO stmt WHILE expr
  ;

try_stmt
  : TRY ':' stmt CATCH expr ':' (FINALLY stmt)
  ;

jump_statement
  : CONTINUE NEWLINE
  | BREAK NEWLINE
  | RETURN NEWLINE
  | RETURN expr NEWLINE
  ;

pass_stmt
  : PASS NEWLINE
  ;


%%

int yyerror(char* s) {
	printf("%s\n", s);
}

int main() {
	yyparse();
}