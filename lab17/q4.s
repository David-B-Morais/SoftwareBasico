.text
.globl pack1

pack1:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)

    movq %rdi, %rbx
    movl %esi, %r12d

    xorpd %xmm0, %xmm0
    movsd %xmm0, -32(%rbp)

    movl $0, %r13d

for:
    cmpl %r12d, %r13d
    jge saifora

    mosvlq %r13d, %rcx
    imulq $8, %rcx
    addq %rbx, %rcx

    movl (%rbx), %edi
    movss 4(%rbx), %xmm0
    cvtss2sd %xmm0, %xmm0
    call foo

    movsd -32(%rbp), %xmm1
    addsd %xmm0, %xmm1
    movsd %xmm1, -32(%rbp)

    incl %r13d
    jmp for

saifora:
    movsd -32(%rbp), %xmm0
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    movq -24(%rbp), %r13
    leave
    ret