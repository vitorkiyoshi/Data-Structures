#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int fim_entrada = 0;
typedef struct No {
    int valor;
    struct No *proximo;
    struct No *anterior;
} No;
typedef struct Paciente{
    char nome[51];
    char privilegio[13];
    int ordem;
    struct Paciente *proximo;
    struct Paciente *anterior;
    No *atendimentos;
} Paciente;
No *add(No *lista, int numero){
    No *novo_no = malloc(sizeof(No));
    novo_no->valor = numero;
    novo_no->anterior = lista;
    novo_no->proximo = NULL;
    if (lista != NULL){
        lista->proximo = novo_no;
    }
    return novo_no;
}
typedef struct Fila{
    Paciente *primeiro;
    Paciente *ultimo;
} Fila;
Fila criar_fila(){
    Fila fila;
    fila.primeiro = NULL;
    fila.ultimo = NULL;
    return fila;
}
void queue_normal(Fila *fila, Paciente *paciente){
    if(fila->primeiro == NULL){
        fila->primeiro = fila->ultimo = paciente;
    } else {
        fila->ultimo->proximo = paciente;
        paciente->anterior = fila->ultimo;
        fila->ultimo = paciente;
    }
}
void queue_prioritario(Fila *fila, Paciente *paciente){
    if(fila->primeiro == NULL){
        fila->primeiro = fila->ultimo = paciente;
    } else {
        fila->primeiro->anterior = paciente;
        paciente->proximo = fila->primeiro;
        fila->primeiro = paciente;
    }
}
Paciente *dequeue(Fila *fila){
    if(fila->primeiro == NULL){
        return NULL;
    } else {
        Paciente *primeiro = fila->primeiro;
        if (fila->primeiro == fila->ultimo){
            fila->primeiro = fila->ultimo = NULL;
        } else {
            fila->primeiro = fila->primeiro->proximo;
        }
        return primeiro;
    }
}

int main(){
    /*Uso agora de 10 filas, em que vão se modificando ao longo do processo*/
    return 0;
}