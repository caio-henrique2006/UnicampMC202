#include <stdio.h>
#include <stdlib.h>
#include "08-operacoes.h"

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
    No *anterior = NULL;

    while (atual != NULL && atual->valor < valor)
    {
        anterior = atual;
        atual = atual->prox;
    }

    // Observa se já existe
    if (atual != NULL && atual->valor == valor)
    {
        return;
    }

    No *novo = malloc(sizeof(No));
    novo->valor = valor;

    novo->prox = atual;
    if (anterior == NULL)
    {
        conjunto->inicio = novo;
    }
    else
    {
        anterior->prox = novo;
    }
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
    printf("C%d = {", id);
    for (No *atual = conjunto->inicio; atual != NULL; atual = atual->prox)
    {
        if (atual != conjunto->inicio)
        {
            printf(", ");
        }
        printf("%d", atual->valor);
    }
    printf("}\n");
}
