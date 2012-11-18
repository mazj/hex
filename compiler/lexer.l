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
#include "parser.tab.h"


#define LEXER_TOKEN(our_type, yytext, token_type)   \
  switch(token_type) {                              \
    case DECIMALINTEGER:                            \
      yylval.integer = atoi(yytext);                \
      return DECIMALINTEGER;                        \
      break;                                        \
    case BININTEGER:                                \
      yylval.integer = atoi(yytext);                \
      return BININTEGER;                            \
      break;                                        \
    case OCTINTEGER:                                \
      yylval.integer = atoi(yytext);                \
      return OCTINTEGER;                            \
      break;                                        \
    case HEXINTEGER:                                \
      yylval.integer = atoi(yytext);                \
      return HEXINTEGER;                            \
      break;                                        \
    case FLOATINGNUM:                               \
      yylval.floating = atof(yytext);               \
      return FLOATINGNUM;                           \
      break;                                        \
    case CHARACTER_LITERAL:                         \
      yylval.character = yytext[1];                 \
      return CHARACTER_LITERAL;                     \
      break;                                        \
    case STRING_LITERAL:                            \
      yylval.string = yytext;                       \
      return STRING_LITERAL;                        \
      break;                                        \
    default:                                        \
      yylval.string = yytext;                       \
      return token_type;                            \
      break;                                        \
  } /* end of switch(token_type) */


int current_line_indent = 0;            /* indentation of current line */
int indent_level = 0;                   /* indentation level passed to parser */

%}

/* Multi-line comment state */
%x IN_COMMENT

/* String literal state */
%x IN_STRING

/* Indent level */
%x IN_INDENT

%option stack
%%

#keywords
"and"                       LEXER_TOKEN("KEYWORD", yytext, AND);
"as"                        LEXER_TOKEN("KEYWORD", yytext, AS);
"base"                      LEXER_TOKEN("KEYWORD", yytext, BASE);
"bool"                      LEXER_TOKEN("KEYWORD", yytext, BOOL);
"break"                     LEXER_TOKEN("KEYWORD", yytext, BREAK);
"case"                      LEXER_TOKEN("KEYWORD", yytext, CASE);
"catch"                     LEXER_TOKEN("KEYWORD", yytext, CATCH);
"char"                      LEXER_TOKEN("KEYWORD", yytext, CHAR);
"class"                     LEXER_TOKEN("KEYWORD", yytext, CLASS);
"const"                     LEXER_TOKEN("KEYWORD", yytext, CONST);
"continue"                  LEXER_TOKEN("KEYWORD", yytext, CONTINUE);
"coroutine"                 LEXER_TOKEN("KEYWORD", yytext, COROUTINE);
"def"                       LEXER_TOKEN("KEYWORD", yytext, DEF);
"defer"                     LEXER_TOKEN("KEYWORD", yytext, DEFER);
"default"                   LEXER_TOKEN("KEYWORD", yytext, DEFAULT);
"do"                        LEXER_TOKEN("KEYWORD", yytext, DO);
"double"                    LEXER_TOKEN("KEYWORD", yytext, DOUBLE);
"elif"                      LEXER_TOKEN("KEYWORD", yytext, ELIF);
"else"                      LEXER_TOKEN("KEYWORD", yytext, ELSE);
"ext"                       LEXER_TOKEN("KEYWORD", yytext, EXT);
"float"                     LEXER_TOKEN("KEYWORD", yytext, FLOAT);
"for"                       LEXER_TOKEN("KEYWORD", yytext, FOR);
"from"                      LEXER_TOKEN("KEYWORD", yytext, FROM);
"if"                        LEXER_TOKEN("KEYWORD", yytext, IF);
"import"                    LEXER_TOKEN("KEYWORD", yytext, IMPORT);
"in"                        LEXER_TOKEN("KEYWORD", yytext, IN);
"int"                       LEXER_TOKEN("KEYWORD", yytext, INT);
"interface"                 LEXER_TOKEN("KEYWORD", yytext, INTERFACE);
"is"                        LEXER_TOKEN("KEYWORD", yytext, IS);
"is not"                    LEXER_TOKEN("KEYWORD", yytext, IS_NOT);
"lazy"                      LEXER_TOKEN("KEYWORD", yytext, LAZY);
"lock"                      LEXER_TOKEN("KEYWORD", yytext, LOCK);
"long"                      LEXER_TOKEN("KEYWORD", yytext, LONG);
"new"                       LEXER_TOKEN("KEYWORD", yytext, NEW);
"not"                       LEXER_TOKEN("KEYWORD", yytext, NOT);
"or"                        LEXER_TOKEN("KEYWORD", yytext, OR);
"pass"                      LEXER_TOKEN("KEYWORD", yytext, PASS);
"private"                   LEXER_TOKEN("KEYWORD", yytext, PRIVATE);
"protected"                 LEXER_TOKEN("KEYWORD", yytext, PROTECTED);
"public"                    LEXER_TOKEN("KEYWORD", yytext, PUBLIC);
"ref"                       LEXER_TOKEN("KEYWORD", yytext, REF);
"return"                    LEXER_TOKEN("KEYWORD", yytext, RETURN);
"short"                     LEXER_TOKEN("KEYWORD", yytext, SHORT);
"sizeof"                    LEXER_TOKEN("KEYWORD", yytext, SIZEOF);
"stackalloc"                LEXER_TOKEN("KEYWORD", yytext, STACKALLOC);
"static"                    LEXER_TOKEN("KEYWORD", yytext, STATIC);
"string"                    LEXER_TOKEN("KEYWORD", yytext, STRING);
"struct"                    LEXER_TOKEN("KEYWORD", yytext, STRUCT);
"switch"                    LEXER_TOKEN("KEYWORD", yytext, SWITCH);
"task"                      LEXER_TOKEN("KEYWORD", yytext, TASK);
"then"                      LEXER_TOKEN("KEYWORD", yytext, THEN);
"this"                      LEXER_TOKEN("KEYWORD", yytext, THIS);
"throw"                     LEXER_TOKEN("KEYWORD", yytext, THROW);
"try"                       LEXER_TOKEN("KEYWORD", yytext, TRY);
"typeof"                    LEXER_TOKEN("KEYWORD", yytext, TYPEOF);
"uchar"                     LEXER_TOKEN("KEYWORD", yytext, UCHAR);
"uint"                      LEXER_TOKEN("KEYWORD", yytext, UINT);
"ulong"                     LEXER_TOKEN("KEYWORD", yytext, ULONG);
"unlock"                    LEXER_TOKEN("KEYWORD", yytext, UNLOCK);
"ushort"                    LEXER_TOKEN("KEYWORD", yytext, USHORT);
"virtual"                   LEXER_TOKEN("KEYWORD", yytext, VIRTUAL);
"volatile"                  LEXER_TOKEN("KEYWORD", yytext, VOLATILE);
"_weakref"                  LEXER_TOKEN("KEYWORD", yytext, WEAKREF);
"where"                     LEXER_TOKEN("KEYWORD", yytext, WHERE);
"while"                     LEXER_TOKEN("KEYWORD", yytext, WHILE);
"finally"                   LEXER_TOKEN("KEYWORD", yytext, FINALLY);

#identifiers
[_a-zA-Z][_a-zA-Z0-9]*      LEXER_TOKEN("IDENTIFIER", yytext, IDENTIFIER);

#character_literal
L?'(\\.|[^\\'])+'           LEXER_TOKEN("CHARACTER_LITERAL", yytext, CHARACTER_LITERAL);

#string_literal
L?\"(\\.|[^\\"])*\"         LEXER_TOKEN("STRING_LITERAL", yytext, STRING_LITERAL);

#inline_comment
\/\/.*                      LEXER_TOKEN("COMMENT", yytext, COMMENT);

#integer
([0]|[0-9]*)[lL]?           LEXER_TOKEN("INTEGER", yytext, DECIMALINTEGER);


#binary_integer
0[bB][0-1]+                 LEXER_TOKEN("BININTEGER", yytext, BININTEGER);

#oct_integer
0[oO][0-7]+                 LEXER_TOKEN("OCTINTEGER", yytext, OCTINTEGER);

#hexidecimal_integer
0[xX][0-9a-fA-F]+           LEXER_TOKEN("HEXINTEGER", yytext, HEXINTEGER);

#floating_number
[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?  LEXER_TOKEN("FLOATINGNUM", yytext, FLOATINGNUM);


#arithmetic_operator
"+"                         LEXER_TOKEN("ARITHMETIC OPERATOR", yytext, PLUS_OP);
"-"                         LEXER_TOKEN("ARITHMETIC OPERATOR", yytext, MINUS_OP);
"*"                         LEXER_TOKEN("ARITHMETIC OPERATOR", yytext, MUL_OP);
"/"                         LEXER_TOKEN("ARITHMETIC OPERATOR", yytext, DIV_OP);
"%"                         LEXER_TOKEN("ARITHMETIC OPERATOR", yytext, MOD_OP);

#assignment_operator
"="                         LEXER_TOKEN("ASSIGNMENT OPERATOR", yytext, ASSIGN_OP);
"~="                        LEXER_TOKEN("ASSIGNMENT OPERATOR", yytext, ASSIGN_OP_WEAKREF);  
"+="                        LEXER_TOKEN("ASSIGNMENT OPERATOR", yytext, ASSIGN_PLUS);
"-="                        LEXER_TOKEN("ASSIGNMENT OPERATOR", yytext, ASSIGN_MINUS);
"*="                        LEXER_TOKEN("ASSIGNMENT OPERATOR", yytext, ASSIGN_MUL);
"/="                        LEXER_TOKEN("ASSIGNMENT OPERATOR", yytext, ASSIGN_DIV);
"%="                        LEXER_TOKEN("ASSIGNMENT OPERATOR", yytext, ASSIGN_MOD);

#bitwise_operator
"~"                         LEXER_TOKEN("BITWISE OPERATOR", yytext, BITWISE_NOT);
"&"                         LEXER_TOKEN("BITWISE OPERATOR", yytext, BITWISE_AND);
"|"                         LEXER_TOKEN("BITWISE OPERATOR", yytext, BITWISE_OR);
"^"                         LEXER_TOKEN("BITWISE OPERATOR", yytext, BITWISE_XOR);
"<<"                        LEXER_TOKEN("BITWISE OPERATOR", yytext, BITWISE_SHIFTLEFT);
">>"                        LEXER_TOKEN("BITWISE OPERATOR", yytext, BITWISE_SHIFTRIGHT); 
"&="                        LEXER_TOKEN("BITWISE OPERATOR", yytext, ASSIGN_BITWISE_AND);
"|="                        LEXER_TOKEN("BITWISE OPERATOR", yytext, ASSIGN_BITWISE_OR);
"^="                        LEXER_TOKEN("BITWISE OPERATOR", yytext, ASSIGN_BITWISE_XOR);
"<<="                       LEXER_TOKEN("BITWISE OPERATOR", yytext, ASSIGN_SHIFTLEFT);
">>="                       LEXER_TOKEN("BITWISE OPERATOR", yytext, ASSIGN_SHIFTRIGHT);

#equality_operator
"=="                        LEXER_TOKEN("EQUALITY OPERATOR", yytext, EQ_OP);
"!="                        LEXER_TOKEN("EQUALITY OPERATOR", yytext, NEQ_OP);
">"                         LEXER_TOKEN("EQUALITY OPERATOR", yytext, GREATER_OP);
"<"                         LEXER_TOKEN("EQUALITY OPERATOR", yytext, LESS_OP);
">="                        LEXER_TOKEN("EQUALITY OPERATOR", yytext, GEQ_OP);
"<="                        LEXER_TOKEN("EQUALITY OPERATOR", yytext, LEQ_OP);

#increment_&_decrement
"++"                        LEXER_TOKEN("INCREMENT", yytext, INC_OP);
"--"                        LEXER_TOKEN("DECREMENT", yytext, DEC_OP);

#lambda_operator
"=>"                        LEXER_TOKEN("LAMBDA OPERATOR", yytext, LAMBDA_OP);


#dot
"."                         LEXER_TOKEN("DOT", yytext, DOT);

#comma
","                         LEXER_TOKEN("COMMA", yytext, COMMA);

#semicolon
";"                         LEXER_TOKEN("SEMICOLON", yytext, SEMICOLON);

#colon
":"                         LEXER_TOKEN("COLON", yytext, COLON);

#bracket
"("                         LEXER_TOKEN("PARENTHESIS", yytext, LPAREN);
")"                         LEXER_TOKEN("PARENTHESIS", yytext, RPAREN);


#sqaure_bracket
"["                         LEXER_TOKEN("SQUARE_BRACKET", yytext, LBRACKET);
"]"                         LEXER_TOKEN("SQUARE_BRACKET", yytext, RBRACKET);


#curly_braces
"{"                         LEXER_TOKEN("CURLY_BRACE", yytext, LBRACE);
"}"                         LEXER_TOKEN("CURLY_BRACE", yytext, RBRACE);

#ellipsis
"..."                       LEXER_TOKEN("POND", yytext, ELLIPSIS);

#pond
"#"                         LEXER_TOKEN("POND", yytext, POND);

#at
"@"                         LEXER_TOKEN("AT", yytext, AT);

#multi-line_comment
<INITIAL>{
"/*"                        BEGIN(IN_COMMENT);
}

<IN_COMMENT>{
"*/"                        BEGIN(INITIAL);
[^*\n]+                     // eat comment in chunks
"*"                         // eat the lone star
\n                          yylineno++;
}

<INITIAL>\n                 {
                              current_line_indent = 0;
                              yy_push_state(IN_INDENT); /* this solves the "return NEWLINE before BEGIN(IN_INDENT)" issue */
                              printf("NEWLINE\n");
                              return NEWLINE;
                            }

#indentation
<IN_INDENT>"  "             {
                              current_line_indent++;
                            }

<IN_INDENT>\t               {
                              /* tab */
                              #ifdef DEBUG
                              printf("TAB\n");
                              #endif
                            }

<IN_INDENT>\n               {
                              current_line_indent = 0; /* ignore blank line*/
                              #ifdef DEBUG
                              printf("NEWLINE\n");
                              #endif
                              return NEWLINE;
                            }

<IN_INDENT>.                {
                              unput(*yytext);
                              /* puts the character back to input stream and scans next character */
                              if(current_line_indent > indent_level) {
                                indent_level++;
                                #ifdef DEBUG
                                printf("INDENT\n");
                                #endif
                                return INDENT;
                              } else if(current_line_indent < indent_level) {
                                indent_level--;
                                #ifdef DEBUG
                                printf("DEDENT\n");
                                #endif
                                return DEDENT;
                              } else {
                                BEGIN(INITIAL);
                              }
                            }

.                           {
                              /* ignore bad characters */
                            }


%%

int
main(int argc, char **argv)
{
  if((yyin = fopen(argv[1], "r")) == 0) {
    exit(1);
  }
  yylex();
  yyparse();
  return 0;
}
