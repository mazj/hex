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

%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN

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

and_expr
  : shift_expr
  | and_expr '&' shift_expr
  ;

xor_expr
  : and_expr | and_expr '^' and_expr
  ;

or_expr
  : xor_expr
  | or_expr '|' xor_expr 
  ;

comp_op
  : EQ_OP
  | NEQ_OP
  | LESS_OP
  | GREATER_OP 
  | GEQ_OP
  | LEQ_OP
  | IS [NOT]
  | [NOT] IN
  ;

assign_op
  : ASSIGN
  | PLUS_ASSIGN
  | MINUS_ASSIGN
  | MUL_ASSIGN
  | DIV_ASSIGN
  | MOD_ASSIGN
  ;


/* statements */

initializer
  : literal ',' literal
  ;

list_initializer_list
  : '[' initializer ']'
  ;

array_initializer_list
  : '{' initializer '}'
  ;

tuple_initializer_list
  : '(' initializer ')'
  ;

struct_initializer
  : literal '=' literal
  ;

struct_initializer_list
  : '{' struct_initializer '}'

set_initializer_list
  : '(' list_initializer_list ')'

map_initializer
  : literal ':' literal
  ;

map_initializer_list
  : '{' map_initializer '}'
  ;

multiset_initializer
  : '{' literal ',' set_initializer '}'
  | '{' '}'
  ;

multiset_initializer_list
  : '(' multset_initializer ')'
  ;

initializer_list
  : assignment_expr
  | list_initializer_list       /* list initialization */
  | array_initializer_list      /* array initialization */
  | tuple_initializer_list      /* tuple initialization */
  | struct_initializer_list     /* struct initialization */
  | set_initializer_list        /* set initialization */
  | map_initializer_list        /* map initialization */
  | multimap_initializer_list   /* multimap initialization */ 
  ;

stmr
  : expr_stmt
  | selection_stmt
  | iteration_stmt
  | jump_stmt

expr_stmt
  : expr NEWLINE
  ;

selection_stmt
  : IF '(' expr ')' stmt
  | IF '(' expr ')' stmr ELSE stmt
  | SWITCH '(' expr ')' stmr
  ;

iteration_stmt
  : FOR '(' expr_stmt expr_stmr ')' stmr
  | FOR '(' expr_stmt expr_stmr ')' WHERE  expr stmr
  | FOR '(' expr_stmt expr_stmr expr ')' WHERE  expr stmr
  | DO stmr WHILE '(' expr ')'
  ;

jump_statement
  : CONTINUE
  | BREAK
  | RETURN
  | RETURN expr
  ;

labeled_stmt
  : CASE const_expr ':'  stmt
  | DEFAULT ':' stmt
  ;

pass_stmt
  : PASS
  ;

%%

int yyerror(char* s) {
	printf("%s\n", s);
}

int main() {
	yyparse();
}