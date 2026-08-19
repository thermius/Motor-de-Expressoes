#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "posfixo.h"

int main ()
{
	Pilha *operandos	= NULL;
	char *saida			= NULL; 
	char entrada 		[32 + 1 ];

	printf("\n************** CALCULADORA SIMPLES DE EXPRESSAO ESCRITA EM C **************\n\n");
	printf ("Informe a expresão (suporta somente numeros de 0 a 9 e 32 caracretes totais para uma expressao): ");
	scanf ("%s",&entrada);

	/*Converte para posfixo*/
	saida = ConverterParaPosfixo (entrada);

	/*processa a expressão*/
	int resultado 	= 0;
	int index 		= 0;
	while (saida[index])
	{
		/*se for um digito, subtrai Ox30H e vai direto para a pilha de operandos*/
		if (isdigit (saida[index])) 
		{ 
			int valor = saida[index] - 0x30;
			Empilhar (&operandos, &valor, sizeof (int), 0, EMPILHAR_DADO_APONTADO);
			index++;
			continue;
		}

		/*se operador, retira dois operandos da pilha e processa*/
		else
		{
			/*obtem os valores*/
			int *ptr_valor_1	= (int*) Desempilhar (&operandos);
			int *ptr_valor_2	= (int*) Desempilhar (&operandos);

			/*verifica se null*/
			if (ptr_valor_1 == NULL  || ptr_valor_2 == NULL) break;

			/*faz o calculo*/
			switch (saida[index])
			{
				case '+':
					resultado = *ptr_valor_2 + *ptr_valor_1;
					break;
				case '-':
					resultado = *ptr_valor_2 - *ptr_valor_1;
					break;
				case '*':
					resultado = *ptr_valor_2 * *ptr_valor_1;
					break;
				case '/':
					resultado = *ptr_valor_2 / *ptr_valor_1;
					break;
			}
			Empilhar (&operandos, &resultado, sizeof (int), 0, EMPILHAR_DADO_APONTADO);
			free (ptr_valor_1);
			free (ptr_valor_2);
		}
		index++;
	}

	/*exibe o resultado*/
	printf("resultado: %i\n", resultado);
	free (saida);
	DestruirPilhaTotal (&operandos);
	return 0;
}
