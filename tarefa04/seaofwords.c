#include <stdio.h>
#include <stdlib.h>

#define MAX 21

int conferir(int n, int m, char** texto, int** aux, char* palavra, int posicaoletra, int x, int y){
    aux[y][x] = 1;
    if(texto[y][x] == palavra[posicaoletra]){
        if (palavra[posicaoletra+1] == '\00'){
            return 1;
        }
        if(y-1 > -1 && !aux[y-1][x]){
            if(conferir(n,m,texto,aux,palavra,posicaoletra+1, x, y-1)) return 1;
        }
        if(y+1 < n && !aux[y+1][x]){
            if(conferir(n,m,texto,aux,palavra,posicaoletra+1, x, y+1)) return 1;
        }
        if(x-1 > -1 && !aux[y][x-1]){
            if(conferir(n,m,texto,aux,palavra,posicaoletra+1, x-1, y)) return 1;
        }
        if(x+1 < m && !aux[y][x+1]){
            if(conferir(n,m,texto,aux,palavra,posicaoletra+1, x+1, y)) return 1;
        }
    }
    aux[y][x] = 0;
    return 0;
}

int conferir_inicial(int n, int m, char** texto, char* palavra){
    int **aux = malloc(sizeof(int*) * n);
    for(int i = 0; i<m; i++){
        aux[i] = malloc(sizeof(int) * m);
        for(int j = 0; j<n; j++){
            aux[i][j] = 0;
        }
    }
    for(int i = 0; i<n; i++) {
        for (int j = 0; j < m; j++) {
            if(texto[i][j] == palavra[0]) {
                if (conferir(n, m, texto, aux, palavra, 0, j, i)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main(){
    int m, n, q;
    scanf("%i", &n);
    scanf("%i", &m);
    scanf("%i", &q);
    char **texto = malloc(n*sizeof(char*));
    char **palavras = malloc(q*sizeof(char*));
    for(int i = 0; i<n; i++){
        texto[i] = malloc(sizeof(char) * m);
        for(int j = 0; j<m; j++){
            scanf(" %c", &texto[i][j]);
        }
    }
    for(int i = 0; i<q; i++){
        palavras[i] = malloc(sizeof(char) * MAX);
        scanf("%s", palavras[i]);
    }
    for(int i = 0; i<q; i++){
        if(!conferir_inicial(n,m,texto, palavras[i])){
            if(i>0){
                printf("\nnao");
            }
            else{
                printf("nao");
            }
        }
        else{
            if(i>0){
                printf("\nsim");
            }
            else{
                printf("sim");
            }
        }
    }
    return 0;
}