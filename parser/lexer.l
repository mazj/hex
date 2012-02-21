%{
#include <stdio.h>
#include "parser.tab.h"

#define RETURN(type, token)						\
		printf("[%s]: %s\n", (type), (token));	
%}


/* underscore */
UNDERSCORE          "_"

COMMENT            "/*"(.|\n)*"*/"

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
NONZERODIGIT		[0-9]												// none zero digit
HEXDIGIT			DIGIT | [a-f] | [A-F]							// hex digit

/* integer and long integer literals */
BININTEGER			"0"("b"|"B") BINDIGIT+									// binary integer
OCTINTEGER			"0"("o"|"O") OCTDIGIT+ | "0" OCTDIGIT+					// oct integer
HEXINTEGER			"0"("x"|"X") HEXDIGIT+									// hex integer
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


%x IN_COMMENT

%%


#keywords
"and"					 RETURN("KEYWORD", "and");
"as"					 RETURN("KEYWORD", "as");
"base"                 RETURN("KEYWORD", "base");
"bool"                 RETURN("KEYWORD", "bool");
"break"                RETURN("KEYWORD", "break");
"catch"                RETURN("KEYWORD", "catch");
"char"                 RETURN("KEYWORD", "char");
"class"                RETURN("KEYWORD", "class");
"const"                RETURN("KEYWORD", "const");
"continue"             RETURN("KEYWORD", "continue");
"coroutine"            RETURN("KEYWORD", "coroutine");
"def"                  RETURN("KEYWORD", "def");
"defer"                RETURN("KEYWORD", "defer");
"default"              RETURN("KEYWORD", "default");
"do"                   RETURN("KEYWORD", "do");
"double"               RETURN("KEYWORD", "double");
"else"                 RETURN("KEYWORD", "else");
"enum"                 RETURN("KEYWORD", "enum");
"ext"                  RETURN("KEYWORD", "ext");
"float"                RETURN("KEYWORD", "float");
"for"                  RETURN("KEYWORD", "for");
"if"                   RETURN("KEYWORD", "if");
"import"               RETURN("KEYWORD", "import");
"in"                   RETURN("KEYWORD", "in");
"int"                  RETURN("KEYWORD", "int");
"interface"            RETURN("KEYWORD", "interface");
"lazy"                 RETURN("KEYWORD", "lazy");
"long"                 RETURN("KEYWORD", "long");
"new"                  RETURN("KEYWORD", "new");
"not"					 RETURN("KEYWORD", "not");
"or"                   RETURN("KEYWORD", "or");
"pass"                 RETURN("KEYWORD", "pass");
"private"              RETURN("KEYWORD", "private");
"protected"            RETURN("KEYWORD", "protected");
"public"               RETURN("KEYWORD", "public");
"return"               RETURN("KEYWORD", "return");
"short"                RETURN("KEYWORD", "short");
"sizeof"               RETURN("KEYWORD", "sizeof");
"stackalloc"		     RETURN("KEYWORD", "stackalloc");
"static"               RETURN("KEYWORD", "static");
"string"               RETURN("KEYWORD", "string");
"struct"               RETURN("KEYWORD", "struct");
"switch"               RETURN("KEYWORD", "switch");
"task"                 RETURN("KEYWORD", "task");
"this"                 RETURN("KEYWORD", "this");
"throw"                RETURN("KEYWORD", "throw");
"try"                  RETURN("KEYWORD", "try");
"typeof"               RETURN("KEYWORD", "typeof");
"uchar"                 RETURN("KEYWORD", "typeof");
"uint"                  RETURN("KEYWORD", "typeof");
"ulong"                 RETURN("KEYWORD", "typeof");
"ushort"                RETURN("KEYWORD", "typeof");
"virtual"              RETURN("KEYWORD", "virtual");
"volatile"             RETURN("KEYWORD", "volatile");
"where"                RETURN("KEYWORD", "where");
"while"                RETURN("KEYWORD", "while");
"finally"              RETURN("KEYWORD", "finally");

#identifiers
[_a-zA-Z][_a-zA-Z0-9]*  				RETURN("IDENTIFIER", yytext);

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




#integer_number


#floating_number
FLOATNUMBER                 RETURN("FLOATINTEGER", yytext);


#arithmetic_operator
"+"		                    RETURN("OP_ARITHMETIC", yytext);
"-"		                    RETURN("OP_ARITHMETIC", yytext);
"*"{1}                      RETURN("OP_ARITHMETIC", yytext);
\/{1}                       RETURN("OP_ARITHMETIC", yytext);
"%"{1}                      RETURN("OP_ARITHMETIC", yytext);

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

