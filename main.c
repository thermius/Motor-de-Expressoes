#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib_padrao/lib.c"
#include "posfixo.c"
#include "lexer/lexer.c"
#include "parsing/parsing.c"
#include "interpretador.c"
#include "buffer_infinito.c"


int main ()
{
	char 	*entrada				= NULL;
	char 	*saida_posfixada		= NULL;
	int 	*saida 					= NULL;
	Fila 	**fila_de_tokens		= NULL;
	Lexer 	*lexer 					= NULL;
	No 		*raiz_abs				= NULL;
	No		*node_corrente			= NULL;

	/*1. ler a entrada*/
	printf ("[ ENTRADA ] - main(): Informe a expressão: ");
	BufferInfinito buffer;
	IniciarBuffer (&buffer);
	LerEntrada (&buffer);
	entrada = ObterPonteiroDoBuffer (&buffer);

	/*2. Convere a entrada para posfixo e exibe*/
	saida_posfixada = ConverterParaPosfixo(entrada);  if (saida_posfixada == NULL ){ printf ("[ NOTA ] - main(): saida posfixada nula\n"); return 0; }
	printf ("[ NOTA ] - main(): saida posfixada: %s\n",saida_posfixada);


	/*3. Inicializa o lexer*/
	InicializarLexer (&lexer, saida_posfixada);

	/*4. Produz os tokens que serão passados para o parsing. Tokenizar gera tokens que são enfileirados para que o parsing possa construir a arvore corretamente*/
	Tokenizar (lexer);

	/*5. Obtem o ponteiro para a fila de tokens  gerada pelo lexer*/
	fila_de_tokens 	= ObterFilaDeToken (lexer);

	/*6. O parsing cria a ABS a partir da fila de tokens e retorna um ponteiro para a raiz da ABS*/
	raiz_abs		= CriarABS (fila_de_tokens);

	/*7. Interpreta a arvore*/
	saida = InterpretarInterativamente  (raiz_abs);

	/*processa a saida*/
	if (saida == NULL)
	{
		printf ("[ NOTA ] - main(): me poupe\n");
	}
	else printf("[ NOTA ] - main(): Resultado da expressao: %d\n", *saida);


	/*8. Libera as memorias*/
	DestruirLexer (&lexer);
	free (saida_posfixada);
	return 0;

}

