/*
 * NOME: Rodrigo Seiji P. Hirao
 * RA: 186837
 */

 #include <stdio.h>
 #include <math.h>
 #include <stdlib.h>

/**
 * Transforma os elementos de uma matriz triângular usando a fórmula z=(x-m)/d, 
 * onde x é um elemento da matriz, m é a média e d é o desvio-padrão de todos os valores na matriz.
 *
 * @param int cols - número de colunas
 * @param double** matriz - matriz triângular
 * 
 * @return double** matriz_result - matriz triângular com números formatados, e 12 casas
 */
 int main(){

    /*
     * Leitura dos dados
     */
    int cols = 0;
    scanf("%d", &cols);
    
    double **matriz = (double**)malloc(cols*sizeof(double*));
    double media = 0, soma = 0, soma_desvio = 0, desvio;
    
    int i, j;

    for(i = 0; i < cols; i++){
        *(matriz+i) = (double*)malloc((i+1)*sizeof(double));
        for(j = 0; j < i+1; j++){
            scanf("%lf", (*(matriz+i) + j));
            soma +=  *(*(matriz+i) + j); //aproveitando a leitura para acumular a soma total
        }
    }
    
    /*
     * Cálculos
     */

    //Cálculo da média
    media = soma / ((pow(cols, 2) + cols)/2); //cálculo da média
    
    //Cálculo do desvio padrão
    for(i = 0; i < cols; i++){
        for(j = 0; j < i+1; j++){
            soma_desvio += pow(*(*(matriz+i)+j) - media, 2);
        }
    }
    desvio = sqrt(soma_desvio / ((pow(cols, 2) + cols)/2));

    //Cálculo final
    for(i = 0; i < cols; i++){
        for(j = 0; j < i+1; j++){
            *(*(matriz+i)+j) = (*(*(matriz+i)+j) - media)/desvio;
        }
    }
    
    /*
     * Print dos valores recolhidos
     */
    
    for(i = 0; i < cols; i++){
        for(j = 0; j < i+1; j++){
            printf("%.12lf ", *(*(matriz+i)+j));
        }
        free(*(matriz+i));
        printf("\n");
    }
    free(matriz);
    printf("\n");
    printf("%.12lf %.12lf ", media, desvio);
    printf("\n");
    
    return 0;
 }
