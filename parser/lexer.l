%{
#include <stdio.h>
#include "parser.tab.h"

#define RETURN(type, token)						\
		printf("[%s]: %s", (type), (token));	
%}


/* escape sequences */
BACKSLASH           "\\\\"
SINGLEQUOTE         "\'"
DOUBLEQUOTE         "\""
ESCAPE              BACKSLASH | SINGLEQUOTE | DOUBLEQUOTE | "\\"

/* string literals */
LOWERLETTER         [a-z]                       // lower case letters
UPPERLETTER         [A-Z]                       // upper case letters
LETTER              LOWERLETTER | UPPERLETTER   // letters
STRINGPREFIX        "r" | "u" | "ur" | "R" | "U" | "UR" | "Ur" | "uR" | "b" | "B" | "br" | "Br" | "bR" | "BR"
STRINGCHAR			[^ESCAPE \n]
STRING              "\"" STRINGCHAR* "\""
STRINGLITERAL       [STRINGPREFIX]STRING

/* digits */
DIGIT               [0-9]											// decimal digit
BINDIGIT 			[0-1]											// binary digit
OCTDIGIT			[0-7]												// oct digit
NONZERODIGIT		[1-9]												// none zero digit
HEXDIGIT			[0-9] | [a-f] | [A-F]							// hex digit

/* integer and long integer literals */
BININTEGER			"0"("b"|"B") BINDIGIT+									// binary integer
OCTINTEGER			"0"("o"|"O") OCTDIGIT+ | "0" OCTDIGIT+					// oct integer
HEXINTEGER			"0"("x"|"X") ([0-9] | [a-f] | [A-F])+									// hex integer
DECIMALINTEGER		NONZERODIGIT DIGIT* | "0"								// decimal integer
INTEGER             DECIMALINTEGER | OCTINTEGER | HEXINTEGER | BININTEGER	// integer
LONGINTEGER			INTEGER("l"|"L")

/* floating point literals */
INTPART				DIGIT+
EXPONENT            ("e" | "E") ["+" | "-"] DIGIT+
FRACTION			"." DIGIT+
POINTFLOAT			[INTPART] FRACTION | INTPART "."
EXPONENTFLOAT		(INTPART | POINTFLOAT) EXPONENT
FLOATNUMBER			POINTFLOAT | EXPONENTFLOAT                                // floating number

/* identifier */
IDENTIFIER          (UNDERSCORE | LETTER)(UNDERSCORE | LETTER | DIGIT)*   // identifier

/* whitespaces */
BACKSPACE           \b
FORMFEED            \f
CARRIAGERETURN      \r
NEWLINE             \n
TAB                 \t
NULL                \0
WHITESPACE          BACKSPACE | FORMFEED | CARRIAGERETURN | NEWLINE | TAB | NULL

/* Multi-line comment state */
%x IN_COMMENT

/* String literal state */
%x IN_STRING


%%


#keywords
"and"                   RETURN("KEYWORD", "AND");
"as"			        RETURN("KEYWORD", "AS");
"base"                  RETURN("KEYWORD", "BASE");
"bool"                  RETURN("KEYWORD", "BOOL");
"break"                 RETURN("KEYWORD", "BREAK");
"catch"                 RETURN("KEYWORD", "CATCH");
"char"                  RETURN("KEYWORD", "CHAR");
"class"                 RETURN("KEYWORD", "CLASS");
"const"                 RETURN("KEYWORD", "CONST");
"continue"              RETURN("KEYWORD", "CONTINUE");
"coroutine"             RETURN("KEYWORD", "COROUTINE");
"def"                   RETURN("KEYWORD", "DEF");
"defer"                 RETURN("KEYWORD", "DEFER");
"default"               RETURN("KEYWORD", "DEFAULT");
"do"                    RETURN("KEYWORD", "DO");
"double"                RETURN("KEYWORD", "DOUBLE");
"else"                  RETURN("KEYWORD", "ELSE");
"enum"                  RETURN("KEYWORD", "ENUM");
"ext"                   RETURN("KEYWORD", "EXT");
"float"                 RETURN("KEYWORD", "FLOAT");
"for"                   RETURN("KEYWORD", "FOR");
"if"                    RETURN("KEYWORD", "IF");
"import"                RETURN("KEYWORD", "IMPORT");
"in"                    RETURN("KEYWORD", "IN");
"int"                   RETURN("KEYWORD", "INT");
"interface"             RETURN("KEYWORD", "INTERFACE");
"lazy"                  RETURN("KEYWORD", "LAZY");
"long"                  RETURN("KEYWORD", "LONG");
"new"                   RETURN("KEYWORD", "NEW");
"not"				    RETURN("KEYWORD", "NOT");
"or"                    RETURN("KEYWORD", "OR");
"pass"                  RETURN("KEYWORD", "PASS");
"private"               RETURN("KEYWORD", "PRIVATE");
"protected"             RETURN("KEYWORD", "PROTECTED");
"public"                RETURN("KEYWORD", "PUBLIC");
"return"                RETURN("KEYWORD", "RETURN");
"short"                 RETURN("KEYWORD", "SHORT");
"sizeof"                RETURN("KEYWORD", "SIZEOF");
"stackalloc"            RETURN("KEYWORD", "STACKALLOC");
"static"                RETURN("KEYWORD", "STATIC");
"string"                RETURN("KEYWORD", "STRING");
"struct"                RETURN("KEYWORD", "STRUCT");
"switch"                RETURN("KEYWORD", "SWITCH");
"task"                  RETURN("KEYWORD", "TASK");
"this"                  RETURN("KEYWORD", "THIS");
"throw"                 RETURN("KEYWORD", "THROW");
"try"                   RETURN("KEYWORD", "TRY");
"typeof"                RETURN("KEYWORD", "TYPEOF");
"uchar"                 RETURN("KEYWORD", "UCHAR");
"uint"                  RETURN("KEYWORD", "UINT");
"ulong"                 RETURN("KEYWORD", "ULONG");
"ushort"                RETURN("KEYWORD", "USHORT");
"virtual"               RETURN("KEYWORD", "VIRTUAL");
"volatile"              RETURN("KEYWORD", "VOLATILE");
"where"                 RETURN("KEYWORD", "WHERE");
"while"                 RETURN("KEYWORD", "WHILE");
"finally"               RETURN("KEYWORD", "FINALLY");

#identifiers
[_a-zA-Z][_a-zA-Z0-9]*  				RETURN("IDENTIFIER", yytext);

#string_literal
<INITIAL>{
	"\""					BEGIN(IN_STRING);
}
<IN_STRING>{
	"\""					BEGIN(INITIAL);
	([^\"\\\\]|\\\\)*		RETURN("STRING", yytext);
}

#inline_comment
\/\/.*                     RETURN("COMMENT", yytext);


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
[-+]?([0]|[1-9]*)[lL]?	RETURN("INTEGER", yytext);


#binary_integer
[-+]?0[bB][0-1]+             RETURN("BININTEGER", yytext);

#oct_integer
[-+]?0[oO]?[0-7]+				RETURN("OCTINTEGER", yytext);

#hexidecimal_integer
[-+]?0[xX][0-9a-fA-F]+					RETURN("HEXINTEGER", yytext);

#floating_number
[-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?    RETURN("FLOATINGNUMBER", yytext);


#arithmetic_operator
"+"		                    RETURN("OP_ARITHMETIC", yytext);
"-"		                    RETURN("OP_ARITHMETIC", yytext);
"*"                      	RETURN("OP_ARITHMETIC", yytext);
\/                       	RETURN("OP_ARITHMETIC", yytext);
"%"                      	RETURN("OP_ARITHMETIC", yytext);

#assignment_operator
"="		                    RETURN("OP_ASSIGNMENT", yytext);
"+="						RETURN("OP_ASSIGNMENT", yytext);
"-="						RETURN("OP_ASSIGNMENT", yytext);
"*="						RETURN("OP_ASSIGNMENT", yytext);
"/="						RETURN("OP_ASSIGNMENT", yytext);
"%="						RETURN("OP_ASSIGNMENT", yytext);

#bitwise_operator
"~"							RETURN("OP_BITWISE", yytext);
"&"							RETURN("OP_BITWISE", yytext);
"|"							RETURN("OP_BITWISE", yytext);
"^"							RETURN("OP_BITWISE", yytext);
"~="						RETURN("OP_BITWISE", yytext);
"&="						RETURN("OP_BITWISE", yytext);
"|="						RETURN("OP_BITWISE", yytext);
"^="						RETURN("OP_BITWISE", yytext);
"<<"						RETURN("OP_BITWISE", yytext);
">>"						RETURN("OP_BITWISE", yytext);
"<<="						RETURN("OP_BITWISE", yytext);
">>="						RETURN("OP_BITWISE", yytext);

#equality_operator
"=="						RETURN("OP_EQUALITY", yytext);
">"                    		RETURN("OP_EQUALITY", yytext);
"<"                    		RETURN("OP_EQUALITY", yytext);
">="                    	RETURN("OP_EQUALITY", yytext);
"<="                    	RETURN("OP_EQUALITY", yytext);

#increment_&_decrement
"++"						RETURN("OP_INCREMENT", yytext);
"--"						RETURN("OP_DECREMENT", yytext);

#lambda_operator
"=>"						RETURN("OP_LAMBDA", yytext);


#dot
"."               			RETURN("DOT", yytext);

#comma
","             			RETURN("COMMA", yytext);

#space
" "             			RETURN("SPACE", yytext);

#colon
":"              			RETURN("COLON", yytext);

#bracket
"("|")"               	     RETURN("BRACKET", yytext);


#sqaure_bracket
"["|"]"               		RETURN("SQUARE_BRACKET", yytext);


#curly_braces
"{"|"}"                     RETURN("CURLY_BRACE", yytext);

#pond
"#"              			RETURN("POND", yytext);

#whitespace
WHITESPACE                 RETURN("WHITESPACE", yytext);

#escape
ESCAPE                     RETURN("ESCAPE", yytext);
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

