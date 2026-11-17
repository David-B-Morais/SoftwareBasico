.text
.globl foo

foo:

while:
    cmpl $0, %esi
    je saifora

    decl %esi

    xorpd %xmm0, %xmm0
    movsd %xmm0, (%rdi)
    addq $8, %rdi

    jmp while

saifora:
    ret