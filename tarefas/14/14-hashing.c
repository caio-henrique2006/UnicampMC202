#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main(void)
{
    Hash *hash = malloc(sizeof(*hash));
    hash->lista1 = hash->lista2 = NULL;
    char command;

    while (scanf(" %c", &command) == 1)
    {
        if (command == 'f')
        {
            if (hash != NULL)
            {
                free(hash->lista1);
                free(hash->lista2);
                free(hash);
            }
            break;
        }

        switch (command)
        {
        case 'c':
        {
            int tam;
            if (scanf("%d", &tam) == 1)
            {
                *hash = criar(hash, tam);
            }
            break;
        }
        case 'i':
        {
            int chave, valor;
            if (scanf("%d %d", &chave, &valor) == 2)
            {
                inserir(hash, chave, valor);
            }
            break;
        }
        case 'b':
        {
            int chave;
            if (scanf("%d", &chave) == 1)
            {
                buscar(hash, chave);
            }
            break;
        }
        case 'r':
        {
            int chave;
            if (scanf("%d", &chave) == 1)
            {
                remover(hash, chave);
            }
            break;
        }
        default:
            break;
        }
    }

    return 0;
}
