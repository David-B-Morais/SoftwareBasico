/*

0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
i i i i f f f f d d d  d  d  d  d  d  c  PP PP PP PP PP PP PP

i = -0xF = - 00 00 00 0f = ff ff ff f0 = ff ff ff f1

f:

0 = 0

0.625 * 2 = 1.25
0.25 * 2 = 0.5
0.5 * 2 = 1

f = 0.101 = 1.01 * 2^-1
E = -1 + 127 = 126 = 0111 1110 

f = 0011 1111 0010 0000 0000 0000 0000 0000
f = 3f 20 00 00

d:

-2 = 2 = 10

0.375 * 2 = 0.75
0.75 * 2 = 1.5
0.5 * 2 = 1

d = 10.011 = 1.0011 * 2^1
E = 1 + 1023 = 1024 = 10000000000

d = 1100 0000 0000 0011 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
d = c0 03 00 00 00 00 00 00

c = 17 = 11

0x5607ea64b010 = f1
0x5607ea64b011 = ff
0x5607ea64b012 = ff
0x5607ea64b013 = ff
0x5607ea64b014 = 00
0x5607ea64b015 = 00
0x5607ea64b016 = 20
0x5607ea64b017 = 3f
0x5607ea64b018 = 00
0x5607ea64b019 = 00
0x5607ea64b01a = 00
0x5607ea64b01b = 00
0x5607ea64b01c = 00
0x5607ea64b01d = 00
0x5607ea64b01e = 03
0x5607ea64b01f = c0
0x5607ea64b020 = 11
0x5607ea64b021 = PP
0x5607ea64b022 = PP
0x5607ea64b023 = PP
0x5607ea64b024 = PP
0x5607ea64b025 = PP
0x5607ea64b026 = PP
0x5607ea64b027 = PP

*/

#include <stdio.h>

void dump (void *p, int n) {
    unsigned char *p1 = (unsigned char *) p;
    while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
    }
}

struct X {
    int i;
    float f;
    double d;
    char c;
} x = {-0xF, 0.625, -2.375, 17};

int main (void) {
    dump (&x, sizeof(struct X));
    return 0;
}
