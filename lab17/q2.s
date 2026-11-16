.text
.globl foo

foo:
    imull $-1, %edi
    cvtsi2sd %edi, %xmm1
    mulsd %xmm1, %xmm0
    ret