.text
.globl buba

buba:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)
    movq %r14, -32(%rbp)
    movq %r15, -40(%rbp)

    movl $0, %ebx /* i */
    movl $0, %r12d /* s */

    movq %rdi, %r13 /* *v */
    movl %esi, %r14d /* n */
    movb %dl, %r15b /* c */

for:
    cmpl %r14d, %ebx
    jge saifora

    cmpb (%r13, %rbx, 1), %r15b
    jl continua

    movb (%r13, %rbx, 1), %dil
    movl %r14d, %esi
    call corta

    addl %eax, %r12d

continua:
    incl %ebx
    jmp for

saifora:
    movl %r12d, %eax

    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    movq -24(%rbp), %r13
    movq -32(%rbp), %r14
    movq -40(%rbp), %r15
    leave
    ret