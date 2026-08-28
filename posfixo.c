#include "posfixo.h"
#include <stdio.h>
#include <stdlib.h>
#include "posfixo.h"
#define OPERADOR_ -1
#define NUMERICO_ -2
#define IDENTIFICADOR_ -3

/* Converte a entrada para posfixo e retorna um ponteiro para a nova entrada posfixada ou NULL. Gerado por IA*/
char *ConverterParaPosfixo (char *entrada)
{
    int     index           = 0;
    int     bytes_extra     = 0;
    char    ultimo_token    = 0; 
    int     posicao_saida   = 0;
    Pilha   *operadores     = NULL;

    /* 1. Alocação Segura: aloca o dobro do tamanho da entrada para garantir espaço para os espaços em branco */
    int tam_entrada = strlen(entrada);
    char *saida = malloc (tam_entrada * 2 + 10);
    if (saida == NULL) return NULL;

    /* 2. Processamento dos Tokens */
    while (entrada[index])
    {
        /* Ignora espaços em branco */
        if (entrada[index] == ' ')
        {
            index++;
            continue;
        }

        char token_atual = entrada[index]; 

        /* Trata o menos unário */
        if (token_atual == '-' && (index == 0 || ultimo_token == OPERADOR_ || ultimo_token == '(')) 
        {
            token_atual = '~';
        }

        switch (token_atual)
        {
            case '(': 
                ultimo_token = '('; 
                Empilhar (&operadores, &token_atual, sizeof (char), 0, EMPILHAR_DADO_APONTADO);
                index++; /* Incrementa o índice */
                break;

            case ')':
                ultimo_token = OPERADOR_;
                while (!Vazio (operadores))
                {
                    char *temp = (char*) Desempilhar (&operadores);
                    if (*temp == '(') { free (temp); break; }
                    saida [posicao_saida++] = *temp;
                    saida [posicao_saida++] = ' ';
                    free (temp);
                }
                index++; /* Incrementa o índice */
                break;

            case '~':
            case '-': 
            case '+':
            case '*':
            case '/':
        
                while (!Vazio (operadores))
                {
                    char *topo = Topo (operadores);
                    if (*topo == '(') break;
                    if (AvaliarProcedencia (*topo) > AvaliarProcedencia (token_atual) || 
                       (AvaliarProcedencia (*topo) == AvaliarProcedencia (token_atual) && token_atual != '~')) 
                    {
                        char *ptr_elemento = (char*) Desempilhar (&operadores);
                        saida [posicao_saida++] = *ptr_elemento;
                        saida [posicao_saida++] = ' ';
                        free (ptr_elemento);
                    }
                    else break;
                }
                Empilhar (&operadores, &token_atual, sizeof (char), 0, EMPILHAR_DADO_APONTADO);
                ultimo_token = OPERADOR_;
                index++; 
                break;

            default:
                /* Números */
                if (isdigit (token_atual)) 
                {
                    while (isdigit (entrada[index]))
                    {
                        saida[posicao_saida++] = entrada[index];
                        index++; 
                    }
                    saida[posicao_saida++] = ' ';
                    ultimo_token = NUMERICO_;
                }

                else if (isalpha (token_atual))
                {
                    printf("[ ERROR ] - ConverterParaPosfixo(): sem suporte ao caractere: %c\n", token_atual);
                    return NULL;
                }


                break;
        }
    }

    /* 3. Desempilha os operadores restantes ao final da expressão */
    while (!Vazio (operadores))
    {
        char *ptr_elemento = (char*) Desempilhar (&operadores);
        saida [posicao_saida++] = *ptr_elemento;
        saida [posicao_saida++] = ' ';
        free (ptr_elemento);
    }

    /* Termina a string com NULO */
    saida[posicao_saida] = '\0';

    return saida;
}

/*Retorna um inteiro para informar a procedencia. Quanto maior o inteiro, maior a procedencia*/
int AvaliarProcedencia (char c)
{
	switch (c)
	{

	case '~':
		return 4;

	case '$':
		return 3;

	case '*':
	case '/':
		return 2;

	case '+':
	case '-':
		return 1;

	}
}

