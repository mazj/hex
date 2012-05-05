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
  struct HexExpr *hex_expr;
  struct HexExprList *hex_expr_list;
  struct HexInteger* hex_integer;
  struct HexLiteral* hex_literal;
  int hex_assign_op;
  struct HexTypeQualifierList* hex_type_qualifier_list;
  struct HexDeclaration* hex_declaration;
  struct HexParameter* hex_parameter;
  struct HexParameterList* hex_parameter_list;
  struct HexInitializer* hex_initializer;
  struct HexLambdaExpr* hex_lambda_expr;
  struct HexAssignment* hex_assignment;
  struct HexAssginmentList* hex_assignment_list;
  struct HexAssignmentStmt* hex_assignment_stmt;
  struct HexAssignmentStmtList *hex_assignment_stmt_list;
  struct HexFuncDec *hex_func_dec;
  struct HexFuncDef *hex_func_def;
  struct HexAttribute *hex_attribute;
  struct HexCompilerProperty *hex_compiler_property;
  struct HexModule *hex_module;
  struct HexSuite *hex_suite;
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
%token <string>     ASSIGN_OP ASSIGN_OP_WEAKREF ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD
%token <string>     BITWISE_NOT BITWISE_AND BITWISE_OR BITWISE_XOR BITWISE_SHIFTLEFT BITWISE_SHIFTRIGHT
%token <string>     ASSIGN_BITWISE_AND ASSIGN_BITWISE_OR ASSIGN_BITWISE_XOR ASSIGN_SHIFTLEFT ASSIGN_SHIFTRIGHT
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
%left ASSIGN_OP ASSIGN_OP_WEAKREF ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD ASSIGN_BITWISE_AND ASSIGN_BITWISE_OR ASSIGN_BITWISE_XOR ASSIGN_SHIFTLEFT ASSIGN_SHIFTRIGHT
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

%type <hex_integer> INTEGER
%type <hex_literal> LITERAL
%type <hex_assign_op> assignment_operator
%type <integer> type_qualifier
%type <hex_type_qualifier_list> type_qualifier_list
%type <integer> type_specifier
%type <hex_declaration> declaration
%type <hex_expr> expr
%type <hex_expr_list> expr_list_
%type <hex_parameter> parameter
%type <hex_parameter_list> parameter_list_core
%type <hex_parameter_list> parameter_list
%type <hex_initializer> initializer
%type <hex_lamnbda_expr> lambda_expr
%type <hex_assignment> assignment
%type <hex_assignment_list> assignment_list
%type <hex_assignment_stmt> assignment_stmt
%type <hex_assignment_stmt_list> assignment_stmt_list
%type <hex_attribute> attribute
%type <hex_compiler_property> compiler_property;
%type <hex_func_dec> func_declaration
%type <hex_func_def> func_definition
%type <hex_module> module;
%type <hex_suite> suite

%error-verbose
%debug

%{

%}

%%

input/* empty line */
  : NEWLINE
  | stmt_group
  | class
  | class_section
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
  : FOR expr IN iterable COLON suite
  | FOR expr IN iterable WHERE expr COLON suite
  ;

iterable
  : expr
  | initializer
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
  : IDENTIFIER                                     { $$ = createModule($1); }
  ;

class
  : class_declaration NEWLINE class_section
  ;

class_section
  : INDENT class_access_specifier COLON suite
  ;

class_access_specifier
  : PRIVATE
  | PUBLIC
  | PROTECTED
  ;

class_declaration
  : CLASS IDENTIFIER COLON
  | CLASS IDENTIFIER COLON expr_list_ COLON
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
  : POND IDENTIFIER ASSIGN_OP IDENTIFIER                                { $$ = createCompilerProperty($2, $4); }
  ;

attribute
  : AT expr                                                             { $$ = createAttribute($2); }
  ;

lambda_expr
  : parameter_list LAMBDA_OP LBRACKET simple_stmt_list RBRACKET
  | parameter_list LAMBDA_OP suite
  ;

func_definition
  : func_declaration COLON suite                                        { $$ = createFuncDef($1, $3); }
  ;

func_declaration
  : DEF IDENTIFIER parameter_list                                       { $$ = createFuncDec(0, 0, 0, $2, $3); }
  | DEF IDENTIFIER LPAREN RPAREN                                        { $$ = createFuncDec(0, 0, 0, $2, 0); }
  | DEF IDENTIFIER IDENTIFIER parameter_list                            { $$ = createFuncDec(0, 0, $2, $3, $4); }
  | DEF IDENTIFIER IDENTIFIER LPAREN RPAREN                             { $$ = createFuncDec(0, 0, $2, $3, 0); }
  | DEF type_specifier IDENTIFIER parameter_list                        { $$ = createFuncDec(0, $2, 0, $3, $4); }
  | DEF type_specifier IDENTIFIER LPAREN RPAREN                         { $$ = createFuncDec(0, $2, 0, $3, 0); }
  | DEF type_qualifier_list IDENTIFIER parameter_list                   { $$ = createFuncDec($2, 0, 0, $3, $4); }
  | DEF type_qualifier_list IDENTIFIER LPAREN RPAREN                    { $$ = createFuncDec($2, 0, 0, $3, 0); }
  | DEF type_qualifier_list type_specifier IDENTIFIER parameter_list    { $$ = createFuncDec($2, $3, 0, $4, $5); }
  | DEF type_qualifier_list type_specifier IDENTIFIER LPAREN RPAREN     { $$ = createFuncDec($2, $3, 0, $4, 0); }
  | DEF type_qualifier_list IDENTIFIER IDENTIFIER parameter_list        { $$ = createFuncDec($2, 0, $3, $4, $5); }
  | DEF type_qualifier_list IDENTIFIER IDENTIFIER LPAREN RPAREN         { $$ = createFuncDec($2, 0, $3, $4, 0); }
  ;

assignment_stmt_list
  : assignment_stmt                              { $$ = createAssignmentStmtList($1,0); }
  | assignment_stmt_list COMMA assignment_stmt   { $$ = createAssignmentStmtList($3, $1); }
  ;

assignment_stmt
  : declaration assignment_list         { $$ = createAssignmentStmt(assignment_stmt_type_declaration, $1, $2); }
  | expr_list_ assignment_list          { $$ = createAssignmentStmt(assignment_stmt_type_expr_list, $1, $2); }
  ;

assignment_list
  : assignment                          { $$ = createAssignmentList($1, 0); }
  | assignment_list assignment          { $$ = createAssignmentList($2, $1); }
  ;

assignment
  : assignment_operator expr            { $$ = createAssignment($1, $2); }
  | assignment_operator initializer     { $$ = createAssignment($1, $2); }
  | assignment_operator lambda_expr     { $$ = createAssignment($1, $2); }
  ;

expr
  : LITERAL                             { $$ = createPrimaryExpr(primary_expr_type_literal, $1); }
  | IDENTIFIER                          { $$ = createPrimaryExpr(primary_expr_type_identifier, $1); }
  | expr tuple_initializer
  | IDENTIFIER tuple_initializer
  | expr list_initializer
  | IDENTIFIER list_initializer
  | expr LPAREN RPAREN                  
  | IDENTIFIER LPAREN RPAREN            { $$ = createPostfixInvocationExpr(postfix_expr_type_invocation, $1, 0); }
  | expr LBRACKET RBRACKET
  | IDENTIFIER LBRACKET RBRACKET
  | expr INC_OP                         { $$ = createPostfixExpr(postfix_expr_type_postfix_inc, $1, 0); }
  | expr DEC_OP                         { $$ = createPostfixExpr(postfix_expr_type_postfix_dec, $1, 0); }
  | INC_OP expr                         { $$ = createUnaryExpr(unary_expr_type_prefix_inc, $2); }
  | DEC_OP expr                         { $$ = createUnaryExpr(unary_expr_type_prefix_dec, $2); }
  | expr MUL_OP expr                    { $$ = createMultiplicativeExpr(multiplicative_expr_type_mul, $1, $3); }
  | expr DIV_OP expr                    { $$ = createMultiplicativeExpr(multiplicative_expr_type_div, $1, $3); }
  | expr MOD_OP expr                    { $$ = createMultiplicativeExpr(multiplicative_expr_type_mod, $1, $3); }
  | expr PLUS_OP expr                   { $$ = createAdditiveExpr(additive_expr_type_plus, $1, $3); }
  | expr MINUS_OP expr                  { $$ = createAdditiveExpr(additive_expr_type_minus, $1, $3); }
  | MINUS_OP expr %prec UMINUS          { $$ = createUnaryExpr(unary_expr_type_unary_minus, $2); }
  | expr BITWISE_SHIFTLEFT expr         { $$ = createBitwiseExpr(bitwise_expr_type_shift_left, $1, $3); }
  | expr BITWISE_SHIFTRIGHT expr        { $$ = createBitwiseExpr(bitwise_expr_type_shift_right, $1, $3); }
  | expr LESS_OP expr                   { $$ = createEqualityExpr(equality_expr_type_less, $1, $3); }
  | expr GREATER_OP expr                { $$ = createEqualityExpr(equality_expr_type_greater, $1, $3); }
  | expr LEQ_OP expr                    { $$ = createEqualityExpr(equality_expr_type_le, $1, $3); }
  | expr GEQ_OP expr                    { $$ = createEqualityExpr(equality_expr_type_is, $1, $3); }
  | expr IS expr                        { $$ = createEqualityExpr(equality_expr_type_le, $1, $3); }
  | expr IS_NOT expr                    { $$ = createEqualityExpr(equality_expr_type_is_not, $1, $3); }
  | expr EQ_OP expr                     { $$ = createEqualityExpr(equality_expr_type_eq, $1, $3); }    
  | expr NEQ_OP expr                    { $$ = createEqualityExpr(equality_expr_type_neq, $1, $3); }
  | expr BITWISE_AND expr               { $$ = createBitwiseExpr(bitwise_expr_type_bitwise_and, $1, $3); }
  | expr BITWISE_XOR expr               { $$ = createBitwiseExpr(bitwise_expr_type_bitwise_xor, $1, $3); }
  | expr BITWISE_OR expr                { $$ = createBitwiseExpr(bitwise_expr_type_bitwise_or, $1, $3); }
  | expr AND expr                       { $$ = createLogicExpr(logic_expr_type_logic_and, $1, $3); }
  | expr OR expr                        { $$ = createLogicExpr(logic_expr_type_logic_or, $1, $3); }
  | expr ELLIPSIS expr                  { $$ = createRangeExpr($1, $3); }
  | IF expr THEN expr ELSE expr         
  | expr DOT IDENTIFIER                 { $$ = createPostfixExpr(postfix_expr_type_accessor, $1, $3); }
  | WEAKREF expr                        { $$ = createWeakref($2); }
  | NOT expr                            { $$ = createUnaryExpr(unary_expr_type_not, $2); }
  | LOCK expr                           { $$ = createLockExpr(1, $2); }
  | UNLOCK expr                         { $$ = createLockExpr(0, $2); }
  | BITWISE_NOT expr                    { $$ = createUnaryExpr(unary_expr_type_bitwise_not, $2); }
  | LPAREN IDENTIFIER RPAREN expr       { $$ = createCastExpr(cast_expr_type_custom_type, $2, $4); }
  | LPAREN type_specifier RPAREN expr   { $$ = createCastExpr(cast_expr_type_type_specifier, &$2, $4); }
  | LPAREN expr RPAREN
  | THIS                                { $$ = createExpr(expr_type_this, 0); }
  | BASE                                { $$ = createExpr(expr_type_base, 0); }
  ;

expr_list_
  : expr                           { $$ = createExprList($1, 0); }
  | expr_list_ COMMA expr          { $$ = createExprList($3, $1); }
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
  : LPAREN parameter_list_core RPAREN                      { $$ = $2; }   
  | LPAREN parameter_list_core COMMA ELLIPSIS RPAREN       { $$ = $2; } 
  ;

parameter_list_core
  : parameter                                              { $$ = createParameterList($1, 0); }           
  | parameter_list_core COMMA parameter                    { $$ = createParameterList($3, $1); }  
  ;

parameter
  : type_qualifier_list type_specifier IDENTIFIER                      { $$ = createParameter($1, $2, 0, $3, 0, 0); }
  | type_qualifier_list type_specifier IDENTIFIER AS IDENTIFIER        { $$ = createParameter($1, $2, 0, $3, $5, 0); }
  | type_qualifier_list IDENTIFIER                                     { $$ = createParameter($1, 0, 0, $2, 0, 0); }
  | type_qualifier_list IDENTIFIER AS IDENTIFIER                       { $$ = createParameter($1, 0, 0, $3, $4, 0); }
  | type_specifier IDENTIFIER                                          { $$ = createParameter(0, $1, 0, $2, 0, 0); }
  | type_specifier IDENTIFIER AS IDENTIFIER                            { $$ = createParameter(0, $1, 0, $2, $4, 0); }
  | IDENTIFIER                                                         { $$ = createParameter(0, 0, $1, 0, 0, 0); }
  | IDENTIFIER IDENTIFIER                                              { $$ = createParameter(0, 0, $1, $2, 0, 0); }
  | IDENTIFIER AS IDENTIFIER                                           { $$ = createParameter(0, 0, 0, $1, $2, 0); }
  | IDENTIFIER IDENTIFIER AS IDENTIFIER                                { $$ = createParameter(0, 0, $1, $2, $4, 0); }
  | REF type_qualifier_list type_specifier IDENTIFIER                  { $$ = createParameter($2, $3, 0, $4, 0, 1); }
  | REF type_qualifier_list type_specifier IDENTIFIER AS IDENTIFIER    { $$ = createParameter($2, $3, 0, $4, $6, 1); }
  | REF type_qualifier_list IDENTIFIER                                 { $$ = createParameter($2, 0, 0, $3, 0, 1); }
  | REF type_qualifier_list IDENTIFIER AS IDENTIFIER                   { $$ = createParameter($2, 0, 0, $3, $5, 1); }
  | REF type_specifier IDENTIFIER                                      { $$ = createParameter(0, $2, 0, $3, 0, 1); }
  | REF type_specifier IDENTIFIER AS IDENTIFIER                        { $$ = createParameter(0, $2, 0, $3, $5, 1); }
  | REF IDENTIFIER                                                     { $$ = createParameter(0, 0, $2, 0, 0, 1); }
  | REF IDENTIFIER IDENTIFIER                                          { $$ = createParameter(0, 0, $2, $3, 0, 1); }
  | REF IDENTIFIER AS IDENTIFIER                                       { $$ = createParameter(0, 0, 0, $2, $3, 1); }
  | REF IDENTIFIER IDENTIFIER AS IDENTIFIER                            { $$ = createParameter(0, 0, $2, $3, $5, 1); }
  ;

declaration
  : type_qualifier_list type_specifier expr_list_                { $$ = createDeclaration($1, $2, 0, $3, 0); }
  | type_qualifier_list expr_list_                               { $$ = createDeclaration($1, 0, 0, $2, 0); }
  | type_specifier expr_list_                                    { $$ = createDeclaration(0, $1, 0, $2, 0); }
  | IDENTIFIER expr_list_                                        { $$ = createDeclaration(0, 0, $1, $2, 0); }
  | type_qualifier_list type_specifier expr_list_ AS IDENTIFIER  { $$ = createDeclaration($1, $2, 0, $3, $5); }
  | type_qualifier_list expr_list_ AS IDENTIFIER                 { $$ = createDeclaration($1, 0, 0, $2, $4); }
  | type_specifier expr_list_ AS IDENTIFIER                      { $$ = createDeclaration(0, $1, 0, $2, $4); }
  | IDENTIFIER expr_list_ AS IDENTIFIER                          { $$ = createDeclaration(0, 0, $1, $2, $4); }
  ;

type_specifier
  : CHAR                          { $$ = type_specifier_char; }
  | SHORT                         { $$ = type_specifier_short; }
  | INT                           { $$ = type_specifier_int; }
  | LONG                          { $$ = type_specifier_long; }
  | FLOAT                         { $$ = type_specifier_float; }
  | DOUBLE                        { $$ = type_specifier_double; }
  | UCHAR                         { $$ = type_specifier_uchar; }
  | USHORT                        { $$ = type_specifier_ushort; }
  | UINT                          { $$ = type_specifier_uint; }
  | ULONG                         { $$ = type_specifier_ulong; }
  ;

type_qualifier_list
  : type_qualifier                      { $$ = createTypeQualifierList($1, 0); }
  | type_qualifier_list type_qualifier  { $$ = createTypeQualifierList($2, $1); }
  ;

type_qualifier
  : CONST                          { $$ = type_qualifier_const; }
  | VOLATILE                       { $$ = type_qualifier_volatile; }
  | STATIC                         { $$ = type_qualifier_static; }
  ;

assignment_operator
  : ASSIGN_OP                      { $$ = assign_op; }
  | ASSIGN_OP_WEAKREF              { $$ = assign_op_weakref; }
  | ASSIGN_OP NEW                  { $$ = assign_op_new; }
  | ASSIGN_OP LAZY NEW             { $$ = assign_op_lazy_new; }
  | ASSIGN_OP STACKALLOC NEW       { $$ = assign_op_new; }
  | ASSIGN_OP STACKALLOC LAZY NEW  { $$ = assign_op_lazy_new; }
  | ASSIGN_MUL                     { $$ = assign_op_mul; }
  | ASSIGN_DIV                     { $$ = assign_op_div; }
  | ASSIGN_MOD                     { $$ = assign_op_mod; }
  | ASSIGN_PLUS                    { $$ = assign_op_plus; }
  | ASSIGN_MINUS                   { $$ = assign_op_minus; }
  | ASSIGN_SHIFTLEFT               { $$ = assign_op_shift_left; }
  | ASSIGN_SHIFTRIGHT              { $$ = assign_op_shift_right; }
  | ASSIGN_BITWISE_AND             { $$ = assign_op_bitwise_and; }
  | ASSIGN_BITWISE_OR              { $$ = assign_op_bitwise_or; }
  | ASSIGN_BITWISE_XOR             { $$ = assign_op_bitwise_xor; }
  ;

LITERAL
  : CHARACTER_LITERAL   { $$ = createLiteral(literal_type_char, &$1); }
  | STRING_LITERAL      { $$ = createLiteral(literal_type_string, $1); }
  | INTEGER             { $$ = createLiteral(literal_type_integer, $1); }
  | FLOATINGNUM         { $$ = createLiteral(literal_type_float, &$1); }
  ;

INTEGER
  : DECIMALINTEGER  { $$ = createInteger(integer_type_decimal, 0, $1); }
  | BININTEGER      { $$ = createInteger(integer_type_binary, 0, $1); }
  | OCTINTEGER      { $$ = createInteger(integer_type_octal, 0, $1); }
  | HEXINTEGER      { $$ = createInteger(integer_type_hexadecimal, 0, $1); }
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