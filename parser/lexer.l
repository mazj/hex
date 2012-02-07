%{
#include <stdio.h>
%}

%%
#keywords
base                 printf("[KEYWORD]\n%s\n\n", yytext);
bool                 printf("[KEYWORD]\n%s\n\n", yytext);
break                printf("[KEYWORD]\n%s\n\n", yytext);
catch                printf("[KEYWORD]\n%s\n\n", yytext);
char                 printf("[KEYWORD]\n%s\n\n", yytext);
class                printf("[KEYWORD]\n%s\n\n", yytext);
const                printf("[KEYWORD]\n%s\n\n", yytext);
continue             printf("[KEYWORD]\n%s\n\n", yytext);
coroutine            printf("[KEYWORD]\n%s\n\n", yytext);
def                  printf("[KEYWORD]\n%s\n\n", yytext);
default              printf("[KEYWORD]\n%s\n\n", yytext);
define               printf("[KEYWORD]\n%s\n\n", yytext);
do                   printf("[KEYWORD]\n%s\n\n", yytext);
double               printf("[KEYWORD]\n%s\n\n", yytext);
else                 printf("[KEYWORD]\n%s\n\n", yytext);
enum                 printf("[KEYWORD]\n%s\n\n", yytext);
ext                  printf("[KEYWORD]\n%s\n\n", yytext);
float                printf("[KEYWORD]\n%s\n\n", yytext);
for                  printf("[KEYWORD]\n%s\n\n", yytext);
goto                 printf("[KEYWORD]\n%s\n\n", yytext);
if                   printf("[KEYWORD]\n%s\n\n", yytext);
in                   printf("[KEYWORD]\n%s\n\n", yytext);
include              printf("[KEYWORD]\n%s\n\n", yytext);
int                  printf("[KEYWORD]\n%s\n\n", yytext);
interface            printf("[KEYWORD]\n%s\n\n", yytext);
long                 printf("[KEYWORD]\n%s\n\n", yytext);
"long long"          printf("[KEYWORD]\n%s\n\n", yytext);
new                  printf("[KEYWORD]\n%s\n\n", yytext);
pass                 printf("[KEYWORD]\n%s\n\n", yytext);
private              printf("[KEYWORD]\n%s\n\n", yytext);
protected            printf("[KEYWORD]\n%s\n\n", yytext);
public               printf("[KEYWORD]\n%s\n\n", yytext);
readonly             printf("[KEYWORD]\n%s\n\n", yytext);
register             printf("[KEYWORD]\n%s\n\n", yytext);
return               printf("[KEYWORD]\n%s\n\n", yytext);
select               printf("[KEYWORD]\n%s\n\n", yytext);
short                printf("[KEYWORD]\n%s\n\n", yytext);
signed               printf("[KEYWORD]\n%s\n\n", yytext);
sizeof               printf("[KEYWORD]\n%s\n\n", yytext);
static               printf("[KEYWORD]\n%s\n\n", yytext);
string               printf("[KEYWORD]\n%s\n\n", yytext);
struct               printf("[KEYWORD]\n%s\n\n", yytext);
switch               printf("[KEYWORD]\n%s\n\n", yytext);
task                 printf("[KEYWORD]\n%s\n\n", yytext);
this                 printf("[KEYWORD]\n%s\n\n", yytext);
throw                printf("[KEYWORD]\n%s\n\n", yytext);
try                  printf("[KEYWORD]\n%s\n\n", yytext);
typeof               printf("[KEYWORD]\n%s\n\n", yytext);
unsigned" "(char|short|int|long|"long long") printf("[KEYWORD]\n%s\n\n", yytext);
virtual              printf("[KEYWORD]\n%s\n\n", yytext);
void                 printf("[KEYWORD]\n%s\n\n", yytext);
void"*"{1}           printf("[KEYWORD]\n%s\n\n", yytext);
volatile             printf("[KEYWORD]\n%s\n\n", yytext);
where                printf("[KEYWORD]\n%s\n\n", yytext);
while                printf("[KEYWORD]\n%s\n\n", yytext);
finally              printf("[KEYWORD]\n%s\n\n", yytext);

#identifiers
[_a-zA-Z][_a-zA-Z0-9]*    printf("[IDENTIFIER]\n%s\n\n", yytext);

#inline
#comment
\/\/.*                     printf("[INLINE COMMENT]\n%s\n\n", yytext);


#multiline
"/*"(.|\n)*"*/"     printf("[MULTILINE COMMENT]\n%s\n\n", yytext);

#operators
">"{1,2}                    printf("[OPERATOR]\n%s\n\n", yytext);
"<"{1,2}                    printf("[OPERATOR]\n%s\n\n", yytext);
"="{1,2}                    printf("[OPERATOR]\n%s\n\n", yytext);
"+"{1,2}                    printf("[OPERATOR]\n%s\n\n", yytext);
"-"{1,2}                    printf("[OPERATOR]\n%s\n\n", yytext);
"*"{1}                      printf("[OPERATOR]\n%s\n\n", yytext);
\/{1}                       printf("[OPERATOR]\n%s\n\n", yytext);
"%"{1}                      printf("[OPERATOR]\n%s\n\n", yytext);

#dot
"."               printf("[DOT]\n\n");

#comma
","             printf("[COMMA]\n\n");

#space
" "             printf("[SPACE]\n\n");

#colon
":"               printf("[COLON]\n\n");

#left_bracket
"("               printf("[LEFT BRACKET]\n\n");

#right_brakcet
")"               printf("[RIGHT BRACKET]\n\n");

#left_square_bracket
"["               printf("[LEFT SQUARE BRACKET]\n\n");

#right_square_brakcet
"]"               printf("[RIGHT SQUARE BRACKET]\n\n");

#pond
"#"              printf("[POND]\n\n");

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

