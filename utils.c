#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// ===== Armas =====

NodoArma* carregar_armas(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    NodoArma* raiz = NULL;
    Arma a;
    while (fscanf(f, "%d;%49[^;];%29[^;];%d;%d;%f\n", &a.id, a.nome, a.tipo, &a.dano, &a.raridade, &a.preco) == 6) {
        raiz = inserir_arma(raiz, a);
    }
    fclose(f);
    return raiz;
}

void salvar_armas(NodoArma* raiz, FILE* arquivo) {
    if (raiz == NULL) return;
    salvar_armas(raiz->esquerda, arquivo);
    fprintf(arquivo, "%d;%s;%s;%d;%d;%.2f\n",
            raiz->arma.id, raiz->arma.nome, raiz->arma.tipo,
            raiz->arma.dano, raiz->arma.raridade, raiz->arma.preco);
    salvar_armas(raiz->direita, arquivo);
}

// ===== Usuários =====

Usuario* carregar_usuarios(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    Usuario* lista = NULL;
    char nome[50], email[50], senha[20];
    while (fscanf(f, "%49[^;];%49[^;];%19[^\n]\n", nome, email, senha) == 3) {
        lista = cadastrar_usuario(lista, nome, email, senha);
    }
    fclose(f);
    return lista;
}

void salvar_usuarios(Usuario* lista, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) return;
    while (lista != NULL) {
        fprintf(f, "%s;%s;%s\n", lista->nome, lista->email, lista->senha);
        lista = lista->prox;
    }
    fclose(f);
}
