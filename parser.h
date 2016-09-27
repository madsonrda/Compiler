typedef enum { Const, Identif, Ast } tipoNodoE;

typedef struct {
    int valorConst;                
} nodoConstante;


typedef struct {
    char valor[20];                      
} nodoIdentificador;

typedef struct {
	int tokenOpr;
	int n_filhos;                                      
    struct astnode **filhos;	
} nodoAst;

typedef struct astnode {
    union {
        nodoIdentificador ident;
        nodoConstante constante;        
        nodoAst astn;        
    };
    tipoNodoE tipoNodo;
    
} astNode;



