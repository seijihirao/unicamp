#include "funcionarios.h"

#include "mymath.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

int funcScan(Funcionario funcionarios[MAX_FUNCIONARIOS]){

    double total_salario;
    scanf("%lf", &total_salario);

    int fator_qualidade;
    scanf("%d", &fator_qualidade);

    int num_funcionarios;
    scanf("%d", &num_funcionarios);

    for(int i = 0; i < num_funcionarios; i++){
        scanf(" %[^ \n]s", funcionarios[i].nome);
        scanf("%d\n", &(funcionarios[i].produtividade_absoluta));
        funcionarios[i].chefe = NULL;
        funcionarios[i].num_subordinados = 0;

    }

    for(int i = 0; i < num_funcionarios - 1;  i++){
        string str_subordinado, str_chefe;
        scanf(" %[^ ]", str_subordinado);
        scanf(" %[^ \n]s\n", str_chefe);
        Funcionario *chefe = funcProcurar(funcionarios, num_funcionarios, str_chefe);
        Funcionario *subordinado = funcProcurar(funcionarios, num_funcionarios, str_subordinado);
        subordinado->chefe = chefe;
        chefe->subordinados[chefe->num_subordinados] = subordinado;
        chefe->num_subordinados++;
    }
    
    Funcionario *chefe;

    for(int i = 0; i < num_funcionarios; i++){
        if(funcionarios[i].chefe == NULL){
            chefe = &funcionarios[i];
            break;
        }
    }

    funcCalcularProdutividadeRelativa(chefe);
    funcCalcularNivelHierarquico(chefe, 1);
    funcCalcularSalarioRelativo(chefe, 0);
    chefe->salario = total_salario/funcCalcularSalarioChefe(chefe);
    for(int i = 0; i < num_funcionarios; i++){
        funcionarios[i].salario = chefe->salario*funcionarios[i].salario_relativo;
    }
    funcCalcularIndiceDeQualidade(funcionarios, num_funcionarios, fator_qualidade);

    return num_funcionarios;
}

Funcionario *funcProcurar(Funcionario funcionarios[MAX_FUNCIONARIOS], int num_funcionarios, string nome){
    for(int i = 0; i < num_funcionarios; i++){
        if(strcmp(funcionarios[i].nome, nome) == 0){
            return &funcionarios[i];
        }
    }
    return NULL;
}

void funcCalcularProdutividadeRelativa(Funcionario *chefe){
    
    if(chefe->num_subordinados == 0){
        chefe->produtividade_relativa = chefe->produtividade_absoluta;
        return;
    }

    double produtividade_relativa_subordinados = 0.0;

    for(int i = 0; i < chefe->num_subordinados; i++){
        funcCalcularProdutividadeRelativa(chefe->subordinados[i]);
        produtividade_relativa_subordinados += chefe->subordinados[i]->produtividade_relativa;
    }
    
    chefe->produtividade_relativa = (chefe->produtividade_absoluta + (produtividade_relativa_subordinados/chefe->num_subordinados))/2;
}

void funcCalcularNivelHierarquico(Funcionario *chefe, int nivel){
    chefe->nivel_hierarquico = nivel;

    for(int i = 0; i < chefe->num_subordinados; i++){
        funcCalcularNivelHierarquico(chefe->subordinados[i], nivel+1);
    }
}

void funcCalcularSalarioRelativo(Funcionario *chefe, double salario_anterior){
    if(chefe->nivel_hierarquico == 1){
        chefe->salario_relativo = 1;
    }else{
        chefe->salario_relativo = salario_anterior*(chefe->chefe->num_subordinados/(chefe->chefe->num_subordinados+1.0));
    }

    for(int i = 0; i < chefe->num_subordinados; i++){
        funcCalcularSalarioRelativo(chefe->subordinados[i], chefe->salario_relativo);
    }
}

double  funcCalcularSalarioChefe(Funcionario *chefe){
    double total = chefe->salario_relativo;
    for(int i = 0; i < chefe->num_subordinados; i++){
        total += funcCalcularSalarioChefe(chefe->subordinados[i]);
    }
    return total;
}

void funcCalcularIndiceDeQualidade(Funcionario funcionarios[MAX_FUNCIONARIOS], int num_funcionarios, int fator){
    for(int i = 0; i < num_funcionarios; i++){
        funcionarios[i].indice_de_qualidade = fator * (iteratedLog((double)funcionarios[i].nivel_hierarquico) + 1) * (funcionarios[i].produtividade_relativa/(log2(funcionarios[i].salario)));
    }
}

int funcMelhorFuncionarioDoAno(Funcionario funcionarios[MAX_FUNCIONARIOS], int num_funcionarios){
    int pos_melhor;
    double maior_indice = 0.0;
    for(int i = 0; i < num_funcionarios; i++){
        if(funcionarios[i].indice_de_qualidade > maior_indice){
            maior_indice = funcionarios[i].indice_de_qualidade;
            pos_melhor = i;
        }
    }
    return pos_melhor;
}
