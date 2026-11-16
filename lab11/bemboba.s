.text
.globl bemboba

bemboba:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    leaq -16(%rbp), %rax
    movl $0, %ecx

for:
    cmpl $4, %ecx
    jge saifora

    movl %edi, (%rax)
    addq $4, %rax

    incl %ecx
    jmp for

saifora:
    leaq -16(%rbp), %rdi
    movl $4, %esi
    call addl
    
    leave
    ret

