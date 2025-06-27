#ifndef ARMAS_H
#define ARMAS_H

typedef struct Arma {
    int id;
    char nome[50];
    char tipo[30];
    int dano;
    int raridade;
    float preco;
} Arma;

typedef struct NodoArma {
    Arma arma;
    struct NodoArma* esquerda;
    struct NodoArma* direita;
} NodoArma;

// Funções do catálogo
NodoArma* inserir_arma(NodoArma* raiz, Arma nova);
NodoArma* buscar_arma(NodoArma* raiz, char nome[]);
void listar_armas(NodoArma* raiz);
void liberar_arvore(NodoArma* raiz);

void listar_armas_por_raridade(NodoArma* raiz);

#endif
