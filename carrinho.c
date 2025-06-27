#include <stdio.h>
#include <stdlib.h>
#include "carrinho.h"

void adicionarAoCarrinho(Sessao *sessao, Arma *arma) {
    CarrinhoNode *novo = (CarrinhoNode *)malloc(sizeof(CarrinhoNode));
    novo->arma = arma;
    novo->prox = NULL;

    if (!sessao->carrinhoInicio) {
        sessao->carrinhoInicio = sessao->carrinhoFim = novo;
    } else {
        sessao->carrinhoFim->prox = novo;
        sessao->carrinhoFim = novo;
    }
    printf("Arma adicionada ao carrinho: %s\n", arma->nome);
}

void finalizarCompra(Sessao *sessao) {
    if (!sessao->carrinhoInicio) {
        printf("Carrinho vazio.\n");
        return;
    }

    CarrinhoNode *atual = sessao->carrinhoInicio;
    while (atual) {
        adicionarAoInventario(sessao->usuario, atual->arma);
        printf("Comprada: %s\n", atual->arma->nome);
        CarrinhoNode *remover = atual;
        atual = atual->prox;
        free(remover);
    }

    sessao->carrinhoInicio = sessao->carrinhoFim = NULL;
    printf("Compra finalizada com sucesso!\n");
}

void liberarCarrinho(CarrinhoNode *inicio) {
    while (inicio) {
        CarrinhoNode *temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }
}
