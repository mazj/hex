%{
#include <stdio.h>
%}

%%
bool{1}                 printf("keyword: %s", yytext);
break{1}                printf("keyword: %s", yytext);
char{1}                 printf("keyword: %s", yytext);
class{1}                printf("keyword: %s", yytext);
const{1}                printf("keyword: %s", yytext);
continue{1}             printf("keyword: %s", yytext);
coroutine{1}            printf("keyword: %s", yytext);
def{1}                  printf("keyword: %s", yytext);
default{1}              printf("keyword: %s", yytext);
define{1}               printf("keyword: %s", yytext);
do{1}                   printf("keyword: %s", yytext);
double{1}               printf("keyword: %s", yytext);
else{1}                 printf("keyword: %s", yytext);
enum{1}                 printf("keyword: %s", yytext);
ext{1}                  printf("keyword: %s", yytext);
float{1}                printf("keyword: %s", yytext);
for{1}                  printf("keyword: %s", yytext);
goto{1}                 printf("keyword: %s", yytext);
if{1}                   printf("keyword: %s", yytext);
in{1}                   printf("keyword: %s", yytext);
include{1}              printf("keyword: %s", yytext);
int{1}                  printf("keyword: %s", yytext);
interface{1}            printf("keyword: %s", yytext);
long{1}                 printf("keyword: %s", yytext);
pass{1}                 printf("keyword: %s", yytext);
private{1}              printf("keyword: %s", yytext);
protected{1}            printf("keyword: %s", yytext);
public{1}               printf("keyword: %s", yytext);
register{1}             printf("keyword: %s", yytext);
return{1}               printf("keyword: %s", yytext);
short{1}                printf("keyword: %s", yytext);
signed{1}               printf("keyword: %s", yytext);
sizeof{1}               printf("keyword: %s", yytext);
static{1}               printf("keyword: %s", yytext);
string{1}               printf("keyword: %s", yytext);
struct{1}               printf("keyword: %s", yytext);
switch{1}               printf("keyword: %s", yytext);
task{1}                 printf("keyword: %s", yytext);
this{1}                 printf("keyword: %s", yytext);
unsigned{1}             printf("keyword: %s", yytext);
void{1}                 printf("keyword: %s", yytext);
void[*]{1}              printf("keyword: %s", yytext);
volatile{1}             printf("keyword: %s", yytext);
while{1}                printf("keyword: %s", yytext);

[_a-zA-Z][_a-zA-Z0-9]*    printf("identifier: %s", yytext);

\/\/.*                     printf("inline comment: %s", yytext);



(\/"*"){1}.*("*"\/){1}      printf("multiline comment: %s", yytext);

">"{1,2}                    printf("operator: %s", yytext);
"<"{1,2}                    printf("operator: %s", yytext);
"="{1,2}                    printf("operator: %s", yytext);
"+"{1,2}                    printf("operator: %s", yytext);
"-"{1,2}                    printf("operator: %s", yytext);
"*"                        printf("operator: %s", yytext);
\/                  printf("operator: %s", yytext);
"%"                        printf("operator: %s", yytext);

"."               printf("dot: %s\n", yytext);



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

