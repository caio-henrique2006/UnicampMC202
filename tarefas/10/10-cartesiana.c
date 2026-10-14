#include <stdio.h>
#include <stdlib.h>

// Estrutura de arvore
struct no
{
    int valor;
    struct no *esq;
    struct no *dir;
};
typedef struct no no;

typedef struct fila_no
{
    no *valor;
    struct fila_no *prox;
} fila_no;

typedef struct
{
    fila_no *frente;
    fila_no *tras;
} fila;

no *recur_arvore_cc(int vetor[], int inicio, int fim)
{
    if (inicio > fim)
        return NULL;

    // Encontra o índice do elemento minimo
    int min_i = inicio;
    for (int i = inicio; i <= fim; i++)
    {
        if (vetor[i] < vetor[min_i])
            min_i = i;
    }

    no *novo_no = (no *)malloc(sizeof(no));
    novo_no->valor = min_i;
    novo_no->esq = recur_arvore_cc(vetor, inicio, min_i - 1);
    novo_no->dir = recur_arvore_cc(vetor, min_i + 1, fim);

    return novo_no;
}

void imprimir_nivel(no *raiz)
{
    fila fila_atual = {NULL, NULL};

    fila_no *novo = malloc(sizeof(fila_no));
    novo->valor = raiz;
    novo->prox = NULL;

    fila_atual.frente = novo;
    fila_atual.tras = novo;

    while (fila_atual.frente != NULL)
    {
        int nivel = 0;
        fila_no *aux = fila_atual.frente;

        while (aux != NULL)
        {
            nivel++;
            aux = aux->prox;
        }

        for (int i = 0; i < nivel; i++)
        {
            fila_no *removido = fila_atual.frente;
            no *atual = removido->valor;
            fila_atual.frente = fila_atual.frente->prox;

            if (fila_atual.frente == NULL)
                fila_atual.tras = NULL;

            printf("%d ", atual->valor);

            if (atual->esq != NULL)
            {
                fila_no *novo_esq = malloc(sizeof(fila_no));
                novo_esq->valor = atual->esq;
                novo_esq->prox = NULL;

                if (fila_atual.tras == NULL)
                {
                    fila_atual.frente = novo_esq;
                    fila_atual.tras = novo_esq;
                }
                else
                {
                    fila_atual.tras->prox = novo_esq;
                    fila_atual.tras = novo_esq;
                }
            }

            if (atual->dir != NULL)
            {
                fila_no *novo_dir = malloc(sizeof(fila_no));
                novo_dir->valor = atual->dir;
                novo_dir->prox = NULL;

                if (fila_atual.tras == NULL)
                {
                    fila_atual.frente = novo_dir;
                    fila_atual.tras = novo_dir;
                }
                else
                {
                    fila_atual.tras->prox = novo_dir;
                    fila_atual.tras = novo_dir;
                }
            }

            free(removido);
        }

        printf("\n");
    }
}

int main()
{
    int N;
    while (scanf("%d", &N) == 1)
    {
        if (N == 0)
            break;

        int vetor[N];
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &vetor[i]);
        }

        no *raiz = recur_arvore_cc(vetor, 0, N - 1);
        imprimir_nivel(raiz);
        printf("\n");
    }

    return 0;
}