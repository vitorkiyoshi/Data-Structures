#include <stdlib.h>
#include <string.h>
#define MAX_CELULA 3
#define MAX_CAMINHO 16
#define MAX_STRING 10000
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
p_celula adicionarConstante(p_lista raiz, int cte){

}
p_celula adicionarExpressao(p_lista raiz, char **exp){

}
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
char **tokenizar(char *expressao) {//cria tokens de expressão, ler celula
    int limite = strlen(expressao) ;
    int quantidade_tokens = 0;
    char *token = malloc(sizeof(char) *MAX_CELULA);
    int pos = 0;
    p_lista lista =NULL;
    raiz=lista;
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
    token[pos] = '\0';
    quantidade_tokens++;
    lista=adicionar(lista, token);
    char *tokens = malloc(sizeof(char) * quantidade_tokens);
    int i=0;
    while(lista!=NULL) {
        tokens[i]=lista->token;
        i++;
        lista=lista->proximo;
    }
    destruirLista(raiz);
    return tokens;
}
char* resolver_expressao(p_celula **celulas, char **expressao, char **dependencias, int quantidade_dependencias) {/*resolver uma expressão apresentando vetor de celulas
 * */
    if(expressao[0][0]>='A'&& expressao[0][0]<='Z'){
        for(int i=0;i<quantidade_dependencias;i++) {
            if(strcmp(expressao[0],dependencias[i])==0){//verificação ciclicidade
                return "ERRO";
            }
            p_celula objetivo = celulas[expressao[0][0]-'A'][atoi(expressao[0]+1)-1];
            if(objetivo->calculado) {
                char *resultado = malloc(sizeof(char)*20);
                itoa(resultado,objetivo->valor,10);
                return resultado;
            } else {
                dependencias[quantidade_dependencias] = expressao[0];
                char *resultado = resolver_expressao(celulas, objetivo->expressao, dependencias, quantidade_dependencias +1);
                objetivo->valor = atoi(resultado);
                objetivo->calculado = 1;
            }
        }
    } else {
        char **primeiro_termo, **segundo_termo;
        primeiro_termo = expressao + 1;
        segundo_termo = expressao;
        int parenteses = 0;
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
        segundo_termo+=2;
        char *resultado_primeiro = resolver_expressao(celulas, primeiro_termo, dependencias, quantidade_dependencias);
        char *resultado_segundo = resolver_expressao(celulas, segundo_termo, dependencias, quantidade_dependencias);
        int result;
        if(operacao=='+'){//conversão de array para int para calculo das operações
            result = atoi(resultado_primeiro) + atoi(resultado_segundo);
        } else if(operacao=='-'){
            result = atoi(resultado_primeiro) - atoi(resultado_segundo);
        }
        free(resultado_primeiro);
        free(resultado_segundo);
        char *resultado = malloc(sizeof(char)*20);//no máximo 20 carac.
        itoa(resultado,result,10);
        return resultado;
    }
}
void destruir_lista(p_lista raiz){
    if(raiz != NULL) {
        destruir_lista(raiz->proximo);
        free(raiz);
    }
}
void escreverArquivo(int colunas, int linhas, p_celula **celulas){

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
    char operacao;//char de entrada
    char string[MAX_STRING];//pegar a linha do csv
    p_celula **celulas;
    scanf("%s %i %i",caminho,&linhas,&colunas);
    *celulas=malloc(linhas*sizeof(*p_celula));
    for(int i=0;i<linhas;i++){
        celulas[i]=malloc(colunas*sizeof(p_celula));
    }
    FILE *arquivo;
    *arquivo=fopen(caminho,"r");//leitura para popular dados locais
    for(int j=0;j<linhas;j++){
        fscanf("%s",string);
        celula=strtok(string,",");
        if(verificarConstante(celula)) {
            celulas[j][0]->expressao=NULL;
            celulas[j][0]->calculado=1;
            celulas[j][0]->valor=atoi(celula);
        }
        else{
            celulas[j][0]->expressao=tokenizar(celula);
            celulas[j][0]->calculado=1;
            celulas[j][0]->valor=NULL;//ainda nn foi calculado
        }
        for(int i=1;i<colunas;i++){
            celula=strtok(NULL,",");
            if(verificarConstante(celula)) {
                celulas[j][i]->expressao=NULL;
                celulas[j][i]->calculado=1;
                celulas[j][i]->valor=atoi(celula);
            }
            else{
                celulas[j][0]->expressao=tokenizar(celula);
                celulas[j][0]->calculado=0;
                celulas[j][0]->valor=NULL;//ainda nn foi calculado
            }
        }
    }
    fclose(arquivo);
    /*agora, realizar as tarefas que o código nos manda*/
    int pos_linha,pos_coluna;
    char destino[MAX_CELULA];
    while(scanf("%c", operacao)!=EOF){
        if(operacao='G'){
            scanf(" %s",destino);
        }
        else{

        }
    }
    return 0;
}