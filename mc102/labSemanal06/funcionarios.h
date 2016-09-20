#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#define MAX_FUNCIONARIOS 100
#define TAMANHO_MAX_NOME 30

typedef char string[TAMANHO_MAX_NOME];

/**
 * Struct de funcionário
 */
typedef struct Funcionario Funcionario;

struct Funcionario{
    string nome;
    int produtividade_absoluta;
    double produtividade_relativa;
    double salario;
    double salario_relativo;
    double indice_de_qualidade;
    Funcionario *chefe;
    Funcionario *(subordinados[MAX_FUNCIONARIOS-1]);
    int num_subordinados;
    int nivel_hierarquico;
};

/**
 * Popular os funcionarios e preencher a hierarquia
 *
 * @param
 * * Funcionario funcionarios[] - lista de funcionários
 *
 * @return
 * * int num_funcionarios - número de funcionários lidos
 */
int funcScan(Funcionario funcionarios[MAX_FUNCIONARIOS]);

/**
 * Procurar o funcionario na lista pelo nome
 * 
 * @param
 * * Funcionario funcionarios[] - lista de funcionários
 * * int num_funcionarios - número de funcionários na lista
 * * string nome - nome do funcionário
 *
 * @return
 * * Funcionario *funcionario - apontador para funcionário encontrado
 */
Funcionario *funcProcurar(Funcionario funcionarios[MAX_FUNCIONARIOS], int num_funcionarios, string nome);

/**
 * Calcular produtividade relativa e preenchê-las no funcionário
 * 
 * @param
 * * Funcionario *chefe - apontador para o funcionário chefe
 */
void funcCalcularProdutividadeRelativa(Funcionario *chefe);

/**
 * Calcular nível hierárquico atial dos funcionários e preenchê-las no funcionário
 * 
 * @param
 * * Funcionario *chefe - apontador para o funcionário chefe
 * * int nivel - nivel hierárquico atual
 */
void funcCalcularNivelHierarquico(Funcionario *chefe, int nivel);

/**
 * Calcular salário do relativo ao salário do chefe
 * 
 * @param
 * * Funcionario *chefe - apontador para o funcionário chefe
 * * double salario_anterior - salário anterior
 */
void  funcCalcularSalarioRelativo(Funcionario *chefe, double salario_anterior);

/**
 * Calcular salário do relativo ao salário do chefe
 * 
 * @param
 * * Funcionario *chefe - apontador para o funcionário chefe
 *
 * @return
 * * double salario - salário encontrado
 */
double  funcCalcularSalarioChefe(Funcionario *chefe);

/**
 * Calcular índice de qualidade dos funcionários e preenchê-las no funcionário
 * 
 * @param
 * * Funcionario funcionarios[] - lista de funcionários
 * * int num_funcionarios - número de funcionários na lista
 * * int fator
 */
void funcCalcularIndiceDeQualidade(Funcionario funcionarios[MAX_FUNCIONARIOS], int num_funcionarios, int fator);

/**
 * Procurar o funcionario com maior índice de qualidade
 * 
 * @param
 * * Funcionario funcionarios[MAX_FUNCIONARIOS] - lista de funcionários
 * * int num_funcinarios - número de funcionários na lista
 *
 * @return
 * * int pos_funcionario - posição na lista do melhor funcionário encontrado
 */
int funcMelhorFuncionarioDoAno(Funcionario funcionarios[MAX_FUNCIONARIOS], int num_funcionarios);

#endif
