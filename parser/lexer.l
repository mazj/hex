%{
#include <stdio.h>
%}

%%
#keywords
bool                 printf("keyword: %s\n", yytext);
break                printf("keyword: %s\n", yytext);
catch                printf("keyword: %s\n", yytext);
char                 printf("keyword: %s\n", yytext);
class                printf("keyword: %s\n", yytext);
const                printf("keyword: %s\n", yytext);
continue             printf("keyword: %s\n", yytext);
coroutine            printf("keyword: %s\n", yytext);
def                  printf("keyword: %s\n", yytext);
default              printf("keyword: %s\n", yytext);
define               printf("keyword: %s\n", yytext);
do                   printf("keyword: %s\n", yytext);
double               printf("keyword: %s\n", yytext);
else                 printf("keyword: %s\n", yytext);
enum                 printf("keyword: %s\n", yytext);
ext                  printf("keyword: %s\n", yytext);
float                printf("keyword: %s\n", yytext);
for                  printf("keyword: %s\n", yytext);
goto                 printf("keyword: %s\n", yytext);
if                   printf("keyword: %s\n", yytext);
in               printf("keyword: %s\n", yytext);
include              printf("keyword: %s\n", yytext);
int                  printf("keyword: %s\n", yytext);
interface          printf("keyword: %s\n", yytext);
long          printf("keyword: %s\n", yytext);
"long long" printf("keyword: %s\n", yytext);
new                 printf("keyword: %s\n", yytext);
pass                 printf("keyword: %s\n", yytext);
private              printf("keyword: %s\n", yytext);
protected            printf("keyword: %s\n", yytext);
public               printf("keyword: %s\n", yytext);
readonly               printf("keyword: %s\n", yytext);
register             printf("keyword: %s\n", yytext);
return               printf("keyword: %s\n", yytext);
select               printf("keyword: %s\n", yytext);
short                printf("keyword: %s\n", yytext);
signed               printf("keyword: %s\n", yytext);
sizeof               printf("keyword: %s\n", yytext);
static               printf("keyword: %s\n", yytext);
string               printf("keyword: %s\n", yytext);
struct               printf("keyword: %s\n", yytext);
switch               printf("keyword: %s\n", yytext);
task                 printf("keyword: %s\n", yytext);
this                 printf("keyword: %s\n", yytext);
throw                printf("keyword: %s\n", yytext);
try                  printf("keyword: %s\n", yytext);
typeof               printf("keyword: %s\n", yytext);
unsigned" "(char|short|int|long|"long long") printf("keyword: %s\n", yytext);
virtual              printf("keyword: %s\n", yytext);
void                 printf("keyword: %s\n", yytext);
void"*"{1}              printf("keyword: %s\n", yytext);
volatile             printf("keyword: %s\n", yytext);
where                printf("keyword: %s\n", yytext);
while                printf("keyword: %s\n", yytext);
finally              printf("keyword: %s\n", yytext);

#identifiers
[_a-zA-Z][_a-zA-Z0-9]*    printf("identifier: %s\n", yytext);

#inline
#comment
\/\/.*                     printf("inline comment: %s\n", yytext);


#multiline
"/*"(.|\n)*"*/"     printf("multiline comment: %s\n", yytext);

#operators
">"{1,2}                    printf("operator: %s\n", yytext);
"<"{1,2}                    printf("operator: %s\n", yytext);
"="{1,2}                    printf("operator: %s\n", yytext);
"+"{1,2}                    printf("operator: %s\n", yytext);
"-"{1,2}                    printf("operator: %s\n", yytext);
"*"{1}                    printf("operator: %s\n", yytext);
\/{1}                 printf("operator: %s\n", yytext);
"%"{1}                      printf("operator: %s\n", yytext);

#dot
"."               printf("dot: %s\n", yytext);

#space
" "             printf("[SPACE]\n", yytext);

\b             printf("[BACKSPACE]\n");
\f             printf("[FORM FEED]\n");
\n             printf("[CARRIAGE RETURN]\n");
\t              printf("[TAB]\n");
\0             printf("[NULL CHARACTER]\n");
%%

int main(int argc, char** argv) {
    if((yyin = fopen("lexer_file", "r")) == 0) {
        exit(1);
    }
    yylex();
    return 0;
}

int yywrap() {
    fclose(yyin);
    return 1;
}

