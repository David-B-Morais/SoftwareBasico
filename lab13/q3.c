#include <stdio.h>

typedef int (*funcp) (int x);

int main(void){
    unsigned char codigo[] = {0xff, 0xc7, 0x89, 0xf8, 0xc3};
    funcp f = (funcp)codigo;
    int i = (*f)(10);
    printf("%d", i);    
    return 0;
}