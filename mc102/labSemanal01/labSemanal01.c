/**
 * NOME: Rodrigo Seiji Piubeli Hirao
 * RA: 186837
 * TURMA: R
 */

#include <stdio.h>

/**
 * Calcular nova data a partir de uma data já existente e uma quantidades de dias restantes 
 * (dias que serão fornecidos na base 6 e deverão ser transformados para a base 10 antes de
 * somados à data) além do formato do calendário do planeta (dias por mês e mêses por ano)
 *
 * @entrada
 * * data {Data} data inicial no formato {{dia}}/{{mes}}/{{ano}}
 * * * dia {int} dia do mês (menor que 10^4)
 * * * mes {int} mês do ano (menor que 10^4)
 * * * ano {int} ano (menor que 10^4)
 * * N {int} quantidade de dias por mês
 * * M {int} quantidade de mêses por ano
 * * X {uint} dias para adicionar (na base 6) (máximo 8 dígitos)
 *
 * @saída
 * * data {Data} nova data após a adição dos dias na base 10
 */
int main(){
    
    //Declaração de variáveis de entrada
    int dia, mes, ano, N, M, X;
    
    //Comunicação com o usuário (Entrada)
    scanf("%d/%d/%d %d %d %d", &dia, &mes, &ano, &N, &M, &X);

    /*
     * Convertendo da base 6 para a base 10
     *
     * * Como o número tem, no máximo 8 dígitos, seu valor máximo será 55555555
     * * Então 6⁷ será a maior potência necessária
     * * 
     * * O número será quebrado em dígitos que serão multiplicados 
     * * pela potência devida de 6 e, então, somados ao resultado
     */
    
    //Declaração de variáveis de conversão
    int X_b10 = 0;
    
    //Conversão
    X_b10 += (X / 10000000) * 6*6*6*6*6*6*6;
    X = X % 10000000;
    X_b10 += (X / 1000000) * 6*6*6*6*6*6;
    X = X % 1000000;
    X_b10 += (X / 100000) * 6*6*6*6*6;
    X = X % 100000;
    X_b10 += (X / 10000) * 6*6*6*6;
    X = X % 10000;
    X_b10 += (X / 1000) * 6*6*6;
    X = X % 1000;
    X_b10 += (X / 100) * 6*6;
    X = X % 100;
    X_b10 += (X / 10) * 6;
    X = X % 10;
    X_b10 += X;

    /*
     * Soma do {{X}} com a data
     */
    
    //Declaração de variáveis de saída
    int r_dia, r_mes, r_ano;

    //Conta
    r_dia = (dia + X_b10 - 1) % N + 1;
    r_mes = (mes + ((dia + X_b10 - 1)/N) - 1) % M + 1;
    r_ano = ano + ((mes + ((dia + X_b10 - 1)/N) - 1) / M);
    
    //Comunicação com o usuário (Saída)
    printf("%d/%d/%d\n", r_dia, r_mes, r_ano);
    
    return 0;
}

