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

    xorps %xmm0, %xmm0
    movss %xmm0, -36(%rbp)

for:
    cmpl %r12d, %r14d
    jge saifora
    
    movslq %r14d, %rcx
    imulq $2, %rcx
    addq %rbx, %rcx

    movswq (%rcx), %rax
    cmpq %rax, %r13
    jge saidoif

    movq %rcx, %rdi
    movl $3, %esi
    call passa_alta

    movss -36(%rbp), %xmm1
    cvtss2sd %xmm1, %xmm1
    addsd %xmm0, %xmm1
    cvtsd2ss %xmm1, %xmm1
    movss %xmm1, -36(%rbp)
    

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