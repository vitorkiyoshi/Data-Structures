#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <string.h>
void troca(int n1, int n2, p_cliente *heap){
    p_cliente temp=heap[n1];
    heap[n1]=heap[n2];
    heap[n2]=temp;
}
void construirHeap(p_cliente *heap,int n, int index){//construindo heap recursivamente
    int maior= index;
    int esq=2*index+1;
    int dir=2*index+2;
    if(esq<n && heap[esq]->av > heap[maior]->av){
        maior=esq;
    }
    if(dir<n && heap[dir]->av > heap[maior]->av){
        maior=dir;
    }
    if(maior!=index){
        troca(index,maior,heap);
        construirHeap(heap,n,maior);
    }
}
void heapsort(p_cliente *heap,int n){//iterativo de construirheap
    for(int i=n/2-1;i>=0;i--){
        construirHeap(heap,n,i);
    }
    for(int i=n-1;i>0;i--){
        troca(0,i,heap);
        construirHeap(heap,i,0);
    }
}
void add_elemento(p_cliente *heap,int *numero_clientes){//adicionando elemento heap
    char nome[15];
    p_cliente temp;
    double avaliacao;
    int x1,y1,x2,y2;
    heap[*numero_clientes]=malloc(sizeof(Cliente));
    scanf("%s %lf %i %i %i %i",nome, &avaliacao, &x1, &y1, &x2, &y2);
    heap[*numero_clientes]->av=avaliacao;
    strcpy(heap[*numero_clientes]->nome,nome);
    heap[*numero_clientes]->x1=x1;
    heap[*numero_clientes]->x2=x2;
    heap[*numero_clientes]->y1=y1;
    heap[*numero_clientes]->y2=y2;
    *numero_clientes+=1;
    if(*numero_clientes>1){//deve-se colocar a pessoa em ultimo
        for(int i=0;i<*numero_clientes;i++){
            temp=heap[i];
            heap[i]=heap[*numero_clientes-1];
            heap[*numero_clientes-1]=temp;
        }
        printf("Cliente %s foi adicionado(a)\n",heap[0]->nome);
    }
    else {
        printf("Cliente %s foi adicionado(a)\n", heap[*numero_clientes - 1]->nome);
    }
}
void remover_elemento(p_cliente *heap,int *numero_clientes,char nome[15]){//desaloca posição do vetor para depois ser realocado
    int pos=0;
    p_cliente temp;
    while(1){
        if(strcmp(heap[pos]->nome,nome)==0){
            temp = heap[*numero_clientes-1];
            heap[*numero_clientes-1] = heap[pos];
            heap[pos] = temp;
            free(heap[*numero_clientes-1]);
            *numero_clientes-=1;
            break;
        }
        pos+=1;
    }
}
/*void remover_ultimo_elemento(p_cliente *heap,int *numero_clientes){
    free(heap[*numero_clientes-1]);
    *numero_clientes-=1;
}*/
int calcDistancia(int x1,int x2,int y1, int y2){//distancia de manhattan
    int x= x1-x2;
    int y= y1-y2;
    if(x<0){
        x=x*(-1);
    }
    if(y<0){
        y=y*(-1);
    }
    return x+y;
}
/*void printarlista(p_cliente *heap, int n){//Função de debug
    for (int i=0;i<n;i++){
        printf("%s\n",heap[i]->nome);
    }
}*/
int main(){
    char operacao='x';
    p_cliente clientes[500],proximo_cliente;
    int *n_clientes=malloc(sizeof(int));
    *n_clientes=0;//inicia com 0
    char nome[15];//remoção a partir de um nome
    //variaveis para avaliar kilometragem
    double kilometragem=0,distancia=0,kilometragem_rentavel=0;
    int n_cancelamentos=0;
    double renda_bruta,renda_liquida,despesas;
    int posX=0,posY=0;//posicao do carro no trajeto
    while (operacao!='T'){
        scanf("%c",&operacao);
        switch(operacao){
            case 'A':
                add_elemento(clientes,n_clientes);
                break;
            case 'C':
                scanf("%s",nome);
                remover_elemento(clientes,n_clientes,nome);
                printf("%s cancelou a corrida\n",nome);
                n_cancelamentos+=1;
                break;
            case 'F':
                distancia+=calcDistancia(posX,proximo_cliente->x1,posY,proximo_cliente->y1);
                //calcular distancia até destino como rentave
                kilometragem_rentavel+=calcDistancia(proximo_cliente->x1,proximo_cliente->x2,proximo_cliente->y1,proximo_cliente->y2);
                //setar posFinal
                posX=proximo_cliente->x2;
                posY=proximo_cliente->y2;
                printf("A corrida de %s foi finalizada\n",proximo_cliente->nome);
                remover_elemento(clientes,n_clientes,proximo_cliente->nome);
                proximo_cliente=NULL;
                heapsort(clientes, *n_clientes);
                proximo_cliente = clientes[*n_clientes - 1];
                break;
        }
        if(*n_clientes-1==0) {
            proximo_cliente = clientes[*n_clientes - 1];
        }

    }//Calculo Final da renda UBER
    kilometragem=kilometragem_rentavel+distancia;
    renda_bruta=7*n_cancelamentos + 1.4*kilometragem_rentavel;
    despesas=57 + ((kilometragem/10)*4.104);
    renda_liquida=renda_bruta-despesas-(renda_bruta*0.25);
    printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
    printf("Km total: %.0lf\n",kilometragem);
    printf("Rendimento bruto: %.2lf\n",renda_bruta);
    printf("Despesas: %.2lf\n",despesas);
    printf("Rendimento liquido: %.2lf\n",renda_liquida);
    free(n_clientes);
    return 0;
}