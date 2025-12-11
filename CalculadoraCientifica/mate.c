#include "mate.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


HistoricoEntrada historico[MAX_HISTORICO];
int indice_historico = 0; // Contagem atual de entradas

float somar(float a, float b) {
    return a + b;
}
float subtrair(float a, float b) {
    return a - b;
}
float multiplicar(float a, float b) {
    return a * b;
}
float dividir(float a, float b) {
    if(b == 0)
    {
        printf("Erro: Divisão por zero\n");
        return 0;
    }
    return a / b;
}
float fatorial(float *a){
    if (*a < 0 || *a != (int)*a) {
        printf("Erro: o fatorial funciona só com inteiros positivos ou zero.\n");
        return *a;
    }
    int num = (int)*a;
    float resultado = 1;
    for (int i = 1; i <= num; i++) {
        resultado *= i;
    }

    *a = resultado;

    return *a;
}

void atribuir_pi(float **a){
    if(a ==  NULL || *a == NULL){
        printf("Erro: ponteiro inválido ao atribuir PI.\n");
        return;
    }

    **a = 3.14159265358979323846f;
}

float euler(){
    return 2.7182818284;
}

float exponencial(float a){
    return exp(a);
}

float logaritmo(float a){
    if(a <= 0){
        printf("Erro: Logaritmo só funciona com números maiores que zero.\n");
        return 0;
    }
    return log(a);
}

void limpar_e_reexibir_cabecalho(float n1_atual) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("======== Bem vindo a Calculadora Cientifica ========\n");
    printf("+: Soma\n-: Subtração\n*: Multiplição\n/: Divisão\n^: Potência\nR: Raiz\n!: Fatorial\nS: Seno\nC: Cosseno\nT: Tangente\nP: Pi\nE: Euler\nX: Exponencial\nG: Logaritmo\nc: Limpar Tela\nH: Exibir Historico\nL: Limpar Historico\n0: Fechar Calculadora Cientifica\n");
    printf("----------------------------------------------------\n");
}

void carregar_historico_do_arquivo() {
    FILE *arquivo = fopen(NOME_ARQUIVO_HISTORICO, "r");
    char linha[100];
    indice_historico = 0; // Resetar o índice antes de carregar

    if (arquivo == NULL) {
        // Se o arquivo não existir, apenas iniciamos com o histórico vazio.
        printf("[INFO] Histórico vazio ou arquivo não encontrado. Iniciando novo histórico.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL && indice_historico < MAX_HISTORICO) {
        // Tenta ler 4 valores do arquivo
        if (sscanf(linha, "%f,%c,%f,%f",
                   &historico[indice_historico].operando1,
                   &historico[indice_historico].operador,
                   &historico[indice_historico].operando2,
                   &historico[indice_historico].resultado) == 4) {

            indice_historico++;
        }
    }

    printf("[INFO] %d entradas de histórico carregadas da última sessão.\n", indice_historico);
    fclose(arquivo);
}

void salvar_historico_no_arquivo() {
    // Abre o arquivo em modo de escrita ("w" - write) para sobrescrever o conteúdo
    FILE *arquivo = fopen(NOME_ARQUIVO_HISTORICO, "w");

    if (arquivo == NULL) {
        perror("Erro ao salvar o histórico no arquivo");
        return;
    }

    for (int i = 0; i < indice_historico; i++) {
        fprintf(arquivo, "%.2f,%c,%.2f,%.2f\n",
                historico[i].operando1,
                historico[i].operador,
                historico[i].operando2,
                historico[i].resultado);
    }

    fclose(arquivo);
}

void adicionar_na_memoria(float n1, char op, float n2, float resultado) {
    if (indice_historico < MAX_HISTORICO) {
        historico[indice_historico].operando1 = n1;
        historico[indice_historico].operador = op;
        historico[indice_historico].operando2 = n2;
        historico[indice_historico].resultado = resultado;
        indice_historico++;
    } else {
        printf("[Aviso] Histórico de memória cheio. Não foi possível adicionar nova entrada.\n");
    }
}

void exibir_historico_da_memoria() {
    printf("\n==== HISTÓRICO DE OPERAÇÕES (MEMÓRIA) (%d de %d) ====\n", indice_historico, MAX_HISTORICO);
    if (indice_historico == 0) {
        printf("O histórico está vazio.\n");
        printf("====================================================\n");
        return;
    }

    for (int i = 0; i < indice_historico; i++) {
        printf("%d. %.2f %c %.2f = %.2f\n",
            i + 1,
            historico[i].operando1,
            historico[i].operador,
            historico[i].operando2,
            historico[i].resultado
        );
    }
    printf("====================================================\n");
}

void limpar_historico_da_memoria() {
    indice_historico = 0;
    printf("[INFO] Histórico de operações na memória limpo.\n");
}
