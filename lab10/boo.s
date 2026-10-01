.text
.globl boo

boo:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

loop:
    cmpl %0, %esi
    je saifora

    decl %esi

    movq -8(%rdi), %rbp
    movl -12(%esi), %rbp
    movl -16(%edx), %rbp

    movl 4(%rdi), %esi
    movl (%rdi), %edi
    call f

    movq -8(%rbp), %rdi
    movl -12(%rbp), %esi
    movl -16(%rbp), %edx

    %eax, 4(%rdi)
    addq $8, %rdi
    jmp loop

saifora:
    leave
    ret

