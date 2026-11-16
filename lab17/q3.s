.text
.globl pack

pack:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

    movq %rbx, -8(%rbp)

    movq %rdi, %rbx
    
    xorpd %xmm0, %xmm0
    movsd %xmm0, -16(%rbp)

while:
    cmpq $0, %rbx
    je saifora

    movsd 8(%rbx), %xmm0
    movl (%rbx), %edi
    call foo

    movsd -16(%rbp), %xmm1
    addsd %xmm0, %xmm1
    movsd %xmm1, -16(%rbp)

    movq 16(%rbx), %rbx
    jmp while

saifora:
    movsd -16(%rbp), %xmm0
    movq -8(%rbp), %rbx
    leave
    ret