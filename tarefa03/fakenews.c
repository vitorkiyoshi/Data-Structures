#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000
double * media(double vetor[], int * tamanho_vetor){
    int *i;
    double *media;
    i=malloc(sizeof(int));
    media=malloc(sizeof(double));
    for(*i=0;*i<*tamanho_vetor;(*i)++){
        *media+=vetor[*i];
    }
    *media/=*tamanho_vetor;
    return media;
}
double * desvioPadrao(double vetor[],double * media,int * tamanho_vetor){
    double *variancia;
    int *i;
    i=malloc(sizeof(int));
    variancia=malloc(sizeof(double));
    for(*i=0;*i<*tamanho_vetor;(*i)++){
        *variancia+=(vetor[*i]-*media)*(vetor[*i]-*media);
    }
    *variancia/=*tamanho_vetor;
    *variancia=sqrt(*variancia);
    return variancia;
}
double * maximo(double vetor[],int * tamanho_vetor){
    double *max;
    int *i;
    max=malloc(sizeof(double));
    i=malloc(sizeof(int));
    *max=0;
    for(*i=0;*i<*tamanho_vetor;(*i)++){
        if(vetor[*i]>*max){
            *max=vetor[*i];
        }
    }
    free(max);
    free(i);
    return max;
}
double * minimo(double vetor[],int * tamanho_vetor){
    double *min;
    int *i;
    min=malloc(sizeof(double));
    i=malloc(sizeof(int));
    *min=vetor[0];
    for(*i=1;*i<*tamanho_vetor;(*i)++){
        if(vetor[*i]<*min){
            *min=vetor[*i];
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
    relevancia=malloc(*n*sizeof(int*));
    nomes=malloc(*n*sizeof(int*));
    atributos=malloc(*n*sizeof(int*));
    for(*i=0;*i<*n;(*i)++){
        //gerando matrizes
        nomes[*i]=malloc(MAX*sizeof(char));
        relevancia[*i] = malloc(*m*sizeof(double));
        atributos[*i] = malloc(4*sizeof(double));
    }
    for(*i=0;*i<*n;(*i)++){
        scanf("%s",nomes[*i]);
        for(*j=0;*j<*m;(*j)++){
            scanf("%lf",&relevancia[*i][*j]);
        }
        atributos[*i][0]= *maximo(relevancia[*i],n);
        atributos[*i][1]= *minimo(relevancia[*i],n);
        atributos[*i][2]= *media(relevancia[*i],n);
        atributos[*i][3]= *desvioPadrao(relevancia[*i],media(relevancia[*i],n),n);
    }
    //saida
    for(*i=0;*i<*n;(*i)++){
        printf("%s ",nomes[*i]);
        printf("%.2lf %.2lf %.2lf %.2lf\n",atributos[*i][0],atributos[*i][1],atributos[*i][2],atributos[*i][3]);
    }

    return 0;
}
