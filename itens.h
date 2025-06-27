#ifndef ITENS_H
#define ITENS_H

typedef struct Item {
    int id;
    char nome[50];
    char tipo[30]; // Tipos variados de itens
    int raridade;  // Classificação de 1 a 5
    int poder;
    float preco;
} Item;

typedef struct NodoItem {
    Item item;
    struct NodoItem* esq;
    struct NodoItem* dir;
} NodoItem;

NodoItem* inserir_item(NodoItem* raiz, Item novo);
void listar_itens(NodoItem* raiz);
Item* buscar_item(NodoItem* raiz, char nome[]);
void liberar_itens(NodoItem* raiz);

#endif
