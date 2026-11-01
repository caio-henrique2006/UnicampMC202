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

    if (altura_esq > altura_dir)
        no->altura = altura_esq + 1;
    else
        no->altura = altura_dir + 1;
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

static No *criar_no(long id, char visibilidade[16], char estado[16])
{
    No *no = malloc(sizeof *no);

    if (no == NULL)
        return NULL;

    no->id = id;

    strncpy(no->visibilidade, visibilidade, sizeof(no->visibilidade) - 1);
    no->visibilidade[sizeof(no->visibilidade) - 1] = '\0';

    strncpy(no->estado, estado, sizeof(no->estado) - 1);
    no->estado[sizeof(no->estado) - 1] = '\0';

    no->altura = 1;
    no->esq = NULL;
    no->dir = NULL;

    return no;
}

static No *inserir_no(No *raiz, long id, char visibilidade[16], char estado[16])
{
    // Caminho até a inserção
    if (raiz == NULL)
        return criar_no(id, visibilidade, estado);

    if (id < raiz->id)
        raiz->esq = inserir_no(raiz->esq, id, visibilidade, estado);
    else if (id > raiz->id)
        raiz->dir = inserir_no(raiz->dir, id, visibilidade, estado);
    else
        return raiz;

    // Caminho de volta atualizando a árvore
    atualizar_altura_no(raiz);

    int fb = fator_balanceamento(raiz);

    if (fb > 1 && id < raiz->esq->id)
        return rotacao_direita(raiz);

    if (fb < -1 && id > raiz->dir->id)
        return rotacao_esquerda(raiz);

    if (fb > 1 && id > raiz->esq->id)
    {
        raiz->esq = rotacao_esquerda(raiz->esq);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && id < raiz->dir->id)
    {
        raiz->dir = rotacao_direita(raiz->dir);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

No *inserir(No *raiz, long id, char visibilidade[16], char estado[16])
{
    return inserir_no(raiz, id, visibilidade, estado);
}

No *buscar(No *raiz, long id)
{
    No *atual = raiz;

    while (atual != NULL)
    {
        if (id < atual->id)
            atual = atual->esq;
        else if (id > atual->id)
            atual = atual->dir;
        else
            return atual;
    }

    return NULL;
}

No *atualizar(No *raiz, long id, char visibilidade[16], char estado[16])
{
    No *alvo = buscar(raiz, id);

    if (alvo == NULL)
        return raiz;

    strncpy(alvo->visibilidade, visibilidade, sizeof(alvo->visibilidade) - 1);
    alvo->visibilidade[sizeof(alvo->visibilidade) - 1] = '\0';
    strncpy(alvo->estado, estado, sizeof(alvo->estado) - 1);
    alvo->estado[sizeof(alvo->estado) - 1] = '\0';

    return raiz;
}

static void imprimir_em_ordem(No *no)
{
    if (no == NULL)
        return;

    imprimir_em_ordem(no->esq);
    printf("%ld", no->id);
    printf(" ");
    imprimir_em_ordem(no->dir);
}

No *imprimir_ordem(No *raiz)
{
    if (raiz == NULL)
    {
        printf("indice vazio\n");
        return raiz;
    }

    printf("documentos: ");
    imprimir_em_ordem(raiz);
    printf("\n");

    return raiz;
}

static void contar(No *no, long *atualizado, long *desatualizado, long *obsoleto)
{
    if (no == NULL)
        return;

    contar(no->esq, atualizado, desatualizado, obsoleto);

    if (strcmp(no->estado, "atualizado") == 0)
        (*atualizado)++;
    else if (strcmp(no->estado, "desatualizado") == 0)
        (*desatualizado)++;
    else if (strcmp(no->estado, "obsoleto") == 0)
        (*obsoleto)++;

    contar(no->dir, atualizado, desatualizado, obsoleto);
}

No *imprimir_categorizado(No *raiz)
{
    long atualizado = 0;
    long desatualizado = 0;
    long obsoleto = 0;

    contar(raiz, &atualizado, &desatualizado, &obsoleto);

    printf("atualizado: %ld, desatualizado: %ld, obsoleto: %ld\n",
           atualizado, desatualizado, obsoleto);

    return raiz;
}
