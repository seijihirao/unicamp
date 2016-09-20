#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base.h"
#include "hospital.h"

Doenca *getDoenca(Doenca *doencas, int quant_doencas, string CID){
    for(int i = 0; i < quant_doencas; i++){
        if(strcmp((doencas+i)->CID, CID) == 0){
            return doencas+i;
        }
    }
    return NULL;
}

Medico *getMedico(Medico *medicos, int quant_medicos, int CRM){
    for(int i = 0; i < quant_medicos; i++){
        if((medicos+i)->CRM == CRM){
            return medicos+i;
        }
    }
    return NULL;
}

Doenca *getDoencaByNome(Doenca *doencas, int quant_doencas, string nome){
    for(int i = 0; i < quant_doencas; i++){
        if(strcmp((doencas+i)->nome, nome) == 0){
            return doencas+i;
        }
    }
    return NULL;
}

Medico *getMedicoByNome(Medico *medicos, int quant_medicos, string nome){
    for(int i = 0; i < quant_medicos; i++){
        if(strcmp((medicos+i)->nome, nome) == 0){
            return medicos+i;
        }
    }
    return NULL;
}

void hospitalAdicionar(Consulta *consulta, string nome_cript, string data, Doenca *doenca, Medico *medico, int matriz[TAM_MATRIZ][TAM_MATRIZ]){
    if(consulta->paciente[0] == '\0'){
        //prineira consulta
        strcpy(consulta->paciente, nome_cript);
        strcpy(consulta->data, data);
        consulta->doenca = doenca;
        consulta->medico = medico;
    }else if(consulta->proxima == NULL){
        //segunda consulta
        Consulta *consulta_nova;
        consulta_nova = (Consulta *)malloc(sizeof(Consulta));

        strcpy(consulta_nova->paciente, nome_cript);
        strcpy(consulta_nova->data, data);
        consulta_nova->doenca = doenca;
        consulta_nova->medico = medico;
        consulta_nova->proxima = consulta;
        consulta->proxima = consulta_nova;
    }else{
        //demais consultas
        string nome_base;
        strcpy(nome_base, consulta->paciente);

        string paciente_nome_antes;
        string paciente_nome_depois;
        string paciente_nome;

        cifraDeHill(consulta->paciente, paciente_nome_antes, matriz, FALSE);
        cifraDeHill(consulta->proxima->paciente, paciente_nome_depois, matriz, FALSE);
        cifraDeHill(nome_cript, paciente_nome, matriz, FALSE); 

        while(!(
            (strcmp(paciente_nome_antes, paciente_nome) <= 0 && strcmp(paciente_nome_depois, paciente_nome) >= 0) ||
            (strcmp(paciente_nome_antes, paciente_nome) <= 0 && strcmp(paciente_nome_antes, paciente_nome_depois) >= 0) ||
            (strcmp(paciente_nome_depois, paciente_nome) >= 0 && strcmp(paciente_nome_antes, paciente_nome_depois) >= 0)
            )){
            consulta = consulta->proxima;
            cifraDeHill(consulta->paciente, paciente_nome_antes, matriz, FALSE);
            cifraDeHill(consulta->proxima->paciente, paciente_nome_depois, matriz, FALSE);
        }

        Consulta *consulta_nova;
        consulta_nova = (Consulta *)malloc(sizeof(Consulta));

        strcpy(consulta_nova->paciente, nome_cript);
        strcpy(consulta_nova->data, data);
        consulta_nova->doenca = doenca;
        consulta_nova->medico = medico;
        consulta_nova->proxima = consulta->proxima;
        consulta->proxima = consulta_nova;
    }
}

void hospitalRemover(Consulta *consulta, string nome, int matriz[TAM_MATRIZ][TAM_MATRIZ]){
    if(consulta->proxima == NULL){
        consulta->paciente[0] = '\0';
        return;
    }


    string paciente_nome_depois;

    cifraDeHill(consulta->proxima->paciente, paciente_nome_depois, matriz, FALSE);

    while(strcmp(paciente_nome_depois, nome) != 0){
        consulta = consulta->proxima;
        cifraDeHill(consulta->proxima->paciente, paciente_nome_depois, matriz, FALSE);
    }
    
    consulta->proxima = consulta->proxima->proxima;
}

void hospitalAlterarDiagnostico(Consulta *consulta, string nome, Doenca *doenca, int matriz[TAM_MATRIZ][TAM_MATRIZ]){
    string paciente_nome_atual;

    cifraDeHill(consulta->paciente, paciente_nome_atual, matriz, FALSE);

    while(strcmp(paciente_nome_atual, nome) != 0){
        consulta = consulta->proxima;
        cifraDeHill(consulta->paciente, paciente_nome_atual, matriz, FALSE);
    }
    
    consulta->doenca = doenca;
}

void hospitalAlterarData(Consulta *consulta, string nome, string data, int matriz[TAM_MATRIZ][TAM_MATRIZ]){
    string paciente_nome_atual;

    cifraDeHill(consulta->paciente, paciente_nome_atual, matriz, FALSE);

    while(strcmp(paciente_nome_atual, nome) != 0){
        consulta = consulta->proxima;
        cifraDeHill(consulta->paciente, paciente_nome_atual, matriz, FALSE);
    }
    
    strcpy(consulta->data, data);
}

void hospitalAlterarMedico(Consulta *consulta, string nome, Medico *medico, int matriz[TAM_MATRIZ][TAM_MATRIZ]){
    string paciente_nome_atual;

    cifraDeHill(consulta->paciente, paciente_nome_atual, matriz, FALSE);

    while(strcmp(paciente_nome_atual, nome) != 0){
        consulta = consulta->proxima;
        cifraDeHill(consulta->paciente, paciente_nome_atual, matriz, FALSE);
    }
    
    consulta->medico = medico;
}

Consulta *getConsultaBase(Consulta *consulta, char letra_base, int matriz[TAM_MATRIZ][TAM_MATRIZ]){
    string nome_base;
    strcpy(nome_base, consulta->paciente);
    
    string paciente_nome_antes;
    string paciente_nome_depois;

    cifraDeHill(consulta->paciente, paciente_nome_antes, matriz, FALSE);
    cifraDeHill(consulta->proxima->paciente, paciente_nome_depois, matriz, FALSE);

    while(!(paciente_nome_antes[0] < letra_base && paciente_nome_depois[0] >= letra_base) &&
        !(paciente_nome_antes[0] <= letra_base && strcmp(paciente_nome_antes, paciente_nome_depois) > 0) &&
        !(paciente_nome_depois[0] >= letra_base && strcmp(paciente_nome_antes, paciente_nome_depois) > 0)){
        consulta = consulta->proxima;
        cifraDeHill(consulta->paciente, paciente_nome_antes, matriz, FALSE);
        cifraDeHill(consulta->proxima->paciente, paciente_nome_depois, matriz, FALSE);
    }
    return consulta->proxima;
}

