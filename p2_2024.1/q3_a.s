.text
.globl foo

foo:
    movl %esi, %ecx
    xorpd %xmm1, %xmm1

while:
    cmpl $0, %ecx
    decl %ecx
    je saifora

    movsd %xmm1, (%rdi)
    addq $8, %rdi

    jmp while

saifora:
    ret
