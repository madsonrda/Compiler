//MATA61 - COMPILADORES
//SEMESTRE 2015.1
//ALUNOS: JEAN FRANCESCOLI E MADSON ARAUJO

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "y.tab.h"
#include "geracaocodigo.h"


char* c;


int flagCond = -1; //Flag que vai indicar qual tipo de operador estamos lhe dando, no caso seria > < <= >= == !=

int cabecalho = 0;

void gerarCodigoAND(astNode *an)
{
	gerarCodigo(an->astn.filhos[0]);
	emitirInstrucao(0);
	gerarCodigo(an->astn.filhos[1]);
	emitirInstrucao(1);
	printf("mul\t	$a0, $t1, $a0\n");
	
}

void gerarCodigoRELOP(astNode *an, int *tmp_label)
{
	
	*tmp_label = getLabel(2);
	gerarCodigo(an->astn.filhos[0]);
	emitirInstrucao(0);
	gerarCodigo(an->astn.filhos[1]);
	emitirInstrucao(1);
}


void gerarCodigoOR(astNode *an)
{
	gerarCodigo(an->astn.filhos[0]);
	emitirInstrucao(0);
	gerarCodigo(an->astn.filhos[1]);
	emitirInstrucao(1);
	printf("add\t	$a0, $t1, $a0\n");
}

void gerarCodigoNOT(astNode *an)
{
	int notend, loadum;
	gerarCodigo(an->astn.filhos[0]);
	notend = getLabel(1);
	loadum = getLabel(1);
	printf("beq\t	$a0, $zero, L%d\n", loadum);
	printf("li\t $a0, 0\n");
	printf("j L%d\n", notend);
	printf("L%d:\n", loadum);
	printf("li\t $a0, 1\n");
	printf("L%d:\n", notend);
}

void gerarCodigoBINOP(astNode *an)
{
	gerarCodigo(an->astn.filhos[0]);
	emitirInstrucao(0); //sw\t $a0, 0($sp) e addiu\t $sp, $sp, -4\n
	gerarCodigo(an->astn.filhos[1]);
	emitirInstrucao(1); //lw\t $t1, 4($sp)\n e addiu\t $sp, $sp, 4\n
	
}

void gerarCodigoSTMT(astNode *an)
{
	if(an->astn.n_filhos >= 2) { 
						if(an->astn.filhos[1] != NULL) 
							gerarCodigo(an->astn.filhos[1]);
						gerarCodigo(an->astn.filhos[0]);
				}
				else {gerarCodigo(an->astn.filhos[0]);}
}

void gerarCodigo(astNode *an)
{
    
    int else_label = 0;
    int end_label = 0;
    int start_loop = 0;
    int end_loop = 0;
    int tmp_label = 0;
     
    if(an != NULL) {
    gerarCabecalho(an);
     switch(an->tipoNodo)
     {
		 case Ast:
			switch(an->astn.tokenOpr) {
				case PLUS:
					gerarCodigoBINOP(an);
					printf("add\t $a0, $t1, $a0\n");
				break;
				
				case MINUS:
					gerarCodigoBINOP(an);
					printf("sub\t $a0, $t1, $a0\n");
				break;
				
				case STAR:
					gerarCodigoBINOP(an);
					printf("mul\t $a0, $a0, $t1\n");
				break;
				
				case SLASH: //Divisao
					gerarCodigoBINOP(an);
					printf("div\t $a0, $t1, $a0\n");
				break;
				case UMINUS:
					gerarCodigo(an->astn.filhos[0]);
					printf("sub\t $a0, $zero, $a0\n");
				break;
				
				case AND:
					gerarCodigoAND(an);	
				break;
				
				case OR:
					gerarCodigoOR(an);
				break;
				
				case NOT:
					gerarCodigoNOT(an);
				break;
				
				case IF:
				else_label = getLabel(1);
				end_label = getLabel(1);
				gerarCodigo(an->astn.filhos[0]);
				printf("beq $a0, $zero, L%d\n", else_label);
				gerarCodigo(an->astn.filhos[1]);
				printf("j L%d\n", end_label);
				printf("L%d:\n", else_label);
				if(an->astn.n_filhos > 2)  //Se for um IF-ELSE
				{
					
					gerarCodigo(an->astn.filhos[2]);
					
				}
				printf("L%d:\n", end_label);		
				break;
				
				case WHILE:
					start_loop = getLabel(1);
					end_loop = getLabel(1);
				
					printf("L%d:\n", start_loop);
					gerarCodigo(an->astn.filhos[0]);
					printf("beq $a0, $zero, L%d\n", end_loop);
					gerarCodigo(an->astn.filhos[1]);
					printf("j L%d\n", start_loop);
					printf("L%d:\n", end_loop);	
				break;
				
				case STMT:
					gerarCodigoSTMT(an);
				break;
				
				case EQUAL:
					
			 
             gerarCodigo(an->astn.filhos[1]);
             printf("sw\t $a0, %s\n", an->astn.filhos[0]->ident.valor);
			
            break;
				break;
				case GT:
					gerarCodigoRELOP(an,&tmp_label);
					printf("bgt\t $t1, $a0, L%d\n", tmp_label);
					printf("li $a0, 0\n");
					printf("j L%d\n", tmp_label+1);
					printf("L%d:\n", tmp_label);
					printf("li $a0, 1\n");
					printf("L%d:\n", tmp_label+1);
				break;
				case GE:
					gerarCodigoRELOP(an, &tmp_label);
					printf("bge\t $t1, $a0 L%d\n", tmp_label);
					printf("li $a0, 0\n");
					printf("j L%d\n", tmp_label+1);
					printf("L%d:\n", tmp_label);
					printf("li $a0, 1\n");
					printf("L%d:\n", tmp_label+1);
				break;
				case LE:
					gerarCodigoRELOP(an, &tmp_label);
					printf("ble\t $t1, $a0, L%d\n", tmp_label);
					printf("li $a0, 0\n");
					printf("j L%d\n", tmp_label+1);
					printf("L%d:\n", tmp_label);
					printf("li $a0, 1\n");
					printf("L%d:\n", tmp_label+1);
				break;
				case LT:
					gerarCodigoRELOP(an, &tmp_label);
					printf("blt\t $t1, $a0, L%d\n", tmp_label);
					printf("li $a0, 0\n");
					printf("j L%d\n", tmp_label+1);
					printf("L%d:\n", tmp_label);
					printf("li $a0, 1\n");
					printf("L%d:\n", tmp_label+1);
				break;
				case EQUALEQUAL:
				    gerarCodigoRELOP(an, &tmp_label);
					printf("beq\t $a0, $t1, L%d\n", tmp_label);
					printf("li $a0, 0\n");
					printf("j L%d\n", tmp_label+1);
					printf("L%d:\n", tmp_label);
					printf("li $a0, 1\n");
					printf("L%d:\n", tmp_label+1);
				break;
				
				case NOTEQUAL:
				    gerarCodigoRELOP(an, &tmp_label);
					printf("bne\t $a0, $t1 L%d\n", tmp_label);
					printf("li $a0, 0\n");
					printf("j L%d\n", tmp_label+1);
					printf("L%d:\n", tmp_label);
					printf("li $a0, 1\n");
					printf("L%d:\n", tmp_label+1);
					break;
				case PRINT:
					gerarCodigo(an->astn.filhos[0]);
					emitirInstrucao(2); //li $v0, 1 e syscall
					break;
				case ATTRIB:
				 if (flagVariavel) { //se é a primeira vez que declara uma variavel
						printf("\t.data\n");
						flagVariavel = 0;
            }
			
            printf("%s:\t .word",an->astn.filhos[0]->ident.valor);

            
            if (an->astn.filhos[1]->tipoNodo == Const) {
                printf(" %d\n", an->astn.filhos[1]->constante.valorConst);
            } else {
				printf(" 0\n");
				an->astn.tokenOpr = EQUAL;
				atribuicoes++;
				Atribuicoes[atribuicoes] = an;
			}
				break;	 
				
		   }
		 break;
		 case Identif:
			printf("lw\t $a0, %s\n", an->ident.valor);
		break;
		case Const:
			printf("li\t $a0, %d\n", an->constante.valorConst);	
		break;
			
	}
  }
  
}

void emitirInstrucao(int tipoInstrucao) //essa funcao fica pro final!!
{
	switch(tipoInstrucao)
	{
		case 0: //empilhar acumulador
			printf("sw\t $a0, 0($sp)\n");
			printf("addiu\t $sp, $sp, -4\n");
		break;
			
		case 1:
			printf("lw\t $t1, 4($sp)\n"); //desempilhar e por em $t1
			printf("addiu\t $sp, $sp, 4\n");
		break;
		
		case 2:
			printf("li\t $v0, 1\n");
			printf("syscall\n");

		break;
		case 3:
			 printf(".text\n");
			printf(".globl main\n\n");
			printf("main:\n");
			break;
	}
}

void gerarCabecalho (astNode *an) {
    int i;

	    if (cabecalho == 0 && (an->tipoNodo != Ast || an->astn.tokenOpr != ATTRIB) && an->astn.tokenOpr != STMT) {

       emitirInstrucao(3);

        cabecalho = 1;
        for(i=0; i<=atribuicoes; i++) {
			gerarCodigo(Atribuicoes[i]);
		}
    }
      
}

