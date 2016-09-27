%{

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "parser.h"

#define N_ID 50

#define YYDEBUG 1



int yylex(void);

astNode *constante(int valor);
astNode *identificador(char value[20]);
astNode *criar_nodo_ast(int tokenodo, int nfilhos, ...);
void checarVariaveis(char *id);
int getLabel(int numLabels);
int acumLabel = 0;
void yyerror(char const *s);
void mapearVariavel(char *id);
extern int numero_linhas;
char Identificadores[N_ID][N_ID];
int nvariaveis = 0;
extern yylineno;


%}
%error-verbose

%union {
    int inteiros;                 
    char identificadores[20];               
    astNode *ASTPonteiro;             
};

%token AND ATTRIB 
%token EQUALEQUAL END 
%token ELSE EQUALTIL  
%token GE GT  IF 
%token LE LPAREN LT LOCAL MINUS NOT NOTEQUAL OR EQUAL
%token PLUS 
%token RPAREN 
%token SEMICOLON SLASH STAR THEN 
%token WHILE
%token VAR
%token PRINT
%token DO STMT

%token <inteiros> DIGSEQ TRUE FALSE NIL CHARACTER_STRING
%token <identificadores> IDENTIFIER
%type <ASTPonteiro> lista_comando nobr_statement bloco   expression atribuirVariavel  

%nonassoc IFX
%nonassoc ELSE


%left OR
%left AND 
%left LT GT LE GE EQUALEQUAL NOTEQUAL
%left PLUS MINUS
%left STAR SLASH

%right NOT

%right UMINUS
%left LPAREN RPAREN


%locations

%start bloco  


%%

bloco : lista_comando  {gerarCodigo($1) ; } ;


lista_comando :
lista_comando nobr_statement  {$$ = criar_nodo_ast(STMT, 2, $2, $1); } |
lista_comando nobr_statement SEMICOLON %prec STMT {$$ = criar_nodo_ast(STMT, 2, $2, $1); } |
 {$$ = NULL;}
;



nobr_statement:

IDENTIFIER EQUAL expression {checarVariaveis($1); $$ = criar_nodo_ast(EQUAL, 2, identificador($1),$3); }|
PRINT LPAREN expression RPAREN {$$ = criar_nodo_ast(PRINT, 1, $3);} |
atribuirVariavel {$$ = $1;} |
WHILE expression DO lista_comando END{ $$ = criar_nodo_ast(WHILE, 3, $2, $4); } |
IF expression THEN lista_comando END %prec IFX { $$ = criar_nodo_ast(IF, 2, $2, $4); } |
IF expression THEN lista_comando ELSE lista_comando END { $$ = criar_nodo_ast(IF, 3, $2, $4, $6); } 


;

expression :
FALSE {$$ = constante($1);}
| TRUE  {$$ = constante($1);}
| DIGSEQ {$$ = constante($1);}
| IDENTIFIER {checarVariaveis($1); $$ = identificador($1);}
| expression PLUS expression { $$ = criar_nodo_ast(PLUS, 2, $1, $3); }
| expression MINUS expression { $$ = criar_nodo_ast(MINUS, 2, $1, $3); }
| expression STAR expression  { $$ = criar_nodo_ast(STAR, 2, $1, $3); }
| expression SLASH expression { $$ = criar_nodo_ast(SLASH, 2, $1, $3); }
| expression OR expression  { $$ = criar_nodo_ast(OR, 2, $1, $3); }
| expression AND expression { $$ = criar_nodo_ast(AND, 2, $1, $3); }
| expression LT expression  { $$ = criar_nodo_ast(LT, 2, $1, $3); }
| expression LE expression  { $$ = criar_nodo_ast(LE, 2, $1, $3); }
| expression GT expression  { $$ = criar_nodo_ast(GT, 2, $1, $3); }
| expression GE expression  { $$ = criar_nodo_ast(GE, 2, $1, $3); }
| expression EQUALEQUAL expression { $$ = criar_nodo_ast(EQUALEQUAL, 2, $1, $3); }
| expression NOTEQUAL expression { $$ = criar_nodo_ast(NOTEQUAL, 2, $1, $3); }
| NOT expression {$$ = criar_nodo_ast(NOT, 1, $2);}
| MINUS expression %prec UMINUS {$$ = criar_nodo_ast(UMINUS, 1, $2);}
| LPAREN expression RPAREN {$$ = $2;}
;
 
 atribuirVariavel:
        VAR IDENTIFIER %prec ATTRIB                 { mapearVariavel($2); $$ = criar_nodo_ast(ATTRIB, 2, identificador($2), constante(0));}
        | VAR IDENTIFIER EQUAL expression %prec ATTRIB    { mapearVariavel($2); $$ = criar_nodo_ast(ATTRIB, 2, identificador($2), $4); }




%%
extern int numero_linhas;
extern char *yytext;



astNode *constante(int valor) {
    astNode *an = malloc(sizeof(astNode));

    an->tipoNodo = Const;
    an->constante.valorConst = valor;

    return an;
}
astNode *identificador(char *id) {
    astNode *an = malloc(sizeof(astNode));
	char valor2[20];
	strcpy(valor2, "_");
    an->tipoNodo = Identif;
	strcat(valor2, id);
	strcpy(an->ident.valor, valor2);
	return an; 
}



astNode *criar_nodo_ast(int tokenodo, int nfilhos, ...) {
    va_list ap;
    astNode *an = malloc(sizeof(astNode));
    int i;
	
	an->astn.filhos = malloc(nfilhos * sizeof(astNode *));
	va_start(ap, nfilhos);
    
    an->tipoNodo = Ast;
    an->astn.tokenOpr = tokenodo;
    an->astn.n_filhos = nfilhos;

    i = 0;
    while (i < nfilhos) {
		an->astn.filhos[i] = va_arg(ap, astNode*);
		i++;
    }
         
    va_end(ap);
    return an;
}

void yyerror(char const *s) {
    fprintf(stdout, "linha %d: %s\n",yylineno, s);
}

int getLabel(int numLabels)
{
	int valTemp = acumLabel;
	acumLabel += numLabels;
	
	return valTemp;
}


int main(void) {
 
    yyparse();
    printf("li\t $v0, 10\n");  
    printf("syscall\n");
    return 0;
}

void mapearVariavel(char *id)
{
	strcpy(Identificadores[nvariaveis++], id);
}

void checarVariaveis(char *id)
{
int i;
for(i=0; i < nvariaveis; i++)
{
	if(strcmp(Identificadores[i], id) == 0)
	{
		return;
	}
}
printf("Erro semântico na linha %d: variável %s não declarada!\n", yylineno, id); 
exit(0);
}
