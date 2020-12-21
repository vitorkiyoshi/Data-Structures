#include "arvore_binaria.h"
void destruir_arvore(p_no raiz){
    if(raiz == NULL){
        return;
    } else{
        destruir_arvore(raiz->esquerdo);
        destruir_arvore(raiz->direito);
        free(raiz->texto);
        free(raiz);
    }
}
p_no criar_no(int valor, char *texto) {
    p_no novo = malloc(sizeof(No));
    novo->esquerdo = novo->direito = novo->pai = NULL;
    novo->valor = valor;
    novo->texto = texto;
    novo->visitado = 0;
    return novo;
}

p_no inserir_no(p_no raiz, p_no novo_no) {
    if (raiz == NULL) {
        return novo_no;
    }
    p_no atual = raiz;
    while (atual != NULL) {
        if (atual->valor > novo_no->valor) {
            if (atual->esquerdo == NULL) {
                atual->esquerdo = novo_no;
                break;
            } else {
                atual = atual->esquerdo;
            }
        } else if (atual->valor < novo_no->valor) {
            if (atual->direito == NULL) {
                atual->direito = novo_no;
                break;
            } else {
                atual = atual->direito;
            }
        }
    }
    novo_no->pai = atual;
    return raiz;
}

p_no adicionar(p_no raiz, int valor, char *texto) {
    p_no novo = criar_no(valor, texto);
    return inserir_no(raiz, novo);
}

p_no buscar(p_no raiz, int valor) {
    p_no atual = raiz;
    while (atual != NULL) {
        if (atual->valor > valor) {
            atual = atual->esquerdo;
        } else if (atual->valor < valor) {
            atual = atual->direito;
        } else {
            return atual;
        }
    }
    return NULL;
}

p_no remover(p_no raiz, int valor) {
    if (raiz == NULL) {
        free(raiz->texto);
        free(raiz);
        return NULL;
    }
    else if(raiz->valor > valor) {
        raiz->esquerdo = remover(raiz->esquerdo, valor);
    }
    else if(raiz->valor < valor) {
        raiz->direito = remover(raiz->direito, valor);
    }
    else{
        if (raiz->esquerdo == NULL && raiz->direito == NULL) {
            p_no temp=raiz;
            free(temp->texto);
            free(temp);
            raiz = NULL;
        } else if(raiz->esquerdo == NULL) {
            p_no temp = raiz;
            raiz = raiz->direito;
            raiz->pai = temp->pai;
            free(temp->texto);
            free(temp);
        }
        else if(raiz->direito == NULL) {
            p_no temp = raiz;
            raiz = raiz->esquerdo;
            raiz->pai = temp->pai;
            free(temp->texto);
            free(temp);
        } else{
            p_no min = raiz->esquerdo;
            while (min->direito != NULL) {
                min = min->direito;
            }
            raiz->valor = min->valor;
            free(raiz->texto);
            raiz->texto = malloc(strlen(min->texto) + 1);
            strcpy(raiz->texto, min->texto);
            min->valor = valor;
            raiz->esquerdo = remover(raiz->esquerdo, valor);
        }
    }
    return raiz;
}
void print_arvore(p_no raiz){
    if(raiz == NULL) return;
    print_arvore(raiz->esquerdo);
    printf("%s", raiz->texto);
    print_arvore(raiz->direito);
}
p_no combinar(p_no *raiz, p_no a, p_no b){
    /*combinar toma um ponteiro, já que pode alterar a raiz da árvore, mas
    não pode retornar a nova raiz, já que precisa retornar o novo nó criado,
     para que a combinação possa ser finalizada.*/
    char *novo_texto = malloc(strlen(a->texto) + strlen(b->texto) + 1);
    strcpy(novo_texto, a->texto);
    strcat(novo_texto, b->texto);
    int novo_valor = a->valor + b->valor;
    *raiz = adicionar(*raiz,novo_valor, novo_texto);
    *raiz = remover(*raiz, a->valor);
    *raiz = remover(*raiz, b->valor);
    if(*raiz!=NULL) {
        p_no novo = buscar(*raiz, novo_valor);
        return novo;
    }
    else{
        return NULL;
    }
}

p_no achar_dupla(p_no raiz, p_no atual, int objetivo){
    if (atual == NULL) return NULL;
    p_no resultado;
    resultado = achar_dupla(raiz, atual->esquerdo, objetivo);
    if(resultado != NULL){
        return resultado;
    }
    if(atual->valor < objetivo) {
        if(atual->visitado == 0) {
            atual->visitado = 1;
            resultado = buscar(raiz, objetivo - atual->valor);
            if (resultado != NULL && resultado->visitado == 0) {
                atual->visitado = 0;
                return combinar(&raiz, atual, resultado);
            }
            atual->visitado = 0;
        }
        return achar_dupla(raiz, atual->direito, objetivo);
    }
    return NULL;
}

p_no achar_tripla(p_no raiz, p_no atual, int objetivo){
    if (atual == NULL) return 0;
    p_no resultado;
    resultado = achar_tripla(raiz, atual->esquerdo, objetivo);
    if(resultado != NULL) {
        return resultado;
    }
    if(atual->valor < objetivo -2){
        /*caso o valor atual for objetivo -2 ou maior, seriam necessários dois
        valores 1 para completar a trinca, dado que valores não podem ser repetir, isso é impossível
         e essa é a condição de parada */
        atual->visitado = 1;
        int valor_atual = atual->valor;
        resultado = achar_dupla(raiz, raiz, objetivo - atual->valor);
        if(resultado != NULL){
            atual->visitado = 0;
            combinar(&raiz, buscar(raiz, valor_atual), resultado);
            return raiz;
        }
        atual->visitado = 0;
        return achar_tripla(raiz, atual->direito, objetivo);
    }
    return NULL;
}
int main() {
    while(1){
        p_no arvore = NULL;
        int cartoes, oficiais;
        if(scanf("%i %i", &cartoes, &oficiais) == EOF) {
            break;
        }
        for(int i = 0;i<cartoes;i++){
            int chave;
            char ignorar;
            char *texto = malloc(6*sizeof(char));
            scanf("%i \"%[^\"]s", &chave, texto);
            arvore = adicionar(arvore, chave, texto);
            scanf("%c ", &ignorar);
        }
        for(int i = 0;i<oficiais;i++){
            int soma;
            scanf("%i", &soma);
            arvore = achar_tripla(arvore, arvore, soma);
        }
        print_arvore(arvore);
        printf("\n");
        destruir_arvore(arvore);
    }
    return 0;
}
