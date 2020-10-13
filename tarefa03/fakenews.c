#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 1000
double * media(double vetor[], int tamanho_vetor){
    int *i;
    double *media;
    i=malloc(sizeof(int));
    media=malloc(sizeof(double));
    *media=0;
    *i=0;
    for(*i=0;*i<tamanho_vetor;(*i)++){
        *media+=vetor[*i];
    }
    *media/=tamanho_vetor;
    free(i);
    return media;
}
double * desvioPadrao(double vetor[],double * media,int tamanho_vetor){
    double *variancia;
    int *i;
    i=malloc(sizeof(int));
    variancia=malloc(sizeof(double));
    *variancia=0;
    *i=0;
    for(*i=0;*i<tamanho_vetor;(*i)++){
        *variancia+=(vetor[*i]-*media)*(vetor[*i]-*media);
    }
    *variancia/=tamanho_vetor;
    *variancia=sqrt(*variancia);
    free(i);
    return variancia;
}
double * maximo(double vetor[],int tamanho_vetor){
    double *max;
    int *i;
    max=malloc(sizeof(double));
    i=malloc(sizeof(int));
    *i=0;
    *max=0;
    for(*i=0;*i<tamanho_vetor;(*i)++){
        if(vetor[*i]>*max){
            *max=vetor[*i];
        }
    }
    free(i);
    return max;
}
double * minimo(double vetor[],int tamanho_vetor){
    double *min;
    int *i;
    min=malloc(sizeof(double));
    i=malloc(sizeof(int));
    *i=0;
    *min=vetor[0];
    for(*i=1;*i<tamanho_vetor;(*i)++){
        if(vetor[*i]<*min){
            *min=vetor[*i];
        }
    }
    free(i);
    return min;
}
int main(){
    char **nomes;
    int *n,*m,*i,*j,*qtde,*selecionados;
    double **relevancia;
    double **atributos;
    i=malloc(sizeof(int));
    j=malloc(sizeof(int));
    qtde=malloc(sizeof(int));
    n=malloc(sizeof(int));
    m=malloc(sizeof(int));
    scanf("%d %d",n,m);
    selecionados=malloc(*n*sizeof(int));
    relevancia=malloc(*n*sizeof(int*));
    nomes=malloc(*n*sizeof(int*));
    atributos=malloc(*n*sizeof(int*));
    *i=0;
    *j=0;
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
        atributos[*i][0]= *maximo(relevancia[*i],*m);
        atributos[*i][1]= *minimo(relevancia[*i],*m);
        atributos[*i][2]= *media(relevancia[*i],*m);
        atributos[*i][3]= *desvioPadrao(relevancia[*i],&atributos[*i][2],*m);
    }
    //saida
    for(*i=0;*i<*n;(*i)++){
        printf("%s ",nomes[*i]);            //0- maximo  1-minimo  2-media  3-desvio padrao
        printf("%.2lf %.2lf %.2lf %.2lf\n",atributos[*i][0],atributos[*i][1],atributos[*i][2],atributos[*i][3]);
    }
    //verificando bots
    printf("\nRESULTADO:\n");
    *qtde=0;
    for(*i=0;*i<5;(*i)++){
        *qtde=0;
        for(*j=0;*j<*n;(*j)++){
            if(*i==0){
                if((atributos[*j][2]>=60.00)&&(atributos[*j][3]>15.00)){
                    selecionados[*qtde]=*j;
                    *qtde+=1;
                }
            }
            if(*i==1){
                if((atributos[*j][2]>=60.00)&&(atributos[*j][3]<=15.00)){
                    selecionados[*qtde]=*j;
                    *qtde+=1;
                }
            }
            if(*i==2){
                if((atributos[*j][2]<60.00)&&(atributos[*j][0]>=80.00)&&(atributos[*j][1]>20.00)){
                    selecionados[*qtde]=*j;
                    *qtde+=1;
                }
            }
            if(*i==3){
                if((atributos[*j][2]<60.00)&&(atributos[*j][0]>=80.00)&&(atributos[*j][1]<=20.00)){
                    selecionados[*qtde]=*j;
                    *qtde+=1;
                }
            }
            if(*i==4){
                if((atributos[*j][2]<60.00)&&(atributos[*j][0]<80.00)){
                    selecionados[*qtde]=*j;
                    *qtde+=1;
                }
            }
        }
        if(*i==0){
            printf("Bot (%d):",*qtde);
            for(*j=0;*j<*qtde;(*j)++){
                printf(" %s",nomes[selecionados[*j]]);
            }
        }
        if(*i==1){
            printf("\nSurpreendente (%d):",*qtde);
            for(*j=0;*j<*qtde;(*j)++){
                printf(" %s",nomes[selecionados[*j]]);
            }
        }
        if(*i==2){
            printf("\nNormal (%d):",*qtde);
            for(*j=0;*j<*qtde;(*j)++){
                printf(" %s",nomes[selecionados[*j]]);
            }
        }
        if(*i==3){
            printf("\nLocal (%d):",*qtde);
            for(*j=0;*j<*qtde;(*j)++){
                printf(" %s",nomes[selecionados[*j]]);
            }
        }
        if(*i==4){
            printf("\nIrrelevante (%d):",*qtde);
            for(*j=0;*j<*qtde;(*j)++){
                printf(" %s",nomes[selecionados[*j]]);
            }
        }
    }
    free(qtde);
    for(*i=0;*i<*n;(*i)++){
        free(nomes[*i]);
        free(atributos[*i]);
        free(relevancia[*i]);
    }
    free(nomes);
    free(atributos);
    free(relevancia);
    free(selecionados);
    free(n);
    free(m);
    free(i);
    free(j);
    return 0;
}
