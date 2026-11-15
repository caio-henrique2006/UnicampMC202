#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

// Wang Hash
int wang_hash(int x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

int posicao1(int chave, int tam)
{
    // Hash 1
    int h = wang_hash(chave);
    return h % tam;
}

int posicao2(int chave, int tam)
{
    // Hash 2
    int h = wang_hash(chave ^ 0x5bd1e995);
    return h % tam;
}

Hash limpa(Hash *hash)
{
    free(hash->lista1);
    free(hash->lista2);

    hash->lista1 = NULL;
    hash->lista2 = NULL;
    hash->tam = 0;
    hash->max = 0;

    return *hash;
}

Hash criar(Hash *hash, int tam)
{
    if (hash != NULL)
    {
        *hash = limpa(hash);
    }

    hash->lista1 = calloc((size_t)tam, sizeof(slot));
    hash->lista2 = calloc((size_t)tam, sizeof(slot));
    hash->tam = tam;
    hash->max = 70; // Porcentagem até redimensionamento

    return *hash;
}

Hash redimensionar(Hash *hash)
{
    slot *old_lista1 = hash->lista1;
    slot *old_lista2 = hash->lista2;
    int old_tam = hash->tam;

    Hash *novo = hash;
    novo->tam = old_tam * 2;
    novo->lista1 = calloc((size_t)novo->tam, sizeof(slot));
    novo->lista2 = calloc((size_t)novo->tam, sizeof(slot));

    for (int i = 0; i < old_tam; i++)
    {
        if (old_lista1[i].occupied)
        {
            int chave = old_lista1[i].key;
            int pos1 = posicao1(chave, novo->tam);
            if (!novo->lista1[pos1].occupied)
            {
                novo->lista1[pos1] = old_lista1[i];
            }
            else
            {
                int pos2 = posicao2(chave, novo->tam);
                if (!novo->lista2[pos2].occupied)
                {
                    novo->lista2[pos2] = old_lista1[i];
                }
            }
        }
    }

    for (int i = 0; i < old_tam; i++)
    {
        if (old_lista2[i].occupied)
        {
            int chave = old_lista2[i].key;
            int pos2 = posicao2(chave, novo->tam);
            if (!novo->lista2[pos2].occupied)
            {
                novo->lista2[pos2] = old_lista2[i];
            }
            else
            {
                int pos1 = posicao1(chave, novo->tam);
                if (!novo->lista1[pos1].occupied)
                {
                    novo->lista1[pos1] = old_lista2[i];
                }
            }
        }
    }

    free(old_lista1);
    free(old_lista2);

    return *novo;
}

bool cucko2(Hash *hash, int chave, int valor, int *counter);

bool cucko1(Hash *hash, int chave, int valor, int *counter)
{
    if (*counter > 10)
    {
        return 0;
    }
    int pos1 = posicao1(chave, hash->tam);
    if (!hash->lista1[pos1].occupied)
    {
        hash->lista1[pos1].key = chave;
        hash->lista1[pos1].value = valor;
        hash->lista1[pos1].occupied = true;
        return 1;
    }
    slot expulso = hash->lista1[pos1];
    hash->lista1[pos1].key = chave;
    hash->lista1[pos1].value = valor;
    hash->lista1[pos1].occupied = true;
    (*counter)++;
    return cucko2(hash, expulso.key, expulso.value, counter);
}

bool cucko2(Hash *hash, int chave, int valor, int *counter)
{
    if (*counter > 10)
    {
        return 0;
    }
    int pos2 = posicao2(chave, hash->tam);
    if (!hash->lista2[pos2].occupied)
    {
        hash->lista2[pos2].key = chave;
        hash->lista2[pos2].value = valor;
        hash->lista2[pos2].occupied = true;
        return 1;
    }
    slot expulso = hash->lista2[pos2];
    hash->lista2[pos2].key = chave;
    hash->lista2[pos2].value = valor;
    hash->lista2[pos2].occupied = true;
    (*counter)++;
    return cucko2(hash, expulso.key, expulso.value, counter);
}

void inserir(Hash *hash, int chave, int valor)
{
    if (hash == NULL)
    {
        return;
    }
    int counter = 0;
    int res = 0;
    while (res == 0)
    {
        res = cucko1(hash, chave, valor, &counter);
        if (res == 1)
        {
            break;
        }
        *hash = redimensionar(hash);
        counter = 0;
    }
}

void remover(Hash *hash, int chave)
{
    if (hash == NULL)
    {
        return;
    }

    int pos1 = posicao1(chave, hash->tam);
    if (hash->lista1[pos1].occupied && hash->lista1[pos1].key == chave)
    {
        hash->lista1[pos1].occupied = false;
        return;
    }

    int pos2 = posicao2(chave, hash->tam);
    if (hash->lista2[pos2].occupied && hash->lista2[pos2].key == chave)
    {
        hash->lista2[pos2].occupied = false;
    }
}

void buscar(Hash *hash, int chave)
{
    if (hash == NULL)
    {
        return;
    }

    int pos1 = posicao1(chave, hash->tam);
    if (hash->lista1[pos1].occupied && hash->lista1[pos1].key == chave)
    {
        printf("%d -> %d\n", chave, hash->lista1[pos1].value);
        return;
    }

    int pos2 = posicao2(chave, hash->tam);
    if (hash->lista2[pos2].occupied && hash->lista2[pos2].key == chave)
    {
        printf("%d -> %d\n", chave, hash->lista2[pos2].value);
        return;
    }

    printf("%d -> !E\n", chave);
}