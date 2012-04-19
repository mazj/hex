%{
#include <stdio.h>
#include "parser3.tab.h"

int current_line_indent = 0;            /* indentation of current line */
int indent_level = 0;                   /* indentation level passed to parser */
int this_line_already_returned = 0;
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
"and"                       printf("%s\n", yytext);
"as"			            printf("%s\n", yytext);
"base"                      printf("%s\n", yytext);
"bool"                      printf("%s\n", yytext);
"break"                     printf("%s\n", yytext);
"case"                      printf("%s\n", yytext);
"catch"                     printf("%s\n", yytext);
"char"                      printf("%s\n", yytext);
"class"                     printf("%s\n", yytext);
"const"                     printf("%s\n", yytext);
"continue"                  printf("%s\n", yytext);
"coroutine"                 printf("%s\n", yytext);
"def"                       printf("%s\n", yytext);
"defer"                     printf("%s\n", yytext);
"default"                   printf("%s\n", yytext);
"do"                        printf("%s\n", yytext);
"double"                    printf("%s\n", yytext);
"elif"                      printf("%s\n", yytext);
"else"                      printf("%s\n", yytext);
"ext"                       printf("%s\n", yytext);
"float"                     printf("%s\n", yytext);
"for"                       printf("%s\n", yytext);
"from"                      printf("%s\n", yytext);
"if"                        printf("%s\n", yytext);
"import"                    printf("%s\n", yytext);
"in"                        printf("%s\n", yytext);
"int"                       printf("%s\n", yytext);
"interface"                 printf("%s\n", yytext);
"is"                        printf("%s\n", yytext);
"is not"                    printf("%s\n", yytext);                    
"lazy"                      printf("%s\n", yytext);
"lock"                      printf("%s\n", yytext);
"long"                      printf("%s\n", yytext);
"new"                       printf("%s\n", yytext);
"not"				        printf("%s\n", yytext);
"or"                        printf("%s\n", yytext);
"pass"                      printf("%s\n", yytext);
"private"                   printf("%s\n", yytext);
"protected"                 printf("%s\n", yytext);
"public"                    printf("%s\n", yytext);
"ref"                       printf("%s\n", yytext);
"return"                    printf("%s\n", yytext);
"short"                     printf("%s\n", yytext);
"sizeof"                    printf("%s\n", yytext);
"stackalloc"                printf("%s\n", yytext);
"static"                    printf("%s\n", yytext);
"string"                    printf("%s\n", yytext);
"struct"                    printf("%s\n", yytext);
"switch"                    printf("%s\n", yytext);
"task"                      printf("%s\n", yytext);
"then"                      printf("%s\n", yytext);
"this"                      printf("%s\n", yytext);
"throw"                     printf("%s\n", yytext);
"try"                       printf("%s\n", yytext);
"typeof"                    printf("%s\n", yytext);
"uchar"                     printf("%s\n", yytext);
"uint"                      printf("%s\n", yytext);
"ulong"                     printf("%s\n", yytext);
"unlock"                    printf("%s\n", yytext);
"ushort"                    printf("%s\n", yytext);
"virtual"                   printf("%s\n", yytext);
"volatile"                  printf("%s\n", yytext);
"_weakref"                  printf("%s\n", yytext);
"where"                     printf("%s\n", yytext);
"while"                     printf("%s\n", yytext);
"finally"                   printf("%s\n", yytext);

#identifiers
[_a-zA-Z][_a-zA-Z0-9]*      printf("IDENTIFIER [%s]\n", yytext);

#character_literal
L?'(\\.|[^\\'])+'           printf("CHARACTER [%s]\n", yytext);

#string_literal
L?\"(\\.|[^\\"])*\"         printf("STRING [%s]\n", yytext);

#inline_comment
\/\/.*                      printf("INLINE COMMENT [%s]\n", yytext);

#integer
([0]|[0-9]*)[lL]?	        printf("INTEGER [%s]\n", yytext);


#binary_integer
0[bB][0-1]+                 printf("BININTEGER [%s]\n", yytext);

#oct_integer
0[oO][0-7]+		            printf("OCTINTEGER [%s]\n", yytext);

#hexidecimal_integer
0[xX][0-9a-fA-F]+           printf("HEXINTEGER [%s]\n", yytext);

#floating_number
[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?  printf("FLOATINGNUM [%s]\n", yytext);


#arithmetic_operator
"+"                         printf("ARITHMETIC OPERATOR [%s]\n", yytext);
"-"                         printf("ARITHMETIC OPERATOR [%s]\n", yytext);
"*"                      	printf("ARITHMETIC OPERATOR [%s]\n", yytext);
"/"                       	printf("ARITHMETIC OPERATOR [%s]\n", yytext);
"%"                      	printf("ARITHMETIC OPERATOR [%s]\n", yytext);

#assignment_operator
"="		                    printf("ASSIGNMENT OPERATOR [%s]\n", yytext);
"~="                        printf("ASSIGNMENT OPERATOR [%s]\n", yytext);  
"+="						printf("ASSIGNMENT OPERATOR [%s]\n", yytext);
"-="						printf("ASSIGNMENT OPERATOR [%s]\n", yytext);
"*="						printf("ASSIGNMENT OPERATOR [%s]\n", yytext);
"/="						printf("ASSIGNMENT OPERATOR [%s]\n", yytext);
"%="						printf("ASSIGNMENT OPERATOR [%s]\n", yytext);

#bitwise_operator
"~"							printf("BITWISE OPERATOR [%s]\n", yytext);
"&"							printf("BITWISE OPERATOR [%s]\n", yytext);
"|"							printf("BITWISE OPERATOR [%s]\n", yytext);
"^"							printf("BITWISE OPERATOR [%s]\n", yytext);
"<<"                        printf("BITWISE OPERATOR [%s]\n", yytext);
">>"                        printf("BITWISE OPERATOR [%s]\n", yytext); 
"&="						printf("BITWISE OPERATOR [%s]\n", yytext);
"|="						printf("BITWISE OPERATOR [%s]\n", yytext);
"^="						printf("BITWISE OPERATOR [%s]\n", yytext);
"<<="						printf("BITWISE OPERATOR [%s]\n", yytext);
">>="						printf("BITWISE OPERATOR [%s]\n", yytext);

#equality_operator
"=="						printf("EQUALITY OPERATOR [%s]\n", yytext);
"!="                        printf("EQUALITY OPERATOR [%s]\n", yytext);
">"                    		printf("EQUALITY OPERATOR [%s]\n", yytext);
"<"                    		printf("EQUALITY OPERATOR [%s]\n", yytext);
">="                    	printf("EQUALITY OPERATOR [%s]\n", yytext);
"<="                    	printf("EQUALITY OPERATOR [%s]\n", yytext);

#increment_&_decrement
"++"						printf("INCREMENT [%s]\n", yytext);
"--"						printf("DECREMENT [%s]\n", yytext);

#lambda_operator
"=>"						printf("LAMBDA OPERATOR [%s]\n", yytext);


#dot
"."               			printf("DOT\n");

#comma
","             			printf("COMMA\n");

#semicolon
";"                         printf("SEMICOLON\n");

#colon
":"              			printf("COLON\n");

#bracket
"("                         printf("LEFT PAREN\n");
")"               	        printf("RIGHT PAREN\n");


#sqaure_bracket
"["                         printf("LEFT SQUARE BRACKET\n");
"]"               		    printf("RIGHT SQUARE BRACKET\n");


#curly_braces
"{"                         printf("LEFT CURLY_BRACE\n");
"}"                         printf("RIGHT CURLY_BRACE\n");

#ellipsis
"..."                       printf("ELIPSIS\n");

#pond
"#"              			printf("POND\n");

#at
"@"                         printf("AT\n");

#multi-line_comment
<INITIAL>{
"/*"                            BEGIN(IN_COMMENT);
}

<IN_COMMENT>{
"*/"                            BEGIN(INITIAL);
[^*\n]+                         // eat comment in chunks
"*"                             // eat the lone star
\n                              yylineno++;
}

<INITIAL>\n                 {
                                current_line_indent = 0;
                                yy_push_state(IN_INDENT); //this solves the "return NEWLINE before BEGIN(IN_INDENT)" issue
                                printf("NEWLINE\n");
                            }

#indentation
<IN_INDENT>"  "             {
                                current_line_indent++;
                            }

<IN_INDENT>\t               {
                                /* tab */
                                printf("TAB\n");
                            }

<IN_INDENT>\n               {
                                current_line_indent = 0; /* ignore blank line*/
                                printf("NEWLINE\n");
                            }

<IN_INDENT>.                {
                                /* puts the character back to input stream and scans next character */
                                unput(*yytext);
                                if(current_line_indent > indent_level) {
                                    indent_level++;
                                    printf("INDENT\n");
                                } else if(current_line_indent < indent_level) {
                                    indent_level--;
                                    printf("DEDENT\n");
                                } else {
                                    BEGIN(INITIAL);
                                }
                            }

.                           {
                                /* ignore bad characters */
                            }


%%

int main(int argc, char** argv) {
    if((yyin = fopen(argv[1], "r")) == 0) {
        exit(1);
    }
    yylex();
    return 0;
}