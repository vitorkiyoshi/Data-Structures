#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*Estrutura do no para uso de HASH*/
typedef struct no {
    struct no* proximo;
    char* texto;
} No;
typedef No* p_no;
typedef enum classificacao {
    VERDE, VERMELHO, AMARELO
} Classificacao;
p_no adicionar_lista(p_no raiz, char *palavra){
    p_no novo = malloc(sizeof(No));
    novo->proximo = raiz;
    novo->texto = palavra;
    return novo;
}
int encontrar_hash(char *palavra, int tamanho){//função hash para busca
    long hash = palavra[0];
    int tamanho_string = strlen(palavra);
    for(int i = 1 ; i<tamanho_string;i++){
        hash *= tamanho;
        hash += palavra[i];
    }
    hash %= tamanho;
    return hash>=0?hash:-hash;
}
void destruir_lista(p_no lista){
    if(lista != NULL){
        destruir_lista(lista->proximo);
        free(lista->texto);
        free(lista);
    }
}
void adicionar(char *palavra, p_no *hash_list, int tamanho){
    int hash = encontrar_hash(palavra, tamanho);
    hash_list[hash] = adicionar_lista(hash_list[hash], palavra);
}
//checa possíveis erros com a lista de palavras, verificando tamanho e após os caracteres
Classificacao checar_palavra(char *p1, char *p2){//checagem preliminar
}
Classificacao checar_dicionario(char* palavra, p_no *hash_list, int tamanho){
}
int main(){
}