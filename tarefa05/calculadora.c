#include <stdio.h>
#include <stdlib.h>
typedef struct No{
    int dado;
    struct No *prox;
    struct No *ant;
} No;
typedef struct No *p_no;
p_no criar_lista(){
    return NULL;
}
void destruir_lista(p_no lista){
    if(lista!=NULL){
        destruir_lista(lista->prox);
        free(lista);
    }
}
p_no add(p_no lista, int numero){
    p_no novo = malloc(sizeof(No));
    novo->prox = novo->ant = NULL;
    novo->dado = numero;
    if(lista) {
        novo->prox = lista;
        lista->ant = novo;
    }
    return novo;
}
p_no add_inverso(p_no lista, int numero){
    p_no novo = malloc(sizeof(No));
    novo->prox = novo->ant = NULL;
    novo->dado = numero;
    p_no primeiro = novo;
    if(lista) {
        primeiro = lista;
        while (lista->prox) lista = lista->prox;
        lista->prox = novo;
        novo->ant = lista;
    }
    return primeiro;
}

void imprimir_lista(p_no lista){
    if(lista!=NULL){
        while(lista->prox){
            lista = lista->prox;
        }
        while(lista && lista->dado == 0) lista = lista->ant;
        if (lista == NULL){
            printf("0");
        }
        while(lista){
            printf("%i", lista->dado);
            lista = lista->ant;
        }
    }
    printf("\n");
}
p_no somar(p_no a,p_no b){
    int carry = 0;
    p_no resultado = criar_lista();
    while(a || b){
        int soma_digitos = (a?a->dado:0) + (b?b->dado:0) + carry;
        resultado = add_inverso(resultado, soma_digitos%10);
        carry = (soma_digitos>=10?1:0);
        if(a) a=a->prox;
        if(b) b=b->prox;
    }
    if(carry){
        resultado = add_inverso(resultado, 1);
    }
    return resultado;
}

p_no subtrair(p_no a, p_no b) {
    p_no a_orig = a, b_orig = b;
    int carry = 0;
    p_no resultado = criar_lista();
    while(a || b){
        int subtracao_digitos = (a?a->dado:0) - (b?b->dado:0) + carry;
        carry = (subtracao_digitos >= 0)? 0 : -1;
        resultado = add_inverso(resultado, subtracao_digitos-10*carry);
        if (a) a=a->prox;
        if (b) b=b->prox;
    }
    if (carry){
        destruir_lista(resultado);
        resultado = subtrair(b_orig, a_orig);
    }
    return resultado;
}

p_no multiplicar_simples(p_no a, int b){
    p_no resultado = criar_lista();
    int carry = 0;
    while(a){
        int mult_digito = a->dado * b + carry;
        resultado = add_inverso(resultado, mult_digito%10);
        carry = mult_digito/10;
        a = a->prox;
    }
    if(carry){
        add_inverso(resultado, carry);
    }
    return resultado;
}
p_no multiplicar(p_no a, p_no b){
    /*ir até a casa da unidade, ir somando cada um*/
    p_no resultado = criar_lista();
    while(b->prox) b=b->prox;
    while(b){
        p_no parcial = multiplicar_simples(a, b->dado);
        resultado = add(resultado, 0);
        p_no anterior = resultado;
        resultado = somar(parcial, resultado);
        b = b->ant;
        destruir_lista(parcial);
        destruir_lista(anterior);
    }
    return resultado;
}
p_no ler_lista(p_no lista){
    char c;
    while (scanf("%c", &c) == 1 && ('0'<=c && c<='9')){
        lista = add(lista, c - '0');
    }
    return lista;
}
int main(){
    /*Scannear numero de operações a serem feitas;
      repetir o processo n vezes:
      scannear operação;
      pegar os 2 numeros e colocar na lista ligada
      imprimir resultado de acordo com operação
      */
    int n_op,i;
    char operacao;
    p_no a,b,result;
    scanf("%i ",&n_op);
    for(i=0;i<n_op;i++){
        scanf("%c ", &operacao);
        a = criar_lista();
        b = criar_lista();
        result = criar_lista();
        a=ler_lista(a);
        b=ler_lista(b);
        switch(operacao){
            case '+':
                result = somar(a,b);
                break;
            case '-':
                result = subtrair(a,b);
                break;
            case '*':
                result = multiplicar(a,b);
                break;
        }
        if(result){
            imprimir_lista(result);
        }
        destruir_lista(a);
        destruir_lista(b);
        destruir_lista(result);
    }
    return 0;
}