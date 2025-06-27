#ifndef ARMAS_H
#define ARMAS_H

typedef struct Arma {
    int id;
    char nome[50];
    char raridade[20];
    float preco;
    struct Arma *esq, *dir;
} Arma;

Arma* carregarArmas(const char *nomeArquivo);
void inserirArmaNaArvore(Arma **raiz, Arma *nova);
void listarArmasPorNome(Arma *raiz);
void listarArmasPorRaridade(Arma *raiz);
Arma* buscarArmaPorNome(Arma *raiz, const char *nome);
void liberarArvoreArmas(Arma *raiz);

#endif
