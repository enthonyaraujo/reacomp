#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

// Callback para comparar dois inteiros
int compare_int(void *a, void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return x - y;
}

int main() {

    List *list = list_create(sizeof(int), NULL, compare_int);
    int item[5] = {2, 5, 3, 8, 9};

    // Adicionando elementos
    for (int i = 0; i < 5; i++) {
        int *data = malloc(sizeof(int));
        *data = item[i];
        list_add(list, data);
        printf("Valor %d adicionado\n", *data);
        free(data);
    }
   printf("----------------------------------------\n");

    // Verificar se um valor está na lista
    int valor = 4;
    printf("Procurando pelo valor %d...\n", valor);

    if (list_contains(list, &valor)) {
        printf("-> Sucesso: %d encontrado!\n", valor);
    } else {
         printf("-> Falha: %d não encontrado.\n", valor);
    }
    printf("----------------------------------------\n");


    printf("Destruindo a lista e liberando toda a memória restante.\n");
    list_destroy(list);
    list = NULL;

    printf("Programa concluído. Memória limpa com sucesso.\n");

    return 0;
}