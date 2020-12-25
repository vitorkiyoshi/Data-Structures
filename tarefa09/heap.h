typedef struct Cliente {
    char nome[15];
    double av;
    int x1,x2,y1,y2;
} Cliente;
typedef struct Cliente *p_cliente;
void remover_elemento(p_cliente *heap, int *n,char nome[15]);