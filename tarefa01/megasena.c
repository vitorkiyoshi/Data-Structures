#include <stdio.h>
#define MAX 100

void lerDezenas(int jogos[][15],int participantes){
    int jogador,posicao,marcado,numero;
    for(jogador=0;jogador<participantes;jogador++){
        posicao = 0;
        for(numero=1;numero<=60;numero++){
            marcado = getchar() == '1';
            if (marcado){
                jogos[jogador][posicao] = numero;
                posicao+=1;
            }
            getchar(); /*Pulando caractere de espaço*/
        }
        if(posicao != 14) {
            jogos[jogador][posicao+1] = 0; /*limite de 15 numeros no volante*/
        }
    }
}
void lerSorteado(int sorteado[6]){
    for(int i=0;i<6;i++){
        scanf("%i",&sorteado[i]);
    }
}
void calcularAcertos(int jogos[][15],int sorteado[6],int acertosJogadores[MAX],int jogadores){
    int acertos=0;
    for(int i=0;i<jogadores;i++){
        for(int j=0;j<15;j++){
            if(jogos[i][j]==0){
                break;
            }
            for(int k=0;k<6;k++){
                if(jogos[i][j]==sorteado[k]){
                    acertos+=1;
                }
            }
        }
        acertosJogadores[i]=acertos;
        acertos=0;
    }
}
void definirPremio(double premio[MAX], int acertosJogadores[MAX], int jogadores, double prize){
    double primeiro,segundo,quadra,quina,sena;
    int qtde=0;
    primeiro=prize*0.62;
    segundo=prize*0.19;
    for(int i=4;i<=6;i++){
        for(int j=0;j<jogadores;j++){
            if(acertosJogadores[j]==i){ /*definindo valor do premio de acordo com acertos*/
                qtde+=1;
            }
        }
        if(i==4){
            quadra=segundo/qtde;
            for(int j=0;j<jogadores;j++){
                if(acertosJogadores[j]==4){
                    premio[j]=quadra;
                }
            }
        }
        if(i==5){
            quina=segundo/qtde;
            for(int j=0;j<jogadores;j++){
                if(acertosJogadores[j]==5){
                    premio[j]=quina;
                }
            }
        }
        if(i==6){
            sena=primeiro/qtde;
            for(int j=0;j<jogadores;j++){
                if(acertosJogadores[j]==6){
                    premio[j]=sena;
                }
            }
        }
        qtde=0;
    }
}
int main(){
    int jogos[MAX][15],jogadores,acertosJogadores[MAX];
    double prize,premio[MAX];
    int sorteado[6];
    scanf("&d&lf", &jogadores, &prize);
    lerDezenas(jogos,jogadores);
    lerSorteado(sorteado);
    calcularAcertos(jogos,sorteado,acertosJogadores,jogadores);
    for(int i=0;i<jogadores;i++){
        premio[i]=0;    /*definindo premio de cada um para 0 por não saber os acertos*/
    }
    definirPremio(premio,acertosJogadores,jogadores,prize);
    for(int i=0;i<jogadores;i++){
        printf("%.2f",premio[i]);
    }
    return 0;
}