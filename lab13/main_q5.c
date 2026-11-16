#include <stdio.h>

typedef int (*funcp) (int x);

int add (int x) {
  return x+1;
}

int main(void){
    unsigned char codigo[] = {0xe8, 0x00, 0x00, 0x00, 0x00, 0xc3};
    funcp f = (funcp)codigo;
    int i = (*f)(10);
    printf("%d", i);    
    return 0;
}