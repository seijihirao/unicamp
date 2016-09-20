/**
 * NOME: RODRIGO SEIJI P. HIRAO
 * RA: 186837
 * TURMA: R
 */

#include <stdio.h>

#include "funcionarios.h"


/**
 * Define o melhor funcionário do mês.
 * A partir de sua produtividade relativa, de seu sarlário e de seu nível na hierarquia.
 *
 * @entrada
 * * 
 *
 * @saída
 * *
 */
int main(){ 
    Funcionario funcionarios[MAX_FUNCIONARIOS];

    int num_funcionarios = funcScan(funcionarios);
    int i = funcMelhorFuncionarioDoAno(funcionarios, num_funcionarios);
    
    printf("%s %.2lf\n", funcionarios[i].nome, funcionarios[i].indice_de_qualidade);

    return 0;
}
