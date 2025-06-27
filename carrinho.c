#include <stdio.h>
#include <stdlib.h>
#include "carrinho.h"
#include "usuarios.h"

void inicializar_carrinho(FilaCarrinho* carrinho) {
    carrinho->inicio = carrinho->fim = NULL;
}

void adicionar_ao_carrinho(FilaCarrinho* carrinho, Arma* arma) {
    ItemCarrinho* novo = (ItemCarrinho*) malloc(sizeof(ItemCarrinho));
    novo->arma = arma;
    novo->prox = NULL;

    if (carrinho->fim == NULL) {
        carrinho->inicio = carrinho->fim = novo;
    } else {
        carrinho->fim->prox = novo;
        carrinho->fim = novo;
    }

    printf("Arma '%s' adicionada ao carrinho.\n", arma->nome);
}

void mostrar_carrinho(FilaCarrinho carrinho) {
    printf("\n--- Carrinho de Compras ---\n");
    ItemCarrinho* atual = carrinho.inicio;
    if (atual == NULL) {
        printf("Carrinho vazio.\n");
        return;
    }
    while (atual != NULL) {
        printf("-> %s | Preço: R$%.2f\n", atual->arma->nome, atual->arma->preco);
        atual = atual->prox;
    }
}

void finalizar_compra(FilaCarrinho* carrinho, Usuario* usuario) {
    ItemCarrinho* atual = carrinho->inicio;
    float total = 0;

    while (atual != NULL) {
        adicionar_arma_inventario(usuario, atual->arma);
        total += atual->arma->preco;

        ItemCarrinho* temp = atual;
        atual = atual->prox;
        free(temp);
    }

    carrinho->inicio = carrinho->fim = NULL;

    printf("\nCompra finalizada com sucesso! Total: R$%.2f\n", total);
}

void liberar_carrinho(FilaCarrinho* carrinho) {
    ItemCarrinho* atual = carrinho->inicio;
    while (atual != NULL) {
        ItemCarrinho* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    carrinho->inicio = carrinho->fim = NULL;
}
