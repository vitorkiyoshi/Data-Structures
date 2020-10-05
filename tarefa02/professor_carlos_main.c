#include <stdio.h>
#include "professor_carlos.h"
#define MAX 100
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
    int operacao,idturma;
    Aluno al;
    char s[15];
    scanf("%d",&operacao);
    switch(operacao){
        case 1 :
            scanf("%d",&idturma);
            al=procura_novo_na_turma(t,numero_turmas,idturma);
            printf("%s\n",al.nome);
        break;

        case 2 : 
            scanf("%d",&idturma);
            al=procura_velho_na_turma(t,numero_turmas,idturma);
            printf("%s\n",al.sobrenome);
        break;

        case 3 :
            al=procura_velho_todas_turmas(t,numero_turmas);
            printf("%s\n",al.nome);
        break;

        case 4 :
            al=procura_novo_todas_turmas(t,numero_turmas);
            printf("%s\n",al.sobrenome);
        break;

        case 5 :
            scanf("%s",s);
            printf("%d\n",conta_substrings(t,numero_turmas,s));
        break;

        case 6 :
            scanf("%d",&idturma);
            scanf("%s",al.nome);
            scanf("%s",al.sobrenome);
            scanf("%d%d%d",&al.nascimento.dia,&al.nascimento.mes,&al.nascimento.ano);
            printf("%d\n",add_aluno(t,al,idturma));
        break;
        
        case 7 :
            scanf("%d",&idturma);
            printf("%d\n",remove_aluno(t,idturma));
        break;
    }
}

int main(){
    int n_operacoes,n_turmas,i;
    Turma t[MAX];
    scanf("%d",&n_turmas);
    scanf("%d",&n_operacoes);
    for(i=0;i<n_turmas;i++){
        t[i]=ler_turma();
    }
    for(i=0;i<n_operacoes;i++){
        ler_operacao(t,n_turmas);
    }
    return 0;
}