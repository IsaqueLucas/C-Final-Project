#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuarios.h"




Usuario* cadastrar_usuario(Usuario* lista, char nome[], char email[], char senha[]) {
    Usuario* novo = malloc(sizeof(Usuario));
    strcpy(novo->nome, nome);
    strcpy(novo->email, email);
    strcpy(novo->senha, senha);
    novo->inventario = NULL;
    novo->prox = lista;
    return novo;
}

Usuario* login(Usuario* lista, char email[], char senha[]) {
    while (lista) {
        if (strcmp(lista->email, email) == 0 && strcmp(lista->senha, senha) == 0)
            return lista;
        lista = lista->prox;
    }
    return NULL;
}

void adicionar_item_inventario(Usuario* usuario, Item* item) {
    Inventario* novo = malloc(sizeof(Inventario));
    novo->item = item;
    novo->prox = usuario->inventario;
    usuario->inventario = novo;
}

void mostrar_inventario(Usuario* usuario) {
    printf("Inventário de %s:\n", usuario->nome);
    Inventario* inv = usuario->inventario;
    while (inv) {
        printf("-> %s [%s] | Poder %d\n", inv->item->nome, inv->item->tipo, inv->item->poder);
        inv = inv->prox;
    }
}

void liberar_usuarios(Usuario* lista) {
    while (lista) {
        Inventario* inv = lista->inventario;
        while (inv) {
            Inventario* temp = inv;
            inv = inv->prox;
            free(temp);
        }
        Usuario* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}
