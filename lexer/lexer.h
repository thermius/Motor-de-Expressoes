#ifndef LEXER_H
#define LEXER_H
//#define DEBUG_LAXER 
#include "../estrutura_de_dados/fila/fila.c"

/*Tokens suportados*/
enum Tokens {
    NUMERICO,
    ABERTURA_PARENTESES,
    FECHAMENTO_PARENTESES,
    ABERTURA_COLCHETES,
    FECHAMENTO_COLCHETES,
    OPERADOR,
    IDENTIFICADOR,
    UNARIO,
    FIM
};

/* Fragmento de token gerado que permite ao lexer conhecer o endereço do token na entrada, o tamanho e recuar a posição do lexer em tam, permitindo devolver o token */
typedef struct _FragmentoDeToken
{
    int         tam_token;
    char        *ptr_token;
    enum        Tokens tipo_de_token;
    
} FragmentoDeToken;


/*Estrutura que guarda o estado do lexer*/
typedef struct _Lexer {
    char        *ptr_entrada;
    int         deslocamento;
    Fila       *fila_de_tokens_gerados;
}   Lexer;

/*Funções*/
int     InicializarLexer    (Lexer**, char *);
void    DestruirLexer       (Lexer**);
void    Tokenizar           (Lexer* );
Fila    **ObterFilaDeToken  (Lexer* );
#endif
