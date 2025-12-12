#ifndef MATE_H
#define MATE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NOME_ARQUIVO_HISTORICO "calculadora_historico.txt"
#define MAX_HISTORICO 100
#define VALOR_NULO_HISTORICO -99999.0
typedef struct {
    double operando1;
    char operador;
    double operando2;
    double resultado;
} HistoricoEntrada;

//Variaveis Globais(para usar no historico)
extern HistoricoEntrada *historico;
extern int indice_historico;
extern int capacidade_historico; // Rastreia o tamanho real do array alocado


//operacoes matematicas
double somar(double a, double b);
double subtrair(double a, double b);
double multiplicar(double a, double b);
double dividir(double a, double b);
double fatorial(double *a);
double exponencial(double a);
double logaritmo(double a);

//funcoes extras
void limpar_e_reexibir_cabecalho(double n1_atual);
double input_valor();

//historico
void inicializar_historico_dinamico();
void liberar_historico_dinamico();
void carregar_historico_do_arquivo();
void salvar_historico_no_arquivo();
void adicionar_na_memoria(double n1, char op, double n2, double resultado);
void exibir_historico_da_memoria();
void limpar_historico_da_memoria();


#endif
