## 🧮 Motor de Expressões Matemáticas com AST

Um motor de processamento de expressões matemáticas desenvolvido em C puro, construído para receber expressões em notação infixa, realizar a análise e conversão para notação pós-fixa e então processar a expressão respeitando precedência, associatividade, parênteses e funções matemáticas.

O projeto nasceu a partir da implementação de uma calculadora capaz de interpretar expressões matemáticas, evoluindo para uma estrutura de processamento composta por lexer, estruturas de dados, parsing e biblioteca de funções.

## 🚀 Compilação

```bash
gcc -o motor-expressoes main.c
```

## 🌳 Árvore de Sintaxe Abstrata (AST)

Após o processamento da expressão, o motor constrói uma Árvore de Sintaxe Abstrata (AST) que representa estruturalmente a operação que será executada.

Por exemplo, para a expressão:

(2 + 6) * 9

A AST pode ser representada como:

                    *
                   / \
                  /   \
                 +     9
                / \
               2   6

Quanto mais abaixo na árvore, maior será a procedência.



e não simplesmente como uma sequência de caracteres.

## 🔄 Pipeline de processamento

A arquitetura do motor pode ser resumida como:

                    EXPRESSÃO
                        │
                        ▼
                ┌──────────────┐
                │    LEXER     │
                │ Tokenização  │
                └──────┬───────┘
                       │
                       ▼
                ┌──────────────┐
                │    PARSER    │
                │  Análise da  │
                │   expressão  │
                └──────┬───────┘
                       │
                       ▼
                ┌──────────────┐
                │     AST      │
                │              │
                │      *       │
                │     / \      │
                │    +   9     │
                │   / \        │
                │  2   6       │
                └──────┬───────┘
                       │
                       ▼
                ┌──────────────┐
                │  AVALIADOR   │
                └──────┬───────┘
                       │
                       ▼
                     72

A AST permite separar a estrutura sintática da expressão da etapa responsável pela sua avaliação.

Isso também cria uma base para futuras extensões do projeto, como variáveis, operadores adicionais, chamadas de funções e construção de um interpretador mais completo.


## 💻 Exemplo de uso no Terminal

Para a expressão 5 * 9 + 4 * ( 4 + 6 + 979 + 4 - -4):

```bash
thermius@arch: ./calculadora 
[ ENTRADA ] - main(): Informe a expressão: 5*9+4*(4+6+979+4--4)
[ NOTA ] - main(): saida posfixada: 5 9 * 4 4 6 + 979 + 4 + 4 ~ - * + 
[ NOTA ] - main(): Resultado da expressao: 4033
thermius@arch: 

```
## 🛡️ Tratamento de expressões inválidas

O motor também possui tratamento para expressões sintaticamente inválidas.

A expressão não precisa ser válida para passar pelas etapas iniciais de processamento. O sistema consegue realizar a tokenização e a construção da representação pós-fixa, identificando posteriormente que a expressão não pode ser interpretada corretamente.

Por exemplo, diante de uma entrada propositalmente absurda:

```bash
45465465-**/-/-*-*-*--*/5656
```

o motor produz:
```bash

[ NOTA ] - main(): saida posfixada:
45465465 * * ~ / ~ / ~ * ~ * ~ ~ * * 5656 / -

```
e, ao tentar interpretar a expressão:
```bash

[ ERROR ] - InterpretarInterativamente(): tá de sacanagem
[ NOTA ] - main(): me poupe
```
O ponto importante é que uma entrada inválida não causa uma falha inesperada do programa. O motor consegue percorrer seu pipeline de processamento e rejeitar a expressão durante a interpretação. 

Esse comportamento é particularmente importante em um sistema que recebe expressões diretamente de um usuário: entradas inesperadas devem ser tratadas como dados inválidos, e não como uma condição capaz de derrubar o processo.

Nota: as mensagens bem-humoradas exibidas pelo programa são intencionais e fazem parte da interface de depuração/demonstração do projeto. 😹


## 📚 Referências
Compiladores: Princípios, Técnicas e Ferramentas — Volume 1

AHO, Alfred V.; SETHI, Ravi; ULLMAN, Jeffrey D.
Compiladores: Princípios, Técnicas e Ferramentas. Volume 1. Rio de Janeiro: LTC, 1995.

Obra utilizada como referência para conceitos relacionados à análise léxica, análise sintática, parsing, linguagens formais e representação estrutural de expressões, servindo como base teórica para componentes do motor, incluindo a construção da Árvore de Sintaxe Abstrata (AST).

Estruturas de Dados Usando C

TENENBAUM, Aaron M.; LANGSAM, Yedidyah; AUGENSTEIN, Moshe J.
Estruturas de Dados Usando C. São Paulo: Makron Books, 1995.

Utilizado como referência para a implementação de estruturas de dados em C, incluindo pilhas, filas, árvores, ponteiros e estruturas dinâmicas.

O projeto combina os conceitos dessas duas áreas: processamento de linguagens e estruturas de dados, implementados diretamente em C.



## 🧪 Validação de memória

O projeto também está sendo preparado para validação de gerenciamento de memória utilizando ferramentas como Valgrind.

Os testes de memória ainda estão em andamento e, portanto, não são utilizados neste README como evidência de ausência de vazamentos ou erros de memória.

A intenção é utilizar a ferramenta posteriormente para verificar as rotinas de:

alocação dinâmica;
liberação de estruturas;
manipulação de tokens;
construção e destruição da AST;
estruturas auxiliares utilizadas durante o processamento.

