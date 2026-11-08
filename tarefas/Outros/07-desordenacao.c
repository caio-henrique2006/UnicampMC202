#include <stdio.h>
#include <stdlib.h>

// Isso n é uma variável global, é uma definição de tipo
typedef struct
{
    char str[101];
    int desordem;
} DNA;

int compara(const void *a, const void *b)
{
    DNA *dna1 = (DNA *)a;
    DNA *dna2 = (DNA *)b;
    if (dna1->desordem < dna2->desordem)
        return -1;
    else if (dna1->desordem > dna2->desordem)
        return 1;
    else
        return 0;
}

int calcula_desordem(char str[], int L)
{
    int desordem = 0;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (str[i] < str[j])
            {
                desordem++;
            }
        }
    }
    return desordem;
}

int main()
{
    int N, L, S;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf(" ");
        scanf("%d %d", &L, &S);
        DNA dnas[S];
        for (int j = 0; j < S; j++)
        {
            scanf("%s", dnas[j].str);
            dnas[j].desordem = calcula_desordem(dnas[j].str, L);
        }
        qsort(dnas, S, sizeof(DNA), compara);

        for (int j = 0; j < S; j++)
        {
            printf("%s\n", dnas[j].str);
        }
        printf("\n");
    }
    return 0;
}