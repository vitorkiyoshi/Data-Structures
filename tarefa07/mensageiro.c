#include <stdio.h>
#include <stdlib.h>
typedef struct No {
    int chave;
    int verif;
    char texto[4];
    struct No *direita;
    struct No *esquerda;
} No;
typedef struct No *p_no;
p_no criarArvore(p_no raiz){
    raiz->texto=NULL;
    raiz->chave=NULL;
    raiz->esquerda=NULL;
    raiz->direita=NULL;
    raiz->verif=NULL;
    return raiz;
}
p_no buscar(p_no raiz,int chave){
    if(raiz==NULL || chave==raiz->chave){
        return raiz;
    }
    if(chave< raiz->chave){
        return buscar(raiz->esquerda,chave);
    }
    else{
        return buscar(raiz->direita,chave);
    }
}

p_no inserir(p_no raiz, int chave,char txt[4]){
    p_no novo;
    if(raiz == NULL){
        novo=malloc(sizeof(No));
        novo->esquerda=novo->direita==NULL;
        novo->chave = chave;
        novo->texto=txt;
        return novo;
    }
    if(chave < raiz->chave){
        raiz->esquerda= inserir(raiz->esquerda,chave);
    }
    else{
        raiz->direita= inserir(raiz->direita,chave);
    }
    return raiz;
}
p_no encontrarSoma(p_no arvore, int soma);
p_no concatenar(p_no arvore1, p_no arvore2){
    p_no concat=criarArvore(concat);
    while(arvore1->chave!=NULL){
        if(buscar(concat, arvore1->chave)){
            inserir(concat, arvore1->chave, arvore1->texto);
        }
        arvore1=arvore1->direita;
    }
    while(arvore2->chave!=NULL){
        if(buscar(concat, arvore2->chave)){
            inserir(concat, arvore2->chave, arvore2->texto);
        }
        arvore2=arvore2->direita;
    }
}
/*O que deve-se fazer:
 * busca binária, verificando soma dos numeros, e soma de algarismos
 * caso um dos dois não corresponda, deve testar proximo recursivamente
 * no final, algoritmo retorna o valor desejado via backtracking, podendo então
 * acessar os nós printando cada sala
 * -> Para mais de uma autoridade, concatenar saidas do encontrar soma, verificando*/
int main(){
    int n_cartoes,n_autoridades,i,chave,soma;
    char texto[4];
    p_no arvore;
    p_no arvore_concatenada;
    arvore=criarArvore(arvore);
    while(scanf("%i %i",&n_cartoes,&n_autoridades)!=EOF){
        for(i=0;i<n_cartoes;i++){
            scanf("%i %s",&chave,texto);
            inserir(arvore,chave,texto);
        }
        for(i=0;i<n_autoridades;i++) {
            scanf(" %i", soma);
            encontrarSoma(arvore,soma);
        }
        /*Após pegar as entradas da mensagem, botar elas na arvore
         * encontrar soma retorna por backtracking nossa soma desejada
         * se tiver mais de uma autoridade, concatenar*/
        if(n_autoridades>1){
            arvore_concatenada=concatenar()
        }
    }

    return 0;
}