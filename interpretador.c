#include "interpretador.h"

/*função que avalia a AST interativamente*/
int *InterpretarInterativamente(No *raiz) 
{

    if (raiz == NULL) 
    {
            printf("[ DEBUG ] - InterpretarInterativamente(): raiz vazia. retornado\n");
            return 0;
    }

    Pilha 	*pilha_de_nos		= NULL;       
    Pilha 	*pilha_de_valores	= NULL;   
    No 		*ultimo_no_visitado	= NULL;
    No 		*no_corrente        = raiz;
    while (no_corrente != NULL || !Vazio(pilha_de_nos)) 
    {
        /*mergulha até a estrema esquerda empilhando os nodes vizidado de forma a simular uma recursão*/
        while (no_corrente != NULL) 
        {
            #ifdef DEBUG_INTERPRETADOR
                printf("[ DEBUG ] - InterpretarInterativamente(): Percorrendo a árvore por meio do node corrente\n");
                printf("[ DEBUG ] - InterpretarInterativamente(): conteudo do node atual:\n");
                if      (no_corrente->tipo_de_dado == NODE_NUMERICO) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_NUMERICO: %i\n",*(int*)no_corrente->ptr_valor);
                else if (no_corrente->tipo_de_dado == NODE_OPERADOR) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_OPERADOR: %c\n",*(char*)no_corrente->ptr_valor);
            #endif 
            Empilhar(&pilha_de_nos, no_corrente, sizeof(No*), 0, EMPILHAR_PONTEIRO);
            no_corrente = no_corrente->ptr_esquerda;

            #ifdef DEBUG_INTERPRETADOR
                if (no_corrente == NULL) printf("[ DEBUG ] - InterpretarInterativamente(): extrema esqueda de node corrente alcançada. O loop será quebrado\n");
            #endif 
        }

        #ifdef DEBUG_INTERPRETADOR
            if (no_corrente == NULL) printf("[ DEBUG ] - InterpretarInterativamente(): desempilhando pai pai_anterior ao node corrente\n");
        #endif 

        /*ao chegar aqui, node_corrente é NULL. Retornamos ao pai anterior*/
        No *pai_anterior = (No *) Desempilhar (&pilha_de_nos);

        #ifdef DEBUG_INTERPRETADOR
            printf("[ DEBUG ] - InterpretarInterativamente(): pai_anterior desempilhado:\n");
            printf("[ DEBUG ] - InterpretarInterativamente(): conteúdo de pai_anterior: \n");
            if      (pai_anterior->tipo_de_dado == NODE_NUMERICO) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_NUMERICO: %i\n",*(int*)pai_anterior->ptr_valor);
            else if (pai_anterior->tipo_de_dado == NODE_OPERADOR) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_OPERADOR: %c\n",*(char*)pai_anterior->ptr_valor);
        #endif 

        #ifdef DEBUG_INTERPRETADOR
            int verificacao = 0;
            if (no_corrente == NULL) printf("[ DEBUG ] - InterpretarInterativamente(): verificando se existe caminho a direita de pai_anterior que não foi visitado\n");
        #endif 

        /*se houver caminhos a direita, e ainda não foi visitado empilha novamente o ultimo pai e segue pela direita. Sem ultimo_no_vistado, o alogritmo entraria em loop infinito revisiando a direita para sempre*/
        if (pai_anterior->ptr_direita != NULL && pai_anterior->ptr_direita != ultimo_no_visitado) 
        {

            #ifdef DEBUG_INTERPRETADOR
                verificacao  = 1;
                printf("[ DEBUG ] - InterpretarInterativamente(): caminho a direta do pai anterior não visitado encontrado: \n");
                if (ultimo_no_visitado == NULL )printf("[ DEBUG ] - InterpretarInterativamente(): ultimo_no_visitado: NULL\n");
                else
                    {
                        printf("[ DEBUG ] - InterpretarInterativamente(): conteúdo de ultimo_no_visitado: \n");
                        if      (ultimo_no_visitado->tipo_de_dado == NODE_NUMERICO) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_NUMERICO: %i\n",*(int*)ultimo_no_visitado->ptr_valor);
                        else if (ultimo_no_visitado->tipo_de_dado == NODE_OPERADOR) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_OPERADOR: %c\n",*(char*)ultimo_no_visitado->ptr_valor);
                    }
                #endif
                #ifdef DEBUG_INTERPRETADOR
                    printf("[ DEBUG ] - InterpretarInterativamente(): empilhando pai_anterior antes de prosseguir pela direta\n"); 
                #endif

                Empilhar(&pilha_de_nos, pai_anterior, sizeof(No*), 0, EMPILHAR_PONTEIRO);
                no_corrente = pai_anterior->ptr_direita; 
        }

        /*se o ultimo pai for numerico, empilha*/
        else if (pai_anterior->tipo_de_dado == NODE_NUMERICO) 
        { 

            #ifdef DEBUG_INTERPRETADOR
                printf("[ DEBUG ] - InterpretarInterativamente(): pai_anterior não obteve caminho a direta valido e foi idenficado como NODE_NUMERICO:\n");
                printf("[ DEBUG ] - InterpretarInterativamente(): conteúdo de pai_anterior: \n");
                if      (pai_anterior->tipo_de_dado == NODE_NUMERICO) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_NUMERICO: %i\n",*(int*)pai_anterior->ptr_valor);
            #endif 

            #ifdef DEBUG_INTERPRETADOR
                    printf("[ DEBUG ] - InterpretarInterativamente(): empilhando valor de pai_anterior em pilha_de_valores: %i\n",*(int*)pai_anterior->ptr_valor); 
            #endif
            Empilhar (&pilha_de_valores, pai_anterior->ptr_valor, sizeof(int), 0, EMPILHAR_PONTEIRO); 
        }

        /*se for um operandor, naturamente teremos dois numeros na pilha pra operar*/
        else if (pai_anterior->tipo_de_dado == NODE_OPERADOR) 
        {

            #ifdef DEBUG_INTERPRETADOR
                printf("[ DEBUG ] - InterpretarInterativamente(): pai_anterior NODE_OPERADOR encontrado:\n");
                printf("[ DEBUG ] - InterpretarInterativamente(): conteúdo de pai_anterior: \n");
                if      (pai_anterior->tipo_de_dado == NODE_OPERADOR) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_OPERADOR: %c\n",*(char*)pai_anterior->ptr_valor);
            #endif 

            int *ptr_dir    = (int *) Desempilhar(&pilha_de_valores);
            int *ptr_esq    = (int *) Desempilhar(&pilha_de_valores);
            
            /*ignora expressões invalidas*/
            if (ptr_dir == NULL || ptr_esq == NULL)
            {   
                printf("[ ERROR ] - InterpretarInterativamente(): tá de sacanagem\n");
                return NULL;
            }

            int val_dir     = *ptr_dir; free(ptr_dir);
            int val_esq     = *ptr_esq; free(ptr_esq);
            char op         = *(char *)pai_anterior->ptr_valor;
            int resultado   = 0;

            #ifdef DEBUG_INTERPRETADOR
                printf("[ DEBUG ] - InterpretarInterativamente(): aplicando a seguinte operação: %i %c %i\n",val_esq, op, val_dir);
            #endif 
            switch (op) 
            {
                case '+': resultado = val_esq + val_dir; break;
                case '-': resultado = val_esq - val_dir; break;
                case '*': resultado = val_esq * val_dir; break;
                case '/': resultado = (val_dir != 0) ? (val_esq / val_dir) : 0; break;
            }

            Empilhar(&pilha_de_valores, &resultado, sizeof(int), 0, ARMAZENAR_COPIA);

            #ifdef DEBUG_INTERPRETADOR
                printf("[ DEBUG ] - InterpretarInterativamente(): resultado: %i %c %i = %i\n",val_esq, op, val_dir, resultado);
            #endif 


        }

        /*se for função, chamar o a função que interpreta*/
        else if (pai_anterior->tipo_de_dado == NODE_FUNCAO) 
        {
        
            int resultado = 0;
            int (*PtrFuncao)(int)   = ( int (*)(int) )pai_anterior->ptr_valor; 
            #ifdef DEBUG_INTERPRETADOR
                printf("[ NOTA ] - InterpretarInterativamente(): NODE_FUNCAO idenficado. Será chamado a função LibFuncaoUnario por padrão da função CriarABS");
            #endif
            int *ptr_dir    = (int *) Desempilhar(&pilha_de_valores);
            int val_dir     = *ptr_dir; free(ptr_dir);
            resultado       = PtrFuncao(val_dir);
            Empilhar(&pilha_de_valores, &resultado, sizeof(int), 0, ARMAZENAR_COPIA);

        }

        #ifdef DEBUG_INTERPRETADOR
                printf("[ DEBUG ] - InterpretarInterativamente(): definindo novo pai_anterior\n");
        #endif 
                
        /*altera o ultimo node visiado*/
        ultimo_no_visitado = pai_anterior;

        #ifdef DEBUG_INTERPRETADOR
            printf("[ DEBUG ] - InterpretarInterativamente(): novo pai_anterior definido para: \n");
            if      (ultimo_no_visitado->tipo_de_dado == NODE_NUMERICO) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_NUMERICO: %i\n",*(int*)ultimo_no_visitado->ptr_valor);
            else if (ultimo_no_visitado->tipo_de_dado == NODE_OPERADOR) printf ("[ DEBUG ] - InterpretarInterativamente(): NODE_OPERADOR: %c\n",*(char*)ultimo_no_visitado->ptr_valor);
        #endif 

    }


    int *ptr_resultado  = (int *) Desempilhar(&pilha_de_valores);;
    /*retorna o valor*/
    return ptr_resultado;
}

/*função que avalia a AST recursivamente. Gerado por IA*/
int InterpretarRecursivamente (No *no)
{
    if (no == NULL) return 0;

    // Caso base: se for número, retorna o valor
    if (no->tipo_de_dado == NODE_NUMERICO)
        return *(int *)no->ptr_valor;

    // Passo recursivo: resolve subárvores
    int esq = InterpretarRecursivamente(no->ptr_esquerda);
    int dir = InterpretarRecursivamente(no->ptr_direita);

    // Aplica a operação
    char op = *(char *)no->ptr_valor;
    switch (op) {
        case '+': return esq + dir;
        case '-': return esq - dir;
        case '*': return esq * dir;
        case '/': return dir != 0 ? esq / dir : 0;
        default:  return 0;
    }
}

