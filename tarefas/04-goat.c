#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Executa a regra 1 e 2
int processa_primeira_letra(char char_atual, char *palavra, char *fim_palavra)
{
    if (char_atual == 'a' || char_atual == 'e' || char_atual == 'i' || char_atual == 'o' || char_atual == 'u' ||
        char_atual == 'A' || char_atual == 'E' || char_atual == 'I' || char_atual == 'O' || char_atual == 'U')
    {
        int tam = strlen(palavra);
        palavra[tam] = char_atual;
        palavra[tam + 1] = '\0';
        strcat(fim_palavra, "ma");
        return 0;
    }
    else
    {
        int tam = strlen(fim_palavra);
        fim_palavra[tam] = char_atual;
        fim_palavra[tam + 1] = '\0';
        strcat(fim_palavra, "ma");
        return 1;
    }
}

// Executa a regra 3
int processa_numero(char char_atual, char *frase, int *i)
{
    char str_numero[1000] = "";
    str_numero[0] = char_atual;
    str_numero[1] = '\0';
    int j = *i;
    while (1)
    {
        j++;
        if (isdigit((unsigned char)frase[j]))
        {
            int tam = strlen(str_numero);
            str_numero[tam] = frase[j];
            str_numero[tam + 1] = '\0';
        }
        else
        {
            break;
        }
    }
    int numero = atoi(str_numero);
    *i = j - 1;
    return numero;
}

// Função de utilidade para somar os a's ao final
void char_a_final(char *a_final, int i)
{
    for (int j = 0; j < i; j++)
    {
        a_final[j] = 'a';
    }
    a_final[i] = '\0';
}

int main()
{
    // Input da frase
    char trans_frase[410000] = "";
    char frase[410000];
    while (fgets(frase, sizeof frase, stdin) != NULL)
    {
        frase[strcspn(frase, "\n")] = '\0';

        // Analisando palavra a palavra:
        trans_frase[0] = '\0';
        int pos_trans_frase = 0;
        char palavra[120] = "";
        char fim_palavra[20] = "";
        char a_final[120] = "";
        int is_primeira_letra = 1;
        int is_primeira_letra_consoante = 0;
        int soma_final = 0;
        for (int i = 0; 1; i++)
        {
            char char_atual = frase[i];
            // Executa a definição da tradução da palavra quando encontra um espaço vazio ou o fim da frase
            if (isspace((unsigned char)char_atual) || char_atual == '\0')
            {
                if (strlen(palavra) > 0 || strlen(fim_palavra) > 0)
                {
                    a_final[0] = '\0';
                    int tam_palavra = strlen(palavra);
                    if (is_primeira_letra_consoante)
                        tam_palavra++;
                    char_a_final(a_final, tam_palavra);
                    strcpy(trans_frase + pos_trans_frase, palavra);
                    pos_trans_frase += strlen(palavra);
                    strcpy(trans_frase + pos_trans_frase, fim_palavra);
                    pos_trans_frase += strlen(fim_palavra);
                    strcpy(trans_frase + pos_trans_frase, a_final);
                    pos_trans_frase += strlen(a_final);
                    if (char_atual != '\0')
                    {
                        strcpy(trans_frase + pos_trans_frase, " ");
                        pos_trans_frase += 1;
                    }
                }
                palavra[0] = '\0';
                fim_palavra[0] = '\0';
                is_primeira_letra_consoante = 0;
                is_primeira_letra = 1;
                if (char_atual == '\0')
                {
                    break;
                }
            }
            // Observa os casos e igora caracteres especiais
            else if (isalpha((unsigned char)char_atual))
            {
                if (is_primeira_letra)
                {
                    is_primeira_letra_consoante = processa_primeira_letra(char_atual, palavra, fim_palavra);
                    is_primeira_letra = 0;
                }
                else
                {
                    int tam = strlen(palavra);
                    palavra[tam] = char_atual;
                    palavra[tam + 1] = '\0';
                }
            }
            else if (isdigit((unsigned char)char_atual))
            {
                soma_final += processa_numero(char_atual, frase, &i);
            }
        }
        // Adapta a gramática da resposta
        if (pos_trans_frase > 0)
        {
            if (trans_frase[pos_trans_frase - 1] == ' ')
            {
                trans_frase[pos_trans_frase - 1] = '\0';
            }
        }
        if (pos_trans_frase == 0 && soma_final == 1)
        {
            printf("%d goat says:\n", soma_final);
        }
        else if (pos_trans_frase == 0 && soma_final != 1)
        {
            printf("%d goats say:\n", soma_final);
        }
        else if (pos_trans_frase != 0 && soma_final == 1)
        {
            printf("%d goat says: %s\n", soma_final, trans_frase);
        }
        else
        {
            printf("%d goats say: %s\n", soma_final, trans_frase);
        }
    }
    return 0;
}
