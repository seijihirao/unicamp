/*
 * NOME: Rodrigo Seiji Piubeli Hirao
 * RA: 186837
 * TURMA: R
 */

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "base.h"

typedef struct{
    string CID;
    string nome;
} Doenca;

typedef struct{
    int CRM;
    string nome;
} Medico;

typedef struct Consulta Consulta;

struct Consulta {
    string paciente;
    string data;
    Doenca *doenca;
    Medico *medico;
    Consulta *proxima;
};

/**
 * Retorna a doença de uma lista a partir de seu CID
 *
 * @param
 * * Doenca *doencas - lista de doenças
 * * int quant_doencas - quantidade de doenças na lista
 * * string CID
 *
 * @returns
 * * Doenca *doenca - apontador para a doença encontrada
 */
Doenca *getDoenca(Doenca *doencas, int quant_doencas, string CID);

/**
 * Retorna o médico de uma lista a partir de seu CRM
 *
 * @param
 * * Medico *medicos - lista de médicos
 * * int quant_medicos - quantidade de médicos na lista
 * * string CRM
 *
 * @returns
 * * Medico *medico - apontador para o médico encontrado
 */
Medico *getMedico(Medico *medicos, int quant_medicos, int CRM);

/**
 * Retorna a doença de uma lista a partir de seu nome
 *
 * @param
 * * Doenca *doencas - lista de doenças
 * * int quant_doencas - quantidade de doenças na lista
 * * string nome
 *
 * @returns
 * * Doenca *doenca - apontador para a doença encontrada
 */
Doenca *getDoencaByNome(Doenca *doencas, int quant_doencas, string nome);

/**
 * Retorna o médico de uma lista a partir de seu nome
 *
 * @param
 * * Medico *medicos - lista de médicos
 * * int quant_medicos - quantidade de médicos na lista
 * * string nome
 *
 * @returns
 * * Medico *medico - apontador para o médico encontrado
 */
Medico *getMedicoByNome(Medico *medicos, int quant_medicos, string nome);

/**
 * Adiciona consulta na lista
 *
 * @param
 * * Consulta consulta - elemento da lista circular de consultas
 * * string nome_cript - nome criptografado
 * * Data data
 * * Doenca *doenca - apontador para a doença
 * * Medico *medico - apontador para o medico
 * * int[2][2] matriz - matriz usada na criptografia
 */
void hospitalAdicionar(Consulta *consulta, string nome_cript, string data, Doenca *doenca, Medico *medico, int matriz[TAM_MATRIZ][TAM_MATRIZ]);

/**
 * Remove consulta da lista
 *
 * @param
 * * Consulta *consulta - elemento da lista circular de consultas
 * * string nome - nome descriptografado
 * * int[2][2] matriz - matriz usada na criptografia
 */
void hospitalRemover(Consulta *consulta, string nome, int matriz[TAM_MATRIZ][TAM_MATRIZ]);

/**
 * Muda a doença na consulta encontrada na lista
 *
 * @param
 * * Consulta *consulta - elemento da lista circular de consultas
 * * string nome - nome descriptografado
 * * Doenca *doenca - apontador para a doença
 * * int[2][2] matriz - matriz usada na criptografia
 */
void hospitalAlterarDiagnostico(Consulta *consulta, string nome, Doenca *doenca, int matriz[TAM_MATRIZ][TAM_MATRIZ]);

/**
 * Muda a data na consulta encontrada na lista
 *
 * @param
 * * Consulta *consulta - elemento da lista circular de consultas
 * * string nome - nome descriptografado
 * * Data data
 * * int[2][2] matriz - matriz usada na criptografia
 */
void hospitalAlterarData(Consulta *consulta, string nome, string data, int matriz[TAM_MATRIZ][TAM_MATRIZ]);

/**
 * Muda o médico na consulta encontrada na lista
 *
 * @param
 * * Consulta *consulta - elemento da lista circular de consultas
 * * string nome - nome descriptografado
 * * Medico *medico - apontador para o medico
 * * int[2][2] matriz - matriz usada na criptografia
 */
void hospitalAlterarMedico(Consulta *consulta, string nome, Medico *medico, int matriz[TAM_MATRIZ][TAM_MATRIZ]);


/**
 * Adiciona consulta na lista
 *
 * @param
 * * Consulta *consulta - apontador para o elemento da lista circular de consultas
 * * char letra_base - letra por onde se iniciará a lista
 * * int[2][2] matriz - matriz usada na criptografia
 *
 * @return
 * * Consulta *consulta
 */
Consulta *getConsultaBase(Consulta *consulta, char letra_base, int matriz[TAM_MATRIZ][TAM_MATRIZ]);

#endif
