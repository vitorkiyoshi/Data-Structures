#include <stdio.h>
#include <stdlib.h>
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
typedef struct No_sequencia_salas{
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
typedef struct{
    p_no inicio,fim;
} Fila;
typedef Fila *p_fila;
p_fila criar_fila(){
    p_fila f;
    f=malloc(sizeof(Fila));
    f->inicio=NULL;
    f->fim=NULL;
    return f;
}
void destruir_fila(p_fila f){
    destruir_lista(f->inicio);
    free(f);
}
void enqueue_direita(p_fila f, char *name, p_no_seq lista_salas){
    p_no novo;
    novo=malloc(sizeof(No));
    novo->nome=*name;
    novo->sequencia_salas=lista_salas;
    novo->minutos=480;
    novo->prox=NULL;
    if(f->inicio==NULL){
        f->inicio= novo;
    }
    else{
        novo->ant=f->fim;
        f->fim->prox=novo;
    }
    f->fim=novo;
}
void enqueue_esquerda(p_fila f, char *name, p_no_seq lista_salas){
    p_no novo;
    novo=malloc(sizeof(No));
    novo->nome=*name;
    novo->sequencia_salas=lista_salas;
    novo->minutos=480;
    novo->ant=NULL;
    if(f->inicio==NULL){
        f->inicio=novo;
    }
    else{
        novo->prox=f->inicio;
        f->inicio->ant=novo;
    }
    f->inicio=novo;
}

void dequeue_esquerda(){

}

/*fila circular para os pacientes
 * se a especialidade tiver disponivel, adiciona na fila dela e passa pra proxima especialidade a ser atendida
 * se já passou por todos, exclui da fila circular
 * se a especialidade tiver lotada, passa pro proximo e continua adicionando 10 min
 * quando a fila circular voltar pro começo, resetar as filas de especialidades
 * sempre que passar pro proximo, adicionar 10 min ao paciente
 */
int main(){

    return 0;
}