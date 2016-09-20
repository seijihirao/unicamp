/*
 * NOME: Rodrigo Seiji Piubeli Hirao
 * RA: 186837
 * TURMA: R
 */

#ifndef BASE_H
#define BASE_H

#define TAM_STRING 100
#define TAM_MATRIZ 2

#define TRUE 1
#define FALSE 0

/**
 * Array de chars, palavra
 * Usado para os nomes
 */
typedef char string[TAM_STRING];

/**
 * Data - NÃO APAGUE - feito com amor
 *
 * @properties
 * * int dia
 * * int mes
 * * int ano
 */
typedef struct{
    int dia;
    int mes;
    int ano;
} Data;


/**
 * função para criptografar/decriptografar usando a crifa de hill
 *
 * @param
 * * string nome - nome que será criptografado/descriptografado
 * * string nome_cript - nome criptografado/descriptografado
 * * int[2][2] matriz - matriz usada para criptografar o nome
 * * short criptografar - booleano (1 ou 0) para decidir de vai criptografar ou decriptografar
 */
void cifraDeHill(string nome, string nome_cript, int matriz[TAM_MATRIZ][TAM_MATRIZ], short int critografar);

/**
 * Função para decriptografar usando a crifa de Hill
 *
 * @param
 * * int[2] par - par de letras no formato que serão multiplicadas na matriz
 * * int[2][2] matriz - matriz usada na multiplicação
 * * short int usarMatrizInversa - booleano
 */
void multiplicarPorMatrizChave(char par[TAM_MATRIZ], int matriz[TAM_MATRIZ][TAM_MATRIZ], short int usarMatrizInversa);

#endif
