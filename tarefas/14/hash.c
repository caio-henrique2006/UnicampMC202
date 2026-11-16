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

int posicao1(int chave, int tam, int seed)
{
    // Hash 1
    int h = wang_hash(chave + seed);
    return h % tam;
}

int posicao2(int chave, int tam, int seed)
{
    // Hash 2
    int h = wang_hash((chave ^ 0x5bd1e995) + seed);
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
    hash->qt_lista1 = 0;
    hash->qt_lista2 = 0;
    hash->seed = 0;

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
    hash->qt_lista1 = 0;
    hash->qt_lista2 = 0;
    hash->seed = 0;

    return *hash;
}

bool cucko1(Hash *hash, int chave, int valor, int *counter, slot *restante);
bool cucko2(Hash *hash, int chave, int valor, int *counter, slot *restante);

// Insere um elemento usando o cuckoo, sem redimensionar.
// Se a corrente falhar, o elemento que sobrou fica em restante.
static bool cucko_inserir(Hash *hash, int chave, int valor)
{
    int counter = 0;
    slot restante;
    return cucko1(hash, chave, valor, &counter, &restante);
}

Hash redimensionar(Hash *hash, slot *extra)
{
    slot *old_lista1 = hash->lista1;
    slot *old_lista2 = hash->lista2;
    int old_tam = hash->tam;
    int new_tam = old_tam * 1.5;

    bool sucesso;
    do
    {
        slot *nova1 = calloc((size_t)new_tam, sizeof(slot));
        slot *nova2 = calloc((size_t)new_tam, sizeof(slot));

        hash->lista1 = nova1;
        hash->lista2 = nova2;
        hash->tam = new_tam;
        hash->qt_lista1 = 0;
        hash->qt_lista2 = 0;
        hash->seed++; // Muda as funcoes hash a cada tentativa

        // Reinsere todos os elementos antigos usando cuckoo (sem descartar)
        sucesso = true;
        for (int i = 0; i < old_tam && sucesso; i++)
        {
            if (old_lista1[i].occupied)
            {
                sucesso = cucko_inserir(hash, old_lista1[i].key, old_lista1[i].value);
            }
        }
        for (int i = 0; i < old_tam && sucesso; i++)
        {
            if (old_lista2[i].occupied)
            {
                sucesso = cucko_inserir(hash, old_lista2[i].key, old_lista2[i].value);
            }
        }
        if (sucesso && extra != NULL)
        {
            sucesso = cucko_inserir(hash, extra->key, extra->value);
        }

        if (!sucesso)
        {
            // Descarta as tabelas novas e tenta de novo, maiores
            free(nova1);
            free(nova2);
            new_tam *= 2;
        }
    } while (!sucesso);

    free(old_lista1);
    free(old_lista2);

    return *hash;
}

bool cucko1(Hash *hash, int chave, int valor, int *counter, slot *restante)
{
    if (*counter > hash->tam)
    {
        restante->key = chave;
        restante->value = valor;
        restante->occupied = true;
        return false;
    }
    int pos1 = posicao1(chave, hash->tam, hash->seed);
    if (!hash->lista1[pos1].occupied)
    {
        hash->lista1[pos1].key = chave;
        hash->lista1[pos1].value = valor;
        hash->lista1[pos1].occupied = true;
        hash->qt_lista1++;
        return true;
    }
    slot expulso = hash->lista1[pos1];
    hash->lista1[pos1].key = chave;
    hash->lista1[pos1].value = valor;
    hash->lista1[pos1].occupied = true;
    (*counter)++;
    return cucko2(hash, expulso.key, expulso.value, counter, restante);
}

bool cucko2(Hash *hash, int chave, int valor, int *counter, slot *restante)
{
    if (*counter > hash->tam)
    {
        restante->key = chave;
        restante->value = valor;
        restante->occupied = true;
        return false;
    }
    int pos2 = posicao2(chave, hash->tam, hash->seed);
    if (!hash->lista2[pos2].occupied)
    {
        hash->lista2[pos2].key = chave;
        hash->lista2[pos2].value = valor;
        hash->lista2[pos2].occupied = true;
        hash->qt_lista2++;
        return true;
    }
    slot expulso = hash->lista2[pos2];
    hash->lista2[pos2].key = chave;
    hash->lista2[pos2].value = valor;
    hash->lista2[pos2].occupied = true;
    (*counter)++;
    return cucko1(hash, expulso.key, expulso.value, counter, restante);
}

void inserir(Hash *hash, int chave, int valor)
{
    if (hash == NULL)
    {
        return;
    }

    int counter = 0;
    slot restante;

    // Observa se a chave já existe e substitui
    int pos1 = posicao1(chave, hash->tam, hash->seed);
    if (hash->lista1[pos1].occupied && hash->lista1[pos1].key == chave)
    {
        hash->lista1[pos1].value = valor;
        return;
    }
    int pos2 = posicao2(chave, hash->tam, hash->seed);
    if (hash->lista2[pos2].occupied && hash->lista2[pos2].key == chave)
    {
        hash->lista2[pos2].value = valor;
        return;
    }

    if (!cucko1(hash, chave, valor, &counter, &restante))
    {
        // Reconstroi incluindo o elemento que sobrou
        *hash = redimensionar(hash, &restante);
        return;
    }

    if ((long)(hash->qt_lista1 + hash->qt_lista2) * 100 >
        (long)hash->max * 2 * hash->tam)
    {
        *hash = redimensionar(hash, NULL);
    }
}

void remover(Hash *hash, int chave)
{
    if (hash == NULL)
    {
        return;
    }

    int pos1 = posicao1(chave, hash->tam, hash->seed);
    if (hash->lista1[pos1].occupied && hash->lista1[pos1].key == chave)
    {
        hash->lista1[pos1].occupied = false;
        hash->qt_lista1--;
        return;
    }

    int pos2 = posicao2(chave, hash->tam, hash->seed);
    if (hash->lista2[pos2].occupied && hash->lista2[pos2].key == chave)
    {
        hash->lista2[pos2].occupied = false;
        hash->qt_lista2--;
    }
}

void buscar(Hash *hash, int chave)
{
    if (hash == NULL)
    {
        return;
    }

    int pos1 = posicao1(chave, hash->tam, hash->seed);
    if (hash->lista1[pos1].occupied && hash->lista1[pos1].key == chave)
    {
        printf("%d -> %d\n", chave, hash->lista1[pos1].value);
        return;
    }

    int pos2 = posicao2(chave, hash->tam, hash->seed);
    if (hash->lista2[pos2].occupied && hash->lista2[pos2].key == chave)
    {
        printf("%d -> %d\n", chave, hash->lista2[pos2].value);
        return;
    }

    printf("%d -> !E\n", chave);
}
