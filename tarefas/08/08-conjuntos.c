#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "08-operacoes.h"

int main()
{
    Conjunto *conjuntos[128] = {NULL};
    char cmd[2];
    while (scanf("%2s", cmd))
    {
        // Cria conjunto
        if (strcmp(cmd, "c") == 0)
        {
            int id;
            scanf("%d", &id);
            if (conjuntos[id] == NULL)
            {
                conjuntos[id] = malloc(sizeof(Conjunto));
            }
            criar_conjunto(conjuntos[id]);
        }
        // Imprime conjunto
        else if (strcmp(cmd, "p") == 0)
        {
            int id;
            scanf("%d", &id);
            imprimir_conjunto(conjuntos[id], id);
        }
        // Adiciona x elementos ao conjunto
        else if (strcmp(cmd, "i") == 0)
        {
            int id, x;
            scanf("%d %d", &id, &x);
            for (int i = 0; i < x; i++)
            {
                int valor;
                scanf("%d", &valor);
                inserir_elemento(conjuntos[id], valor);
            }
        }
        // Remove x elementos do conjunto
        else if (strcmp(cmd, "r") == 0)
        {
            int id, x;
            scanf("%d %d", &id, &x);
            for (int i = 0; i < x; i++)
            {
                int valor;
                scanf("%d", &valor);
                remover_elemento(conjuntos[id], valor);
            }
        }
        // Realiza a união de dois conjuntos
        else if (strcmp(cmd, "u") == 0)
        {
            int destino, origem1, origem2;
            scanf("%d %d %d", &destino, &origem1, &origem2);
            if (conjuntos[destino] == NULL)
            {
                conjuntos[destino] = malloc(sizeof(Conjunto));
            }
            uniao_conjuntos(conjuntos[destino], conjuntos[origem1], conjuntos[origem2]);
        }
        // Realiza a interseção de dois conjuntos
        else if (strcmp(cmd, "n") == 0)
        {
            int destino, origem1, origem2;
            scanf("%d %d %d", &destino, &origem1, &origem2);
            if (conjuntos[destino] == NULL)
            {
                conjuntos[destino] = malloc(sizeof(Conjunto));
            }
            intersecao_conjuntos(conjuntos[destino], conjuntos[origem1], conjuntos[origem2]);
        }
        // Realiza a diferença de dois conjuntos
        else if (strcmp(cmd, "m") == 0)
        {
            int destino, origem1, origem2;
            scanf("%d %d %d", &destino, &origem1, &origem2);
            if (conjuntos[destino] == NULL)
            {
                conjuntos[destino] = malloc(sizeof(Conjunto));
            }
            diferenca_conjuntos(conjuntos[destino], conjuntos[origem1], conjuntos[origem2]);
        }
        // Verifica se um elemento está contido em um conjunto
        else if (strcmp(cmd, "e") == 0)
        {
            int id, valor;
            scanf("%d %d", &id, &valor);
            if (conjuntos[id] != NULL && contem_elemento(conjuntos[id], valor))
            {
                printf("%d esta em C%d\n", valor, id);
            }
            else
            {
                printf("%d nao esta em C%d\n", valor, id);
            }
        }
        // Encerra o programa
        else if (strcmp(cmd, "t") == 0)
        {
            break;
        }
        else
        {
            break;
        }
    }

    return 0;
}