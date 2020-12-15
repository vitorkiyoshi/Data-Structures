#include <stdio.h>
#include <stdlib.h>
//listas ligadas
typedef struct No{
    char *nome;
    int minutos;
    struct No_sequencia_salas *sequencia_salas;
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
    struct No_sequencia_salas *prox;
    struct No_sequencia_salas *ant;
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
    novo->ant = lista;
    novo->sala = numero;
    novo->prox=NULL;
    if(lista){
        lista->prox=novo;
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
void enqueue_direita(p_fila f, char name[51], p_no_seq *lista_salas, int min){
        p_no novo;
        novo = malloc(sizeof(No));
        novo->nome = *name;
        novo->sequencia_salas = lista_salas;
        novo->minutos = min;
        novo->prox = NULL;
        if (f->inicio == NULL) {
            f->inicio = novo;
        } else {
            f->fim->prox = novo;
        }
        f->fim = novo;
}
int enqueue_direita_esp(p_fila_esp f, char name[51], p_no_seq *lista_salas){//apenas enqueue esquerda
    if(f->tamanho>0) {
        p_no novo;
        novo = malloc(sizeof(No));
        novo->nome = *name;
        novo->sequencia_salas = lista_salas;
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
void enqueue_esquerda(p_fila f, char name[51], p_no_seq *list_salas, int min){
        p_no novo;
        novo = malloc(sizeof(No));
        novo->nome = *name;
        novo->sequencia_salas = list_salas;
        novo->minutos = min;
        novo->prox = NULL;
        if (f->inicio == NULL) {
            f->inicio = novo;
        } else {
            f->inicio->ant = novo;
        }
        f->inicio = novo;
}
void dequeue_esquerda(p_fila f,p_fila g,p_fila_esp salas[]){//de uma fila pra outra, verifica disponibilidade da sala
    int addminutos=f->inicio->minutos+10;
    if(f->inicio->sequencia_salas->prox==NULL){
        if(enqueue_direita_esp(salas[f->inicio->sequencia_salas->sala],f->inicio->nome,&f->inicio->sequencia_salas)){
             //basta printar resultados, nome e horario de saida
             int horas= addminutos/60;
             int min=addminutos%60;
             printf("%s %d:%d\n",f->inicio->nome,horas,min);
        }
        else{
            enqueue_direita(g,f->inicio->nome,&f->inicio->sequencia_salas,addminutos);//se não só vai pra outra fila
        }
    }
    else{
        if(enqueue_direita_esp(salas[f->inicio->sequencia_salas->sala],f->inicio->nome,&f->inicio->sequencia_salas)){
            enqueue_direita(g,f->inicio->nome,&f->inicio->sequencia_salas->prox,addminutos);//espera proximo atendimento
        }
        else{
            enqueue_direita(g,f->inicio->nome,&f->inicio->sequencia_salas,addminutos);
        }
    }
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
void dequeue_direita(p_fila f,p_fila g){
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
    while(scanf("%i",&esp)!='\n'){
        a = add(a,esp-1);
    }
    while(a->ant){
        a=a->ant;
    }
    return a;
}
void criar_Salas(p_fila_esp esp[]){
    int i;
    int tam_esp[9]={10,2,5,3,4,7,2,1,4};//setando especialidades
    for(i=0;i<9;i++){
        esp[i]=criar_fila_esp(tam_esp[i]);
    }
}
void destruirSalas(p_fila_esp esp[]){
    int i;
    for(i=0;i<9;i++){
        destruir_fila_esp(esp[i]);
    }
}
int main(){
    p_fila pacientesA,pacientesB;
    p_fila_esp especialidades[9];
    p_no_seq lista_esp;
    char nome_paciente[51];
    char prioridade[13];
    criar_Salas(especialidades);
    lista_esp=criar_lista_seq();
    pacientesA=criar_fila();
    pacientesB=criar_fila();
    //enquanto nn ter eof pra leitura, fazer leitura das n salas
    while(scanf("\"%[^\"]50s %s" , nome_paciente, prioridade)!=EOF){
        lista_esp=lerSalas(lista_esp);
        if(prioridade=="normal"){
            enqueue_direita(pacientesA,nome_paciente,lista_esp,480);
        }
        else{
            enqueue_esquerda(pacientesA,nome_paciente,lista_esp,480);
        }
    }
    while(pacientesA->inicio!=NULL && pacientesB->inicio!=NULL){
            while(pacientesA!=NULL){
                dequeue_esquerda(pacientesA,pacientesB,especialidades);//após isso, deve-se resetar as salas
            }
            destruirSalas(especialidades);
            criar_Salas(especialidades);
            while(pacientesB!=NULL){
                dequeue_esquerda(pacientesB,pacientesA,especialidades);//após isso, deve-se resetar as salas
            }
            destruirSalas(especialidades);
            criar_Salas(especialidades);
    }

    return 0;
}