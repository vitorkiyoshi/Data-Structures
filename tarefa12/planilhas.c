#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "planilha.h"
#define MAX_CELULA 7
#define MAX_CAMINHO 30
#define MAX_STRING 1000
int main(){
    /*fscanf pegar valor com virgulas da célula, realizar as operações verificando ciclicidade
     * alterar primeiramente a matriz de celulas local, após,
     * printar saída de arquivo com supostos erros*/
    int linhas,colunas;
    char caminho[MAX_CAMINHO];//registra caminho do csv
    char *celula;//manipulação da string
    char string[MAX_STRING];//pegar a linha do csv
    p_celula **celulas;
    scanf("%s %i %i",caminho,&colunas,&linhas);
    celulas=malloc(linhas*sizeof(p_celula**));
    for(int i=0;i<linhas;i++){
        celulas[i]=malloc(colunas*sizeof(p_celula*));
        for(int j=0;j<colunas;j++){
            celulas[i][j] = malloc(sizeof(Celula));
        }
    }
    FILE *arquivo;
    arquivo=fopen(caminho,"r");//leitura para popular dados locais
    char c;
    for(int j=0;j<linhas;j++){
        fscanf(arquivo,"%[^\n]%c",string, &c);
        celula=strtok(string,",");
        if(verificarConstante(celula)) {
            celulas[j][0]->expressao=NULL;
            celulas[j][0]->calculado=1;
            celulas[j][0]->valor=atoi(celula);
        }
        else{
            celulas[j][0]->expressao=tokenizar(celula);
            celulas[j][0]->calculado=0;//nn setar valor para setar depois
        }
        for(int i=1;i<colunas;i++){
            celula=strtok(NULL,",");//acessar os outros valores
            if(verificarConstante(celula)) {
                celulas[j][i]->expressao=NULL;
                celulas[j][i]->calculado=1;
                celulas[j][i]->valor=atoi(celula);
            }
            else{
                celulas[j][i]->expressao=tokenizar(celula);
                celulas[j][i]->calculado=0;
            }
        }
    }
    fclose(arquivo);
    /*agora, realizar as tarefas que o código nos manda*/
    int pos_linha,pos_coluna,novo_valor;
    char operacao;//char de entrada
    char destino[MAX_CELULA];
    while(scanf("%c", &operacao)!=EOF){
        if(operacao=='G'){
            scanf("%s",destino);
            pos_coluna=(int) destino[0] -65; //65 devido tabela ASCII do caractere'A'
            pos_linha=atoi(destino+1)-1;//coluna
            char **dependencias = malloc(sizeof(char *) * linhas * colunas);
            dependencias[0] = destino;
            if(celulas[pos_linha][pos_coluna]->calculado==0){
                char *resultado = resolver_expressao(celulas,celulas[pos_linha][pos_coluna]->expressao,dependencias,1);
                printf("%s: %s\n", destino, resultado);
                if(resultado[0]!='#') {
                    celulas[pos_linha][pos_coluna]->valor = atoi(resultado);
                    celulas[pos_linha][pos_coluna]->calculado = 1;
                }
                free(resultado);
            }
            else{
                printf("%s: %i\n", destino, celulas[pos_linha][pos_coluna]->valor);
            }
            free(dependencias);
        }
        else if (operacao=='S'){
            scanf("%s %i ",destino,&novo_valor);
            pos_coluna=(int) destino[0] -65;
            pos_linha=atoi(destino+1)-1;
            printf("%s: %i -> %i\n",destino,celulas[pos_linha][pos_coluna]->valor,novo_valor);
            celulas[pos_linha][pos_coluna]->valor = novo_valor;
            celulas[pos_linha][pos_coluna]->expressao=NULL;
            celulas[pos_linha][pos_coluna]->calculado=1;
        }
        for(int j=0;j<linhas;j++){
            for(int i=0;i<colunas;i++){
                if(celulas[j][i]->expressao != NULL){
                    celulas[j][i]->calculado = 0;
                }
            }
        }
    }
    //no final, reescrever csv modificado
    //escreverArquivo(colunas,linhas,celulas,caminho);
    //free para celulas
    for(int i=0;i<linhas;i++){
        for(int j=0;j<colunas;j++){
            if(celulas[i][j]->expressao!=NULL) {
                for(int k = 0;celulas[i][j]->expressao[k] != NULL; k++){
                    free(celulas[i][j]->expressao[k]);
                }
                free(celulas[i][j]->expressao);
            }
            free(celulas[i][j]);
        }
        free(celulas[i]);
    }
    free(celulas);
    return 0;
}