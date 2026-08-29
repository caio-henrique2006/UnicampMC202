#include <stdio.h>
#include <math.h>

void input_v(int n, int V[])
{
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &V[i]);
    }
}

void build_r(int tam_r, int r, int n, int V[], int R[])
{
    for (int i = 0; i < tam_r; i++)
    {
        int soma = 0;
        for (int j = i * r; j < ((i + 1) * r); j++)
        {
            if (j < n)
            {
                soma += V[j];
            }
            else
            {
                break;
            }
        }
        R[i] = soma;
    }
}

void operSoma(int V[], int r, int R[], int a, int b)
{
    int i_atual = a;
    int soma = 0;
    while ((i_atual) % r != 0 && i_atual <= b)
    {
        soma += V[i_atual];
        i_atual += 1;
    }
    while (b - (i_atual) >= r)
    {
        soma += R[(i_atual) / r];
        i_atual += r;
    }
    while ((i_atual - 1) != b)
    {
        soma += V[i_atual];
        i_atual += 1;
    }
    printf("%d \n", soma);
}

void operSubst(int V[], int r, int R[], int a, int b)
{
    R[(a / r)] = R[(a / r)] + (b - V[a]);
    V[a] = b;
}

int main()
{
    int n;
    scanf("%d", &n);
    int V[n];
    input_v(n, V);
    int r = ceil(sqrt(n));
    int tam_r = ceil((double)n / r);
    int R[tam_r];
    build_r(tam_r, r, n, V, R);

    char mod;
    int a, b;
    while (scanf(" %c %d %d", &mod, &a, &b))
    {
        if (mod == 's')
        {
            operSoma(V, tam_r, R, a, b);
        }
        if (mod == 'a')
        {
            operSubst(V, tam_r, R, a, b);
        }
    }

    return 0;
}