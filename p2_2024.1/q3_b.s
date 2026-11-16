.text
.globl boo

boo:
    pushq %rbp
    movq %rsp, %rbp
    subq $64, %rsp

    movsd %xmm0, -8(%rbp) /* d */
    movss %xmm1, -12(%rbp) /* bias */
    
    movl $0, -16(%rbp) /* i */

for:
    cmpl $5, -16(%rbp)
    jge saifora

    movsd -8(%rbp), %xmm0
    call inv

    cvtsd2ss %xmm0, %xmm0

    movq %rbp, %rax
    subq $56, %rax /* rax = endereço de temp[0] */

    movslq -16(%rbp), %rcx
    imulq $8, %rcx

    addq %rcx, %rax

    movss %xmm0, (%rax) /* temp[i].val = inv(d) */
    movl -16(%rbp), %ecx
    movl %ecx, 4(%rax)

    incl -16(%rbp)
    jmp for

saifora:
    movss -56(%rbp), %xmm0
    addss -12(%rbp), %xmm0

    leave
    ret
