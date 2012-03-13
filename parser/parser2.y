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
  | expr NEWLINE
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
  | expr NEW_OP expr
  | expr BITWISE_AND expr
  | expr BITWISE_XOR expr
  | expr BIWISE_OR expr
  | expr AND expr
  | expr OR expr
  | expr IF expr ELSE expr
  | parameter_list LAMBDA_OP expr
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