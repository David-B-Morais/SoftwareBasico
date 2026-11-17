.text
.globl boba

boba:
    pushq %rbp
    movq %rsp, %rbp
    subq $112, %rsp
    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    
    movss %xmm0, -20(%rbp) /* val */
    movl %esi, %ebx /* n */

while:
    cmpl $0, %ebx
    je saifora

    movl $5, %edi
    call indexa
    movl %eax, %r12d /* i = indexa(TAM) */ 

    movslq %r12d, %rcx
    imulq $16, %rcx
    leaq -104(%rbp), %rdx /* &reg[0] */
    addq %rcx, %rdx
    movb %r12b, (%rdx)

    movss -20(%rbp), %xmm0
    call corta
    
    movslq %r12d, %rcx /* recalcula &reg[i] (%rcx/%rdx não sobrevivem à chamada) */
    imulq $16, %rcx 
    leaq -104(%rbp), %rdx 
    addq %rcx, %rdx
    movsd %xmm0, 8(%rdx)

    decl %ebx
    jmp while

saifora:
    movsd -96(%rbp), %xmm0 /* return reg[0].d  (-104 + 8) */
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    leave
    ret