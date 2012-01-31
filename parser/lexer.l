%{
#include <stdio.h>
%}

%%
bool{1}                 printf("keyword: %s\n", yytext);
break{1}                printf("keyword: %s\n", yytext);
char{1}                 printf("keyword: %s\n", yytext);
class{1}                printf("keyword: %s\n", yytext);
coroutine{1}            printf("keyword: %s\n", yytext);
def{1}                  printf("keyword: %s\n", yytext);
default{1}              printf("keyword: %s\n", yytext);
define{1}               printf("keyword: %s\n", yytext);
do{1}                   printf("keyword: %s\n", yytext);
double{1}               printf("keyword: %s\n", yytext);
else{1}                 printf("keyword: %s\n", yytext);
ext{1}                  printf("keyword: %s\n", yytext);
float{1}                printf("keyword: %s\n", yytext);
if{1}                   printf("keyword: %s\n", yytext);
in{1}                   printf("keyword: %s\n", yytext);
include{1}              printf("keyword: %s\n", yytext);
int{1}                  printf("keyword: %s\n", yytext);
interface{1}            printf("keyword: %s\n", yytext);
long{2}                 printf("keyword: %s\n", yytext);
pass{1}                 printf("keyword: %s\n", yytext);
private{1}              printf("keyword: %s\n", yytext);
protected{1}            printf("keyword: %s\n", yytext);
public{1}               printf("keyword: %s\n", yytext);
return{1}               printf("keyword: %s\n", yytext);
short{1}                printf("keyword: %s\n", yytext);
string{1}               printf("keyword: %s\n", yytext);
switch{1}               printf("keyword: %s\n", yytext);
task{1}                 printf("keyword: %s\n", yytext);
this{1}                 printf("keyword: %s\n", yytext);
unsigned{1}             printf("keyword: %s\n", yytext);
void{1}                 printf("keyword: %s\n", yytext);
void*{1}                printf("keyword: %s\n", yytext);
while{1}                printf("keyword: %s\n", yytext);

[a-zA-Z][a-zA-Z0-9]*    printf("identifier: %s\n", yytext);
%%

int main(int argc, char** argv) {
    if((yyin = fopen("lexer_file", "r")) == 0) {
        exit(1);
    }
    while(yylex())
            ;
    return 0;
}

int yywrap() {
    fclose(yyin);
    return 1;
}

