.data
msg: .string "numero: "
fmt: .string "%d"

.text
.globl novonum

novonum:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp
    
    movq $msg, %rdi
    call printf

    movq $fmt, %rdi
    leaq -4(%rbp), %rsi
    call scanf
    
    movl -4(%rbp), %eax
    
    leave
    ret