#include <stdio.h>
#include "professor_carlos.h"
#define MAX 100
int tamanho_string(char string[]){//tamanho das strings
    int i;
    for(i=0;i<MAX;i++){
        if(string[i]=='\00'){
            return i;
        }
    }
    return 0;
}

int comparar_strings(char string1[],char string2[]){ 
    /*Compara para ver qual string lexicograficamente é maior, 1 para string1 em primeiro, -1 para string 2 em prim*/
    int x=tamanho_string(string1);
    int y=tamanho_string(string2);
    if(x>=y){
        for(int i=0;i<y;i++){
            if(string1[i]<string2[i]){
                return -1;
            }
            else if(string1[i]>string2[i]){
                return 1;
            }
        }
        if(x!=y){
            return 1;
        }
    }
    else{
        for(int i=0;i<x;i++){
            if(string1[i]<string2[i]){
                return -1;
            }
            else if(string1[i]>string2[i]){
                return 1;
            }
        }
        return -1;
    }
    return 0;
}


void ordenarTurma(Turma t[],int qtde,int turma){
    int i,j;
    Aluno troca;
    for(i=qtde;i>0;i--){
        for(j=0;j<i-1;j++){
            if(comparar_strings(t[turma].alunos[j].sobrenome,t[turma].alunos[j+1].sobrenome)>0){
                troca=t[turma].alunos[j+1];
                t[turma].alunos[j+1]=t[turma].alunos[j];
                t[turma].alunos[j]=troca;
            }
        }
    }
    for(i=qtde;i>0;i--){
        for(j=0;j<i-1;j++){
            if(comparar_strings(t[turma].alunos[j].nome,t[turma].alunos[j+1].nome)>0){
                troca=t[turma].alunos[j+1];
                t[turma].alunos[j+1]=t[turma].alunos[j];
                t[turma].alunos[j]=troca;
            }
        }
    }
}

Aluno procura_novo_na_turma(Turma t[], int qtd_turmas, int j){
    ordenarTurma(t,t[j].qtd,j);
    Aluno novo=t[j].alunos[0];
    Data dataNovo=t[j].alunos[0].nascimento;
    int i=0;
    for(i=1;i<t[j].qtd;i++){
        Data data=t[j].alunos[i].nascimento;
        if((data.ano>dataNovo.ano)||((data.ano==dataNovo.ano)&&(data.mes>dataNovo.mes))||((data.ano==dataNovo.ano)&&(data.mes==dataNovo.mes)&&(data.dia>dataNovo.dia))){
            novo=t[j].alunos[i];
            dataNovo=t[j].alunos[i].nascimento;
        }
    }
    return novo;
}

Aluno procura_novo_todas_turmas(Turma t[], int qtd_turmas){
    Aluno maisNovo;
    Turma novos[1];
    novos[0].qtd=qtd_turmas;
    int i=0;
    for(i=0;i<qtd_turmas;i++){
        novos[0].alunos[i]= procura_novo_na_turma(t,0,i);
    }
    maisNovo=procura_novo_na_turma(novos,0,0);
    return maisNovo;
}

Aluno procura_velho_na_turma(Turma t[], int qtd_turmas, int j){
    ordenarTurma(t,t[j].qtd,j);
    Aluno velho=t[j].alunos[0];
    Data dataVelho=t[j].alunos[0].nascimento;
    int i=0;
    for(i=1;i<t[j].qtd;i++){
        Data data=t[j].alunos[i].nascimento;
         if((data.ano<dataVelho.ano)||((data.ano==dataVelho.ano)&&(data.mes<dataVelho.mes))||((data.ano==dataVelho.ano)&&(data.mes==dataVelho.mes)&&(data.dia<dataVelho.dia))){
            velho=t[j].alunos[i];
            dataVelho=t[j].alunos[i].nascimento;
        }
    }
    return velho;
}

Aluno procura_velho_todas_turmas(Turma t[], int qtd_turmas){
    Aluno maisVelho;
    Turma velhos[1];
    velhos[0].qtd=qtd_turmas;
    int i;
    for(i=0;i<qtd_turmas;i++){
        velhos[0].alunos[i]= procura_velho_na_turma(t,0,i);
    }
    maisVelho=procura_velho_na_turma(velhos,0,0);
    return maisVelho;
}
int substring(char string[],char substring[],int tam_substring){
    int pos_substring=0;
    int pos_string=0;
    int i=tamanho_string(string);
    for(int j=0;j<i;j++){
        if(pos_substring==tam_substring){
            return 1;
        }
        if(string[pos_string]==substring[pos_substring]){
            pos_substring+=1;
        }
        else{
            pos_substring=0;
        }
        pos_string+=1;
    }
    if(string[pos_string]==substring[pos_substring]){
        if(pos_substring==tam_substring){
            return 1;
        }
    }
    return 0;
    
}
int conta_substrings(Turma t[], int qtd_turmas, char *padrao){
    /*Achando tamanho da substring*/
    int numero=0;
    int tam_substring=tamanho_string(padrao);
    for(int i=0;i<qtd_turmas;i++){
        for(int j=0;j<t[i].qtd;j++){
            if(substring(t[i].alunos[j].nome,padrao,tam_substring)==1){
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