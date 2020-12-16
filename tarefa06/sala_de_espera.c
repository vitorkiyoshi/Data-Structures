#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int fim_entrada = 0;
typedef struct No {/*fila agora possui sistema de privilegios quando entra para uma novafila*/
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

Paciente *ler_paciente(){
    Paciente *paciente = malloc(sizeof(struct Paciente));
    paciente->atendimentos = NULL;
    paciente->anterior = paciente->proximo = NULL;
    if(scanf("\"%50[^\"]s" , paciente->nome) == EOF){
        fim_entrada = 1;
        return paciente;
    }
    scanf("\" %s", paciente->privilegio);
    char c;
    int sala;
    do{
        scanf("%c",&c);
        if(c >= '1' && c <= '9') {
            sala = c - '0';
            paciente->atendimentos = add(paciente->atendimentos,sala - 1);
        }
    }while(c!='\n');
    while(paciente->atendimentos->anterior){
        paciente->atendimentos = paciente->atendimentos->anterior;
    }
    return paciente;
}
int comparar_pacientes(const void *a, const void *b){
    int valor_1 = ((Paciente *)a)->ordem;
    int valor_2 = ((Paciente *)b)->ordem;
    return (valor_1 > valor_2) - (valor_1 < valor_2);
}

int main(){
    /*Uso agora de 10 filas, em que vão se modificando ao longo do processo*/
    int tamanhos[9] = {10,2,5,3,4,7,2,1,4};
    int maximo_novos = 0;
    for(int i = 0; i<9;i++){
        maximo_novos += tamanhos[i];
    }
    Fila filas[9];
    for(int i = 0; i<9;i++){
        filas[i] = criar_fila();
    }
    Paciente **pacientes_em_espera = malloc(sizeof(Paciente*) * maximo_novos);
    int posicao = 0;
    while(!fim_entrada){
        Paciente *atual = ler_paciente();
        if(!fim_entrada) {
            atual->ordem = posicao;
            if (strcmp("normal", atual->privilegio) == 0) {
                queue_normal(&filas[atual->atendimentos->valor], atual);
            } else {
                queue_prioritario(&filas[atual->atendimentos->valor], atual);
            }
            posicao += 1;
        } else {
            free(atual);
        }
    }
    int tempo = 490;
    while(1){
        int numero_saidos_da_fila = 0;
        for(int i = 0; i<9;i++){
            for(int j=0;j<tamanhos[i];j++){
                Paciente *saido = dequeue(&filas[i]);
                if (saido != NULL){
                    pacientes_em_espera[numero_saidos_da_fila] = saido;
                    numero_saidos_da_fila += 1;
                } else{
                    break;
                }
            }
        }
        if(numero_saidos_da_fila == 0){
            break;
        }
        qsort(pacientes_em_espera,numero_saidos_da_fila,sizeof(Paciente*), comparar_pacientes);
        for(int i = 0; i<numero_saidos_da_fila;i++){
            Paciente *atual = pacientes_em_espera[i];
            No *anterior = atual->atendimentos;
            atual->atendimentos = anterior->proximo;
            free(anterior);
            if(atual->atendimentos == NULL){
                int horas = tempo/60;
                int minutos = tempo%60;
                printf("%02i:%02i %s\n",horas,minutos,atual->nome);
                free(atual);
            } else {
                if (strcmp("normal", atual->privilegio) == 0) {
                    queue_normal(&filas[atual->atendimentos->valor], atual);
                } else {
                    queue_prioritario(&filas[atual->atendimentos->valor], atual);
                }
            }
        }
        tempo += 10;
    }
    free(pacientes_em_espera);
    return 0;
}