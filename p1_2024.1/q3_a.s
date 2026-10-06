.text
.globl corta

corta:
    movsbl %dil, %eax
    addl %esi, %eax
    ret