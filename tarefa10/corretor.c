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
    int tamanho_a = strlen(p1);
    int tamanho_b = strlen(p2);
    int limite = tamanho_a>tamanho_b?tamanho_a:tamanho_b;
    int diff = tamanho_a-tamanho_b;
    int erro = 0;
    if (diff>1 || diff<-1){
        return VERMELHO;
    }
    for(int i=0;i<limite;i++){
        char a = i<tamanho_a?p1[i]:'\0';
        char b = i<tamanho_b?p2[i]:'\0';
        if(a != b){
            if(i+1<limite && (diff == -1 || diff == 1) && !erro){//verificação de limites de caracteres
                erro = 1;
                if (diff == -1 && a == p2[i+1]) {
                    p2++;
                    continue;
                } else if (diff == 1 && b == p1[i+1]){
                    p1++;
                    continue;
                }
            }
            if(erro) {
                return VERMELHO;
            } else {
                erro = 1;
            }
        }
    }
    if(erro){
        return AMARELO;
    } else {
        return VERDE;
    }
}
Classificacao checar_dicionario(char* palavra, p_no *hash_list, int tamanho){//checagem de caracteres em relação a palavra original
    int hash = encontrar_hash(palavra, tamanho);//*checar de conflito
    p_no palavra_atual = hash_list[hash];
    Classificacao estado = VERMELHO;
    while(palavra_atual != NULL){
        Classificacao comparar_atual = checar_palavra(palavra, palavra_atual->texto);
        if(comparar_atual == VERDE){
            return VERDE;
        } else if(comparar_atual == AMARELO){
            estado = AMARELO;
        }
        palavra_atual = palavra_atual->proximo;
    }
    if(estado == AMARELO){
        return AMARELO;
    } else {//verifica após se ainda tem desconto de limite de caracteres
        for(int i = 0;i<tamanho;i++){
            if (i==hash) continue;
            palavra_atual = hash_list[i];
            while(palavra_atual != NULL){
                Classificacao comparar_atual = checar_palavra(palavra, palavra_atual->texto);
                if(comparar_atual == VERDE){
                    return VERDE;
                } else if(comparar_atual == AMARELO){
                    return AMARELO;
                }
                palavra_atual = palavra_atual->proximo;
            }
        }
    }
    return VERMELHO;
}
int main(){
    /*pegar ints de dicionario, e depois as palavras a serem verificadas*/
    int tamanho, quantidade_testes;
    scanf("%i %i", &tamanho, &quantidade_testes);
    p_no *hash_list = malloc(sizeof(p_no) * tamanho);
    //criar lista hash
    for(int i = 0; i<tamanho; i++){
        hash_list[i] = NULL;
    }
    for(int i = 0; i<tamanho; i++){
        char *palavra = malloc(sizeof(char) * 26);
        scanf("%s", palavra);
        adicionar(palavra, hash_list, tamanho);
    }
    //apos armazenar palavras, comparar
    for(int i = 0; i<quantidade_testes; i++){
        char *palavra = malloc(sizeof(char)*25);
        scanf("%s", palavra);
        Classificacao classificacao_palavra = checar_dicionario(palavra, hash_list, tamanho);
        switch (classificacao_palavra) {//basta printar os resultados
            case VERDE:
                printf("verde\n");
                break;
            case AMARELO:
                printf("amarelo\n");
                break;
            case VERMELHO:
                printf("vermelho\n");
                break;
        }
        free(palavra);
    }
    for(int i = 0; i<tamanho; i++){
        destruir_lista(hash_list[i]);
    }
    free(hash_list);
}