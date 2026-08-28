#include "parsing.h"

/*Cria a arvore de sintaxe abstrata e retorna um ponteiro para a raiz ou NULL*/
No *CriarABS (Fila **fila_de_tokens)
{
    if (fila_de_tokens == NULL || (*fila_de_tokens) == NULL) return NULL;

    Pilha   *pilha_de_nodes = NULL;
    No      *pai_corrente   = NULL;
    No      *no_esquerda    = NULL;
    No      *no_direita     = NULL;
    int     *ptr_numero     = NULL;
    char    caracter;

    /*enquanto não esvaziar a pilha, obtem um fragmento de token e cria o node*/
    while (!VazioFila ((*fila_de_tokens)))
    {
        FragmentoDeToken *fragmento_corrente = (FragmentoDeToken*) Desenfileirar (fila_de_tokens);

        /*Cria o node de acordo com o tipo de token*/
        switch (fragmento_corrente->tipo_de_token)
        {
                case NUMERICO:

                    #ifdef DEBUG_PARSING
                        printf ("[ DEBUG ] - CriarABS(): token  NUMERICO recebido para criação de node: ");
                        for (int i = 0; i < fragmento_corrente->tam_token; i++) printf ("%c",fragmento_corrente->ptr_token[i]);
                        printf ("\n");
                    #endif

                    /*converte a string numerica para binario*/
                    ptr_numero      = TextoParaNumero   (fragmento_corrente->ptr_token, fragmento_corrente->tam_token);

                    /*cria o nome numerico*/
                    pai_corrente    = CriarNode         (ptr_numero, sizeof (int), NODE_NUMERICO, ARMAZENAR_COPIA);

                    /*empilha o node*/
                    Empilhar        (&pilha_de_nodes,    pai_corrente, sizeof(No), 0,  EMPILHAR_PONTEIRO);
                    break;

                case OPERADOR:

                    #ifdef DEBUG_PARSING
                        printf ("[ DEBUG ] - CriarABS(): token  OPERADOR recebido para criação de node: ");
                        printf ("%c",*fragmento_corrente->ptr_token);
                        printf ("\n");
                    #endif
                    
                    /*cria o node dos operandos*/
                    no_direita  = (No*) Desempilhar     (&pilha_de_nodes);
                    no_esquerda = (No*) Desempilhar     (&pilha_de_nodes); 

                    /*cria o node do operador*/
                    caracter        = *fragmento_corrente->ptr_token;
                    pai_corrente    = CriarNode         (&caracter, sizeof (char), NODE_OPERADOR, ARMAZENAR_COPIA);

                    /*vincula operador com operandos*/
                    VincularNode(&pai_corrente, no_esquerda, no_direita);

                    /*empilha o node*/
                    Empilhar        (&pilha_de_nodes,    pai_corrente, sizeof(No), 0,  EMPILHAR_PONTEIRO);
                    break;

                case UNARIO:

                    #ifdef DEBUG_PARSING
                        printf ("[ DEBUG ] - CriarABS(): token  UNARIO recebido para criação de node. Função padrão: LibFuncaoUnario");
                        printf ("%c",*fragmento_corrente->ptr_token);
                        printf ("\n");
                    #endif
                    no_direita      = (No*) Desempilhar (&pilha_de_nodes);
                    pai_corrente    = CriarNode (&LibFuncaoUnario, sizeof (void*), NODE_FUNCAO, ARMAZENAR_PONTEIRO);

                    VincularNode(&pai_corrente, NULL, no_direita);

                    /*empilha o node*/
                    Empilhar (&pilha_de_nodes, pai_corrente, sizeof(No*), 0, EMPILHAR_PONTEIRO);
                break;

        }

        free (fragmento_corrente);
    }
     #ifdef DEBUG_PARSING
        printf ("[ DEBUG ] - CriarABS(): ABS criada\n");
    #endif   
        /*retorna um ponteiro para a raiz*/
        return (No*) Desempilhar (&pilha_de_nodes);
}

/*Conterte o texto para numero binario. Gerado por IA*/
int     *TextoParaNumero (char *inicio_token, int fim)
{
    int numero = 0;
    int *ptr_numero = malloc(sizeof(int));

    if (ptr_numero == NULL)
        return NULL;

    for (int i = 0; i < fim; i++)
        numero = numero * 10 + (inicio_token[i] - '0');

    *ptr_numero = numero;

    return ptr_numero;
}

/*Exibe a arvore recursivamente em ordem (da extrema esquerda até a estrema direita). Gerado por IA*/
void DebugABS (No *no)
{
    if (no == NULL)
        return;

    DebugABS(no->ptr_esquerda);


    if (no->tipo_de_dado == NODE_NUMERICO)
        printf("NUMERICO: %d\n", *(int *)no->ptr_valor);

    else if (no->tipo_de_dado == NODE_OPERADOR)
        printf("OPERADOR: %c\n", *(char *)no->ptr_valor);

    DebugABS(no->ptr_direita);
}