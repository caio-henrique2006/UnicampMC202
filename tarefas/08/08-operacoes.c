#include <stdio.h>
#include <stdlib.h>
#include "08-operacoes.h"

static int comparar_inteiros(const void *a, const void *b)
{
    const int x = *(const int *)a;
    const int y = *(const int *)b;

    if (x < y)
    {
        return -1;
    }
    if (x > y)
    {
        return 1;
    }
    return 0;
}

void liberar_conjunto(Conjunto *conjunto)
{
    No *atual = conjunto->inicio;
    while (atual != NULL)
    {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    conjunto->inicio = NULL;
}

void criar_conjunto(Conjunto *conjunto)
{
    liberar_conjunto(conjunto);
}

void inserir_elemento(Conjunto *conjunto, int valor)
{
    No *atual = conjunto->inicio;
    while (atual != NULL)
    {
        if (atual->valor == valor)
        {
            return;
        }
        atual = atual->prox;
    }

    No *novo = malloc(sizeof(No));

    novo->valor = valor;
    novo->prox = conjunto->inicio;
    conjunto->inicio = novo;
}

void remover_elemento(Conjunto *conjunto, int valor)
{
    No *anterior = NULL;
    No *atual = conjunto->inicio;

    while (atual != NULL)
    {
        if (atual->valor == valor)
        {
            if (anterior == NULL)
            {
                conjunto->inicio = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

void uniao_conjuntos(Conjunto *destino, const Conjunto *origem1, const Conjunto *origem2)
{
    criar_conjunto(destino);

    for (No *atual = origem1->inicio; atual != NULL; atual = atual->prox)
    {
        inserir_elemento(destino, atual->valor);
    }

    for (No *atual = origem2->inicio; atual != NULL; atual = atual->prox)
    {
        inserir_elemento(destino, atual->valor);
    }
}

void intersecao_conjuntos(Conjunto *destino, const Conjunto *origem1, const Conjunto *origem2)
{
    criar_conjunto(destino);

    for (No *atual = origem1->inicio; atual != NULL; atual = atual->prox)
    {
        if (contem_elemento(origem2, atual->valor))
        {
            inserir_elemento(destino, atual->valor);
        }
    }
}

void diferenca_conjuntos(Conjunto *destino, const Conjunto *origem1, const Conjunto *origem2)
{
    criar_conjunto(destino);

    for (No *atual = origem1->inicio; atual != NULL; atual = atual->prox)
    {
        if (!contem_elemento(origem2, atual->valor))
        {
            inserir_elemento(destino, atual->valor);
        }
    }
}

int contem_elemento(const Conjunto *conjunto, int valor)
{
    for (No *atual = conjunto->inicio; atual != NULL; atual = atual->prox)
    {
        if (atual->valor == valor)
        {
            return 1;
        }
    }

    return 0;
}

void imprimir_conjunto(const Conjunto *conjunto, int id)
{
    int quantidade = 0;
    No *atual = conjunto->inicio;
    while (atual != NULL)
    {
        quantidade++;
        atual = atual->prox;
    }

    if (quantidade == 0)
    {
        printf("C%d = {}\n", id);
        return;
    }

    int *valores = malloc((size_t)quantidade * sizeof(int));

    atual = conjunto->inicio;
    for (int i = 0; i < quantidade; i++)
    {
        valores[i] = atual->valor;
        atual = atual->prox;
    }

    qsort(valores, (size_t)quantidade, sizeof(int), comparar_inteiros);

    printf("C%d = {", id);
    for (int i = 0; i < quantidade; i++)
    {
        if (i > 0)
        {
            printf(", ");
        }
        printf("%d", valores[i]);
    }
    printf("}\n");

    free(valores);
}
