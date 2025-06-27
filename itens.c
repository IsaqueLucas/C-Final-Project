#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itens.h"

NodoItem* inserir_item(NodoItem* raiz, Item novo) {
    if (raiz == NULL) {
        NodoItem* novoNodo = malloc(sizeof(NodoItem));
        novoNodo->item = novo;
        novoNodo->esq = novoNodo->dir = NULL;
        return novoNodo;
    }
    if (strcmp(novo.nome, raiz->item.nome) < 0)
        raiz->esq = inserir_item(raiz->esq, novo);
    else
        raiz->dir = inserir_item(raiz->dir, novo);
    return raiz;
}

void listar_itens(NodoItem* raiz) {
    if (raiz) {
        listar_itens(raiz->esq);
        printf("-> %s [%s] | Poder: %d | Raridade: %d | R$%.2f\n", raiz->item.nome, raiz->item.tipo, raiz->item.poder, raiz->item.raridade, raiz->item.preco);
        listar_itens(raiz->dir);
    }
}

Item* buscar_item(NodoItem* raiz, char nome[]) {
    if (raiz == NULL) return NULL;
    int cmp = strcmp(nome, raiz->item.nome);
    if (cmp == 0) return &(raiz->item);
    else if (cmp < 0) return buscar_item(raiz->esq, nome);
    else return buscar_item(raiz->dir, nome);
}

void liberar_itens(NodoItem* raiz) {
    if (raiz) {
        liberar_itens(raiz->esq);
        liberar_itens(raiz->dir);
        free(raiz);
    }
}
