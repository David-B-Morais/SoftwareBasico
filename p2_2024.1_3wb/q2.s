.text
.globl boba

boba:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)

    movss %xmm0, -32(%rbp)
    leaq -72(%rbp), %r13
    movl $0, %ebx

for:
    cmpl $5, %ebx
    jge saifora

    movss -32(%rbp), %xmm0
    call calcula
    movl %eax, %r12d

    movslq %r12d, %rdx
    imulq $8, %rdx
    addq %r13, %rdx

    movss -32(%rbp), %xmm0
    cvtss2sd %xmm0, %xmm0
    movsd (%rdx), %xmm1
    addsd %xmm0, %xmm1
    movsd %xmm1, (%rdx)

    incl %ebx
    jmp for

saifora:
    movsd -72(%rbp), %xmm0
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    movq -24(%rbp), %r13
    leave
    ret