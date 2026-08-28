#ifndef ARVORE_H
#define ARVORE_H
//#define DEBUG_ARVORE_H
#define ARMAZENAR_PONTEIRO 	1
#define ARMAZENAR_COPIA		2
#define	TAM_DESCRICAO		32
typedef struct _Node 
{
	void 		*ptr_valor;
	int 		tamanho_dado;
	int	  		tipo_de_dado;
	int 		tipo_de_armazenamento;
	int 		id;	
	char  		descricao [TAM_DESCRICAO];
	struct		_Node *ptr_direita;
	struct		_Node *ptr_esquerda;
} No;

static 	 int	 				debug_arvore = 0;
No		*CriarNode 				(void*, int, int, int);
No		*VincularNode			(No**,No*, No*);
void 	*ObterValorDoNo			(No *);

#endif

