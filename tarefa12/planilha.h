#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//estruturas para lista de tokens e celulas
typedef struct lista_token{
    char *token;
    struct lista_token *proximo;
} Lista_token;

typedef struct celula{
    char **expressao;
    int valor;
    int calculado;
} Celula;

p_lista adicionar(p_lista raiz, char *token);
void destruir_lista(p_lista raiz);
char **tokenizar(char *expressao);
char* resolver_expressao(p_celula **celulas, char **expressao, char **dependencias, int quantidade_dependencias);
void escreverArquivo(int colunas, int linhas, p_celula **celulas, char *caminho);
int verificarConstante(char *str);