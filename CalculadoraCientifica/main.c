// main.c

#include <stdio.h>
#include <locale.h>
#include "mate.h"
#include <math.h>
#include <stdlib.h>


int main(){

    setlocale(LC_ALL, "Portuguese");

    char opc;
    float n1, n2;

    limpar_e_reexibir_cabecalho(0.0f);

    printf("=== TUTORIAL BASICO ===\n");
    printf("A calculadora funciona de forma sequencial. Explicação: Você digita o primeiro valor, depois escolhe uma das opções acima, depois outro valor e o resultado vai se acumulando!\n");
    printf("Pressione ENTER depois de cada opção ou valor inserido!\n");
    printf("- (Após limpar a tela com a opção 'C' o tutorial some!) -\n");

    printf("----------------------------------------------------\n");


    scanf("%f",&n1);

    do{
        scanf(" %c",&opc);

        if(opc != '0' && opc != 'C'){
            scanf("%f",&n2);
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
                n1 = pow(n1,n2); //Usamos math.h
                break;
            case 'R':
                n1 = pow(n1,1.0/n2); //Usamos math.h
                break;

            case 'C':
                limpar_e_reexibir_cabecalho(n1);
                break;

            case '0':
                printf("Fechando Calculadora Cientifica...");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }

        if(opc != '0' && opc != 'C'){
             printf("%f\n", n1);
        }


    }while(opc != '0');

    printf("\n");
    return 0;
}
