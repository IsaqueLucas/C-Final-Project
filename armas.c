#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "armas.h"

void inserirArmaNaArvore(Arma **raiz, Arma *nova) {
    if (!(*raiz)) {
        *raiz = nova;
        return;
    }
    if (strcmp(nova->nome, (*raiz)->nome) < 0)
        inserirArmaNaArvore(&(*raiz)->esq, nova);
    else
        inserirArmaNaArvore(&(*raiz)->dir, nova);
}

Arma* carregarArmas(const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) return NULL;

    Arma *raiz = NULL;
    while (!feof(fp)) {
        Arma *nova = (Arma *)malloc(sizeof(Arma));
        nova->esq = nova->dir = NULL;
        if (fscanf(fp, "%d;%49[^;];%19[^;];%f\n", &nova->id, nova->nome, nova->raridade, &nova->preco) == 4)
            inserirArmaNaArvore(&raiz, nova);
        else
            free(nova);
    }

    fclose(fp);
    return raiz;
}

void listarArmasPorNome(Arma *raiz) {
    if (raiz) {
        listarArmasPorNome(raiz->esq);
        printf("[%d] %s (%s) - R$%.2f\n", raiz->id, raiz->nome, raiz->raridade, raiz->preco);
        listarArmasPorNome(raiz->dir);
    }
}

int compararRaridade(const void *a, const void *b) {
    Arma *aa = *(Arma **)a;
    Arma *bb = *(Arma **)b;
    return strcmp(aa->raridade, bb->raridade);
}

void coletarArmas(Arma *raiz, Arma **vetor, int *index) {
    if (raiz) {
        coletarArmas(raiz->esq, vetor, index);
        vetor[(*index)++] = raiz;
        coletarArmas(raiz->dir, vetor, index);
    }
}

void listarArmasPorRaridade(Arma *raiz) {
    int total = 0;
    Arma *vetor[100];
    coletarArmas(raiz, vetor, &total);
    qsort(vetor, total, sizeof(Arma *), compararRaridade);
    for (int i = 0; i < total; i++)
        printf("[%d] %s (%s) - R$%.2f\n", vetor[i]->id, vetor[i]->nome, vetor[i]->raridade, vetor[i]->preco);
}

Arma* buscarArmaPorNome(Arma *raiz, const char *nome) {
    if (!raiz) return NULL;
    int cmp = strcmp(nome, raiz->nome);
    if (cmp == 0) return raiz;
    return (cmp < 0) ? buscarArmaPorNome(raiz->esq, nome) : buscarArmaPorNome(raiz->dir, nome);
}

void liberarArvoreArmas(Arma *raiz) {
    if (raiz) {
        liberarArvoreArmas(raiz->esq);
        liberarArvoreArmas(raiz->dir);
        free(raiz);
    }
}
