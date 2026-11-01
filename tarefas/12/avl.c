#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"

static int altura_no(No *no)
{
    return no == NULL ? 0 : no->altura;
}

static int fator_balanceamento(No *no)
{
    if (no == NULL)
        return 0;

    return altura_no(no->esq) - altura_no(no->dir);
}

static void atualizar_altura_no(No *no)
{
    if (no == NULL)
        return;

    int altura_esq = altura_no(no->esq);
    int altura_dir = altura_no(no->dir);

    no->altura = (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

static No *rotacao_direita(No *y)
{
    No *x = y->esq;
    No *subarvore = x->dir;

    x->dir = y;
    y->esq = subarvore;

    atualizar_altura_no(y);
    atualizar_altura_no(x);

    return x;
}

static No *rotacao_esquerda(No *x)
{
    No *y = x->dir;
    No *subarvore = y->esq;

    y->esq = x;
    x->dir = subarvore;

    atualizar_altura_no(x);
    atualizar_altura_no(y);

    return y;
}

static No *criar_no(No *novo)
{
    No *no = malloc(sizeof *no);

    if (no == NULL)
    {
        return NULL;
    }

    no->id = novo->id;

    strncpy(no->visibilidade, novo->visibilidade, sizeof(no->visibilidade) - 1);
    no->visibilidade[sizeof(no->visibilidade) - 1] = '\0';

    strncpy(no->estado, novo->estado, sizeof(no->estado) - 1);
    no->estado[sizeof(no->estado) - 1] = '\0';

    no->altura = 1;
    no->esq = NULL;
    no->dir = NULL;

    return no;
}

static No *inserir_no(No *raiz, No *novo)
{
    if (raiz == NULL)
        return criar_no(novo);

    if (novo->id < raiz->id)
        raiz->esq = inserir_no(raiz->esq, novo);
    else if (novo->id > raiz->id)
        raiz->dir = inserir_no(raiz->dir, novo);
    else
        return raiz;

    atualizar_altura_no(raiz);

    int fb = fator_balanceamento(raiz);

    if (fb > 1 && novo->id < raiz->esq->id)
        return rotacao_direita(raiz);

    if (fb < -1 && novo->id > raiz->dir->id)
        return rotacao_esquerda(raiz);

    if (fb > 1 && novo->id > raiz->esq->id)
    {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && novo->id < raiz->dir->id)
    {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

No *inserir(No *raiz, No *novo)
{
    if (novo == NULL)
        return raiz;

    return inserir_no(raiz, novo);
}

static void imprimir_em_ordem(No *no, int *primeiro)
{
    if (no == NULL)
        return;

    imprimir_em_ordem(no->esq, primeiro);

    if (!*primeiro)
        printf(" ");
    printf("%ld", no->id);
    *primeiro = 0;

    imprimir_em_ordem(no->dir, primeiro);
}

No *imprimir_ordem(No *raiz)
{
    if (raiz == NULL)
    {
        printf("indice vazio\n");
        return raiz;
    }

    int primeiro = 1;

    printf("documentos: ");
    imprimir_em_ordem(raiz, &primeiro);
    printf("\n");

    return raiz;
}
