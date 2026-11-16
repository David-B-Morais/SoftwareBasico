#include <string.h>
#include <stdlib.h>

extern int i;
char *buff = NULL;
static int k = 0;
int f(char *p);

int g(char *s1, char *s2) {
  int a = strlen(s1);
  int b = strlen(s2);
  buff = (char *) malloc(a + b + 1);
  strcat(strcpy(buff,s1), s2);

  k += a + b + i;
  return f(buff); 
}

/*

T (função definida no módulo): g
D (global inicializada com valor diferente de 0):
B (global sem inicialização ou = 0 / NULL): buff
U (usado mas definido em outro lugar): i, f, strlen, malloc, srtcat, strcpy
minúscula (t, d, b) (static: local, não exportado): k

*/