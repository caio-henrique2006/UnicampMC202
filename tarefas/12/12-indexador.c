#include <stdio.h>
#include <string.h>

#include "avl.h"

static int codigo_visibilidade(const char *visibilidade)
{
    if (strcmp(visibilidade, "restrito") == 0)
        return 0;
    if (strcmp(visibilidade, "interno") == 0)
        return 1;
    if (strcmp(visibilidade, "publico") == 0)
        return 2;
    if (strcmp(visibilidade, "bloqueado") == 0)
        return 3;

    return -1;
}

static int codigo_estado(const char *estado)
{
    if (strcmp(estado, "atualizado") == 0)
        return 0;
    if (strcmp(estado, "desatualizado") == 0)
        return 1;
    if (strcmp(estado, "obsoleto") == 0)
        return 2;

    return -1;
}

static const char *nome_visibilidade(int visibilidade)
{
    switch (visibilidade)
    {
    case 0:
        return "restrito";
    case 1:
        return "interno";
    case 2:
        return "publico";
    case 3:
        return "bloqueado";
    default:
        return "desconhecido";
    }
}

static const char *nome_estado(int estado)
{
    switch (estado)
    {
    case 0:
        return "atualizado";
    case 1:
        return "desatualizado";
    case 2:
        return "obsoleto";
    default:
        return "desconhecido";
    }
}

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
            char nome_visibilidade_lido[16];
            char nome_estado_lido[16];
            int visibilidade;
            int estado;

            if (scanf("%ld %15s %15s", &id, nome_visibilidade_lido,
                      nome_estado_lido) != 3)
                return 0;

            visibilidade = codigo_visibilidade(nome_visibilidade_lido);
            estado = codigo_estado(nome_estado_lido);

            if (visibilidade < 0 || estado < 0)
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
                       nome_visibilidade(encontrado->visibilidade),
                       nome_estado(encontrado->estado));
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
