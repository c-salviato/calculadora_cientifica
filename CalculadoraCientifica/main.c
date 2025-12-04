#include <stdio.h>
#include <locale.h>
#include "mate.h"
#include <math.h>

int main(){

    setlocale(LC_ALL, "Portuguese");

    int opc;
    float n1, n2;


    printf("======== Bem vindo a Calculadora Cientifica ========\n");



    printf("Digite um valor: \n");
    scanf("%f",&n1);

    do{

        printf("Escolha uma opção: \nSoma: 1\nSubtração: 2\nMultiplição: 3\nDivisão: 4\nPotencia: 5\nRaiz: 6\nFechar Calculadora Cientifica: 0\n");
        scanf("%d",&opc);
        if(opc != 0){
            printf("Digite um valor: \n");
            scanf("%f",&n2);
        }
        switch(opc){

            case 1:
                n1 = somar(n1,n2);
                break;
            case 2:
                n1 = subtrair(n1,n2);
                break;
            case 3:
                n1 = multiplicar(n1,n2);
                break;
            case 4:
                n1 = dividir(n1,n2);
                break;
            case 5:
                n1 = pow(n1,n2); //Usamos math.h
                break;
            case 6:
                n1 = pow(n1,1.0/n2); //Usamos math.h
                break;
            case 0:
                printf("Fechando Calculadora Cientifica...");
                break;
        }
        if(opc != 0){
            printf("O resultado é: %f\n", n1);
        }

    }while(opc != 0);


}
