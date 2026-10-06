.text
.globl foo

foo:
    /* Prólogo */
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    /* Salva os registradores callee-saved que vamos usar */
    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)
    movq %r14, -32(%rbp)
    movq %r15, -40(%rbp)

    /* Guardamos os parâmetros em registradores callee-saved */
    movq %rdi, %r12
    movl %esi, %r13d
    movq %rdx, %r14

    movl $0, %r15d /* soma */
    movl $0, %ebx /* i */

loop:
    cmpl %r13d, %ebx
    jge saifora

    movswq (%r12, %rbx, 2), %rax
    cmpq %r14, %rax
    jl continua

    movw (%r12, %rbx, 2), %di
    movl $3, %esi
    call passa_alta

    addl %eax, %r15d

continua:
    incl %ebx
    jmp loop

saifora:
    /* return soma */
    movl %r15d, %eax

    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    movq -24(%rbp), %r13
    movq -32(%rbp), %r14
    movq -40(%rbp), %r15
    leave
    ret