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
void add_elemento(p_cliente *heap,int *numero_clientes){//adicionando elemento heap
    char nome[15];
    double avaliacao;
    int x1,y1,x2,y2;
    scanf("%s %lf %i %i %i %i",nome, &avaliacao, &x1, &y1, &x2, &y2);
    *numero_clientes+=1;
    heap[*numero_clientes-1]->av=avaliacao;
    heap[*numero_clientes-1]->nome=nome;
    heap[*numero_clientes-1]->x1=x1;
    heap[*numero_clientes-1]->x2=x2;
    heap[*numero_clientes-1]->y1=y1;
    heap[*numero_clientes-1]->y2=y2;
}
void remover_elemento(p_cliente *heap, int *n, char name[]){//remover elemento do vetor heap
    int m=1;
    p_cliente temp;
    i=0;
    while(m){
        if(heap[i]->nome==nome){
            m=0;
            for(int j=i;j<*n-1;j++){
                heap[j]=heap[j+1];
            }
            *n-=1;
        }
    }
}
int calcularDistancia(int x1,int x2,int y1, int y2){
    int x,y;
    if(x1-x2<0){
        x=-(x1-x2);
    }
    else{
        x=x1-x2;
    }
    if(y1-y2<0){
        y=-(y1-y2);
    }
    else{
        y=y1-y2;
    }
    return x+y;
}
int addDistancia(int kilometragem, int distancia){
    if(kilometragem==0){

    }
    else{
        kilometragem+=
    }
}
int main(){
    char operacao;//variaveis utilizadas para entrada
    char nome[15];
    double avaliacao;
    int *numero_clientes,x1,x2,y1,y2;
    numero_clientes=malloc(sizeof(int));
    p_cliente clientes[MAX];
    *numero_clientes=0;
    //variaveis para calculo efetivo de dist, renda
    int kilometragem,posX,posY;
    double renda_bruta;
    double despesas;
    double renda_liquida;
    while(operacao!='T'){
        scanf("%c", &operacao);
        switch(operacao){
            case 'A':
                add_elemento(clientes,numero_clientes);
                printf("Cliente %s foi adicionado(a)",clientes[*numero_clientes-1]->nome);
            case 'C':
                scanf("%s",nome);
                remover_elemento(clientes,numero_clientes,nome);
                printf("%s cancelou a corrida");
            case 'F':
                heapsort(clientes,*numero_clientes);
                //adicionar distancia da origem do carro até ponto inicial do cliente
                //adicionar kilometragem até destino
                //setar carro na posição final
                /*Para o preço*/

        }
    }
    printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
}