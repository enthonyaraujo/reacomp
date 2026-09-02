---
title: Tipos Estruturados
lang: pt-BR
description: O que são os tipos estruturados struct, union e enum e como são utilizados na programação.
author:
  - Anderson Carlos da Silva Morais
  - Marília Fonsêca Andrade
date: 2025-10-31
categories:
  - struct
  - union
  - enum
  - typedef
---


# Introdução

Tipos estruturados de dados são tipos de dados fora dos tipos habituais, como `int`, `float`, `char` e `bool`. Eles são utilizados para tornar a linguagem mais dinâmica e versátil. Tradicionalmente, são estudados três tipos de dados estruturados: **enumerações (`enums`), registros (`structs`) e uniões (`unions`)**.

# Enum

Um **enum** ou enumeração define um conjunto de valores **inteiros** referenciados por um nome, podendo ser utilizados para melhorar a legibilidade e a compreensão do código.

## Exemplo 1

Uma enumeração é definida usando a palavra reservada `enum` seguida por um nome que a identifica, e por chaves que delimitam os valores nomeados que podem ser referenciados, ressaltando que os valores nomeados são escritos todos em maiúsculo para destacar que são valores imutáveis, por exemplo:

```c
enum dia_da_semana {
    DOMINGO,
    SEGUNDA,
    TERCA,
    QUARTA,
    QUINTA,
    SEXTA,
    SABADO
};
```

Por padrão, o compilador designa 0 ao primeiro nome, 1 ao segundo, e assim sucessivamente. Para exemplificar o uso, utilizaremos um `switch-case`, um local onde enums se destacam ao tornar o código significativamente mais legível do que se fossem usados números.

```{.c}
int main() {
    enum dia_da_semana hoje = QUARTA;

    printf("Valor numerico de hoje (QUARTA): %d\n", hoje);

    switch (hoje) {
        case DOMINGO:
            printf("Hoje e Domingo. Dia de descanso.\n");
            break;
        case SEXTA:
            printf("Hoje e Sexta-feira!:\n");
            break;
        case QUARTA:
            printf("Hoje e Quarta-feira. Metade da semana.\n");
            break;
        default:
            printf("Dia de trabalho/estudo.\n");
            break;
    }

    return 0;
}
```

Saída

```{.console code-line-numbers="false"}
$ Valor numerico de hoje (QUARTA): 3
  Hoje e Quarta-feira. Metade da semana.
```

## Exemplo 2

Nem sempre desejamos que a contagem inicie em 0. Em algumas situações, é necessário que as constantes possuam valores específicos, como códigos de erro ou status de rede.

Este exemplo ilustra como atribuir valores de forma manual. Observe que, ao atribuir um valor, o próximo item (caso não seja atribuído) dará continuidade à contagem a partir desse valor.

```c
#include <stdio.h>

enum status {
    PENDENTE = 1,
    PROCESSANDO,
    CONCLUIDO = 10,
    FALHA = -1
};

void verificarStatus(enum status s) {
    if (s == CONCLUIDO) {
        printf("Status: Operacao concluida com sucesso (Codigo %d).\n", s);
    } else if (s == FALHA) {
        printf("Status: Operacao falhou (Codigo %d).\n", s);
    } else {
        printf("Status: Operacao em andamento (Codigo %d).\n", s);
    }
}

int main() {
    // Imprime os valores para demonstrar a atribuição
    printf("Valores do Enum Status:\n");
    printf("  PENDENTE: %d\n", PENDENTE);
    printf("  PROCESSANDO: %d\n", PROCESSANDO); // Será 2
    printf("  CONCLUIDO: %d\n", CONCLUIDO);
    printf("  FALHA: %d\n", FALHA);

    verificarStatus(CONCLUIDO);
    verificarStatus(PENDENTE);

    return 0;
}
```

Saída

```{.console code-line-numbers="false"}
$ Valores do Enum Status:
    PENDENTE: 1
    PROCESSANDO: 2
    CONCLUIDO: 10
    FALHA: -1
  Status: Operacao concluida com sucesso (Codigo 10).
  Status: Operacao em andamento (Codigo 1).
```
## Boas práticas

Uma das principais armadilhas que os enums ajudam a evitar é a utilização de números mágicos. Um "número mágico" refere-se a um valor numérico, como 0, 1 ou -1, que é utilizado diretamente no código sem uma definição explícita de seu significado. Por exemplo, um código como `if (status == 2)` pode ser considerado ambíguo. Qual é o significado de `2`?

Isso dificulta a leitura e a manutenção do código. Se você precisar alterar o valor que representa `PENDENTE` de `2` para `3`, terá que buscar e substituir todos os `2` no código, o que pode resultar na modificação de um `2` que não está relacionado ao status.

Uma boa prática é reunir essas constantes em um enum com nomes que sejam descritivos. Por padrão, os nomes das constantes em um enum são escritos em letras maiúsculas para sinalizar que se trata de valores imutáveis.


# Struct

Registro ou _struct_ é um tipo de dado que permite armazenar múltiplos valores de tipos diferentes sob um único nome, agrupando informações que estão correlacionadas.

Uma _struct_ é definida usando a palavra reservada `struct` seguida do **nome genérico**; em sequência, o par de chaves define o escopo dos múltiplos valores.

```c
struct nome_generico{
    int valor1;
    char valor2;
    float valor3;
};
```

Por exemplo, vamos criar uma _struct_ que represente uma pessoa. Vamos abstrair que uma pessoa é composta pelos dados de idade, altura, peso e nome.

```c
struct pessoa {
    char nome[100];
    int idade;
    float altura;
    float peso;
};
```


No caso acima, o nome tem no máximo 100 caracteres, a idade em anos é do tipo inteiro, a altura e peso em ponto flutuante. Agora, podemos usar esse novo tipo de dado que criamos.

```{.c code-line-numbers="false"}
struct pessoa p1 = {"Marilia", 23, 1.65, 60.0};
```

Dentro da função `main` é criada uma variável `p1` do tipo `Pessoa` usando a sintaxe `struct Pessoa`, em que são repassados valores para cada campo da struct, respectivamente. Ou seja, usando a sintaxe de chaves `{}`, os valores devem estar na mesma ordem em que os membros foram declarados na _struct_.

Se não quiser inicializar todos os campos, você pode fornecer apenas os valores dos primeiros membros. Os membros restantes serão inicializados com seus valores padrão (`0`, `NULL` etc.).

```{.c code-line-numbers="false"}
struct pessoa p1; = {"Marilia"};
```

Em C99 e versões posteriores, você pode usar designadores para inicializar membros específicos, independentemente da ordem. Isso torna a inicialização mais legível e robusta contra mudanças na ordem dos membros. Por exemplo,

```{.c code-line-numbers="false"}
struct pessoa p1 = {.nome = "Marilia", .altura = 1.65, .idade = 23, .peso = 60.0};
```

Também podemos inicializar os campos individualmente usando o operador ponto.

```{.c code-line-numbers="false"}
struct pessoa p1; = {"Marilia", 23, 1.65, 60.0};

strcpy(p1.nome, "Marilia"); // necessário <string.h>
p1.idade = 23;
p1.altura = 1.65;
p1.peso = 60.0;
```

O operador ponto também é usado para  acessar os valores salvos de uma estrutura.

```c
int main()
{
    struct pessoa p1 = {"Marilia", 23, 1.65, 60.0};

    printf("Nome: %s\n",p1.nome);
    printf("Idade: %d anos\n",p1.idade);
    printf("Altura: %.2f m\n",p1.altura);
    printf("Peso: %.2f kg\n",p1.peso);

    return 0;
}
```

Saída:

```{.console code-line-numbers="false"}
$ Nome: Marilia
  Idade: 23 anos
  Altura: 1.65 m
  Peso: 60.00 kg
```

## Structs aninhadas

Como uma _struct_ é um tipo de dado, é possível que um dos campos seja uma outra _struct_, sendo útil para representar **relações hierárquicas**.

Abaixo temos um exemplo de uso de registros com relação hierárquica, onde todo Herói é uma pessoa, nessa relação a _struct_ `heroi` é composta por:

- **classe**: determina se um herói é Guerreiro, Mago etc;
- **persona**: herda os dados da _struct_ `pessoa`;
- **nível**: nível de experiência ou poder (nunca negativo).

Para acessarmos valores de uma _struct_ que está dentro de outra struct, basta acessar o valor de maneira hierárquica, como exemplificado na impressão de nome e idade do herói:

```{.c code-line-numbers="false"}
protagonista.persona.nome // acessa primeiro persona, e na sequência o nome
protagonista.persona.idade // acessa primeiro persona, e na sequência idade
```

Segue abaixo o código completo que apresenta uma relação hierárquica de _structs_.

```{.c filename=heroi.c}
#include <stdio.h>

enum classe {
    MAGO,
    GUERREIRO,
    ARQUEIRO,
    PALADINO,
    FEITICEIRO,
    BARBARO
};

struct pessoa {
    char nome[100];
    int idade;
    float altura;
    float peso;
};

struct heroi {
    enum classe tipo;
    struct pessoa persona;
    unsigned int nivel;
};

int main()
{
    struct pessoa p1 = {"Marilia", 23, 1.65, 60};

    struct heroi protagonista = {FEITICEIRO, p1, 18};

    printf("Classe: %d  \n",protagonista.tipo);
    printf("Nome do heroi: %s\n", protagonista.persona.nome);
    printf("Idade: %d anos\n", protagonista.persona.idade);
    printf("Nivel: %d\n", protagonista.nivel);

    return 0;
}
```

Saída:

```{.console code-line-numbers="false"}
$ Classe: 4
  Nome do heroi: Marilia
  Idade: 23 anos
  Nivel: 18
```

## Array de structs

Podemos usar um _array_ de registros para armazenar múltiplos registros. Isso é útil ao gerenciar uma coleção de itens do mesmo tipo estruturado, como uma lista de estudantes, um catálogo de produtos ou, no nosso caso, diversas pessoas.

A sintaxe para declarar um array de structs é parecida com a de qualquer outro array:

```{.c code-line-numbers="false"}
struct nome_da_struct nome_do_array[tamanho];
```

A seguir, apresentamos um exemplo que cria um array com 3 pessoas e percorre esse array para exibir as informações de cada uma:

```c
#include <stdio.h>

struct pessoa{
    char nome[100];
    int idade;
    float altura;
    float peso;
};

int main() {
    struct pessoa turma[3] = {
        {"Pedrinho", 50, 1.75, 80.0},
        {"Elizabhet", 35, 1.60, 54.0},
        {"Ana", 25, 1.67, 52.0},
    };

    for (int i = 0; i < 3; i++) {
        printf("Pessoa %d:\n", i + 1);
        printf("Nome: %s\n", turma[i].nome);
        printf("Idade: %d anos\n", turma[i].idade);
        printf("Altura: %.2f m\n", turma[i].altura);
        printf("Peso: %.2f kg\n\n", turma[i].peso);
    }

    return 0;
}
```

Saída

```{.console code-line-numbers="false"}
$ Pessoa 1:
  Nome: Pedrinho
  Idade: 50 anos
  Altura: 1.75 m
  Peso: 80.00 kg

  Pessoa 2:
  Nome: Elizabhet
  Idade: 35 anos
  Altura: 1.60 m
  Peso: 54.00 kg

  Pessoa 3:
  Nome: Ana
  Idade: 25 anos
  Altura: 1.67 m
  Peso: 52.00 kg
```

## Ponteiro para struct

Podemos utilizar ponteiros para registros para manipular dinamicamente informações de um registro. Isso é essencial tanto para a alocação dinâmica de memória quanto para a passagem eficiente de _structs_ grandes para funções (passagem por referência), prevenindo a duplicação de todos os dados.

O exemplo a seguir ilustra como usar um ponteiro para passar uma _struct_ a uma função e modificar seus dados originais.

```c
#include <stdio.h>

struct pessoa {
    char nome[100];
    int idade;
    float altura;
    float peso;
};

void celebrar_aniversario(struct pessoa *p) {
    printf("Celebrando aniversario de %s\n", (*p).nome); //
    (*p).idade = (*p).idade + 1;
    printf("Feliz aniversario! Nova idade: %d anos.\n", (*p).idade);
}

int main() {
    struct pessoa p1 = {"Marilia", 23, 1.65, 60};

    printf("Idade original: %d anos\n", p1.idade);
    celebrar_aniversario(&p1);
    printf("Idade apos a funcao: %d anos\n", p1.idade);

    return 0;
}
```

Saída

```{.console code-line-numbers="false"}
$ Idade original: 23 anos
  Celebrando aniversario de Marilia
  Feliz aniversario! Nova idade: 24 anos.
  Idade apos a funcao: 24 anos
```

A sintaxe para acessar um campo de uma struct por meio de um ponteiro parece bastante carregada. Temos de desreferenciar o ponteiro e depois usar o operador ponto. Para simplificar isso tudo, C permite o acesso com o operador seta. Dessa maneira, o código de `celebrar_aniversario` ficaria assim:

```c
void celebrar_aniversario(struct pessoa *p) {
    printf("Celebrando aniversario de %s\n", p->nome); //
    p->idade = p->idade + 1;
    printf("Feliz aniversario! Nova idade: %d anos.\n", p->idade);
}
```

O uso da seta é mais comum e deixa o código mais legível.


## Boas práticas

Cuidado ao passar _structs_ para funções. Ao passar uma _struct_ para uma função (por exemplo, `void minha_funcao(struct pessoa p)`), o sistema criará uma cópia completa dessa _struct_. Isso é ineficiente e consome memória. Nessas situações, geralmente é mais eficaz passar um ponteiro (`void minha_funcao(struct pessoa *p)`), conforme demonstrado no exemplo anterior.

Além disso, evite nomear os campos com apenas uma letra (como `n`, `i` ou `p`). Em vez disso, utilize nomes descritivos (como `nome`, `idade`, `peso`) que facilitem significativamente a leitura e a manutenção do código.

# Union

Uma União ou _union_ é similar a uma _struct_, inclusive a sintaxe e acesso aos membros. Contudo, seus valores compartilham o mesmo espaço de memória. Ou seja, somente um dos seus valores pode ser armazenado por vez.

```c
#include <stdio.h>

union uniao{
    int valor1;
    float valor2;
    char valor3;
};

int main() {
    printf("%zu Bytes\n", sizeof(union uniao));

    return 0;
}
```

A estrutura _union_ é útil quando temos pouco espaço de armazenamento ou podemos fazer com que várias variáveis compartilhem o mesmo espaço. O espaço compartilhado das variáveis será o tamanho do maior tipo de variável que a união possui.

Considere um sistema que reserve 4 bytes para o tipo `int`, 1 byte para `char` e  4 bytes para `float`. Nossa `union` acima terá tamanho de 4 bytes e esse espaço será compartilhado entre `valor1`, `valor2` e `valor3`.

Se usássemos `struct` em vez de `union`, o tamanho seria 12 bytes. Você poderia pensar que seria 9 bytes (4+4+1), mas devido ao _padding_ são adicionados mais 3 bytes. Não é nosso objetivo tratar isso aqui, apenas deixar claro que cada campo de uma _struct_ tem seu espaço reservado, enquanto com _union_ todos compartilham o mesmo espaço.


## Exemplo 1

Os sensores são dispositivos que possuem pouca ou nenhuma memória disponível para uso, além disso, as leituras requeridas podem ser representadas com valores diferentes. Imagine um sensor que consiga realizar a leitura de valores inteiros, valores aproximados e também capaz de informar se o sensor está funcionando corretamente.

Esse sensor pode ser representado pela `union` abaixo:

```{.c code-line-numbers="false"}
union sensor{
    int dados_inteiros;
    float dados_aproximados;
    char estado_sensor;
};
```

Durante a execução do código abaixo, o `sensor1` irá ter valores de suas variáveis modificados:

```{.c code-line-numbers="false"}
int main()
{
    union sensor sensor1;

    // Armazena um inteiro
    sensor1.dados_inteiros = 100;
    printf("Leitura inteira: %d\n", sensor1.dados_inteiros);

    // Agora armazena um float (sobrescreve o valor anterior)
    sensor1.dados_aproximados = 28.7;
    printf("Leitura decimal: %.2f\n", sensor1.dados_aproximados);

    // Agora armazena um caractere (sobrescreve os anteriores)
    sensor1.estado_sensor = 'L';
    printf("Estado do sensor: %c\n", sensor1.estado_sensor);

    return 0;
}
```

Saída:

```{.console code-line-numbers="false"}
$ Leitura inteira: 100
  Leitura decimal: 28.70
  Estado do sensor: L
```

## Exemplo 2

Este exemplo ilustra o que ocorre ao tentarmos acessar um membro da união que não foi propriamente inicializado (inativo). Observe que o valor de `dados_int` é alterado assim que `dados_aprox` é estabelecido.

```c
int main()
{
    union sensor sensor1;

    sensor1.dados_int = 65;
    printf("Inteiro (ativo): %d\n", sensor1.dados_inteiros);
    printf("Char (inativo): %c\n", sensor1.estado_sensor);

    sensor1.estado_sensor = 'B';
    printf("Char (ativo): %c\n", sensor1.estado_sensor);

    printf("Inteiro (inativo): %d\n", sensor1.dados_inteiros);

    return 0;
}
```

Saída:

```{.console code-line-numbers="false"}
$ Inteiro (ativo): 65
  Char (inativo): A
  Char (ativo): B
  Inteiro (inativo): 66
```

Como o espaço de memória é compartilhado, quando lemos na linha 7 o atributo `estado_sensor` o retorno é `'A'`, pois a letra A tem o valor 65 na tabela ASCII. De modo semelhante, quando mudamos `estado_sensor` para `B`, o inteiro correspondente é 66.

Portanto, ao escrever em um membro (por exemplo, dados_aprox), os dados armazenados em outro membro (por exemplo, dados_inteiros) são corrompidos.

## Boas práticas

Tentar acessar o membro inativo levará a um lixo de memória, que ocorre quando a representação binária de um tipo é interpretada como outro. Uma maneira segura de usar _union_ é rastrear qual membro está ativo no momento. Isso é frequentemente realizado aninhando uma `union` dentro de uma `struct` que possui uma _tag_ (normalmente um `enum`) para indicar o tipo de dado que está em uso.

# Bônus: typedef

Toda vez que precisamos criar uma enumeração, registro ou união precisamos colocar as palavras-chave correspondentes:

```{.c code-line-numbers="false"}
enum dia_da_semana dia = ...;
enum classe tipo = ...;
struct Pessoa p1 = ...;
struct heroi protagonista = ...;
union sensor sensor1 = ...;
```

Nosso código pode ficar mais conciso e legível definindo essas estruturas como um novo tipo.


```{.c code-line-numbers="false"}
typedef enum dia_da_semana Dia;
typedef enum classe Classe;
typedef struct pessoa Pessoa;
typedef struct heroi Heroi;
typedef union sensor Sensor;
```

Desse modo, criamos alias e a sintaxe é modificada para:

```{.c code-line-numbers="false"}
Dia dia = ...;
Classe tipo = ...;
Pessoa p1 = ...;
Heroi protagonista = ...;
Sensor sensor1 = ...;
```

O mais comum é usarmos o `typedef` já na definição da estrutura.

```{.c code-line-numbers="false"}
typedef enum {
    DOMINGO,
    SEGUNDA,
    TERCA,
    QUARTA,
    QUINTA,
    SEXTA,
    SABADO
} Dia;
```

Note que depois de `enum` não há um nome, uma tag. Porém, caso a estrutura seja autorreferenciada, precisamos nomeá-la:

```{.c code-line-numbers="false"}
typedef struct no {
    int chave;
    struct no *proximo;
} No;
```


---

Neste tutorial, você aprendeu:

✅ a definir e usar _enums_

✅ a definir e inicializar _structs_

✅ a acessar os campos de uma _struct_

✅ a usar _structs_ aninhadas, _array_ de _structs_ e ponteiro para _structs_

✅ a definir e usar _unions_

✅ a utilizar `typedef` para criar apelidos ou alias para tipos estruturados


---

::: callout-note
## Aviso da Redação
Este artigo foi revisado e editado pela equipe do blog em **04 de novembro de 2025**.
:::