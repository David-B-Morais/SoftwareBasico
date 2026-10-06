#include <stdio.h>

unsigned char configuraBits(unsigned char byteConf, int bitInicial, int bitFinal){
    unsigned char mascara = 0;
    for (int i = bitInicial; i <= bitFinal; i++){
        mascara = mascara | (1 << i);
    }
    return mascara | byteConf;
}

int main(void){
    char c = 0x80;
    printf("%x\n", configuraBits(c, 1, 3));
    return 0;
}