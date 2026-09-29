.text
.globl add2

add2:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    cmpq $0, %rdi
    je saifora

    movq %rdi, -8(%rbp)
    movq 8(%rdi), %rdi
    call add2
    movq -8(%rbp), %rdi
    addl (%rdi), %eax

    jmp final

saifora:
    movl $0, %eax

final:
    leave
    ret