#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "armas.h"
#include "usuarios.h"
#include "carrinho.h"
#include "utils.h"


int main() {


    NodoArma* armas = carregar_armas("armas.txt");
    Usuario* usuarios = carregar_usuarios("usuarios.txt");
    Usuario* logado = NULL;
    FilaCarrinho carrinho;
    inicializar_carrinho(&carrinho);



    int opcao;
    char nome[50], email[50], senha[20], busca[50];



    do {
        printf("\n==== GameArms - E-commerce de Armas ====\n");
        printf("1. Cadastrar usuário\n");
        printf("2. Login\n");
        printf("3. Listar armas\n");
        printf("4. Buscar arma por nome\n");
        printf("5. Adicionar arma ao carrinho\n");
        printf("6. Ver carrinho\n");
        printf("7. Finalizar compra\n");
        printf("8. Ver inventário\n");
        printf("9. Sair\n");
        printf("10. Listar armas (ordem alfabética)\n");
        printf("11. Listar armas por raridade\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer




        switch (opcao) {
            case 1:
                printf("Nome: "); fgets(nome, 50, stdin); nome[strcspn(nome, "\n")] = 0;
                printf("Email: "); fgets(email, 50, stdin); email[strcspn(email, "\n")] = 0;
                printf("Senha: "); fgets(senha, 20, stdin); senha[strcspn(senha, "\n")] = 0;
                usuarios = cadastrar_usuario(usuarios, nome, email, senha);
                break;

            case 2:
                printf("Email: "); fgets(email, 50, stdin); email[strcspn(email, "\n")] = 0;
                printf("Senha: "); fgets(senha, 20, stdin); senha[strcspn(senha, "\n")] = 0;
                logado = buscar_usuario(usuarios, email, senha);
                break;

            case 3:
                listar_armas(armas);
                break;

            case 4:
                printf("Nome da arma: "); fgets(busca, 50, stdin); busca[strcspn(busca, "\n")] = 0;
                NodoArma* resultado = buscar_arma(armas, busca);
                if (resultado)
                    printf("Encontrado: %s | Dano: %d | Preço: R$%.2f\n", resultado->arma.nome, resultado->arma.dano, resultado->arma.preco);
                else
                    printf("Arma não encontrada.\n");
                break;

            case 5:
                if (!logado) {
                    printf("Você precisa estar logado.\n");
                    break;
                }
                printf("Nome da arma: "); fgets(busca, 50, stdin); busca[strcspn(busca, "\n")] = 0;
                NodoArma* arma = buscar_arma(armas, busca);
                if (arma) adicionar_ao_carrinho(&carrinho, &arma->arma);
                else printf("Arma não encontrada.\n");
                break;

            case 6:
                mostrar_carrinho(carrinho);
                break;

            case 7:
                if (!logado) printf("Faça login primeiro.\n");
                else finalizar_compra(&carrinho, logado);
                break;

            case 8:
                if (!logado) printf("Faça login primeiro.\n");
                else mostrar_inventario(logado);
                break;

            case 9:

                printf("Salvando dados...\n");
                {
                    FILE* f = fopen("armas.txt", "w");
                    if (f) {
                        salvar_armas(armas, f);
                        fclose(f);
                    }
                    salvar_usuarios(usuarios, "usuarios.txt");
                }
                liberar_arvore(armas);
                liberar_usuarios(usuarios);
                liberar_carrinho(&carrinho);
                printf("Encerrando programa.\n");
                break;
            case 10:
                listar_armas(armas);
                break;

            case 11:
                listar_armas_por_raridade(armas);
                break;

            default:
                printf("Opção inválida.\n");
        }


    } while (opcao != 9);

    return 0;
}
