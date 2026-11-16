.text
.globl foo

foo:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    movq %rbx, -8(%rbp) /* v */
    movq %r12, -16(%rbp) /* n */
    movq %r13, -24(%rbp) /* filtro */
    movq %r14, -32(%rbp) /* i */

    movq %rdi, %rbx
    movl %esi, %r12d
    movq %rdx, %r13

    movl $0, %r14d
    xorpd %xmm1, %xmm1 /* soma = 0 */
    movsd %xmm1, -40(%rbp)

for:
    cmpl %r12d, %r14d
    jge saifora

    movq %r14, %rcx
    imulq $2, %rcx
    addq %rbx, %rcx

    movswq (%rcx), %r8
    cmpq %r13, %r8
    jle saidoif

    movq %rcx, %rdi
    movl $3, %esi
    call passa_alta

    cvtss2sd %xmm0, %xmm0
    addsd -40(%rbp), %xmm0
    movsd %xmm0, -40(%rbp)

saidoif:
    incl %r14d
    jmp for

saifora:
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    movq -24(%rbp), %r13
    movq -32(%rbp), %r14
    leave
    ret
