#ifndef AVL_H
#define AVL_H

typedef struct no No;

/*
Visibilidade: restrito (0), interno (1), publico(2) ou bloqueado(3)
Estado: atualizado(0), desatualizado(1) ou obsoleto(2)
*/

struct no
{
    long id;
    int visibilidade;
    int estado;
    int altura;
    No *esq;
    No *dir;
};

No *inserir(No *raiz, long id, int visibilidade, int estado);
No *buscar(No *raiz, long id);
No *atualizar(No *raiz, long id, int visibilidade, int estado);
No *imprimir_ordem(No *raiz);
No *imprimir_categorizado(No *raiz);

#endif
