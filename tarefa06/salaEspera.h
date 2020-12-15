//listas ligadas
typedef struct No{
    char nome[51];
    int minutos;
    struct No_sequencia_salas *sequencia_salas;
    struct No *prox;
    struct No *ant;
} No;
typedef struct No *p_no;
typedef struct No_sequencia_salas{  /*LISTA LIGADA PARA ESPECIALIDADES*/
    int sala;
    struct No_sequencia_salas *prox;
    struct No_sequencia_salas *ant;
} No_sequencia_salas;
typedef struct No_sequencia_salas *p_no_seq;
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