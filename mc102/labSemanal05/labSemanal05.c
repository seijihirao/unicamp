/*
 * NOME: Rodrigo Seiji Piubeli Hirao
 * RA: 186837
 * TURMA: R
 */

#include <stdio.h>
#include <math.h>

#define NUM_PESSOAS 40
#define TAM_STRING 200

typedef char string[TAM_STRING];

//data
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

//pessoa
typedef struct {
    string nome;
    Data nascimento;
    char sexo;
    char preferencia_sexual;
    int quant_pessoas_boa_afinidade;
} Pessoa;

//aresta do grafo
typedef struct {
    Pessoa *pessoa1;
    Pessoa *pessoa2;
    double afinidade;
} Aresta;

//grafo
typedef struct {
    Pessoa vertices[NUM_PESSOAS];
    Aresta arestas[((NUM_PESSOAS - 1) * NUM_PESSOAS)/2];

    int num_vertices;
    int num_arestas;
} Grafo;

//
typedef struct {
    Pessoa *pessoa;
    char codNome[5];
    char codNasc[4];
    double pesoAresta;
    double sintonia;
} Sintonia;

/*
 * Ler todas as pessoas e montar o grafo delas
 *
 * @entrada
 * * Grafo *grafo - grafo contendo as pessoas e suas afinidades
 */
void readPessoas(Grafo *grafo);

/*
 * Procurar vértice com mais incidências de arestas no grafo
 *
 * @entrada
 * * Grafo grafo - grafo a ser lido
 *
 * @saida
 * * int posicao - posição do vértice com maior incidência no grafo lido
 */
Pessoa* procurarPessoaMaisPop(Grafo *grafo);

/*
 * Cria lista de sintonias
 *
 * @entrada
 * * Sintonia *sintonias
 * * Grafo *grafo
 * * Pessoa *pessoaMaisPop
 */
int inicializarSintonia(Sintonia *sintonias, Grafo *grafo, Pessoa *pessoaMaisPop);

/*
 * Codifica o nome com Soundex
 *
 * @entrada
 * * Sintonia *sintonias
 * * int num_sintonias
 */
void gerarSoundex(Sintonia *sintonias, int num_sintonias);

/*
 * Codifica o o aniversária com numerologia
 *
 * @entrada
 * * Sintonia *sintonias
 * * int num_sintonias
 * * Data data_atual
 */
void gerarNumeroData(Sintonia *sintonias, int num_sintonias, Data data_atual);

/*
 * Gera o valor da sintonia a partir da média ponderada dos valores anteriormente gerados
 *
 * @entra
 * * Sintonia *sintonias
 * * int num_sintonias
 */
void gerarSintonia(Sintonia *sintonias, int num_sintonias);

/*
 * Compara similaridade entre 2 strings, retornando o número de caracteres iguais
 *
 * @entrada
 * * string str1
 * * string str2
 *
 * @saida
 * * double num_ocorrencias - 0.0~1.0 
 */
double strsim(string str1, string str2);

/*
 * Calcula média geométrica entre 2 números (número 1 * número 2)^(1/2)
 *
 * @entrada
 * * double numero1
 * * double numero2
 *
 * @saida
 * * double resultado - mérdia geométrica dos 2 números
 */
double mediaGeometrica(double numero1, double numero2);

/*
 * Analizar dados do questionário de alunos de uma turma e analizar o aluno que tem maior sintonia com o aluno mais popular.
 *
 * @entrada
 * * Data data_atual - data atual
 * * int num_pessoas - número de pessoas
 * * [Pessoa] pessoas - lista de pessoas
 *
 * @saida
 * * Pessoa pessoa_mais_popular - pessoa mais popular da turma
 * * Pessoa pessoa_mais_sintonia - pessoa da turma com maior sintonia com a pessoa mais popular
 */
int main(){
    
    Data data_atual;
    scanf("%d/%d/%d\n", &data_atual.dia, &data_atual.mes, &data_atual.ano);

    Grafo grafo;
    readPessoas(&grafo);

    Pessoa *pessoaMaisPop = procurarPessoaMaisPop(&grafo);
    
    /*
     * Cálculo das sintonias
     */
    Sintonia sintonias[NUM_PESSOAS];
    
    int num_sintonias = inicializarSintonia(sintonias, &grafo, pessoaMaisPop);

    gerarSoundex(sintonias, num_sintonias);
    gerarNumeroData(sintonias, num_sintonias, data_atual);
    gerarSintonia(sintonias, num_sintonias);

    int pos_my_love;
    double maior_sintonia = 0;
    for(int i = 1; i < num_sintonias; i++){
        if(sintonias[i].sintonia > maior_sintonia){
            pos_my_love = i;
            maior_sintonia = sintonias[i].sintonia;
        }
    }
    
    //The end
    printf("%s combina com %s com %.2lf de sintonia s2\n", sintonias[0].pessoa->nome, sintonias[pos_my_love].pessoa->nome, sintonias[pos_my_love].sintonia);

    return 0;
}

/*
 * Functions
 */

void readPessoas(Grafo *grafo){

    scanf("%d\n", &(grafo->num_vertices));
    
    //Criando os vértices e a matriz temporária
    double temp_aresta[grafo->num_vertices][grafo->num_vertices];
    for(int i = 0; i < grafo->num_vertices; i++){
        scanf(" %[^\n]s\n", grafo->vertices[i].nome);
        scanf("%d/%d/%d %c %c\n", 
            &(grafo->vertices[i].nascimento.dia), 
            &(grafo->vertices[i].nascimento.mes), 
            &(grafo->vertices[i].nascimento.ano), 
            &(grafo->vertices[i].sexo), 
            &(grafo->vertices[i].preferencia_sexual)
            );
        grafo->vertices[i].quant_pessoas_boa_afinidade = 0;
        for(int j = 0; j < grafo->num_vertices; j++){
            if(j == i){
                continue;
            }
            scanf("%lf", &temp_aresta[i][j]);
        }
    }
    
    //Criando arestas a partir da matriz temporária
    grafo->num_arestas = 0;
    for(int i = 0; i < grafo->num_vertices; i++){
        for(int j = 0; j < grafo->num_vertices; j++){
            if(i < j){
                double afinidade = mediaGeometrica(temp_aresta[i][j], temp_aresta[j][i]);
                if(afinidade >= 5){
                    grafo->arestas[grafo->num_arestas].pessoa1 = &grafo->vertices[i];
                    grafo->arestas[grafo->num_arestas].pessoa2 = &grafo->vertices[j];
                    grafo->arestas[grafo->num_arestas].afinidade = afinidade;
                    grafo->vertices[i].quant_pessoas_boa_afinidade++;
                    grafo->vertices[j].quant_pessoas_boa_afinidade++;
                    grafo->num_arestas++;
                }
            }
        }
    }
}

Pessoa* procurarPessoaMaisPop(Grafo *grafo){
    Pessoa *posicao;
    int maior_valor = 0;
    for(int i = 0; i < grafo->num_vertices;  i++){
        if(grafo->vertices[i].quant_pessoas_boa_afinidade > maior_valor){
            posicao = &grafo->vertices[i];
            maior_valor = grafo->vertices[i].quant_pessoas_boa_afinidade;
        }
    }
    return posicao;
}

int inicializarSintonia(Sintonia *sintonias, Grafo *grafo, Pessoa *pessoaMaisPop){
    sintonias[0].pessoa = pessoaMaisPop;
    
    int cont_sintonias = 1;
    for(int i = 0; i < grafo->num_arestas; i++){
        if(pessoaMaisPop == grafo->arestas[i].pessoa1 && grafo->arestas[i].pessoa1->sexo == grafo->arestas[i].pessoa2->preferencia_sexual){
            sintonias[cont_sintonias].pessoa = grafo->arestas[i].pessoa2;
            sintonias[cont_sintonias].pesoAresta = grafo->arestas[i].afinidade;
            cont_sintonias++;
        }
        else if(pessoaMaisPop == grafo->arestas[i].pessoa2 && grafo->arestas[i].pessoa2->sexo == grafo->arestas[i].pessoa1->preferencia_sexual){
            sintonias[cont_sintonias].pessoa = grafo->arestas[i].pessoa1;
            sintonias[cont_sintonias].pesoAresta = grafo->arestas[i].afinidade;
            cont_sintonias++;
        }
    }
    return cont_sintonias;
}

void gerarSoundex(Sintonia *sintonias, int num_sintonias){
    string temp_nome;
    for(int i = 0; i < num_sintonias; i++){
        short int jailbait = 0;
        //we need hashmaps pls
        for(int j = 0;;j++){
            switch(sintonias[i].pessoa->nome[j]){
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                case 'y':
                case 'h':
                case 'w':
                case 'A':
                case 'E':
                case 'I':
                case 'O':
                case 'U':
                case 'Y':
                case 'H':
                case 'W':
                    temp_nome[j] = '0';
                    break;
                case 'g':
                case 'j':
                case 'G':
                case 'J':
                    temp_nome[j] = '1';
                    break;
                case 's':
                case 'z':
                case 'x':
                case 'S':
                case 'Z':
                case 'X':
                    temp_nome[j] = '2';
                    break;
                case 'c':
                case 'k':
                case 'q':
                case 'C':
                case 'K':
                case 'Q':
                    temp_nome[j] = '3';
                    break;
                case 'b':
                case 'p':
                case 'B':
                case 'P':
                    temp_nome[j] = '4';
                    break;
                case 'm':
                case 'n':
                case 'M':
                case 'N':
                    temp_nome[j] = '5';
                    break;
                case 'd':
                case 't':
                case 'D':
                case 'T':
                    temp_nome[j] = '6';
                    break;
                case 'f':
                case 'v':
                case 'F':
                case 'V':
                    temp_nome[j] = '7';
                    break;
                case 'l':
                case 'L':
                    temp_nome[j] = '8';
                    break;
                case 'r':
                case 'R':
                    temp_nome[j] = '9';
                    break;
                case ' ':
                case '\n':
                case '\0':
                default:
                    temp_nome[j] = '\0';
                    jailbait = 1;
                    break;
            }
            if(jailbait){
                break;
            }
        }
        int j = 1;
        sintonias[i].codNome[0] = temp_nome[0];
        for(int full_j = 1; j < 4; full_j++){
            if(temp_nome[full_j] == '\0'){
                break;
            }
            
            if(temp_nome[full_j] != temp_nome[full_j-1] && temp_nome[full_j] != '0'){
                sintonias[i].codNome[j] = temp_nome[full_j];
                j++;
            }
        }
        for(;j < 4; j++){
            sintonias[i].codNome[j] = '0';
        }
        sintonias[i].codNome[0] = sintonias[i].pessoa->nome[0];
        for(j = 0; j < 4; j++){
            for(int k = 1; j+k < 4 && sintonias[i].codNome[j] == sintonias[i].codNome[j+k]; k++){
                sintonias[i].codNome[j+k] = '0';
            }
        }
        sintonias[i].codNome[4] = '\0';
    }
}

void gerarNumeroData(Sintonia *sintonias, int num_sintonias, Data data_atual){
    for(int i = 0; i < num_sintonias; i++){
        Data nasc = sintonias[i].pessoa->nascimento;
        int soma_data = nasc.dia + nasc.mes + ((nasc.ano/1000) + ((nasc.ano%1000)/100) + ((nasc.ano%100)/10) + (nasc.ano%10));
        while(soma_data > 9){
            soma_data = (soma_data/10) + (soma_data%10);
        }
        int idade = (data_atual.ano - nasc.ano) - 1;
        if(nasc.mes < data_atual.mes  || (nasc.mes == data_atual.mes && nasc.dia <= data_atual.dia)){
            idade++;
        }
        while(idade > 99){
            idade /= 10;
        }
        if(idade > 9){
            sprintf(sintonias[i].codNasc, "%1d%2d", soma_data, idade);
        }else {
            sprintf(sintonias[i].codNasc, "%1d0%1d", soma_data, idade);
        }
    }
}

void gerarSintonia(Sintonia *sintonias, int num_sintonias){
    for(int i = 1; i < num_sintonias; i++){
        sintonias[i].sintonia = (
            (3*strsim(sintonias[0].codNome, sintonias[i].codNome)) + 
            (5*strsim(sintonias[0].codNasc, sintonias[i].codNasc)) +
            (2*sintonias[i].pesoAresta)/10
            )/10;
    }
}

double strsim(string str1, string str2){
    double cont_ocorrencias = 0, cont_total = 0;
    for(int i = 0; ; i++){
        if(str1[i] == '\0' || str2[i] == '\0'){
            break;
        }
        if(str1[i] == str2[i]){
            cont_ocorrencias++;
        }
        cont_total++;
    }
    return cont_ocorrencias/cont_total;
}

double mediaGeometrica(double numero1, double numero2){
    return sqrt((numero1 * numero2));
}
