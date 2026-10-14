#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h"

typedef struct
{
    char palavra[100];
    int frequencia;
} Valor;

static int comparar_valores(const void *a, const void *b)
{
    const Valor *ia = (const Valor *)a;
    const Valor *ib = (const Valor *)b;

    if (ia->frequencia != ib->frequencia)
        return ib->frequencia - ia->frequencia;

    return strcmp(ia->palavra, ib->palavra);
}

static void coletar_prefixo(No *raiz, const char *prefixo, Valor *valores, int *n)
{
    if (raiz == NULL)
        return;

    coletar_prefixo(raiz->esq, prefixo, valores, n);

    if (strncmp(raiz->palavra, prefixo, strlen(prefixo)) == 0)
    {
        strcpy(valores[*n].palavra, raiz->palavra);
        valores[*n].frequencia = raiz->frequencia;
        (*n)++;
    }

    coletar_prefixo(raiz->dir, prefixo, valores, n);
}

void imprimir(No *raiz)
{
    // Travessia em ordem
    if (raiz != NULL)
    {
        imprimir(raiz->esq);
        printf("%s ", raiz->palavra);
        imprimir(raiz->dir);
    }
}

No *inserir(No *raiz, char *palavra, int frequencia)
{
    if (raiz == NULL) // Caso a árvore esteja vazia
    {
        raiz = (No *)malloc(sizeof(No));
        strcpy(raiz->palavra, palavra);
        raiz->frequencia = frequencia;
        raiz->esq = NULL;
        raiz->dir = NULL;
    }
    else // Percorrendo e colocando na folha da árvore
    {
        int cmp = strcmp(palavra, raiz->palavra);
        if (cmp < 0)
            raiz->esq = inserir(raiz->esq, palavra, frequencia);
        else if (cmp > 0)
            raiz->dir = inserir(raiz->dir, palavra, frequencia);
        else
            raiz->frequencia = frequencia;
    }
    return raiz;
}

No *buscar(No *raiz, char *palavra)
{
    if (raiz == NULL)
        return NULL;

    int cmp = strcmp(palavra, raiz->palavra);
    if (cmp < 0)
        return buscar(raiz->esq, palavra);
    if (cmp > 0)
        return buscar(raiz->dir, palavra);
    if (cmp == 0)
        return raiz;
    return NULL;
}

void autocomplete(No *raiz, char *prefixo, int k)
{
    if (raiz == NULL)
        return;

    Valor valores[1000];
    int n = 0;

    // Pega as palavras que se encaixam no prefixo e coloca em valores
    coletar_prefixo(raiz, prefixo, valores, &n);

    if (n == 0) // Se não houverem palavras que se encaixam no prefixo
    {
        printf("nothing for %s.\n", prefixo);
        return;
    }

    qsort(valores, n, sizeof(Valor), comparar_valores);

    if (k > n)
        k = n;

    for (int i = 0; i < k; i++)
        printf("(%s,%d) ", valores[i].palavra, valores[i].frequencia);
    printf("\n");
}

No *remover(No *raiz, char *palavra)
{
    No *aux;

    if (raiz == NULL)
        return NULL;

    int cmp = strcmp(palavra, raiz->palavra);
    if (cmp < 0)
        raiz->esq = remover(raiz->esq, palavra);
    else if (cmp > 0)
        raiz->dir = remover(raiz->dir, palavra);
    else // Se encontrou o nó a ser removido
    {
        if (raiz->esq == NULL)
        {
            aux = raiz->dir;
            free(raiz);
            return aux;
        }
        if (raiz->dir == NULL)
        {
            aux = raiz->esq;
            free(raiz);
            return aux;
        }
        aux = raiz->dir;
        while (aux->esq != NULL) // Percorre até o nó mais à esquerda da subárvore direita
            aux = aux->esq;

        strcpy(raiz->palavra, aux->palavra);
        raiz->frequencia = aux->frequencia;
        raiz->dir = remover(raiz->dir, aux->palavra);
    }

    return raiz;
}

void liberar(No *raiz)
{
    if (raiz != NULL)
    {
        liberar(raiz->esq);
        liberar(raiz->dir);
        free(raiz);
    }
}