#ifndef OPERACOES_H
#define OPERACOES_H

typedef struct No
{
    int valor;
    struct No *prox;
} No;

typedef struct
{
    No *inicio;
} Conjunto;

void liberar_conjunto(Conjunto *conjunto);
void criar_conjunto(Conjunto *conjunto);
void inserir_elemento(Conjunto *conjunto, int valor);
void remover_elemento(Conjunto *conjunto, int valor);
void uniao_conjuntos(Conjunto *destino, const Conjunto *origem1, const Conjunto *origem2);
void intersecao_conjuntos(Conjunto *destino, const Conjunto *origem1, const Conjunto *origem2);
void diferenca_conjuntos(Conjunto *destino, const Conjunto *origem1, const Conjunto *origem2);
int contem_elemento(const Conjunto *conjunto, int valor);
void imprimir_conjunto(const Conjunto *conjunto, int id);

#endif