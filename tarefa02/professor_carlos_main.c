#include <stdio.h>
#include "professor_carlos.h"
#define MAX 100
void ler_primeira_entrada(x,y){
    scanf("%d%d",&x,&y);
}
Turma ler_turma(){
    int qtde,i;
    Turma x;
    scanf("%d",&qtde);
    x.qtd=qtde;
    for(i=0;i<qtde;i++){
        scanf("%s", x.alunos[i].nome);
        scanf("%s", x.alunos[i].sobrenome);
        scanf("%d%d%d",&x.alunos[i].nascimento.dia,&x.alunos[i].nascimento.mes,&x.alunos[i].nascimento.ano);
    }
    return x;
}
void ler_operacao(Turma t[],int numero_turmas){
    int operacao;
    scanf("%d",&operacao);
    switch(operacao){
        case 1 :
            int idturma;
            scanf("%d",&idturma);
            Aluno novo=procura_novo_na_turma(t,numero_turmas,idturma);
            printf("%s",novo.nome);
        break;

        case 2 : 
            int idturma;
            scanf("%d",&idturma);
            Aluno velho=procura_velho_na_turma(t,numero_turmas,idturma);
            printf("%s",velho.sobrenome);
        break;

        case 3 :
            Aluno mVelho=procura_velho_todas_turmas(t,numero_turmas);
            printf("%s",mVelho.nome);
        break;

        case 4 :
            Aluno mNovo=procura_novo_todas_turmas(t,numero_turmas);
            printf("%s",mNovo.sobrenome);
        break;

        case 5 :
            
        break;

        case 6 :
            int idturma;
            Aluno a;
            scanf("%d",&idturma);
            scanf("%s",a.nome);
            scanf("%s",a.sobrenome);
            scanf("%d%d%d",&a.nascimento.dia,&a.nascimento.mes,&a.nascimento.ano);
            printf("%d",add_aluno(t,a,idturma));
        break;
        
        case 7 :
            int idturma;
            scanf("%d",&idturma);
            printf("%d",remove_aluno(t,idturma));
        break;
    }
}

int main(){
    int n_operacoes,n_turmas,i;
    Turma t[MAX];
    ler_primeira_entrada(n_operacoes,n_turmas);
    for(i=0;i<n_turmas;i++){
        t[i]=ler_turma();
    }
    for(i=0;i<n_operacoes;i++){
        ler_operacao(t,n_turmas);
    }
    return 0;
}