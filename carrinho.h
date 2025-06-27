#ifndef CARRINHO_H
#define CARRINHO_H

#include "usuarios.h"

void adicionarAoCarrinho(Sessao *sessao, Arma *arma);
void finalizarCompra(Sessao *sessao);
void liberarCarrinho(CarrinhoNode *inicio);

#endif
