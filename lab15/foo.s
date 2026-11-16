.text
.globl foo

foo:
    movsd %xmm0, %xmm8
    movsd %xmm0, %xmm9

    cvtss2sd %xmm1, %xmm1

    addsd %xmm1, %xmm8
    subsd %xmm1, %xmm9
    
    mulsd %xmm9, %xmm8
    
    cvtsd2ss %xmm8, %xmm0
    
    ret
