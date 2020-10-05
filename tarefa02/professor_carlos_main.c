#include <stdio.h>
#include "professor_carlos.h"
#define MAX 100
Turma ler_turma(){
    int qtde,i;
    Turma x;
    scanf("%d",&qtde);
    x.qtd=qtde;
    for(i=0;i<qtde;i++){
        scanf("%s",x.alunos[i].nome);
        scanf("%s",x.alunos[i].sobrenome);
        scanf("%d",&x.alunos[i].nascimento.dia);
        scanf("%d",&x.alunos[i].nascimento.mes);
        scanf("%d",&x.alunos[i].nascimento.ano);
    }
    return x;
}
void ler_operacao(Turma t[],int numero_turmas){
    Aluno al;
    int operacao,idturma;
    char s[5];
    scanf(" %d",&operacao);
    switch(operacao){
        case 1 :
            scanf(" %d",&idturma);
            printf("%s\n",procura_novo_na_turma(t,numero_turmas,idturma).nome);
        break;

        case 2 : 
            scanf(" %d",&idturma);
            printf("%s\n",procura_velho_na_turma(t,numero_turmas,idturma).sobrenome);
        break;

        case 3 :
            printf("%s\n",procura_velho_todas_turmas(t,numero_turmas).nome);
        break;

        case 4 :
            printf("%s\n",procura_novo_todas_turmas(t,numero_turmas).sobrenome);
        break;

        case 5 :
            scanf(" %s",s);
            printf("%d\n",conta_substrings(t,numero_turmas,s));
        break;

        case 6 :
            scanf(" %d",&idturma);
            scanf(" %s",al.nome);
            scanf(" %s",al.sobrenome);
            scanf("%d %d %d",&al.nascimento.dia,&al.nascimento.mes,&al.nascimento.ano);
            printf("%d\n",add_aluno(t,al,idturma));
        break;
        
        case 7 :
            scanf(" %d ",&idturma);
            printf("%d\n",remove_aluno(t,idturma));
        break;
    }
}

int main(){
    int n_operacoes,n_turmas,i,j;
    Turma t[MAX];
    scanf(" %d ",&n_turmas);
    scanf(" %d ",&n_operacoes);
    for(i=0;i<n_turmas;i++){
        t[i]=ler_turma();
    }
    for(j=0;j<n_operacoes;j++){
        ler_operacao(t,n_turmas);
    }
    return 0;
}