#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_CELULA 7
#define MAX_CAMINHO 30
#define MAX_RESULTADO 20
#define MAX_STRING 1000
typedef struct lista_token{
    char *token;
    struct lista_token *proximo;
} Lista_token;

typedef Lista_token* p_lista;

typedef struct celula{
    char **expressao;
    int valor;
    int calculado;
} Celula;
typedef Celula* p_celula;
p_lista adicionar(p_lista raiz, char *token) {//adiciona token na lista de tokens
    p_lista novo = malloc(sizeof(Lista_token));
    novo->token=token;
    novo->proximo=NULL;
    if(raiz==NULL) {
        return novo;
    }
    p_lista ultimo =raiz;
    while(ultimo->proximo!=NULL) {
        ultimo=ultimo->proximo;
    }
    ultimo->proximo=novo;
    return raiz;
}
void destruir_lista(p_lista raiz){
    if(raiz != NULL) {
        destruir_lista(raiz->proximo);
        free(raiz);
    }
}
char **tokenizar(char *expressao) {//cria tokens de expressão, ler celula
    int limite = strlen(expressao) ;
    int quantidade_tokens = 0;
    char *token;
    token = malloc(sizeof(char) * MAX_CELULA);
    int pos = 0;
    p_lista lista =NULL;
    for(int i=0;i<limite;i++){
        if(expressao[i] ==' ') {
            token[pos] = '\0';
            pos = 0;
            lista = adicionar(lista, token);
            quantidade_tokens++;
            token = malloc(sizeof(char) *MAX_CELULA);
        } else {
            token[pos] = expressao[i] ;
            pos++;
        }
    }
    free(token);
    p_lista raiz=lista;
    char **tokens;
    tokens = malloc(sizeof(char*) * (quantidade_tokens + 1));
    int i=0;
    while(lista!=NULL) {
        tokens[i]=lista->token;
        i++;
        lista=lista->proximo;
    }
    tokens[quantidade_tokens] = NULL;
    destruir_lista(raiz);
    return tokens;
}
char* resolver_expressao(p_celula **celulas, char **expressao, char **dependencias, int quantidade_dependencias) {/*resolver uma expressão apresentando vetor de celulas
 * */
    if(expressao[0][0] == '='){
        expressao++;
    }
    if(expressao[0][0]>='A'&& expressao[0][0]<='Z'){
        for(int i=0;i<quantidade_dependencias;i++) {
            if(strcmp(expressao[0],dependencias[i])==0){//verificação ciclicidade
                return "#ERRO#";
            }
            p_celula objetivo = celulas[atoi(expressao[0]+1)-1][expressao[0][0]-'A'];
            if(objetivo->calculado) {
                char *resultado = malloc(sizeof(char)*20);
                sprintf(resultado, "%d", objetivo->valor);
                return resultado;
            } else {
                dependencias[quantidade_dependencias] = expressao[0];
                char *resultado = resolver_expressao(celulas, objetivo->expressao, dependencias, quantidade_dependencias +1);
                objetivo->valor = atoi(resultado);
                objetivo->calculado = 1;
                return resultado;
            }
        }
    } else {
        char **primeiro_termo, **segundo_termo;
        primeiro_termo = expressao + 1;
        segundo_termo = expressao;
        int parenteses = segundo_termo[0][0] == '('?-1:0;
        char operacao;
        while(1){
            if(segundo_termo[0][0] == '('){
                parenteses += 1;
            } else if (segundo_termo[0][0] == ')'){
                parenteses -= 1;
            } else if(parenteses == 0 && (segundo_termo[0][0] == '+' || segundo_termo[0][0]=='-')){
                operacao = segundo_termo[0][0];
                break;//realizando break após contagem de parenteses;
            }
            segundo_termo++;
        }
        segundo_termo+=1;
        char *resultado_primeiro = resolver_expressao(celulas, primeiro_termo, dependencias, quantidade_dependencias);
        if(resultado_primeiro[0]=='#'){
            return resultado_primeiro;
        }
        char *resultado_segundo = resolver_expressao(celulas, segundo_termo, dependencias, quantidade_dependencias);
        if(resultado_segundo[0]=='#'){
            free(resultado_primeiro);
            return resultado_segundo;
        }
        int result;
        if(operacao=='+'){//conversão de array para int para calculo das operações
            result = atoi(resultado_primeiro) + atoi(resultado_segundo);
        } else{
            result = atoi(resultado_primeiro) - atoi(resultado_segundo);
        }
        char resultado[20];//no máximo 20 carac.
        sprintf(resultado, "%d", result);
        free(resultado_primeiro);
        free(resultado_segundo);
        return resultado;
    }
    return NULL;
}

void escreverArquivo(int colunas, int linhas, p_celula **celulas, char *caminho){
    FILE *arquivo=fopen(caminho, "w");
    for(int i=0;i<linhas;i++) {
        for(int j=0;j<colunas-1;j++) {
            if(celulas[i][j]->expressao==NULL) {
                fprintf(arquivo, "%i,", celulas[i][j]->valor);
            }
            else{
                fprintf(arquivo, "%s,",*celulas[i][j]->expressao);
            }
        }
        if(celulas[i][colunas-1]->expressao==NULL) {
            fprintf(arquivo, "%i,\n", celulas[i][colunas-1]->valor);
        }
        else{
            fprintf(arquivo, "%s,\n",*celulas[i][colunas-1]->expressao);
        }
    }
    fclose(arquivo);
}
int verificarConstante(char *str){
    if(str[0]=='='){
        return 0;
    }
    return 1;
}
int main(){
    /*fscanf pegar valor com virgulas da célula, realizar as operações verificando ciclicidade
     * alterar primeiramente a matriz de celulas local, após,
     * printar saída de arquivo com supostos erros*/
    int linhas,colunas;
    char caminho[MAX_CAMINHO];//registra caminho do csv
    char *celula;//manipulação da string
    char string[MAX_STRING];//pegar a linha do csv
    p_celula **celulas;
    scanf("%s %i %i",caminho,&colunas,&linhas);
    celulas=malloc(linhas*sizeof(p_celula**));
    for(int i=0;i<linhas;i++){
        celulas[i]=malloc(colunas*sizeof(p_celula*));
        for(int j=0;j<colunas;j++){
            celulas[i][j] = malloc(sizeof(Celula));
        }
    }
    FILE *arquivo;
    arquivo=fopen(caminho,"r");//leitura para popular dados locais
    char c;
    for(int j=0;j<linhas;j++){
        fscanf(arquivo,"%[^\n]%c",string, &c);
        celula=strtok(string,",");
        if(verificarConstante(celula)) {
            celulas[j][0]->expressao=NULL;
            celulas[j][0]->calculado=1;
            celulas[j][0]->valor=atoi(celula);
        }
        else{
            celulas[j][0]->expressao=tokenizar(celula);
            celulas[j][0]->calculado=0;//nn setar valor para setar depois
        }
        for(int i=1;i<colunas;i++){
            celula=strtok(NULL,",");//acessar os outros valores
            if(verificarConstante(celula)) {
                celulas[j][i]->expressao=NULL;
                celulas[j][i]->calculado=1;
                celulas[j][i]->valor=atoi(celula);
            }
            else{
                celulas[j][i]->expressao=tokenizar(celula);
                celulas[j][i]->calculado=0;
            }
        }
    }
    fclose(arquivo);
    /*agora, realizar as tarefas que o código nos manda*/
    int pos_linha,pos_coluna,novo_valor;
    char operacao;//char de entrada
    char destino[MAX_CELULA];
    while(scanf("%c", &operacao)!=EOF){
        if(operacao=='G'){
            scanf("%s",destino);
            pos_coluna=(int) destino[0] -65; //65 devido tabela ASCII do caractere'A'
            pos_linha=atoi(destino+1)-1;//coluna
            char **dependencias = malloc(sizeof(char *) * linhas * colunas);
            dependencias[0] = destino;
            if(celulas[pos_linha][pos_coluna]->calculado==0){
                char *resultado = resolver_expressao(celulas,celulas[pos_linha][pos_coluna]->expressao,dependencias,1);
                printf("%s: %s\n", destino, resultado);
                if(resultado[0]=='#') {
                    celulas[pos_linha][pos_coluna]->valor = atoi(resultado);
                    celulas[pos_linha][pos_coluna]->calculado = 1;
                }
            }
            else{
                printf("%s: %i\n", destino, celulas[pos_linha][pos_coluna]->valor);
            }
            free(dependencias);
        }
        else if (operacao=='S'){
            scanf("%s %i ",destino,&novo_valor);
            pos_coluna=(int) destino[0] -65;
            pos_linha=atoi(destino+1)-1;
            printf("%s: %i -> %i\n",destino,celulas[pos_linha][pos_coluna]->valor,novo_valor);
            celulas[pos_linha][pos_coluna]->valor = novo_valor;
            celulas[pos_linha][pos_coluna]->expressao=NULL;
            celulas[pos_linha][pos_coluna]->calculado=1;
        }
        for(int j=0;j<linhas;j++){
            for(int i=0;i<colunas;i++){
                if(celulas[j][i]->expressao != NULL){//resetar as celulas já que mudou uma cte
                    celulas[j][i]->calculado = 0;
                }
            }
        }
    }
    //no final, reescrever csv modificado
    //escreverArquivo(colunas,linhas,celulas,caminho);
    //free para celulas
    for(int i=0;i<linhas;i++){
        for(int j=0;j<colunas;j++){
            if(celulas[i][j]->expressao!=NULL) {
                for(int k = 0;celulas[i][j]->expressao[k] != NULL; k++){
                    free(celulas[i][j]->expressao[k]);
                }
                free(celulas[i][j]->expressao);
            }
            free(celulas[i][j]);
        }
        free(celulas[i]);
    }
    free(celulas);
    return 0;
}