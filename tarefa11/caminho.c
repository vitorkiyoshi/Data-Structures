#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct ponto {//estruturas para lista de distancias
    double x,y;
    int inicial;
    double distancia_ao_objetivo;
} Ponto;

typedef Ponto* p_ponto;
typedef struct no {
    p_ponto atual;
    struct no *proximo;
} No;
typedef No* p_no;
//dist. euclidiana entre dois pontos(usar estrutura de ponto)
double calcular_distancia(p_ponto a, p_ponto b){
    double x = a->x - b->x;
    double y = a->y - b->y;
    return sqrt(x*x + y*y);
}
//operações para listas
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
//comparador de distancias
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

int main() {//usar então as listas para formar grafo de distancias, consistindo em achar a menor dist
    p_no lista_pontos = NULL;
    p_no lista_objetivos = NULL;
    int tamanho = 1;
    p_ponto leitura = malloc(sizeof(Ponto));
    //leitura inicial
    scanf("%lf %lf", &leitura->x, &leitura->y);
    leitura->inicial=1;
    leitura->distancia_ao_objetivo = INFINITY;
    lista_pontos = adicionar(lista_pontos, leitura);
    char tipo[15];
    while(1){//após leitura inicial, registrar comparação entre os pontos até EOF
        leitura = malloc(sizeof(Ponto));
        if(scanf("%lf %lf", &leitura->x, &leitura->y) == EOF){
            free(leitura);
            break;
        }
        scanf("%s ", tipo);
        leitura->inicial=0;
        if(strcmp(tipo,"Lugia")){//verificando se o tipo é lugia, superior a todos os outros no grafo
            leitura->distancia_ao_objetivo = INFINITY;//tipologia especial que é maior que qualquer double
            lista_pontos = adicionar(lista_pontos, leitura);
            tamanho++;
        } else {
            leitura->distancia_ao_objetivo = 0;
            lista_objetivos = adicionar(lista_objetivos, leitura);
        }
    }
    //usando então agora vetor para distancias, bastando calcular na hora a dist agora
    p_ponto *pontos = malloc(sizeof(p_ponto)*tamanho);
    p_no atual = lista_pontos;
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
    //ordenando distancias usando comparador
    qsort(pontos, tamanho, sizeof(p_ponto), comparar_pontos);
    for(int i=0;i<tamanho;i++){
        for(int j=0;j<i;j++){//adicionando mais pontos de break para aumentar eficiencia
            double distancia_i_j = calcular_distancia(pontos[i], pontos[j]);
            if(distancia_i_j < pontos[i]->distancia_ao_objetivo){
                if(distancia_i_j>pontos[j]->distancia_ao_objetivo) {
                    pontos[i]->distancia_ao_objetivo = distancia_i_j;
                } else {
                    pontos[i]->distancia_ao_objetivo = pontos[j]->distancia_ao_objetivo;
                    break;
                }
            }
            if(pontos[j]->distancia_ao_objetivo > pontos[i]->distancia_ao_objetivo){
                break;
            }
        }
        if(pontos[i]->inicial){
            printf("%i", (int) ceil(pontos[i]->distancia_ao_objetivo));
            break;
        }
    }
    /*Free para: listapontos, listaobjetivos e pontos*/
    destruir_lista(lista_pontos);
    destruir_lista(lista_objetivos);
    free(pontos);
    return 0;
}