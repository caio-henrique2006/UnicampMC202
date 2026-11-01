#ifndef AVL_H
#define AVL_H

typedef struct no No;

struct no
{
    long id;
    char visibilidade[16];
    char estado[16];
    int altura;
    int FB;
    No *esq;
    No *dir;
};

No *inserir(No *raiz, No *novo);
No *buscar(No *raiz, long id);
No *atualizar(No *raiz, No *atualizado);
No *imprimir_ordem(No *raiz);
No *imprimir_categorizado(No *raiz);

#endif
