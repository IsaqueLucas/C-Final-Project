#ifndef USUARIOS_H
#define USUARIOS_H

#include "armas.h"

typedef struct InventarioNode {
    Arma *arma;
    struct InventarioNode *prox;
} InventarioNode;

typedef struct Usuario {
    char nome[50];
    char email[50];
    InventarioNode *inventario;
    struct Usuario *prox;
} Usuario;

typedef struct CarrinhoNode {
    Arma *arma;
    struct CarrinhoNode *prox;
} CarrinhoNode;

typedef struct Sessao {
    Usuario *usuario;
    CarrinhoNode *carrinhoInicio, *carrinhoFim;
} Sessao;

Usuario* carregarUsuarios(const char *nomeArquivo);
Usuario* loginOuCadastro(Usuario **lista, const char *email, const char *nome);
void adicionarAoInventario(Usuario *usuario, Arma *arma);
void salvarInventario(Usuario *usuario);
void exibirInventario(Usuario *usuario);
void recomendarArmas(Usuario *usuario);
void liberarUsuarios(Usuario *lista);
void carregarInventario(Usuario *usuario);
int checarNoInventario(Usuario *usuario, int idArma);


#endif
