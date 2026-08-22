# 🧮 Motor de Expressões Matemáticas

Calculadora de expressões matemáticas desenvolvida em **C puro**. Implementa conversão de notação infixa para pós-fixa (algoritmo Shunting Yard) com suporte a números multi-dígitos e funções matemáticas.

## ✨ Funcionalidades

- ✅ Conversão de expressões **infixa → pós-fixa** (algoritmo Shunting Yard)
- ✅ Suporte a **números com múltiplos dígitos**
- ✅ **Funções matemáticas** (sin, cos, sqrt, etc)
- ✅ Suporte completo a **parênteses** com aninhamento
- ✅ **Precedência correta** de operadores (`*`, `/` antes de `+`, `-`)
- ✅ Operadores suportados: `+`, `-`, `*`, `/`
- ✅ **Zero vazamento de memória** (verificado com Valgrind)
- ✅ Implementação educacional e bem comentada

## 🚀 Compilação

```bash
gcc -o motor-expressoes main.c 
```

### 💻 Uso no terminal:

```bash
thermius@arch: ./a.out 
************** CALCULADORA SIMPLES DE EXPRESSAO ESCRITA EM C **************
Informe a expresão (suporta somente numeros de 0 a 9 e 32 caracretes totais para uma expressao): (2+6+5+9+4+9)*9    
resultado: 315
thermius@arch:

```

## 📚 Conceitos Demonstrados

- Algoritmo Shunting Yard (Dijkstra)
- Pilhas (stacks) para processamento de operadores
- Precedência e associatividade de operadores
- Tokenização e parsing de expressões
- Conversão char → número (multi-dígito)
- Avaliação de funções matemáticas
- Gerenciamento seguro de memória em C

## 🚧 Roadmap do Interpretador

Atualmente a ferramenta funciona como uma **calculadora de expressões**. O projeto evoluirá para um **interpretador completo** que utilizará **Árvore de Sintaxe Abstrata (AST)** para processar comandos, similar a linguagens de programação.

**Próximas fases:**
1️⃣ **Chamada a funções da "biblioteca padrão"**
2️⃣ **Controle de fluxo** (if, while, for)
3️⃣ **Variáveis e escopos**

## 🎯 Limitações Atuais

- Máximo 32 caracteres por expressão (expansível)
- Apenas operadores binários (`+`, `-`, `*`, `/`)
- Sem suporte a operadores unários (negação, etc)
- Sem suporte a variáveis
- Sem estruturas de controle

## 🧹 Gerenciamento eficiente de memória com Valgrind

```bash

==19173== HEAP SUMMARY:
==19173== in use at exit: 0 bytes in 0 blocks
==19173== total heap usage: 36 allocs, 36 frees, 2,756 bytes allocated
==19173==
==19173== All heap blocks were freed -- no leaks are possible
==19173==
==19173== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 1)
```

**Resultado:** 36 alocações e 36 liberações, sem vazamentos de memória ou erros detectados pelo Valgrind.


### 📚 Referência
**Estruturas de Dados Usando C**
- **Autores**: Aaron M. Tenenbaum, Yedidyah Langsam, Moshe J. Augenstein
- **Formato**: Capa comum
- **Edição**: Português
Este projeto utiliza os conceitos fundamentais de pilhas (stacks) e algoritmos de conversão de expressões apresentados no capítulo 2 desta obra.


### 📄 Licença
© 2026. Todos os direitos reservados.
Este projeto é disponibilizado exclusivamente para fins de portfólio e demonstração técnica. O código-fonte não pode ser copiado, redistribuído, modificado ou utilizado, integral ou parcialmente, sem autorização prévia e explícita do autor.
