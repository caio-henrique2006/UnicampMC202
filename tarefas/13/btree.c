#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

// Funções para fila encadeada utilizadas para a impressão por níveis da árvore B
void fila_inicializar(Fila *fila)
{
    if (!fila)
        return;

    fila->frente = NULL;
    fila->tras = NULL;
}

bool fila_vazia(const Fila *fila)
{
    return fila == NULL || fila->frente == NULL;
}

void fila_enfileirar(Fila *fila, No *no)
{
    if (!fila || !no)
        return;

    FilaNo *novo = malloc(sizeof(*novo));
    if (!novo)
        return;

    novo->no = no;
    novo->prox = NULL;

    if (fila_vazia(fila))
    {
        fila->frente = novo;
        fila->tras = novo;
        return;
    }

    fila->tras->prox = novo;
    fila->tras = novo;
}

No *fila_desenfileirar(Fila *fila)
{
    if (!fila || fila_vazia(fila))
        return NULL;

    FilaNo *atual = fila->frente;
    No *no = atual->no;

    fila->frente = atual->prox;
    if (fila->frente == NULL)
        fila->tras = NULL;

    free(atual);
    return no;
}

// Encontra posição para inserção/descida e informa se a chave já existe no nó
static int buscarPosicaoNo(const No *no, int codigo, bool *encontrou)
{
    int esquerda = 0;
    int direita = no->chaves_usadas - 1;

    while (esquerda <= direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;
        int codigo_meio = no->dados[meio].codigo;

        if (codigo_meio == codigo)
        {
            if (encontrou)
                *encontrou = true;
            return meio;
        }

        if (codigo_meio < codigo)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }

    if (encontrou)
        *encontrou = false;

    return esquerda;
}

// Percorre a BTree para encontrar o código
static bool contemCodigo(const No *no, int codigo)
{
    bool encontrou = false;
    int indice_insercao = buscarPosicaoNo(no, codigo, &encontrou);

    if (encontrou)
        return true;

    if (no->eh_folha)
        return false;

    return contemCodigo(no->filhos[indice_insercao], codigo);
}

// Processa a divisão dos filhos quando grau atinge o limite máximo
static void dividirFilho(No *pai, int indice_filho)
{
    No *filho_para_dividir = pai->filhos[indice_filho];
    int grau_minimo = filho_para_dividir->t;

    // Divisão dos filhos
    No *irmao_direito = malloc(sizeof *irmao_direito);
    irmao_direito->eh_folha = filho_para_dividir->eh_folha;
    irmao_direito->t = grau_minimo;
    irmao_direito->chaves_usadas = grau_minimo - 1;
    irmao_direito->dados = malloc((2 * grau_minimo - 1) * sizeof *irmao_direito->dados);
    irmao_direito->filhos = malloc((2 * grau_minimo) * sizeof *irmao_direito->filhos);

    for (int posicao_filho = 0; posicao_filho < 2 * grau_minimo; posicao_filho++)
        irmao_direito->filhos[posicao_filho] = NULL;

    for (int deslocamento_chave = 0; deslocamento_chave < grau_minimo - 1; deslocamento_chave++)
        irmao_direito->dados[deslocamento_chave] = filho_para_dividir->dados[deslocamento_chave + grau_minimo];

    if (!filho_para_dividir->eh_folha)
    {
        for (int deslocamento_filho = 0; deslocamento_filho < grau_minimo; deslocamento_filho++)
            irmao_direito->filhos[deslocamento_filho] = filho_para_dividir->filhos[deslocamento_filho + grau_minimo];
    }

    filho_para_dividir->chaves_usadas = grau_minimo - 1;

    // Limpa os dados e filhos do nó que foi dividido
    for (int posicao = grau_minimo; posicao < 2 * grau_minimo - 1; posicao++)
        filho_para_dividir->dados[posicao] = (Data){0, 0, 0};

    for (int posicao = grau_minimo; posicao < 2 * grau_minimo; posicao++)
        filho_para_dividir->filhos[posicao] = NULL;

    // Atualizando o pai
    for (int posicao_filho = pai->chaves_usadas; posicao_filho >= indice_filho + 1; posicao_filho--)
        pai->filhos[posicao_filho + 1] = pai->filhos[posicao_filho];

    pai->filhos[indice_filho + 1] = irmao_direito;

    for (int posicao_chave = pai->chaves_usadas - 1; posicao_chave >= indice_filho; posicao_chave--)
        pai->dados[posicao_chave + 1] = pai->dados[posicao_chave];

    pai->dados[indice_filho] = filho_para_dividir->dados[grau_minimo - 1];
    pai->chaves_usadas++;
}

static void inserirEmNoNaoCheio(No *no, int codigo, long inicio, long fim)
{
    // Se for folha, insere diretamente na posição correta (garante que não está cheio)
    if (no->eh_folha)
    {
        bool encontrou = false;
        int indice_insercao = buscarPosicaoNo(no, codigo, &encontrou);

        for (int indice_chave = no->chaves_usadas - 1; indice_chave >= indice_insercao; indice_chave--)
        {
            no->dados[indice_chave + 1] = no->dados[indice_chave];
        }

        no->dados[indice_insercao].codigo = codigo;
        no->dados[indice_insercao].inicio = inicio;
        no->dados[indice_insercao].fim = fim;
        no->chaves_usadas++;
        return;
    }

    // Se não for folha, percorre recursivamente para encontrar o filho correto
    bool encontrou = false;
    int indice_chave = buscarPosicaoNo(no, codigo, &encontrou);

    // Divide o filho se estiver cheio na descida da árvore
    if (no->filhos[indice_chave]->chaves_usadas == 2 * no->t - 1)
    {
        dividirFilho(no, indice_chave);
        if (codigo > no->dados[indice_chave].codigo)
            indice_chave++;
    }

    inserirEmNoNaoCheio(no->filhos[indice_chave], codigo, inicio, fim);
}

void imprimirPorNiveis(const No *raiz)
{
    if (!raiz)
        return;

    if (raiz->chaves_usadas == 0)
    {
        printf("A arvore esta vazia.\n");
        return;
    }

    // Usa filas para percorrer em largura
    Fila fila;
    fila_inicializar(&fila);
    fila_enfileirar(&fila, (No *)raiz);

    int nivel = 0;
    while (!fila_vazia(&fila))
    {
        int qtd_no_nivel = 0;

        for (FilaNo *atual = fila.frente; atual != NULL; atual = atual->prox)
            qtd_no_nivel++;

        No **nos_do_nivel = malloc((size_t)qtd_no_nivel * sizeof(*nos_do_nivel));
        if (!nos_do_nivel)
            return;

        for (int i = 0; i < qtd_no_nivel; i++)
            nos_do_nivel[i] = fila_desenfileirar(&fila);

        printf("nivel %d: ", nivel);

        for (int i = 0; i < qtd_no_nivel; i++)
        {
            No *atual = nos_do_nivel[i];

            // if (i > 0)
            //     printf(" ");

            printf("[");
            for (int j = 0; j < atual->chaves_usadas; j++)
            {
                if (j > 0)
                    printf(",");
                printf("%d", atual->dados[j].codigo);
            }
            printf("] ");
        }

        printf("\n");

        for (int i = 0; i < qtd_no_nivel; i++)
        {
            No *atual = nos_do_nivel[i];

            // Se não for folha, enfileira os filhos para o próximo nível
            if (!atual->eh_folha)
            {
                for (int j = 0; j < 2 * atual->t; j++)
                {
                    if (atual->filhos[j])
                        fila_enfileirar(&fila, atual->filhos[j]);
                }
            }
        }

        free(nos_do_nivel);
        nivel++;
    }
}

No *criarArvoreB(int t)
{

    No *raiz = malloc(sizeof *raiz);
    if (!raiz)
        return NULL;

    raiz->eh_folha = true;
    raiz->t = t;
    raiz->chaves_usadas = 0;
    raiz->dados = malloc((2 * t - 1) * sizeof *raiz->dados);
    raiz->filhos = malloc((2 * t) * sizeof *raiz->filhos);

    for (int i = 0; i < 2 * t; i++)
        raiz->filhos[i] = NULL;

    return raiz;
}

bool inserir(No **raiz, int codigo, long inicio, long fim)
{
    if (!raiz || !*raiz)
        return false;

    if (contemCodigo(*raiz, codigo))
        return false;

    No *raiz_atual = *raiz;

    // Se a raiz estiver cheia, cria uma nova raiz e divide a antiga
    if (raiz_atual->chaves_usadas == 2 * raiz_atual->t - 1)
    {
        No *nova_raiz = malloc(sizeof *nova_raiz);
        if (!nova_raiz)
            return false;

        nova_raiz->eh_folha = false;
        nova_raiz->t = raiz_atual->t;
        nova_raiz->chaves_usadas = 0;
        nova_raiz->dados = malloc((2 * nova_raiz->t - 1) * sizeof *nova_raiz->dados);
        nova_raiz->filhos = malloc((2 * nova_raiz->t) * sizeof *nova_raiz->filhos);

        for (int posicao_filho = 0; posicao_filho < 2 * nova_raiz->t; posicao_filho++)
            nova_raiz->filhos[posicao_filho] = NULL;

        nova_raiz->filhos[0] = raiz_atual;
        *raiz = nova_raiz;

        dividirFilho(nova_raiz, 0);
        inserirEmNoNaoCheio(nova_raiz, codigo, inicio, fim);
        return true;
    }

    inserirEmNoNaoCheio(raiz_atual, codigo, inicio, fim);
    return true;
}

bool buscar(const No *raiz, int codigo, long *inicio, long *fim)
{
    const No *atual = raiz;

    while (atual)
    {
        bool encontrou = false;
        int indice = buscarPosicaoNo(atual, codigo, &encontrou);

        if (encontrou)
        {
            if (inicio)
                *inicio = atual->dados[indice].inicio;
            if (fim)
                *fim = atual->dados[indice].fim;
            return true;
        }

        if (atual->eh_folha)
            return false;

        atual = atual->filhos[indice];
    }

    return false;
}

static void listarRecursivo(const No *no)
{
    if (!no)
        return;

    for (int i = 0; i < no->chaves_usadas; i++)
    {
        if (!no->eh_folha)
            listarRecursivo(no->filhos[i]);

        printf("%d ", no->dados[i].codigo);
    }

    if (!no->eh_folha)
        listarRecursivo(no->filhos[no->chaves_usadas]);
}

void listar(const No *raiz)
{
    if (raiz->chaves_usadas == 0)
    {
        printf("A arvore esta vazia.\n");
        return;
    }
    listarRecursivo(raiz);
    printf("\n");
}
