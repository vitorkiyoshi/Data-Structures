#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
/*Estruturas, pontos para dist. euclidiana e para calculo via grafo*/
typedef struct Ponto {
    double x,y;
    int inicial;
    double distancia_ao_objetivo;
} Ponto;
typedef Ponto *p_ponto;
typedef struct No {//lista de pontos
    p_ponto atual;
    struct No *proximo;
} No;
typedef No *p_no;
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
//comparar a distnacia entre os pontos, para saber qual o menor
int comparar_pontos(const void *a, const void *b){
    double oa = (*((p_ponto*)a))->distancia_ao_objetivo;
    double ob = (*((p_ponto*)b))->distancia_ao_objetivo;
    if (oa > ob)
        return 1;
    else if (oa < ob)
        return -1;
    else
        return 0;
}
//ponteiro para que consiga ser dinamicamente alocado, double pointer para matriz.
double **encontrar_matriz_distancias(p_ponto *pontos, int tamanho){
    double **distancias = malloc(tamanho * sizeof(double *));
    for (int i = 0; i < tamanho; i++) {
        distancias[i] = malloc(tamanho * sizeof(double));
    }
    for (int i = 0; i < tamanho; i++) {
        distancias[i][i] = 0.0;
        for (int j = i + 1; j < tamanho; j++) {
            distancias[i][j] = calcular_distancia(pontos[i], pontos[j]);
            distancias[j][i] = calcular_distancia(pontos[i], pontos[j]);
        }
    }
    return distancias;
}
int round_up(double dist) {//verificação de arredondament
    int distancia_inteira = (int) dist;
    if(dist == distancia_inteira){
        return distancia_inteira;
    } else{
        return distancia_inteira + 1;
    }
}

int main(){
    p_no lista_pontos = criarlista();
    p_no lista_objetivos = criarlista();
    int tamanho=1;
    p_ponto leitura = malloc(sizeof(Ponto));
    char tipo[15];
    scanf("%lf %lf", &leitura->x, &leitura->y);
    leitura->inicial=1;
    leitura->distancia_ao_objetivo = INFINITY;//tipologia especial para que seja maior que qualquer outro numero double.
    lista_pontos = adicionar(lista_pontos, leitura);

    return 0;
}