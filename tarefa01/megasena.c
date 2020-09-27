#include <stdio.h>
#define MAX 1000

void lerDezenas(int jogos[][6],int participantes){
    for(int jogador=0;jogador<participantes;jogador++){
        int posicao = 0;
        for(int numero=1;numero<=60;numero++){
            int marcado = getchar() == '1';
            if (marcado){
                jogos[jogador][posicao] = numero;
                posicao++;
            }
            getchar(); /*Pulando caractere de espaço*/
        }
        if(posicao != 59) {
            jogos[jogador][posicao+1] = 0;
        }
    }
}
int main(){
    int jogador;
    int jogos[MAX][6];
    int jogadores;
    double prize;
    scanf("&d&f", &jogadores, &prize);
    lerDezenas(jogos,jogadores);
    return 0;
}