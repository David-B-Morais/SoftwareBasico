#include <stdio.h>

int numBits0(unsigned int u){
    int zeros = 0;
    for (int i = 0; i < 32; i++){
        if ((u & 1) == 0)
            zeros++;
        u = u >> 1;
    }
    return zeros;
}

int main(void){
    unsigned int n = 1; /* 5 = 101*/
    printf("%d\n", numBits0(n));
    return 0;
}