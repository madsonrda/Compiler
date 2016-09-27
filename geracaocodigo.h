#define SIZE_TABLE 50

int flagVariavel = 1;
int flagInitProgram = 0;

astNode *Atribuicoes[100];
int atribuicoes = -1;

void emitirInstrucao(int tipoInstrucao);
//int indice = 0;
void gerarCodigo(astNode *an);
void cgenAssignVariable(char *variable, astNode *expression);
void gerarCodigoOR(astNode *an);
void gerarCodigoAND(astNode *an);
void gerarCodigoNOT(astNode *an);
void gerarCodigoRELOP(astNode *an, int *tmp_label);
void gerarCodigoATTRIB(astNode *an);
void gerarCodigoBINOP(astNode *an);
void gerarCodigoSTMT(astNode *an);
void gerarCodigoATTRIB(astNode *an);
void gerarCabecalho (astNode *tree);
void gerarATRB(char *variavel, astNode* an);
