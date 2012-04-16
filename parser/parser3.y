%{

#include <stdio.h>
#include "ast3.h"

#define YYDEBUG 1
#define YYERROR_VERBOSE

yydebug = 1;
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
%token <string> ELIF ELSE EXT
%token <string> FLOAT FOR FROM
%token <string> IF IMPORT
%token <string> IN INT INTERFACE IS IS_NOT
%token <string> LAZY LOCK LONG
%token <string> NEW NOT
%token <string> OR
%token <string> PASS PRIVATE PROTECTED PUBLIC
%token <string> REF RETURN
%token <string> SHORT SIZEOF STACKALLOC STATIC STRING STRUCT SWITCH
%token <string> TASK THEN THIS THROW TRY TYPEOF
%token <string> UCHAR UINT ULONG UNLOCK USHORT
%token <string> VIRTUAL VOLATILE
%token <string> WEAKREF WHERE WHILE
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
%token <string>     ASSIGN_BITWISE_NOT ASSIGN_BITWISE_AND ASSIGN_BITWISE_OR ASSIGN_BITWISE_XOR ASSIGN_SHIFTLEFT ASSIGN_SHIFTRIGHT
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
%token <string>     AT

%token NEWLINE
%token INDENT
%token DEDENT

%left IDENTIFIER

%left LOCK UNLOCK
%left ELLIPSIS
%left ASSIGN_OP ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD ASSIGN_BITWISE_NOT ASSIGN_BITWISE_AND ASSIGN_BITWISE_OR ASSIGN_BITWISE_XOR ASSIGN_SHIFTLEFT ASSIGN_SHIFTRIGHT
%left WEAKREF
%left IF
%left THEN
%left ELSE
%left OR
%left AND
%left BITWISE_OR
%left BITWISE_XOR
%left BITWISE_AND
%left EQ_OP NEQ_OP NOT IS IS_NOT
%left GREATER_OP LESS_OP GEQ_OP LEQ_OP
%left BITWISE_SHIFTLEFT BITWISE_SHIFTRIGHT
%left PLUS_OP MINUS_OP
%left MUL_OP DIV_OP MOD_OP
%left BITWISE_NOT
%nonassoc DEC_OP INC_OP
%left LBRACKET RBRACKET
%left LPAREN RPAREN
%left LBRACE RBRACE
%right NEW DOT
%left COMMA
%right LAMBDA_OP

%nonassoc UMINUS

%right SUITE_PREC

%type <integer> INTEGER

%error-verbose
%debug

%{

%}

%%

input/* empty line */
  : NEWLINE
  | suite
  | stmt_group
  ;

suite
  : NEWLINE INDENT stmt_group NEWLINE DEDENT %prec SUITE_PREC
  | NEWLINE INDENT stmt_group NEWLINE
  ;

stmt_group
  : stmt
  | stmt_group NEWLINE stmt
  ;

stmt
  : simple_stmt_list
  | compound_stmt
  | control_simple_stmt
  ;

simple_stmt_list
  : simple_stmt
  | simple_stmt_list SEMICOLON simple_stmt
  ;

simple_stmt
  : expr_list_
  | declaration
  | assignment_stmt
  | import_stmt
  | func_declaration
  | if_stmt_simple
  | decorator
  ;

control_simple_stmt
  : return_stmt
  | break_stmt
  | continue_stmt
  ;

return_stmt
  : RETURN NEWLINE
  | RETURN expr_list_ NEWLINE
  ;

break_stmt
  : BREAK NEWLINE
  ;

continue_stmt
  : CONTINUE NEWLINE
  ;

compound_stmt
  : if_stmt
  | while_stmt
  | try_stmt
  | for_stmt
  | func_definition
  ;

try_stmt
  : TRY COLON suite catch_stmt_group
  | TRY COLON suite catch_stmt_group finally_stmt
  | TRY COLON suite finally_stmt
  ;

finally_stmt
  : FINALLY COLON suite
  ;

catch_stmt_group
  : catch_stmt
  | catch_stmt_group catch_stmt
  ;

catch_stmt
  : CATCH COLON suite
  | CATCH LPAREN declaration RPAREN COLON suite
  | CATCH LPAREN IDENTIFIER RPAREN COLON suite
  ;

while_stmt
  : WHILE expr COLON suite
  ;

for_stmt
  : FOR iterable IN expr COLON suite
  | FOR iterable IN expr WHERE expr COLON suite
  ;

iterable
  : expr
  | tuple_initializer
  ;

if_stmt_simple
  : IF expr COLON expr_list_
  | IF expr RETURN expr_list_
  ; 

if_stmt
  : IF expr COLON suite elif_group ELSE COLON suite
  | IF expr COLON suite ELSE COLON suite
  | IF expr COLON suite elif_group
  | IF expr COLON suite
  ;

elif_group
  : elif_stmt
  | elif_group elif_stmt
  ;

elif_stmt
  : ELIF expr COLON suite
  ;

import_stmt
  : direct_import_stmt
  | relative_import_stmt
  ;

relative_import_stmt
  : FROM module_list IMPORT module
  | FROM module_list IMPORT module AS IDENTIFIER
  ;

direct_import_stmt
  : IMPORT module_list
  | IMPORT module_list AS IDENTIFIER
  ;

module_list
  : module
  | module_list DOT module
  ;

module
  : IDENTIFIER
  ;

decorator
  : LBRACKET decorator_list RBRACKET
  ;

decorator_list
  : decorator_list_single
  | decorator_list COMMA decorator_list_single
  ;

decorator_list_single
  : compiler_property
  | attribute
  ;

compiler_property
  : POND IDENTIFIER ASSIGN_OP IDENTIFIER
  ;

attribute
  : AT expr
  ;

lambda_expr
  : parameter_list LAMBDA_OP LBRACKET simple_stmt_list RBRACKET
  | parameter_list LAMBDA_OP suite
  ;

func_definition
  : func_declaration COLON suite
  ;

func_declaration
  : DEF IDENTIFIER parameter_list
  | DEF IDENTIFIER LPAREN RPAREN
  | DEF IDENTIFIER IDENTIFIER parameter_list
  | DEF IDENTIFIER IDENTIFIER LPAREN RPAREN
  | DEF type_specifier IDENTIFIER parameter_list
  | DEF type_specifier IDENTIFIER LPAREN RPAREN
  | DEF type_qualifier_list IDENTIFIER parameter_list
  | DEF type_qualifier_list IDENTIFIER LPAREN RPAREN
  | DEF type_qualifier_list type_specifier IDENTIFIER parameter_list
  | DEF type_qualifier_list type_specifier IDENTIFIER LPAREN RPAREN
  | DEF type_qualifier_list IDENTIFIER IDENTIFIER parameter_list
  | DEF type_qualifier_list IDENTIFIER IDENTIFIER LPAREN RPAREN
  ;

assignment_stmt_list
  : assignment_stmt
  | assignment_stmt_list COMMA assignment_stmt
  ;

assignment_stmt
  : declaration assignment_list
  | expr_list_ assignment_list
  ;

assignment_list
  : assignment
  | assignment_list assignment
  ;

assignment
  : assignment_operator expr
  | assignment_operator initializer
  | assignment_operator lambda_expr
  ;

expr
  : LITERAL
  | IDENTIFIER
  | expr tuple_initializer
  | IDENTIFIER tuple_initializer
  | expr list_initializer
  | IDENTIFIER list_initializer
  | expr LPAREN RPAREN
  | IDENTIFIER LPAREN RPAREN
  | expr LBRACKET RBRACKET
  | IDENTIFIER LBRACKET RBRACKET
  | expr INC_OP
  | expr DEC_OP
  | INC_OP expr
  | DEC_OP expr
  | expr MUL_OP expr
  | expr DIV_OP expr
  | expr MOD_OP expr
  | expr PLUS_OP expr
  | expr MINUS_OP expr
  | MINUS_OP expr %prec UMINUS
  | expr BITWISE_SHIFTLEFT expr
  | expr BITWISE_SHIFTRIGHT expr
  | expr LESS_OP expr
  | expr GREATER_OP expr
  | expr LEQ_OP expr
  | expr GEQ_OP expr
  | expr IS expr
  | expr IS_NOT expr
  | expr EQ_OP expr
  | expr NEQ_OP expr
  | expr BITWISE_AND expr
  | expr BITWISE_XOR expr
  | expr BITWISE_OR expr
  | expr AND expr
  | expr OR expr
  | expr ELLIPSIS expr
  | IF expr THEN expr ELSE expr
  | expr DOT IDENTIFIER
  | WEAKREF expr
  | NOT expr
  | LOCK expr
  | UNLOCK expr
  | BITWISE_NOT expr
  | LPAREN IDENTIFIER RPAREN expr
  | LPAREN type_specifier RPAREN expr
  | LPAREN expr RPAREN
  | THIS
  | BASE
  ;

expr_list_
  : expr
  | expr_list_ COMMA expr
  ;

initializer
 : list_initializer
 | array_initializer
 | struct_initializer
 | tuple_initializer
 | set_initializer
 | map_multimap_initializer
 ;

map_multimap_initializer
  : LBRACE map_multimap_initializer_list RBRACE
  ;

map_multimap_initializer_list
  : map_multimap_initializer_single
  | map_multimap_initializer_list COMMA map_multimap_initializer_single
  ;

map_multimap_initializer_single
  : expr COLON expr
  ;

struct_initializer
  : LBRACE assignment_stmt_list RBRACE
  ;

set_initializer
  : LBRACKET LPAREN expr_list_ RPAREN RBRACKET
  ;

array_initializer
  : LBRACE expr_list_ RBRACE
  ;

tuple_initializer
  : LPAREN expr_list_ RPAREN
  ;

list_initializer
  : LBRACKET expr_list_ RBRACKET
  ;

parameter_list
  : LPAREN parameter_list_core RPAREN
  | LPAREN parameter_list_core COMMA ELLIPSIS RPAREN
  ;

parameter_list_core
  : parameter
  | parameter_list_core COMMA parameter
  ;

parameter
  : type_qualifier_list type_specifier IDENTIFIER
  | type_qualifier_list type_specifier IDENTIFIER AS IDENTIFIER
  | type_qualifier_list IDENTIFIER
  | type_qualifier_list IDENTIFIER AS IDENTIFIER
  | type_specifier IDENTIFIER
  | type_specifier IDENTIFIER AS IDENTIFIER
  | IDENTIFIER IDENTIFIER
  | IDENTIFIER IDENTIFIER AS IDENTIFIER
  | IDENTIFIER
  | IDENTIFIER AS IDENTIFIER
  | REF parameter
  ;

declaration
  : type_qualifier_list type_specifier expr_list_
  | type_qualifier_list expr_list_
  | type_specifier expr_list_
  | IDENTIFIER expr_list_
  | declaration AS IDENTIFIER
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
  ;

type_qualifier_list
  : type_qualifier
  | type_qualifier_list type_qualifier
  ;

type_qualifier
  : CONST
  | VOLATILE
  | STATIC
  ;

assignment_operator
  : ASSIGN_OP
  | ASSIGN_OP DEFER
  | ASSIGN_OP NEW
  | ASSIGN_OP LAZY NEW
  | ASSIGN_OP STACKALLOC NEW
  | ASSIGN_OP STACKALLOC LAZY NEW
  | ASSIGN_MUL
  | ASSIGN_DIV
  | ASSIGN_MOD
  | ASSIGN_PLUS
  | ASSIGN_MINUS
  | ASSIGN_SHIFTLEFT
  | ASSIGN_SHIFTRIGHT
  | ASSIGN_BITWISE_NOT
  | ASSIGN_BITWISE_AND
  | ASSIGN_BITWISE_OR
  | ASSIGN_BITWISE_XOR
  ;

LITERAL
  : CHARACTER_LITERAL
  | STRING_LITERAL
  | INTEGER
  | FLOATINGNUM
  ;

INTEGER
  : DECIMALINTEGER
  | BININTEGER
  | OCTINTEGER
  | HEXINTEGER
  ;

%%


int yyerror(char* s) {
  printf("[%d] %s\n", __LINE__, s);
}

/* Return 1 stops at EOF,
 * return 0 continues reading. 
 */
int yywrap() {
  return 1;
}