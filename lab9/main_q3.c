#include <stdio.h>

void foo(int a[], int n);

int main(void){
    int v[] = {1, 2, 0};
    int i;
    printf("Vetor antes de usar a função foo: ");
    for (i = 0; i < 3; i++){
        printf("%d ", v[i]);
    }
    foo(v, 3);
    printf("\nVetor depois de usar a função foo: ");
    for (i = 0; i < 3; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
    return 0;
}