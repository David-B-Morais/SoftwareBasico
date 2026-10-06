/* 

0 1 2 3 4 5 6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23
i i i i s s PP PP *p *p *p *p *p *p *p *p c  PP PP PP PP PP PP PP

bb está alocado em 0x7ffc0131d9a0

i = -20 = ff ff ff ec

s = 31 = 00 1f

p = 0x7ffc0131d9a4
p = 00 00 7f fc 01 31 d9 a0

c = 'e' = 101 = 65

0x7ffc0131d99c - ec
0x7ffc0131d99d - ff
0x7ffc0131d99e - ff
0x7ffc0131d99f - ff
0x7ffc0131d9a0 - 1f
0x7ffc0131d9a1 - 00
0x7ffc0131d9a2 - PP
0x7ffc0131d9a3 - PP
0x7ffc0131d9a4 - a0
0x7ffc0131d9a5 - d9
0x7ffc0131d9a6 - 31
0x7ffc0131d9a7 - 01
0x7ffc0131d9a8 - fc
0x7ffc0131d9a9 - 7f
0x7ffc0131d9aa - 00
0x7ffc0131d9ab - 00
0x7ffc0131d9ac - 65
0x7ffc0131d9ad - PP
0x7ffc0131d9ae - PP
0x7ffc0131d9af - PP
0x7ffc0131d9b0 - PP
0x7ffc0131d9b1 - PP
0x7ffc0131d9b2 - PP
0x7ffc0131d9b3 - PP

*/

#include <stdio.h>

void dump (void *p, int n) {
    unsigned char *p1 = (unsigned char *) p;
    while (n--) {
        printf("%p - %02x\n", p1, *p1);
        p1++;
    }
}

struct Bravo {
    int i;
    short s;
    short *p;
    char c;
};

int main(void) {
    struct Bravo bb;
    bb.i = -20;
    bb.s = 31;
    bb.p = &bb.s;
    bb.c = 'e';
    dump(&bb, sizeof(struct Bravo));
    return 0;
}