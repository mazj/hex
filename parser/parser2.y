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


%left ASSIGN_NOT ASSIGN_AND ASSIGN_OR ASSIGN_XOR ASSIGN_SHIFTLEFT ASSIGN_SHIFTRIGHT
%left ASSIGN_OP ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD
%left AND OR 
%left BITWISE_AND BITWISE_OR BITWISE_XOR
%left EQ_OP NEQ_OP
%left GREATER_OP LESS_OP GEQ_OP LEQ_OP
%left BITWISE_SHIFTLEFT BITWISE_SHIFTRIGHT
%left PLUS_OP MINUS_OP
%left MUL_OP DIV_OP MOD_OP
%right NOT
%nonassoc IFX
%nonassoc ELSE

%type <integer> INTEGER

%error-verbose
%%

input
  : NEWLINE /* empty line */
  | stmt NEWLINE
  ;

stmt_group
  : stmt
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

return_stmt
  : RETURN NEWLINE
  | RETURN expr_list NEWLINE
  ;

compound_stmt
  : if_stmt
  | while_stmt
  | dowhile_stmt
  | try_stmt
  | func_def
  ;

func_def
  : DEF declaration_specifiers IDENTIFIER LPAREN parameter_list RPAREN COLON suite
  | DEF LPAREN parameter_list RPAREN COLON suite
  ;

try_stmt
  : TRY COLON suite catch_group
  : TRY COLON suite catch_group finally_stmt
  | TRY COLON suite finally_stmt
  ;

finally_stmt
  : FINALLY COLON suite
  ;

catch_group
  : catch_stmt
  | catch_group catch_stmt
  ;

catch_stmt
  : CATCH expr COLON suite
  ;

dowhile_stmt
  : DO suite WHILE expr
  ;

while_stmt
  : WHILE expr COLON suite
  ;

for_stmt
  : FOR IDENTIFIER IN expr suite
  : FOR IDENTIFIER IN expr WHERE expr suite
  ;

if_stmt
  : IF expr COLON suite elif_group
  | IF expr COLON suite elif_group ELSE COLON suite
  ;

elif_group
  : elif_stmt
  | elif_group elif_stmt
  ;

elif_stmt
  : ELIF expr COLON suite
  ;

import_stmt
  : IMPORT import_alias_list
  | FROM module IMPORT import_alias_list
  ;

import_alias_list
  : import_alias
  | import_alias_list COMMA import_alias
  ;

import_alias
  : module
  | module AS IDENTIFIER 
  ;

module
  : IDENTIFIER
  | IDENTIFIER DOT module
  ;

suite
  : stmt_list NEWLINE
  | NEWLINE INDENT stmt_group DEDENT
  ;

expr_stmt
  : expr_list
  ;

expr_list
  : expr_list COMMA expr
  ;

expr
  : LITERAL
  | IDENTIFIER
  | expr LBRACKET expr RBRACKET
  | expr DOT IDENTIFIER
  | expr INC_OP
  | expr DEC_OP
  | unary_operator expr
  | SIZEOF IDENTIFIER
  | LPAREN IDENTIFIER RPAREN expr
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
  | expr NEW expr
  | expr BITWISE_AND expr
  | expr BITWISE_XOR expr
  | expr BITWISE_OR expr
  | expr AND expr
  | expr OR expr
  | expr IF expr ELSE expr
  | lambda_parameter_list LAMBDA_OP expr
  | declaration
  | initializer
  ;

initializer_list
  : initializer_list COMMA initializer
  ;

initializer
  : assignment_stmt
  | LBRACKET initializer_list RBRACKET                            /* list */
  | LBRACKET initializer_list COMMA RBRACKET                      /* list */
  | LBRACE initializer_list RBRACE                                /* array */
  | LBRACE initializer_list COMMA RBRACE                          /* array */
  | LPAREN initializer_list RPAREN                                /* tuple */
  | LPAREN initializer_list COMMA RPAREN                          /* tuple */
  | LBRACE struct_initializer_list RBRACE                         /* struct */
  | LBRACE struct_initializer_list COMMA RBRACE                   /* struct */
  | LPAREN LBRACKET initializer_list  RBRACKET RPAREN             /* set */
  | LPAREN LBRACKET initializer_list COMMA RBRACKET RPAREN        /* set */
  | LBRACE map_initializer_list RBRACE                            /* map */
  | LBRACE map_initializer_list COMMA RBRACE                      /* map */
  | LBRACE multimap_initializer_list RBRACE                       /* multimap */
  | LBRACE multimap_initializer_list COMMA RBRACE                 /* multimap */
  ;

multimap_initializer_list
  : LITERAL COLON LPAREN RPAREN
  | LITERAL COLON LPAREN map_initializer_list RPAREN
  | IDENTIFIER COLON LPAREN RPAREN
  | IDENTIFIER COLON LPAREN map_initializer_list RPAREN
  | multimap_initializer_list COMMA LITERAL COLON LPAREN RPAREN
  | multimap_initializer_list COMMA LITERAL COLON LPAREN map_initializer_list RPAREN
  | multimap_initializer_list COMMA IDENTIFIER COLON LPAREN RPAREN
  | multimap_initializer_list COMMA IDENTIFIER COLON initializer_list
  ;

map_initializer_list
  : LITERAL COLON LITERAL
  | LITERAL COLON initializer_list
  | IDENTIFIER COLON LITERAL
  | IDENTIFIER COLON initializer_list
  | map_initializer_list COMMA LITERAL COLON LITERAL
  | map_initializer_list COMMA LITERAL COLON initializer_list
  | map_initializer_list COMMA IDENTIFIER COLON LITERAL
  | map_initializer_list COMMA IDENTIFIER COLON initializer_list
  ;

struct_initializer_list
  : IDENTIFIER ASSIGN_OP LITERAL
  | IDENTIFIER ASSIGN_OP initializer
  | struct_initializer_list COMMA IDENTIFIER ASSIGN_OP LITERAL
  | struct_initializer_list COMMA IDENTIFIER ASSIGN_OP initializer
  ;

assignment_stmt
  : declaration assignment_operator expr
  ;

lambda_parameter_list
  : alias_parameter_list
  | parameter_list
  ;

alias_parameter_list
  : alias_parameter_list COMMA alias_parameter
  ;

alias_parameter
  : typeless_parameter AS IDENTIFIER
  | type_parameter AS IDENTIFIER
  ;

parameter_list
  : type_parameter_list
  | type_parameter_list COMMA ELLIPSIS
  | typeless_parameter_list
  | typeless_parameter_list COMMA ELLIPSIS
  | type_parameter_list COMMA typeless_parameter_list
  | type_parameter_list COMMA typeless_parameter_list COMMA ELLIPSIS
  ;

type_parameter_list
  : type_parameter_list COMMA type_parameter
  ;

typeless_parameter_list
  : typeless_parameter_list COMMA typeless_parameter
  ; 

type_parameter
  : type_specifier IDENTIFIER
  | type_qualifier type_specifier IDENTIFIER
  ;

typeless_parameter
  : IDENTIFIER
  | type_qualifier IDENTIFIER
  ;

declaration
  : declarators
  | declaration_specifiers declarators
  ;

declarators
  : declarator
  | declarators COMMA declarator
  ;

declarator
  : IDENTIFIER
  | IDENTIFIER LBRACKET INTEGER RBRACKET
  | IDENTIFIER LBRACKET RBRACKET
  ;

declaration_specifiers
  : storage_class_specifier
  | storage_class_specifier type_qualifier_list
  | storage_class_specifier type_qualifier_list type_specifier
  | type_qualifier_list
  | type_qualifier_list type_specifier
  | type_specifier
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

type_qualifier_list
  : type_qualifier
  | type_qualifier_list type_qualifier
  ;

type_qualifier
  : CONST
  | VOLATILE
  ;

storage_class_specifier
  : STATIC
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

unary_operator
  : PLUS_OP
  | MINUS_OP
  | INC_OP
  | DEC_OP
  | BITWISE_NOT
  | NOT
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