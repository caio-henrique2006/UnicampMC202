#include <stdio.h>
#include <string.h>

#include "avl.h"

int main(void)
{
    No *raiz = NULL;
    char comando;

    while (scanf(" %c", &comando) == 1)
    {
        if (comando == 'f')
            break;

        switch (comando)
        {
        case 'i':
        case 'a':
        {
            long id;
            char visibilidade[16];
            char estado[16];

            if (scanf("%ld %15s %15s", &id, visibilidade, estado) != 3)
                return 0;

            if (comando == 'i')
                raiz = inserir(raiz, id, visibilidade, estado);
            else
                raiz = atualizar(raiz, id, visibilidade, estado);

            break;
        }

        case 'b':
        {
            long x;
            No *encontrado;

            if (scanf("%ld", &x) != 1)
                return 0;

            encontrado = buscar(raiz, x);

            if (encontrado != NULL)
                printf("%ld, %s, %s\n", encontrado->id,
                       encontrado->visibilidade, encontrado->estado);
            else
                printf("%ld nao existe\n", x);

            break;
        }

        case 'l':
            raiz = imprimir_ordem(raiz);
            break;

        case 't':
            raiz = imprimir_categorizado(raiz);
            break;

        default:
            break;
        }
    }

    return 0;
}
