/*
 * NOME: Rodrigo Seiji Piubeli Hirao
 * RA: 186837
 * TURMA: R
 */

#include <stdio.h>

#include "base.h"

void cifraDeHill(string nome, string nome_cript, int matriz[TAM_MATRIZ][TAM_MATRIZ], short int criptografar){
    int i;
    for(i = 0; nome[i] != '\0'; i += TAM_MATRIZ){
        char par[TAM_MATRIZ];
        //montando par
        for(int k = 0; k < TAM_MATRIZ; k++){
            par[k] = nome[i+k];
        }
        //multiplicando
        multiplicarPorMatrizChave(par, matriz, criptografar == FALSE);
        //colocando par de volta no nome
        for(int k = 0; k < TAM_MATRIZ; k++){
            nome_cript[i+k] = par[k];
        }
    }
    nome_cript[i] = '\0';
}

void multiplicarPorMatrizChave(char par[TAM_MATRIZ], int matriz[TAM_MATRIZ][TAM_MATRIZ], short int usarMatrizInversa){
    
    int temp_par[TAM_MATRIZ];
    
    //transformar par em int
    for(int i = 0; i < TAM_MATRIZ; i++){
        temp_par[i] = (int)(par[i]) - 65;
    }
    
    //montando matriz
    if(usarMatrizInversa == TRUE){
        int det = matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
        int det_inverse = det;

        while(det_inverse % 26 != 1){
            det_inverse += det;
        }

        det_inverse /= det;

        int temp_matriz[TAM_MATRIZ][TAM_MATRIZ];
        temp_matriz[0][0] = ((+ matriz[1][1] * det_inverse) % 26 + 26) % 26;
        temp_matriz[0][1] = ((- matriz[0][1] * det_inverse) % 26 + 26) % 26;
        temp_matriz[1][0] = ((- matriz[1][0] * det_inverse) % 26 + 26) % 26;
        temp_matriz[1][1] = ((+ matriz[0][0] * det_inverse) % 26 + 26) % 26;
        matriz = temp_matriz;
    }
    
    //multiplicação
    for(int i = 0; i < TAM_MATRIZ; i++){
        temp_par[i] = ((matriz[i][0] * ((int)(par[0]) - 65)) + (matriz[i][1] * ((int)(par[1]) - 65)))%26;
    }
    
    //tranformar par em char
    for(int i = 0; i < TAM_MATRIZ; i++){
        par[i] = (char)(temp_par[i] + 65);
    }
}

