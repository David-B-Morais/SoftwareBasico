.text
.globl foo

foo:
    incl %edi
    movl %edi, %eax
    ret
