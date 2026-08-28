#ifndef PARSING_H	
#define PARSING_H
//#define DEBUG_PARSING
#include "../estrutura_de_dados/arvore/arvore.c"
/*Nodes que o parsing consegue criar. O motor do interpretador avalia o tipo de node para decidi a ação a ser executada*/
enum TipoDeNode {
    NODE_NUMERICO,
    NODE_OPERADOR,
    NODE_FUNCAO,
    NODE_IDENTIFICADOR
};

int 	*TextoParaNumero	(char *, int);
#endif