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
            No novo_no;

            if (scanf("%ld %15s %15s", &id, visibilidade, estado) != 3)
                return 0;

            preencher_no(&novo_no, id, visibilidade, estado);

            if (comando == 'i')
                raiz = inserir(raiz, &novo_no);
            else
                raiz = atualizar(raiz, &novo_no);

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
