%{
#include <stdio.h>
#include "strnutils.h"
#include "parser.tab.h"

#define RETURN(type, token_string, token)			\
		printf("[%s]: %s", (type), (token_string));	\
        return token;
%}

/* Multi-line comment state */
%x IN_COMMENT

/* String literal state */
%x IN_STRING



%%

#keywords
"and"                   RETURN("KEYWORD", strtoupper(yytext), AND);
"as"			        RETURN("KEYWORD", strtoupper(yytext), AS);
"base"                  RETURN("KEYWORD", strtoupper(yytext), BASE);
"bool"                  RETURN("KEYWORD", strtoupper(yytext), BOOL);
"break"                 RETURN("KEYWORD", strtoupper(yytext), BREAK);
"catch"                 RETURN("KEYWORD", strtoupper(yytext), CATCH);
"char"                  RETURN("KEYWORD", strtoupper(yytext), CHAR);
"class"                 RETURN("KEYWORD", strtoupper(yytext), CLASS);
"const"                 RETURN("KEYWORD", strtoupper(yytext), CONST);
"continue"              RETURN("KEYWORD", strtoupper(yytext), CONTINUE);
"coroutine"             RETURN("KEYWORD", strtoupper(yytext), COROUTINE);
"def"                   RETURN("KEYWORD", strtoupper(yytext), DEF);
"defer"                 RETURN("KEYWORD", strtoupper(yytext), DEFER);
"default"               RETURN("KEYWORD", strtoupper(yytext), DEFAULT);
"do"                    RETURN("KEYWORD", strtoupper(yytext), DO);
"double"                RETURN("KEYWORD", strtoupper(yytext), DOUBLE);
"else"                  RETURN("KEYWORD", strtoupper(yytext), ELSE);
"enum"                  RETURN("KEYWORD", strtoupper(yytext), ENUM);
"ext"                   RETURN("KEYWORD", strtoupper(yytext), EXT);
"float"                 RETURN("KEYWORD", strtoupper(yytext), FLOAT);
"for"                   RETURN("KEYWORD", strtoupper(yytext), FOR);
"if"                    RETURN("KEYWORD", strtoupper(yytext), IF);
"import"                RETURN("KEYWORD", strtoupper(yytext), IMPORT);
"in"                    RETURN("KEYWORD", strtoupper(yytext), IN);
"int"                   RETURN("KEYWORD", strtoupper(yytext), INT);
"interface"             RETURN("KEYWORD", strtoupper(yytext), INTERFACE);
"lazy"                  RETURN("KEYWORD", strtoupper(yytext), LAZY);
"long"                  RETURN("KEYWORD", strtoupper(yytext), LONG);
"new"                   RETURN("KEYWORD", strtoupper(yytext), NEW);
"not"				    RETURN("KEYWORD", strtoupper(yytext), NOT);
"or"                    RETURN("KEYWORD", strtoupper(yytext), OR);
"pass"                  RETURN("KEYWORD", strtoupper(yytext), PASS);
"private"               RETURN("KEYWORD", strtoupper(yytext), PRIVATE);
"protected"             RETURN("KEYWORD", strtoupper(yytext), PROTECTED);
"public"                RETURN("KEYWORD", strtoupper(yytext), PUBLIC);
"return"                RETURN("KEYWORD", strtoupper(yytext), RETURN);
"short"                 RETURN("KEYWORD", strtoupper(yytext), SHORT);
"sizeof"                RETURN("KEYWORD", strtoupper(yytext), SIZEOF);
"stackalloc"            RETURN("KEYWORD", strtoupper(yytext), STACKALLOC);
"static"                RETURN("KEYWORD", strtoupper(yytext), STATIC);
"string"                RETURN("KEYWORD", strtoupper(yytext), STRING);
"struct"                RETURN("KEYWORD", strtoupper(yytext), STRUCT);
"switch"                RETURN("KEYWORD", strtoupper(yytext), SWITCH);
"task"                  RETURN("KEYWORD", strtoupper(yytext), TASK);
"this"                  RETURN("KEYWORD", strtoupper(yytext), THIS);
"throw"                 RETURN("KEYWORD", strtoupper(yytext), THROW);
"try"                   RETURN("KEYWORD", strtoupper(yytext), TRY);
"typeof"                RETURN("KEYWORD", strtoupper(yytext), TYPEOF);
"uchar"                 RETURN("KEYWORD", strtoupper(yytext), UCHAR);
"uint"                  RETURN("KEYWORD", strtoupper(yytext), UINT);
"ulong"                 RETURN("KEYWORD", strtoupper(yytext), ULONG);
"ushort"                RETURN("KEYWORD", strtoupper(yytext), USHORT);
"virtual"               RETURN("KEYWORD", strtoupper(yytext), VIRTUAL);
"volatile"              RETURN("KEYWORD", strtoupper(yytext), VOLATILE);
"where"                 RETURN("KEYWORD", strtoupper(yytext), WHERE);
"while"                 RETURN("KEYWORD", strtoupper(yytext), WHILE);
"finally"               RETURN("KEYWORD", strtoupper(yytext), FINALLY);

#identifiers
[_a-zA-Z][_a-zA-Z0-9]*  RETURN("IDENTIFIER", yytext, IDENTIFIER);

#string_literal
L?\"(\\.|[^\\"])*\"     RETURN("STRING_LITERAL", yytext, STRING_LITERAL);

#inline_comment
\/\/.*                  RETURN("COMMENT", yytext, COMMENT);


#multi-line_comment
<INITIAL>{
     "/*"              	BEGIN(IN_COMMENT);
}
<IN_COMMENT>{
"*/"      				BEGIN(INITIAL);
[^*\n]+   				// eat comment in chunks
"*"       				// eat the lone star
\n        				yylineno++;
 }

#integer
[-+]?([0]|[1-9]*)[lL]?	RETURN("INTEGER", yytext, INTEGER);


#binary_integer
[-+]?0[bB][0-1]+        RETURN("BININTEGER", yytext, BININTEGER);

#oct_integer
[-+]?0[oO][0-7]+		RETURN("OCTINTEGER", yytext, OCTINTEGER);

#hexidecimal_integer
[-+]?0[xX][0-9a-fA-F]+	RETURN("HEXINTEGER", yytext, HEXINTEGER);

#floating_number
[-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?    RETURN("FLOATINGNUM", yytext, FLOATINGNUM);

#arithmetic_operator
"+"                         RETURN("ARITHMETIC OPERATOR", yytext, PLUS_OP);
"-"                         RETURN("ARITHMETIC OPERATOR", yytext, MINUS_OP);
"*"                      	RETURN("ARITHMETIC OPERATOR", yytext, MUL_OP);
"/"                       	RETURN("ARITHMETIC OPERATOR", yytext, DIV_OP);
"%"                      	RETURN("ARITHMETIC OPERATOR", yytext, MOD_OP);

#assignment_operator
"="		                    RETURN("ASSIGNMENT OPERATOR", yytext, '=');
"+="						RETURN("ASSIGNMENT OPERATOR", yytext, PLUS_ASSIGN);
"-="						RETURN("ASSIGNMENT OPERATOR", yytext, MINUS_ASSIGN);
"*="						RETURN("ASSIGNMENT OPERATOR", yytext, MUL_ASSIGN);
"/="						RETURN("ASSIGNMENT OPERATOR", yytext, DIV_ASSIGN);
"%="						RETURN("ASSIGNMENT OPERATOR", yytext, MOD_ASSIGN);

#bitwise_operator
"~"							RETURN("BITWISE OPERATOR", yytext, NOT_BITWISE);
"&"							RETURN("BITWISE OPERATOR", yytext, AND_BITWISE);
"|"							RETURN("BITWISE OPERATOR", yytext, OR_BITWISE);
"^"							RETURN("BITWISE OPERATOR", yytext, XOR_BITWISE);
"~="						RETURN("BITWISE OPERATOR", yytext, NOT_ASSIGN);
"&="						RETURN("BITWISE OPERATOR", yytext, AND_ASSIGN);
"|="						RETURN("BITWISE OPERATOR", yytext, OR_ASSIGN);
"^="						RETURN("BITWISE OPERATOR", yytext, XOR_ASSIGN);
"<<"						RETURN("BITWISE OPERATOR", yytext, SHIFTLEFT_BITWISE);
">>"						RETURN("BITWISE OPERATOR", yytext, SHIFTRIGHT_BITWISE);
"<<="						RETURN("BITWISE OPERATOR", yytext, SHIFTLEFT_ASSIGN);
">>="						RETURN("BITWISE OPERATOR", yytext, SHIFTRIGHT_ASSIGN);

#equality_operator
"=="						RETURN("EQUALITY OPERATOR", yytext, EQ_OP);
">"                    		RETURN("EQUALITY OPERATOR", yytext, GREATER_OP);
"<"                    		RETURN("EQUALITY OPERATOR", yytext, LESS_OP);
">="                    	RETURN("EQUALITY OPERATOR", yytext, GEQ_OP);
"<="                    	RETURN("EQUALITY OPERATOR", yytext, LEQ_OP);

#increment_&_decrement
"++"						RETURN("INCREMENT & DECREMENT", yytext, INC_OP);
"--"						RETURN("INCREMENT & DECREMENT", yytext, DEC_OP);

#lambda_operator
"=>"						RETURN("LAMBDA OPERATOR", yytext, LAMBDA_OP);


#dot
"."               			RETURN("DOT", yytext, '.');

#comma
","             			RETURN("COMMA", yytext, ',');


#colon
":"              			RETURN("COLON", yytext, ':');

#bracket
"("                         RETURN("BRACKET", yytext, '(');
")"               	        RETURN("BRACKET", yytext, ')');


#sqaure_bracket
"["                         RETURN("SQUARE_BRACKET", yytext, '[');
"]"               		    RETURN("SQUARE_BRACKET", yytext, ']');


#curly_braces
"{"                         RETURN("CURLY_BRACE", yytext, '{');
"}"                         RETURN("CURLY_BRACE", yytext, '}');

#ellipsis
"..."                       RETURN("POND", yytext, ELLIPSIS);

#pond
"#"              			RETURN("POND", yytext, POND);


.                           { /* ignore bad characters */ }
%%

int main(int argc, char** argv) {
    if((yyin = fopen(argv[1], "r")) == 0) {
        exit(1);
    }
    yylex();
    return 0;
}

int yywrap() {
    fclose(yyin);
    return 1;
}

