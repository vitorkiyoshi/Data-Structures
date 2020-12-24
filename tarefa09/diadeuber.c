#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <string.h>
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
        if(F_DIR(k)<n && heap[F_ESQ(k)]->av < heap[F_DIR(k)]->av){
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
        troca(0,n-1,heap);
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
    strcpy(nome,heap[*numero_clientes]->nome);
    heap[*numero_clientes-1]->x1=x1;
    heap[*numero_clientes-1]->x2=x2;
    heap[*numero_clientes-1]->y1=y1;
    heap[*numero_clientes-1]->y2=y2;
}
void remover_elemento(p_cliente *heap, int *n, char name[]){//remover elemento do vetor heap
    int m=1;
    int i=0;
    while(m){
        if(strcmp(heap[i]->nome,name)==0){
            m=0;
            for(int j=i;j<*n-1;j++){
                heap[j]=heap[j+1];
            }
            *n-=1;
        }
        i+=1;
    }
}
int calcularDistancia(int x1,int x2,int y1, int y2){//distancia de manhattan de um ponto para outro
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

int main(){
    char operacao=' ';//variaveis utilizadas para entrada
    char nome[15];
    int *numero_clientes,qtde_cancelamentos=0;
    numero_clientes=malloc(sizeof(int));
    p_cliente clientes[MAX];
    *numero_clientes=0;
    //variaveis para calculo efetivo de dist, renda
    int pos_inicial=0;//posicao inicial do vetor
    int kilometragem=0,posX,posY;
    double renda_bruta;
    double despesas;
    double renda_liquida;
    while(operacao!='T'){
        scanf("%c", &operacao);
        switch(operacao){
            case 'A':
                add_elemento(clientes,numero_clientes);
                printf("Cliente %s foi adicionado(a)\n",clientes[*numero_clientes-1]->nome);
            case 'C':
                scanf("%s",nome);
                remover_elemento(clientes,numero_clientes,nome);
                printf("%s cancelou a corrida\n",nome);
                qtde_cancelamentos+=1;
            case 'F':
                heapsort(clientes,*numero_clientes);
                if(kilometragem==0){
                    kilometragem+=calcularDistancia(0,clientes[pos_inicial]->x1,0,clientes[pos_inicial]->y1); //chegando até o cliente
                }
                else{
                    kilometragem+=calcularDistancia(posX,clientes[pos_inicial]->x1,posY,clientes[pos_inicial]->y1);//chegando até o cliente
                }
                //adicionar kilometragem até destino
                kilometragem+=calcularDistancia(clientes[pos_inicial]->x1,clientes[pos_inicial]->x2,clientes[pos_inicial]->y1,clientes[pos_inicial]->y2);
                //setar carro na posição final
                posX=clientes[pos_inicial]->x2;
                posY=clientes[pos_inicial]->y2;
                /*Para o preço, calcular */
                printf("A corrida de %s foi finalizada\n",clientes[pos_inicial]->nome);
                pos_inicial+=1;
        }
    }
    renda_bruta=1.4*kilometragem;
    despesas= 57+((kilometragem/10)*4.104)+(renda_bruta/4)+(qtde_cancelamentos*7);
    renda_liquida=renda_bruta-despesas;
    printf("Jornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %i\n",kilometragem);
    printf("Rendimento bruto: %.2lf\n",renda_bruta);
    printf("Despesas: %.2lf\n",despesas);
    printf("Rendimento liquido: %.2lf\n",renda_liquida);
    free(numero_clientes);
}