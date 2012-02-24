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
  : STRINGLITERAL
  | INTEGER
  | FLOATINGNUM
  ;

ELLIPSIS
  : "..."
  ;

primary_expr
  : IDENTIFIER
  | LITERAL 
  ;

postfix_expre
  : primary_expr
  | postfix_expr '[' expr ']'
  | postfix_expr '(' ')'
  | postfix_expr '(' arg_expr_list ')'
  | postfix_expr '.' IDENTIFIER
  | postfix_expr INC_OP
  | postfix_expr DEC_OP
  ;

arg_expr_list
  : assignment_expr
  | arg_expr_list ',' assignment_exprs
  ;

unary_expr
  : postfix_expr
  | INC_OP unary_expr
  | DEC_OP unary_expr
  | unary_operator cast_expr
  | SIZEOF (IDENTIFIER | TYPE)
  ;

unary_operator
  : AND_BITWISE
  | MUL_OP
  | PLUS_OP
  | MINUS_OP
  | NOT_BITWISE
  | NOT
  ;

cast_expr
  : unary_expr
  | '(' typename ')' cast_expr
  ;

multiplicative_expr
  : cast_expr
  | multiplicative_expr MUL_OP cast_expr
  | multiplicative_expr DIV_OP cast_expr
  | multiplicative_expr MOD_OP cast_expr
  ;

additive_expr
  : multiplicative_expr
  | additive_expr PLUS_OP multiplicative_expr
  | additive_expr MINUS_OP multiplicative_expr
  ;

shift_expr
  : additive_expr
  | shift_expr SHIFTLEFT_BITWISE additive_expr
  | shift_expr SHIFTRIGHT_BITWISE additive_expr
  ;

relational_expr
  : shift_expr
  | relational_expr LESS_OP shift_expr
  | relational_expr GREATER_OP shift_expr
  | relational_expr LE_OP shift_expr
  | relational_expr GE_OP shift_expr
  ;

equality_expr
  : relational_expr
  | equality_expr EQ_OP relational_expr
  | equality_expr NEQ_OP relational_expr
  ;

and_expr
  : equality_expr
  | and_expr '&' equality_expr
  ;

exclusive_or_expr
  : and_expr
  | exclusive_or_expr '^' and_expr
  ;

inclusive_or_expr
  : exclusive_or_expr
  | inclusive_or_expr '|' exclusive_or_expr
  ;

logical_and_expr
  : inclusive_or_expr
  | logical_and_expr AND inclusive_or_expr
  ;

logical_or_expr
  : logical_and_expr
  | logical_or_expr OR logical_and_expr
  ;

conditional_expr
  : logical_or_expr
  | expression IF logical_or_expr ELSE conditional_expr
  ;

assignment_expr
  : conditional_expr
  | unary_expr assignment_operator assignment_expr
  ;

assignment_operator
  : ASSIGN_OP
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

expr
  : assignment_expr
  | expression ',' assignment_expr
  ;

declaration
  : declaration_specifiers ';'
  | declaration_specifiers init_declarator_list ';'
  ;

declaration_specifiers
  : storage_class_specifier
  | storage_class_specifier declaration_specifiers
  | [type_specifier]
  | [type_specifier] declaration_specifiers
  | type_qualifier
  | type_qualifier declaration_specifiers
  ;

init_declarator_list
  : init_declarator
  | init_declarator_list ',' init_declarator
  ;

storage_class_specifier
  : CONST
  | STATIC
  | VOLATILE
  ;

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

/* initializers */

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
  | '(' '[' list_initializer_list  ']' ')'      /* set */
  | '(' '[' list_initializer_list ','  ']' ')'  /* set */
  | '{' map_initializer_list '}'                /* map */
  | '{' map_initializer_list ',' '}'            /* map */
  | '[' multimap_initializer_list ']'           /* multimap */
  | '[' multimap_initializer_list ',' ']'       /* multimap */
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

while_stmt
  : WHILE expr ':' suite [ELSE ':' suite]
  ;

for_stmt
  : FOR target_list IN expr_list ':' suite [WHERE comp_expr] [ELSE ':' suite]
  ;


try_stmt
  : try1_stmt | try2_stmt

try1_stmt
  : TRY ':' suite (CATCH [expr [(AS | ',') target]] ':' suite)+ [ELSE : suite]
  ;

try2_stmt
  : TRY ':' suite FINALLY ':' suite
  ;

jump_statement
  : CONTINUE NEWLINE
  | BREAK NEWLINE
  | RETURN NEWLINE
  | RETURN expr NEWLINE
  ;

labeled_stmt
  : CASE const_expr ':'  stmt
  | DEFAULT ':' stmt
  ;

pass_stmt
  : PASS
  ;

lambda_form
  : parameter_list "=>" expression
  ;











%%

int yyerror(char* s) {
	printf("%s\n", s);
}

int main() {
	yyparse();
}