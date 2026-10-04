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

void imprimir_nivel(no *raiz, int N)
{
    if (raiz == NULL)
        return;

    no **fila = malloc(sizeof(no *) * N);
    int inicio = 0, fim = 0;

    fila[fim++] = raiz;

    while (inicio < fim)
    {
        int nivel_tamanho = fim - inicio;

        for (int i = 0; i < nivel_tamanho; i++)
        {
            no *atual = fila[inicio++];
            printf("%d ", atual->valor);

            if (atual->esq != NULL)
                fila[fim++] = atual->esq;

            if (atual->dir != NULL)
                fila[fim++] = atual->dir;
        }

        printf("\n");
    }

    free(fila);
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
        imprimir_nivel(raiz, N);
        printf("\n");
    }
    return 0;
}