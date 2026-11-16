/*

0 1 2  3  4 5 6 7 8 9  10 11 12 13 14 15 16 17 18 19 20 21 22 23
s s PP PP f f f f c PP PP PP PP PP PP PP d  d  d  d  d  d  d  d 

a = 12 = 00 0c

c = -12 = f4 

b:

12 = 1100

0.125 * 2 = 0.25
0.25 * 2 = 0.5
0.5 * 2 = 1

b = 1100.001 = 1.100001 * 2^3
E = 3 + 127 = 130 = 10000010

b = 0100 0001 0100 0010 0000 0000 0000 0000
b = 41 42 00 00 

d:

E = 3 + 1023 = 1026 = 10000000010
d = 0100 0000 0010 1000 0100 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
d = 40 28 40 00 00 00 00 00

0x7ffee4bb4260 - 0c
0x7ffee4bb4261 - 00
0x7ffee4bb4262 - PP
0x7ffee4bb4263 - PP
0x7ffee4bb4264 - 00
0x7ffee4bb4265 - 00
0x7ffee4bb4266 - 42
0x7ffee4bb4267 - 41 
0x7ffee4bb4268 - f4
0x7ffee4bb4269 - PP
0x7ffee4bb426a - PP
0x7ffee4bb426b - PP
0x7ffee4bb426c - PP
0x7ffee4bb426d - PP
0x7ffee4bb426e - PP
0x7ffee4bb426f - PP
0x7ffee4bb4270 - 00
0x7ffee4bb4271 - 00
0x7ffee4bb4272 - 00
0x7ffee4bb4273 - 00
0x7ffee4bb4274 - 00
0x7ffee4bb4275 - 40
0x7ffee4bb4276 - 28
0x7ffee4bb4277 - 40

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
    short a;
    float b;
    char c;
    double d;
} s = {12, 12.125, -12, 12.125};

int main(void) {
    dump(&s, sizeof(struct S));
    return 0;
}