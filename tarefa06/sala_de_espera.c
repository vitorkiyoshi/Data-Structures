#include <stdio.h>
#include <stdlib.h>
//listas ligadas
typedef struct No{
    char *nome;
    int minutos;
    struct p_no_seq *sequencia_salas;
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
typedef struct No_sequencia_salas{  /*LISTA LIGADA PARA ESPECIALIDADES*/
    int sala;
    struct No *prox;
    struct No *ant;
} No_sequencia_salas;
typedef struct No_sequencia_salas *p_no_seq;
p_no_seq criar_lista_seq(){
    return NULL;
}
void destruir_lista_seq(p_no_seq lista){
    if(lista!=NULL){
        destruir_lista(lista->prox);
        free(lista);
    }
}
p_no add(p_no_seq lista, int numero){
    p_no_seq novo= malloc(sizeof(No_sequencia_salas));
    novo->prox = novo->ant = NULL;
    novo->ant = numero;
    if(lista) {
        novo->prox = lista;
        lista->ant = novo;
    }
    return novo;
}
//FILA DEQUE em pacientes, outra fila simples(salas)
typedef struct{
    p_no inicio,fim;
} Fila;
typedef struct{
    p_no inicio,fim;
    int tamanho;
} Fila_especialidade;
typedef Fila *p_fila;
typedef Fila_especialidade *p_fila_esp;
p_fila criar_fila(){
    p_fila f;
    f=malloc(sizeof(Fila));
    f->inicio=NULL;
    f->fim=NULL;
    return f;
}
p_fila_esp criar_fila_esp(int tam){
    p_fila_esp f;
    f=malloc(sizeof(Fila));
    f->inicio=NULL;
    f->fim=NULL;
    f->tamanho=tam;
    return f;
}
void destruir_fila(p_fila f){
    destruir_lista(f->inicio);
    free(f);
}
void destruir_fila_esp(p_fila_esp f){
    destruir_lista(f->inicio);
    free(f);
}
void enqueue_direita(p_fila f, char name[50], p_no_seq lista_salas){
        p_no novo;
        novo = malloc(sizeof(No));
        novo->nome = *name;
        novo->sequencia_salas = lista_salas;
        novo->minutos = 480;
        novo->prox = NULL;
        if (f->inicio == NULL) {
            f->inicio = novo;
        } else {
            f->fim->prox = novo;
        }
        f->fim = novo;
}
int enqueue_direita_esp(p_fila_esp f, char name[51], p_no_seq lista_salas){//apenas enqueue esquerda
    if(f->tamanho>0) {
        p_no novo;
        novo = malloc(sizeof(No));
        novo->nome = *name;
        novo->sequencia_salas = lista_salas;
        novo->minutos = 480;
        novo->prox = NULL;
        if (f->inicio == NULL) {
            f->inicio = novo;
        } else {
            f->fim->prox = novo;
        }
        f->fim = novo;
        f->tamanho-=1;
        return 1;
    }
    else{
        return 0;
    }
}
void enqueue_esquerda(p_fila f, char name[51], p_no_seq lista_salas){
        p_no novo;
        novo = malloc(sizeof(No));
        novo->nome = *name;
        novo->sequencia_salas = lista_salas;
        novo->minutos = 480;
        novo->prox = NULL;
        if (f->inicio == NULL) {
            f->inicio = novo;
        } else {
            f->inicio->ant = novo;
        }
        f->inicio = novo;
}
void dequeue_esquerda(p_fila f){
    if(f->fim == f->inicio && f->fim != NULL){
        f->fim = f->inicio = NULL;
    } else if (f->fim!=NULL) {
        f->inicio = f->inicio->prox;
    }
}
void dequeue_esquerda_esp(p_fila_esp f){//precisará apenas da dequeue esquerda, por não necessitar
    if(f->fim == f->inicio && f->fim != NULL){
        f->fim = f->inicio = NULL;
        f->tamanho+=1;
    } else if (f->fim!=NULL) {
        f->inicio = f->inicio->prox;
        f->tamanho+=1;
    }
}
void dequeue_direita(p_fila f){
    if(f->fim == f->inicio && f->fim != NULL){
        f->fim = f->inicio = NULL;
    } else if (f->fim!=NULL) {
        f->fim = f->fim->ant;
    }
}

/*2 filas para pacientes, conforme atende, vai pra outra fila e vice versa
 * se a especialidade tiver disponivel, adiciona na fila dela e passa pra proxima especialidade a ser atendida
 * se já passou por todos, exclui da fila circular
 * se a especialidade tiver lotada, passa pro proximo e continua adicionando 10 min
 * quando a fila circular voltar pro começo, resetar as filas de especialidades
 * sempre que passar pro proximo, adicionar 10 min ao paciente
 */
//Funções de entrada e saída
p_no_seq lerSalas(p_no_seq a){
    int esp;
    while(scanf("%d",&esp)!='\n'){
        a = add(a,esp);
    }
    return a;
}
int main(){
    p_fila pacientesA,pacientesB;
    p_fila especialidades[9];
    p_no_seq lista_esp;
    int tam_esp[9]={10,2,5,3,4,7,2,1,4}; //setando especialidades
    char nome_paciente[51];
    char prioridade[13];
    int i;
    for(i=0;i<9;i++){
        especialidades[i]=criar_fila(tam_esp[i]);
    }
    lista_esp=criar_lista_seq();
    //enquanto nn ter eof pra leitura, fazer leitura das n salas
    while(scanf("\"%[^\"]50s %s" , nome_paciente, prioridade)!=EOF){
        lista_esp=lerSalas(lista_esp);

    }
    /*fazer a parte de operação
     *
     * */
    return 0;
}