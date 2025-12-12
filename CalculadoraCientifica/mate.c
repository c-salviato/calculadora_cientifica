#include "mate.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


HistoricoEntrada *historico = NULL;
int indice_historico = 0;
int capacidade_historico = 0;

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


//funcoes extras(ainda importantes)

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

void inicializar_historico_dinamico() {

    historico = (HistoricoEntrada *)malloc(MAX_HISTORICO * sizeof(HistoricoEntrada));
    if (historico == NULL) {
        perror("Falha ao alocar memoria para o historico");
        exit(EXIT_FAILURE);
    }

    capacidade_historico = MAX_HISTORICO;
    carregar_historico_do_arquivo();
    printf("[INFO] Historico dinamico inicializado com capacidade para %d entradas.\n", capacidade_historico);
}

void liberar_historico_dinamico() {
    if (historico != NULL) {
        free(historico);
        historico = NULL;
        indice_historico = 0;
        capacidade_historico = 0;
        printf("[INFO] Memória do histórico liberada.\n");
    }
}


void carregar_historico_do_arquivo() {
    FILE *arquivo = fopen(NOME_ARQUIVO_HISTORICO, "r");
    char linha[100];
    indice_historico = 0;

    if (arquivo == NULL) {
        printf("[INFO] Historico vazio ou arquivo nao encontrado. Iniciando novo historico.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL && indice_historico < capacidade_historico) {

        if (sscanf(linha, "%lf,%c,%lf,%lf",
                     &historico[indice_historico].operando1,
                     &historico[indice_historico].operador,
                     &historico[indice_historico].operando2,
                     &historico[indice_historico].resultado) == 4) {

            indice_historico++;
        }
    }

    printf("[INFO] %d entradas de historico carregadas da ultima sessao.\n", indice_historico);
    fclose(arquivo);
}

void salvar_historico_no_arquivo() {

    FILE *arquivo = fopen(NOME_ARQUIVO_HISTORICO, "w");

    if (arquivo == NULL) {
        perror("Erro ao salvar o historico no arquivo");
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

    if (indice_historico >= capacidade_historico) {

        int nova_capacidade = capacidade_historico * 2;
        HistoricoEntrada *temp = (HistoricoEntrada *)realloc(historico, nova_capacidade * sizeof(HistoricoEntrada));

        if (temp == NULL) {
            printf("ERRO: Falha ao expandir a memoria do historico.\n");
            return;
        }

        historico = temp;
        capacidade_historico = nova_capacidade;
        printf("[INFO] Capacidade do historico expandida para %d entradas.\n", capacidade_historico);
    }

    double n2_para_salvar = n2;

    if (op == '!' || op == 'S' || op == 'C' || op == 'T' || op == 'X' || op == 'G') {
        n2_para_salvar = VALOR_NULO_HISTORICO;
    }

    historico[indice_historico].operando1 = n1;
    historico[indice_historico].operador = op;
    historico[indice_historico].operando2 = n2_para_salvar;
    historico[indice_historico].resultado = resultado;
    indice_historico++;
}

void exibir_historico_da_memoria() {
    printf("\n==== HISTORICO DE OPERACOES (MEMORIA) (%d de %d) ====\n", indice_historico, capacidade_historico);
    if (indice_historico == 0) {
        printf("O histórico está vazio.\n");
        printf("====================================================\n");
        return;
    }

    for (int i = 0; i < indice_historico; i++) {

        if (historico[i].operando2 == VALOR_NULO_HISTORICO) {

            printf("%d. %c(%.5lf) = %.5lf\n",
                i + 1,
                historico[i].operador,
                historico[i].operando1,
                historico[i].resultado
            );

        } else {

            printf("%d. %.5lf %c %.5lf = %.5lf\n",
                i + 1,
                historico[i].operando1,
                historico[i].operador,
                historico[i].operando2,
                historico[i].resultado
            );
        }
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

double logaritmo(double a) {
    if (a <= 0.0) {
        printf("Erro: Logaritmo so funciona com numeros maiores que zero.\n");
        return 0.0;
    }

    int max_iteracoes = 100;

    if (a == 1.0){
        return 0.0;
    }
    double x = a;
    double log_result = 0.0;

    while (x > 2.0) {
        x /= 2.0;
        log_result += 0.6931471805599453;
    }

    double z = (x - 1.0) / (x + 1.0);
    double termo = z;
    double z_quadrado = z * z;
    double soma_serie = z;

    for (int n = 3; n < max_iteracoes; n += 2) {
        termo *= z_quadrado;
        soma_serie += termo / (double)n;
    }

    log_result += 2.0 * soma_serie;

    return log_result;
}

double fatorial_custom(int n) {
    if (n < 0) return 0.0;
    if (n == 0 || n == 1) return 1.0;

    double resultado = 1.0;
    for (int i = 2; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

double exponencial(double a) {

    int num_termos = 15;
    double resultado = 0.0;

    if (a > 700.0) return 1.0e+300;

    for (int n = 0; n < num_termos; n++) {
        double termo = pow(a, n) / fatorial_custom(n);
        resultado += termo;
    }

    return resultado;
}
