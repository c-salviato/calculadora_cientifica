#include "mate.h"
#include <stdio.h>

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
    return a / b;
}
float fatorial(float n){



    if (n < 0 || n != (int)n) {
        printf("Erro: o fatorial funciona só com inteiros positivos ou zero.\n");

    }

    int num = (int)n;
    double resultado = 1;


    for (int i = 1; i <= num; i++) {
        resultado = resultado * i;
    }

    return resultado;
}
