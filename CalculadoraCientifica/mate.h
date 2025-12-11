#ifndef MATE_H
#define MATE_H
#include <stdio.h>
#include <stdlib.h>


#define NOME_ARQUIVO_HISTORICO "calculadora_historico.txt"
#define MAX_HISTORICO 100
typedef struct {
    float operando1;
    char operador;
    float operando2;
    float resultado;
} HistoricoEntrada;

//operacoes matematicas
float somar(float a, float b);
float subtrair(float a, float b);
float multiplicar(float a, float b);
float dividir(float a, float b);
float fatorial(float *a);
void atribuir_pi(float **a);
float euler();
float exponencial(float a);
float logaritmo(float a);

//funcoes extras
void limpar_e_reexibir_cabecalho(float n1_atual);

//historico
void carregar_historico_do_arquivo();
void salvar_historico_no_arquivo();
void adicionar_na_memoria(float n1, char op, float n2, float resultado);
void exibir_historico_da_memoria();
void limpar_historico_da_memoria();


#endif
