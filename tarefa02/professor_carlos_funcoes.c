#include <stdio.h>
#include "professor_carlos.h"
#define MAX 100
int tamanho_string(char string[]){
    for(int i=0;i<MAX;i++){
        if(string[i]=='\00'){
            return i;
        }
    }
}
int comparar_strings(char string1[],char string2[]){ 
    /*Compara para ver qual string lexicograficamente é maior, 1 para string1 em primeiro, -1 para string 2 em prim*/
    int x=tamanho_string(string1);
    int y=tamanho_string(string2);
    if(x>=y){
        for(int i=0;i<y;i++){
            if(string1[i]<string2[i]){
                return 1;
            }
            else if(string1[i]>string2[i]){
                return -1;
            }
        }
        if(x!=y){
            return -1;
        }
    }
    else{
        for(int i=0;i<x;i++){
            if(string1[i]<string2[i]){
                return 1;
            }
            else if(string1[i]>string2[i]){
                return -1;
            }
        }
        return 1;
    }
    return 0;
}
int substring(char string[],char substring[],int tam_substring){
    int x=tamanho_string(string);
    int i,j,igual=1;
    for(i=0;i<=(x-tam_substring);i++){
        for(j=0;j<tam_substring;j++){
            if(string[i+j]!=substring[j]){
                igual=0;
            }
        }
        if(igual==1){
            return 1;
        }
    }
    return 0;
}
void ordenarTurma(Turma t[],int qtde,int turma){
    int i,j;
    Aluno troca;
    for(i=qtde;i>0;i--){//para o sobrenome
        for(j=0;j<i;j++){
            if(comparar_strings(t[turma].alunos[j].sobrenome,t[turma].alunos[j+1].sobrenome)<0){
                troca=t[turma].alunos[j];
                t[turma].alunos[j]=t[turma].alunos[j+1];
                t[turma].alunos[j+1]=troca;
            }
        }
    }
    for(i=qtde;i>0;i--){//para o nome
        for(j=0;j<i;j++){
            if(comparar_strings(t[turma].alunos[j].nome,t[turma].alunos[j+1].nome)<0){
                troca=t[turma].alunos[j];
                t[turma].alunos[j]=t[turma].alunos[j+1];
                t[turma].alunos[j+1]=troca;
            }
        }
    }
}
Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j){
    ordenarTurma(t,t[j].qtd,j);
    Aluno novo;
    Data dataNovo=t[j].alunos[0].nascimento;
    int i=0;
    for(i=1;i<t[j].qtd;i++){
        Data data=t[j].alunos[i].nascimento;
        if(((data.ano*365)+(data.mes*30)+data.dia)>((dataNovo.ano*365)+(dataNovo.mes*30)+dataNovo.dia)){
            novo=t[j].alunos[i];
            dataNovo=t[j].alunos[i].nascimento;
        }
    }
    return novo;
}
Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas){

}
Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j){
    ordenarTurma(t,t[j].qtd,j);
        Aluno velho;
        Data dataVelho=t[j].alunos[0].nascimento;
        int i=0;
        for(i=1;i<t[j].qtd;i++){
            Data data=t[j].alunos[i].nascimento;
            if(((data.ano*365)+(data.mes*30)+data.dia)<((dataVelho.ano*365)+(dataVelho.mes*30)+dataVelho.dia)){
                velho=t[j].alunos[i];
                dataVelho=t[j].alunos[i].nascimento;
            }
        }
        return velho;
}
Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas){
    
}

int conta_substrings(Turma t[], int qtd_turmas, char *padrao){
    /*Achando tamanho da substring*/
    int numero=0;
    int tam_substring=tamanho_string(padrao);
    int ver;
    for(int i=0;i<qtd_turmas;i++){
        for(int j=0;j<t[i].qtd;j++){
            ver=substring(t[i].alunos[j].nome,padrao,tam_substring);
            if(ver==1){
                numero+=1;
            }
        }
    }
    return numero;
}
int add_aluno(Turma t[], Aluno A, int j){
    t[j].alunos[t[j].qtd]=A;
    t[j].qtd+=1;
    return t[j].qtd;
}
int remove_aluno(Turma t[], int j){
    t[j].qtd-=1;
    return t[j].qtd;
}