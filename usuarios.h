#ifndef USUARIOS_H
#define USUARIOS_H

#include "itens.h"

typedef struct Inventario {
    Item* item;
    struct Inventario* prox;
} Inventario;

typedef struct Usuario {
    char nome[50];
    char email[50];
    char senha[20];
    Inventario* inventario;
    struct Usuario* prox;
} Usuario;

Usuario* cadastrar_usuario(Usuario* lista, char nome[], char email[], char senha[]);
Usuario* login(Usuario* lista, char email[], char senha[]);
void mostrar_inventario(Usuario* usuario);
void adicionar_item_inventario(Usuario* usuario, Item* item);
void liberar_usuarios(Usuario* lista);

#endif
