#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct ponto {
    double x,y;
    int visitado, objetivo;
} Ponto;

typedef Ponto* p_ponto;
typedef struct no {
    p_ponto atual;
    struct no *proximo;
} No;
typedef No* p_no;
double distancia(p_ponto a, p_ponto b){
    double x = a->x - b->x;
    double y = a->y - b->y;
    return sqrt(x*x + y*y);
}

typedef struct par{
    double ordem;
    int valor;
} Par;
typedef Par* p_par;
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
int comparar_pares(const void * a, const void * b){
    double oa = (*((p_par*)a))->ordem;
    double ob = (*((p_par*)b))->ordem;
    if (oa > ob)
        return 1;
    else if (oa < ob)
        return -1;
    else
        return 0;
}
double encontrar_caminho(p_ponto *pontos, double **distancias, int atual, int tamanho, double maior_distancia){
    pontos[atual]->visitado = 1;
    for(int i=0;i<tamanho;i++){
        if(pontos[i]->objetivo && distancias[atual][i] < maior_distancia){
            maior_distancia = distancias[atual][i];
        }
    }
    p_par *proximos = malloc((tamanho-2) * sizeof(p_par));
    int quantidade_proximos = 0;
    for(int i=0;i<tamanho;i++){
        if(!pontos[i]->visitado && distancias[i][atual] < maior_distancia && !pontos[i]->objetivo){
            proximos[quantidade_proximos] = malloc(sizeof(Par));
            proximos[quantidade_proximos]->valor = i;
            proximos[quantidade_proximos]->ordem = distancias[i][atual];
            quantidade_proximos++;
        }
    }
    qsort(proximos, quantidade_proximos, sizeof(p_par), comparar_pares);
    for(int i=0;i<quantidade_proximos;i++){
        if(proximos[i]->ordem<maior_distancia){
            double distancia_caminho = encontrar_caminho(pontos,distancias, proximos[i]->valor, tamanho, maior_distancia);
            distancia_caminho = distancia_caminho>proximos[i]->ordem?distancia_caminho:proximos[i]->ordem;
            if(distancia_caminho<maior_distancia){
                maior_distancia = distancia_caminho;
            }
        }
    }
    for(int i = 0; i<quantidade_proximos;i++){
        free(proximos[i]);
    }
    free(proximos);
    return maior_distancia;
}
int main() {
    p_no lista_pontos = NULL;
    int tamanho = 1;
    p_ponto leitura = malloc(sizeof(Ponto));
    scanf("%lf %lf", &leitura->x, &leitura->y);
    leitura->visitado=1;
    leitura->objetivo=0;
    lista_pontos = adicionar(lista_pontos, leitura);
    char tipo[15];
    while(1){
        leitura = malloc(sizeof(Ponto));
        if(scanf("%lf %lf", &leitura->x, &leitura->y) == EOF){
            free(leitura);
            break;
        }
        scanf("%s ", tipo);
        leitura->visitado=0;
        leitura->objetivo=!strcmp(tipo,"Lugia");
        lista_pontos = adicionar(lista_pontos, leitura);
        tamanho++;
    }
    p_ponto *pontos = malloc(sizeof(p_ponto)*tamanho);
    p_no atual = lista_pontos;
    for(int i=0;i<tamanho;i++){
        pontos[i] = atual->atual;
        atual = atual->proximo;
    }
    double **distancias = malloc(tamanho * sizeof(double*));
    for(int i = 0; i<tamanho;i++){
        distancias[i] = malloc(tamanho*sizeof(double));
    }
    for(int i = 0;i<tamanho;i++){
        distancias[i][i] = 0.0;
        for(int j = i+1;j<tamanho;j++){
            distancias[i][j] = distancias[j][i] = distancia(pontos[i], pontos[j]);
        }
    }
    int pos_atual = tamanho-1;
    double maior_distancia = encontrar_caminho(pontos, distancias, pos_atual, tamanho, INFINITY);
    int maior_distancia_inteira = (int) maior_distancia;
    printf("%i", (maior_distancia_inteira == maior_distancia? maior_distancia_inteira: maior_distancia_inteira+1));
    free(pontos);
    for(int i = 0; i<tamanho;i++){
        free(distancias[i]);
    }
    free(distancias);
    destruir_lista(lista_pontos);
    return 0;
}