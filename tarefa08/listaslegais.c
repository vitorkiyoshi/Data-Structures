#include <stdio.h>
#include <stdlib.h>
#include "Arvore_RN.h"
//Funções de interação para criação de Nós
p_no criar_no(long valor){
    p_no novo = malloc(sizeof(No));
    novo->esquerdo = novo->direito = novo->pai = NULL;
    novo->valor = valor;
    novo->quantidade = 1;
    novo->cor = VERMELHA;
    return novo;
}

p_no rotacionar_esquerda(p_no no){
    p_no x=no->direito;
    no->direito=x->esquerdo;
    x->esquerdo=no;
    x->cor=no->cor;
    no->cor=VERMELHA;
    return x;
}

p_no rotacionar_direita(p_no no){
    p_no x=no->esquerdo;
    no->esquerdo=x->direito;
    x->direito=no;
    x->cor=no->cor;
    no->cor=VERMELHA;
    return x;
}
int ehVermelho(p_no x){
    if(x==NULL){
        return 0;
    }
    return x->cor==VERMELHA;
}
int ehPreto(p_no x){
    if(x==NULL){
        return 1;
    }
    return x->cor==PRETA;
}

void sobeVermelho(p_no raiz){
    raiz->cor= VERMELHA;
    raiz->esquerdo->cor= PRETA;
    raiz->direito->cor= PRETA;
}

p_no inserir(p_no raiz, long valor_novo) {
    p_no novo;
    if(raiz==NULL){
        novo=criar_no(valor_novo);
        return novo;
    }
    if(valor_novo<raiz->valor){
        raiz->esquerdo=inserir(raiz->esquerdo,valor_novo);
    }
    else if(valor_novo>raiz->valor){
        raiz->direito=inserir(raiz->direito,valor_novo);
    } else {
        raiz->quantidade += 1;
        return raiz;
    }
    if(ehVermelho(raiz->direito)&& ehPreto(raiz->esquerdo)){
        raiz = rotacionar_esquerda(raiz);
    }
    if(ehVermelho(raiz->esquerdo) && ehVermelho(raiz->esquerdo->esquerdo)){
        raiz = rotacionar_direita(raiz);
    }
    if(ehVermelho(raiz->esquerdo) && ehVermelho(raiz->direito)){
        sobeVermelho(raiz);
    }
    return raiz;
}

p_no buscar(p_no raiz, long valor) {
    p_no atual = raiz;
    while (atual != NULL){
        if(atual->valor > valor){
            atual = atual->esquerdo;
        } else if (atual->valor < valor) {
            atual = atual->direito;
        } else {
            return atual;
        }
    }
    return NULL;
}

int contar_ocorrencias(p_no raiz, long valor) {
    p_no no_valor = buscar(raiz, valor);
    if(no_valor == NULL){
        return 0;
    } else {
        return no_valor->quantidade;
    }
}

int descobrir_minimo_remocao(p_no atual, int parcial) {
    if(atual == NULL){
        return parcial;
    }
    parcial = descobrir_minimo_remocao(atual->esquerdo, parcial);
    parcial = descobrir_minimo_remocao(atual->direito, parcial);
    if(atual->valor > atual->quantidade){
        parcial += atual->quantidade;
    } else {
        parcial += atual->quantidade - atual->valor;
    }
    return parcial;
}
void destruir_arvore(p_no raiz){
    if(raiz == NULL){
        return;
    } else{
        destruir_arvore(raiz->esquerdo);
        destruir_arvore(raiz->direito);
        free(raiz);
    }
}
/*Deve adicionar as operações, e utilizar as funções de implementação*/
int main() {
    p_no arvore = NULL;
    int iniciais, operacoes;
    long adicionar;
    scanf("%d %d", &iniciais, &operacoes);
    for(int i=0;i<iniciais;i++){
        scanf("%ld", &adicionar);
        arvore = inserir(arvore, adicionar);
    }
    for(int i=0;i<operacoes;i++) {
        int operacao;
        scanf("%i", &operacao);
        long contar;
        switch(operacao){
            case 1:
                scanf("%ld", &adicionar);
                arvore = inserir(arvore, adicionar);
                break;
            case 2:
                scanf("%ld", &contar);
                printf("%i\n", contar_ocorrencias(arvore, contar));
                break;
            case 3:
                printf("%i\n", descobrir_minimo_remocao(arvore, 0));
                break;
        }
    }
    destruir_arvore(arvore);
    return 0;
}
