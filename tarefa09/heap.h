typedef struct Cliente {
    char nome[15];
    double av;
    int x1,x2,y1,y2;
} Cliente;
typedef struct Cliente *p_cliente;
void heapsort(p_cliente *heap, int n);//Uso de heapsort para ordenação das avaliações de cliente,
void desce_no_heap(p_cliente *heap,int n, int k);
void remover_elemento(p_cliente *heap, int *n);
int F_ESQ(int n);
int F_DIR(int n);