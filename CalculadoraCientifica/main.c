#include <stdio.h>
#include <locale.h>
#include "mate.h"
#include <math.h>

int main(){

    setlocale(LC_ALL, "Portuguese");

    char opc;
    float n1, n2;


    printf("======== Bem vindo a Calculadora Cientifica ========\n");



    printf("Digite um valor: \n");
    scanf("%f",&n1);

    do{

        printf("Escolha uma opção: \n+: Soma\n-: Subtração\n*: Multiplição\n/: Divisão\n^: Potência\nR: Raiz\n0: Fechar Calculadora Cientifica\n");
        scanf(" %c",&opc);
        if(opc != '0'){
            printf("Digite um valor: \n");
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
            case '0':
                printf("Fechando Calculadora Cientifica...");
                break;
        }
        if(opc != '0'){
            printf("O resultado é: %f\n", n1);
        }

    }while(opc != '0');


}
