#include <stdio.h>
#include <math.h>

void input_v(int n, int V[])
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &V[i]);
    }
}

void build_r(int r, int n, int V[], int R[])
{
    // printf("Valores: %d %d", r, n);
    printf("Tamanho de R: %f", ceil(n / r));
    for (int i = 0; i < ceil(n / r); i++)
    {
        int soma = 0;
        for (int j = 0; j < r; j++)
        {
            soma += V[(i * r) + j];
        }
        R[i] = soma;
        printf("Somas: %d \n", soma);
    }
}

/*
int operSoma(int V[], int R[], int i, int j)
{
}

int operSubst(int V[], int R[], int i, int x)
{
}
*/

int main()
{
    int n;
    scanf("%d", &n);
    int V[n];
    input_v(n, V);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", V[i]);
    }
    printf("\n");
    int r = ceil(sqrt(n));
    printf("r = %d \n", r);
    int tam_r = ceil(r / n);
    int R[tam_r];
    build_r(r, n, V, R);
    /*
    for (int i = 0; i < r; i++)
    {
        printf("%d \n", R[i]);
    }
    /*
    while (1)
    {
        scanf("%d", &N);
        if (N == 0)
        {
            break;
        }
    }
    */

    return 0;
}