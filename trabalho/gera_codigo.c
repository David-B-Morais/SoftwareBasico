/* Nome_do_Aluno1 Matricula Turma */
/* Nome_do_Aluno2 Matricula Turma */

#include <stdio.h>
#include "gera_codigo.h"

/*
 * Gerador de codigo de maquina x86-64 para a linguagem LBS.
 *
 * Registro de ativacao de cada funcao LBS (32 bytes abaixo de %rbp):
 *
 *      -4(%rbp)   v0
 *      -8(%rbp)   v1
 *     -12(%rbp)   v2
 *     -16(%rbp)   v3
 *     -20(%rbp)   v4
 *     -24(%rbp)   p0  (copia de %edi, feita no prologo)
 *     -32(%rbp)   (nao usado; mantem %rsp multiplo de 16)
 *
 * O parametro chega em %edi (convencao C/Linux). Ele e' copiado para a
 * pilha porque %edi e' "caller-saved": uma chamada (call) pode destrui-lo
 * e, alem disso, precisamos de %edi para passar o argumento da chamada.
 *
 * Todas as contas sao feitas em %eax, que e' tambem o registrador do valor
 * de retorno. Nenhum registrador "callee-saved" e' usado alem de %rbp, que
 * e' salvo e restaurado pelo prologo/epilogo.
 *
 * Nao ha variaveis globais: o estado da geracao fica na struct Gerador,
 * criada dentro de gera_codigo e passada por ponteiro as funcoes auxiliares.
 */

#define MAX_LINHA 128   /* tamanho maximo de uma linha do fonte */
#define MAX_FUNCS 50    /* o arquivo tem no maximo 50 linhas    */

/* Layout do registro de ativacao (ver desenho acima) */
#define TAM_VAR       4       /* cada variavel local ocupa 4 bytes (int)     */
#define DESLOC_P0     (-24)   /* posicao da copia do parametro               */
#define TAM_REGISTRO  32      /* 5 locais + p0 = 24, arredondado para 16n    */

/* Numeros dos registradores na codificacao x86 */
#define EAX 0
#define EDI 7

/* Byte ModRM para um operando de memoria "desloc8(%rbp)": mod=01 e r/m=101.
   O numero do registrador entra nos 3 bits do meio (campo reg). */
#define MODRM_RBP_DESLOC8  0x45
#define BITS_CAMPO_REG     3

/* Faixa de constantes que cabem num imediato de 8 bits com sinal */
#define IMM8_MIN  (-128)
#define IMM8_MAX  127

/* Um operando "varpc": variavel local, parametro ou constante */
typedef struct {
  char tipo;    /* 'v' = variavel local, 'p' = parametro, '$' = constante */
  int valor;    /* indice da variavel, 0 para p0, ou valor da constante   */
} Operando;

/* Estado da geracao */
typedef struct {
  unsigned char *cod;           /* vetor de saida                              */
  int pos;                      /* proxima posicao livre em cod                */
  int inicio_func[MAX_FUNCS];   /* posicao, em cod, do inicio de cada funcao   */
  int nfuncs;                   /* numero de funcoes lidas ate agora           */
  int terminou_com_ret;         /* o ultimo comando lido foi um ret?           */
} Gerador;

/* ---------- emissao de bytes ---------- */

/* grava um byte no vetor de codigo */
static void emite(Gerador *g, int b) {
  g->cod[g->pos++] = (unsigned char) b;
}

/* grava um inteiro de 32 bits em little-endian (imediatos e deslocamentos) */
static void emite_int(Gerador *g, int v) {
  unsigned int u = (unsigned int) v;
  int i;
  for (i = 0; i < 4; i++) {
    emite(g, u & 0xFF);         /* byte menos significativo primeiro */
    u >>= 8;
  }
}

/* grava os bytes que indicam o par "registrador, desloc(%rbp)" */
static void emite_reg_mem(Gerador *g, int reg, int desloc) {
  emite(g, MODRM_RBP_DESLOC8 | (reg << BITS_CAMPO_REG));
  emite(g, desloc);
}

/* ---------- operandos ---------- */

/* deslocamento, em relacao a %rbp, da variavel local v<idx> */
static int desloc_var(int idx) {
  return -TAM_VAR * (idx + 1);    /* v0 -> -4, v1 -> -8, ... v4 -> -20 */
}

/* deslocamento de um operando que esta' na pilha (variavel ou parametro) */
static int desloc(Operando o) {
  return (o.tipo == 'p') ? DESLOC_P0 : desloc_var(o.valor);
}

/* carrega o valor de um operando no registrador reg (EAX ou EDI) */
static void carrega(Gerador *g, Operando o, int reg) {
  if (o.tipo == '$') {
    emite(g, 0xB8 + reg);         /* movl $const, %reg       */
    emite_int(g, o.valor);
  } else {
    emite(g, 0x8B);               /* movl desloc(%rbp), %reg */
    emite_reg_mem(g, reg, desloc(o));
  }
}

/* guarda %eax na variavel local v<idx> */
static void guarda_em_var(Gerador *g, int idx) {
  emite(g, 0x89);                 /* movl %eax, desloc(%rbp) */
  emite_reg_mem(g, EAX, desloc_var(idx));
}

/* ---------- traducao dos comandos ---------- */

/* inicio de funcao: cria o registro de ativacao e salva o parametro */
static void gera_prologo(Gerador *g) {
  emite(g, 0x55);                                    /* pushq %rbp            */
  emite(g, 0x48); emite(g, 0x89); emite(g, 0xE5);    /* movq  %rsp, %rbp      */
  emite(g, 0x48); emite(g, 0x83); emite(g, 0xEC);    /* subq  $TAM_REGISTRO,  */
  emite(g, TAM_REGISTRO);                            /*       %rsp            */
  emite(g, 0x89);                                    /* movl  %edi,           */
  emite_reg_mem(g, EDI, DESLOC_P0);                  /*       DESLOC_P0(%rbp) */
}

/* desfaz o registro de ativacao e retorna (valor de retorno ja em %eax) */
static void gera_epilogo(Gerador *g) {
  emite(g, 0xC9);                 /* leave */
  emite(g, 0xC3);                 /* ret   */
}

/* ret varpc */
static void gera_ret(Gerador *g, Operando o) {
  carrega(g, o, EAX);
  gera_epilogo(g);
}

/* zret a b : se a == 0, retorna b; senao continua na proxima instrucao
 *   movl  a, %eax
 *   cmpl  $0, %eax
 *   jne   continua
 *   movl  b, %eax
 *   leave
 *   ret
 * continua:
 */
static void gera_zret(Gerador *g, Operando a, Operando b) {
  int pos_salto;

  carrega(g, a, EAX);
  emite(g, 0x83); emite(g, 0xF8); emite(g, 0);   /* cmpl $0, %eax */
  emite(g, 0x75);                                /* jne rel8      */
  pos_salto = g->pos;     /* o deslocamento do salto so' e' conhecido  */
  emite(g, 0);            /* depois: reserva 1 byte e preenche abaixo  */

  gera_ret(g, b);

  /* o deslocamento do jne e' relativo ao endereco da instrucao seguinte a
     ele, ou seja, e' o numero de bytes do trecho que deve ser pulado */
  g->cod[pos_salto] = (unsigned char) (g->pos - (pos_salto + 1));
}

/* %eax = %eax op desloc(%rbp) : segundo operando na pilha */
static void opera_com_memoria(Gerador *g, char op, int desloc) {
  if (op == '+') {
    emite(g, 0x03);                   /* addl  */
  } else if (op == '-') {
    emite(g, 0x2B);                   /* subl  */
  } else {
    emite(g, 0x0F); emite(g, 0xAF);   /* imull */
  }
  emite_reg_mem(g, EAX, desloc);
}

/* %eax = %eax op $valor : segundo operando constante.
   Se a constante cabe em 8 bits, usa a forma curta da instrucao (o
   processador estende o sinal); e' a mesma escolha que o montador faz. */
static void opera_com_constante(Gerador *g, char op, int valor) {
  if (valor >= IMM8_MIN && valor <= IMM8_MAX) {
    if (op == '+') {
      emite(g, 0x83); emite(g, 0xC0);   /* addl  $imm8, %eax       */
    } else if (op == '-') {
      emite(g, 0x83); emite(g, 0xE8);   /* subl  $imm8, %eax       */
    } else {
      emite(g, 0x6B); emite(g, 0xC0);   /* imull $imm8, %eax, %eax */
    }
    emite(g, valor);
  } else {
    if (op == '+') {
      emite(g, 0x05);                   /* addl  $imm32, %eax       */
    } else if (op == '-') {
      emite(g, 0x2D);                   /* subl  $imm32, %eax       */
    } else {
      emite(g, 0x69); emite(g, 0xC0);   /* imull $imm32, %eax, %eax */
    }
    emite_int(g, valor);
  }
}

/* v<dest> = a op b   (op e' '+', '-' ou '*')
 *   movl  a, %eax
 *   op    b, %eax
 *   movl  %eax, v<dest>
 */
static void gera_oper(Gerador *g, int dest, Operando a, char op, Operando b) {
  carrega(g, a, EAX);
  if (b.tipo == '$')
    opera_com_constante(g, op, b.valor);
  else
    opera_com_memoria(g, op, desloc(b));
  guarda_em_var(g, dest);
}

/* v<dest> = call num arg
 *   movl  arg, %edi        (1o parametro inteiro na convencao C/Linux)
 *   call  funcao
 *   movl  %eax, v<dest>    (valor de retorno vem em %eax)
 *
 * O call usado (opcode E8) e' relativo: seu operando de 32 bits e' a
 * distancia entre o inicio da funcao chamada e o endereco da instrucao
 * seguinte ao call. Por ser relativo, o codigo funciona em qualquer
 * endereco de memoria onde o vetor esteja.
 */
static void gera_call(Gerador *g, int dest, int num, Operando arg) {
  int pos_seguinte;

  carrega(g, arg, EDI);
  emite(g, 0xE8);                         /* call rel32 */
  pos_seguinte = g->pos + 4;              /* depois dos 4 bytes do operando */
  emite_int(g, g->inicio_func[num] - pos_seguinte);
  guarda_em_var(g, dest);
}

/* ---------- leitura do fonte ---------- */

/* traduz uma atribuicao: "vN = call num varpc" ou "vN = varpc op varpc" */
static void traduz_atribuicao(Gerador *g, const char *l) {
  Operando a, b;
  int dest, num;
  char op;

  if (sscanf(l, "v%d = call %d %c%d", &dest, &num, &a.tipo, &a.valor) == 4)
    gera_call(g, dest, num, a);
  else if (sscanf(l, "v%d = %c%d %c %c%d", &dest, &a.tipo, &a.valor,
                  &op, &b.tipo, &b.valor) == 6)
    gera_oper(g, dest, a, op, b);
}

/* traduz uma linha do fonte; o primeiro caractere identifica o comando */
static void traduz_linha(Gerador *g, const char *l) {
  Operando a, b;
  int eh_ret = 0;

  while (*l == ' ' || *l == '\t')       /* ignora espacos iniciais */
    l++;

  switch (*l) {
    case 'f':   /* function */
      g->inicio_func[g->nfuncs++] = g->pos;
      gera_prologo(g);
      break;

    case 'e':   /* end */
      /* se a funcao nao acabou com ret, evita "cair" na funcao seguinte */
      if (!g->terminou_com_ret)
        gera_epilogo(g);
      break;

    case 'r':   /* ret varpc */
      if (sscanf(l, "ret %c%d", &a.tipo, &a.valor) == 2)
        gera_ret(g, a);
      eh_ret = 1;
      break;

    case 'z':   /* zret varpc varpc */
      if (sscanf(l, "zret %c%d %c%d", &a.tipo, &a.valor,
                 &b.tipo, &b.valor) == 4)
        gera_zret(g, a, b);
      break;

    case 'v':   /* atribuicao */
      traduz_atribuicao(g, l);
      break;

    default:    /* linha em branco: ignora */
      break;
  }
  g->terminou_com_ret = eh_ret;
}

/* ---------- funcao principal ---------- */

void gera_codigo (FILE *f, unsigned char code[], funcp *entry) {
  char linha[MAX_LINHA];
  Gerador g;

  g.cod = code;
  g.pos = 0;
  g.nfuncs = 0;
  g.terminou_com_ret = 0;

  while (fgets(linha, MAX_LINHA, f) != NULL)
    traduz_linha(&g, linha);

  /* a funcao chamada externamente e' a ultima do arquivo */
  if (g.nfuncs > 0)
    *entry = (funcp) (code + g.inicio_func[g.nfuncs - 1]);
  else
    *entry = NULL;
}
