#include <stdio.h>

unsigned char configuraBits(unsigned char byteConf, int bitInicial, int bitFinal){
    for (int i = bitInicial; i <= bitFinal; i++){
        byteConf = byteConf | (1 << i);
    }
    return byteConf;
}

int main(void){
    char c = 0x80;
    printf("%x\n", configuraBits(c, 1, 3));
    return 0;
}