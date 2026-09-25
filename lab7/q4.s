.data
nums:  .int  65, -105, 111, 34
Sf: .string "soma = %d\n"

.text
.globl main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)  /* guarda rbx */
  movq    %r12, -16(%rbp)  /* guarda r12 */
/********************************************************/

movl $0, %ebx /* i = 0; */
movl $0, %edx /* soma = 0 */

L1:
    cmpl $4, %ebx
    je L2

    movslq %ebx, %rcx
    imulq $4, %rcx
    addq $nums, %rcx

    addl (%rcx), %edx

    addl $1, %ebx
    jmp L1

L2:
    movl %edx, %eax

    /*************************************************************/
    /* este trecho imprime o valor de %eax (estraga %eax)  */
    movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
    movl    %eax, %esi   /* segundo parametro  (inteiro) */
    movl  $0, %eax
    call  printf       /* chama a funcao da biblioteca */
    /*************************************************************/

    /***************************************************************/
    /* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
    movq  $0, %rax  /* rax = 0  (valor de retorno) */
    movq    -16(%rbp), %r12 /* recupera r12 */
    movq    -8(%rbp), %rbx  /* recupera rbx */
    leave
    ret      
    /***************************************************************/
