/*
 * NOME: Rodrigo Seiji Piubeli Hirao
 * RA: 186837
 * TURMA: R
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "hospital.h"


/**
 *
 * Organizar o registro de mpedicos, doenças e consultas de um hospital.
 * Criando-se, assim um CRUD que usa a cifra de Hill como criptografia.
 *
 */
int main(){
    /**
     * Doenças
     */
    Doenca *doencas;
    int quant_doencas;
    scanf("%d", &quant_doencas);
    doencas = (Doenca *)malloc(quant_doencas * sizeof(Doenca));

    for(int i = 0; i < quant_doencas; i++){
        scanf("%s %[^\n]s\n", (doencas+i)->CID, (doencas+i)->nome);
    }

    /**
     * Médicos
     */
    Medico *medicos;
    int quant_medicos;
    scanf("%d", &quant_medicos);
    medicos = (Medico *)malloc(quant_medicos * sizeof(Medico));

    for(int i = 0; i < quant_medicos; i++){
        scanf("%d %[^\n]s\n", &((medicos+i)->CRM), (medicos+i)->nome);
    }
    
    /**
     * Matriz
     */
    int matriz[TAM_MATRIZ][TAM_MATRIZ];
    for(int i = 0; i < TAM_MATRIZ; i++){
        for(int j = 0; j < TAM_MATRIZ; j++){
            scanf("%d", &matriz[i][j]);
        }
    }

    /**
     * Letra Base
     */
    char letra_base;
    scanf("\n%c", &letra_base);  
    
    /**
     * Operações
     */
    string operacao;
    Consulta *consulta;
    consulta = (Consulta *)malloc(sizeof(Consulta));
    consulta->paciente[0] = '\0';
    consulta->proxima = NULL;
    
    
    while(TRUE){
        scanf("%s", operacao);
        
        string nome;
        if(strcmp(operacao, "0") != 0){
            scanf("%s", nome);
        }
        
        if(strcmp(operacao, "add") == 0){
            string data;
            scanf("%s", data);
            string CID;
            scanf("%s", CID);
            int CRM;
            scanf("%d", &CRM);
            
            hospitalAdicionar(consulta, nome, data, getDoenca(doencas, quant_doencas, CID), getMedico(medicos, quant_medicos, CRM), matriz);
        }
        else if(strcmp(operacao, "rm") == 0){
            hospitalRemover(consulta, nome, matriz);
        }
        else if(strcmp(operacao, "altdiag") == 0){
            string doenca_nome;
            scanf(" %[^\n]s", doenca_nome);

            hospitalAlterarDiagnostico(consulta, nome, getDoencaByNome(doencas, quant_doencas, doenca_nome), matriz);
        }
        else if(strcmp(operacao, "altdata") == 0){
            string data;
            scanf(" %[^\n]s", data);

            hospitalAlterarData(consulta, nome, data, matriz);
        }
        else if(strcmp(operacao, "altmed") == 0){
            string medico_nome;
            scanf(" %[^\n]s", medico_nome);
            
            hospitalAlterarMedico(consulta, nome, getMedicoByNome(medicos, quant_medicos, medico_nome), matriz);
        }else{
            consulta = getConsultaBase(consulta, letra_base, matriz);
            break;
        }
    }
    
    string nome_base;
    strcpy(nome_base, consulta->paciente);

    do{
        string nome;
        cifraDeHill(consulta->paciente, nome, matriz, FALSE);
        printf("%s %s %s %d\n", nome, consulta->data, consulta->doenca->CID, consulta->medico->CRM);
        consulta = consulta->proxima;

    }while(strcmp(consulta->paciente, nome_base) != 0);
    
    free(doencas);
    free(medicos);
    free(consulta);

    return 0;
}

