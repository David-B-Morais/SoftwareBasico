.text
.globl foo

foo:
    pushq %rbp
    movq %rsp, %rbp
    subq $48, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)
    movq %r13, -24(%rbp)
    movq %r14, -32(%rbp)

    movq %rdi, %rbx
    movl %esi, %r12d
    movq %rdx, %r13

    movl $0, %r14d
    
    xorpd %xmm0, %xmm0
    movsd %xmm0, -40(%rbp)

for:
    cmpl %r12d, %r14d
    jge saifora

    movslq %r14d, %rcx
    imulq $2, %rcx
    addq %rbx, %rcx

    movswq (%rcx), %r8
    cmpq %r8, %r13
    jge saidoif
    
    movq %rcx, %rdi
    movl $3, %esi
    call passa_alta

    cvtss2sd %xmm0, %xmm0
    movsd -40(%rbp), %xmm1
    addsd %xmm0, %xmm1
    movsd %xmm1, -40(%rbp)

saidoif:
    incl %r14d
    jmp for

saifora:
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    movq -24(%rbp), %r13
    movq -32(%rbp), %r14
    leave
    ret