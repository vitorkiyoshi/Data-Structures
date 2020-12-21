#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct No {
    struct No *esquerdo, *direito, *pai;
    int valor;
    char *texto;
    int visitado;
} No;
typedef No* p_no;
p_no remover(p_no raiz, int valor);
p_no buscar(p_no raiz, int valor);
p_no adicionar(p_no raiz, int valor, char *texto);
void destruir_arvore(p_no raiz);
void print_arvore(p_no raiz);