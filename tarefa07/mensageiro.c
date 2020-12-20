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
        novo->verif=0;
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
p_no remover_rec(p_no raiz, int chave){
    if(raiz == NULL){
        return NULL;
    }
    if(chave<raiz->chave){
        raiz->esquerda=remover_rec(raiz->esquerda,chave);
    }
    else if(chave>raiz->chave){
        raiz->direita=remover_rec(raiz->direita,chave);
    }
    else if(raiz->esquerda==NULL){
        return raiz->dir;
    }
    else if(raiz->direita==NULL){
        return raiz->esquerda;
    }
    else{
        remover_sucessor(raiz);
    }
    return raiz;
}
void remover_sucessor(p_no raiz){
    p_no min=raiz->direita;
    p_no pai=raiz;
    while(min->esquerda !=NULL){
        pai=min;
        min=min->esquerda;
    }
    if(pai->esquerda==min){
        pai->esquerda=min->direita;
    }
    else{
        pai->direita=min->direita;
    }
    raiz->chave=min->chave;
}
p_no achar_dupla(p_no raiz, p_no atual, int objetivo){
    if (atual == NULL) return NULL;
    p_no resultado;
    if((resultado = achar_dupla(raiz, atual->direita, objetivo))){
        return resultado;
    }
    if(atual->valor < objetivo){
        if(atual->visitado == 0) {
            atual->visitado = 1;
            p_no resultado = buscar_iterativo(raiz, objetivo - atual->valor);
            if (resultado != NULL || resultado->visitado == 0) {
                return combinar(raiz, atual, resultado);
            }
            atual->visitado = 0;
        }
        return (achar_dupla(raiz, atual->esquerda, objetivo));
    }
}

p_no achar_tripla(p_no raiz, p_no atual, int objetivo){
    if (atual == NULL) return 0;
    p_no resultado;
    if(resultado = achar_tripla(raiz, atual->direita, objetivo)) {
        return resultado;
    }
    if(atual->valor < objetivo -2){
        atual->visitado = 1;
        if(resultado = achar_dupla(raiz, raiz, objetivo - atual->valor)){
            return combinar(raiz, atual, resultado);
        }
        atual->visitado = 0;
        return achar_tripla(raiz, atual->esquerda, objetivo);
    }
}
p_no combinar(p_no raiz, p_no a, p_no b){
    char *novo_texto = malloc(strlen(a->texto) + strlen(b->texto) + 1);
    strcpy(novo_texto, a->texto);
    strcat(novo_texto, b->texto);
    p_no novo = adicionar_no(raiz,a->valor + b->valor, novo_texto);
    remover_rec(raiz, a->valor);
    remover_rec(raiz, b->valor);
    destruir_no(a);
    destruir_no(b);
    return novo;
}
p_no destruirArvore(p_no arvore){

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
    p_no arvore_somas;
    p_no arvore_concatenada;
    arvore=criarArvore(arvore);
    arvore_somas=criarArvore(arvore_somas);
    while(scanf("%i %i",&n_cartoes,&n_autoridades)!=EOF){
        for(i=0;i<n_cartoes;i++){
            scanf("%i %s",&chave,texto);
            inserir(arvore,chave,texto);
        }
        for(i=0;i<n_autoridades;i++) {
            scanf(" %i", soma);

        }
        /*Após pegar as entradas da mensagem, botar elas na arvore
         * encontrar soma retorna por backtracking nossa soma desejada
         * se tiver mais de uma autoridade, concatenar*/
        if(n_autoridades>1){

        }
        else{

        }
    }


    return 0;
}