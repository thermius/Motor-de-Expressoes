#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arvore.h"

/*Cria um node e retorna o ponteiro  para o node  recencriado. O novo node é uma copia dos  bytes apontados por ptr_valor. Retorna NULL se erro*/
No *CriarNode (void *ptr_valor, int tamanho_dado,  int tipo_de_dado, int tipo_de_armazenamento)
{
	if (ptr_valor == NULL)
	{
		#ifdef DEBUG_ARVORE_H
			printf("[ DEBUG ] - CriarNode(): ponteiro para valor nulo recebido. retornando null\n");
		#endif
			return NULL;
	}
	if (tipo_de_armazenamento != ARMAZENAR_PONTEIRO && tipo_de_armazenamento != ARMAZENAR_COPIA)
	{
		#ifdef DEBUG_ARVORE_H
			printf("[ DEBUG ] - CriarNode(): tipo de armazenamento invalido informado\n");
		#endif
		return NULL;
	}	
	if (tipo_de_armazenamento == ARMAZENAR_COPIA && tamanho_dado < 1 ) 		
	{

		#ifdef DEBUG_ARVORE_H
			printf("[ DEBUG ] - CriarNode(): tamanho_dado do dado invalido\n");
		#endif
		return NULL;
	}

	/*ponteiro para a memoria onde será guardado o conteudo a apontado caso o armazenamenot seja ARMAZENAR_COPIA*/
	void *ptr_novo_dado = NULL;

	/*aloca memoria e testa o ponteiro*/
	No *ptr_novo_no	= malloc (sizeof (No));
	if (ptr_novo_no == NULL)
	{
		#ifdef DEBUG_ARVORE_H
			printf("[ DEBUG ] - CriarNode(): falha na alocaçao de memoria para o novo node\n");
		#endif
		return NULL;
	}

	/*aloca memoria para o dado que será guardado na arvore e testa o ponteiro*/
	if (tipo_de_armazenamento == ARMAZENAR_COPIA)
	{
		ptr_novo_dado = malloc (tamanho_dado);
		if (ptr_novo_dado == NULL)
		{
			#ifdef DEBUG_ARVORE_H
				printf("[ DEBUG ] - CriarNode(): falha na alocaçao de memoria para o novo dado\n");
			#endif
			free(ptr_novo_no);
			return NULL;
		}
	}

	/*preenche os elementos do node*/
	ptr_novo_no->tipo_de_dado				= tipo_de_dado;
	ptr_novo_no->tipo_de_armazenamento 		= tipo_de_armazenamento;
	ptr_novo_no->ptr_direita 				= NULL;
	ptr_novo_no->ptr_esquerda				= NULL;
	ptr_novo_no->descricao[0]				= 0;

	/*decide o tipo de armazenamento do node*/
	if (tipo_de_armazenamento == ARMAZENAR_PONTEIRO)
	{
		ptr_novo_no->tamanho_dado				= sizeof (void*);
		ptr_novo_no->ptr_valor 					= ptr_valor;
	}
	else 
	{
		memcpy(ptr_novo_dado, ptr_valor, tamanho_dado);
		ptr_novo_no->tamanho_dado 	= tamanho_dado;
		ptr_novo_no->ptr_valor 		= ptr_novo_dado;
	}

	/*retorna o ponteiro para o node*/
	#ifdef DEBUG_ARVORE_H
		printf("[ DEBUG ] - CriarNode(): node criado com sucesso\n");
	#endif
	return ptr_novo_no;
}

/*Vincula o node filho ao node pai. O no pai dever ser o ponteiro para a esquerda ou direita. Do contrario, o pai será sobreescrito e o ponteiro será perdido. Retorna um ponteiro para o node pai NULL se erro.*/
No *VincularNode (No **pai, No *filho_esquerda,No *filho_direita)
{
	if( pai == NULL  || (*pai) == NULL)
	{
		#ifdef DEBUG_ARVORE_H
			printf("[ DEBUG ] - VincularNode(): ponteiro filho ou pai é nulo\n");
		#endif
		return NULL;
	}

	(*pai)->ptr_esquerda	= filho_esquerda;
	(*pai)->ptr_direita		= filho_direita;
	#ifdef DEBUG_ARVORE_H
		printf("[ DEBUG ] - VincularNode(): vinculo feito \n");
	#endif
	return (*pai);
}

/*Retorna um o ponteiro void para o dado armazenado pelo node ou NULL*/
void *ObterValorDoNo( No *no)
{
	if (no == NULL) return NULL;
	return no->ptr_valor;
}

/*Destroi a arvore de forma interativa. A destruição não usa recursão, mas o custo de retornar a raiz a cada liberação é alto se arvore for grande. Uma pilha também pode usada mais teriamos um cenário em que duas estruturas de dados são usadas para formar uma*/
void DestruirArvore (No **raiz)
{
	if (raiz == NULL || (*raiz) == NULL) return;
	
	No *raiz_corrente 		= (*raiz);
	No *k					= NULL;

	while (1)
	{
			/*se chegar na raiz e não tiver caminhos para esquerda e direta, quebra o loop*/
			if 	(raiz_corrente == (*raiz) && raiz_corrente->ptr_esquerda == NULL && raiz_corrente->ptr_direita == NULL)  break;
			/*mergulha até a estrema esquerda*/
			if 	(raiz_corrente->ptr_esquerda) { k = raiz_corrente; raiz_corrente = raiz_corrente->ptr_esquerda; continue;}
			/*vai pra direta*/
			if 	(raiz_corrente->ptr_direita)  { k = raiz_corrente; raiz_corrente = raiz_corrente->ptr_direita;	continue;}
			/*se chegar aqui, podemos liberar o node pois ele não tem mais caminhos*/
			if 	(raiz_corrente->tipo_de_armazenamento == ARMAZENAR_COPIA) free (raiz_corrente->ptr_valor);
			/*quebra o vinculo com o node anterior*/
			if 	(k->ptr_esquerda == raiz_corrente) 	 k->ptr_esquerda = NULL;
			if 	(k->ptr_direita  == raiz_corrente)	 k->ptr_direita  = NULL;
			/*libera o node*/
			free (raiz_corrente);
			/*volta a raiz*/
			raiz_corrente = (*raiz); 
	}	
			/*destroi a raiz e aponta pra null*/
			if (raiz_corrente->tipo_de_armazenamento == ARMAZENAR_COPIA) free(raiz_corrente->ptr_valor);
			free (raiz_corrente);
			(*raiz) = NULL;
			
			#ifdef DEBUG_ARVORE_H
				printf("[ DEBUG ] - DestruirArvore(): arvore destruida\n");
			#endif
}


/*Função alternativa que destroi a pilha recursivamente. Gerado por IA*/
void DestruirArvoreRecursivamente(No **raiz)
{
    if (raiz == NULL || *raiz == NULL) return;

    DestruirArvoreRecursivamente (&(*raiz)->ptr_esquerda);
    DestruirArvoreRecursivamente (&(*raiz)->ptr_direita);

    if ((*raiz)->tipo_de_armazenamento == ARMAZENAR_COPIA)
        free((*raiz)->ptr_valor);

    free(*raiz);

    *raiz = NULL;
    #ifdef DEBUG_ARVORE_H
		printf("[ DEBUG ] - DestruirArvoreRecursivamente(): arvore destruida\n");
	#endif
}

/*Insere uma descrição opcinoal no node. Ao exibir a arvore, a descrição poderá ajudar a enteder o fluxo de processamento*/
void InformarDescricaoDoNode (No *node, char *descricao)
{

	/*se node nulo ignora*/
	if (node == NULL) 
	{	
		#ifdef DEBUG_ARVORE_H
			printf("[ DEBUG ] - InformarDescricaoDoNode(): node nulo ignorado\n");
		#endif	
		return;
	}

	/*copia a descrição enquanto houver entrada e enquanto houver espaço*/
	int index = 0;
	while (index < TAM_DESCRICAO - 1 && descricao [index])
	{
		node->descricao[index] = descricao[index];
		index++;
	}

	/*finaliza a descrição*/
	node->descricao [index]= descricao[index] = 0;

}


