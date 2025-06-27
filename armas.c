#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "armas.h"

NodoArma* inserir_arma(NodoArma* raiz, Arma nova) {
    if (raiz == NULL) {
        NodoArma* novo = (NodoArma*) malloc(sizeof(NodoArma));
        novo->arma = nova;
        novo->esquerda = novo->direita = NULL;
        return novo;
    }
    if (strcmp(nova.nome, raiz->arma.nome) < 0)
        raiz->esquerda = inserir_arma(raiz->esquerda, nova);
    else
        raiz->direita = inserir_arma(raiz->direita, nova);
    return raiz;
}

NodoArma* buscar_arma(NodoArma* raiz, char nome[]) {
    if (raiz == NULL)
        return NULL;
    int cmp = strcmp(nome, raiz->arma.nome);
    if (cmp == 0)
        return raiz;
    else if (cmp < 0)
        return buscar_arma(raiz->esquerda, nome);
    else
        return buscar_arma(raiz->direita, nome);
}

void listar_armas(NodoArma* raiz) {
    if (raiz != NULL) {
        listar_armas(raiz->esquerda);
        printf("ID: %d | Nome: %s | Tipo: %s | Dano: %d | Raridade: %d | Preço: R$%.2f\n",
               raiz->arma.id, raiz->arma.nome, raiz->arma.tipo, raiz->arma.dano, raiz->arma.raridade, raiz->arma.preco);
        listar_armas(raiz->direita);
    }
}

void liberar_arvore(NodoArma* raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);
        liberar_arvore(raiz->direita);
        free(raiz);
    }
}

#include <stdlib.h>

// Estrutura auxiliar
typedef struct {
    Arma* arma;
} ArmaPtr;

int comparar_raridade(const void* a, const void* b) {
    ArmaPtr* ap = (ArmaPtr*) a;
    ArmaPtr* bp = (ArmaPtr*) b;
    return bp->arma->raridade - ap->arma->raridade; // decrescente
}

// Função para contar total de armas
int contar_armas(NodoArma* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contar_armas(raiz->esquerda) + contar_armas(raiz->direita);
}

// Função para preencher vetor
void preencher_vetor_armas(NodoArma* raiz, ArmaPtr* vetor, int* i) {
    if (raiz == NULL) return;
    preencher_vetor_armas(raiz->esquerda, vetor, i);
    vetor[*i].arma = &raiz->arma;
    (*i)++;
    preencher_vetor_armas(raiz->direita, vetor, i);
}

void listar_armas_por_raridade(NodoArma* raiz) {
    int n = contar_armas(raiz);
    if (n == 0) {
        printf("Nenhuma arma cadastrada.\n");
        return;
    }

    ArmaPtr* vetor = (ArmaPtr*) malloc(sizeof(ArmaPtr) * n);
    int i = 0;
    preencher_vetor_armas(raiz, vetor, &i);

    qsort(vetor, n, sizeof(ArmaPtr), comparar_raridade);

    printf("\n--- Armas ordenadas por raridade ---\n");
    for (int j = 0; j < n; j++) {
        Arma* a = vetor[j].arma;
        printf("ID: %d | Nome: %s | Tipo: %s | Dano: %d | Raridade: %d | Preço: R$%.2f\n",
               a->id, a->nome, a->tipo, a->dano, a->raridade, a->preco);
    }

    free(vetor);
}
