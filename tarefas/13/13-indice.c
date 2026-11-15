#include <stdio.h>
#include "btree.h"

int main(void)
{
    No *root = NULL;
    char command;

    while (scanf(" %c", &command) == 1)
    {
        if (command == 'f')
            break;

        switch (command)
        {
        case 'c':
        {
            int t;
            if (scanf("%d", &t) == 1)
            {
                root = criarArvoreB(t);
            }
            break;
        }
        case 'i':
        {
            int x;
            long ini, fim;
            if (scanf("%d %ld %ld", &x, &ini, &fim) == 3)
            {
                inserir(&root, x, ini, fim);
            }
            break;
        }
        case 'p':
        {
            imprimirPorNiveis(root);
            break;
        }
        case 'b':
        {
            int x;
            long ini, fim;
            if (scanf("%d", &x) == 1)
            {
                if (buscar(root, x, &ini, &fim))
                {
                    printf("%d: %ld %ld\n", x, ini, fim);
                }
                else
                {
                    printf("%d nao esta na arvore\n", x);
                }
            }
            break;
        }
        case 'l':
        {
            listar(root);
            break;
        }
        default:
            break;
        }
    }

    return 0;
}
