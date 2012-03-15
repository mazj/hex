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
%token <string>     NEWLINE
%token <string>     INDENT
%token <string>     DEDENT


%left ASSIGN_BITWISE_NOT ASSIGN_BITWISE_AND ASSIGN_BITWISE_OR ASSIGN_BITWISE_XOR ASSIGN_SHIFTLEFT ASSIGN_SHIFTRIGHT ASSIGN_OP ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD
%left COMMA
%left IDENTIFIER
%left IF
%left LESE
%left OR
%left AND
%left BITWISE_OR 
%left BITWISE_XOR
%left BITWISE_AND
%left EQ_OP NEQ_OP
%left GREATER_OP LESS_OP GEQ_OP LEQ_OP
%left BITWISE_SHIFTLEFT BITWISE_SHIFTRIGHT
%left PLUS_OP MINUS_OP
%left MUL_OP DIV_OP MOD_OP
%left LBRACKET RBRACKET
%right NOT BITWISE_NOT DEC_OP INC_OP
%right NEW DOT
%nonassoc conditional
%nonassoc forstmt

%type <integer> INTEGER

%error-verbose
%%

input
  : NEWLINE /* empty line */
  | suite
  ;

suite
  : NEWLINE INDENT stmt_group DEDENT
  ;

stmt_group
  : stmt NEWLINE
  | stmt_group stmt
  ;

stmt
  : stmt_list NEWLINE
  | compound_stmt
  ;

stmt_list
  : simple_stmt
  | stmt_list SEMICOLON simple_stmt
  ;

simple_stmt
  : expr_stmt
  | assignment_stmt
  | pass_stmt
  | return_stmt
  | break_stmt
  | continue_stmt
  | import_stmt
  | func_declaration
  ;

return_stmt
  : RETURN expr_list
  ;

pass_stmt
  : PASS NEWLINE
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
  | dowhile_stmt
  | try_stmt
  | for_stmt
  | func_definition
  ;

return_stmt
  : RETURN NEWLINE
  | RETURN expr_list NEWLINE
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
  : CATCH declaration COLON suite
  ;

dowhile_stmt
  : DO suite WHILE expr
  ;

while_stmt
  : WHILE expr COLON suite
  ;

for_stmt
  : FOR target_list IN target_list suite
  | FOR target_list IN target_list WHERE expr suite %prec forstmt
  ;

target_list
  : tuple_initializer
  ;

if_stmt
  : IF expr COLON suite elif_group ELSE COLON suite
  | IF expr COLON suite elif_group
  ;

elif_group
  : ELIF expr COLON suite
  | elif_group ELIF expr COLON suite
  ;

import_stmt
  : IMPORT import_alias
  | FROM expr IMPORT import_alias
  ;

import_alias
  : expr
  | expr AS IDENTIFIER 
  ;

func_definition
  : DEF declaration IDENTIFIER LPAREN parameter_list RPAREN COLON suite
  ;

func_declaration
  : DEF declaration IDENTIFIER LPAREN parameter_list RPAREN
  ;

assignment_stmt_list
  : assignment_stmt
  | assignment_stmt_list COMMA assignment_stmt
  ;

assignment_stmt
  : declaration assignment_list
  ;

assignment_list
  : assignment
  | assignment_list assignment
  ;

assignment
  : assignment_operator expr_list
  ;

expr_stmt
  : expr_group
  ;

expr_group
  : expr
  | expr_group SEMICOLON expr
  ; 

expr_list
  : expr
  | expr_list COMMA expr
  ;

expr
  : LITERAL
  | IDENTIFIER
  | expr DOT expr
  | expr INC_OP
  | expr DEC_OP
  | expr MUL_OP expr
  | expr DIV_OP expr
  | expr MOD_OP expr
  | expr PLUS_OP expr
  | expr MINUS_OP expr
  | expr BITWISE_SHIFTLEFT expr
  | expr BITWISE_SHIFTRIGHT expr
  | expr LESS_OP expr
  | expr GREATER_OP expr
  | expr LEQ_OP expr
  | expr GEQ_OP expr
  | expr EQ_OP expr
  | expr NEQ_OP expr
  | expr NEW expr
  | expr BITWISE_AND expr
  | expr BITWISE_XOR expr
  | expr BITWISE_OR expr
  | expr AND expr
  | expr OR expr
  | expr IF expr ELSE expr %prec conditional
  | NOT expr
  | BITWISE_NOT expr
  | INC_OP expr
  | DEC_OP expr
  | list_initializer
  | tuple_initializer
  | set_initializer
  | array_initializer
  | struct_initializer
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
  : LBRACKET LPAREN expr_list RPAREN RBRACKET
  ;

array_initializer
  : LBRACE expr_list RBRACE
  ;

tuple_initializer
  : LPAREN expr_list RPAREN
  ;

list_initializer
  : LBRACKET expr_list RBRACKET
  ;

parameter_list
  : LPAREN parameter_list_core RPAREN
  ;

parameter_list_core
  : declaration
  | parameter_list_core COMMA declaration
  ;

declaration
  : expr_list
  | type_qualifier_list type_specifier expr_list
  | type_qualifier_list expr_list
  | type_specifier expr_list
  | IDENTIFIER expr_list
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
  | ASSIGN_OP NEW
  | ASSIGN_OP LAZY NEW
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
  printf("%s\n", s);
}

/* Return 1 stops at EOF,
 * return 0 continues reading. 
 */
int yywrap() {
  return 1;
}