.text
.globl foo

foo:
    pushq %rbp
    movq %rsp, %rbp
    subq $32, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)

    movq %rdi, %r12 /* %r12 = st *(sobrevive às chamadas) */
    movss %xmm0, -28(%rbp)

    xorpd %xmm0, %xmm0
    movsd %xmm0, -24(%rbp)
    
    movl $0, %ebx

for:
    cmpl $5, %ebx
    jge saifora

    movslq %ebx, %rcx
    imulq $8, %rcx
    addq %r12, %rcx

    movw %bx, (%rcx)

    movss 4(%rcx), %xmm0
    movss -28(%rbp), %xmm1
    call boba

    cvtss2sd %xmm0, %xmm0
    addsd -24(%rbp), %xmm0
    movsd %xmm0, -24(%rbp)

    incl %ebx
    jmp for

saifora:
    movsd -24(%rbp), %xmm0
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    leave
    ret
