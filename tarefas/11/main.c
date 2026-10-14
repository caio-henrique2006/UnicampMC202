#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h"

int main(void)
{
    No *raiz = NULL;
    char linha[256];
    char comando[32];
    char palavra[128];
    char prefixo[128];
    int frequencia = 0;
    int k = 0;

    while (fgets(linha, sizeof(linha), stdin) != NULL)
    {
        sscanf(linha, "%31s", comando);

        if (strcmp(comando, "EXIT") == 0)
            break;
        else if (strcmp(comando, "INSERT") == 0)
        {
            if (sscanf(linha, "%*s %127s %d", palavra, &frequencia) == 2)
                raiz = inserir(raiz, palavra, frequencia);
        }
        else if (strcmp(comando, "SEARCH") == 0)
        {
            No *encontrado = NULL;
            if (sscanf(linha, "%*s %127s", palavra) == 1)
                encontrado = buscar(raiz, palavra);
            if (encontrado != NULL)
                printf("%s %d\n", encontrado->palavra, encontrado->frequencia);
            else
                printf("%s not found.\n", palavra);
        }
        else if (strcmp(comando, "AUTOCOMPLETE") == 0)
        {
            if (sscanf(linha, "%*s %127s %d", prefixo, &k) == 2)
                autocomplete(raiz, prefixo, k);
        }

        else if (strcmp(comando, "DELETE") == 0)
        {
            if (sscanf(linha, "%*s %127s", palavra) == 1)
                raiz = remover(raiz, palavra);
        }
        else if (strcmp(comando, "PRINT") == 0)
        {
            if (raiz == NULL)
                printf("the dictionary is empty.");
            else
                imprimir(raiz);
            printf("\n");
        }
    }

    liberar(raiz);
    return 0;
}
