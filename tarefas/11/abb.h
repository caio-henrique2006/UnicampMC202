#ifndef ABB_H
#define ABB_H

struct no
{
    char palavra[128];
    int frequencia;
    struct no *esq;
    struct no *dir;
};

typedef struct no No;

No *inserir(No *raiz, char *palavra, int frequencia);
No *buscar(No *raiz, char *palavra);
void autocomplete(No *raiz, char *prefixo, int k);
No *remover(No *raiz, char *palavra);
void imprimir(No *raiz);
void liberar(No *raiz);

#endif
