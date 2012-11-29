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


%{

#include <stdio.h>
#include "ast.h"

//#define YYDEBUG 1
//#define YYERROR_VERBOSE

//yydebug = 1;
%}

%union {
  char character;
  char* string;
  int integer;
  double floating;
  struct HexExpr *hex_expr;
  struct HexExprList *hex_expr_list;
  struct HexInteger *hex_integer;
  struct HexLiteral *hex_literal;
  int hex_assign_op;
  struct HexTypeQualifierList *hex_type_qualifier_list;
  struct HexDeclaration *hex_declaration;
  struct HexParameter *hex_parameter;
  struct HexParameterList *hex_parameter_list;
  struct HexListInitializer *hex_list_initializer;
  struct HexArrayInitializer *hex_array_initializer;
  struct HexTupleInitializer *hex_tuple_initializer;
  struct HexStructInitializer *hex_struct_initializer;
  struct HexSetInitializer *hex_set_initializer;
  struct HexMapInitializerSingle *hex_map_initializer_single;
  struct HexMapInitializerList *hex_map_initializer_list;
  struct HexMapInitializer *hex_map_initializer;
  struct HexInitializer *hex_initializer;
  struct HexLambdaExpr *hex_lambda_expr;
  struct HexAssignment *hex_assignment;
  struct HexAssignmentList *hex_assignment_list;
  struct HexAssignmentStmt *hex_assignment_stmt;
  struct HexAssignmentStmtList *hex_assignment_stmt_list;
  struct HexFuncDec *hex_func_dec;
  struct HexFuncDef *hex_func_def;
  struct HexAttribute *hex_attribute;
  struct HexCompilerProperty *hex_compiler_property;
  struct HexDecoratorListSingle *hex_decorator_list_single;
  struct HexDecoratorList *hex_decorator_list;
  struct HexDecorator *hex_decorator;
  struct HexClassDeclaration *hex_class_declaration;
  struct HexClassSection *hex_class_section;
  struct HexModule *hex_module;
  struct HexModuleList *hex_module_list;
  struct HexDirectImportStmt *hex_direct_import_stmt;
  struct HexRelativeImportStmt *hex_relative_import_stmt;
  struct HexImportStmt *hex_import_stmt;
  struct HexElifStmt *hex_elif_stmt;
  struct HexElifGroup *hex_elif_group;
  struct HexIfStmt *hex_if_stmt;
  struct HexIfStmtSimple *hex_if_stmt_simple;
  struct HexIterable *hex_iterable;
  struct HexWhileStmt *hex_while_stmt;
  struct HexForStmt *hex_for_stmt;
  struct HexCatchStmt *hex_catch_stmt;
  struct HexCatchStmtGroup *hex_catch_stmt_group;
  struct HexFinallyStmt *hex_finally_stmt;
  struct HexTryStmt *hex_try_stmt;
  struct HexCompoundStmt *hex_compound_stmt;
  struct HexReturnStmt *hex_return_stmt;
  struct HexControlSimpleStmt *hex_control_simple_stmt;
  struct HexSimpleStmt *hex_simple_stmt;
  struct HexSimpleStmtList *hex_simple_stmt_list;
  struct HexStmt *hex_stmt;
  struct HexStmtGroup *hex_stmt_group;
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
%type <hex_expr_list> expr_list
%type <hex_parameter> parameter
%type <hex_parameter_list> parameter_list_core
%type <hex_parameter_list> parameter_list
%type <hex_list_initializer> list_initializer
%type <hex_array_initializer> array_initializer
%type <hex_tuple_initializer> tuple_initializer
%type <hex_struct_initializer> struct_initializer
%type <hex_set_initializer> set_initializer
%type <hex_map_initializer_single> map_initializer_single
%type <hex_map_initializer_list> map_initializer_list 
%type <hex_map_initializer> map_initializer
%type <hex_initializer> initializer
%type <hex_lambda_expr> lambda_expr
%type <hex_assignment> assignment
%type <hex_assignment_list> assignment_list
%type <hex_assignment_stmt> assignment_stmt
%type <hex_assignment_stmt_list> assignment_stmt_list
%type <hex_attribute> attribute
%type <hex_compiler_property> compiler_property;
%type <hex_decorator_list_single> decorator_list_single
%type <hex_decorator_list> decorator_list
%type <hex_decorator> decorator
%type <hex_class_declaration> class_declaration
%type <hex_class_section> class_section
%type <integer> class_access_specifier
%type <hex_func_dec> func_declaration
%type <hex_func_def> func_definition
%type <hex_module> module;
%type <hex_module_list> module_list;
%type <hex_direct_import_stmt> direct_import_stmt
%type <hex_relative_import_stmt> relative_import_stmt
%type <hex_import_stmt> import_stmt
%type <hex_elif_stmt> elif_stmt
%type <hex_elif_group> elif_group
%type <hex_if_stmt> if_stmt
%type <hex_if_stmt_simple> if_stmt_simple
%type <hex_iterable> iterable
%type <hex_while_stmt> while_stmt
%type <hex_for_stmt> for_stmt
%type <hex_catch_stmt> catch_stmt
%type <hex_catch_stmt_group> catch_stmt_group
%type <hex_finally_stmt> finally_stmt
%type <hex_try_stmt> try_stmt
%type <hex_compound_stmt> compound_stmt
%type <hex_return_stmt> return_stmt
%type <hex_control_simple_stmt> control_simple_stmt
%type <hex_simple_stmt> simple_stmt
%type <hex_simple_stmt_list> simple_stmt_list
%type <hex_stmt> stmt
%type <hex_stmt_group> stmt_group
%type <hex_suite> suite

%error-verbose
%debug

%{

%}

%%

input/* empty line */
  : NEWLINE
  | stmt_group                                                                  { hex_ast_set_parse_tree_root($1, HEX_PARSE_TREE_ROOT_TYPE_STMT_GROUP);   }
  | class                                                                       { /* hex_ast_set_parse_tree_root($1, HEX_PARSE_TREE_ROOT_TYPE_CLASS); */   }
  | class_section                                                               { /* hex_ast_set_parse_tree_root($1, HEX_PARSE_TREE_ROOT_TYPE_CLASS_SECTION); */ }
  ;

suite
  : NEWLINE INDENT stmt_group NEWLINE DEDENT %prec SUITE_PREC                   { $$ =  hex_ast_create_suite($3); }
  | NEWLINE INDENT stmt_group NEWLINE                                           { $$ =  hex_ast_create_suite($3); }
  ;

stmt_group
  : stmt                                                                        { $$ = hex_ast_create_stmt_group($1, 0); }
  | stmt_group NEWLINE stmt                                                     { $$ = hex_ast_create_stmt_group($3, $1); }
  ;

stmt
  : simple_stmt_list                                                            { $$ = hex_ast_create_stmt(stmt_type_simple_stmt_list, $1); }
  | compound_stmt                                                               { $$ = hex_ast_create_stmt(stmt_type_compound_stmt, $1); }
  | control_simple_stmt                                                         { $$ = hex_ast_create_stmt(stmt_type_control_simple_stmt, $1); }
  ;

simple_stmt_list
  : simple_stmt                                                                 { $$ = hex_ast_create_simple_stmt_list($1, 0); }
  | simple_stmt_list SEMICOLON simple_stmt                                      { $$ = hex_ast_create_simple_stmt_list($3, $1); }
  ;

simple_stmt
  : expr_list                                                                   { $$ = hex_ast_create_simple_stmt(simple_stmt_type_expr_list, $1); }
  | declaration                                                                 { $$ = hex_ast_create_simple_stmt(simple_stmt_type_declaration, $1); }
  | assignment_stmt                                                             { $$ = hex_ast_create_simple_stmt(simple_stmt_type_assignment_stmt, $1); }
  | import_stmt                                                                 { $$ = hex_ast_create_simple_stmt(simple_stmt_type_import_stmt, $1); }
  | func_declaration                                                            { $$ = hex_ast_create_simple_stmt(simple_stmt_type_func_declaration, $1); }
  | if_stmt_simple                                                              { $$ = hex_ast_create_simple_stmt(simple_stmt_type_if_stmt_simple, $1); }
  | decorator                                                                   { $$ = hex_ast_create_simple_stmt(simple_stmt_type_decorator, $1); }
  ;

control_simple_stmt
  : return_stmt                                                                 { $$ = hex_ast_create_control_simple_stmt(control_simple_stmt_return, $1); }
  | BREAK                                                                       { $$ = hex_ast_create_control_simple_stmt(control_simple_stmt_break, 0); }
  | CONTINUE                                                                    { $$ = hex_ast_create_control_simple_stmt(control_simple_stmt_continue, 0); }
  ;

return_stmt
  : RETURN                                                                      { $$ = hex_ast_create_return_stmt(return_stmt_type_none, 0); }
  | RETURN expr_list                                                            { $$ = hex_ast_create_return_stmt(return_stmt_type_expr_list, $2); }
  ;

compound_stmt
  : if_stmt                                                                     { $$ = hex_ast_create_compound_stmt(compound_stmt_type_if_stmt, $1); }
  | while_stmt                                                                  { $$ = hex_ast_create_compound_stmt(compound_stmt_type_while_stmt, $1); }
  | try_stmt                                                                    { $$ = hex_ast_create_compound_stmt(compound_stmt_type_try_stmt, $1); }
  | for_stmt                                                                    { $$ = hex_ast_create_compound_stmt(compound_stmt_type_for_stmt, $1); }
  | func_definition                                                             { $$ = hex_ast_create_compound_stmt(compound_stmt_type_func_def, $1); }
  ;

try_stmt
  : TRY COLON suite catch_stmt_group                                            { $$ = hex_ast_create_try_stmt($3, $4, 0); }
  | TRY COLON suite catch_stmt_group finally_stmt                               { $$ = hex_ast_create_try_stmt($3, $4, $5); }
  | TRY COLON suite finally_stmt                                                { $$ = hex_ast_create_try_stmt($3, 0, $4); }
  ;

finally_stmt
  : FINALLY COLON suite                                                         { $$ = hex_ast_create_finally_stmt($3); }
  ;

catch_stmt_group
  : catch_stmt                                                                  { $$ = hex_ast_create_catch_stmt_group($1, 0); }
  | catch_stmt_group catch_stmt                                                 { $$ = hex_ast_create_catch_stmt_group($2, $1); }
  ;

catch_stmt
  : CATCH COLON suite                                                           { $$ = hex_ast_create_catch_stmt(catch_stmt_type_none, 0, $3); }
  | CATCH LPAREN declaration RPAREN COLON suite                                 { $$ = hex_ast_create_catch_stmt(catch_stmt_type_declaration, $3, $6); }
  | CATCH LPAREN IDENTIFIER RPAREN COLON suite                                  { $$ = hex_ast_create_catch_stmt(catch_stmt_type_identifier, $3, $6); }
  ;

while_stmt
  : WHILE expr COLON suite                                                      { $$ = hex_ast_create_while_stmt($2, $4); }
  ;

for_stmt
  : FOR expr IN iterable COLON suite                                            { $$ = hex_ast_create_for_stmt($4, $2, 0, $6); }
  | FOR expr IN iterable WHERE expr COLON suite                                 { $$ = hex_ast_create_for_stmt($4, $2, $6, $8); }
  ;

iterable
  : expr                                                                        { $$ = hex_ast_create_iterable(iterable_type_expr, $1); }
  | initializer                                                                 { $$ = hex_ast_create_iterable(iterable_type_initializer, $1); }
  ;

if_stmt_simple
  : IF expr COLON expr_list                                                    { $$ = hex_ast_create_if_stmt_simple(if_stmt_simple_type_expr, $2, $4); }
  | IF expr RETURN expr_list                                                   { $$ = hex_ast_create_if_stmt_simple(if_stmt_simple_type_return, $2, $4); }
  ;

if_stmt
  : IF expr COLON suite elif_group ELSE COLON suite                             { $$ = hex_ast_create_if_stmt($2, $4, $5, $8); }
  | IF expr COLON suite ELSE COLON suite                                        { $$ = hex_ast_create_if_stmt($2, $4, 0, $7); }
  | IF expr COLON suite elif_group                                              { $$ = hex_ast_create_if_stmt($2, $4, $5, 0); }
  | IF expr COLON suite                                                         { $$ = hex_ast_create_if_stmt($2, $4, 0, 0); }
  ;

elif_group
  : elif_stmt                                                                   { $$ = hex_ast_create_elif_group($1, 0); }
  | elif_group elif_stmt                                                        { $$ = hex_ast_create_elif_group($2, $1); }
  ;

elif_stmt                              
  : ELIF expr COLON suite                                                       { $$ = hex_ast_create_elif_stmt($2, $4); }
  ;

import_stmt
  : direct_import_stmt                                                          { $$ = hex_ast_create_import_stmt(import_stmt_type_direct, $1); }
  | relative_import_stmt                                                        { $$ = hex_ast_create_import_stmt(import_stmt_type_relative, $1); }
  ;

relative_import_stmt
  : FROM module_list IMPORT module                                              { $$ = hex_ast_create_relative_import_stmt($2, $4, 0); }
  | FROM module_list IMPORT module AS IDENTIFIER                                { $$ = hex_ast_create_relative_import_stmt($2, $4, $6); }
  ;

direct_import_stmt
  : IMPORT module_list                                                          { $$ = hex_ast_create_direct_import_stmt($2, 0); }
  | IMPORT module_list AS IDENTIFIER                                            { $$ = hex_ast_create_direct_import_stmt($2, $4); }
  ;

module_list
  : module                                                                      { $$ = hex_ast_create_module_list($1, 0); }
  | module_list DOT module                                                      { $$ = hex_ast_create_module_list($3, $1); }
  ;

module
  : IDENTIFIER                                                                  { $$ = hex_ast_create_module($1); }
  ;

class
  : class_declaration NEWLINE class_section
  ;

class_section
  : INDENT class_access_specifier COLON suite                                   { $$ = hex_ast_create_class_section($2, $4); }
  ;

class_access_specifier
  : PRIVATE                                                                     { $$ = class_access_specifier_private; }
  | PUBLIC                                                                      { $$ = class_access_specifier_public; }
  | PROTECTED                                                                   { $$ = class_access_specifier_protected; }
  ;

class_declaration
  : CLASS IDENTIFIER COLON                                                      { $$ = hex_ast_create_class_declaration($2, 0); }
  | CLASS IDENTIFIER COLON expr_list COLON                                     { $$ = hex_ast_create_class_declaration($2, $4); }
  ;

decorator
  : LBRACKET decorator_list RBRACKET                                            { $$ = hex_ast_create_decorator($2); }
  ;

decorator_list
  : decorator_list_single                                                       { $$ = hex_ast_create_decorator_list($1, 0); }
  | decorator_list COMMA decorator_list_single                                  { $$ = hex_ast_create_decorator_list($3, $1); }
  ;

decorator_list_single                                                   
  : compiler_property                                                           { $$ = hex_ast_create_decorator_list_single(decorator_list_single_type_compiler_property, $1); }
  | attribute                                                                   { $$ = hex_ast_create_decorator_list_single(decorator_list_single_type_attribute, $1); }
  ;

compiler_property
  : POND IDENTIFIER ASSIGN_OP IDENTIFIER                                        { $$ = hex_ast_create_compiler_property($2, $4); }
  ;

attribute
  : AT expr                                                                     { $$ = hex_ast_create_attribute($2); }
  ;

lambda_expr
  : parameter_list LAMBDA_OP LBRACKET simple_stmt_list RBRACKET                 { $$ = hex_ast_create_lambda_expr(lambda_type_simple, $1, $4); }
  | parameter_list LAMBDA_OP suite                                              { $$ = hex_ast_create_lambda_expr(lambda_type_suite, $1, $3); }
  ;

func_definition
  : func_declaration COLON suite                                                { $$ = hex_ast_create_func_def($1, $3); }
  ;

func_declaration
  : DEF IDENTIFIER parameter_list                                               { $$ = hex_ast_create_func_dec(0, -1, 0, $2, $3); }
  | DEF IDENTIFIER LPAREN RPAREN                                                { $$ = hex_ast_create_func_dec(0, -1, 0, $2, 0); }
  | DEF IDENTIFIER IDENTIFIER parameter_list                                    { $$ = hex_ast_create_func_dec(0, -1, $2, $3, $4); }
  | DEF IDENTIFIER IDENTIFIER LPAREN RPAREN                                     { $$ = hex_ast_create_func_dec(0, -1, $2, $3, 0); }
  | DEF type_specifier IDENTIFIER parameter_list                                { $$ = hex_ast_create_func_dec(0, $2, 0, $3, $4); }
  | DEF type_specifier IDENTIFIER LPAREN RPAREN                                 { $$ = hex_ast_create_func_dec(0, $2, 0, $3, 0); }
  | DEF type_qualifier_list IDENTIFIER parameter_list                           { $$ = hex_ast_create_func_dec($2, -1, 0, $3, $4); }
  | DEF type_qualifier_list IDENTIFIER LPAREN RPAREN                            { $$ = hex_ast_create_func_dec($2, -1, 0, $3, 0); }
  | DEF type_qualifier_list type_specifier IDENTIFIER parameter_list            { $$ = hex_ast_create_func_dec($2, $3, 0, $4, $5); }
  | DEF type_qualifier_list type_specifier IDENTIFIER LPAREN RPAREN             { $$ = hex_ast_create_func_dec($2, $3, 0, $4, 0); }
  | DEF type_qualifier_list IDENTIFIER IDENTIFIER parameter_list                { $$ = hex_ast_create_func_dec($2, -1, $3, $4, $5); }
  | DEF type_qualifier_list IDENTIFIER IDENTIFIER LPAREN RPAREN                 { $$ = hex_ast_create_func_dec($2, -1, $3, $4, 0); }
  ;

assignment_stmt_list
  : assignment_stmt                                                             { $$ = hex_ast_create_assignment_stmt_list($1,0); }
  | assignment_stmt_list COMMA assignment_stmt                                  { $$ = hex_ast_create_assignment_stmt_list($3, $1); }
  ;

assignment_stmt
  : declaration assignment_list                                                 { $$ = hex_ast_create_assignment_stmt(assignment_stmt_type_declaration, $1, $2); }
  | expr_list assignment_list                                                  { $$ = hex_ast_create_assignment_stmt(assignment_stmt_type_expr_list, $1, $2); }
  ;

assignment_list
  : assignment                                                                  { $$ = hex_ast_create_assignment_list($1, 0); }
  | assignment_list assignment                                                  { $$ = hex_ast_create_assignment_list($2, $1); }
  ;

assignment
  : assignment_operator expr                                                    { $$ = hex_ast_create_assignment($1, assignment_type_expr, $2); }
  | assignment_operator initializer                                             { $$ = hex_ast_create_assignment($1, assignment_type_initializer, $2); }
  | assignment_operator lambda_expr                                             { $$ = hex_ast_create_assignment($1, assignment_type_lambda, $2); }
  ;

expr
  : LITERAL                                                                     { $$ = hex_ast_create_primary_expr(primary_expr_type_literal, $1); }
  | IDENTIFIER                                                                  { $$ = hex_ast_create_primary_expr(primary_expr_type_identifier, $1); }
  | expr tuple_initializer                                                      {
                                                                                  int type = postfix_invocation_expr_with_args_type_expr;
                                                                                  $$ = hex_ast_create_postfix_expr(postfix_expr_type_invocation_with_args, type, $1, $2);
                                                                                }
  | IDENTIFIER tuple_initializer                                                {
                                                                                  int type = postfix_invocation_expr_with_args_type_identifier;
                                                                                  $$ = hex_ast_create_postfix_expr(postfix_expr_type_invocation_with_args, type, $1, $2);
                                                                                }
  | expr list_initializer                                                       {
                                                                                  int type = postfix_index_expr_type_expr;
                                                                                  $$ = hex_ast_create_postfix_expr(postfix_expr_type_index, type, $1, $2);
                                                                                }
  | IDENTIFIER list_initializer                                                 {
                                                                                  int type = postfix_index_expr_type_identifier;
                                                                                  $$ = hex_ast_create_postfix_expr(postfix_expr_type_index, type, $1, $2);
                                                                                }
  | expr LPAREN RPAREN                                                          {
                                                                                  int invocation_type = postfix_invocation_expr_type_expr;
                                                                                  $$ = hex_ast_create_postfix_expr(postfix_expr_type_invocation, invocation_type, $1, 0);
                                                                                }
  | IDENTIFIER LPAREN RPAREN                                                    {
                                                                                  int invocation_type = postfix_invocation_expr_type_identifier;
                                                                                  $$ = hex_ast_create_postfix_expr(postfix_expr_type_invocation, invocation_type, $1, 0);
                                                                                }
  | expr LBRACKET RBRACKET                                                      {
                                                                                  int type = postfix_index_expr_type_expr;
                                                                                  $$ = hex_ast_create_postfix_expr(postfix_expr_type_index, type, $1, 0);
                                                                                }
  | IDENTIFIER LBRACKET RBRACKET                                                {
                                                                                  int type = postfix_index_expr_type_identifier;
                                                                                  $$ = hex_ast_create_postfix_expr(postfix_expr_type_index, type, $1, 0);
                                                                                }
  | expr INC_OP                                                                 { $$ = hex_ast_create_postfix_expr(postfix_expr_type_postfix_inc, -1, $1, 0); }
  | expr DEC_OP                                                                 { $$ = hex_ast_create_postfix_expr(postfix_expr_type_postfix_dec, -1, $1, 0); }
  | INC_OP expr                                                                 { $$ = hex_ast_create_unary_expr(unary_expr_type_prefix_inc, $2); }
  | DEC_OP expr                                                                 { $$ = hex_ast_create_unary_expr(unary_expr_type_prefix_dec, $2); }
  | expr MUL_OP expr                                                            { $$ = hex_ast_create_multiplicative_expr(multiplicative_expr_type_mul, $1, $3); }
  | expr DIV_OP expr                                                            { $$ = hex_ast_create_multiplicative_expr(multiplicative_expr_type_div, $1, $3); }
  | expr MOD_OP expr                                                            { $$ = hex_ast_create_multiplicative_expr(multiplicative_expr_type_mod, $1, $3); }
  | expr PLUS_OP expr                                                           { $$ = hex_ast_create_additive_expr(additive_expr_type_plus, $1, $3); }
  | expr MINUS_OP expr                                                          { $$ = hex_ast_create_additive_expr(additive_expr_type_minus, $1, $3); }
  | MINUS_OP expr %prec UMINUS                                                  { $$ = hex_ast_create_unary_expr(unary_expr_type_unary_minus, $2); }
  | expr BITWISE_SHIFTLEFT expr                                                 { $$ = hex_ast_create_bitwise_expr(bitwise_expr_type_shift_left, $1, $3); }
  | expr BITWISE_SHIFTRIGHT expr                                                { $$ = hex_ast_create_bitwise_expr(bitwise_expr_type_shift_right, $1, $3); }
  | expr LESS_OP expr                                                           { $$ = hex_ast_create_equality_expr(equality_expr_type_less, $1, $3); }
  | expr GREATER_OP expr                                                        { $$ = hex_ast_create_equality_expr(equality_expr_type_greater, $1, $3); }
  | expr LEQ_OP expr                                                            { $$ = hex_ast_create_equality_expr(equality_expr_type_le, $1, $3); }
  | expr GEQ_OP expr                                                            { $$ = hex_ast_create_equality_expr(equality_expr_type_ge, $1, $3); }
  | expr IS expr                                                                { $$ = hex_ast_create_equality_expr(equality_expr_type_is, $1, $3); }
  | expr IS_NOT expr                                                            { $$ = hex_ast_create_equality_expr(equality_expr_type_is_not, $1, $3); }
  | expr EQ_OP expr                                                             { $$ = hex_ast_create_equality_expr(equality_expr_type_eq, $1, $3); }    
  | expr NEQ_OP expr                                                            { $$ = hex_ast_create_equality_expr(equality_expr_type_neq, $1, $3); }
  | expr BITWISE_AND expr                                                       { $$ = hex_ast_create_bitwise_expr(bitwise_expr_type_bitwise_and, $1, $3); }
  | expr BITWISE_XOR expr                                                       { $$ = hex_ast_create_bitwise_expr(bitwise_expr_type_bitwise_xor, $1, $3); }
  | expr BITWISE_OR expr                                                        { $$ = hex_ast_create_bitwise_expr(bitwise_expr_type_bitwise_or, $1, $3); }
  | expr AND expr                                                               { $$ = hex_ast_create_logic_expr(logic_expr_type_logic_and, $1, $3); }
  | expr OR expr                                                                { $$ = hex_ast_create_logic_expr(logic_expr_type_logic_or, $1, $3); }
  | expr ELLIPSIS expr                                                          { $$ = hex_ast_create_range_expr($1, $3); }
  | IF expr THEN expr ELSE expr                                                 { $$ = hex_ast_create_conditional_expr($2, $4, $6); }
  | expr DOT IDENTIFIER                                                         { $$ = hex_ast_create_postfix_expr(postfix_expr_type_accessor, -1, $1, $3); }
  | WEAKREF expr                                                                { $$ = hex_ast_create_weakref_expr($2); }
  | NOT expr                                                                    { $$ = hex_ast_create_unary_expr(unary_expr_type_not, $2); }
  | BITWISE_NOT expr                                                            { $$ = hex_ast_create_unary_expr(unary_expr_type_bitwise_not, $2); }
  | LOCK expr                                                                   { $$ = hex_ast_create_lock_expr(1, $2); }
  | UNLOCK expr                                                                 { $$ = hex_ast_create_lock_expr(0, $2); }
  | LPAREN IDENTIFIER RPAREN expr                                               { $$ = hex_ast_create_cast_expr(cast_expr_type_custom_type, $2, $4); }
  | LPAREN type_specifier RPAREN expr                                           { $$ = hex_ast_create_cast_expr(cast_expr_type_type_specifier, &$2, $4); }                  
  | THIS DOT expr                                                               { $$ = hex_ast_create_this_expr($3); }
  | BASE DOT expr                                                               { $$ = hex_ast_create_base_expr($3); }
  ;

expr_list
  : expr                                                                        { $$ = hex_ast_create_expr_list($1, 0); }
  | expr_list COMMA expr                                                        { $$ = hex_ast_create_expr_list($3, $1); }
  ;

initializer
  : list_initializer                                                            { $$ = hex_ast_create_initializer(initializer_type_list, $1); }
  | array_initializer                                                           { $$ = hex_ast_create_initializer(initializer_type_array, $1); }
  | struct_initializer                                                          { $$ = hex_ast_create_initializer(initializer_type_struct, $1); }
  | tuple_initializer                                                           { $$ = hex_ast_create_initializer(initializer_type_tuple, $1); }  
  | set_initializer                                                             { $$ = hex_ast_create_initializer(initializer_type_set, $1); }
  | map_initializer                                                             { $$ = hex_ast_create_initializer(initializer_type_map, $1); }
  ;

map_initializer
  : LBRACE map_initializer_list RBRACE                                          { $$ = hex_ast_create_map_initializer($2); }
  ;

map_initializer_list
  : map_initializer_single                                                      { $$ = hex_ast_create_map_initializer_list($1, 0); }
  | map_initializer_list COMMA map_initializer_single                           { $$ = hex_ast_create_map_initializer_list($3, $1); }
  ;

map_initializer_single
  : expr COLON expr                                                             { $$ = hex_ast_create_map_initializer_single($1, $3); }
  ;

struct_initializer
  : LBRACE assignment_stmt_list RBRACE                                          { $$ = hex_ast_create_struct_initializer($2); }
  ;

set_initializer
  : LBRACKET LPAREN expr_list RPAREN RBRACKET                                  { $$ = hex_ast_create_set_initializer($3); }
  ;

array_initializer
  : LBRACE expr_list RBRACE                                                    { $$ = hex_ast_create_array_initializer($2); }
  ;

tuple_initializer
  : LPAREN expr_list RPAREN                                                    { $$ = hex_ast_create_tuple_initializer($2); }
  ;

list_initializer
  : LBRACKET expr_list RBRACKET                                                { $$ = hex_ast_create_list_initializer($2); }
  ;

parameter_list
  : LPAREN parameter_list_core RPAREN                                           { $$ = $2; }
  | LPAREN parameter_list_core COMMA ELLIPSIS RPAREN                            { $$ = $2; } 
  ;

parameter_list_core
  : parameter                                                                   { $$ = hex_ast_create_parameter_list($1, 0); }           
  | parameter_list_core COMMA parameter                                         { $$ = hex_ast_create_parameter_list($3, $1); }  
  ;

parameter
  : type_qualifier_list type_specifier IDENTIFIER                               { $$ = hex_ast_create_parameter($1, $2, 0, $3, 0, 0); }
  | type_qualifier_list type_specifier IDENTIFIER AS IDENTIFIER                 { $$ = hex_ast_create_parameter($1, $2, 0, $3, $5, 0); }
  | type_qualifier_list IDENTIFIER                                              { $$ = hex_ast_create_parameter($1, -1, 0, $2, 0, 0); }
  | type_qualifier_list IDENTIFIER AS IDENTIFIER                                { $$ = hex_ast_create_parameter($1, -1, 0, $2, $4, 0); }
  | type_specifier IDENTIFIER                                                   { $$ = hex_ast_create_parameter(0, $1, 0, $2, 0, 0); }
  | type_specifier IDENTIFIER AS IDENTIFIER                                     { $$ = hex_ast_create_parameter(0, $1, 0, $2, $4, 0); }
  | IDENTIFIER                                                                  { $$ = hex_ast_create_parameter(0, -1, $1, 0, 0, 0); }
  | IDENTIFIER IDENTIFIER                                                       { $$ = hex_ast_create_parameter(0, -1, $1, $2, 0, 0); }
  | IDENTIFIER AS IDENTIFIER                                                    { $$ = hex_ast_create_parameter(0, -1, 0, $1, $2, 0); }
  | IDENTIFIER IDENTIFIER AS IDENTIFIER                                         { $$ = hex_ast_create_parameter(0, -1, $1, $2, $4, 0); }
  | REF type_qualifier_list type_specifier IDENTIFIER                           { $$ = hex_ast_create_parameter($2, $3, 0, $4, 0, 1); }
  | REF type_qualifier_list type_specifier IDENTIFIER AS IDENTIFIER             { $$ = hex_ast_create_parameter($2, $3, 0, $4, $6, 1); }
  | REF type_qualifier_list IDENTIFIER                                          { $$ = hex_ast_create_parameter($2, -1, 0, $3, 0, 1); }
  | REF type_qualifier_list IDENTIFIER AS IDENTIFIER                            { $$ = hex_ast_create_parameter($2, -1, 0, $3, $5, 1); }
  | REF type_specifier IDENTIFIER                                               { $$ = hex_ast_create_parameter(0, $2, 0, $3, 0, 1); }
  | REF type_specifier IDENTIFIER AS IDENTIFIER                                 { $$ = hex_ast_create_parameter(0, $2, 0, $3, $5, 1); }
  | REF IDENTIFIER                                                              { $$ = hex_ast_create_parameter(0, -1, $2, 0, 0, 1); }
  | REF IDENTIFIER IDENTIFIER                                                   { $$ = hex_ast_create_parameter(0, -1, $2, $3, 0, 1); }
  | REF IDENTIFIER AS IDENTIFIER                                                { $$ = hex_ast_create_parameter(0, -1, 0, $2, $3, 1); }
  | REF IDENTIFIER IDENTIFIER AS IDENTIFIER                                     { $$ = hex_ast_create_parameter(0, -1, $2, $3, $5, 1); }
  ;

declaration
  : type_qualifier_list type_specifier expr_list                                { $$ = hex_ast_create_declaration($1, $2, 0, $3, 0); }
  | type_qualifier_list expr_list                                               { $$ = hex_ast_create_declaration($1, -1, 0, $2, 0); }
  | type_specifier expr_list                                                    { $$ = hex_ast_create_declaration(0, $1, 0, $2, 0); }
  | IDENTIFIER expr_list                                                        { $$ = hex_ast_create_declaration(0, -1, $1, $2, 0); }
  | type_qualifier_list type_specifier expr_list AS IDENTIFIER                  { $$ = hex_ast_create_declaration($1, $2, 0, $3, $5); }
  | type_qualifier_list expr_list AS IDENTIFIER                                 { $$ = hex_ast_create_declaration($1, -1, 0, $2, $4); }
  | type_specifier expr_list AS IDENTIFIER                                      { $$ = hex_ast_create_declaration(0, $1, 0, $2, $4); }
  | IDENTIFIER expr_list AS IDENTIFIER                                          { $$ = hex_ast_create_declaration(0, -1, $1, $2, $4); }
  ;

type_specifier
  : CHAR                                                                        { $$ = type_specifier_char; }
  | SHORT                                                                       { $$ = type_specifier_short; }
  | INT                                                                         { $$ = type_specifier_int; }
  | LONG                                                                        { $$ = type_specifier_long; }
  | FLOAT                                                                       { $$ = type_specifier_float; }
  | DOUBLE                                                                      { $$ = type_specifier_double; }
  | UCHAR                                                                       { $$ = type_specifier_uchar; }
  | USHORT                                                                      { $$ = type_specifier_ushort; }
  | UINT                                                                        { $$ = type_specifier_uint; }
  | ULONG                                                                       { $$ = type_specifier_ulong; }
  ;

type_qualifier_list
  : type_qualifier                                                              { $$ = hex_ast_create_type_qualifier_list($1, 0); }
  | type_qualifier_list type_qualifier                                          { $$ = hex_ast_create_type_qualifier_list($2, $1); }
  ;

type_qualifier
  : CONST                                                                       { $$ = type_qualifier_const; }
  | VOLATILE                                                                    { $$ = type_qualifier_volatile; }
  | STATIC                                                                      { $$ = type_qualifier_static; }
  ;

assignment_operator
  : ASSIGN_OP                                                                   { $$ = assign_op; }
  | ASSIGN_OP_WEAKREF                                                           { $$ = assign_op_weakref; }
  | ASSIGN_OP NEW                                                               { $$ = assign_op_new; }
  | ASSIGN_OP LAZY NEW                                                          { $$ = assign_op_lazy_new; }
  | ASSIGN_OP STACKALLOC NEW                                                    { $$ = assign_op_new; }
  | ASSIGN_OP STACKALLOC LAZY NEW                                               { $$ = assign_op_lazy_new; }
  | ASSIGN_DIV                                                                  { $$ = assign_op_div; }
  | ASSIGN_MUL                                                                  { $$ = assign_op_mul; }
  | ASSIGN_MOD                                                                  { $$ = assign_op_mod; }
  | ASSIGN_PLUS                                                                 { $$ = assign_op_plus; }
  | ASSIGN_MINUS                                                                { $$ = assign_op_minus; }
  | ASSIGN_SHIFTLEFT                                                            { $$ = assign_op_shift_left; }
  | ASSIGN_SHIFTRIGHT                                                           { $$ = assign_op_shift_right; }
  | ASSIGN_BITWISE_AND                                                          { $$ = assign_op_bitwise_and; }
  | ASSIGN_BITWISE_OR                                                           { $$ = assign_op_bitwise_or; }
  | ASSIGN_BITWISE_XOR                                                          { $$ = assign_op_bitwise_xor; }
  ;

LITERAL
  : CHARACTER_LITERAL                                                           { $$ = hex_ast_create_literal(literal_type_char, &$1); }
  | STRING_LITERAL                                                              { $$ = hex_ast_create_literal(literal_type_string, $1); }
  | INTEGER                                                                     { $$ = hex_ast_create_literal(literal_type_integer, $1); }
  | FLOATINGNUM                                                                 { $$ = hex_ast_create_literal(literal_type_float, &$1); }
  ;

INTEGER
  : DECIMALINTEGER                                                              { $$ = hex_ast_create_integer(integer_type_decimal, 0, $1); }
  | BININTEGER                                                                  { $$ = hex_ast_create_integer(integer_type_binary, 0, $1); }
  | OCTINTEGER                                                                  { $$ = hex_ast_create_integer(integer_type_octal, 0, $1); }
  | HEXINTEGER                                                                  { $$ = hex_ast_create_integer(integer_type_hexadecimal, 0, $1); }
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
