#include <stdio.h>

int g(char *s1, char *s2);

int i = 0;
int k = 0;
char s1[] = "ola";
char s2[] = " mundo";

int f(char *p) {
  ...  /* algum código */
}

int main() {
  int j;
  ...
  j = g(s1, s2);
  printf("%d",k);
  ...
 }


/*

Resultado do printf: imprime 0
Justificativa: o k de arq1.c é static, portanto é local àquele módulo e não é visto pelo ligador;
o k do segundo módulo é outra variável. A função g faz k += 3 + 6 + 0 (strlen(“ola”) = 3, strlen(“ mundo”) = 6, i = 0),
alterando apenas o k estático de arq1.c. O main imprime o k global do seu próprio módulo, que foi inicializado com 0 e nunca foi alterado.

*/