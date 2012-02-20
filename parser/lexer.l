%{
#include <stdio.h>
#include "parser.tab.h"

#define RETURN(type, token)	\
		printf("[%s]: %s\n", (type), (token));
		return token;
%}

/* digits */
DIGITS              [0-9]

%%


#keywords
and					 RETURN("KEYWORD", "and");
base                 RETURN("KEYWORD", "base");
bool                 RETURN("KEYWORD", "bool");
break                RETURN("KEYWORD", "break");
catch                RETURN("KEYWORD", "catch");
char                 RETURN("KEYWORD", "char");
class                RETURN("KEYWORD", "class");
const                RETURN("KEYWORD", "const");
continue             RETURN("KEYWORD", "continue");
coroutine            RETURN("KEYWORD", "coroutine");
def                  RETURN("KEYWORD", "def");
defer                RETURN("KEYWORD", "defer");
default              RETURN("KEYWORD", "default");
do                   RETURN("KEYWORD", "do");
double               RETURN("KEYWORD", "double");
else                 RETURN("KEYWORD", "else");
enum                 RETURN("KEYWORD", "enum");
ext                  RETURN("KEYWORD", "ext");
float                RETURN("KEYWORD", "float");
for                  RETURN("KEYWORD", "for");
if                   RETURN("KEYWORD", "if");
import               RETURN("KEYWORD", "import");
in                   RETURN("KEYWORD", "in");
int                  RETURN("KEYWORD", "int");
interface            RETURN("KEYWORD", "interface");
lazy                 RETURN("KEYWORD", "lazy");
long                 RETURN("KEYWORD", "long");
new                  RETURN("KEYWORD", "new");
not					 RETURN("KEYWORD", "not");
or                   RETURN("KEYWORD", "or");
pass                 RETURN("KEYWORD", "pass");
private              RETURN("KEYWORD", "private");
protected            RETURN("KEYWORD", "protected");
public               RETURN("KEYWORD", "public");
return               RETURN("KEYWORD", "return");
short                RETURN("KEYWORD", "short");
sizeof               RETURN("KEYWORD", "sizeof");
stackalloc		     RETURN("KEYWORD", "stackalloc");
static               RETURN("KEYWORD", "static");
string               RETURN("KEYWORD", "string");
struct               RETURN("KEYWORD", "struct");
switch               RETURN("KEYWORD", "switch");
task                 RETURN("KEYWORD", "task");
this                 RETURN("KEYWORD", "this");
throw                RETURN("KEYWORD", "throw");
try                  RETURN("KEYWORD", "try");
typeof               RETURN("KEYWORD", "typeof");
unsigned" "(char|short|int|long) RETURN("KEYWORD", "TYPE ALIAS");
virtual              RETURN("KEYWORD", "virtual");
volatile             RETURN("KEYWORD", "volatile");
where                RETURN("KEYWORD", "where");
while                RETURN("KEYWORD", "while");
finally              RETURN("KEYWORD", "finally");

#identifiers
[_a-zA-Z][_a-zA-Z0-9]*    RETURN("IDENTIFIER", yytext);

#inline_comment
\/\/.*                     RETURN("COMMENT", yytext);


#multi-line_comment
"/*"(.|\n)*"*/"     		RETURN("COMMENT", yytext);

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
("("|")")               	RETURN("BRACKET", yytext);


#sqaure_bracket
"["|"]"               		RETURN("SQUARE_BRACKET", yytext);


#pond
"#"              			RETURN("POND", yytext);

\b             printf("[BACKSPACE]\n\n");
\f             printf("[FORM FEED]\n\n");
\n             printf("[CARRIAGE RETURN]\n\n");
\t              printf("[TAB]\n\n");
\0             printf("[NULL CHARACTER]\n\n");
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

