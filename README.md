# Calculadora de Expressões
Calculadora de expressões matemáticas que converte notação infixa  para pós-fixa usando o algoritmo de Shunting Yard, com suporte a  parênteses e operadores com precedência. Implementado em C puro.

# 🧮 Calculadora de Expressões

Conversor de expressões matemáticas de notação infixa para pós-fixa com avaliador completo. Implementa o algoritmo de Shunting Yard em C puro.

## ✨ Funcionalidades

- ✅ Conversão de expressões **infixa → pós-fixa** (algoritmo Shunting Yard)
- ✅ Suporte completo a **parênteses** com aninhamento
- ✅ **Precedência correta** de operadores (`*`, `/` antes de `+`, `-`)
- ✅ Operadores suportados: `+`, `-`, `*`, `/`
- ✅ **Zero vazamento de memória** (verificado com Valgrind)
- ✅ Implementação educacional e bem comentada

## 🚀 Compilação

```bash
gcc -o calculadora main.c 
```

### 💻 Uso no terminal:
```bash

thermius@arch: ./a.out 

************** CALCULADORA SIMPLES DE EXPRESSAO ESCRITA EM C **************

Informe a expresão (suporta somente numeros de 0 a 9 e 32 caracretes totais para uma expressao): (2+6+5+9+4+9)*9    
resultado: 315
thermius@arch: 
```


### 📚 Conceitos Demonstrados

- Algoritmo Shunting Yard (Dijkstra)
- Pilhas (stacks) para processamento de operadores
- Precedência e associatividade de operadores
- Tokenização de expressões
- Gerenciamento seguro de memória em C


### 🚧 Roadmap

- [ ] Suportar operadores unários
- [ ] Integrar funções matemáticas
- [ ] Variáveis e tabela de símbolos
- [ ] Estruturas de controle (if, for, while)
- [ ] Transformar em interpretador completo

### 🎯 Limitações Atuais

- Máximo 32 caracteres por expressão
- Apenas operadores binários (`+`, `-`, `*`, `/`)
- Sem suporte a operadores unários (negação, etc)
- Sem suporte a funções (sin, cos, sqrt, etc)
- Sem suporte a variáveis
  
### 🧹 Gerenciamento eficiente de memória com Valgrind

```bash

************** CALCULADORA SIMPLES DE EXPRESSAO ESCRITA EM C **************

Informe a expresão (suporta somente numeros de 0 a 9 e 32 caracretes totais para uma expressao): (2+6+5+9+4+9)*9
resultado: 315
==19173== 
==19173== HEAP SUMMARY:
==19173==     in use at exit: 0 bytes in 0 blocks
==19173==   total heap usage: 36 allocs, 36 frees, 2,756 bytes allocated
==19173== 
==19173== All heap blocks were freed -- no leaks are possible
==19173== 
==19173== For lists of detected and suppressed errors, rerun with: -s
==19173== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
thermius@arch: 
```
Resultado: 36 alocações e 36 liberações, sem vazamentos de memória ou erros detectados pelo Valgrind no teste realizado.


### 📚 Referência

**Estruturas de Dados Usando C**
- **Autores**: Aaron M. Tenenbaum, Yedidyah Langsam, Moshe J. Augenstein
- **Formato**: Capa comum
- **Edição**: Português

Este projeto utiliza os conceitos fundamentais de pilhas (stacks) e algoritmos de conversão de expressões apresentados no capítulo 2 desta obra.


### 📄 Licença

© 2026. Todos os direitos reservados.

Este projeto é disponibilizado exclusivamente para fins de portfólio e demonstração técnica. O código-fonte não pode ser copiado, redistribuído, modificado ou utilizado, integral ou parcialmente, sem autorização prévia e explícita do autor.
