%{
#include <stdio.h>
#include "parser.h"
#include "y.tab.h"

int numero_linhas = 1;

%}

%option yylineno
%option yywrap

letra         [A-Za-z]
numero           [0-9]
id              ({letra}|_)({letra}|({numero}|_))*

nPositivo    [1-9][0-9]*
zero            0
num          {nPositivo}|{zero}

%%



{num}    {
                yylval.inteiros = atoi(yytext);
                return DIGSEQ;
            }

"+"             return PLUS;
"-"             return MINUS;
"*"             return STAR;
"/"             return SLASH;


">="            return GE;
"<="            return LE;
"=="            return EQUALEQUAL;
"~="            return NOTEQUAL;
">"             return GT;
"<"             return LT;


"("             return LPAREN;
")"             return RPAREN;
"="             return EQUAL;

"and"           return AND;
"do"            return DO;
"else"          return ELSE;
"while"         return WHILE;
"then"          return THEN;
"end"           return END;
"var"           return VAR;
"or"            return OR;
"not"           return NOT;
"if"			return IF;


"print"         return PRINT;

[;]           return SEMICOLON;

[{}]         {
                return *yytext;
             }

{id}        { 
                strcpy(yylval.identificadores, yytext);
                return IDENTIFIER;
            }

[ \t\n]+        ;       /* ignoring whitespace */



.           yyerror("Caracter desconhecido!");
%%
int yywrap(void) {
    return 1;
}

