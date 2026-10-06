.text
.globl boo

boo:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)
    movq %r14, -32(%rbp)
    movq %r15, -40(%rbp)

    movl $0, %ebx
    movl $0, %r12d

    movl %edx, %r13d /* n */
    movl %edi, %r14d /* lim */
    movq %rsi, %r15 /* *v */

for:
    cmpl %r13d, %ebx
    jge saifora

    movl (%r15, %rbx, 4), %edi
    movl %r14d, %esi
    call valida

    cmpl $0, %eax
    je continua

    addl (%r15, %rbx, 4), %r12d

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
