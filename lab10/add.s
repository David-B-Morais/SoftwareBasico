.text
.globl add

add:
    pushq %rbp
    movq %rsp,%rbp
    
    movl $0, %eax
    
for:
    cmpq $0, %rdi
    je saifora

    addl (%rdi), %eax

    movq 8(%rdi), %rdi
    jmp for

saifora:
    leave /* devolve o %rsp no valor original e faz o copy %rbp */
    ret