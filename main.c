#include <stdio.h>
#include <string.h>
#include "armas.h"
#include "usuarios.h"
#include "carrinho.h"

int main() {
    Arma *armas = carregarArmas("armas.txt");
    Usuario *usuarios = carregarUsuarios("usuarios.txt");

    char email[50], nome[50];
    printf("Digite seu e-mail: ");
    scanf(" %49[^\n]", email);
    printf("Digite seu nome: ");
    scanf(" %49[^\n]", nome);

    Sessao sessao;

    sessao.usuario = loginOuCadastro(&usuarios, email, nome);
    sessao.carrinhoInicio = sessao.carrinhoFim = NULL;
    carregarInventario(sessao.usuario);


    int opcao;
    char nomeBusca[50];
    do {
        printf("\n1. Listar armas por nome\n2. Listar por raridade\n3. Buscar arma\n4. Adicionar ao carrinho\n5. Finalizar compra\n6. Ver inventario\n7. Recomendar armas\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: listarArmasPorNome(armas); break;
            case 2: listarArmasPorRaridade(armas); break;
            case 3:
                printf("Digite nome da arma: ");
                scanf(" %49[^\n]", nomeBusca);
                Arma *arma = buscarArmaPorNome(armas, nomeBusca);
                if (arma)
                    printf("Encontrada: %s (%s)\n", arma->nome, arma->raridade);
                else printf("Arma nao encontrada.\n");
                break;
            case 4:
                printf("Digite nome da arma: ");
                scanf(" %49[^\n]", nomeBusca);
                Arma *armaCarrinho = buscarArmaPorNome(armas, nomeBusca);
                if (armaCarrinho)
                    adicionarAoCarrinho(&sessao, armaCarrinho);
                else printf("Arma nao encontrada.\n");
                break;
            case 5:
                finalizarCompra(&sessao);
                salvarInventario(sessao.usuario);
                break;
            case 6:
                exibirInventario(sessao.usuario);
                break;
            case 7:
                recomendarArmas(sessao.usuario);
                break;
        }
    } while (opcao != 0);

    liberarCarrinho(sessao.carrinhoInicio);
    liberarArvoreArmas(armas);
    liberarUsuarios(usuarios);
    return 0;
}
