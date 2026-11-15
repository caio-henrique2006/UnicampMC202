#ifndef BTREE_H
#define BTREE_H

typedef struct no No;
typedef struct data Data;
typedef struct fila_no FilaNo;
typedef struct fila Fila;

struct no
{
    bool eh_folha;
    int t;
    int chaves_usadas;
    Data *dados;
    No **filhos;
};

struct data
{
    int codigo;
    long inicio;
    long fim;
};

struct fila_no
{
    No *no;
    FilaNo *prox;
};

struct fila
{
    FilaNo *frente;
    FilaNo *tras;
};

No *criarArvoreB(int t);
bool inserir(No **raiz, int codigo, long inicio, long fim);
bool buscar(const No *raiz, int codigo, long *inicio, long *fim);
void listar(const No *raiz);
void imprimirPorNiveis(const No *raiz);
void fila_inicializar(Fila *fila);
bool fila_vazia(const Fila *fila);
void fila_enfileirar(Fila *fila, No *no);
No *fila_desenfileirar(Fila *fila);

#endif