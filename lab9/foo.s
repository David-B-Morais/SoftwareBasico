.text
.globl foo

foo:
    movl $0, %ebx
    movl $0, %ecx

L1:
    cmpl %ebx, %esi
    je L2

    movslq %ebx, %rax /* transforma i em 64 bits */

    addl (%rdi, %rax, 4), %ecx /* s += a[i] -> %rdi + %rax * 4 */

    cmpl $0, (%rdi, %rax, 4)
    jne L3

    movl %ecx, (%rdi, %rax, 4)
    movl $0, %ecx

L3:
    addl $1, %ebx
    jmp L1

L2:
    ret