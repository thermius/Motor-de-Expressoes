#include "lexer.h"

/*Função que inicializa o laxer. Retorna 0 se sucesso e -1 se erro*/
int InicializarLexer (Lexer **lexer, char *ptr_entrada)
{
    /*requer que o laxer seja NULL para inicializar*/
    if ((*lexer) != NULL) return -1;

    /*aloca memoria para o lexer e testa */
    (*lexer) = malloc (sizeof (Lexer));
    if ((*lexer) == NULL)
    {
        #ifdef DEBUG_LAXER
            printf(" [ DEBUG ] - InicializarLexer(): falha na alocação de memória para o lexer\n");
        #endif        
    }

    /*inicaliza os campos*/
    (*lexer)->fila_de_tokens_gerados        = NULL;
    (*lexer)->ptr_entrada                   = ptr_entrada;
    (*lexer)->deslocamento                  = 0;
    return  0;

}

/* Função que identifica o próximo token*/
void Tokenizar(Lexer *lexer)
{
    if (lexer == NULL)
    {
        #ifdef DEBUG_LAXER
            printf("[ DEBUG ] - Tokenizar(): lexer não inicializado\n");
        #endif       
        return;
    }

    /*loop que gera tokens até encontrar o fim da expressoa ou até encontrar um token invalido*/
    while (1)
    {
        /*ignora espaços em branco*/
        while (isspace (lexer->ptr_entrada[lexer->deslocamento])) lexer->deslocamento++;

        /*variaveis utilizadas*/
        char *ptr_inicio    = &lexer->ptr_entrada[lexer->deslocamento];
        int inicio          = lexer->deslocamento;
        FragmentoDeToken    token_formado;

        /*se chegar no fim*/
        if (lexer->ptr_entrada[lexer->deslocamento] == 0)
        {
            /*cria o fragmento de token*/
            token_formado.tam_token     = 0;
            token_formado.ptr_token     = NULL;
            token_formado.tipo_de_token = FIM;
            Enfileirar (&lexer->fila_de_tokens_gerados, (void*) &token_formado, sizeof (FragmentoDeToken), 0, ENFILEIRAR_DADO_APONTADO);
            #ifdef DEBUG_LAXER
                printf("[ DEBUG ] - Tokenizar(): fim da expressão\n");
            #endif 
            return;
        }


        /*se digito*/
        if (isdigit (lexer->ptr_entrada[lexer->deslocamento]))
        {

            /*enquanto for numero, avança a entrada*/
            while (isdigit (lexer->ptr_entrada[lexer->deslocamento]))lexer->deslocamento++;

            /*cria o fragmento de token*/
            token_formado.tam_token     = lexer->deslocamento - inicio;
            token_formado.ptr_token     = ptr_inicio;
            token_formado.tipo_de_token = NUMERICO;
            Enfileirar (&lexer->fila_de_tokens_gerados, (void*) &token_formado, sizeof (FragmentoDeToken), 0, ENFILEIRAR_DADO_APONTADO);

            #ifdef DEBUG_LAXER
                printf("[ DEBUG ] - Tokenizar(): token NUMERICO encontrado: ");
                for (int i = inicio; i < lexer->deslocamento; i++) printf ("%c", lexer->ptr_entrada[i]);
                printf("\n");
            #endif 
        
            continue;

        }

        switch (lexer->ptr_entrada[lexer->deslocamento])
        {
            
            /*se qualquer outro operador aritimetico*/
            case '-':
            case '*':
            case '/':
            case '+':
                lexer->deslocamento++;
                token_formado.tam_token     = lexer->deslocamento - inicio;
                token_formado.ptr_token     = ptr_inicio;
                token_formado.tipo_de_token = OPERADOR;

                Enfileirar (&lexer->fila_de_tokens_gerados, (void*) &token_formado, sizeof (FragmentoDeToken), 0, ENFILEIRAR_DADO_APONTADO);
                #ifdef DEBUG_LAXER
                    printf("[ DEBUG ] - Tokenizar(): token OPERADOR encontrado: %c\n",lexer->ptr_entrada[lexer->deslocamento-1]);
                #endif
                continue;

            case '~':
                lexer->deslocamento++;
                token_formado.tam_token     = lexer->deslocamento - inicio;
                token_formado.ptr_token     = ptr_inicio;
                token_formado.tipo_de_token = UNARIO;

                Enfileirar (&lexer->fila_de_tokens_gerados, (void*) &token_formado, sizeof (FragmentoDeToken), 0, ENFILEIRAR_DADO_APONTADO);
                #ifdef DEBUG_LAXER
                    printf("[ DEBUG ] - Tokenizar(): token UNARIO encontrado: %c\n",lexer->ptr_entrada[lexer->deslocamento-1]);
                #endif
                continue;
                
            /*qualquer outro token é tratado como identificado*/
            default:
                while (isalnum (lexer->ptr_entrada[lexer->deslocamento])) lexer->deslocamento++;
                token_formado.tam_token     = lexer->deslocamento - inicio;
                token_formado.tipo_de_token = IDENTIFICADOR;
                Enfileirar (&lexer->fila_de_tokens_gerados, (void*) &token_formado, sizeof (FragmentoDeToken), 0, ENFILEIRAR_DADO_APONTADO);

                #ifdef DEBUG_LAXER
                    printf("[ DEBUG ] - Tokenizar(): token IDENTIFICADOR encontrado: ");
                    for (int i = inicio; i < lexer->deslocamento; i++) printf ("%c", lexer->ptr_entrada[i]);
                    printf("\n");
                #endif 
                continue;
        }
    } /*fim loop infinito*/
}


/*Função que devolve um token*/
void DevolverToken (Lexer *lexer)
{  

    FragmentoDeToken *fragmento = (FragmentoDeToken*) Desenfileirar (&lexer->fila_de_tokens_gerados);
    if (lexer == NULL || fragmento == NULL) 
    {
        #ifdef DEBUG_LAXER
            printf(" [ DEBUG ] - DevolverToken(): laxer vazio\n");
        #endif     
        return;
    }

    while (fragmento->tam_token > 0) { lexer->deslocamento--; fragmento->tam_token --; }
    free (fragmento);
    #ifdef DEBUG_LAXER
        printf(" [ DEBUG ] - DevolverToken(): token devolvido\n");
    #endif     
}

/*Função que devolve o endereço de memoria do ponteiro para a pilha de tokens. Isso acontece porque a pilha entre o lexer e o parsing é compartilhada (lexer produz, parsing consome)*/
Fila   **ObterFilaDeToken  (Lexer *lexer)
{   
    if (lexer == NULL) return NULL;
    return &lexer->fila_de_tokens_gerados;
}

/*Destroi o laxer e a pilha de tokens*/
void    DestruirLexer       (Lexer **lexer)
{
    if (lexer == NULL || (*lexer) == NULL)  return;
    
    /*destroi a pilha de tokens gerados*/
    DestruirFila (&(*lexer)->fila_de_tokens_gerados);
    /*libera a memoria do lexer e aponta para null*/
    free ((*lexer));
    (*lexer) = NULL;
}