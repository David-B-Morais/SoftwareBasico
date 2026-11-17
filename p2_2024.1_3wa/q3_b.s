.text
.globl boo

boo:
    pushq %rbp
    movq %rsp, %rbp
    subq $80, %rsp

    movq %rbx, -8(%rbp)
    movq %r12, -16(%rbp)

    leaq -56(%rbp), %r12

    movsd %xmm0, -64(%rbp)
    movss %xmm1, -72(%rbp) 

    movl $0, %ebx

for:
    cmpl $5, %ebx
    jge saifora

    movsd -64(%rbp), %xmm0
    call inv

    movslq %ebx, %rcx
    imulq $8, %rcx
    addq %r12, %rcx

    cvtsd2ss %xmm0, %xmm0
    movss %xmm0, (%rcx)
    movl %ebx, 4(%rcx)

    incl %ebx
    jmp for

saifora:
    movss (%r12), %xmm0
    movss -72(%rbp), %xmm1
    addss %xmm1, %xmm0
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    leave
    ret