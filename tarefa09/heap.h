typedef struct Cliente {
    char nome[15];
    double av;
    int x1,x2,y1,y2;
} Cliente;
typedef struct Cliente *p_cliente;
void heap_sort(int v*, n);//Uso de heapsort para ordenação das avaliações de cliente,
void desce_no_heap(p_cliente *heap,int n, int k);
void remover_elemento(char nome[]);
int F_ESQ(int n);
int F_DIR(int n);
void adicionar_elemento(char nome[], double avaliacao, int x1, int y1, int x2, int y2);