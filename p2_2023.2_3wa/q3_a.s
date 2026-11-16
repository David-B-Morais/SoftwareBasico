.text
.globl acerta

acerta:
    movslq %esi, %rcx
    imulq $4, %rcx
    addq %rdi, %rcx
    movl (%rcx), %eax
    ret