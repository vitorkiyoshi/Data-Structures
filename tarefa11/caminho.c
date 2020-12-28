#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
/*Estruturas, pontos para dist. euclidiana e para calculo via grafo*/
typedef struct ponto {
    double x,y;
    int inicial;
    double distancia_ao_objetivo;
} Ponto;

typedef Ponto* p_ponto;
typedef struct no {//lista de pontos
    p_ponto atual;
    struct no *proximo;
} No;
typedef No* p_no;
double calcular_distancia(p_ponto a, p_ponto b){//dist. Euclidiana
    double x = a->x - b->x;
    double y = a->y - b->y;
    return sqrt(x*x + y*y);
}
//operar lista
p_no adicionar(p_no raiz, p_ponto ponto){
    p_no novo = malloc(sizeof(No));
    novo->atual = ponto;
    novo->proximo = raiz;
    return novo;
}
void destruir_lista(p_no raiz){
    if(raiz != NULL) {
        destruir_lista(raiz->proximo);
        free(raiz->atual);
        free(raiz);
    }
}
int main() {
}