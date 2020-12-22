#ifndef TAREFA08_ARVORE_RN_H
#define TAREFA08_ARVORE_RN_H
enum Cor {VERMELHA, PRETA};

typedef struct No {
    struct No *esquerdo, *direito, *pai;
    enum Cor cor;
    long valor;
    int quantidade;
} No;
typedef No* p_no;

p_no criar_no(long valor);
p_no achar_pai(p_no filho);
p_no achar_avo(p_no neto);
p_no achar_irmao(p_no irmao);
p_no achar_tio(p_no sobrinho);
p_no rotacionar_direita(p_no no);
p_no rotacionar_esquerda(p_no no);
//void consertar_arvore(p_no novo);
p_no inserir(p_no raiz, long valor_novo);
p_no buscar(p_no raiz, long valor);
#endif //TAREFA08_ARVORE_RN_H
