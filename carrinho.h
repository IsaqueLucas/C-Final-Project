#ifndef CARRINHO_H
#define CARRINHO_H

#include "armas.h"

typedef struct ItemCarrinho {
    Arma* arma;
    struct ItemCarrinho* prox;
} ItemCarrinho;

typedef struct {
    ItemCarrinho* inicio;
    ItemCarrinho* fim;
} FilaCarrinho;

// Operações do carrinho
void inicializar_carrinho(FilaCarrinho* carrinho);
void adicionar_ao_carrinho(FilaCarrinho* carrinho, Arma* arma);
void mostrar_carrinho(FilaCarrinho carrinho);
void finalizar_compra(FilaCarrinho* carrinho, Usuario* usuario);
void liberar_carrinho(FilaCarrinho* carrinho);

#endif
