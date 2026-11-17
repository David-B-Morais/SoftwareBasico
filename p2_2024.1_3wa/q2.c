/* prog1.c */

#include <stdio.h>
extern int i;

static void sub () {
    i--;
    printf ("i = %d\n", i);
}

void calcula () {
    sub ();
}

/* prog2.c */

#include <stdio.h>
int i = 12;

int sub ();
void calcula ();

int main (void) {
    printf("i = %08x\n", i);
    sub ();
    calcula ();
    return 0;
}

/* 

a)

prog1.c

T: calcula
t: sub
U: i, printf

pro2.c

T: main
D: i
U: sub, calcula, printf

b)

Ocorre um erro de ligação e o executável não é gerado. O módulo prog2.o referencia o símbolo sub (U), 
mas a única definição de sub está em prog1.c e é declarada static, ou seja, é um símbolo local (t) que 
não é exportado. Assim, o ligador não encontra nenhuma definição exportada para sub e termina com erro de referência indefinida.

*/