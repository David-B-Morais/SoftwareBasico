/* arquivo.c */

#include <stdio.h>
#include "header.h"

int minhaVariavel = 42;

void funcaoModulo1() {
    printf("Função do Módulo 1\n");
    printf("Valor da variável: %d\n", minhaVariavel);
    
    funcaoModulo2();
}

/* main.c */

#include <stdio.h>
#include "header.h
"
void funcaoModulo2() {
    printf("Função do Módulo 2\n");
    printf("Valor da variável: %d\n", minhaVariavel);
    
    funcaoModulo1();
}

int main() {
    funcaoModulo1();
    return 0;
}

/* 

arquivo.c

T: funcaoModulo1
U: printf, funcaoModulo2
D: minhaVariavel

main.c

T: main, funcaoModulo2
U: printf, minhaVariavel, funcaoModulo1

*/