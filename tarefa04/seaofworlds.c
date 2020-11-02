#include <stdio.h>
#define MAX 21

int main(){
    int m, n, q;
    scanf("%i", &n);
    scanf("%i", &m);
    scanf("%i", &q);
    char texto[m][n];
    char palavras[q][MAX];
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            scanf(" %c", &texto[i][j]);
        }
    }
    for(int i = 0; i<q; i++){
        scanf("%s", palavras[i]);
    }
    for(int i = 0; i<q; i++){
        if(!conferir_inicial(n,m,texto, palavras[i])){
            printf("não");
            return 0;
        }
    }
    printf("sim");
    return 0;
}