/* 

0 1  2 3 4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23
c PP s s PP PP PP PP *p *p *p *p *p *p *p *p i  i  i  i  PP PP PP PP

S está alocado na posição: 0x7ffc54b9fd90

c = 'e' = 101 -> 101 em hex = 65

s = 12 -> 12 em hex = 0c, mas como 12 é um short e ocupa 2 bytes, = 000c

p = 0x00007ffc54b9fd92
p = 00 00 7f fc 54 b9 fd 92

i = -20 -> -20 em hex = ff ff ff ec

0x7ffc54b9fd90 - 65
0x7ffc54b9fd91 - PP
0x7ffc54b9fd92 - 0c
0x7ffc54b9fd93 - 00
0x7ffc54b9fd94 - PP
0x7ffc54b9fd95 - PP
0x7ffc54b9fd96 - PP
0x7ffc54b9fd97 - PP
0x7ffc54b9fd98 - 92
0x7ffc54b9fd99 - fd
0x7ffc54b9fd9a - b9
0x7ffc54b9fd9b - 54
0x7ffc54b9fd9c - fc
0x7ffc54b9fd9d - 7f
0x7ffc54b9fd9e - 00
0x7ffc54b9fd9f - 00
0x7ffc54b9fda0 - ec 
0x7ffc54b9fda1 - ff
0x7ffc54b9fda2 - ff
0x7ffc54b9fda3 - ff
0x7ffc54b9fda4 - PP
0x7ffc54b9fda5 - PP
0x7ffc54b9fda6 - PP
0x7ffc54b9fda7 - PP

*/

#include <stdio.h>
void dump (void *p, int n) {
    unsigned char *p1 = (unsigned char *) p;
    while (n--) {
        printf("%p - %02x\n", p1, *p1);
        p1++;
    }
}

struct S {
    char c;
    short s;
    short *p;
    int i;
};

int main(void) {
    struct S s;
    s.c = 'e';
    s.s = 12;
    s.p = &s.s;
    s.i = -20;
    dump(&s, sizeof(struct S));
    return 0;
}