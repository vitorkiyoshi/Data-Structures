#include <stdio.h>
#include <stdlib.h>
#include <heap.h>
#define MAX 500
//definindo utilização de vetores
int F_DIR(int n){//relatar posição dos vizinhos
    return 2*n;
}
int F_ESQ(int n){
    return 2*n+1;
}
void troca(int n1, int n2, p_cliente *heap){
    p_cliente temp=heap[n1];
    heap[n1]=heap[n2];
    heap[n2]=temp;
}
void desce_no_heap(p_cliente *heap, int n, int k){
    int maior_filho;
    if(F_ESQ(k)<n){
        maior_filho=F_ESQ(k);
        if(F_DIR(K)<n && heap[F_ESQ(k)]->av < heap[F_DIR(k)]->av){
            maior_filho=F_DIR(k);
        }
        if(heap[k]->av<heap[maior_filho]->av){
            troca(k,maior_filho,heap);
            desce_no_heap(heap, n, maior_filho);
        }
    }
}
void heapsort(p_cliente *heap, int n){
    int k;
    for(k=n/2; k>=0; k--){
        desce_no_heap(heap,n,k);
    }
    while(n>1){
        troca(heap[0],heap(n-1));
        n--;
        desce_no_heap(heap,n,0);
    }
}

void remover_elemento(char nome[]){

}

int main(){
    char operacao;
    char nome[15];
    Cliente clientes[MAX];
    while(operacao!='T'){
        scanf("%c",operacao);
        switch(operacao){
            case 'A':
                scanf("%s",nome);
            case 'C':
                scanf("%s",nome);

            case 'F':;
        }
    }
    printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
}