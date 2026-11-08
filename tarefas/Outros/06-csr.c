#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compara_elementos(const void *a, const void *b)
{
    const int (*elem_a)[3] = a;
    const int (*elem_b)[3] = b;

    if ((*elem_a)[0] > (*elem_b)[0])
        return 1;
    if ((*elem_a)[0] < (*elem_b)[0])
        return -1;
    if ((*elem_a)[1] > (*elem_b)[1])
        return 1;
    if ((*elem_a)[1] < (*elem_b)[1])
        return -1;
    return 0;
}

void imprimir_elementos(int i, int j, int x)
{
    printf("(%d,%d) = %d\n", i, j, x);
}

int main()
{
    int k;
    scanf(" %d", &k);
    // Monta matriz VC:
    int (*matriz_vc)[3] = malloc(k * sizeof(int[3]));
    for (int a = 0; a < k; a++)
    {
        int i, j, x;
        scanf(" %d %d %d", &i, &j, &x);
        matriz_vc[a][0] = i;
        matriz_vc[a][1] = j;
        matriz_vc[a][2] = x;
    }
    // Ordena matriz VC:
    qsort(matriz_vc, k, sizeof(int[3]), compara_elementos);

    // Monta matriz CSR:
    int tam_coluna = 0;
    int tam_linha = 0;
    int R[(matriz_vc[k - 1][0] + 1) + 1];
    memset(R, 0, sizeof R);
    for (int a = 0; a < k; a++)
    {
        // Pega tamanho da maior coluna:
        if (tam_coluna < matriz_vc[a][1])
        {
            tam_coluna = matriz_vc[a][1];
        }
        // Pega tamanho da maior linha:
        if (tam_linha < matriz_vc[a][0])
        {
            tam_linha = matriz_vc[a][0];
        }
        // Monta vetor R:
        if (a == 0)
        {
            R[matriz_vc[a][0]] = 0;
        }
        else if (matriz_vc[a][0] != matriz_vc[a - 1][0])
        {
            for (int b = matriz_vc[a - 1][0]; b < matriz_vc[a][0]; b++)
            {
                R[b + 1] = a;
            }
        }
    }
    // Conserta 0 final de R:
    R[matriz_vc[k - 1][0] + 1] = k;
    // Recupera valores em CSR:
    int i, j;
    while (scanf(" %d %d", &i, &j) == 2)
    {
        if (i == -1 && j == -1)
        {
            break;
        }
        else if (i > tam_linha || j > tam_coluna)
        {
            imprimir_elementos(i, j, 0);
        }
        else if (R[i] == R[i + 1])
        {
            imprimir_elementos(i, j, 0);
        }
        else
        {
            int encontrou_pelomenos_um = 0;
            for (int a = R[i]; a < R[i + 1]; a++)
            {
                if (matriz_vc[a][1] == j)
                {
                    encontrou_pelomenos_um = 1;
                    imprimir_elementos(i, j, matriz_vc[a][2]);
                    break;
                }
            }
            if (!encontrou_pelomenos_um)
            {
                imprimir_elementos(i, j, 0);
            }
        }
    }
    free(matriz_vc);

    return 0;
}