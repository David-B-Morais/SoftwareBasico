.text
.globl boo

boo:
    pushq %rbp
    movq %rsp, %rbp
    suq $32, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)
    
    movq %rdi, %rbx /* s */
    movl %esi, %r12d /* n */
    movl $0, %r13d /* acum */

while:
    cmpq $0, %rbx
    je saifora

    movq $norma, %rdi
    movl %r12d, %esi
    addl %r13d, %esi
    call acerta
    movl %eax, (%rbx)

    addl %r12d, %r13d
    movq 8(%rbx), %rbx
    jmp while

saifora:
    movl %r13d, %eax
    movq  -8(%rbp), %rbx       
    movq  -16(%rbp), %r12
    movq  -24(%rbp), %r13
    leave
    ret

    