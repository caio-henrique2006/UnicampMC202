#ifndef HASH_H
#define HASH_H

#include <stdbool.h>

typedef struct
{
    int key;
    int value;
    bool occupied;
} slot;

typedef struct
{
    slot *lista1;
    slot *lista2;
    int tam;
    int max;
} Hash;

Hash criar(Hash *hash, int tam);
void inserir(Hash *hash, int chave, int valor);
void remover(Hash *hash, int chave);
void buscar(Hash *hash, int chave);

#endif
