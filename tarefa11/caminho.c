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
p_no criarlista(){
    p_no lista;
    lista->atual=NULL;
    lista->proximo=NULL;
    return lista;
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
int comparar_pontos(const void * a, const void * b){
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
            distancias[i][j] = distancias[j][i] = calcular_distancia(pontos[i], pontos[j]);
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

int main() {
    //listas
    p_no lista_pontos = criarlista();
    p_no lista_objetivos = criarlista();
    int tamanho = 1;
    p_ponto leitura = malloc(sizeof(Ponto));
    scanf("%lf %lf", &leitura->x, &leitura->y);
    leitura->inicial=1;
    leitura->distancia_ao_objetivo = INFINITY;//tipologia especial para que seja maior que qualquer outro numero double.
    lista_pontos = adicionar(lista_pontos, leitura);
    char tipo[15];
    // 2 doubles como ponto
    while(1){
        leitura = malloc(sizeof(Ponto));
        if(scanf("%lf %lf", &leitura->x, &leitura->y) == EOF){
            free(leitura);
            break;
        }
        scanf("%s ", tipo);
        leitura->inicial=0;
        if(strcmp(tipo,"Lugia")){//definindo distancia até o objetivo
            leitura->distancia_ao_objetivo = INFINITY;
            lista_pontos = adicionar(lista_pontos, leitura);
            tamanho++;
        } else {
            leitura->distancia_ao_objetivo = 0;
            lista_objetivos = adicionar(lista_objetivos, leitura);
        }
    }
    //registrando matriz de distancias
    p_ponto *pontos = malloc(sizeof(p_ponto)*tamanho);
    p_no atual = lista_pontos;
    /*Deve-se então, registrar qual possui menor distancia entre os pontos e o lugia, assim percorrendo a lista*/
    for(int i=0;i<tamanho;i++){
        pontos[i] = atual->atual;
        p_no no_objetivo = lista_objetivos;
        while(no_objetivo != NULL){
            p_ponto objetivo = no_objetivo->atual;
            double distancia_ao_objetivo = calcular_distancia(pontos[i], objetivo);
            if(distancia_ao_objetivo < pontos[i]->distancia_ao_objetivo){
                pontos[i]->distancia_ao_objetivo = distancia_ao_objetivo;
            }
            no_objetivo = no_objetivo->proximo;
        }
        atual = atual->proximo;
    }
    qsort(pontos, tamanho, sizeof(p_ponto), comparar_pontos);
    double **distancias = encontrar_matriz_distancias(pontos, tamanho);//criando matriz com pontos em ordem
    for(int i=0;i<tamanho;i++){
        for(int j=0;j<i;j++){
            if(distancias[i][j] < pontos[i]->distancia_ao_objetivo){
                if(distancias[i][j]>pontos[j]->distancia_ao_objetivo) {
                    pontos[i]->distancia_ao_objetivo = distancias[i][j];
                } else {
                    pontos[i]->distancia_ao_objetivo = pontos[j]->distancia_ao_objetivo;
                    break;
                }
            }
        }
        if(pontos[i]->inicial){
            printf("%i", round_up(pontos[i]->distancia_ao_objetivo));//por fim, printar o primeiro valor
        }
    }
    //free para: listapontos, listaobjetivos, pontos, distancias
    destruir_lista(lista_pontos);
    destruir_lista(lista_objetivos);
    free(pontos);
    for(int i = 0;i<tamanho;i++){
        free(distancias[i]);
    }
    free(distancias);
    return 0;
}