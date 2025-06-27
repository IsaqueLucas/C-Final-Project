#ifndef UTILS_H
#define UTILS_H

#include "usuarios.h"
#include "armas.h"

// Armas
NodoArma* carregar_armas(const char* filename);
void salvar_armas(NodoArma* raiz, FILE* arquivo);

// Usuários
Usuario* carregar_usuarios(const char* filename);
void salvar_usuarios(Usuario* lista, const char* filename);

#endif
