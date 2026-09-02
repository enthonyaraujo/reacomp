---
title: "Funções em C"
lang: pt-BR
toc-title: Conteúdo
description: "Protótipos de funções"
author: ["Frederico Gregório Emidio Santos Ferreira", "Guilherme Silva Aguiar"]
date: "2025-11-02"
categories:
  - C
  - funções
---

# Introdução

Na arquitetura da linguagem C, as funções representam os blocos de construção fundamentais para a programação modular e estruturada. Elas encapsulam a lógica, promovem a reutilização e melhoram a legibilidade do código.

As funções em C possuem uma lista de parâmetros e pelo menos um retorno.

```{.c code-line-numbers="false"}
tipo_do_retorno nome_da_funcao(lista_de_parametros){
    // escopo da função
}
```

Dizemos que `tipo_do_retorno nome_da_funcao(lista_de_parametros)` é a assinatura da função.

Exemplo concreto:

```{.c code-line-numbers="false"}
// 'n1' e 'n2' são PARÂMETROS
int somar_inteiros(int n1, int n2){ return n1 + n2; }
```

O código acima indica que a função se chama `somar_inteiros` e que ela recebe como entrada dois argumentos do tipo `int`. A palavra-chave `return` indica o que a função vai devolver. Nesse caso, a função devolve, ou retorna, a soma de inteiros que obviamente é do tipo `int`.

Quando queremos usar uma função, geralmente dizemos que vamos chamá-la:

```{.c code-line-numbers="false"}
int a = 10;
int b = 20;
// 'a' e 'b' são ARGUMENTOS
int soma = somar_inteiros(a, b);
```

A sintaxe é simples. Apenas o nome da função e seus argumentos.


:::{.callout-tip }
Quando declaramos ou definimos uma função, as variáveis de entrada são chamadas de parâmetros. Mas, quando usamos uma função, as variáveis de entrada são chamadas de argumentos.
:::

Observe que a lista de parâmetros pode ser vazia, ou seja, a função não receberá nenhum argumento. Nesse caso, é necessário manter os parênteses.

```{.c code-line-numbers="false"}
void imprimir() {/*...*/}
```

A palavra reservada `void` indica que a função não vai retornar valor algum. Trata-se de uma função sem retorno.


## Classificação


Algumas funções têm comportamentos especiais definidos por como são escritas ou declaradas.


### Funções Recursivas

Uma **função recursiva** é uma função que chama a si mesma, direta ou indiretamente. Elas são essenciais para resolver problemas que podem ser subdivididos em problemas menores e idênticos (como árvores ou o cálculo de fatorial).

Uma função recursiva deve ter um caso para parar a recursão (caso base) e um passo recursivo que se aproxima do caso base.

```c
int fatorial(int n) {
    if (n <= 1) {
        return 1; // Caso base
    else
        return n * fatorial(n - 1); // Passo recursivo
}
```


## Funções Estáticas

São funções declaradas com a palavra-chave `static`. Isso não muda o que a função faz, mas muda sua **visibilidade**. Isso quer dizer que uma função `static` só é visível (só pode ser chamada) de dentro do mesmo arquivo `.c` onde foi definida. Ela é, na prática, uma função "privada" àquele módulo, ajudando a evitar conflitos de nomes em projetos grandes.

```{.c code-line-numbers="false"}
static int funcao_auxiliar(int a, int b) { /* .... */ }
```

## Funções em Linha

Uma função em linha é declarada com a palavra-chave `inline`. Isso serve para que o compilador tente otimizar o código. Em vez de gerar uma chamada de função (que tem um pequeno custo, "overhead"), o compilador pode substituir a chamada pelo próprio corpo da função.

Geralmente são funções muito pequenas e que são chamadas com muita frequência.

```{.c code-line-numbers="false"}
inline int max(int a, int b) { return (a > b) ? a : b; }
```

## Funções de ordem superior e callback

Uma função de ordem superior é uma função que recebe outra função como argumento. Na verdade, ela recebe o endereço da função. Já a função de callback é a função passada como argumento. Isso é realizado usando ponteiros para funções que está fora do escopo deste tópico.


# Protótipos de Função

O compilador C processa os arquivos-fonte de forma sequencial (de cima para baixo). As funções são definidas, geralmente, antes da função `main`. Se nosso arquivo principal possui muitas funções, é preciso passar por todas elas para ver a função principal. Muitas vezes não queremos conhecer o que, ou como, faz cada função. Apenas a assinatura da função é suficiente.

Para que uma função possa ser invocada antes de sua definição completa no código, é necessária uma declaração antecipada: o protótipo de função.

O protótipo é uma **declaração** que resolve isso. É como um "aviso prévio" para o compilador.

> **Analogia:** Pense no protótipo como o **sumário** de um livro. O sumário (no início) informa que o "Capítulo 5: Ponteiros" existe e começa na página 80. Você ainda não leu o capítulo, mas sabe que ele existe e como encontrá-lo.

O protótipo informa ao compilador três coisas essenciais sobre a função (sua "assinatura"):

- O **tipo de retorno** (o que ela devolve, ex.: `int`, `float`, `void` etc).
- O **nome** da função (ex.: `calcular_soma`).
- Os **tipos de parâmetros** que ela espera receber (ex.: `(int, int)`).

Os protótipos servem como um "contrato" ou interface para o compilador. Eles especificam três informações essenciais: o tipo de retorno da função, seu nome e os tipos de seus parâmetros.

Essa declaração antecipada (`int calcular_soma(int a, int b);`, por exemplo) é crucial para a verificação de tipos (_type-checking_). Ela permite que o compilador valide se uma chamada de função está fornecendo o número correto de argumentos e se os tipos desses argumentos são compatíveis com o que a função espera receber, prevenindo erros comuns em tempo de compilação.

## Exemplo 1

Esta é a estrutura de código ideal e mais comum. O protótipo (declaração) vem no topo, permitindo que a função `main` chame a função, cuja lógica (definição) está escrita mais abaixo no arquivo.

```c
#include <stdio.h>

/* 1. Protótipo da Função (Declaração)
 * Informa ao compilador a "assinatura" da função 'soma'.
 */
int soma(int a, int b);

int main() {

    /* 2. Chamada da Função
     * O compilador confia no protótipo e permite esta chamada.
     */
    int resultado = soma(10, 5);
    printf("O resultado da soma é: %d\n", resultado);

    return 0;
}

/*
 * 3. Definição da Função (Implementação)
 * O código real que a função executa.
 */
int soma(int a, int b) {
    return a + b;
}
```

Saída

```{.console code-line-numbers="false"}
$ O resultado da soma é: 15
```

O propósito da linha 6 é dizer ao compilador que existirá uma função chamada `soma` que recebe dois `int` como entrada e retorna um `int` como saída. Após a função `main`, na linha 23, ocorre a implementação da função, o que ela realmente faz. Neste ponto, ela deve obedecer ao contrato da declaração do protótipo, ou seja, receber dois inteiros e retornar um inteiro.


Esta é a boa prática em C por duas razões principais, pois permite que a função `main` (a lógica principal) seja a primeira coisa que o leitor vê no arquivo. Além disso, as funções auxiliares (como `soma`) podem ser definidas abaixo, mantendo o fluxo de leitura lógico. Isso aumenta a legibilidade e organização do código.

No próximo exemplo, vamos mostrar o que acontece se omitirmos o protótipo.

## Exemplo 2

```c
#include <stdio.h>

/* Note a ausência de um protótipo aqui */

int main() {

    /* O compilador chega aqui sem nunca ter ouvido falar da função 'soma'.
     * Isso irá gerar um aviso (warning) ou um erro.
     */
    int resultado = soma(10, 5);

    printf("O resultado é: %d\n", resultado);
    return 0;
}

// A função só é definida aqui, depois de já ter sido usada no 'main'.
int soma(int a, int b) {
    return a + b;
}

```

Mensagem comum:

```{.console code-line-numbers="false"}
warning: implicit declaration of function 'soma' [-Wimplicit-function-declaration]
```

O aviso `implicit declaration of function 'soma'` (declaração implícita da função 'soma') é o ponto central deste exemplo. Esse erro acontece porque o compilador está nos dizendo: "Você me pediu para usar `soma`, mas eu não tinha ideia do que era. Tive que assumir (implicitamente) como ela funcionava". E isso é perigoso, pois o compilador não pode verificar se a chamada está correta (ex.: se `soma` retornasse `float`, o código estaria errado).

Embora a função exista, ela aparece tarde demais no código. O protótipo resolveria a reclamação do compilador ao "avisar" o `main` com antecedência.

Em projetos grandes, esses protótipos são geralmente colocados em arquivos de cabeçalho (`.h`), separando a interface (protótipos) da implementação (definições da função).

---

Neste tutorial, você aprendeu:

✅ a declarar funções antes de usá-las (protótipo).

✅ a definir funções tardiamente (implementação).


---

::: callout-note
## Aviso da Redação
Este artigo foi revisado e editado pela equipe do blog em **03 de novembro de 2025**.
:::