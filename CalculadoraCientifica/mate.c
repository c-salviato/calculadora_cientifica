#include "mate.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


HistoricoEntrada historico[MAX_HISTORICO];
int indice_historico = 0; // Contagem atual de entradas

double somar(double a, double b) {
    return a + b;
}
double subtrair(double a, double b) {
    return a - b;
}
double multiplicar(double a, double b) {
    return a * b;
}
double dividir(double a, double b) {
    if(b == 0)
    {
        printf("Erro: Divisão por zero\n");
        return 0.0;
    }
    return a / b;
}
double fatorial(double *a){
    if (*a < 0 || *a != (int)*a) {
        printf("Erro: o fatorial funciona so com inteiros positivos ou zero.\n");
        return *a;
    }
    int num = (int)*a;
    double resultado = 1;
    for (int i = 1; i <= num; i++) {
        resultado *= i;
    }

    *a = resultado;

    return *a;
}

void atribuir_pi(double **a){
    if(a == NULL || *a == NULL){
        printf("Erro: ponteiro invalido ao atribuir PI.\n");
        return;
    }

    **a = 3.14159265358979323846;
}

double euler(){
    return 2.7182818284;
}

double logaritmo(double a){
    if(a <= 0){
        printf("Erro: Logaritmo so funciona com números maiores que zero.\n");
        return 0.0;
    }
    return log(a);
}

void limpar_e_reexibir_cabecalho(double n1_atual) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("======== Bem vindo a Calculadora Cientifica ========\n");
    printf("- Funcoes de Calculo -\n+: Soma\n-: Subtracao\n*: Multiplicacao\n/: Divisao\n^: Potencia\nR: Raiz\n!: Fatorial\nS: Seno\nC: Cosseno\nT: Tangente\nX: Exponencial\nG: Logaritmo\nc: Limpar Tela\nH: Exibir Historico\nL: Limpar Historico\n0: Fechar Calculadora Cientifica\n");
    printf("----------------------------------------------------\n");
    printf("- Valores Padrao -\npi: PI Grego\ne: Valor de Euler\n");
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

void adicionar_na_memoria(double n1, char op, double n2, double resultado) {
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
    printf("[INFO] Historico de operacoes na memoria limpo.\n");
}

double input_valor() {
    char str[50];

    scanf("%s", str);

    if (strcmp(str, "pi") == 0) return 3.141592653589793;
    if (strcmp(str, "e") == 0)  return 2.718281828459045;

    int pontos = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {

        if (str[i] == '-') {
            if (i != 0) {
                printf("Erro: Sinal negativo no meio do numero.\n");
                return 0.0;
            }
        }
        else if (str[i] == '.') {
            if (pontos > 0) {
                printf("Erro: Numero com multiplos pontos decimais.\n");
                return 0.0;
            }
            pontos++;
        }
        else if (str[i] < '0' || str[i] > '9') {
            printf("Erro: Entrada invalida ('%c' nao eh um numero).\n", str[i]);
            return 0.0;
        }
    }
    return atof(str);
}
