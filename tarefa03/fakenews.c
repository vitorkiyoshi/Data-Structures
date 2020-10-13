#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
double * media(double * vetor[], int * tamanho_vetor){
    int *i,*media;
    i=malloc(sizeof(int));
    media=malloc(sizeof(double));
    for(*i=0;*i<*tamanho_vetor;*i++){
        *media+=*vetor[*i];
    }
    *media/=*tamanho_vetor;
    free(i);
    free(media);
    return media;
}
double * desvioPadrao(double * vetor[],double * media,int*tamanho_vetor){
    double *variancia;
    int *i;
    variancia=malloc(sizeof(double));
    *i=malloc(sizeof(int));
    for(*i=0;*i<*tamanho_vetor;*i++){
        *variancia+=((*media-*vetor[*i])*(*media-*vetor[*i]));
    }
    *variancia=sqrt(*variancia);
    return variancia;
}
double * maximo(double * vetor[],int * tamanho_vetor){
    double *max;
    int *i;
    max=malloc(sizeof(double));
    i=malloc(sizeof(int));
    *max=0;
    for(*i=0;*i<*tamanho_vetor;*i++){
        if(*vetor[*i]>*max){
            *max=*vetor[*i];
        }
    }
    free(max);
    free(i);
    return max;
}
double * minimo(double * vetor[],int * tamanho_vetor){
    double *min;
    int *i;
    min=malloc(sizeof(double));
    i=malloc(sizeof(int));
    *min=*vetor[0];
    for(*i=1;*i<*tamanho_vetor;*i++){
        if(*vetor[*i]<*min){
            *min=*vetor[*i];
        }
    }
    return min;
}
int main(){
    char **nomes;
    int *n,*m;
    int *i;
    int *j;
    double **relevancia;
    double **atributos;
    i=malloc(sizeof(int));
    j=malloc(sizeof(int));
    n=malloc(sizeof(int));
    m=malloc(sizeof(int));
    scanf("%d%d",n,m);
    *relevancia=malloc(*n*sizeof(int*));
    *nomes=malloc(*n*sizeof(int*));
    *atributos=malloc(*n*sizeof(int*));
    for(*i=0;*i<*n;*i++){
        //gerando matrizes
        nomes[*i]=malloc(MAX*sizeof(char));
        relevancia[*i] = malloc(*m*sizeof(double));
        atributos[*i] = malloc(4*sizeof(double));
    }
    for(*i=0;*i<*n;*i++){
        scanf("%d",*nomes[*i]);
        for(*j=0;*j<*m;*j++){
            scanf("%lf",relevancia[*i][*j]);
        }
    }

    return 0;
}
