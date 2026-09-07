#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Contato
{
    char nome[60];
    char endereco[110];
    char telefone[20];
    char aniversario[20];
};

void trim(char *s)
{
    while (*s && isspace((unsigned char)*s))
    {
        memmove(s, s + 1, strlen(s));
    }
}

void insercao(struct Contato contatos[], char *nome, char *endereco, char *telefone, char *aniversario)
{
    int i = 0;
    while (contatos[i].nome[0] != '\0')
    {
        i++;
    }
    strcpy(contatos[i].nome, nome);
    strcpy(contatos[i].endereco, endereco);
    strcpy(contatos[i].telefone, telefone);
    strcpy(contatos[i].aniversario, aniversario);
}

int remocao(struct Contato contatos[], char *nome)
{
    int q_removidos = 0;
    for (int i = 0; i < 1010; i++)
    {
        if (strcmp(contatos[i].nome, nome) == 0)
        {
            contatos[i].nome[0] = '\0';
            contatos[i].endereco[0] = '\0';
            contatos[i].telefone[0] = '\0';
            contatos[i].aniversario[0] = '\0';
            q_removidos++;
            break;
        }
    }
    return q_removidos;
}

void busca(struct Contato contatos[], char *nome)
{
    int pelo_menos_um_encontrado = 0;
    int pos_contatos = 1;
    printf("Resultado da busca:\n");
    for (int i = 0; i < 1010; i++)
    {
        if (strstr(contatos[i].nome, nome) != NULL)
        {
            pelo_menos_um_encontrado = 1;
            printf("(%d) %s\t%s\t%s\t%s\n", pos_contatos, contatos[i].nome, contatos[i].endereco, contatos[i].telefone, contatos[i].aniversario);
            printf("\n");
        }
        if (contatos[i].nome[0] != '\0')
        {
            pos_contatos++;
        }
    }
    if (!pelo_menos_um_encontrado)
    {
        printf("Nenhum contato.\n");
        printf("\n");
    }
}

void impressao(struct Contato contatos[])
{
    int q_contatos = 0;
    int pos_contatos = 1;
    printf("Listagem:\n");
    for (int i = 0; i < 1010; i++)
    {
        if (contatos[i].nome[0] != '\0')
        {
            printf("(%d) %s\t%s\t%s\t%s\n", pos_contatos, contatos[i].nome, contatos[i].endereco, contatos[i].telefone, contatos[i].aniversario);
            printf("\n");
            q_contatos++;
            pos_contatos++;
        }
    }
}

int main()
{
    struct Contato contatos[1010] = {0};
    char modo;
    while (scanf(" %c", &modo))
    {
        getchar();

        if (modo == 'f')
        {
            break;
        }
        else if (modo == 'i')
        {
            char nome[60];
            char endereco[110];
            char telefone[20];
            char aniversario[20];
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';
            trim(nome);
            fgets(endereco, sizeof(endereco), stdin);
            endereco[strcspn(endereco, "\n")] = '\0';
            trim(endereco);
            fgets(telefone, sizeof(telefone), stdin);
            telefone[strcspn(telefone, "\n")] = '\0';
            trim(telefone);
            fgets(aniversario, sizeof(aniversario), stdin);
            aniversario[strcspn(aniversario, "\n")] = '\0';
            trim(aniversario);
            insercao(contatos, nome, endereco, telefone, aniversario);
            printf("Contato para %s inserido.\n", nome);
            printf("\n");
        }
        else if (modo == 'r')
        {
            char nome_remocao[60];
            int q_removidos = 0;
            fgets(nome_remocao, sizeof(nome_remocao), stdin);
            nome_remocao[strcspn(nome_remocao, "\n")] = '\0';
            q_removidos = remocao(contatos, nome_remocao);
            printf("Contatos de %s removidos: %d.\n", nome_remocao, q_removidos);
            printf("\n");
        }
        else if (modo == 'b')
        {
            char nome_busca[60];
            fgets(nome_busca, sizeof(nome_busca), stdin);
            nome_busca[strcspn(nome_busca, "\n")] = '\0';
            busca(contatos, nome_busca);
        }
        else if (modo == 'p')
        {
            impressao(contatos);
        }
    }

    return 0;
}