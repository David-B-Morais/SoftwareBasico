/* 

s está alocado em 0x7ffee4bb4260

0 1 2 3 4 5  6  7  8  9  10 11 12 13 14 15
i i i i c PP PP PP *p *p *p *p *p *p *p *p

i = -16 = ff ff ff f0

c = 'd' = 100 = 64

p = 0x7ffee4bb4264
p = 00 00 7f fe e4 bb 42 64

0x7ffee4bb4260 - f0
0x7ffee4bb4261 - ff
0x7ffee4bb4262 - ff
0x7ffee4bb4263 - ff
0x7ffee4bb4264 - 64
0x7ffee4bb4265 - PP
0x7ffee4bb4266 - PP
0x7ffee4bb4267 - PP
0x7ffee4bb4268 - 64
0x7ffee4bb4269 - 42
0x7ffee4bb426a - bb
0x7ffee4bb426b - e4
0x7ffee4bb426c - fe
0x7ffee4bb426d - 7f
0x7ffee4bb426e - 00
0x7ffee4bb426f - 00

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
    int a;
    char c;
    char *p;
};

int main(void) {
    struct S s;
    s.a = -16;
    s.c = 'd';
    s.p = &s.c;
    dump(&s, sizeof(struct S));
    return 0;
}