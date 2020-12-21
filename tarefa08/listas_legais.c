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
//buscas para arvore
p_no achar_pai(p_no filho){
    if(filho == NULL) {
        return NULL;
    } else {
        return filho->pai;
    }
}

p_no achar_avo(p_no neto){
    return achar_pai(achar_pai(neto));
}

p_no achar_irmao(p_no irmao){
    p_no pai = achar_pai(irmao);
    if (pai == NULL) {
        return NULL;
    } else {
        if(irmao == pai->esquerdo){
            return pai->direito;
        } else {
            return pai->esquerdo;
        }
    }
}

p_no achar_tio(p_no sobrinho){
    return achar_irmao(achar_pai(sobrinho));
}
void rotacionar_direita(p_no no){
    p_no filho_esquerdo = no->esquerdo;
    p_no p = achar_pai(no);
    no->esquerdo = filho_esquerdo->direito;
    filho_esquerdo->direito = no;
    no->pai = filho_esquerdo;
    if (no->esquerdo != NULL) {
        no->esquerdo->pai = no;
    }
    if (p != NULL) {
        if (no == p->direito) {
            p->direito = filho_esquerdo;
        } else {
            p->esquerdo = filho_esquerdo;
        }
    }
    filho_esquerdo->pai = p;
}

void rotacionar_esquerda(p_no no){
    p_no filho_direito = no->direito;
    p_no pai = achar_pai(no);
    no->direito = filho_direito->esquerdo;
    filho_direito->esquerdo = no;
    no->pai = filho_direito;
    if (no->direito != NULL) {
        no->direito->pai = no;
    }
    if (pai != NULL) {
        if (no == pai->direito) {
            pai->direito = filho_direito;
        } else {
            pai->esquerdo = filho_direito;
        }
    }
    filho_direito->pai = pai;
}

p_no inserir_simples(p_no raiz, p_no novo_no){
    if (raiz == NULL){
        return novo_no;
    }
    p_no atual = raiz;
    while(atual != NULL){
        if (atual->valor > novo_no->valor){
            if(atual->esquerdo == NULL) {
                atual->esquerdo = novo_no;
                break;
            } else {
                atual = atual->esquerdo;
            }
        } else if (atual->valor < novo_no->valor) {
            if(atual->direito == NULL) {
                atual->direito = novo_no;
                break;
            } else {
                atual = atual->direito;
            }
        } else {
            atual->quantidade += 1;
            free(novo_no);
            return NULL;
        }
    }
    novo_no->pai = atual;
    return novo_no;
}

void consertar_arvore(p_no novo) {
    p_no pai = achar_pai(novo);
    p_no tio = achar_tio(novo);
    p_no avo = achar_avo(novo);
    if(pai == NULL){
        novo->cor = PRETA;
    } else if (pai->cor == VERMELHA) {
        if(tio != NULL && tio->cor == VERMELHA){
            pai->cor = PRETA;
            tio->cor = PRETA;
            avo->cor = PRETA;
            consertar_arvore(avo);
        } else {
            if (novo == pai->direito && pai == avo->esquerdo) {
                rotacionar_esquerda(pai);
                novo = novo->esquerdo;
            } else if (novo == pai->esquerdo && pai == avo->direito) {
                rotacionar_direita(pai);
                novo = novo->direito;

            }
            pai = achar_pai(novo);
            avo = achar_avo(novo);
            if (novo == pai->direito) {
                rotacionar_esquerda(avo);
            } else {
                rotacionar_direita(avo);
            }
            pai->cor = PRETA;
            avo->cor = VERMELHA;
        }
    }
}

p_no inserir(p_no raiz, long valor_novo) {
    p_no novo = criar_no(valor_novo);
    p_no nova_raiz = inserir_simples(raiz, novo);
    if (nova_raiz != NULL){
        raiz = nova_raiz;
        consertar_arvore(novo);
        while(raiz->pai != NULL){
            raiz = raiz->pai;
        }
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
    return 0;
}
