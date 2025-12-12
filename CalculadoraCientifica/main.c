#include <stdio.h>
#include "mate.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(){


    char opc;
    double n1, n2, res;

    limpar_e_reexibir_cabecalho(0.0);

    printf("=== TUTORIAL BASICO ===\n");
    printf("A calculadora funciona de forma sequencial. Explicacao: Voce digita o primeiro valor, depois escolhe uma das opcoes acima, depois outro valor e o resultado vai se acumulando!\n");
    printf("Pressione ENTER depois de cada opcao ou valor inserido!\n");
    printf("- (Apos limpar a tela com a opcao 'c' o tutorial some!) -\n");

    printf("----------------------------------------------------\n");

    n1 = input_valor();

    do{
        scanf(" %c",&opc);

        int precisa_de_n2 = 1;
        double n1_ini = n1;

        if(opc != '0' && opc != 'c' && opc != 'H' && opc != 'L' && opc != '!' && opc != 'S' && opc != 'C' && opc != 'T' && opc != 'X' && opc != 'G'){
             n2 = input_valor();
        } else {
             precisa_de_n2 = 0;
        }

        switch(opc){

            case '+':
                n1 = somar(n1,n2);
                break;
            case '-':
                n1 = subtrair(n1,n2);
                break;
            case '*':
                n1 = multiplicar(n1,n2);
                break;
            case '/':
                n1 = dividir(n1,n2);
                break;
            case '^':
                n1 = pow(n1,n2); // Usamos math.h
                break;
            case 'R':
                n1 = pow(n1,1.0/n2); // Usamos math.h
                break;

            case '!':
                fatorial(&n1);
                break;

            case 'S':
                n1 = sin(n1); // Usamos math.h
                break;

            case 'C':
                n1 = cos(n1); // Usamos math.h
                break;

            case 'T':
                n1 = tan(n1); // Usamos math.h
                break;

            case 'X':
                n1 = exp(n1); // Usamos math.h
                break;

            case 'G':
                n1 = logaritmo(n1); // Usamos math.h
                break;

            case 'c':
                limpar_e_reexibir_cabecalho(n1);
                break;

            case 'H':
                exibir_historico_da_memoria();
                break;

            case 'L':
                limpar_historico_da_memoria();
                break;

            case '0':
                printf("Fechando Calculadora Cientifica...");
                salvar_historico_no_arquivo();
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                precisa_de_n2 = 0;
                break;
        }
        double resultado_n1 = n1;

        if(precisa_de_n2 && opc != '0' && opc != 'c' && opc != 'H' && opc != 'L'){
             adicionar_na_memoria(n1_ini, opc, n2, resultado_n1);
             printf("%.15lf\n", n1);
        }
        else if (opc != '0'){
             printf("%.15lf\n", n1);
        }

    }while(opc != '0');

    printf("\n");
    return 0;
}
